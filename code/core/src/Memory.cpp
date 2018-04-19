#include "Memory.h"

namespace gemini {

void InitChunk(MemChunk& mem, std::size_t blockSize, UChar blocks) {
	assert(blockSize > 0);
	assert(blocks > 0);
	// Overflow check
	assert((blockSize * blocks) / blockSize == blocks);

	mem.firstAvailableBlock_ = 0;
	mem.blocksAvailable_ = blocks;
	if (mem.pData_ == nullptr)
		mem.pData_ = new UChar[blockSize * blocks];

	UChar i = 0;
	UChar* p = mem.pData_;
	for (; i != blocks; p += blockSize)
	{
		memset(p, 0, blockSize);
		*p = ++i;
	}
}

void* AllocateChunk(MemChunk& mem, std::size_t blockSize) {
	if (!mem.blocksAvailable_) return nullptr;

	assert((mem.firstAvailableBlock_ * blockSize) / blockSize ==
		mem.firstAvailableBlock_);

	UChar* pResult = mem.pData_ + (mem.firstAvailableBlock_ * blockSize);
	mem.firstAvailableBlock_ = *pResult;
	--mem.blocksAvailable_;

	return pResult;
}
void DeallocateChunk(MemChunk& mem, void* p, std::size_t blockSize) {
	assert(p >= mem.pData_);

	UChar* toRelease = static_cast<UChar*>(p);
	assert((toRelease - mem.pData_) % blockSize == 0);

	*toRelease = mem.firstAvailableBlock_;
	mem.firstAvailableBlock_ = static_cast<UChar>(
		(toRelease - mem.pData_) / blockSize);
	assert(mem.firstAvailableBlock_ == (toRelease - mem.pData_) / blockSize);

	++mem.blocksAvailable_;
}

void ReleaseChunk(MemChunk& mem)
{
	if (mem.canFree_) {
		delete[] mem.pData_;
	}
}

FixedAllocator::FixedAllocator()
	: m_blockSize(0)
	, m_numBlocks(0)
	, m_pAllocChunk(nullptr)
	, m_pDeallocChunk(nullptr)
{

}

FixedAllocator::~FixedAllocator()
{
	for (MemChunk& mem : m_chunks)
	{
		ReleaseChunk(mem);
	}
}

void FixedAllocator::init(std::size_t blockSize, UInt numBlocks)
{
	m_blockSize = blockSize;
	m_numBlocks = numBlocks;
	m_pAllocChunk = m_pDeallocChunk = nullptr;
}

void* FixedAllocator::allocateImpl()
{
	const std::size_t multiple = m_blockSize / 4;
	assert((multiple * 4) == m_blockSize);
	if (m_pAllocChunk == 0 || m_pAllocChunk->blocksAvailable_ == 0)
	{
		for (Chunks::iterator i = m_chunks.begin(); ; ++i)
		{
			if (i == m_chunks.end())
			{
				MemChunk newChunk;
				InitChunk(newChunk, multiple, m_numBlocks);
				m_chunks.push_back(newChunk);
				m_pAllocChunk = &m_chunks.back();
				m_pDeallocChunk = &m_chunks.front();
				break;
			}
			if (i->blocksAvailable_ > 0)
			{
				m_pAllocChunk = &*i;
				break;
			}
		}
	}

	return AllocateChunk(*m_pAllocChunk, multiple);
}

void FixedAllocator::deallocateImpl(void* p)
{
	assert(!m_chunks.empty());
	assert(m_pDeallocChunk);
	const std::size_t chunkLength = m_numBlocks * m_blockSize;
	MemChunk* lo = m_pDeallocChunk;
	MemChunk* hi = m_pDeallocChunk + 1;
	MemChunk* loBound = &m_chunks.front();
	MemChunk* hiBound = &m_chunks.back() + 1;
	void* pTemp = p;

	if (hi == hiBound) hi = 0;
	for (;;)
	{
		if (lo)
		{
			if (pTemp >= lo->pData_ && pTemp < lo->pData_ + chunkLength)
			{
				m_pDeallocChunk = lo;
				break;
			}
			if (lo == loBound) lo = 0;
			else --lo;
		}

		if (hi)
		{
			if (pTemp >= hi->pData_ && pTemp < hi->pData_ + chunkLength)
			{
				m_pDeallocChunk = hi;
				break;
			}
			if (++hi == hiBound) hi = 0;
		}
	}
	assert(m_pDeallocChunk->pData_ <= pTemp);
	assert(m_pDeallocChunk->pData_ + m_numBlocks*m_blockSize > pTemp);
	DeallocateChunk(*m_pDeallocChunk, pTemp, m_blockSize);
	if (m_pDeallocChunk->blocksAvailable_ == m_numBlocks)
	{
		MemChunk& lastChunk = m_chunks.back();
		if (&lastChunk == m_pDeallocChunk)
		{
			return;
		}
		if (lastChunk.blocksAvailable_ == m_numBlocks)
		{
			ReleaseChunk(lastChunk);
			m_chunks.pop_back();
			m_pAllocChunk = m_pDeallocChunk;
		}
		else
		{
			std::swap(*m_pDeallocChunk, lastChunk);
			m_pAllocChunk = &m_chunks.back();
		}
	}
}

void* MemoryHoldChunk::allocateImpl()
{
	void* p = 0;
	if (m_freeBlocks.empty())
	{
		const std::size_t multiple = m_blockSize / 4;
		assert((multiple * 4) == m_blockSize);
		if (m_chunks.empty() || m_chunks.back().blocksAvailable_ <= 0)
		{
			MemChunk newChunk;
			InitChunk(newChunk, multiple, m_numBlocks);
			m_chunks.push_back(newChunk);
		}

		p = AllocateChunk(m_chunks.back(), multiple);
	}
	else
	{
		p = m_freeBlocks.back();
		m_freeBlocks.pop_back();
	}
	return p;
}

void MemoryHoldChunk::deallocateImpl(void* p)
{
	m_freeBlocks.push_back(p);
}

void MemoryHoldChunk::clear()
{
	for (Chunks::iterator iter = m_chunks.begin();
		iter != m_chunks.end(); ++iter)
	{
		ReleaseChunk(*iter);
	}

	m_chunks.clear();
	m_freeBlocks.clear();
}

}