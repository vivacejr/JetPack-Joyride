#include "main.h"

#ifndef RING_H
#define RING_H


class Ring {
public:
    Ring() {}
    Ring(float x, float y,float z,float w,color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    bool collision(pt a,pt b,pt c);
    void tick();
    float speed;
    float dir;
    float radius;
    float display;
    float timer;
    float erase;
    // float dir=d;
private:
    VAO *object;
};


#endif // Drangon_H
