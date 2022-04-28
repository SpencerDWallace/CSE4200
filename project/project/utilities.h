#pragma once

enum Direction {UP,DOWN,LEFT,RIGHT,NONE};

struct Vector2D{
  int x;
  int y;
  Vector2D();
  Vector2D(int X, int Y){x = X, y = Y;};
  void SetPosition(int X, int Y){x = X, y = Y;};
};

  
