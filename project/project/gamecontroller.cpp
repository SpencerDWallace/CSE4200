#include "gamecontroller.h"

GameController::GameController()
{

}

void GameController::StartGame(Vector2D* ScreenSize, int Map[], Vector2D* MapSpace){
  mapSpace = MapSpace;
  playerSnake = SpawnSnake();
  raycast = new Raycast(ScreenSize, Map, MapSpace);
  playerSnake->position = new Vector2D(10,10);
  raycast->position = playerSnake->position;
  raycast->movement = new Vector2D(0,0);
  raycast->player = (PlayerController*)playerSnake;
  playerSnake->raycast = raycast;
}

Snake* GameController::SpawnSnake(){
  int spawnX = rand() % (int)mapSpace->x;
  int spawnY = rand() % (int)mapSpace->y;
  Vector2D spawnPosition(spawnX, spawnY);
  Direction spawnDirection = playerDirection = Direction::NONE;
  return new Snake(spawnPosition, spawnDirection, mapSpace);
}

void GameController::Tick()
{
  //printf("made it! gc\n");
  //raycast->Tick();
  //printf("returned from raycast tick\n");
  playerSnake->Tick();
}
