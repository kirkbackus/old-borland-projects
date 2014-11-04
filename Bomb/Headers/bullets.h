#ifndef __BULLETS_H
#define __BULLETS_H

class Bullet {
    public:

    int type;
    int power;
    float xs,ys,xp,yp,x,y,h,v,dir;
    bool destroy;
    float r,g,b;

    int size;
    Blackbox::Polygon* collide;

    Bullet(int id, float xpos, float ypos, float direction, Blackbox::Polygon* collision_mask);
    ~Bullet();

    void Update();
    void Draw(float red, float green, float blue);
};

Bullet::Bullet(int id, float xpos, float ypos, float direction, Blackbox::Polygon* collision_mask) {
    type = id;
    dir = direction;
    x = xpos; xs = x;
    y = ypos; ys = y;
    collide = collision_mask;
    destroy = 0;

    switch(type) {
        case 0: //None - This should never be called
        break;

        case 1: //Pistol Bullet

        h = cos(PI/180*direction)*16;
        v = sin(PI/180*direction)*16;
        size = 2;
        power = 15;
        break;

        case 2: //Rocket

        h = cos(PI/180*direction)*10;
        v = sin(PI/180*direction)*10;
        size = 16;
        power = 120;
        break;

        case 3: //Lazer

        h = cos(PI/180*direction)*25;
        v = sin(PI/180*direction)*25;
        size = 2;
        power = 100;
        break;

        case 4: //Shotgun

        h = cos(PI/180*direction)*16;
        v = sin(PI/180*direction)*16;
        size = 2;
        power = 15;
        break;

        case 5: //Machine Gun

        h = cos(PI/180*direction)*16;
        v = sin(PI/180*direction)*16;
        size = 2;
        power = 10;
    }
}

Bullet::~Bullet() {
    if (type==2) pe.Burst(x,y,1,200,r,g,b);
    else pe.Burst(x,y,.5,8,r,g,b);
}

void Bullet::Update() {
    if (destroy) return;
    xp = x;
    yp = y;
    x += h;
    y += v;
}

void Bullet::Draw(float red, float green, float blue) {
    r = red; g = green; b = blue;
    pe.Burst(x,y,.3,2,r,g,b);
    pe.Burst((x+xp)/2,(y+yp)/2,.3,2,r,g,b);

    glPushMatrix();
    glTranslatef(x,y,0);
    DrawCircle(0,0,size,16,r,g,b,1,1);
    glPopMatrix();
}
#endif
