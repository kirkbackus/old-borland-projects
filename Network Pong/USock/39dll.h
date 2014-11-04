#define min(a,b) a < b ? a : b
#define max(a,b) a > b ? a : b

#include "includes.h"
#include "tools.cpp"
#include "socket.cpp"
#include "buffer.cpp"
#include "list.cpp"

CList buffers;
CList sockets;
CList files;

int AddSocket(CSocket*);
int AddBuffer(CBuffer*);
int AddFile(HANDLE);

double tcpconnect(char*ip, double port, double mode)
{
    CSocket* sock = new CSocket();
	if(sock->tcpconnect(ip, (int)port, (int)mode))
		return AddSocket(sock);
	delete sock;
	return -1;
}

double tcplisten(double port, double max, double mode)
{
	CSocket* sock = new CSocket();
	if(sock->tcplisten((int)port, (int) max,(int)mode))
		return AddSocket(sock);
	delete sock;
	return -1;
}

double tcpaccept(double sockid, double mode)
{
	CSocket*sock = (CSocket*)sockets.item((int)sockid);
	if(sock == NULL)return -1;
	CSocket*sock2 = sock->tcpaccept((int)mode);
	if(sock2 != NULL)return AddSocket(sock2);
	return -1;
}

char* tcpip(double sockid)
{
	CSocket*sock = (CSocket*)sockets.item((int)sockid);
	if(sock == NULL)return NULL;
	return sock->tcpip();
}

double setnagle(double sockid, double value)
{
	CSocket*sock = (CSocket*)sockets.item((int)sockid);
	if(sock == NULL)return 0;
	if(value)
		sock->setnagle(true);
	else sock->setnagle(false);
	return 1;
}
double tcpconnected(double sockid)
{
	CSocket*sock = (CSocket*)sockets.item((int)sockid);
	if(sock == NULL)return 0;
	if(sock->tcpconnected())return 1;
	else return 0;
}
double udpconnect(double port, double mode)
{
	CSocket* sock = new CSocket();
	if(sock->udpconnect((int)port, (int)mode))
		return AddSocket(sock);
	delete sock;
	return -1;
}
double sendmessage(double sockid, char*ip, double port, double buffid)
{
	CSocket*sock = (CSocket*)sockets.item((int)sockid);
	CBuffer*buff = (CBuffer*)buffers.item((int)buffid);
	if(sock == NULL)return -1;
	if(buff == NULL)return -2;
	int size = sock->sendmessage(ip, (int)port, buff);
	if(size < 0)return -sock->lasterror();
	return size;
}

double receivemessage(double sockid, double len, double buffid)
{
	CSocket*sock = (CSocket*)sockets.item((int)sockid);
	CBuffer*buff = (CBuffer*)buffers.item((int)buffid);
	if(sock == NULL)return -1;
	if(buff == NULL)return -2;
	int size = sock->receivemessage((int)len, buff);
	if(size < 0)
	{
		int error = sock->lasterror();
		if(error == 10054)return 0;
		return -error;
	}
	return size;
}
double peekmessage(double sockid, double len, double buffid)
{
	CSocket*sock = (CSocket*)sockets.item((int)sockid);
	CBuffer*buff = (CBuffer*)buffers.item((int)buffid);
	if(sock == NULL)return -1;
	if(buff == NULL)return -2;
	int size = sock->peekmessage((int)len, buff);
	if(size < 0)
	{
		int error = sock->lasterror();
		if(error == 10054)return 0;
		return -error;
	}
	return size;
}

double setformat(double sockid, double mode, char*sep)
{
	CSocket*sock = (CSocket*)sockets.item((int)sockid);
	if(sock == NULL)return -1;
	return sock->SetFormat((int)mode, sep);
}

char* lastinIP()
{
	return CSocket::lastinIP();
}

double lastinPort()
{
	return CSocket::lastinPort();
}

double setsync(double sockid, double mode)
{
	CSocket*sock = (CSocket*)sockets.item((int)sockid);
	if(sock == NULL)return -1;
	sock->setsync((int)mode);
	return 1;
}
double closesock(double sockid)
{
	CSocket*sock = (CSocket*)sockets.item((int)sockid);
	if(sock == NULL)return -1;
	delete sock;
	sockets.set((int)sockid, NULL);
	return 1;
}

double socklasterror(double sockid)
{
	CSocket*sock = (CSocket*)sockets.item((int)sockid);
	if(sock == NULL)return -1;
	return -sock->lasterror();
}

char* myhost()
{
	return CSocket::myhost();
}

double compareip(char*ip, char*mask)
{
	return CTools::comparematch(ip, mask);
}

double sockexit()
{
	CSocket::SockExit();
	return 1;
}

double sockstart()
{
	CSocket::SockStart();
	return 1;
}

char* hostip(char*host)
{
	return CSocket::GetIp(host);
}


double getsocketid(double sockid)
{
	CSocket*sock = (CSocket*)sockets.item((int)sockid);
	if(sock == NULL)return -1;
	return sock->sockid;
}
//Buffers
double writebyte(double val, double buffid)
{
	CBuffer*buff = (CBuffer*)buffers.item((int)buffid);
	if(buff == NULL)return 0;
	return buff->writebyte((unsigned char)val);
}
double writeshort(double val, double buffid)
{
	CBuffer*buff = (CBuffer*)buffers.item((int)buffid);
	if(buff == NULL)return 0;
	return buff->writeshort((short)val);
}
double writeushort(double val, double buffid)
{
	CBuffer*buff = (CBuffer*)buffers.item((int)buffid);
	if(buff == NULL)return 0;
	return buff->writeushort((unsigned short)val);
}
double writeint(double val, double buffid)
{
	CBuffer*buff = (CBuffer*)buffers.item((int)buffid);
	if(buff == NULL)return 0;
	return buff->writeint((int)val);
}
double writeuint(double val, double buffid)
{
	CBuffer*buff = (CBuffer*)buffers.item((int)buffid);
	if(buff == NULL)return 0;
	return buff->writeuint((unsigned int)val);
}
double writefloat(double val, double buffid)
{
	CBuffer*buff = (CBuffer*)buffers.item((int)buffid);
	if(buff == NULL)return 0;
	return buff->writefloat((float)val);
}
double writedouble(double val, double buffid)
{
	CBuffer*buff = (CBuffer*)buffers.item((int)buffid);
	if(buff == NULL)return 0;
	return buff->writedouble(val);
}
double writechars(char*str, double buffid)
{
	CBuffer*buff = (CBuffer*)buffers.item((int)buffid);
	if(buff == NULL)return 0;
	return buff->writechars(str);
}
double writestring(char*str, double buffid)
{
	CBuffer*buff = (CBuffer*)buffers.item((int)buffid);
	if(buff == NULL)return 0;
	return buff->writestring(str);
}

double readbyte(double buffid)
{
	CBuffer*buff = (CBuffer*)buffers.item((int)buffid);
	if(buff == NULL)return 0;
	return buff->readbyte();
}

double readshort(double buffid)
{
	CBuffer*buff = (CBuffer*)buffers.item((int)buffid);
	if(buff == NULL)return 0;
	return buff->readshort();
}

double readushort(double buffid)
{
	CBuffer*buff = (CBuffer*)buffers.item((int)buffid);
	if(buff == NULL)return 0;
	return buff->readushort();
}

double readint(double buffid)
{
	CBuffer*buff = (CBuffer*)buffers.item((int)buffid);
	if(buff == NULL)return 0;
	return buff->readint();
}

double readuint(double buffid)
{
	CBuffer*buff = (CBuffer*)buffers.item((int)buffid);
	if(buff == NULL)return 0;
	return buff->readuint();
}
double readfloat(double buffid)
{
	CBuffer*buff = (CBuffer*)buffers.item((int)buffid);
	if(buff == NULL)return 0;
	return buff->readfloat();
}
double readdouble(double buffid)
{
	CBuffer*buff = (CBuffer*)buffers.item((int)buffid);
	if(buff == NULL)return 0;
	return buff->readdouble();
}
char* readchars(double len, double buffid)
{
	CBuffer*buff = (CBuffer*)buffers.item((int)buffid);
	if(buff == NULL)return NULL;
	return buff->readchars((int)len);
}

char* readstring(double buffid)
{
	CBuffer*buff = (CBuffer*)buffers.item((int)buffid);
	if(buff == NULL)return NULL;
	return buff->readstring();
}

char* readsep(char*sep, double buffid)
{
	CBuffer*buff = (CBuffer*)buffers.item((int)buffid);
	if(buff == NULL)return NULL;
	return buff->readsep(sep);
}
double getpos(double pos, double buffid)
{
	CBuffer*buff = (CBuffer*)buffers.item((int)buffid);
	if(buff == NULL)return 0;
	if(pos == 0)return buff->writepos;
	else return buff->readpos;
}

double clearbuffer(double buffid)
{
	CBuffer*buff = (CBuffer*)buffers.item((int)buffid);
	if(buff == NULL)return 0;
	buff->clear();
	return 1;
}

double buffsize(double buffid)
{
	CBuffer*buff = (CBuffer*)buffers.item((int)buffid);
	if(buff == NULL)return 0;
	return buff->count;
}

double setpos(double pos, double buffid)
{
	CBuffer*buff = (CBuffer*)buffers.item((int)buffid);
	if(buff == NULL)return 0;
	buff->readpos = (int)pos;
	buff->writepos = (int)pos;
	return pos;
}

double bytesleft(double buffid)
{
	CBuffer*buff = (CBuffer*)buffers.item((int)buffid);
	if(buff == NULL)return 0;
	return buff->bytesleft();
}

double createbuffer()
{
	CBuffer* buff = new CBuffer();
	return AddBuffer(buff);
}
double freebuffer(double buffid)
{
	if(buffid == 0)return 0; //no deleting default buffer
	CBuffer*buff = (CBuffer*)buffers.item((int)buffid);
	if(buff == NULL)return 0;
	delete buff;
	buffers.set((int)buffid, NULL);
	return 1;
}
double copybuffer(double destinationid, double sourceid)
{
	CBuffer*destination = (CBuffer*)buffers.item((int)destinationid);
	if(destination == NULL)return 0;
	CBuffer*source = (CBuffer*)buffers.item((int)sourceid);
	if(source == NULL)return 0;
	destination->addBuffer(source);
	return 1;

}
double copybuffer2(double destinationid, double start, double len, double sourceid)
{
	CBuffer*destination = (CBuffer*)buffers.item((int)destinationid);
	if(destination == NULL)return 0;
	CBuffer*source = (CBuffer*)buffers.item((int)sourceid);
	if(source == NULL)return 0;
	destination->addBuffer(source->data+(int)start, (int)len);
	return 1;

}
//tools
char* getmacaddress()
{
	return CTools::getmacaddress();
}
char* md5string(char*str)
{
	return CTools::md5string(str);
}

char* md5buffer(double buffid)
{
	CBuffer*buff = (CBuffer*)buffers.item((int)buffid);
	if(buff == NULL)return NULL;
	return CTools::md5buffer(buff);
}

double bufferencrypt(char*pass, double buffid)
{
	CBuffer*buff = (CBuffer*)buffers.item((int)buffid);
	if(buff == NULL)return 0;
	CTools::encryptedbuffer(buff, pass);
	return 1;
}

double adler32(double buffid)
{
	CBuffer*buff = (CBuffer*)buffers.item((int)buffid);
	if(buff == NULL)return 0;
	return CTools::adler32(buff);
}

double bufferexists(double buffid)
{
	CBuffer*buff = (CBuffer*)buffers.item((int)buffid);
	if(buff == NULL)return 0;
	return 1;
}

double netconnected()
{
	return CTools::netconnected();
}

double fileopen(char*name, double mode)
{
	HANDLE file = CTools::BinOpen(name, (int)mode);
	if(file != NULL)
		return AddFile(file);
	return -1;
}

double fileclose(double fileid)
{
	HANDLE file = (HANDLE)files.item((int)fileid);
	if(file == NULL)return -1;
	files.set((int)fileid, NULL);
	return CTools::BinClose(file);
}

double filewrite(double fileid, double buffid)
{
	HANDLE file = (HANDLE)files.item((int)fileid);
	if(file == NULL)return -1;
	CBuffer*buff = (CBuffer*)buffers.item((int)buffid);
	if(buff == NULL)return -1;
	return CTools::BinWrite(file, buff);
}

double fileread(double fileid, double bytes, double buffid)
{
	HANDLE file = (HANDLE)files.item((int)fileid);
	if(file == NULL)return -1;
	CBuffer*buff = (CBuffer*)buffers.item((int)buffid);
	if(buff == NULL)return -1;
	return CTools::BinRead(file, (int)bytes, buff);
}
double filepos(double fileid)
{
	HANDLE file = (HANDLE)files.item((int)fileid);
	if(file == NULL)return -1;
	return CTools::BinGetPos(file);
}
double filesetpos(double fileid, double pos)
{
	HANDLE file = (HANDLE)files.item((int)fileid);
	if(file == NULL)return -1;
	return CTools::BinSetPos(file, (int)pos);
}
double filesize(double fileid)
{
	HANDLE file = (HANDLE)files.item((int)fileid);
	if(file == NULL)return -1;
	return CTools::BinFileSize(file);
}

double iptouint(char*ip)
{
	return CTools::ip2uint(ip);
}
char* uinttoip(double ip)
{
	return CTools::uint2ip((unsigned int)ip);
}
int AddBuffer(CBuffer*b)
{
	for(int i = 0; i < buffers.count; i ++)
	{
		if(buffers[i] == NULL)
		{
			buffers.set(i, b);
			return i;
		}
	}
	buffers.Add(b);
	return buffers.count-1;
}

int AddSocket(CSocket*b)
{
	for(int i = 0; i < sockets.count; i ++)
	{
		if(sockets[i] == NULL)
		{
			sockets.set(i, b);
			return i;
		}
	}
	sockets.Add(b);
	return sockets.count-1;
}

int AddFile(HANDLE b)
{
	for(int i = 0; i < files.count; i ++)
	{
		if(files[i] == NULL)
		{
			files.set(i, b);
			return i;
		}
	}
	files.Add(b);
	return files.count-1;
}

double Init39()
{
    CSocket::SockStart();
    buffers.Add(new CBuffer());
    sockets.Add(new CSocket()); //dummy socket
    return 1;
}

double Close39() {
    CSocket::SockExit();
    for(int i = 0; i < buffers.count; i++)if(buffers[i] != NULL)delete (CBuffer*)buffers.item(i);
    for(int i = 0; i < sockets.count; i++)if(sockets[i] != NULL)delete (CSocket*)sockets.item(i);
    for(int i = 0; i < files.count; i ++)if(files[i] != NULL)CTools::BinClose((HANDLE)files.item(i));
}
