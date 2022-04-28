#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#include "index.h"

Vector2D* screenDimensions = new Vector2D(1024,512);
//-----------------------------MAP----------------------------------------------
Vector2D* mapMatrix = new Vector2D(12,12);      //map matrix x,y
const int mapS = mapMatrix->x*mapMatrix->y;      //map rectangle size

int map[] = 
  {1,1,1,1,1,1,1,1,1,1,1,1,
   1,0,0,0,0,0,0,0,0,0,0,1,
   1,0,0,0,0,0,0,0,0,0,0,1,
   1,0,0,0,0,0,0,0,0,0,0,1,
   1,0,0,0,0,0,0,0,0,0,0,1,
   1,0,0,0,0,0,0,0,0,0,0,1,
   1,0,0,0,0,0,0,0,0,0,0,1,
   1,0,0,0,0,0,0,0,0,0,0,1,
   1,0,0,0,0,0,0,0,0,0,0,1,
   1,0,0,0,0,0,0,0,0,0,0,1,
   1,0,0,0,0,0,0,0,0,0,0,1,
   1,1,1,1,1,1,1,1,1,1,1,1};

GameController* gamecontroller = new GameController();

void Tick()
{
  gamecontroller->Tick();
}

void Buttons(unsigned char key,int x,int y)
{
 // Tick();
  if(key=='a') gamecontroller->playerSnake->SetLookDirection(Direction::LEFT); 
  if(key=='d') gamecontroller->playerSnake->SetLookDirection(Direction::RIGHT); 
  if(key=='w') gamecontroller->playerSnake->SetLookDirection(Direction::UP); 
  if(key=='s') gamecontroller->playerSnake->SetLookDirection(Direction::DOWN); 
  
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
 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 Tick();
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
