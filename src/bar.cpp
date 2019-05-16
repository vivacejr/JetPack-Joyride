#include "bar.h"
// #include "main.h"

Bar::Bar(float x, float y,float z, float l,float w,color_t c) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->fuel=l;
    this->width=w;
    this->color = c;
}

void Bar::draw(glm::mat4 VP) {
    float w=this->width;
    float l=this->fuel;
    GLfloat body[] = {
        w/2,l,0,
        -w/2,l,0,
        w/2,0,0,
        w/2,0,0,
        -w/2,0,0,
        -w/2,l,0,
    };   
    this->object = create3DObject(GL_TRIANGLES, 6, body, this->color, GL_FILL);
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
	glm::mat4 rotate               ;
	rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Bar::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}        

void Bar::tick() {
    // this->position.x -= speed;
    // this->position.y -= speed;
}

