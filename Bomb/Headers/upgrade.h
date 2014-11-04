class Upgrade {
    public:

    int type;

    Blackbox::Polygon* collide;

    float x,y;
    float rotation;

    bool visible;
    int reload;

    Upgrade(float xpos, float ypos, int t1, Blackbox::Polygon* collision_mask);

    void Draw();
};

Upgrade::Upgrade(float xpos, float ypos, int t1, Blackbox::Polygon* collision_mask) {
    x = xpos;
    y = ypos;
    type = t1;
    collide = collision_mask;
    visible = 1;
    rotation = 0;
}

void Upgrade::Draw() {
    if (!visible) {
        if (reload>0) reload--;
        else visible = 1;
        return;
    }

    rotation += 1;

    glPushMatrix();
    glTranslatef(x,y,0);
    glRotatef(rotation,0,0,1);

    DrawCircle(0,0,16,16,1,1,1,.25,0);
    DrawCircle(0,0,16,16,1,1,1,1,1);

    switch (type) {
        case 0: //Health

        DrawRectangle(-8,-4,8,4,0,1,0,1,0);
        DrawRectangle(-4,-8,4,8,0,1,0,1,0);

        break;

        case 1: //Add Ammo

        DrawRectangle(-8,-4,8,4,1,0,0,1,0);
        DrawRectangle(-4,-8,4,8,1,0,0,1,0);

        break;

        case 2: //Machine Gun

        DrawRectangle(-8,-4,8,0,1,0,1,1,0);
        DrawRectangle(-8,0,-4,4,1,0,1,1,0);

        break;

        case 3: //Rocket Launcher

        DrawRectangle(-8,-4,8,0,0,0,1,1,0);
        DrawRectangle(-8,0,-4,4,0,0,1,1,0);

        break;

        case 4: //Lazer

        DrawRectangle(-8,-4,8,0,1,1,0,1,0);
        DrawRectangle(-8,0,-4,4,1,1,0,1,0);

        break;

        case 5: //Shotgun

        DrawRectangle(-8,-4,8,0,0,1,0,1,0);
        DrawRectangle(-8,0,-4,4,0,1,0,1,0);

        break;
    }

    glPopMatrix();
}
