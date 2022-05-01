
#include "snake.h"
#include <cstdio>
#include <math.h>

Snake::Snake()
{
  score = 0;
  dead = false;
}

Snake:: Snake(const Vector2D initialPosition, const Direction initialDirection, Vector2D* MapSize)
{
  score = 0;
  dead = false;
  position = new Vector2D(initialPosition.x, initialPosition.y);
  SnakeBody.push_back(position); direction = initialDirection; MapSpace = MapSize;

}

void Snake::Restart(const Vector2D initialPosition, const Direction initialDirection)
{
  printf("Final Score: %d\n", score);
  score = 0;
  dead = false;
  
  SnakeBody.clear();
  if(position == nullptr)
    position = new Vector2D(initialPosition.x, initialPosition.y);
  else
    *position = initialPosition;
  
  SnakeBody.push_back(position);
  *movement = Vector2D(0,0);
  direction = initialDirection;
  
}

void Snake::BodyFollow()
{
  // if(!collidedWithFruit){
     int BodyIndexClear = SnakeBody[SnakeBody.size()-1]->x + SnakeBody[SnakeBody.size()-1]->y*MapSpace->x; 
     map[BodyIndexClear] = 0;
  // }
  // collidedWithFruit = false;
  for(int i = SnakeBody.size()-1; i > 0; i--){
    *SnakeBody[i] = *SnakeBody[i-1];
    int moveSnake = SnakeBody[i]->x + SnakeBody[i]->y*MapSpace->x; 
    map[moveSnake] = 2;
  }

}

int Snake::Move()
{
  BodyFollow(); //call before updating head

  *position = GetNextPosition();
  checkSelfCollide(); 
  
  checkFruitCollide();

  map[IndexFromPosition()] = 2;

  return IndexFromPosition();
}

void Snake::AddBody()
{
  SnakeBody.push_back(new Vector2D(position->x, position->y));
}

void Snake::spawnFruit()
{
  bool fruitNotSpawned = true;
  while(fruitNotSpawned)
  {
    int spawnX = rand() % (int)MapSpace->x;
    int spawnY = rand() % (int)MapSpace->y;
    int fruitSpawnIndex = spawnX + spawnY*MapSpace->x;
    if( map[fruitSpawnIndex] == 0 )
    {
      fruitNotSpawned = false;
      map[fruitSpawnIndex] = 3;
    }
  }
}

void Snake::checkFruitCollide()
{
  if(map[IndexFromPosition()] == 3){
    spawnFruit();
    AddBody();
    score++;
  }
}

void Snake::checkSelfCollide()
{
  if(map[IndexFromPosition()] == 2)
    dead = true;
}

void Snake::Tick()
{

  //printf("made it! snake\n");
  Snake::Move();
  PlayerController::updateMovement();
  PlayerController::Tick();
  //printf("made it from pc tick\n");

  //printf("made it from snake move\n");
}

