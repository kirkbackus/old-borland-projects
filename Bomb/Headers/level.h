#ifndef __LEVEL_H
#define __LEVEL_H

#include "upgrade.h"

class Level {
    public:

    vector<Blackbox::Polygon*> polygons;
    vector<Upgrade*> upgrades;

    void AddUpgrade(float x, float y, int type, Blackbox::Polygon* collision_mask) {
        upgrades.push_back(new Upgrade(x,y,type,collision_mask));
    }

    void AddRectangle(float x1, float y1, float x2, float y2) {
        polygons.push_back(new Blackbox::Polygon());

        polygons[polygons.size()-1]->position.x = (x1+x2)/2;
        polygons[polygons.size()-1]->position.y = (y1+y2)/2;

        float cx, cy;

        cx = polygons[polygons.size()-1]->position.x;
        cy = polygons[polygons.size()-1]->position.y;

        polygons[polygons.size()-1]->BuildRect(x1-cx,y1-cy,x2-cx,y2-cy);
    }

    void AddCircle(float x, float y, float r, float detail) {
        polygons.push_back(new Blackbox::Polygon());
        polygons[polygons.size()-1]->BuildCircle(0,0,r,detail);
        polygons[polygons.size()-1]->position.x = x;
        polygons[polygons.size()-1]->position.y = y;
    }

    void SetLimits(float width, float height) {
        AddRectangle(-1024,-1024,width+1024,32);
        AddRectangle(-1024,height-32,width+1024,height+1024);
        AddRectangle(width-32,-1024,width+1024,height+1024);
        AddRectangle(-1024,-1024,32,height+1024);
    }

    void Collided(Player* p) {
        p->collide->position.x = p->x;
        p->collide->position.y = p->y;

        Blackbox::Vector vtmp;
        for (int i=0;i<polygons.size();i++) {
            if (p->collide->Collided(polygons[i],&vtmp)) {
                p->collide->position -= vtmp*1.1;
            }
        }

        for (int i=0;i<upgrades.size();i++) {
            upgrades[i]->collide->position.x = upgrades[i]->x;
            upgrades[i]->collide->position.y = upgrades[i]->y;
            if (p->collide->Collided(upgrades[i]->collide)) {
                if (!upgrades[i]->visible) continue;

                bool max = 0;

                switch(upgrades[i]->type) {
                    case 0: //Health
                    if (p->health<100) p->AddHealth();
                    else max = 1;
                    break;

                    case 1: //Ammo
                    if (p->weapon->ammo < p->weapon->maxammo) p->AddAmmo();
                    else max = 1;
                    break;

                    case 2: //Machine Gun
                    if (p->weapon->type!=5) p->weapon->Change(5);
                    else max = 1;
                    break;

                    case 3: //Rocket Launcher
                    if (p->weapon->type!=2) p->weapon->Change(2);
                    else max = 1;
                    break;

                    case 4: //Laser
                    if (p->weapon->type!=3) p->weapon->Change(3);
                    else max = 1;
                    break;

                    case 5: //Shotgun
                    if (p->weapon->type!=4) p->weapon->Change(4);
                    else max = 1;
                    break;

                    default:
                    break;
                }

                if (!max) {
                    upgrades[i]->visible = 0;
                    upgrades[i]->reload = 600;
                }
            }
        }

        p->x = p->collide->position.x;
        p->y = p->collide->position.y;

        for (int i=0;i<p->weapon->bullets.size();i++) {
            Collided(p->weapon->bullets[i]);
        }
    }

    void CollidedBullets(Player* p1, Player* p2, Player* p3, Player* p4) {
        if (!p1->visible || !p1->alive) return;

        p1->collide->position.x = p1->x;
        p1->collide->position.y = p1->y;

        if (p2->visible && p2->alive)
        for (int i=0;i<p2->weapon->bullets.size();i++) {
            p2->weapon->bullets[i]->collide->position.x = p2->weapon->bullets[i]->x;
            p2->weapon->bullets[i]->collide->position.y = p2->weapon->bullets[i]->y;
            if (p1->collide->Collided(p2->weapon->bullets[i]->collide)) {
                if (p1->control) p1->Hurt(p2->weapon->bullets[i]->power,p2);
                delete p2->weapon->bullets[i];
                p2->weapon->bullets.erase(p2->weapon->bullets.begin()+i);
                i--;
            }
        }

        if (p3->visible && p3->alive)
        for (int i=0;i<p3->weapon->bullets.size();i++) {
            p3->weapon->bullets[i]->collide->position.x = p3->weapon->bullets[i]->x;
            p3->weapon->bullets[i]->collide->position.y = p3->weapon->bullets[i]->y;
            if (p1->collide->Collided(p3->weapon->bullets[i]->collide)) {
                if (p1->control) p1->Hurt(p3->weapon->bullets[i]->power,p3);
                delete p3->weapon->bullets[i];
                p3->weapon->bullets.erase(p3->weapon->bullets.begin()+i);
                i--;
            }
        }

        if (p4->visible && p4->alive)
        for (int i=0;i<p4->weapon->bullets.size();i++) {
            p4->weapon->bullets[i]->collide->position.x = p4->weapon->bullets[i]->x;
            p4->weapon->bullets[i]->collide->position.y = p4->weapon->bullets[i]->y;
            if (p1->collide->Collided(p4->weapon->bullets[i]->collide)) {
                if (p1->control) p1->Hurt(p4->weapon->bullets[i]->power,p4);
                delete p4->weapon->bullets[i];
                p4->weapon->bullets.erase(p4->weapon->bullets.begin()+i);
                i--;
            }
        }
    }

    void Collided(Bullet* b) {
        b->collide->position.x = b->x;
        b->collide->position.y = b->y;

        Blackbox::Vector vtmp;
        for (int i=0;i<polygons.size();i++) {
            if (b->collide->Collided(polygons[i],&vtmp)) {
                b->destroy = 1;
            }
        }
    }

    void Clear() {
        for (int i=0;i<polygons.size();) {
            delete polygons[i];
            polygons.erase(polygons.begin()+i);
        }
    }

    void Draw() {
        for (int i=0;i<polygons.size();i++) {
            DrawPolygon(polygons[i],1,1,1,.5,0);
            DrawPolygon(polygons[i],1,1,1,1,1);
        }

        for (int i=0;i<upgrades.size();i++) {
            upgrades[i]->Draw();
        }
    }
};

#endif
