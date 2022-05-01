#pragma once

#include "snake.h"
#include "raycast.h"
#include "playercontroller.h"
#include "utilities.h"
#include <math.h>
#include <cstdio>

//class MainFunction;

class GameController{

  //friend class MainFunction; // give MainFunction access to protected variables because only MainFunction should interect with GameController
  
public:
  GameController();
  //  GameController(Vector2D &ScreenSize, int Map[], Vector2D &MapSpace)
  
//protected:
  Vector2D* mapSpace;
  Snake* playerSnake;
  Direction playerDirection;
  Raycast* raycast;
  bool gameover;
  
public:

  void StartGame(Vector2D* ScreenSize, int Map[], Vector2D* MapSpace);
  
  Snake* SpawnSnake();

  void SpawnFruit();

  void Tick();

  void Restart();
};
