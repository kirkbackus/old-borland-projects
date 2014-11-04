#ifndef __WEAPON_H
#define __WEAPON_H

#include "bullets.h"

class Weapon {
    public:

    int type;

    int reloadtime;
    int reload;
    int maxammo, ammo;
    vector<Bullet*> bullets;

    Weapon(int id);
    ~Weapon();

    void Update();
    bool Shoot(float xpos, float ypos, float direction, Blackbox::Polygon* collide_mask);
    bool CanShoot();

    void Draw(float xpos, float ypos, float direction, float r, float g, float b, bool alive);

    void Change(int id);
};

Weapon::~Weapon() {
    for (int i=0;i<bullets.size();) {
        delete bullets[i];
        bullets.erase(bullets.begin()+i);
    }
}

Weapon::Weapon(int id) {
    Change(id);
}

void Weapon::Change(int id) {
    type = id;
    reload = 0;

    switch(type) {
        case 0: //No weapon

        reloadtime = 0;
        ammo = 0;
        maxammo = 0;

        break;

        case 1: //Pistol

        reloadtime = 20;
        maxammo = 50;
        ammo = 25;
        break;

        case 2: //Rocket

        reloadtime = 100;
        maxammo = 6;
        ammo = 3;
        break;

        case 3: //Laser

        reloadtime = 120;
        maxammo = 8;
        ammo = 4;
        break;

        case 4: //Shotgun

        reloadtime = 60;
        maxammo = 120;
        ammo = 60;
        break;

        case 5: //Machine Gun

        reloadtime = 4;
        maxammo = 260;
        ammo = 130;
        break;
    }
}

bool Weapon::CanShoot() { return ((reload==0 ? 1 : 0) && ammo>0); }

bool Weapon::Shoot(float xpos, float ypos, float direction, Blackbox::Polygon* collide_mask) {
    if (CanShoot()) {
        reload = reloadtime;
        if (type!=4) {
            bullets.push_back(new Bullet(type,xpos,ypos,direction,collide_mask));
            ammo--;
        } else if (ammo>=5) {
            bullets.push_back(new Bullet(type,xpos,ypos,direction-10,collide_mask));
            bullets.push_back(new Bullet(type,xpos,ypos,direction-5,collide_mask));
            bullets.push_back(new Bullet(type,xpos,ypos,direction,collide_mask));
            bullets.push_back(new Bullet(type,xpos,ypos,direction+5,collide_mask));
            bullets.push_back(new Bullet(type,xpos,ypos,direction+10,collide_mask));
            ammo-=5;
        }

    } else return 0;
    return 1;
}

void Weapon::Update() {
    if (reload>0) reload-=1;

    for (int i=0;i<bullets.size();i++) {
        bullets[i]->Update();
        if (bullets[i]->destroy) {
            delete bullets[i];
            bullets.erase(bullets.begin()+i);
            i--;
        }
    }
}

void Weapon::Draw(float xpos, float ypos, float direction, float r, float g, float b, bool alive) {
    //Weapon Drawing Code HERE
    if (alive) {
        glPushMatrix();

        glTranslatef(xpos,ypos,0);
        glRotatef(direction,0,0,1);

        DrawRectangle(0,-4,16,4,r,g,b,.5,0);
        DrawRectangle(0,-4,16,4,r,g,b,1,1);

        glPopMatrix();
    }

    //Draw all bullets
    for (int i=0;i<bullets.size();i++) {
        if (bullets[i]!=NULL) bullets[i]->Draw(r,g,b);
    }
}
#endif
