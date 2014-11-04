#ifndef __H__TEXTURES_
#define __H__TEXTURES_

class Texture {
    private:

    GLuint txt;

    public:

    Texture() { glGenTextures(1, &txt); }
    ~Texture() { glDeleteTextures(1, &txt); }
    HINSTANCE hi;

    void SetTexture() { glBindTexture(GL_TEXTURE_2D, txt); }
    GLuint GetTexture() { return(txt);}

    bool LoadTexture64(const char* fname);
    bool LoadTexture128(const char* fname);
    bool LoadTexture256(const char* fname);
    bool LoadTexture512(const char* fname);
};

bool Texture::LoadTexture64(const char* fname) {
    HBITMAP image;
    image=(HBITMAP)LoadImage(hi,fname,IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
    if (image==NULL)return false;
    byte bits[64][64][4];
    GetBitmapBits(image,64*64*4,bits);

    glBindTexture(GL_TEXTURE_2D, txt);

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_REPEAT);

    gluBuild2DMipmaps( GL_TEXTURE_2D, 3, 64, 64, GL_RGBA, GL_UNSIGNED_BYTE, bits);

    delete &bits;

    return true;
}

bool Texture::LoadTexture128(const char* fname) {
    HBITMAP image;
    image=(HBITMAP)LoadImage(NULL,fname,IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
    if (image==NULL)return false;
    byte bits[128][128][4];
    GetBitmapBits(image,128*128*4,bits);

    glBindTexture(GL_TEXTURE_2D, txt);

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_REPEAT);

    gluBuild2DMipmaps( GL_TEXTURE_2D, 3, 128, 128, GL_RGBA, GL_UNSIGNED_BYTE, bits);

    delete &bits;

    return true;
}

bool Texture::LoadTexture256(const char* fname) {
    HBITMAP image;
    image=(HBITMAP)LoadImage(hi,fname,IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
    if (image==NULL)return false;
    byte bits[256][256][4];
    GetBitmapBits(image,256*256*4,bits);

    glBindTexture(GL_TEXTURE_2D, txt);

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_REPEAT);

    gluBuild2DMipmaps( GL_TEXTURE_2D, 3, 256, 256, GL_RGBA, GL_UNSIGNED_BYTE, bits );

    delete &bits;

    return true;
}

bool Texture::LoadTexture512(const char* fname) {
    HBITMAP image;
    image=(HBITMAP)LoadImage(hi,fname,IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
    if (image==NULL)return false;
    byte bits[512][512][4];
    GetBitmapBits(image,512*512*4,bits);

    glBindTexture(GL_TEXTURE_2D, txt);

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_REPEAT);

    gluBuild2DMipmaps( GL_TEXTURE_2D, 3, 512, 512, GL_RGBA, GL_UNSIGNED_BYTE, bits );

    delete &bits;

    return true;
}

#endif
