//*******************************************
// Camera Class
// Written by Kirk Backus
//*******************************************

#ifndef __H__CAMERA_
#define __H__CAMERA_

class Camera {
    public:
        
    Camera();
           
    float x,y,z;
    float xt,yt,zt;
    float dir;
    
    void MoveForward(float factor);
    void RotateCamera(float factor);
    
    void Update();
};

Camera::Camera() {
    x = 256; y = 256; z = 64;
    xt = 288; yt = 288; zt = 64;
    dir = 45;
}

void Camera::MoveForward(float factor) {
    x += cos(PI/180*dir)*factor;
    y += sin(PI/180*dir)*factor;
    xt = x + cos(PI/180*dir)*32;
    yt = y + sin(PI/180*dir)*32;
}

void Camera::RotateCamera(float factor) {
    dir += factor;
    xt = x + cos(PI/180*dir)*32;
    yt = y + sin(PI/180*dir)*32;
}

void Camera::Update() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    gluPerspective(45, 640/480, 1, 10000);
    gluLookAt(x,y,z,xt,yt,zt,0,0,1);
    
    glMatrixMode(GL_MODELVIEW);
}
    
#endif
