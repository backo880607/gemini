#ifndef GEMINI_MsgDefine_INCLUDE
#define GEMINI_MsgDefine_INCLUDE

namespace gemini {

/**
* @brief 消息类型
* 可以对消息类型设置不同的优先级，但消息类型的标识值不代表优先级。
* @note 0~32为预留的消息类型标识，自定义的请从0x20开始。
*/
#define MSG_TYPE_TERMINALTION		0x00
#define MSG_TYPE_LOGOUT				0x01
#define MSG_TYPE_LOGIN				0x02
#define MSG_TYPE_HEARTBEAT			0x03
#define MSG_TYPE_SVRERROR			0x04
#define MSG_TYPE_REQERROR			0x05
#define MSG_TYPE_NORMAL				0X06
#define MSG_TYPE_SUCCESS			0x07

/**
* @brief 数据类型
* @note 最大枚举值不应超过15。
*/
enum class DataType {
	DT_None = 0,
	DT_MEMSEQ,				///< 内存字节序
	DT_JSON,				///< Json格式
	DT_XML,					///< XML格式
};

/**
* @brief 数据编码
* @note 最大枚举值不应超过15。
*/
enum class EncodingType {
	Encoding_None = 0,
	Encoding_UTF8,			///< Utf8编码
	Encoding_UTF16,			///< Utf16编码
	Encoding_UTF32,			///< Utf32编码
};

/**
* @brief 数据压缩
* @note 最大枚举值不应超过3。
*/
enum class CompressType {
	CPT_NONE = 0,			///< 不进行数据压缩
	CPT_ZLIB,				///< zlib压缩
	CPT_GZIP,				///< gzip压缩
	CPT_DEFLATE				///< deflate压缩
};

/**
* @brief 加密类型
* @note 最大枚举值不应超过3。
*/
enum class Encryption {
	Encry_None = 0,
	Encry_AES,
};

#define STRUCT_VAR_SIZE(tag, property) sizeof(((tag*)0)->property)
#define STRUCT_VAR_SIZE_NS(ns, tag, property) sizeof(((ns::tag*)0)->property)

}
#endif // !GEMINI_MsgDefine_INCLUDE
