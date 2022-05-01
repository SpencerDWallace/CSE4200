#pragma once

#include <cstdio>
#include <math.h>

enum Direction {UP,DOWN,LEFT,RIGHT,NONE};
#define PI 3.14159265


struct Vector2D{
  float x;
  float y;
  Vector2D();
  Vector2D(float X, float Y)
  {
    x = X; y = Y;
  };

  void SetPosition(const float& X, const float& Y)
  {
    x = X; y = Y;
  };
  
  void MoveUp(Vector2D* MapSpace, float moveAmount){
    this->SetPosition(this->x, this->y - moveAmount);
    if(this->y < 1)
      this->y = MapSpace->x - 2;
  };

  void MoveDown(Vector2D* MapSpace, float moveAmount){
    this->SetPosition(this->x, this->y + moveAmount);
    if(this->y > MapSpace->y - 2)
      this->y = 1;
  };

  void MoveLeft(Vector2D* MapSpace, float moveAmount){
    this->SetPosition(this->x - moveAmount, this->y);
    if(this->x < 1)
      this->x = MapSpace->y - 2;
  };

  void MoveRight(Vector2D* MapSpace, float moveAmount){
    this->SetPosition(this->x + moveAmount, this->y);
    if(this->x > MapSpace->x - 2)
      this->x = 1;
  };

};

/*
struct Rect{
  Vector2D* position;
  Vector2D* size;
  Rect();
  Rect(Vector2D* pos, Vector2D* s)
  {
    position = pos; size = s;
  };

  bool checkBounds(Vector2D* p1)
  {
    float minX = position->x - (((int)size->x)>>1);
    float maxX = position->x + (((int)size->x)>>1);
    float minY = position->y - (((int)size->y)>>1);
    float maxY = position->y + (((int)size->y)>>1);
    if( ( p1->x >= minX && p1->x <= maxX ) && (p1->y >= minY && p1->y <= maxY) )
      return true;
    return false;
  };
  
};

struct Vector2Di{
  int x;
  int y;
  Vector2Di();
  Vector2Di(int X, int Y){x = X, y = Y;};
  void SetPosition(int X, int Y){x = X, y = Y;};
};

*/
