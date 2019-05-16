#include "volcano.h"

Volcano::Volcano(float x, float y, float z,float r,float h,color_t c) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->radius=r;
    this->height=h;
    GLfloat body[2000] ;
    float n=100;
    lp(i,0,n)
    {
        body[9*i+0]=r*cos(i*2.0*M_PI/n);
        body[9*i+1]=0;
        body[9*i+2]=r*sin(i*2.0*M_PI/n);
        body[9*i+3]=r*cos((i+1)*2.0*M_PI/n);
        body[9*i+4]=0;
        body[9*i+5]=r*sin((i+1)*2.0*M_PI/n);
        body[9*i+6]=0;
        body[9*i+7]=h;
        body[9*i+8]=0;
    }
	this->object = create3DObject(GL_TRIANGLES,3*n, body, c, GL_FILL);
}

void Volcano::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate;
    rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Volcano::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}        

void Volcano::tick() {
    // this->position.x -= speed;
    // this->position.y -= speed;
}

