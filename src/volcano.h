#include "main.h"

#ifndef VOLCANO_H
#define VOLCANO_H


class Volcano {
public:
    Volcano() {}
    Volcano(float x, float y, float z,float r,float h,color_t c);
    glm::vec3 position;
    float rotation;
    float radius,height;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
private:
	VAO *object;
};

#endif // VOLCANO_H
