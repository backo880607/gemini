#include "../public/Memory.h"
#include <mutex>

namespace gemini {

Boolean operator<(const MemoryChunk& lhs, void* rhs) {
  return lhs.pData_ < rhs;
}
Boolean operator<(void* lhs, const MemoryChunk& rhs) { return rhs < lhs; }

MemoryHoldChunk::MemoryHoldChunk() {}

MemoryHoldChunk::~MemoryHoldChunk() {}

void* MemoryHoldChunk::allocateImpl(size_t size) {
  void* p = 0;
  _mutex.lock();
  if (_freeBlocks.empty()) {
    if (_chunks.empty() || _chunks.back().blocksAvailable_ <= 0) {
      MemoryChunk newChunk;
      newChunk.init(size, MEM_BLOCKS_MAX);
      _chunks.push_back(newChunk);
    }

    p = _chunks.back().allocate(size);
  } else {
    p = _freeBlocks.back();
    _freeBlocks.pop_back();
  }
  _mutex.unlock();
  return p;
}

void MemoryHoldChunk::deallocateImpl(void* p) {
  _mutex.lock();
  _freeBlocks.push_back(p);
  _mutex.unlock();
}

void MemoryHoldChunk::clearImpl() {
  for (Chunks::iterator iter = _chunks.begin(); iter != _chunks.end(); ++iter) {
    iter->release();
  }

  _chunks.clear();
  _freeBlocks.clear();
}

MemoryChunk::MemoryChunk(unsigned char* val)
    : canFree_(false),
      pData_(val),
      firstAvailableBlock_(0),
      blocksAvailable_(0) {}

void MemoryChunk::init(std::size_t blockSize, unsigned char blocks) {
  if (pData_ == nullptr) pData_ = new unsigned char[blockSize * blocks];

  reset(blockSize, blocks);
}

void MemoryChunk::reset(std::size_t blockSize, unsigned char blocks) {
  firstAvailableBlock_ = 0;
  blocksAvailable_ = blocks;

  unsigned char i = 0;
  unsigned char* p = pData_;
  for (; i != blocks; p += blockSize) {
    memset(p, 0, blockSize);
    *p = ++i;
  }
}

void* MemoryChunk::allocate(std::size_t blockSize) {
  if (!blocksAvailable_) return nullptr;

  unsigned char* pResult = pData_ + (firstAvailableBlock_ * blockSize);
  firstAvailableBlock_ = *pResult;
  --blocksAvailable_;

  return pResult;
}

void MemoryChunk::deallocate(void* p, std::size_t blockSize) {
  unsigned char* toRelease = static_cast<unsigned char*>(p);
  *toRelease = firstAvailableBlock_;
  firstAvailableBlock_ =
      static_cast<unsigned char>((toRelease - pData_) / blockSize);
  ++blocksAvailable_;
}

void MemoryChunk::release() {
  if (canFree_) delete[] pData_;
}

FixedAllocator::FixedAllocator()
    : _blockSize(0),
      _numBlocks(0),
      _pAllocChunk(nullptr),
      _pDeallocChunk(nullptr) {}

FixedAllocator::~FixedAllocator() {
  for (MemoryChunk& mem : _chunks) {
    mem.release();
  }
}

void FixedAllocator::init(std::size_t blockSize, unsigned char numBlocks) {
  _blockSize = blockSize;
  _numBlocks = numBlocks;
  _pAllocChunk = _pDeallocChunk = nullptr;
}

void* FixedAllocator::allocateImpl(std::size_t size) {
  std::unique_lock<SpinMutex> locker(_mutex);
  if (_pAllocChunk == 0 || _pAllocChunk->blocksAvailable_ == 0) {
    for (Chunks::iterator i = _chunks.begin();; ++i) {
      if (i == _chunks.end()) {
        MemoryChunk newChunk;
        newChunk.init(size, _numBlocks);
        _chunks.push_back(newChunk);
        _pAllocChunk = &_chunks.back();
        _pDeallocChunk = &_chunks.front();
        break;
      }
      if (i->blocksAvailable_ > 0) {
        _pAllocChunk = &*i;
        break;
      }
    }
  }

  return _pAllocChunk->allocate(size);
}
void FixedAllocator::deallocateImpl(void* p) {
  std::unique_lock<SpinMutex> locker(_mutex);
  const std::size_t chunkLength = _numBlocks * _blockSize;
  MemoryChunk* lo = _pDeallocChunk;
  MemoryChunk* hi = _pDeallocChunk + 1;
  MemoryChunk* loBound = &_chunks.front();
  MemoryChunk* hiBound = &_chunks.back() + 1;
  void* pTemp = p;

  if (hi == hiBound) hi = 0;
  for (;;) {
    if (lo) {
      if (pTemp >= lo->pData_ && pTemp < lo->pData_ + chunkLength) {
        _pDeallocChunk = lo;
        break;
      }
      if (lo == loBound)
        lo = 0;
      else
        --lo;
    }

    if (hi) {
      if (pTemp >= hi->pData_ && pTemp < hi->pData_ + chunkLength) {
        _pDeallocChunk = hi;
        break;
      }
      if (++hi == hiBound) hi = 0;
    }
  }

  _pDeallocChunk->deallocate(pTemp, _blockSize);
  if (_pDeallocChunk->blocksAvailable_ == _numBlocks) {
    MemoryChunk& lastChunk = _chunks.back();
    if (&lastChunk == _pDeallocChunk) {
      return;
    }
    if (lastChunk.blocksAvailable_ == _numBlocks) {
      lastChunk.release();
      _chunks.pop_back();
      _pAllocChunk = _pDeallocChunk;
    } else {
      std::swap(*_pDeallocChunk, lastChunk);
      _pAllocChunk = &_chunks.back();
    }
  }
}

Memory::Memory() {}

Memory::~Memory() { m_vecMem.clear(); }

static const std::size_t g_MinSize = 4;
void* Memory::allocate(std::size_t size) {
  std::size_t index = size / g_MinSize;
  _mutex.lock();
  if (index > m_vecMem.size()) {
    m_vecMem.resize(index);
  }

  data_type& memBk = m_vecMem[index - 1];
  if (memBk == nullptr) {
    memBk = data_type(new mem_type());
    memBk->init(size, MEM_BLOCKS_MAX);
  }

  _mutex.unlock();
  return memBk->allocateImpl(size);
}

void Memory::deallocate(void* p, std::size_t size) {
  std::size_t index = size / g_MinSize;
  _mutex.lock();
  data_type& memBk = m_vecMem[index - 1];
  _mutex.unlock();
  memBk->deallocateImpl(p);
}

}  // namespace gemini