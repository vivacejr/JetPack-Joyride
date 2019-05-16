#include "main.h"

#ifndef ROCKET_H
#define ROCKET_H


class Rocket{
public:
    Rocket() {}
    Rocket(float x, float y,float z,float w,ll i,color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    bool tick();
    bool collision(pt a,pt b,pt c);
    float speed;
    float dir;
    float verdir;
    float height;
    float radius;
    float erase;
    ll index;
    float initialx;
    float rotx,roty,rotz;
private:
    VAO *object;
};


#endif // Drangon_H
