#include "main.h"

#ifndef FUELUP_H
#define FUELUP_H


class Fuelup {
public:
    Fuelup() {}
    Fuelup(float x, float y,float z, float l,float w,color_t c1,color_t c2 );
    glm::vec3 position;
    float rotation,rotation2;
    float length,width;
    float erase;
    color_t color;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
private:
    VAO *object;
	VAO *object2;
};

#endif // Fuelbar_H
