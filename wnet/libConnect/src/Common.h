#ifndef Common_2016_3_29_06_H_
#define Common_2016_3_29_06_H_

#include "../include/types.h"

namespace WStone {

void _internal_logCallback(
	const char* file, 
	unsigned line, 
	const wchar_t* msg, ...);

void _internal_sysLog(
	const char* file, 
	unsigned line,
	const wchar_t* cErr, 
	unsigned long errID);

int getCPUNumbers();

#define safeDelete(p) \
{\
	if(nullptr != p) {\
		delete p;\
		p = nullptr;\
	}\
}

#define safeDeleteArray(p) \
{\
	if(nullptr != p) {\
	delete[] p;\
	p = nullptr;\
	}\
}

#define safeRelease(p)\
{\
	if(nullptr != p) {\
		CloseHandle(p);\
		p = nullptr;\
	}\
}

enum OperationType
{
	OPT_UNKNOWN = 0,
	OPT_ACCEPT = 1,
	OPT_READ = 1 << 1,
	OPT_WRITE = 1 << 2,
};

const static unsigned s_signature = 0x19881213;
const static unsigned s_bufferlength = 8 * 1024;

typedef struct _tagPERIODATA
{
	_tagPERIODATA();
	~_tagPERIODATA();

	void resetBuffer();

	OVERLAPPED overlapped;
	char8* buffer;
	WSABUF overlappedBuffer;
	OperationType opType;
	unsigned fd;
}IOContext, *PIOContext;

typedef struct _tagPERSOCKETDATA
{
	_tagPERSOCKETDATA();
	~_tagPERSOCKETDATA();

	PIOContext getNewIOContext();
	void removeIOContext(PIOContext pIOContext);

	unsigned fd;
	unsigned short clientPort;
	std::wstring clientIP;
	FastMutex _mtIOContexts;
	std::vector<PIOContext> ioContexts;
}SocketContext, *PSocketContext;


#pragma warning(disable : 4200)

#pragma pack(push, 1)
typedef struct _tagPacketHeader
{
	static char8* packet(
		unsigned msgid, 
		const char8* data, 
		unsigned& length);

	unsigned packetLength;
	unsigned signature;
	unsigned msgid;
	unsigned reserved;
	unsigned crc;
	char8 body[0];
}PacketHeader, *PPacketHeader;
#pragma pack(pop)

#define LOG(msg, ...) _internal_logCallback(__FILE__, __LINE__, L##msg, __VA_ARGS__)
#define SYSLOG(msg, errid) _internal_sysLog(__FILE__, __LINE__, L##msg, errid)

}


#endif //Common_2016_3_29_06_H_