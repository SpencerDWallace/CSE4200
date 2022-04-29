#pragma once

#include <cstdio>

enum Direction {UP,DOWN,LEFT,RIGHT,NONE};

struct Vector2D{
  float x;
  float y;
  Vector2D();
  Vector2D(float X, float Y){x = X, y = Y;};
  void SetPosition(const float& X, const float& Y){this->x = X, this->y = Y;};
  void MoveUp(Vector2D* MapSpace, float moveAmount){
    this->SetPosition(this->x, this->y - moveAmount);
    printf("x is: %f | y is: %f\n", this->x, this->y);
    if(this->y < 0)
      this->y = MapSpace->y;
    //this->SetPosition(this->x, (int)(this->y - moveAmount)%(int)MapSpace->y );
  };
  void MoveDown(Vector2D* MapSpace, float moveAmount){
    this->SetPosition(this->x, this->y + moveAmount);
    printf("x is: %f | y is: %f\n", this->x, this->y);
    if(this->y > MapSpace->y)
      this->y = 0;
    //this->SetPosition(this->x, (int)(this->y + moveAmount)%(int)MapSpace->y );
  };
  void MoveLeft(Vector2D* MapSpace, float moveAmount){
    this->SetPosition(this->x - moveAmount, this->y);
    printf("x is: %f | y is: %f\n", this->x, this->y);
    if(this->x < 0)
      this->x = MapSpace->x;
    //this->SetPosition( (int)(this->x - moveAmount + (int)MapSpace->x)%(int)MapSpace->x, this->y );
  };
  void MoveRight(Vector2D* MapSpace, float moveAmount){
    this->SetPosition(this->x + moveAmount, this->y);
    printf("x is: %f | y is: %f\n", this->x, this->y);
    if(this->x > MapSpace->x)
      this->x = 0;
    //this->SetPosition( (int)(this->x + moveAmount)%(int)MapSpace->x, this->y );
  };

};


struct Vector2Di{
  int x;
  int y;
  Vector2Di();
  Vector2Di(int X, int Y){x = X, y = Y;};
  void SetPosition(int X, int Y){x = X, y = Y;};
};



