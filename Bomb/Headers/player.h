#include "weapon.h"

class Player {
    public:

    float xs, ys, x, y, xp, yp;
    float aimx, aimy, aimdir;
    float health;

    bool control;

    float r,g,b;

    bool alive;
    int respawn;

    bool visible;

    Weapon* weapon;
    Player* lasthurt;
    Player* killedby;

    Blackbox::Polygon* collide;

    Blackbox::Polygon* bullet;
    Blackbox::Polygon* rocket;

    Player(float xstart, float ystart, int weapon_id);
    ~Player();

    void SetCollisionPoly(Blackbox::Polygon* polygon) { collide = polygon; }
    void SetCollisionBullets(Blackbox::Polygon* bullets, Blackbox::Polygon* rockets) { bullet = bullets; rocket = rockets; }
    void SetColor(float red, float green, float blue) { r = red; g = green; b = blue; }
    void Activate(bool make_active) { visible = make_active; }

    void Hurt(int health_lose, Player* player);

    bool Shoot();
    void Update();
    void Draw();

    void AddHealth();
    void AddAmmo();
};

Player::Player(float xstart, float ystart, int weapon_id) {
    x = xstart; xs = x;
    y = ystart; ys = y;
    visible = 0;
    health = 100;
    control = 0;

    alive = 1;
    respawn = -1;
    killedby = NULL;

    weapon = new Weapon(weapon_id);
}

Player::~Player() {
    delete weapon;
    delete collide;
}

void Player::AddHealth() {
    health+=33;
    if (health>100) health = 100;
}

void Player::Hurt(int health_lose, Player* player) {
    if (health>0) {
        health -= health_lose;
        lasthurt = player;
    }
}

void Player::AddAmmo() {
    weapon->ammo += weapon->maxammo/3+1;
    if (weapon->ammo > weapon->maxammo) weapon->ammo = weapon->maxammo;
}

void Player::Update() {
    weapon->Update(); //Update Weapon

    if (health<=0 && respawn==-1) {
        respawn = 100;
        alive = 0;
        pe.Burst(x,y,3,500,r,g,b);
        killedby = lasthurt;
    } else if (respawn > 0) {
        respawn--;
        if (respawn==0) {
            respawn=-1;
            alive = 1;
            health = 100;
            x = Choose(64,1216);
            y = Choose(64,880);
            weapon->Change(1);
        }
    }

    if (health < 0) health = 0;
}

bool Player::Shoot() {
    if (weapon->type==2) return(weapon->Shoot(x,y,aimdir,rocket));
    else return(weapon->Shoot(x,y,aimdir,bullet));
}

void Player::Draw() {
    if (!visible) return;

    weapon->Draw(x,y,aimdir,r,g,b,alive);

    if (!alive) return;

    collide->position.x = x;
    collide->position.y = y;

    DrawPolygon(collide,r,g,b,.5,0);
    DrawPolygon(collide,r,g,b,1,1);
}
