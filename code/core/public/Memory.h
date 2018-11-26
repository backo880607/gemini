#ifndef GEMINI_Memory_INCLUDE
#define GEMINI_Memory_INCLUDE
#include "Common.h"

namespace gemini {

// 块最大可分配的对象个数，限制为255（即一个unsigned char可表示的大小）
#ifndef MEM_BLOCKS_MAX
#define MEM_BLOCKS_MAX 255
#endif

#ifndef MEM_BLOCKSIZE_MAX
#define MEM_BLOCKSIZE_MAX 64
#endif

// 大块内存信息
struct CORE_API MemoryChunk {
  MemoryChunk()
      : canFree_(true),
        pData_(nullptr),
        firstAvailableBlock_(0),
        blocksAvailable_(0) {}
  MemoryChunk(unsigned char* val);
  ~MemoryChunk() {}

  void init(std::size_t blockSize, unsigned char blocks);
  void reset(std::size_t blockSize, unsigned char blocks);
  void* allocate(std::size_t blockSize);
  void deallocate(void* p, std::size_t blockSize);
  void release();

  Boolean canFree_;
  unsigned char* pData_;               // 大块内存首地址
  unsigned char firstAvailableBlock_;  // 第一个可用区块索引
  unsigned char blocksAvailable_;      // 可以区块的个数
};

class CORE_API FixedAllocator {
  typedef std::vector<MemoryChunk> Chunks;

 public:
  FixedAllocator();
  ~FixedAllocator();

  void init(std::size_t blockSize, unsigned char numBlocks);

  void* allocateImpl(std::size_t size);
  void deallocateImpl(void* p);

  std::size_t blockSize() const { return _blockSize; }

 private:
  std::size_t _blockSize;
  unsigned char _numBlocks;
  MemoryChunk* _pAllocChunk;    // 上次分配的Chunk
  MemoryChunk* _pDeallocChunk;  // 上次释放的Chunk
  Chunks _chunks;
  SpinMutex _mutex;
};

class CORE_API MemoryHoldChunk {
  typedef std::vector<MemoryChunk> Chunks;  // 管理多个大块内存
  typedef std::vector<void*> FreeBlocks;  // 所有空闲区块的首地址列表
 public:
  MemoryHoldChunk();
  ~MemoryHoldChunk();

  void* allocateImpl(size_t size);
  // 放入空闲区块列表即可
  void deallocateImpl(void* p);

  // 将已分配的大块内存全部归还给系统
  void clearImpl();

 private:
  Chunks _chunks;
  FreeBlocks _freeBlocks;
  SpinMutex _mutex;
};

// 分配了即不释放功能，即当Chunk为空，不归还系统，而是供下次分配使用
template <typename T, std::size_t NumBlocks = 255>
class MemoryHold : public MemoryHoldChunk {
  typedef T value_type;
  typedef T* stored_type;

 public:
  MemoryHold() {}
  ~MemoryHold() { clear(); }

  stored_type allocate(size_t size) {
    void* p = allocateImpl(size);
    return new (static_cast<stored_type>(p)) value_type();
  }

  // 放入空闲区块列表即可
  void deallocate(stored_type p, size_t num = 1) {
    p->~value_type();
    deallocateImpl(p);
  }

  // 将已分配的大块内存全部归还给系统
  void clear() { clearImpl(); }
};

class CORE_API Memory {
  typedef FixedAllocator mem_type;
  typedef std::shared_ptr<mem_type> data_type;

 public:
  Memory();
  ~Memory();

  void* allocate(std::size_t size);
  void deallocate(void* p, std::size_t size);

  static const std::size_t MinSize = sizeof(void*);

 private:
  std::vector<data_type> m_vecMem;
  SpinMutex _mutex;
};

}
#endif  // GEMINI_Memory_INCLUDE