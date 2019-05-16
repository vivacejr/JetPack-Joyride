#include "main.h"

#ifndef BAR_H
#define BAR_H


class Bar {
public:
    Bar() {}
    Bar(float x, float y,float z, float l,float w,color_t c );
    glm::vec3 position;
    float rotation,rotation2;
    float fuel,width;
    color_t color;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
private:
	VAO *object;
};

#endif // Bar_H
