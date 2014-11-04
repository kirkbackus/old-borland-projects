//------------------------------------------
// ULTIMATE SOCKET - Written by Kirk Backus
//------------------------------------------
// Makes use of the 39dll source by 39ster
// of the Game Maker Community
// gmc.yoyogames.com
//------------------------------------------
#ifndef ___SOCKET_J30_09_H
#define ___SOCKET_J30_09_H

#include <string>
#include "USock/39dll.h"

class BaseSocket {
    protected:

    int id;

    public:

    int ResetBuffer() { clearbuffer(0); }

    int WriteByte(byte buffer) { writebyte(buffer,0); }
    int WriteShort(short buffer) { writeshort(buffer,0); }
    int WriteUShort(unsigned short buffer) { writeushort(buffer,0); }
    int WriteInt(int buffer) { writeint(buffer,0); }
    int WriteUInt(unsigned int buffer) { writeuint(buffer,0); }
    int WriteFloat(float buffer) { writefloat(buffer,0); }
    int WriteDouble(double buffer) { writedouble(buffer,0); }
    int WriteString(char* buffer) { writestring(buffer,0); }
    int WriteStruct(char* buffer) { writechars(buffer,0); }

    byte ReadByte() { return((byte)readbyte(0)); }
    short ReadShort() { return((short)readshort(0)); }
    unsigned short ReadUShort() { return((unsigned short)readushort(0)); }
    int ReadInt() { return((int)readint(0)); }
    unsigned int ReadUInt() { return((unsigned int)readuint(0)); }
    float ReadFloat() { return((float)readfloat(0)); }
    double ReadDouble() { return(readdouble(0)); }
    char* ReadString() { return(readstring(0)); }
    void ReadStruct(char* buffer, int size) { buffer = readchars(size,0); return ((void)buffer);}

    char* GetIPAddress() { return (hostip("")); }
};

class ServerSocket : public BaseSocket {
    private:

    std::vector<int> connections;

    public:

    ServerSocket();
    ~ServerSocket();

    int Listen(int,int);

    int Accept();

    int Send();
    int Send(int socketid);
    int Receive(int);

    int GetNumConnections() { return connections.size(); }
};

class ClientSocket : public BaseSocket {
    private:

    int host;

    public:

    ClientSocket();
    ~ClientSocket();

    int Connect(char*, int);

    int Send();
    int Receive();
};

class HTTPSocket : public BaseSocket {
    public:

    bool DownloadFile(char*, char*);
    std::string GetIP();
};

//------------------------------------------------------------------------------
// Server Socket Declarations
//------------------------------------------------------------------------------
ServerSocket::ServerSocket() {
  id = -1;
}

ServerSocket::~ServerSocket() {
  for (int i=0;i<connections.size();i++) { closesock(connections[i]); }
  if (id>=0) closesock(id);
}

int ServerSocket::Listen(int port, int maxconnections) {
  id = (int)tcplisten(port, maxconnections, 1);
  return (1);
}

int ServerSocket::Accept() {
    int tmp = (int)tcpaccept(id, 1);
    if (tmp>0) connections.push_back(tmp);
    else {
        int error = WSAGetLastError();
        if (error!=10035) return error;
        else tmp = 0;
    }
    return tmp;
}

int ServerSocket::Send() {
  for (int i=0;i<connections.size();i++) {
    sendmessage(connections[i], 0, 0, 0);
  }
  return 1;
}

int ServerSocket::Send(int socketid) {
  for (int i=0;i<connections.size();i++) {
    sendmessage(socketid, 0, 0, 0);
  }
  return 1;
}

int ServerSocket::Receive(int connectionid) {
    int size;
    if (connectionid >= connections.size()) return -3;
    size = (int)receivemessage(connections[connectionid], 0, 0);
    if (size==0) connections.erase(connections.begin()+connectionid);
    return(size);
}

//------------------------------------------------------------------------------
// Client Socket Declarations
//------------------------------------------------------------------------------
ClientSocket::ClientSocket() {
  host = -1;
}

ClientSocket::~ClientSocket() {
  if (host!=-1) closesock(host);
}

int ClientSocket::Connect(char* ipaddress, int port) {
    host = (int)tcpconnect(ipaddress, port, 1);
    return (host);
}

int ClientSocket::Send() {
    if (host==-1) return -1;
    sendmessage(host, 0, 0, 0);
}

int ClientSocket::Receive() {
    if (host==-1) return -1;
    return((int)receivemessage(host, 0, 0));
}

//------------------------------------------------------------------------------
// HTTP Socket Declarations
//------------------------------------------------------------------------------
bool HTTPSocket::DownloadFile(char* webaddress, char* savetofile) {
    std::string server = "";
    std::string file = "/";

    std::string location = webaddress;
    std::string filename = savetofile;

    int port = 80;
    int i = 0;
    int error = 200;

    if (location.find("http://")==1) location.erase(location.begin(),location.begin()+7);

    i = location.find("/");
    if(i>0) {
        file = location.substr(i,location.size()-i+1);
        location.erase(i, file.length());
    }

    i = location.find(":");
    if(i>0) {
        port = atoi(location.substr(1,i-1).c_str());
        location.erase(location.begin()+1, location.begin()+i);
    }

    server = location;

    std::string c1310 = "";
    c1310 += char(13);
    c1310 += char(10);

    std::string tmp;

    int tcp = (int)tcpconnect((char*)server.c_str(), port, 0);
    if(!tcp)return false;

    setformat(tcp, 1, (char*)c1310.c_str());

    clearbuffer(0);
    tmp = "GET "+file+" HTTP/1.1" + c1310;
    writechars((char*)tmp.c_str(),0);
    tmp = "Host: " + server + c1310;
    writechars((char*)tmp.c_str(),0);
    tmp = "Connection: close" + c1310;
    writechars((char*)tmp.c_str(),0);
    tmp = "Accept: image/gif, image/x-xbitmap, image/jpeg, image/pjpeg, application/x-shockwave-flash, application/vnd.ms-excel, application/vnd.ms-powerpoint, application/msword, application/xaml+xml, application/vnd.ms-xpsdocument, application/x-ms-xbap, application/x-ms-application, application/x-alambik-script, application/x-alambik-alamgram-link, */*"+c1310;
    writechars((char*)tmp.c_str(),0);
    tmp = "Accept-Language: en-us"+c1310;
    writechars((char*)tmp.c_str(),0);
    tmp = "User-Agent: Mozilla/4.0 (compatible; MSIE 7.0; Windows NT 5.1; InfoPath.1; .NET CLR 2.0.50727; .NET CLR 1.1.4322)"+c1310;
    writechars((char*)tmp.c_str(),0);
    sendmessage(tcp, 0, 0, 0);

    bool endloop = false;
    std::string sw;
    char* t;
    while(!endloop) {
        receivemessage(tcp, 0, 0);
        t = readsep(" ",0);
        if (t!=NULL) sw = t;
        if (sw=="HTTP/1.1" || sw=="HTTP/1.0") {
            error = atoi(readsep(" ",0));
            if(error != 200 && error != 301) {
                closesocket(tcp);
                return 0;
            }
        }
        if (sw=="Location:") {
            if(error == 301) {
                closesocket(tcp);
                std::string url = readsep((char*)c1310.c_str(),0);
                return DownloadFile((char*)url.c_str(),savetofile);
            }
        }
        if (sw=="") {
            endloop = true;
        }
    }
    setformat(tcp, 2, 0); //turn off all formatting so we can receive file data.
    int tfile = (int)fileopen(savetofile, 1);

    while(receivemessage(tcp, 50000, 0) > 0) {
        filewrite(tfile, 0);
    }

    closesocket(tcp);
    fileclose(tfile);
    return 1;
}

std::string HTTPSocket::GetIP() {
    int tcp;
    std::string c1310 = "";
    c1310 += char(13);
    c1310 += char(10);
    tcp = (int)tcpconnect("whatismyip.org", 80, 0);
    if(!tcp)return "";
    setformat(tcp, 1, (char*)(c1310+c1310).c_str()); //set format to text mode to receive double blank lines (the whole header file)

    std::string tmp;
    clearbuffer(0);
    tmp = "GET / HTTP/1.1" + c1310;
    writechars((char*)tmp.c_str(),0);
    tmp = "Host: whatismyip.org" + c1310;
    writechars((char*)tmp.c_str(),0);
    tmp = "Connection: close" + c1310;
    writechars((char*)tmp.c_str(),0);
    tmp = "Accept: image/gif, image/x-xbitmap, image/jpeg, image/pjpeg, application/x-shockwave-flash, application/vnd.ms-excel, application/vnd.ms-powerpoint, application/msword, application/xaml+xml, application/vnd.ms-xpsdocument, application/x-ms-xbap, application/x-ms-application, application/x-alambik-script, application/x-alambik-alamgram-link, */*"+c1310;
    writechars((char*)tmp.c_str(),0);
    tmp = "Accept-Language: en-us"+c1310;
    writechars((char*)tmp.c_str(),0);
    tmp = "User-Agent: Mozilla/4.0 (compatible; MSIE 7.0; Windows NT 5.1; InfoPath.1; .NET CLR 2.0.50727; .NET CLR 1.1.4322)"+c1310;
    writechars((char*)tmp.c_str(),0);
    sendmessage(tcp,0,0,0);

    int a = (int)receivemessage(tcp,0,0);
    a = (int)receivemessage(tcp, 16,0);
    closesocket(tcp);
    return readchars(bytesleft(0),0);
}
#endif
