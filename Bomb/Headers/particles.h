#include "textures.h"

struct Particle {
    float x,y,h,v;
    float friction;
    float size;
    float life;
    float r,g,b;
};

class ParticleEngine {
    public:

    vector<Particle*> particles;

    ParticleEngine();

    void Burst(float x, float y, float speed, int number, float r, float g, float b);
    void Update();
    void Draw();
} pe;

ParticleEngine::ParticleEngine() {
    //txt = new Texture();
    //if(!txt->LoadTexture64("particle.bmp")) MessageBox(NULL,"ERROR LOADING particle.bmp","ERROR",MB_OK | MB_ICONINFORMATION);
}

void ParticleEngine::Burst(float x, float y, float speed, int number, float r, float g, float b) {
    for (int i=0;i<number;i++) {
        particles.push_back(new Particle());
        particles[particles.size()-1]->x = x;
        particles[particles.size()-1]->y = y;

        particles[particles.size()-1]->r = r;
        particles[particles.size()-1]->g = g;
        particles[particles.size()-1]->b = b;

        particles[particles.size()-1]->size = 8;
        particles[particles.size()-1]->life = 1;
        particles[particles.size()-1]->friction = 0;

        float rdir = PI/180*(rand()%360);
        float spd = speed*(rand()%100)/100.0;
        particles[particles.size()-1]->h = cos(rdir)*spd;
        particles[particles.size()-1]->v = sin(rdir)*spd;
    }
}

void ParticleEngine::Update() {
    for (int i=0;i<particles.size();i++) {
        particles[i]->x+=particles[i]->h;
        particles[i]->y+=particles[i]->v;

        if (particles[i]->life>0)particles[i]->life-=.01;
        else {
            delete particles[i];
            particles.erase(particles.begin()+i);
            i--;
        }
    }
}

void ParticleEngine::Draw() {
    glBlendFunc(GL_SRC_ALPHA,GL_ONE);

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();

    for (int i=0;i<particles.size();i++) {
        glBegin(GL_TRIANGLE_STRIP);

        glColor4f(particles[i]->r,particles[i]->g,particles[i]->b,particles[i]->life);

        glTexCoord2d(1,1); glVertex2f(particles[i]->x+particles[i]->size/2,particles[i]->y+particles[i]->size/2); // Top Right
        glTexCoord2d(0,1); glVertex2f(particles[i]->x-particles[i]->size/2,particles[i]->y+particles[i]->size/2); // Top Left
		glTexCoord2d(1,0); glVertex2f(particles[i]->x+particles[i]->size/2,particles[i]->y-particles[i]->size/2); // Bottom Right
		glTexCoord2d(0,0); glVertex2f(particles[i]->x-particles[i]->size/2,particles[i]->y-particles[i]->size/2); // Bottom Left

        glEnd();
    }

    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}
