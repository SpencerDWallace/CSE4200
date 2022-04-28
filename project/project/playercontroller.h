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
  
 public:

  virtual int IndexFromPosition();

  virtual int Move();

  virtual void SetLookDirection(Direction newDirection){direction = newDirection;};
  
  virtual void MoveUp(){
    position->SetPosition(position->x,(position->y - 1)%MapSpace->y );
  };
  virtual void MoveDown(){
    position->SetPosition(position->x,(position->y + 1)%MapSpace->y );
  };
  virtual void MoveLeft(){
    position->SetPosition( (position->x - 1)%MapSpace->x, position->y );
  };
  virtual void MoveRight(){
    position->SetPosition( (position->x + 1)%MapSpace->x, position->y );
  };

  virtual void Tick(){
    raycast->Tick();
  }

};
