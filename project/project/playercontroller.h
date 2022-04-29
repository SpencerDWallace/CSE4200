#pragma once

#include "raycast.h"
#include "utilities.h"

class PlayerController{

public:
  PlayerController();

protected:

  Vector2D* MapSpace;
  Vector2D* position;
  Vector2D* nextPosition;
  Direction direction;
  Raycast* raycast;
  float moveAmount = 0.1;
 public:

  virtual Vector2D GetPosition();
  virtual Vector2D GetNextPosition();

  virtual int IndexFromPosition();

  virtual int Move();

  virtual void SetLookDirection(Direction newDirection)
  {
    direction = newDirection;
    raycast->SetLookDirection(newDirection);
  };
  
  virtual void Tick(){
    raycast->Tick();
  }

};
