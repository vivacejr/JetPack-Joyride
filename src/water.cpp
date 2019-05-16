#include "water.h"
#include "main.h"

Water::Water(float x, float y,float z,float t,float a,color_t c) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->total=t;
    this->side=a;
    GLfloat body[100000];
    ll n=t/a;
    ll cnt=0;
    ld z1=t/2;
    lp(i,0,n)
    {
        ld x=-t/2;
        lp(j,0,n)
        {
             if((i+j)%2==0)
             {
                body[cnt++]=x;                  
                body[cnt++]=0;                
                body[cnt++]=z1;                  
                body[cnt++]=x+a;                  
                body[cnt++]=0;                
                body[cnt++]=z1;  
                body[cnt++]=x+a;                  
                body[cnt++]=0;                
                body[cnt++]=z1-a;  
                body[cnt++]=x;                  
                body[cnt++]=0;                
                body[cnt++]=z1;  
                body[cnt++]=x;                  
                body[cnt++]=0;                
                body[cnt++]=z1-a;  
                body[cnt++]=x+a;                  
                body[cnt++]=0;                
                body[cnt++]=z1-a;  

             }   
             x+=a;
        }
        z1-=a;
    } 

	this->object = create3DObject(GL_TRIANGLES, cnt/3, body, c, GL_FILL);
}

void Water::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    	glm::mat4 rotate,rotate2   ;
    	rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Water::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}        

void Water::tick() {
    // this->position.x -= speed;
    // this->position.y -= speed;
}

