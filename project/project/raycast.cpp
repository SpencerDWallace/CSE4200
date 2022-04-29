#include "raycast.h"
#include "playercontroller.h"
#include <cstdio>

Raycast::Raycast()
{

}

Raycast::Raycast(Vector2D* ScreenSize, int Map[], Vector2D* MapSpace){
  screenSize = ScreenSize; //watch out for this if there are any weird errors later
  map = Map;
  mapSpace = MapSpace;
  mapS = mapSpace->x;// * mapSpace->y;
}

void Raycast::Tick()
{
  updateMovement();
//  printf("made it to raycast tick\n");
  drawMap2D();
//  printf("made it from drawMap\n");
  drawPlayer2D();
//  printf("made it from drawPlayer\n");
  drawRays2D();
//  printf("made it from drawRays\n");
}

void Raycast::lookUp(){
  movement->SetPosition(0,-1);
  lookAngle = 90.f;
}

void Raycast::lookDown(){
  movement->SetPosition(0,1);
  lookAngle = 270.f;
}

void Raycast::lookLeft(){
  movement->SetPosition(-1,0);
  lookAngle = 180.f;
}

void Raycast::lookRight(){
  movement->SetPosition(1,0);
  lookAngle = 0.f;
}

void Raycast::SetLookDirection(Direction newLookDirection) {
  lookDirection = newLookDirection;
  updateMovement();
}

void Raycast::updateMovement(){
  switch(lookDirection){
  case UP: lookUp();
    break;
  case DOWN: lookDown();
    break;
  case LEFT: lookLeft();
    break;
  case RIGHT: lookRight();
    break;
  default: break;
  }
}

void Raycast::drawMap2D()
{
  int x,y,xo,yo;
  for(y=0;y<mapSpace->y;y++)
    {
      for(x=0;x<mapSpace->x;x++)
	{
	  if(map[y*(int)mapSpace->x+x]==1){ glColor3f(1,1,1);} else{ glColor3f(0,0,0);}
	  xo=x*mapS; yo=y*mapS;
	  glBegin(GL_QUADS);
	  glVertex2i( 0   +xo+1, 0   +yo+1);
	  glVertex2i( 0   +xo+1, mapS+yo-1);
	  glVertex2i( mapS+xo-1, mapS+yo-1);
	  glVertex2i( mapS+xo-1, 0   +yo+1);
	  glEnd();
	}
    }
};

void Raycast::drawPlayer2D()
{
//  Vector2D playerPosition = player->GetPosition();
  float px = position->x*mapS; float py = position->y*mapS;
  float pdx = (player->GetNextPosition().x - position->x)*mapS;
  float pdy = (player->GetNextPosition().y - position->y)*mapS;
  //  float pdx = playerPosition.x - player->GetNextPosition().x;
  //float pdy = playerPosition.y - player->GetNextPosition().y;
  //  float px = position->x*mapS; float py = position->y*mapS;
  //  float pdx = position->x; float pdy = movement->y*mapS;
  //  float pdx = movement->x*moveAmount; float pdy = movement->y*moveAmount;
  //  float pdx = movement->x - px; float pdy = movement->y - py;
  glColor3f(1,1,0);   glPointSize(8);    glLineWidth(4);
  glBegin(GL_POINTS); glVertex2i(px,py); glEnd();
  glBegin(GL_LINES);  glVertex2i(px,py); glVertex2i(px+pdx*2,py+pdy*2); glEnd();
};


void Raycast::drawRays2D()
{
  Vector2D playerPosition = player->GetPosition();
  float px = position->x*mapS; float py = position->y*mapS;
  float pdx = (player->GetNextPosition().x - position->x)*mapS;
  float pdy = (player->GetNextPosition().y - position->y)*mapS;
  //float moveAmount = 0.001;
  //float px = position->x; float py = position->y;
  //float pdx = movement->x*moveAmount; float pdy = movement->y*moveAmount;
  //  float pdx = movement->x - px; float pdy = movement->y - py;
  
  glColor3f(0,1,1); glBegin(GL_QUADS); glVertex2i(526,  0); glVertex2i(1006,  0); glVertex2i(1006,160); glVertex2i(526,160); glEnd();
  glColor3f(0,0,1); glBegin(GL_QUADS); glVertex2i(526,0); glVertex2i(1006,0); glVertex2i(1006,screenSize->y); glVertex2i(526,screenSize->y); glEnd();
  
  int r,mx,my,mp,dof,side; float vx,vy,rx,ry,ra,xo,yo,disV,disH;
  
  ra=FixAng(lookAngle+30);                                                              //ray set back 30 degrees
  
  for(r=0;r<60;r++)
    {
      //---Vertical---
      dof=0; side=0; disV=100000;
      float Tan=tan(degToRad(ra));
      if(cos(degToRad(ra))> 0.001){ rx=(((int)px>>6)<<6)+64;      ry=(px-rx)*Tan+py; xo= 64; yo=-xo*Tan;}//looking left
      else if(cos(degToRad(ra))<-0.001){ rx=(((int)px>>6)<<6) -0.0001; ry=(px-rx)*Tan+py; xo=-64; yo=-xo*Tan;}//looking right
      else { rx=px; ry=py; dof=8;}                                                  //looking up or down. no hit
      
      while(dof<8)
	{
	  mx=(int)(rx)>>6; my=(int)(ry)>>6; mp=my*mapSpace->x+mx;
	  if(mp>0 && mp<mapSpace->x*mapSpace->y && map[mp]==1){ dof=8; disV=cos(degToRad(ra))*(rx-px)-sin(degToRad(ra))*(ry-py);}//hit
	  else{ rx+=xo; ry+=yo; dof+=1;}                                               //check next horizontal
	}
      vx=rx; vy=ry;
      
      //---Horizontal---
      dof=0; disH=100000;
      Tan=1.0/Tan;
      if(sin(degToRad(ra))> 0.001){ ry=(((int)py>>6)<<6) -0.0001; rx=(py-ry)*Tan+px; yo=-64; xo=-yo*Tan;}//looking up
      else if(sin(degToRad(ra))<-0.001){ ry=(((int)py>>6)<<6)+64;      rx=(py-ry)*Tan+px; yo= 64; xo=-yo*Tan;}//looking down
      else{ rx=px; ry=py; dof=8;}                                                   //looking straight left or right
      
      while(dof<8)
	{
	  mx=(int)(rx)>>6; my=(int)(ry)>>6; mp=my*mapSpace->x+mx;
	  if(mp>0 && mp<mapSpace->x*mapSpace->y && map[mp]==1){ dof=8; disH=cos(degToRad(ra))*(rx-px)-sin(degToRad(ra))*(ry-py);}//hit
	  else{ rx+=xo; ry+=yo; dof+=1;}                                               //check next horizontal
	}
      
      glColor3f(0,0.8,0);
      if(disV<disH){ rx=vx; ry=vy; disH=disV; glColor3f(0,0.6,0);}                  //horizontal hit first
      //glLineWidth(2); glBegin(GL_LINES); glVertex2i(px,py); glVertex2i(rx,ry); glEnd();//draw 2D ray
      
      int ca=FixAng(lookAngle-ra); disH=disH*cos(degToRad(ca));                            //fix fisheye
      int lineH = (mapS*screenSize->y)/(disH); if(lineH>screenSize->y){ lineH=screenSize->y;}                     //line height and limit
      int lineOff = 160 - (lineH>>1);                                               //line offset
      
      glLineWidth(8);glBegin(GL_LINES);glVertex2i(r*8+530,lineOff);glVertex2i(r*8+530,lineOff+lineH);glEnd();//draw vertical wall
      
      ra=FixAng(ra-1);                                                              //go to next ray
    }
}
