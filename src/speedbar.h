#include "main.h"

#ifndef SPEEDBAR_H
#define SPEEDBAR_H


class Speedbar {
public:
    Speedbar() {}
    Speedbar(float x, float y,float z, float l,float w,color_t c );
    glm::vec3 position;
    float rotation,rotation2;
    float speed,width;
    color_t color;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
private:
    VAO *object;
};

#endif // Speedbar_H
