#ifndef BOMB_BOMB_H
#define BOMB_BOMB_H

class Bomb {
    public:

    float x,y;
    int id;
    byte type;
    int life;

    //0 - Regular
    //1 - Time Bomb
    //2 - Skull Bomb
    //3 - Through Bomb

    Bomb(float xpos, float ypos, int bomb_type) {
        x = xpos; y = ypos; type = (byte)bomb_type;
    }
};

#endif
