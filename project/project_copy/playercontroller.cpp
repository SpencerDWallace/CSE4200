
#include "playercontroller.h"
#include <cstdio>

PlayerController::PlayerController()
{

}

int PlayerController::IndexFromPosition()
{
  int intX = (int)(position->x + 0.5);
  int intY = (int)(position->y + 0.5);
  int offset = (int)(MapSpace->x + 0.5);

  return (intX + intY*offset);
}

Vector2D PlayerController::GetPosition()
{
  return *position;
}

Vector2D PlayerController::GetNextPosition()
{
  if(nextPosition == nullptr)
    nextPosition = new Vector2D(position->x, position->y);
  else
    *nextPosition = *position;

  switch(direction)
    {
    case UP: nextPosition->MoveUp(MapSpace, moveAmount);
      break;
    case DOWN: nextPosition->MoveDown(MapSpace, moveAmount);
      break;
    case LEFT: nextPosition->MoveLeft(MapSpace, moveAmount);
      break;
    case RIGHT: nextPosition->MoveRight(MapSpace, moveAmount);
      break;
    default: 
      break;
    }
  //  printf("X is: %f | Y is: %f\n", nextPosition->x, nextPosition->y);
  return *nextPosition;
}

int PlayerController::Move()
{
  *position = GetNextPosition();
  return IndexFromPosition();
}

void PlayerController::lookUp(){
  movement->SetPosition(0,-1);
}

void PlayerController::lookDown(){
  movement->SetPosition(0,1);
}

void PlayerController::lookLeft(){
  movement->SetPosition(-1,0);
}

void PlayerController::lookRight(){
  movement->SetPosition(1,0);
}

void PlayerController::updateMovement(){
  switch(direction){
  case UP: lookUp();
    break;
  case DOWN: lookDown();
    break;
  case LEFT: lookLeft();
    break;
  case RIGHT: lookRight();
    break;
  default: break;
  }
}
