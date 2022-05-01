#include "gamecontroller.h"

GameController::GameController()
{
  gameover = false;
}

void GameController::StartGame(Vector2D* ScreenSize, int Map[], Vector2D* MapSpace){
  mapSpace = MapSpace;
  playerSnake = SpawnSnake();
  raycast = new Raycast(ScreenSize, Map, MapSpace);
//  playerSnake->position = new Vector2D(200,200);
  playerSnake->map = raycast->map;
  playerSnake->movement = new Vector2D(0,0);
  raycast->position = playerSnake->position;
  raycast->movement = playerSnake->movement;
  raycast->player = (PlayerController*)playerSnake;
  playerSnake->raycast = raycast;
  playerSnake->spawnFruit();
}

void GameController::Restart()
{
  gameover = false;
  int spawnX = 2 + (rand() %( (int)mapSpace->x - 4 ));
  int spawnY = 2 + (rand() %( (int)mapSpace->y - 4));
  Vector2D spawnPosition(spawnX, spawnY);  
  Vector2D initialMovement(0,0);
  playerSnake->Restart(spawnPosition, Direction::NONE);
  raycast->position = playerSnake->position;
  playerSnake->spawnFruit();
}

Snake* GameController::SpawnSnake(){
  int spawnX = 2 + (rand() %( (int)mapSpace->x - 4 ));
  int spawnY = 2 + (rand() %( (int)mapSpace->y - 4));
  Vector2D spawnPosition(spawnX, spawnY);
  Direction spawnDirection = playerDirection = Direction::NONE;
  return new Snake( spawnPosition, spawnDirection, mapSpace);
}

void GameController::Tick()
{
  playerSnake->Tick();
  if(playerSnake->dead)
    gameover = true;
}
