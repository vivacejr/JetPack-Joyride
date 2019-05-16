#include "main.h"
#include "timer.h"
#include "ball.h"
#include "water.h"
#include "ring.h"
#include "bar.h"
#include "volcano.h"
#include "speedbar.h"
#include "fuelup.h"
#include "power.h"
#include "rocket.h"
#include "canon.h"
#include "canonfire.h"
#include "arrow.h"

GLMatrices Matrices,Ortho;
GLuint     programID;
GLFWwindow *window;

glm::mat4 globalrot;

/**************************
* Customizable functions *
**************************/
ld gspeed=0.4;
trunaCam Vcam,Vcam2;
Ball ball1;
Water water;
Bar fuelbar,altitudebar,health;
Speedbar speedbar;
Arrow aro;

Power powerset[1000];
Rocket rocketset[1000];
Canonfire canonset[1000];

ll power_index=0;
ll rocket_index=0;
ll canon_index=0;
ld canon_timer=10;
ld shield=10;
vector<Volcano> vol;
vpll vvol;
vector<Canon> can;
vpll vcan;
vector<Ring> rg;
vpll vrg;
vector<Fuelup> fup;
vpll vfup;
ll c=1,cur=0;
ld barrel=0,twist=0,loop=0;
float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0;

Timer t60(1.0 / 60);

void keyboard(GLFWwindow *window, int key, int scancode, int action, int mods) {
    // Function is called first on GLFW_PRESS.

    if (action == GLFW_RELEASE) 
    {
        if(key==GLFW_KEY_C)
        {
            c++;
            c%=5;
        }
        if(key==GLFW_KEY_SPACE)
        {
            if(power_index<1000)
            {
                Power p;
                p = Power(ball1.position.x,ball1.position.y,ball1.position.z,(float)0.2,power_index,COLOR_DARKBLUE);
                powerset[power_index++]=p;
            }
        }
        if(key==GLFW_KEY_R)
        {
            if(rocket_index<1000)
            {
                Rocket p;
                p = Rocket(ball1.position.x,ball1.position.y,ball1.position.z,(float)0.2,power_index,COLOR_DARKBLUE);
                p.rotx=globalrot[2][0];
                p.roty=globalrot[2][1];
                p.rotz=globalrot[2][2];
                rocketset[rocket_index++]=p;
            }
        }
    } 
    else if (action == GLFW_PRESS)
    {
        switch (key) {
        case GLFW_KEY_ESCAPE:
            quit(window);
            break;
        default:
            break;
        }
    }
}
void draw() {
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram (programID);

    if(c==0)
    {        
        // plane view
        Vcam.eye = glm::vec3(ball1.position.x,ball1.position.y+0.3,ball1.position.z+1);
        Vcam.target = glm::vec3(ball1.position.x,ball1.position.y,ball1.position.z+2);
        Vcam.target.x += 2.0*sin(ball1.rotation1 * M_PI / 180.0f);
        Vcam.target.z -= 2.0-2*cos(ball1.rotation1 * M_PI / 180.0f);
        Vcam.eye.x += sin(ball1.rotation1 * M_PI / 180.0f);
        Vcam.eye.z -= 1.0-cos(ball1.rotation1 * M_PI / 180.0f);
        Vcam.up = glm::vec3(0,1,0);
    }
    else if(c==1)
    {
        Vcam.eye = glm::vec3(ball1.position.x,ball1.position.y+2,ball1.position.z-2);
        Vcam.target = glm::vec3(ball1.position.x,ball1.position.y,ball1.position.z);
        Vcam.eye.x += -sin(ball1.rotation1 * M_PI / 180.0f);
        Vcam.eye.z += 1.0-cos(ball1.rotation1 * M_PI / 180.0f);
        Vcam.up = glm::vec3(0,1,0);
    }
    else if(c==2)
    {
    	//followcam
    	Vcam.eye.x =  ball1.position.x - 5*globalrot[2][0]+2*globalrot[1][0];
    	Vcam.eye.y =  ball1.position.y - 5*globalrot[2][1]+2*globalrot[1][1];
    	Vcam.eye.z =  ball1.position.z - 5*globalrot[2][2]+2*globalrot[1][2];
    	Vcam.up.x=globalrot[1][0];
    	Vcam.up.y=globalrot[1][1];
    	Vcam.up.z=globalrot[1][2];
        Vcam.target = glm::vec3(ball1.position.x,ball1.position.y,ball1.position.z);
    	
    }
    else if(c==3)
    {
        //top down
        Vcam.eye = glm::vec3(ball1.position.x,100+ball1.position.y,ball1.position.z);
        Vcam.target = glm::vec3(ball1.position.x,ball1.position.y,ball1.position.z);
        Vcam.up = glm::vec3(0,0,1);
    }
    else
    {
        Vcam.eye = glm::vec3(-100,100,0);
        Vcam.target = glm::vec3(0,0,0);
        Vcam.up = glm::vec3(0,0,1);	
    }
    Matrices.view = glm::lookAt( Vcam.eye, Vcam.target, Vcam.up ); // Rotating Camera for 3D
    glm::mat4 VP = Matrices.projection * Matrices.view;
    glm::mat4 MVP;  // MVP = Projection * View * Model
   

    Vcam2.eye = glm::vec3(0,0,1);
    Vcam2.target = glm::vec3(0,0,0);
    Vcam2.up = glm::vec3(0,1,0);
    Ortho.view = glm::lookAt( Vcam2.eye, Vcam2.target, Vcam2.up ); // Rotating Camera for 3D
    glm::mat4 VP2 = Ortho.projection * Ortho.view;
    glm::mat4 MVP2;  // MVP = Projection * View * Model
   
    lp(i,0,power_index)
    {
        if(powerset[i].erase==0)
             powerset[i].draw(VP);
    }
    lp(i,0,rocket_index)
    {
        if(rocketset[i].erase==0)
        {
        	rocketset[i].speed=gspeed;
             rocketset[i].draw(VP);
    	}
    }
    lp(i,0,canon_index)
    {
        if(canonset[i].erase==0)
             canonset[i].draw(VP);
    }
    ball1.draw(VP);
    water.draw(VP);
    aro.draw(VP);
    lp(i,0,rg.size())
   	{
    	rg[i].draw(VP);
    }
    lp(i,0,vol.size())
    {
    	vol[i].draw(VP);
    }
    lp(i,0,fup.size())
    {
    	if(fup[i].erase==0)
   			fup[i].draw(VP);
    }
    lp(i,0,can.size())
    {
    	if(can[i].erase==0)
    		can[i].draw(VP);
    }
    fuelbar.draw(VP2);
    altitudebar.draw(VP2);
    speedbar.draw(VP2);
    health.draw(VP2);
}

void tick_input(GLFWwindow *window) {

    int left  = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int up  = glfwGetKey(window, GLFW_KEY_UP);
    int down = glfwGetKey(window, GLFW_KEY_DOWN);
    int Q = glfwGetKey(window, GLFW_KEY_Q);
    int E = glfwGetKey(window, GLFW_KEY_E);
    int W = glfwGetKey(window, GLFW_KEY_W);
    int S = glfwGetKey(window, GLFW_KEY_S);
    int B = glfwGetKey(window, GLFW_KEY_B);
    int N = glfwGetKey(window, GLFW_KEY_N);
    int M = glfwGetKey(window, GLFW_KEY_M);
    if (left) 
    {
        ball1.rotation1+=2;
    }
    if(right)
    {
        ball1.rotation1-=2;
    }
    if (up) 
    {
        ball1.rotation3-=2;
    }
    if(down)
    {
        ball1.rotation3+=2;
    }
    if(E)
    {
        ball1.rotation2+=2;
    }
    if(Q)
    {	
        ball1.rotation2-=2;
    }
    if(W)
    {
    	gspeed+=0.03;
        speedbar.rotation+=1;
        ball1.speed +=0.03;
    }
    if(S)
    {
    	gspeed-=0.03;
        speedbar.rotation-=1;
        ball1.speed -=0.03;
    }
    if(B&M&&barrel==0)
    {
    	barrel=360;
    }
    if(barrel>0)
    {
    	barrel-=5;
        // ball1.rotation1+=10;
       	ball1.rotation3-=5;
    }
    if(N&M&&twist==0)
    {
    	twist=360;
    }
    if(twist>0)
    {
    	twist-=5;
        // ball1.rotation1+=10;
       	ball1.rotation2-=5;
    }
    if(N&B&&loop==0)
    {
    	loop=360;
    }
    if(loop>0)
    {
    	loop-=5;
        // ball1.rotation1+=10;
       	ball1.rotation1-=5;
    }
    fuelbar.fuel-=ball1.speed/5000.0;
    altitudebar.fuel=(ball1.position.y+10)/100.0;

    ball1.position.x += ball1.speed * globalrot[2][0];
    ball1.position.y += ball1.speed * globalrot[2][1];
    ball1.position.z += ball1.speed * globalrot[2][2];
}

void tick_elements() {
	shield-=0.1;
	if(shield<=0)shield=0;
    ball1.tick();
    lp(i,0,power_index)
    {
        powerset[i].tick();
        ld r=can[cur].side;
        ld x=can[cur].position.x;
	    ld y=can[cur].position.y;
	    ld z=can[cur].position.z;
	    ld x1=x-r;
	    ld x2=x+r;
	    ld z1=z-r;
	    ld z2=z+r;
	    ld y1=y-r;
	    ld y2=y+r;
	    ld px=powerset[i].position.x;
	    ld py=powerset[i].position.y;
	    ld pz=powerset[i].position.z;
    	if(px>=x1&&px<=x2&&pz>=z1&&pz<=z2&&py>=y1&&py<=y2)
    	{
    		can[cur].erase=1;
    		cur++;
    	}
    }    
    lp(i,0,rocket_index)
    {
        rocketset[i].tick();
        ld r=can[cur].side;
		ld x=can[cur].position.x;
	    ld y=can[cur].position.y;
	    ld z=can[cur].position.z;
	    ld x1=x-r;
	    ld x2=x+r;
	    ld z1=z-r;
	    ld z2=z+r;
	    ld y1=y-r;
	    ld y2=y+r;
	    ld px=rocketset[i].position.x;
	    ld py=rocketset[i].position.y;
	    ld pz=rocketset[i].position.z;
    	if(px>=x1&&px<=x2&&pz>=z1&&pz<=z2&&py>=y1&&py<=y2)
    	{
    		can[cur].erase=1;
    		cur++;
    	}
    }
    lp(i,0,fup.size())
    {
    	if(fup[i].erase==1)continue;
        ld r=fup[i].length;
        ld l=fup[i].width;
		ld x=fup[i].position.x;
	    ld y=fup[i].position.y;
	    ld z=fup[i].position.z;
	    ld x1=x-r;
	    ld x2=x+r;
	    ld z1=z-l;
	    ld z2=z+l;
	    ld y1=y-r;
	    ld y2=y+r;
	    ld px=ball1.position.x;
	    ld py=ball1.position.y;
	    ld pz=ball1.position.z;
    	if(px>=x1&&px<=x2&&pz>=z1&&pz<=z2&&py>=y1&&py<=y2)
    	{
    		fup[i].erase=1;
    		fuelbar.fuel+=0.1;
    	}    	
	    canonset[i].tick();

    }
    ld s=can[cur].side;
    ld x=can[cur].position.x+s;
    ld y=can[cur].position.y+s;
    ld z=can[cur].position.z+s;
   	ld bx=ball1.position.x-x;
    ld by=ball1.position.y-y;
    ld bz=ball1.position.z-z;
    ld det=sqrt(bx*bx+by*by+bz*bz);
    bx/=det;
    by/=det;
    bz/=det;
    canon_timer -=0.1;
    if(canon_timer<=0)
    {
    	canon_timer=10;
	   	Canonfire c = Canonfire(x,y,z,0.1,canon_index,COLOR_BLACK);  
	    c.ux=bx/10.0;
	    c.uy=by/10.0;
	    c.uz=bz/10.0;
	    canonset[canon_index]=c;
	    canon_index++;
    }
    lp(i,0,canon_index)
    {
        ld r=ball1.radius;
        ld l=ball1.body_length/2.0;
		ld x=ball1.position.x;
	    ld y=ball1.position.y;
	    ld z=ball1.position.z;
	    ld x1=x-r;
	    ld x2=x+r;
	    ld z1=z-l;
	    ld z2=z+l;
	    ld y1=y-r;
	    ld y2=y+r;
	    ld px=canonset[i].position.x;
	    ld py=canonset[i].position.y;
	    ld pz=canonset[i].position.z;
    	if(shield<=0&&px>=x1&&px<=x2&&pz>=z1&&pz<=z2&&py>=y1&&py<=y2)
    	{
    		shield=10;
    		health.fuel-=0.1;
    	}    	
	    canonset[i].tick();
    }
    lp(i,0,vol.size())
    {
    	ld x=vol[i].position.x;
    	ld z=vol[i].position.z;
    	ld r=vol[i].radius;
    	ld x1=x-r;
    	ld x2=x+r;
    	ld z1=z-r;
    	ld z2=z+r;
    	ld px=ball1.position.x;
    	ld pz=ball1.position.z;
    	if(shield<=0&&px>=x1&&px<=x2&&pz>=z1&&pz<=z2)
    	{
    		shield=10;
    		health.fuel-=0.1;
    	}
    }

    aro.position.x=can[cur].position.x;
    aro.position.z=can[cur].position.z;
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models
    ball1 = Ball(0, 0,0.2, COLOR_YELLOW,COLOR_BLUE,COLOR_RED);
    water = Water(0, -10,0,1000,40,COLOR_SKY);
    lp(i,0,vrg.size())
    {
    	rg.pb(Ring(vrg[i].ff, 0,vrg[i].ss,2,COLOR_RED));
    }
    altitudebar = Bar(-3,-2.5,0,1.5,0.3,COLOR_DARKSKY);
    speedbar = Speedbar(3,-2.5,0,0.7,0.05,COLOR_RED);
    fuelbar = Bar(-3.5, -2.5,0,1.5,0.3,COLOR_ORANGE);
    health = Bar(-2.5, -2.5	,0,1.5,0.3,COLOR_GREEN);
    aro = Arrow(vcan[0].ff, 3,vcan[0].ss,0.5,2,COLOR_RED);
    lp(i,0,vvol.size())
    {
    	vol.pb(Volcano(vvol[i].ff,-9.999,vvol[i].ss,3,7,COLOR_ORANGE));
    }
    lp(i,0,vfup.size())
    {
    	fup.pb(Fuelup(vfup[i].ff, 0,vfup[i].ss,0.4,0.4,COLOR_BLUE,COLOR_BYELLOW));
    }
    lp(i,0,vcan.size())
    {
    	can.pb(Canon(vcan[i].ff, -6.88,vcan[i].ss,2,2,COLOR_BROWN,COLOR_BYELLOW));
    }
    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}


int main(int argc, char **argv) {
    srand(time(0));
    int width  = 1900;
    int height = 1040;
    lp(i,0,10)
    {
    	lp(j,0,10)
    	{
    		vvol.pb(mp(i*100-500,j*100-500));
    	}
    }
    vcan.pb(mp(0,50));
    vcan.pb(mp(0,200));
    vcan.pb(mp(300,200));
    vcan.pb(mp(-300,200));
    vcan.pb(mp(-200,300));
    vcan.pb(mp(0,500));
    lp(i,0,10)
    {
    	lp(j,0,10)
    	{
    		vrg.pb(mp(i*70-350,j*70-350));
    	}
    }
    lp(i,0,10)
    {
    	lp(j,0,10)
    	{
    		vfup.pb(mp(i*80-400,j*80-400));
    	}
    }
    window = initGLFW(width, height);

    initGL (window, width, height);

    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers
   	    if(health.fuel<=0||altitudebar.fuel<=0||fuelbar.fuel<=0)
	    {
    		break;
    	}

        if (t60.processTick()) {
            // 60 fps
            // OpenGL Draw commands
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

            tick_elements();
            tick_input(window);
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
    return (abs(a.x - b.x) * 2 < (a.width + b.width)) &&
           (abs(a.y - b.y) * 2 < (a.height + b.height));
}

void reset_screen() {
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
    Matrices.projection = glm::perspective(60.0f*M_PI/100, (double)1,0.1,(double)10000.0);
    Ortho.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
}
