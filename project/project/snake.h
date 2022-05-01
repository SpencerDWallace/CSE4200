#pragma once

#include <vector>
#include "utilities.h"
#include "playercontroller.h"

class GameController;

class Snake: public PlayerController{
  friend class GameController;

public:
  Snake();

  Snake(const Vector2D initialPosition, const Direction initialDirection, Vector2D* MapSize);
  std::vector<Vector2D*> SnakeBody;

protected:
  int* map;
  int score;	
  bool dead;
  
public:

  int GetScore() {return score;};
  void IncreaseScore() {score++;};
  void ResetScore() {score = 0;};
 
  virtual int Move() override;
    
protected:
  void checkFruitCollide();
  void checkSelfCollide();
  void spawnFruit();
  void BodyFollow();
  void AddBody();
  void Tick();
  void Restart(const Vector2D intialPosition, const Direction initialDirection);

};
