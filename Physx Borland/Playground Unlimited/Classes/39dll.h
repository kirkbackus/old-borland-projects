//Load the dll
HMODULE n39 = LoadLibrary("GameData/39.dll");

/**************************
 * Function Pointer Declarations
 *
 **************************/
typedef char* (__cdecl * sfunc)();
typedef char* (__cdecl * sfunc1d)(double);
typedef char* (__cdecl * sfunc1s)(double);
typedef char* (__cdecl * sfuncds)(double, const char*);
typedef char* (__cdecl * sfunc1)(const char*);

typedef double (__cdecl * dfuncsd)(const char*, double);
typedef double (__cdecl * dfuncds)(double, const char*);
typedef double (__cdecl * dfunc2s) (const char*, const char*);
typedef double (__cdecl * dfuncs2d)(const char*, double, double);
typedef double (__cdecl * dfuncdsd)(double, const char*, double);


dfunc1 WriteByte = (dfunc1)GetProcAddress(n39,"WriteByte");
dfuncsd WriteString = (dfuncsd)GetProcAddress(n39,"WriteString");
dfunc1 WriteShort = (dfunc1)GetProcAddress(n39,"WriteShort");
dfunc1 WriteInt = (dfunc1)GetProcAddress(n39,"WriteInt");
dfunc1 WriteFloat = (dfunc1)GetProcAddress(n39,"WriteFloat");
dfunc1 WriteDouble = (dfunc1)GetProcAddress(n39,"WriteDouble");
dfunc ReadByte = (dfunc)GetProcAddress(n39,"ReadByte");
sfuncds ReadString = (sfuncds)GetProcAddress(n39,"ReadString");
dfunc ReadShort = (dfunc)GetProcAddress(n39,"ReadShort");
dfunc ReadDouble = (dfunc)GetProcAddress(n39,"ReadDouble");
dfunc ClearBuffer = (dfunc)GetProcAddress(n39,"ClearBuffer");
dfunc1 SetPos = (dfunc1)GetProcAddress(n39,"SetPos");
dfunc1 GetPos = (dfunc1)GetProcAddress(n39,"GetPos");
dfunc BufferSize = (dfunc)GetProcAddress(n39,"BufferSize");

dfunc CreateBuffer = (dfunc)GetProcAddress(n39,"CreateBuffer");
dfunc1 SetBuffer = (dfunc1)GetProcAddress(n39,"SetBuffer");
dfunc ResetBuffer = (dfunc)GetProcAddress(n39,"ResetBuffer");
dfunc1 DestroyBuffer = (dfunc1)GetProcAddress(n39,"DestroyBuffer");
dfunc1 WriteuShort = (dfunc1)GetProcAddress(n39,"WriteuShort");
dfunc1 WriteuInt = (dfunc1)GetProcAddress(n39,"WriteuInt");
dfunc ReaduShort = (dfunc)GetProcAddress(n39,"ReaduShort");
dfunc ReaduInt = (dfunc)GetProcAddress(n39,"ReaduInt");

dfuncs2d TcpConnect = (dfuncs2d)GetProcAddress(n39,"TcpConnect");
dfunc3 TcpListen = (dfunc3)GetProcAddress(n39,"TcpListen");
dfunc2 TcpAccept = (dfunc2)GetProcAddress(n39,"TcpAccept");
dfuncdsd MessageSend = (dfuncdsd)GetProcAddress(n39,"MessageSend");
dfunc2 MessageRecieve = (dfunc2)GetProcAddress(n39,"MessageRecieve");
dfunc2 SetSync = (dfunc2)GetProcAddress(n39,"setSync");
dfuncds SetFormat = (dfuncds)GetProcAddress(n39,"SetFormat");
dfunc2 UdpConnect = (dfunc2)GetProcAddress(n39,"UdpConnect");
sfunc1 GetIp = (sfunc1)GetProcAddress(n39,"GetIp");
sfunc LastUdpIp = (sfunc)GetProcAddress(n39,"LastUdpIp");
dfunc1 SockClose = (dfunc1)GetProcAddress(n39,"SockClose");
dfunc1 TcpAddress = (dfunc1)GetProcAddress(n39,"TcpAddress");
dfunc LastError = (dfunc)GetProcAddress(n39,"LastError");
sfunc MyHost = (sfunc)GetProcAddress(n39,"MyHost");
dfunc2s IpCompare = (dfunc2s)GetProcAddress(n39,"IpCompare");
dfunc SockExit = (dfunc)GetProcAddress(n39,"SockExit");
dfunc SockStart = (dfunc)GetProcAddress(n39,"SockStart");
sfunc GetMACAddress = (sfunc)GetProcAddress(n39,"GetMACAddress");
dfunc2 MessagePeek = (dfunc2)GetProcAddress(n39,"MessagePeek");
dfunc2 SetNagleAlgorithm = (dfunc2)GetProcAddress(n39,"SetNagleAlgorithm");
dfunc1 IsSockConnected = (dfunc1)GetProcAddress(n39,"IsSockConnected");
dfunc5 SetRawOption = (dfunc5)GetProcAddress(n39,"SetRawOption");
dfunc4 GetRawOption = (dfunc4)GetProcAddress(n39,"GetRawOption");

class MySock {
  private:

  //Game Id, used for sending packets, value can be between 0 and 65536
  int es_id;

  //Ports
  int port_tcp;
  int port_udp_s;
  int port_udp_c;

  //Other variables
  double last_time;
  double hdl_tcp_server;
  double hdl_udp_server;
  double hdl_tcp_client;
  double hdl_udp_client;
  double hdl_player_c;
  double new_cl;
  char* ip_server;
  char* ip_client;
  char* es_status;
  bool es_init;

  int current_time;

  public:

  MySock() {
    //Unique Id for game
    es_id=314;

    //Ports to use
    port_tcp = 1200;
    port_udp_s = 1201;
    port_udp_c = 1202;

    last_time = 0;
    hdl_tcp_server = -1;
    hdl_udp_server = -1;
    hdl_tcp_client = -1;
    hdl_udp_client = -1;
    hdl_player_c = -1;
    new_cl = -1;
    ip_server = "";
    ip_client = "";
    es_status = "";
    es_init = true;

    current_time=GetTickCount();
  }

  ~MySock() {
    Stop();
    es_init=false;
  }

  bool Stop();
  bool Create();
  int Check();
  bool Join(char* sname);

  //Start
  void PacketStart();

  //Writing Routines
  bool PacketWrite(const char* val);
  bool PacketWrite(char val);
  bool PacketWrite(unsigned short val);
  bool PacketWrite(unsigned int val);
  bool PacketWrite(short val);
  bool PacketWrite(int val);
  bool PacketWrite(float val);
  bool PacketWrite(double val);

  //Read/Write
  void PacketSend(double val);

  char* PacketReadStr();
  char PacketReadB();
  unsigned short PacketReadUs();
  unsigned int PacketReadUi();
  short PacketReadS();
  int PacketReadI();
  double PacketReadF();
};

bool MySock::Create() {
  if(es_status != "") return false;
  hdl_udp_server = UdpConnect(port_udp_s,1);
  if(!hdl_udp_server) return false;
  hdl_tcp_server = TcpListen(port_tcp,4,1);
  if(!hdl_tcp_server) {
      SockClose(hdl_udp_server);
      return false;
  } else {
      es_status = "host-0";
      return true;
  }
}

bool MySock::Stop() {
  if(es_status == "host-0") {
    SockClose(hdl_tcp_server);
    SockClose(hdl_udp_server);
    es_status = "";
    return true;
  } else if(es_status == "host-1") {
    ClearBuffer();
    WriteuShort(es_id);
    WriteByte(0);
    MessageSend(hdl_player_c,"",0);
    SockClose(hdl_player_c);
    SockClose(hdl_tcp_server);
    SockClose(hdl_udp_server);
    es_status = "";
    return true;
  } else if(es_status == "client-0") {
    SockClose(hdl_tcp_client);
    SockClose(hdl_udp_client);
    es_status = "";
    return true;
  } else if(es_status == "client-1") {
    ClearBuffer();
    WriteuShort(es_id);
    WriteByte(0);
    MessageSend(hdl_tcp_client,"",0);
    SockClose(hdl_tcp_client);
    SockClose(hdl_udp_client);
    es_status = "";
    return true;
  }
  return false;
}

int MySock::Check() {
  current_time=GetTickCount();
  if(es_status == "host-0") {
      double new_cl, size, i;
      if(hdl_player_c == -1) {
          new_cl = TcpAccept(hdl_tcp_server,1);
          if(new_cl) {
              last_time = current_time;
              ip_client = LastUdpIp();
              hdl_player_c = new_cl;
              ClearBuffer();
              WriteuShort(es_id);
              WriteByte(1);
              MessageSend(new_cl,"",0);
          }
      } else {
          if((current_time - last_time) > 30000) {
              ClearBuffer();
              WriteuShort(es_id);
              WriteByte(0);
              MessageSend(hdl_player_c,"",0);
              SockClose(hdl_player_c);
              hdl_player_c = -1;
          } else {
              size = MessageRecieve(hdl_player_c,0);
              if(size > 0) {
                  if(ReaduShort() == es_id) {
                      i = ReadByte();
                      if(i == 2) {
                          es_status = "host-1";
                          return 1;
                      }
                  }
              }
          }
      }
      return 0;
  } else if(es_status == "client-0") {
      if((current_time - last_time) > 30000) {
          ClearBuffer();
          WriteuShort(es_id);
          WriteByte(0);
          MessageSend(hdl_tcp_client,"",0);
          SockClose(hdl_tcp_client);
          SockClose(hdl_udp_client);
          es_status = "";
          return 2;
      } else {
          double size, i;
          size = MessageRecieve(hdl_tcp_client,0);
          if(size > 0) {
              if(ReaduShort() == es_id) {
                  i = ReadByte();
                  if(i == 1) {
                      ClearBuffer();
                      WriteuShort(es_id);
                      WriteByte(2);
                      MessageSend(hdl_tcp_client,"",0);
                      es_status = "client-1";
                      return 1;
                  } else if(i == 2 || i == 0) {
                      closesocket(hdl_tcp_client);
                      closesocket(hdl_udp_client);
                      es_status = "";
                      return 2;
                  }
              }
          }
      }
  } else if(es_status == "host-1") {
      double size, i;
      new_cl = TcpAccept(hdl_tcp_server,1);
      if(new_cl) {
              ClearBuffer();
              WriteuShort(es_id);
              WriteByte(2);
              MessageSend(new_cl,"",0);
              SockClose(new_cl);
      }
      while(true) {
          size = MessageRecieve(hdl_player_c,0);
          if(size < 0) size = MessageRecieve(hdl_udp_server,0);
          if(size < 0) exit;
          if(ReaduShort() == es_id) {
              i = ReadByte();
              if(i == 10) return 1;
              else if(i == 0) {
                  SockClose(hdl_player_c);
                  SockClose(hdl_tcp_server);
                  SockClose(hdl_udp_server);
                  es_status = "";
                  return 0;
              }
          }
      }
      return -1;
  } else if(es_status == "client-1") {
      while(true) {
          double size, i;
          size = MessageRecieve(hdl_tcp_client,0);
          if(size < 0) size = MessageRecieve(hdl_udp_client,0);
          if(size < 0) return 0;
          if(ReaduShort() == es_id) {
              i = ReadByte();
              if(i == 10) return 1;
              else if(i == 0) {
                  closesocket(hdl_tcp_client);
                  closesocket(hdl_udp_client);
                  es_status = "";
                  es_status = "";
                  return 0;
              }
          }
      }
      return -1;
  }
  return(-1);
}

bool MySock::Join(char* sname) {
  if(es_status != "") return false;
  hdl_udp_client = UdpConnect(port_udp_c,1);
  if(!hdl_udp_client) return false;
  hdl_tcp_client = TcpConnect(sname,port_tcp,1);
  if(!hdl_tcp_client) {
    SockClose(hdl_udp_client);
    return false;
  } else {
    es_status = "client-0";
    ip_server = sname;
    last_time = current_time;
    return true;
  }
}

void MySock::PacketStart() {
  ClearBuffer();
  WriteuShort(es_id);
  WriteByte(10);
}

//Writing Routines
bool MySock::PacketWrite(const char* val) {
  WriteByte(20); WriteString(val,true);
  return(1);
}

bool MySock::PacketWrite(char val) {
  WriteByte(0); WriteByte(val);
  return(1);
}

bool MySock::PacketWrite(unsigned short val) {
  WriteByte(1); WriteuShort(val);
  return(1);
}

bool MySock::PacketWrite(unsigned int val) {
  WriteByte(2); WriteuInt(val);
  return(1);
}

bool MySock::PacketWrite(short val) {
  WriteByte(3); WriteShort(val);
  return(1);
}

bool MySock::PacketWrite(int val) {
  WriteByte(4); WriteInt(val);
  return(1);
}

bool MySock::PacketWrite(float val) {
  WriteByte(4); WriteDouble(val);
  return(1);
}

bool MySock::PacketWrite(double val) {
  WriteByte(4); WriteDouble(val);
  return(1);
}

void MySock::PacketSend(double val) {
  if(es_status == "host-1") {
    if(val) MessageSend(hdl_udp_server,ip_client,port_udp_c);
    else MessageSend(hdl_player_c,"",0);
  } else {
    if(val) MessageSend(hdl_udp_client,ip_server,port_udp_s);
    else MessageSend(hdl_tcp_client,"",0);
  }
}

char* MySock::PacketReadStr() {
  if (ReadByte()==20)return (ReadString(0,""));
  return ("");
}

char MySock::PacketReadB() {
  if (ReadByte()==0)return(ReadByte());
  return(0);
}

unsigned short MySock::PacketReadUs() {
  if (ReadByte()==0)return(ReadByte());
  if (ReadByte()==1)return(ReaduShort());
  return(0);
}

unsigned int MySock::PacketReadUi() {
  if (ReadByte()==0)return(ReadByte());
  if (ReadByte()==1)return(ReaduShort());
  if (ReadByte()==2)return(ReaduInt());
  return(0);
}

short MySock::PacketReadS() {
  if (ReadByte()==0)return(ReadByte());
  if (ReadByte()==3)return(ReadShort());
  return(0);
}

int MySock::PacketReadI() {
  if (ReadByte()==0)return(ReadByte());
  if (ReadByte()==3)return(ReadShort());
  if (ReadByte()==4)return(ReadDouble());
  return(0);
}

double MySock::PacketReadF() {
  if (ReadByte()==0)return(ReadByte());
  if (ReadByte()==1)return(ReaduShort());
  if (ReadByte()==2)return(ReaduInt());
  if (ReadByte()==3)return(ReadShort());
  if (ReadByte()==4)return(ReadDouble());
  return(0);
}
