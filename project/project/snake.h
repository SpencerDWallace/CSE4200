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
  std::vector<Vector2D> body;

protected:
  int score;	

public:

  int GetScore() {return score;};
  void IncreaseScore() {score++;};
  void ResetScore() {score = 0;};
 
  virtual int Move() override;
    
protected:
  void BodyFollow();
  void Tick();
  
};
