#include "main.h"

#ifndef ARROW_H
#define ARROW_H


class Arrow {
public:
    Arrow() {}
    Arrow(float x, float y,float z, float r,float l,color_t c);
    glm::vec3 position;
    float rotation;
    float width;
    float length;
    color_t color;
    float ux,uy,uz;
    float erase;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
private:
    VAO *object;
    VAO *object2;
};

#endif // Canon_H
