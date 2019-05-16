#include "canonfire.h"
// #include "main.h"

Canonfire::Canonfire(float x, float y,float z,float r,ll id,color_t c) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->color = c;
    this->width=r;
    this->erase=0;
    this->index=id;
    GLfloat body[] = {
        r,r,r, // triangle 1 : begin
        -r,r, r,
        r, -r, r, // triangle 1 : end
        -r,r,r, // triangle 1 : begin
        r,-r,r, // triangle 1 : begin
        -r,-r,r, // triangle 1 : begin
        
        r,r,-r, // triangle 1 : begin
        -r,r, -r,
        r, -r, -r, // triangle 1 : end
        -r,r,-r, // triangle 1 : begin
        r,-r,-r, // triangle 1 : begin
        -r,-r,-r,
        
        r,r,r, // triangle 1 : begin
        r,-r, r,
        r, -r, -r, // triangle 1 : end
        r,r,-r, // triangle 1 : begin
        r,-r,-r, // triangle 1 : begin
        r,r,r,
 
        -r,r,r, // triangle 1 : begin
        -r,-r, r,
        -r, -r, -r, // triangle 1 : end
        -r,r,-r, // triangle 1 : begin
        -r,-r,-r, // triangle 1 : begin
        -r,r,r,       

        r,r,r, // triangle 1 : begin
        -r,r, r,
        -r, r, -r, // triangle 1 : end
        -r,r,-r, // triangle 1 : begin
        r,r,-r, // triangle 1 : begin
        r,r,r,

        r,-r,r, // triangle 1 : begin
        -r,-r, r,
        -r, -r, -r, // triangle 1 : end
        -r,-r,-r, // triangle 1 : begin
        r,-r,-r, // triangle 1 : begin
        r,-r,r  ,
    };
    this->object = create3DObject(GL_TRIANGLES, 36, body, this->color, GL_FILL);
}

void Canonfire::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate               ;
    rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Canonfire::tick() {
    this->position.x += this->ux*4.0;
    this->position.y += this->uy*4.0;
    this->position.z += this->uz*4.0;
}

