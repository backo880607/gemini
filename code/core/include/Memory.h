#ifndef GEMINI_Memory_INCLUDE
#define GEMINI_Memory_INCLUDE
#include "../public/Common.h"

namespace gemini {

#ifndef MEM_BLOCKS_MAX
#define MEM_BLOCKS_MAX	255
#endif

#ifndef MEM_BLOCKSIZE_MAX  
#define MEM_BLOCKSIZE_MAX 64  
#endif

struct MemChunk
{
	Boolean canFree_;
	UChar* pData_;	// ����ڴ��׵�ַ
	UChar firstAvailableBlock_;	// ��һ��������������
	UChar blocksAvailable_;		// ��������ĸ���
};

class CORE_API FixedAllocator
{
	typedef std::vector<MemChunk> Chunks;
public:
	FixedAllocator();
	~FixedAllocator();
	void init(std::size_t blockSize, UInt numBlocks);

	void* allocateImpl();
	void deallocateImpl(void* p);

	const std::size_t blockSize() const { return m_blockSize; }

private:
	UInt m_numBlocks;
	std::size_t m_blockSize;
	MemChunk* m_pAllocChunk;  // �ϴη����Chunk
	MemChunk* m_pDeallocChunk; // �ϴ��ͷŵ�Chunk
	Chunks m_chunks;
};

// the template parameter is a multiple of 4
template <UInt Size, UInt Numbers>
class MemoryT : public FixedAllocator
{
protected:
	MemoryT() { FixedAllocator::init(Size, Numbers); }
	~MemoryT() {};
	MemoryT(const MemoryT&) {}
	MemoryT& operator= (const MemoryT&) { return *this; }
public:

	template <typename T>
	T* allocate() {
		static_assert(sizeof(T) == Size);
		T* p = (T*)allocateImpl();
		return new (p)T();
	}
	template <typename T>
	void deallocate(T* p) {
		p->~T();
		deallocateImpl(p);
	}
};

class CORE_API Memory4Bytes : public MemoryT<4, 1000>
{
public:
	static Memory4Bytes& instance() { static Memory4Bytes obj; return obj; }
};
class CORE_API Memory8Bytes : public MemoryT<8, 1000000>
{
public:
	static Memory8Bytes& instance() { static Memory8Bytes obj; return obj; }
};

class CORE_API MemoryHoldChunk
{
	typedef std::vector<MemChunk> Chunks;			// ����������ڴ�
	typedef std::vector<void*> FreeBlocks;		// ���п���������׵�ַ�б�
public:
	MemoryHoldChunk(std::size_t blockSize, UInt numBlocks) : m_numBlocks(numBlocks), m_blockSize(blockSize) {}
	~MemoryHoldChunk() { clear(); }

	void* allocateImpl();
	void deallocateImpl(void* p);

	void clear();
private:
	UInt m_numBlocks;
	std::size_t m_blockSize;
	Chunks m_chunks;
	FreeBlocks m_freeBlocks;
};

// the size of T must is the multiple of 4
template <typename T, std::size_t NumBlocks = 1000>
class MemoryHold : public MemoryHoldChunk
{
	//static_assert(sizeof(T) % 4 == 0);
	typedef T		value_type;
	typedef T*		stored_type;
public:
	MemoryHold() : MemoryHoldChunk(sizeof(T), NumBlocks) {}
	~MemoryHold() { }
	stored_type allocate() {
		void* p = allocateImpl();
		return new (static_cast<stored_type>(p))value_type();
	}

	// ������������б���
	void deallocate(stored_type p, std::size_t num = 1) {
		p->~value_type();
		deallocateImpl(p);
	}
};

}

#endif	// GEMINI_Memory_INCLUDE