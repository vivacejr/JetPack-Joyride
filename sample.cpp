#include "ball.h"
#include "main.h"

Ball::Ball(float x, float y, float r,color_t c1,color_t c2,color_t c3) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    GLfloat body[] = {
        r,r,w, // triangle 1 : begin
        r,-r,w 	,
    };

	this->obj_body = create3DObject(GL_TRIANGLES, 36, body, c1, GL_FILL);
}

void Ball::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    	glm::mat4 rotate,rotate2   ;
    	rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->obj_body);
}

void Ball::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}        

void Ball::tick() {
    // this->position.x -= speed;
    // this->position.y -= speed;
}

