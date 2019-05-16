#include "power.h"
// #include "main.h"

Power::Power(float x, float y,float z,float w,ll i,color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->speed = g_speed;
    this->radius = w;
    this->erase=0;
    this->index=i;
    this->verspeed=0.1;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    // GLfloat vertex_buffer_data;
    double sz=1000,r=w,pi=3.1415926;
    // cin >> n;
    GLfloat vertex_buffer_data[9*(ll)sz];
    ld c1=0.0,c2=0.0;
    ld p1=w,p2=0;
    lp(i,0,sz)
    {
        vertex_buffer_data[9*i]=c1;   
        vertex_buffer_data[9*i+1]=0.0;    
        vertex_buffer_data[9*i+2]=c2; 
        vertex_buffer_data[9*i+3]=p1; 
        vertex_buffer_data[9*i+4]=0.0;    
        vertex_buffer_data[9*i+5]=p2; 
        vertex_buffer_data[9*i+6]=(float)(r * cos(2*pi*(i+1)/sz)); 
        vertex_buffer_data[9*i+7]=0.0;    
        vertex_buffer_data[9*i+8]=(float)(r * sin(2*pi*(i+1)/sz)); 
        p1=(float)(r * cos(2*pi*(i+1)/sz));
        p2=(float)(r * sin(2*pi*(i+1)/sz));
    } 
    this->object = create3DObject(GL_TRIANGLES, 3*sz, vertex_buffer_data, color, GL_FILL);
}


void Power::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}


bool Power::tick() {
    this->position.y -= this->verspeed;
    if(this->position.y<=-10)this->erase=1;
}

bool Power::collision(pt a,pt b,pt c) {
}