#include "canon.h"
// #include "main.h"

Canon::Canon(float x, float y,float z, float w,float r,color_t c,color_t c2) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->color = c;
    this->side=r;
    this->width=w;
    this->erase=0;
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

/////////////////////////////////////////////
    };
    float d=2;
    GLfloat body2[] = {
        r/d,r+w,r/d, // triangle 1 : begin
        -r/d,r+w, r/d,
        r/d, r, r/d, // triangle 1 : end
        -r/d,r+w,r/d, // triangle 1 : begin
        r/d,r,r/d, // triangle 1 : begin
        -r/d,r,r/d, // triangle 1 : begin
        
        r/d,r+w,-r/d, // triangle 1 : begin
        -r/d,r+w, -r/d,
        r/d, r, -r/d, // triangle 1 : end
        -r/d,r+w,-r/d, // triangle 1 : begin
        r/d,r,-r/d, // triangle 1 : begin
        -r/d,r,-r/d,
        
        r/d,r+w,r/d, // triangle 1 : begin
        r/d,r, r/d,
        r/d,r, -r/d, // triangle 1 : end
        r/d,r+w,-r/d, // triangle 1 : begin
        r/d,r,-r/d, // triangle 1 : begin
        r/d,r+w,r/d,
 
        -r/d,r+w,r/d, // triangle 1 : begin
        -r/d,r, r/d,
        -r/d,r, -r/d, // triangle 1 : end
        -r/d,r+w,-r/d, // triangle 1 : begin
        -r/d,r,-r/d, // triangle 1 : begin
        -r/d,r+w,r/d,       

        r/d,r+w,r/d, // triangle 1 : begin
        -r/d,r+w, r/d,
        -r/d, r+w, -r/d, // triangle 1 : end
        -r/d,r+w,-r/d, // triangle 1 : begin
        r/d,r+w,-r/d, // triangle 1 : begin
        r/d,r+w,r/d,

        r/d,r,r/d, // triangle 1 : begin
        -r/d,r, r/d,
        -r/d, r, -r/d, // triangle 1 : end
        -r/d,r,-r/d, // triangle 1 : begin
        r/d,r,-r/d, // triangle 1 : begin
        r/d,r,r/d  ,
    };   
    this->object = create3DObject(GL_TRIANGLES, 36, body, this->color, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 36, body2, c2, GL_FILL);
}

void Canon::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate               ;
    rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    draw3DObject(this->object2);
}

void Canon::tick() {
    // this->position.x -= speed;
    // this->position.y -= speed;
}

