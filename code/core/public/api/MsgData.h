#ifndef GEMINI_MsgData_INCLUDE
#define GEMINI_MsgData_INCLUDE
#include "../Common.h"
#include "MsgDefine.h"

namespace boost {
	namespace asio {
		template <typename Allocator>
		class basic_streambuf;
	}
}

namespace gemini {

class CORE_API MsgData
{
	/**
	* @brief 消息头-128字节
	*/
	struct MsgHead {
		MSG_UINT8 	type;			///< 传输的消息类型
		MSG_UINT8   funcID;			///< 功能号
		MSG_UINT8 	dataEncode;		///< 数据类型(4bits)，及数据编码类型(4bits)
		MSG_UINT8 	cptEncryPri;	///< 数据压缩类型(2bits)，加密类型(2bits)及优先级(4bits)
		//UShort  seq;			///< 消息块序号
		MSG_UINT32 	size;			///< 实际传输的数据大小
		MSG_UINT32 	originSize;		///< 原始数据大小，即压缩前的数据大小
		MSG_UINT32 	id;				///< 客户端消息ID(12bits)，服务端会话ID(20bits)
		Char	path[120];		///< 处理路径
	};

public:
	typedef MSG_UINT8 T_TYPE;

	class mutable_buffer {
	public:
		/// Construct an empty buffer.
		mutable_buffer() : _data(0), _size(0) {}
		/// Construct a buffer to represent a given memory range.
		mutable_buffer(void* data, std::size_t size) : _data(data), _size(size) {}

		void* _data;
		std::size_t _size;
	};

	static const MSG_UINT32 s_maxBlock = 64*1024; 	///< 最大的消息传输块大小，超过该长度的消息，分块传输
	static const MSG_UINT32 s_msgHeadSize = sizeof(MsgHead);
private:
    MsgHead& getHead() { return _head; }
	const MsgHead& getHead() const { return _head; }
public:
	MsgData();
	~MsgData();

	/**
	 * 判断是否含有数据及消息头中的数据大小是否等于缓冲区中实际数据的大小
	 */
	Boolean valid() const;

	/**
	 * @brief 获取消息类型
	 * @see MsgType
	 */
	MSG_UINT8 getType() const { return getHead().type; }
	/**
	 * @brief 设置消息类型
	 * @see MsgType
	 */
	void setType(MSG_UINT8 type) { getHead().type = type; }

	/**
	 * @brief 获取功能号
	 */
	MSG_UINT8 getFunctionID() const { return getHead().funcID; }
	/**
	 * @brief 设置功能号
	 */
	void setFunctionID(MSG_UINT8 id) { getHead().funcID = id; }

	/**
	 * @brief 获取数据类型
	 * @see DataType
	 */
	DataType getDataType() const { return (DataType)(getHead().dataEncode >> 4); }
	/**
	 * @brief 设置数据类型
	 * @see DataType
	 */
	void setDataType(DataType dt)
	{ getHead().dataEncode = (getHead().dataEncode & 15) | ((MSG_UINT8)dt << 4); }

	/**
	 * @brief 获取数据编码类型
	 * @see EncodingType
	 */
	EncodingType getEncoding() const { return (EncodingType)(getHead().dataEncode & 15); }
	/**
	 * @brief 设置数据编码类型
	 * @see EncodingType
	 */
	void setEncoding(EncodingType enType)
	{ getHead().dataEncode = ((getHead().dataEncode >> 4) << 4) | (MSG_UINT8)enType; }
	
	/**
	 * @brief 获取数据压缩类型
	 * @see CompressType
	 */
	CompressType getCompressType() const { return (CompressType)(getHead().cptEncryPri >> 6); }
	/**
	 * @brief 设置数据压缩类型
	 * @see CompressType
	 */
	void setCompressType(CompressType cpt)
	{ getHead().cptEncryPri = (getHead().cptEncryPri & 63) | ((MSG_UINT8)cpt << 6); }

	/**
	 * @brief 获取数据加密类型
	 * @see Encryption
	 */
	Encryption getEncryption() const
	{ return (Encryption)((getHead().cptEncryPri >> 4) & 3); }
	/**
	 * @brief 设置数据加密类型
	 * @see Encryption
	 */
	void setEncryption(Encryption encry)
	{ getHead().cptEncryPri = ((getHead().cptEncryPri >> 6) << 6) | (((MSG_UINT8)encry << 4) | getPriority()); }

	/**
	 * @brief 获取消息优先级
	 */
	MSG_UINT8 getPriority() const { return MSG_UINT8(getHead().cptEncryPri & 15); }
	/**
	 * @brief 设置消息优先级
	 * @param [in] priority 值越大，优先级越高
	 */
	void setPriority(MSG_UINT8 priority)
	{ getHead().cptEncryPri = ((getHead().cptEncryPri >> 4) << 4) | priority; }

	/**
	 * @brief 获取序号
	 */
	//UShort getSeq() const { return getHead().seq; }
	/**
	 * @brief 设置序号
	 */
	//void setSeq(UShort seq) { getHead().seq = seq; }
	
	/**
	 * @brief 获取ID
	 */
	MSG_UINT32 getID() const { return getHead().id; }
	/**
	 * @brief 获取传输的消息ID
	 */
	MSG_UINT32 getMsgID() const { return getHead().id >> 20; }
	/**
	 * @brief 设置传输的消息ID
	 * @param id 消息ID
	 * @note 消息ID应小于4096
	 */
	void setMsgID(MSG_UINT32 id)
	{ getHead().id = ((getHead().id << 12) >> 12) | ((MSG_UINT32)id << 20); }

	/**
	 * @brief 获取会话ID
	 */
	MSG_UINT32 getSessionID() const { return (getHead().id << 12) >> 12; }
	/**
	 * @brief 设置会话ID
	 */
	void setSessionID(MSG_UINT32 id)
	{ getHead().id = ((getHead().id >> 20) << 20) | id; }

	String getPath() const { return getHead().path; }
	void setPath(const Char* path) { }

	/**
	 * @brief 获取头部首地址
	 */
	Char* getHeadBuffer() { return (Char*)&_head; }
	/**
	 * @brief 获取头部大小，字节为单位
	 */
	MSG_UINT32 getHeadSize() const { return s_msgHeadSize; }
	/**
	 * @brief 获取数据区首地址
	 */
	const Char* getDataBuffer();

	/**
	 * @brief 获取实际缓冲区的或则传输的数据大小
	 */
	MSG_UINT32 getDataSize() const { return (getHead().size); }
	/**
	 * @brief 获取压缩之前的数据大小
	 */
	MSG_UINT32 getOriginSize() const { return getHead().originSize; }

	/**
	 * @brief 获得AES CBC模式加密的长度
	 */
	MSG_UINT32 getAESCBCSize() const;

	/**
	 * @brief 将消息头进行网络字节顺序到主机字节顺序的转换
	 */
	void networkToHost();
	/**
	 * @brief 将消息头进行主机字节顺序到网络字节顺序的转换
	 */
	void hostToNetwork();

	/**
	 * @brief 根据头信息准备好数据缓冲区
	 * @return 返回包含一个接收数据的首地址，及需接收的大小（字节）
	 */
	mutable_buffer prepare();
	/**
	 * @brief 准备指定大小的接收数据缓冲区
	 * @param [in] size 缓冲区大小（字节）
	 * @return 返回包含一个接收数据的首地址，及需接收的大小（字节）
	 */
	mutable_buffer prepare(std::size_t size);
	/**
	 * @brief 确认指定大小的数据已写入缓冲区
	 * @param [in] size 确认的数据大小，字节为单位
	 * 
	 * @return      返回缓冲区是否已满
	 * @retval false 缓冲区未满，还有数据没有接受确认
	 * @retval true  缓冲区已满，数据已接受确认完毕
	 */
	Boolean commit(std::size_t size);

	/**
	* @brief 遍历缓冲区里的数据
	* @param [in] pos  [开始查找的位置]
	* @param [out] data [返回数据的起始地址]
	* @param [out] size [返回数据的大小]
	* 
	* @return      是否取到数据
	* @retval false	没有取到数据
	* @retval true	取到数据
	*/
	Boolean step(MSG_UINT32 pos, const Char*& data, MSG_UINT32& size);

	/**
	 * @brief 处理流程 1.编码 2.压缩 3.加密
	 * @return 是否处理成功
	 * @retval false 处理失败
	 * @retval true  处理成功
	 */
	Boolean format();
	/** 
	 * @brief 处理流程 1.编码 2.压缩 3.加密
	 * @param [in] pData 数据内存首地址
	 * @param [in] size  数据大小（字节为单位）
	 * 
	 * @return 是否处理成功
	 * @retval false 处理失败
	 * @retval true  处理成功
	 */
	Boolean format(const void* pData, std::size_t size);
	/** 
	 * @brief 处理流程 1.解密 2.解压 3.反编码
	 *
	 * @return 是否处理成功
	 * @retval false 处理失败
	 * @retval true  处理成功
	 */
	Boolean parse();

	void reset();
private:
	friend class OutMsgData;
	friend class InMsgData;
	MsgHead _head;	///< 消息头
	std::shared_ptr<boost::asio::basic_streambuf<std::allocator<Char>>> _data;	 ///< 数据
};

}
#endif // GEMINI_MsgData_INCLUDE