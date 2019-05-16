#include "main.h"

#ifndef BALL_H
#define BALL_H


class Ball {
public:
    Ball() {}
    Ball(float x, float y, float r,color_t c1,color_t c2,color_t c3);
    glm::vec3 position;
    float rotation1,rotation2,rotation3;
    bool rotation_flag;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void move_right();
    void move_left();    
    void tick();
    float radius;
    double speed;
    float dir;
    float wing_width,wing_height;
    float wing_length;
    float body_length;
    float mat[4][4];
    color_t color,col_body,col_upperwing,col_lowerwing;
private:
	VAO *object;
    VAO *obj_body;
    VAO *obj_upperwing;
    VAO *obj_lowerwing;
};

#endif // BALL_H
