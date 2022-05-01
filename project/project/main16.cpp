#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#include "index.h"
#include <chrono>
Vector2D* screenDimensions = new Vector2D(1024,512);
//-----------------------------MAP----------------------------------------------
Vector2D* mapMatrix = new Vector2D(16,16);      //map matrix x,y
const int mapS = mapMatrix->x*mapMatrix->y;      //map rectangle size

int map[] = 
  { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};

GameController* gamecontroller = new GameController();


double GetCurrentTime()
{
 using Duration = std::chrono::duration<double>;
 return std::chrono::duration_cast<Duration>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
}

const double frame_delay = 1.0 / 2.0; // 60 FPS
double last_render = 0;

void OnIdle()
{

}


void Tick()
{
  glutPostRedisplay();
}

void Buttons(unsigned char key,int x,int y)
{
  
  if(key=='a')
    {
       gamecontroller->playerSnake->SetLookDirection(Direction::LEFT); 
    }
  if(key=='d') 
    {
       gamecontroller->playerSnake->SetLookDirection(Direction::RIGHT); 
    }
  if(key=='w') 
    {
       gamecontroller->playerSnake->SetLookDirection(Direction::UP); 
    }
  if(key=='s') 
    {
       gamecontroller->playerSnake->SetLookDirection(Direction::DOWN); 
    }
  
  glutPostRedisplay();
}

void init()
{
 glClearColor(0.3, 0.3, 0.3, 0);
 gluOrtho2D(0, screenDimensions->x, screenDimensions->y, 0);
 // px=150; py=400; pa=90;
 // pdx=cos(degToRad(pa)); pdy=-sin(degToRad(pa));
}

void display()
{
  
  const double current_time = GetCurrentTime();
  if( ( current_time - last_render ) < frame_delay )
    return;

  last_render = current_time;
  
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  gamecontroller->Tick();
  //drawMap2D();
  //drawPlayer2D();
  //drawRays2D();
  glutSwapBuffers();
}

int main(int argc, char* argv[])
{
  gamecontroller->StartGame(screenDimensions, map, mapMatrix);
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(screenDimensions->x, screenDimensions->y);
  glutCreateWindow("3D snake");
  init();
  glutDisplayFunc(display);
  glutIdleFunc(Tick);
  glutKeyboardFunc(Buttons);
  glutMainLoop();
}
