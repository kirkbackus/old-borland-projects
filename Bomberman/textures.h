class Textures {
  private:

  unsigned int txt[100];  //Space for textures
  int id;
  int numtex;
  HINSTANCE hi;

  public:

  Textures(HINSTANCE _hi) {
    id=0;
    numtex=0;
    hi=_hi;

    //Generate Space for textures
    glGenTextures(100, &txt[numtex]);
  }

  void SetTexture(int _id) {
    if (_id>numtex)_id=numtex;id=_id;
    glBindTexture(GL_TEXTURE_2D, txt[id]);
  }

  int NumTextures() {
    return(numtex);
  }

  bool AddTexture128(const char* fname,int index);
  bool AddTexture64(const char* fname,int index);
  bool AddTexture16(const char* fname,int index, int transparent);
};

bool Textures::AddTexture128(const char* fname,int index) {
  HBITMAP image;
  image=(HBITMAP)LoadImageA(hi,fname,IMAGE_BITMAP,0,0,LR_LOADFROMFILE | LR_LOADTRANSPARENT);
  if (image==NULL)return false;
  byte bits[128][128][4];
  GetBitmapBits(image,65535,bits);

  for (int x=0;x<128;x++) {
    for (int y=0;y<128;y++) {
      //Switch BGR to RGB ^_^
      byte bit=bits[x][y][0];
      bits[x][y][0]=bits[x][y][2];
      bits[x][y][2]=bit;
    }
  }

  unsigned long transcolor=RGB(bits[0][127][0],bits[0][127][1],bits[0][127][2]);
  for (int x=0;x<128;x++) {
    for (int y=0;y<128;y++) {
      if (transcolor!=RGB(bits[x][y][0],bits[x][y][1],bits[x][y][2]))
        bits[x][y][3]=255;
    }
  }

  glBindTexture(GL_TEXTURE_2D, txt[index]);

  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_CLAMP);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_CLAMP);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 128, 128, 0,
		GL_RGBA, GL_UNSIGNED_BYTE, bits);

  numtex++;

  delete &bits;

  return true;
}

bool Textures::AddTexture64(const char* fname, int index) {
  HBITMAP image;
  image=(HBITMAP)LoadImageA(hi,fname,IMAGE_BITMAP,0,0,LR_LOADFROMFILE | LR_LOADTRANSPARENT);
  if (image==NULL)return false;
  byte bits[64][64][4];
  GetBitmapBits(image,16383,bits);

  //Switch BGR to RGB ^_^
  for (int x=0;x<64;x++) {
    for (int y=0;y<64;y++) {
      byte bit=bits[x][y][0];
      bits[x][y][0]=bits[x][y][2];
      bits[x][y][2]=bit;
    }
  }

  unsigned long transcolor=RGB(bits[0][63][0],bits[0][63][1],bits[0][63][2]);
  for (int x=0;x<64;x++) {
    for (int y=0;y<64;y++) {
      if (transcolor!=RGB(bits[x][y][0],bits[x][y][1],bits[x][y][2]))
        bits[x][y][3]=255;
    }
  }

  glBindTexture(GL_TEXTURE_2D, txt[index]);

  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR_MIPMAP_NEAREST);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_CLAMP);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_CLAMP);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 64, 64, 0, GL_RGBA, GL_UNSIGNED_BYTE, bits);

  numtex++;

  delete &bits;

  return true;
}

bool Textures::AddTexture16(const char* fname, int index, int transparent) {
  HBITMAP image=(HBITMAP)LoadImageA(hi,fname,IMAGE_BITMAP,0,0,LR_LOADFROMFILE | LR_LOADTRANSPARENT);
  if (image==NULL)return false;
  byte bits[16][16][4];
  GetBitmapBits(image,1024,bits);

  //Switch BGR to RGB ^_^
  for (int x=0;x<16;x++) {
    for (int y=0;y<16;y++) {
      byte bit=bits[x][y][0];
      bits[x][y][0]=bits[x][y][2];
      bits[x][y][2]=bit;
    }
  }

  unsigned long transcolor=RGB(bits[0][15][0],bits[0][15][1],bits[0][15][2]);
  for (int x=0;x<16;x++) {
    for (int y=0;y<16;y++) {
      if (transcolor!=RGB(bits[x][y][0],bits[x][y][1],bits[x][y][2]))bits[x][y][3]=255;
      if (!transparent)bits[x][y][3]=255;
    }
  }

  glBindTexture(GL_TEXTURE_2D, txt[index]);

  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR_MIPMAP_NEAREST);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_CLAMP);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_CLAMP);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 16, 16, 0, GL_RGBA, GL_UNSIGNED_BYTE, bits);

  numtex++;

  delete &bits;

  return true;
}