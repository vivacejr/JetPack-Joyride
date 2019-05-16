#include "fuelup.h"
// #include "main.h"

Fuelup::Fuelup(float x, float y,float z, float r,float w,color_t c1,color_t c2) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->length=r;
    this->width=w;
    this->color = c1;
    this->erase=0;
    float r2=r/2.0;
    float w2=w/2.0;
    GLfloat body2[] ={

        r+r,r2,w2, // triangle 1 : begin
        -r+r,r2, w2,
        r+r, -r2, w2, // triangle 1 : end
        -r+r,r2,w2, // triangle 1 : begin
        r+r,-r2,w2, // triangle 1 : begin
        -r+r,-r2,w2, // triangle 1 : begin
        
        r+r,r2,-w2, // triangle 1 : begin
        -r+r,r2, -w2,
        r+r, -r2, -w2, // triangle 1 : end
        -r+r,r2,-w2, // triangle 1 : begin
        r+r,-r2,-w2, // triangle 1 : begin
        -r+r,-r2,-w2,
        
        r+r,r2,w2, // triangle 1 : begin
        r+r,-r2, w2,
        r+r, -r2, -w2, // triangle 1 : end
        r+r,r2,-w2, // triangle 1 : begin
        r+r,-r2,-w2, // triangle 1 : begin
        r+r,r2,w2,
 
        -r+r,r2,w2, // triangle 1 : begin
        -r+r,-r2, w2,
        -r+r, -r2, -w2, // triangle 1 : end
        -r+r,r2,-w2, // triangle 1 : begin
        -r+r,-r2,-w2, // triangle 1 : begin
        -r+r,r2,w2,       

        r+r,r2,w2, // triangle 1 : begin
        -r+r,r2, w2,
        -r+r, r2, -w2, // triangle 1 : end
        -r+r,r2,-w2, // triangle 1 : begin
        r+r,r2,-w2, // triangle 1 : begin
        r+r,r2,w2,

        r+r,-r2,w2, // triangle 1 : begin
        -r+r,-r2, w2,
        -r+r, -r2, -w2, // triangle 1 : end
        -r+r,-r2,-w2, // triangle 1 : begin
        r+r,-r2,-w2, // triangle 1 : begin
        r+r,-r2,w2  ,

        r-r,r2,w2, // triangle 1 : begin
        -r-r,r2, w2,
        r-r, -r2, w2, // triangle 1 : end
        -r-r,r2,w2, // triangle 1 : begin
        r-r,-r2,w2, // triangle 1 : begin
        -r-r,-r2,w2, // triangle 1 : begin
        
        r-r,r2,-w2, // triangle 1 : begin
        -r-r,r2, -w2,
        r-r, -r2, -w2, // triangle 1 : end
        -r-r,r2,-w2, // triangle 1 : begin
        r-r,-r2,-w2, // triangle 1 : begin
        -r-r,-r2,-w2,
        
        r-r,r2,w2, // triangle 1 : begin
        r-r,-r2, w2,
        r-r, -r2, -w2, // triangle 1 : end
        r-r,r2,-w2, // triangle 1 : begin
        r-r,-r2,-w2, // triangle 1 : begin
        r-r,r2,w2,
 
        -r-r,r2,w2, // triangle 1 : begin
        -r-r,-r2, w2,
        -r-r, -r2, -w2, // triangle 1 : end
        -r-r,r2,-w2, // triangle 1 : begin
        -r-r,-r2,-w2, // triangle 1 : begin
        -r-r,r2,w2,       

        r-r,r2,w2, // triangle 1 : begin
        -r-r,r2, w2,
        -r-r, r2, -w2, // triangle 1 : end
        -r-r,r2,-w2, // triangle 1 : begin
        r-r,r2,-w2, // triangle 1 : begin
        r-r,r2,w2,

        r-r,-r2,w2, // triangle 1 : begin
        -r-r,-r2, w2,
        -r-r, -r2, -w2, // triangle 1 : end
        -r-r,-r2,-w2, // triangle 1 : begin
        r-r,-r2,-w2, // triangle 1 : begin
        r-r,-r2,w2  ,
    };
    GLfloat body[] = {
        r,r,w, // triangle 1 : begin
        -r,r, w,
        r, -r, w, // triangle 1 : end
        -r,r,w, // triangle 1 : begin
        r,-r,w, // triangle 1 : begin
        -r,-r,w, // triangle 1 : begin
        
        r,r,-w, // triangle 1 : begin
        -r,r, -w,
        r, -r, -w, // triangle 1 : end
        -r,r,-w, // triangle 1 : begin
        r,-r,-w, // triangle 1 : begin
        -r,-r,-w,
        
        r,r,w, // triangle 1 : begin
        r,-r, w,
        r, -r, -w, // triangle 1 : end
        r,r,-w, // triangle 1 : begin
        r,-r,-w, // triangle 1 : begin
        r,r,w,
 
        -r,r,w, // triangle 1 : begin
        -r,-r, w,
        -r, -r, -w, // triangle 1 : end
        -r,r,-w, // triangle 1 : begin
        -r,-r,-w, // triangle 1 : begin
        -r,r,w,       

        r,r,w, // triangle 1 : begin
        -r,r, w,
        -r, r, -w, // triangle 1 : end
        -r,r,-w, // triangle 1 : begin
        r,r,-w, // triangle 1 : begin
        r,r,w,

        r,-r,w, // triangle 1 : begin
        -r,-r, w,
        -r, -r, -w, // triangle 1 : end
        -r,-r,-w, // triangle 1 : begin
        r,-r,-w, // triangle 1 : begin
        r,-r,w  ,

    };   

    this->object = create3DObject(GL_TRIANGLES, 36, body, c1, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 72, body2,c2, GL_FILL);
}

void Fuelup::draw(glm::mat4 VP) {

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

void Fuelup::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}        

void Fuelup::tick() {
    // this->position.x -= speed;
    // this->position.y -= speed;
}

