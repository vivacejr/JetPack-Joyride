#include "main.h"

#ifndef POWER_H
#define POWER_H


class Power{
public:
    Power() {}
    Power(float x, float y,float z,float w,ll i,color_t color);
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
    float verspeed;
private:
    VAO *object;
};


#endif // Drangon_H
