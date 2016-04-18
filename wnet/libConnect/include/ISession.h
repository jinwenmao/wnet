#ifndef ISession_2016_3_29_12_H_
#define ISession_2016_3_29_12_H_

namespace WStone {

typedef char char8; // 网络通讯使用UTF8编码

class __declspec(novtable) ISession
{
public:
	virtual ~ISession() { }

public:
	/************************************************************
	@brief : 获取会话套接字
	*************************************************************/
	virtual unsigned getHandle() = 0;
	/**********************************************************
	*@brief : 获取端点IP地址信息
	***********************************************************/
	virtual const wchar_t* getPeerIP() = 0;

	/**********************************************************
	*@brief : 获取端点端口信息
	***********************************************************/
	virtual unsigned short getPeerPort() = 0;

	/**********************************************************
	*@brief : 判断会话是否在线
	*@return : 成功返回true
	***********************************************************/
	virtual bool isAlive() = 0;
	
	/**********************************************************
	*@brief : 执行数据发送
	*@id : 消息ID
	*@msg : 发送数据
	*@lens : 发送数据长度
	*@return : 成功返回true，反之则反
	***********************************************************/
	virtual bool send(unsigned id, const char8* msg, unsigned lens) = 0;

	/**********************************************************
	*@brief : 执行获取数据, 该方法只适用于阻塞模式
	*@buffer : 接受缓冲区
	*@lens : 接受缓冲区大小
	*@return : 返回获取到的数据，（字节数）
	***********************************************************/
	virtual unsigned recv(char8* buffer, unsigned lens) = 0;
};

}

#endif //ISession_2016_3_29_12_H_