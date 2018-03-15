#include "../../public/api/MsgData.h"
#include "../../public/Buffer.h"

#include <mutex>

#include <boost/asio/streambuf.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/array.hpp>

#if GEMINI_OS == GEMINI_OS_LINUX
#include <netinet/in.h>
#elif GEMINI_OS == GEMINI_OS_WINDOWS_NT
#include <Winsock2.h>
#include "../../../../third_party/DataCompress/zlib.h"
#endif

namespace gemini {

uint8_t s_key[] = { 0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c };
uint8_t s_iv[] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f };
const UInt AES_BLOCK_LEN = 16;

//const UInt _S_MsgTypes[] = { MsgType::MSG_RealTime, MsgType::MSG_History, MsgType::MSG_Cur5Minutes, MsgType::MSG_SliceTime, MsgType::MSG_ExRight, 0 };
//const std::size_t _S_MsgTypesLen = (sizeof(_S_MsgTypes) / sizeof(_S_MsgTypes[0])) - 1;
MsgData::MsgData()
{
	memset(&_head, 0, s_msgHeadSize);
	setType(MSG_TYPE_NORMAL);
	setFunctionID(0);
	setDataType(DataType::DT_MEMSEQ);
	setEncoding(EncodingType::Encoding_UTF32);
	setCompressType(CompressType::CPT_NONE);
	setEncryption(Encryption::Encry_None);
	setPriority(0);
	setSeq(0);
}

MsgData::~MsgData()
{
}

const Char* MsgData::getDataBuffer()
{
	return boost::asio::buffer_cast<const Char*>(_data->data());
}

UInt MsgData::getAESCBCSize() const
{
	if (getEncryption() != Encryption::Encry_AES)
		return getDataSize();

	UInt remainders = getDataSize() % AES_BLOCK_LEN;
	return remainders == 0 ? getDataSize() : (getDataSize() + (AES_BLOCK_LEN - remainders));
}

void MsgData::networkToHost()
{
	UShort* ptr = (UShort*)&getHead();
	*ptr = ntohs(*ptr);
	++ptr;
	*ptr = ntohs(*ptr);
	getHead().seq = ntohs(getHead().seq);
	getHead().size = ntohs(getHead().size);
	getHead().originSize = ntohl(getHead().originSize);
	getHead().id = ntohl(getHead().id);
}

void MsgData::hostToNetwork()
{
	UShort* ptr = (UShort*)&getHead();
	*ptr = htons(*ptr);
	++ptr;
	*ptr = htons(*ptr);
	getHead().seq = htons(getHead().seq);
	getHead().size = htons(getHead().size);
	getHead().originSize = htonl(getHead().originSize);
	getHead().id = htonl(getHead().id);
}

MsgData::mutable_buffer MsgData::prepare()
{
	const std::size_t size = getAESCBCSize() - boost::asio::buffer_size(_data->data());
	boost::asio::streambuf::mutable_buffers_type buffer = _data->prepare(size > s_maxBlock ? s_maxBlock : size);
	return mutable_buffer(buffer.data(), buffer.size());
}

MsgData::mutable_buffer MsgData::prepare(std::size_t size)
{
	boost::asio::streambuf::mutable_buffers_type buffer = _data->prepare(size);
	return mutable_buffer(buffer.data(), buffer.size());
}

Boolean MsgData::commit(std::size_t size)
{
	_data->commit(size);
	return getAESCBCSize() == boost::asio::buffer_size(_data->data());
}

Boolean MsgData::step(UInt pos, const Char*& data, UInt& size)
{
	UInt buffSize = boost::asio::buffer_size(_data->data());
	if (pos >= buffSize)
		return false;

	UInt len = buffSize - pos;
	data = boost::asio::buffer_cast<const Char*>(_data->data()) + pos;
	size = len > s_maxBlock ? s_maxBlock : len;
	return true;
}

Boolean MsgData::valid() const
{
	return getDataSize() > 0 && getAESCBCSize() == boost::asio::buffer_size(_data->data());
}

Boolean MsgData::format()
{
	const Char* pData = boost::asio::buffer_cast<const Char*>(_data->data());
	const UInt size = boost::asio::buffer_size(_data->data());
	return format(pData, size);
}

std::mutex g_zlibMutex;
Boolean MsgData::format(const void* pData, std::size_t size)
{
	const CompressType cpt = getCompressType();
	const Encryption encry = getEncryption();
	if (cpt == CompressType::CPT_NONE && encry == Encryption::Encry_None)
	{
		getHead().size = size;
		getHead().originSize = size;
		if (pData != boost::asio::buffer_cast<const Char*>(_data->data()))
		{
			_data->consume(_data->size());
			_data->prepare(getHead().size);
			_data->sputn((const char*)pData, getHead().size);
		}
		return true;
	}

	std::size_t postCompressSize = (size + 12) * 1.1;
	//Char* comBuf = (Char*)malloc(postCompressSize*sizeof(Char));
	Buffer<Char> comBuf(postCompressSize + 16);
	const Char* data = nullptr;
	// 压缩处理
	if (cpt == CompressType::CPT_ZLIB) {
		Int rt = compress((Bytef*)comBuf.begin(), (uLongf*)&postCompressSize, (const Bytef *)pData, (uLong)size);
		if (rt != Z_OK)
		{
			//LOG(Logger::LOG_INFO).Log("数据压缩错误	rt: ").Log(rt);
			return false;
		}
		comBuf[postCompressSize / sizeof(Char)] = 0;

		data = comBuf.begin();
		getHead().size = postCompressSize;
		getHead().originSize = size;
	}
	else if (cpt == CompressType::CPT_NONE) {
		memcpy(comBuf.begin(), pData, size);
		data = comBuf.begin();
		getHead().size = size;
		getHead().originSize = size;
	}
	else {
		return false;
	}


	// 加密处理
	if (encry == Encryption::Encry_AES)
	{
		std::unique_lock<std::mutex> locker(g_zlibMutex);
		Buffer<Char> encryBuf(getAESCBCSize() + 16);
		//Char* encryBuf = (Char*)malloc(getAESCBCSize() * sizeof(Char));
		//AES128_CBC_encrypt_buffer((uint8_t*)encryBuf.begin(), (uint8_t*)data, (uint32_t)getHead().size, s_key, s_iv);
		_data->consume(_data->size());
		_data->prepare(getAESCBCSize());
		_data->sputn(encryBuf.begin(), getAESCBCSize());
		//free(encryBuf);
	}
	else
	{
		if (data != boost::asio::buffer_cast<const Char*>(_data->data()))
		{
			_data->consume(_data->size());
			_data->prepare(getHead().size);
			_data->sputn(data, getHead().size);
		}
	}

	comBuf.reset();
	return true;
}

Boolean MsgData::parse()
{
	const Char* data = boost::asio::buffer_cast<const Char*>(_data->data());

	// 解密
	Encryption encry = getEncryption();
	if (encry == Encryption::Encry_AES)
	{
		std::unique_lock<std::mutex> locker(g_zlibMutex);
		Buffer<Char> decryBuf(getAESCBCSize());
		//AES128_CBC_decrypt_buffer((uint8_t*)decryBuf.begin(), (uint8_t*)data, (uint32_t)getAESCBCSize(), s_key, s_iv);
		_data->consume(_data->size());
		_data->prepare(getHead().size);
		_data->sputn(decryBuf.begin(), getHead().size);
		setEncryption(Encryption::Encry_None);
		data = boost::asio::buffer_cast<const Char*>(_data->data());
		decryBuf.reset();
	}

	// 解压
	const CompressType cpt = getCompressType();
	if (cpt == CompressType::CPT_ZLIB)
	{
		UInt originSize = getOriginSize();
		uLongf bufSize = (uLongf)(originSize*1.1 + 12);
		Buffer<Char> buf(bufSize);
		Int rt = uncompress((Bytef*)buf.begin(), &bufSize,
			(const Bytef *)data, (uLong)getHead().size);
		if (rt != Z_OK || bufSize != originSize)
		{
			//LOG(Logger::LOG_INFO).Log("数据解压错误	rt: ").Log(rt);
			return false;
		}

		buf[originSize] = '\0';
		setCompressType(CompressType::CPT_NONE);
		getHead().size = originSize;
		_data->consume(_data->size());
		_data->prepare(originSize);
		_data->sputn(buf.begin(), originSize);
		buf.reset();
	}

	return true;
}

void MsgData::reset()
{
	_data = std::shared_ptr<boost::asio::basic_streambuf<std::allocator<Char>>>(new boost::asio::basic_streambuf<std::allocator<Char>>());
}

}