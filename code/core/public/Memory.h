#ifndef GEMINI_Memory_INCLUDE
#define GEMINI_Memory_INCLUDE
#include "Common.h"

namespace gemini {

// �����ɷ���Ķ������������Ϊ255����һ��unsigned char�ɱ�ʾ�Ĵ�С��
#ifndef MEM_BLOCKS_MAX
#define MEM_BLOCKS_MAX 255
#endif

#ifndef MEM_BLOCKSIZE_MAX
#define MEM_BLOCKSIZE_MAX 64
#endif

// ����ڴ���Ϣ
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
  unsigned char* pData_;               // ����ڴ��׵�ַ
  unsigned char firstAvailableBlock_;  // ��һ��������������
  unsigned char blocksAvailable_;      // ��������ĸ���
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
  MemoryChunk* _pAllocChunk;    // �ϴη����Chunk
  MemoryChunk* _pDeallocChunk;  // �ϴ��ͷŵ�Chunk
  Chunks _chunks;
  SpinMutex _mutex;
};

class CORE_API MemoryHoldChunk {
  typedef std::vector<MemoryChunk> Chunks;  // ����������ڴ�
  typedef std::vector<void*> FreeBlocks;  // ���п���������׵�ַ�б�
 public:
  MemoryHoldChunk();
  ~MemoryHoldChunk();

  void* allocateImpl(size_t size);
  // ������������б���
  void deallocateImpl(void* p);

  // ���ѷ���Ĵ���ڴ�ȫ���黹��ϵͳ
  void clearImpl();

 private:
  Chunks _chunks;
  FreeBlocks _freeBlocks;
  SpinMutex _mutex;
};

// �����˼����ͷŹ��ܣ�����ChunkΪ�գ����黹ϵͳ�����ǹ��´η���ʹ��
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

  // ������������б���
  void deallocate(stored_type p, size_t num = 1) {
    p->~value_type();
    deallocateImpl(p);
  }

  // ���ѷ���Ĵ���ڴ�ȫ���黹��ϵͳ
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