
#include "playercontroller.h"
#include <cstdio>

PlayerController::PlayerController()
{

}

int PlayerController::IndexFromPosition()
{
  return (position->x + position->y*MapSpace->y);
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
    case UP: printf("nextpos up\n");nextPosition->MoveUp(MapSpace, moveAmount);
      break;
    case DOWN: printf("nextpos down\n");nextPosition->MoveDown(MapSpace, moveAmount);
      break;
    case LEFT: printf("nextpos left\n");nextPosition->MoveLeft(MapSpace, moveAmount);
      break;
    case RIGHT: printf("nextpos right\n");nextPosition->MoveRight(MapSpace, moveAmount);
      break;
    default: printf("nextpos default\n");
      break;
    }
  printf("X is: %f | Y is: %f\n", nextPosition->x, nextPosition->y);
  return *nextPosition;
}

int PlayerController::Move()
{
  *position = GetNextPosition();
  return IndexFromPosition();
}
