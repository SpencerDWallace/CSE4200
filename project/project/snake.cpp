
#include "snake.h"
#include <cstdio>

Snake::Snake()
{
  score = 0;
}

Snake::Snake(const Vector2D initialPosition, const Direction initialDirection, Vector2D* MapSize)
{
  score = 0;
  body.push_back(initialPosition); direction = initialDirection; MapSpace = MapSize;
}

void Snake::BodyFollow()
{
  for(int i = body.size()-1; i > 0; i--)
    body[i] = body[i-1];
}

int Snake::Move()
{
  BodyFollow(); //call before updating head
  //  printf("made it from bodyfollow\n");
  return PlayerController::Move();
}

void Snake::Tick()
{

  //printf("made it! snake\n");
  PlayerController::Tick();
  //printf("made it from pc tick\n");
  Snake::Move();
  //printf("made it from snake move\n");
}

