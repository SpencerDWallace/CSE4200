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
  Vector2D* movement;
  Direction direction;
  Raycast* raycast;
  float moveAmount = 1;
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

  virtual void updateMovement();
  
  virtual void lookUp();
  
  virtual void lookDown();
  
  virtual void lookLeft();
  
  virtual void lookRight();
  
  virtual void Tick(){

    raycast->Tick();
  }

};
