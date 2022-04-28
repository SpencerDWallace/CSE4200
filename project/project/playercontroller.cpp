
#include "playercontroller.h"

PlayerController::PlayerController()
{

}

int PlayerController::IndexFromPosition()
{
  return (position->x + position->y*MapSpace->y);
}

int PlayerController::Move()
{
  switch(direction){
  case UP: MoveUp();
      break;
  case DOWN: MoveDown();
    break;
  case LEFT: MoveLeft();
    break;
  case RIGHT: MoveRight();
    break;
  default:
    break;
  }
  return IndexFromPosition();
}
