#include "main.h"

#ifndef CANON_H
#define CANON_H


class Canon {
public:
    Canon() {}
    Canon(float x, float y,float z, float l,float w,color_t c ,color_t c2);
    glm::vec3 position;
    float rotation;
    float width;
    float side;
    float erase;
    color_t color;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
private:
    VAO *object;
    VAO *object2;
};

#endif // Canon_H
