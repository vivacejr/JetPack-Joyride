#include "main.h"

#ifndef CANONFIRE_H
#define CANONFIRE_H


class Canonfire {
public:
    Canonfire() {}
    Canonfire(float x, float y,float z, float l,ll id,color_t c);
    glm::vec3 position;
    float rotation;
    float width;
    float side;
    color_t color;
    float ux,uy,uz;
    float erase;
    ll index;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
private:
    VAO *object;
    VAO *object2;
};

#endif // Canon_H
