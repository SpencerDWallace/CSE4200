#pragma once

#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#include "utilities.h"

class Raycast{
public:

  Raycast();
  Raycast(Vector2D* ScreenSize, int Map[], Vector2D* MapSpace);
    
//protected:

  Vector2D* position;
  Vector2D* movement;
  float lookAngle;
  Vector2D* screenSize;
  Vector2D* mapSpace;
  int mapS;
  int* map; //map array for drawing 3D map
  Direction lookDirection;

public:

  //call SetLookDirection prior to tick in order for raycast to update correctly
  void Tick();

  void updateMovement();

  void lookUp(){
    movement->SetPosition(0,-1);
  };

  void lookDown(){
    movement->SetPosition(0,1);
  };

  void lookLeft(){
    movement->SetPosition(-1,0);
  };

  void lookRight(){
    movement->SetPosition(1,0);
  };
  
  void SetLookDirection(Direction newLookDirection) {
    lookDirection = newLookDirection;
    updateMovement();
  };

  void drawMap2D();

  //------------------------PLAYER------------------------------------------------
  void drawPlayer2D();
  
  //---------------------------Draw Rays and Walls--------------------------------
  void drawRays2D();

protected:
  virtual float degToRad(int a) { return a*M_PI/180.0;};
  virtual int FixAng(int a){ if(a>359){ a-=360;} if(a<0){ a+=360;} return a;};

};
