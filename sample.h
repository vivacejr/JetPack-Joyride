#include "main.h"

#ifndef BALL_H
#define BALL_H


class Ball {
public:
    Ball() {}
    Ball(float x, float y, float r,color_t c1,color_t c2,color_t c3);
    glm::vec3 position;
    float rotation,rotation2;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
private:
	VAO *object;
};

#endif // BALL_H
