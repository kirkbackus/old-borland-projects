class HUD {
    public:

    glFont* font;

    float health;
    float ammo;
    float maxammo;

    int weaponid;
    char weapon[32];

    HUD(HDC dc);

    void Draw();
};

HUD::HUD(HDC dc) {
    font = new glFont(dc,"Arial",32);
}

void HUD::Draw() {
    glPushMatrix();

    DrawRectangle(8,8,192,40,0,0,0,1,0);
    DrawRectangle(8,8,8+184*(health/100.0),40,0,.8,0,1,0);
    DrawRectangle(8,8,192,20,1,1,1,.25,0);
    DrawRectangle(8,8,192,40,0,0,0,1,1);

    switch(weaponid) {
        case 0:
        sprintf(weapon,"None");
        break;

        case 1:
        sprintf(weapon,"Pistol");
        break;

        case 2:
        sprintf(weapon,"Rocket Launcher");
        break;

        case 3:
        sprintf(weapon,"Laser");
        break;

        case 4:
        sprintf(weapon,"Shotgun");
        break;

        case 5:
        sprintf(weapon,"Machine Gun");
        break;

        default:
        sprintf(weapon,"-- YOU SHOULDN'T SEE THIS --");
        break;
    }

    glColor4f(0,0,0,1);
    font->glPrint(322,7,FA_CENTER,weapon);
    glColor4f(1,1,1,1);
    font->glPrint(320,5,FA_CENTER,weapon);

    glColor4f(0,0,0,1);
    font->glPrint(636,7,FA_RIGHT,"%i/%i",(int)ammo,(int)maxammo);
    glColor4f(1,1,1,1);
    font->glPrint(635,5,FA_RIGHT,"%i/%i",(int)ammo,(int)maxammo);

    glPopMatrix();
}
