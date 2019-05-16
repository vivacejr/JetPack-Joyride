#include "ball.h"
#include "main.h"

Ball::Ball(float x, float y, float r,color_t c1,color_t c2,color_t c3) {
    this->position = glm::vec3(x, y, 0);
    this->rotation_flag=0;
    // this->speed = g_speed;
    this->radius = r;
    this->dir=-1;
    this->col_body=c1;
    this->col_upperwing=c2;
    this->col_lowerwing=c3;
    this->wing_width=0.2;
    this->wing_height=0.2;
    this->wing_length=1;
    this->body_length=2;
    this->speed=0.1;
    // Our vertices. Three consecutive floats give a 3D body; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    // GLfloat vertex_buffer_data;
    double n=100,pi=3.1415926;
    // cin >> n;
    GLfloat upper_wing[1000],lower_wing[1000];
    ll cnt=0,n1=n;
    float w=body_length/2.0;
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
        r,-r,w 	,
    };

	this->obj_body = create3DObject(GL_TRIANGLES, 36, body, c1, GL_FILL);
    lp(i,0,20)
    {
        upper_wing[9*i]=r;
        upper_wing[9*i+1]=wing_height*(i+1)/20.0;
        upper_wing[9*i+2]=wing_width;
        upper_wing[9*i+3]=r;
        upper_wing[9*i+4]=wing_height*(i+1)/20.0;
        upper_wing[9*i+5]=-wing_width;
        upper_wing[9*i+6]=r+wing_length;
        upper_wing[9*i+7]=wing_height*(i+1)/20.0;
        upper_wing[9*i+8]=0;
    }
    lp(i,20,40)
    {
        upper_wing[9*i]=-r;
        upper_wing[9*i+1]=wing_height*(i+1-20)/20.0;
        upper_wing[9*i+2]=wing_width;
        upper_wing[9*i+3]=-r;
        upper_wing[9*i+4]=wing_height*(i+1-20)/20.0;
        upper_wing[9*i+5]=-wing_width;
        upper_wing[9*i+6]=-r-wing_length;
        upper_wing[9*i+7]=wing_height*(i+1-20)/20.0;
        upper_wing[9*i+8]=0;
    }

    this->obj_upperwing= create3DObject(GL_TRIANGLES, 40*3, upper_wing, c2, GL_FILL);
    lp(i,0,20)
    {
        lower_wing[9*i]=r;
        lower_wing[9*i+1]=-wing_height*(i)/20.0;
        lower_wing[9*i+2]=wing_width;
        lower_wing[9*i+3]=r;
        lower_wing[9*i+4]=-wing_height*(i)/20.0;
        lower_wing[9*i+5]=-wing_width;
        lower_wing[9*i+6]=r+wing_length;
        lower_wing[9*i+7]=-wing_height*(i)/20.0;
        lower_wing[9*i+8]=0;
    }
    lp(i,20,40)
    {
        lower_wing[9*i]=-r;
        lower_wing[9*i+1]=-wing_height*(i-20)/20.0;
        lower_wing[9*i+2]=wing_width;
        lower_wing[9*i+3]=-r;
        lower_wing[9*i+4]=-wing_height*(i-20)/20.0;
        lower_wing[9*i+5]=-wing_width;
        lower_wing[9*i+6]=-r-wing_length;
        lower_wing[9*i+7]=-wing_height*(i-20)/20.0;
        lower_wing[9*i+8]=0;
    }
    this->obj_lowerwing= create3DObject(GL_TRIANGLES, 40*3, lower_wing, c3, GL_FILL);
}

void Ball::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    	glm::mat4 rotate1,rotate2,rotate3   ;

        rotate1    = glm::rotate((float) (this->rotation1 * M_PI / 180.0f), glm::vec3(0, 1, 0));
        rotate2    = glm::rotate((float) (this->rotation2 * M_PI / 180.0f), glm::vec3(0, 0, 1));
        rotate3    = glm::rotate((float) (this->rotation3 * M_PI / 180.0f), glm::vec3(1, 0, 0));
        // cout<<rotation<<" "<<rotation2<<endl;
        this->rotation1 =0;
        this->rotation2 =0;
        this->rotation3 =0;

        globalrot *= rotate1*rotate2*rotate3;

    Matrices.model *= (translate * globalrot);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->obj_body);
    draw3DObject(this->obj_lowerwing);
    draw3DObject(this->obj_upperwing);
}

void Ball::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}        

void Ball::tick() {
    // this->position.x -= speed;
    // this->position.y -= speed;
}

    
void Ball::move_right() {
    // this->position.x += move_size;
}
void Ball::move_left() {
    // this->position.x -= move_size;
}
