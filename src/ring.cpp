#include "ring.h"
// #include "main.h"

const float move_size = 0.05,jump_size=0.5;    
Ring::Ring(float x, float y,float z,float w,color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->speed = g_speed;
    this->radius = w;
    this->dir=-1;
    this->display=0;
    this->erase=0;
    double n=100,x1=w,y1=w+0.1,pi=3.1415926;
    GLfloat vertex_buffer_data[180000];
    pi*=2.0;
    ll cnt=0;
    ld yc=0;
    lp(i,0,30)
    {
        lp(i,0,n)
        {
            cnt+=18;
            vertex_buffer_data[18*i+0]=x1*sin(pi/2+(i-1)*pi/n);   
            vertex_buffer_data[18*i+1]=x1*cos(pi/2+(i-1)*pi/n); 
            vertex_buffer_data[18*i+2]=yc;    
            vertex_buffer_data[18*i+3]=y1*sin(pi/2+(i-1)*pi/n); 
            vertex_buffer_data[18*i+4]=y1*cos(pi/2+(i-1)*pi/n); 
            vertex_buffer_data[18*i+5]=yc;    
            vertex_buffer_data[18*i+6]=x1*sin(pi/2+(i)*pi/n); 
            vertex_buffer_data[18*i+7]=x1*cos(pi/2+(i)*pi/n); 
            vertex_buffer_data[18*i+8]=yc;    
            vertex_buffer_data[18*i+9]=x1*sin(pi/2+(i)*pi/n);    
            vertex_buffer_data[18*i+10]=x1*cos(pi/2+(i)*pi/n);    
            vertex_buffer_data[18*i+11]=yc;    
            vertex_buffer_data[18*i+12]=y1*sin(pi/2+(i-1)*pi/n);    
            vertex_buffer_data[18*i+13]=y1*cos(pi/2+(i-1)*pi/n);    
            vertex_buffer_data[18*i+14]=yc;    
            vertex_buffer_data[18*i+15]=y1*sin(pi/2+(i)*pi/n);    
            vertex_buffer_data[18*i+16]=y1*cos(pi/2+(i)*pi/n);    
            vertex_buffer_data[18*i+17]=yc;    
        }
        yc+=0.1;
    } 
    this->object = create3DObject(GL_TRIANGLES, cnt/3, vertex_buffer_data, color, GL_FILL);
}

void Ring::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Ring::tick() 
{
}
bool Ring::collision(pt a,pt b,pt c) 
{
}
