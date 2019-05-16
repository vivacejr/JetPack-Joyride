#include "main.h"

#ifndef WATER_H
#define WATER_H


class Water {
public:
    Water() {}
    Water(float x, float y,float z,float t,float a,color_t c);
    glm::vec3 position;
    float rotation,rotation2;
    void draw(glm::mat4 VP);
    float total,side;
    void set_position(float x, float y);
    void tick();
private:
	VAO *object;
};

#endif // BALL_H
