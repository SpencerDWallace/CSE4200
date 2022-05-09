#include "raycast.h"
#include "playercontroller.h"
#include <cstdio>

Raycast::Raycast()
{
  debug = false;
  defaultLighting = false;
}

Raycast::Raycast(Vector2D* ScreenSize, int Map[], Vector2D* MapSpace){
  debug = false;
  defaultLighting = false;
  screenSize = ScreenSize;
  map = Map;
  mapSpace = MapSpace;
  mapS = mapSpace->x * mapSpace->y;
}

void Raycast::Tick()
{
  drawMap2D();
  drawRays2D();
}

void Raycast::lookUp(){
  lookAngle = 90.f;
}

void Raycast::lookDown(){
  lookAngle = 270.f;
}

void Raycast::lookLeft(){
  lookAngle = 180.f;
}

void Raycast::lookRight(){
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
  int x,y;
  float xo,yo;
  int width = (((int)(screenSize->x))>>1)/mapSpace->x;

  for(y=0;y<mapSpace->y;y++)
    {
      for(x=0;x<mapSpace->x;x++)
	{
	  
	  if(map[y*(int)mapSpace->x + x]==1)
	    glColor3f(0.4,0.4,0.4);
	  else if(map[y*(int)mapSpace->x + x] == 2)
	    glColor3f(0,0.8,0);
	  else if(map[y*(int)mapSpace->x + x] == 3)
	    glColor3f(0.8,0,0);
	  else
	    glColor3f(0,0,0);
	  
	  xo=x*width; yo=y*width;
	  if(debug){
	    glBegin(GL_QUADS);
	    glVertex2i( 0   +xo+1, 0   +yo+1);
	    glVertex2i( 0   +xo+1, width+yo-1);
	    glVertex2i( width+xo-1, width+yo-1);
	    glVertex2i( width+xo-1, 0   +yo+1);
	    glEnd();
	  }
	  else{
	    glBegin(GL_QUADS);
	    glVertex2i( 0   +xo-1, 0   +yo-1);
	    glVertex2i( 0   +xo-1, width+yo+1);
	    glVertex2i( width+xo+1, width+yo+1);
	    glVertex2i( width+xo+1, 0   +yo-1);
	    glEnd();
	  }
	}
    }
};

/*
void Raycast::drawPlayer2D()
{
  int w = (((int)(screenSize->x))>>1)/mapSpace->x;
  float px = position->x*w + w/2; float py = position->y*w - w/2;
  float pdx = movement->x*w;
  float pdy = movement->y*w;
  
  glColor3f(0,0.8,0);   glPointSize(w);    glLineWidth(1);
  glBegin(GL_POINTS); glVertex2i(px,py); glEnd();
  glColor3f(0,0.8,0.8);
  glBegin(GL_LINES);  glVertex2i(px,py); glVertex2i(px+pdx,py+pdy); glEnd();
};
*/

void Raycast::drawRays2D()
{
  int height = screenSize->y;
  int width = screenSize->x;
  glColor3f(0.3,0.3,0.3); glBegin(GL_QUADS); glVertex2i(width>>1,  0); glVertex2i(width,  0); glVertex2i(width,height>>1); glVertex2i(width>>1,height>>1); glEnd();
  glColor3f(0.4,0.4,0.4); glBegin(GL_QUADS); glVertex2i(width>>1,height>>1); glVertex2i(width,height>>1); glVertex2i(width,height); glVertex2i(width>>1,height); glEnd();
  
  int w = (((int)(screenSize->x))>>1)/mapSpace->x;
  float px = position->x*w + w/2; float py = position->y*w + w/2;
  int mapX = 32; int mapY = 32;
  int r,mx,my,mp,dof,side; float vx,vy,rx,ry,ra,xo,yo,disV,disH;
  int fov = 64;
  int LPA = 8;
  ra=FixAng(lookAngle+(fov>>1)); //ray set back 30 degrees

  float color[3];
  float pie = 0;
  for(r=0;r<(fov*LPA);r++)
    {
      color[0] = color[1] = color[2] = 0.0;
      bool hit = false;
      //---Vertical---
      dof=0; side=0; disV=100000;
      float Tan=tan(degToRad(ra));
      if(cos(degToRad(ra))> 0.01){ rx=(((int)px>>4)<<4)+16;      ry=(px-rx)*Tan+py; xo= 16; yo=-xo*Tan;}//looking left
      else if(cos(degToRad(ra))<-0.01){ rx=(((int)px>>4)<<4) -0.01; ry=(px-rx)*Tan+py; xo=-16; yo=-xo*Tan;}//looking right
      else { rx=px; ry=py; dof=32;}                                                  //looking up or down. no hit
      
      while(dof<32)
	{
	  mx=(int)(rx)>>4; my=(int)(ry)>>4; mp=my*mapX+mx;
	  if(mp>0 && mp<mapX*mapY && map[mp]!=0){ hit = true; dof=32; disV=cos(degToRad(ra))*(rx-px)-sin(degToRad(ra))*(ry-py);}//hit
	  else{ rx+=xo; ry+=yo; dof+=1;}                                               //check next horizontal
	}
      vx=rx; vy=ry;
      
      
      if(hit){
	if(map[mp] == 1){
	  color[0] = color[1] = color[2] = 0.5;
	  glColor3f(0.5,0.5,0.5);
	}
	else if(map[mp] == 2) {
	  color[0] = color[2] = 0;
	  color[1] = 0.8;
	    glColor3f(0,0.8,0);
	  }
	else if(map[mp] == 3){
	  color[1] = color[2] = 0.0;
	  color[0] = 0.8;
	  glColor3f(0.8,0,0);
	}
      }
      
      hit = false;
      
      //---Horizontal---
      dof=0; disH=100000;
      Tan=1.0/Tan;
      if(sin(degToRad(ra))> 0.01){ ry=(((int)py>>4)<<4) -0.01; rx=(py-ry)*Tan+px; yo=-16; xo=-yo*Tan;}//looking up
      else if(sin(degToRad(ra))<-0.01){ ry=(((int)py>>4)<<4)+16;      rx=(py-ry)*Tan+px; yo= 16; xo=-yo*Tan;}//looking down
      else{ rx=px; ry=py; dof=32;}                                                   //looking straight left or right
      
      while(dof<32)
	{
	  mx=(int)(rx)>>4; my=(int)(ry)>>4; mp=my*mapX+mx;
	  if(mp>0 && mp<mapX*mapY && map[mp]!=0){ hit = true; dof=32; disH=cos(degToRad(ra))*(rx-px)-sin(degToRad(ra))*(ry-py);}//hit
	  else{ rx+=xo; ry+=yo; dof+=1;}                                               //check next horizontal
	}
      
      if(disV<disH){ rx=vx; ry=vy; disH=disV;}
      else{
	if(hit){
	  if(map[mp] == 1){
	    color[0] = color[1] = color[2] = 0.5;
	    glColor3f(0.8,0.8,0.8);
	  }
	  else if(map[mp] == 2) {
	    color[0] = color[2] = 0;
	    color[1] = 0.8;
	    glColor3f(0,0.8,0);
	  }
	  else if(map[mp] == 3){
	    color[1] = color[2] = 0.0;
	    color[0] = 0.8;
	    glColor3f(0.8,0,0);
	  }
	}
      }
      //horizontal hit first
      if(debug){
	glLineWidth(2); glBegin(GL_LINES); glVertex2i(px,py); glVertex2i(rx,ry); glEnd();//draw 2D ray
      }
      
      int ca=FixAng(lookAngle-ra); disH=disH*cos(degToRad(ca));                            //fix fisheye
      int lineH = (16*height)/(disH); if(lineH>height){ lineH=height;}                     //line height and limit
      int lineOff = (height>>1) - (lineH>>1);                                               //line offset
      float lineWidth = ((int)(screenSize->x)>>1)/(fov*LPA);
      float shading = (height/lineH)/(PI*sin(pie));
      pie += PI/(fov*LPA);
      
      if(!defaultLighting){
	color[0] = color[0]/shading;
	color[1] = color[1]/shading;
	color[2] = color[2]/shading;
      }
  
      glColor3fv(color);

      glLineWidth(lineWidth);glBegin(GL_LINES);glVertex2i(r*lineWidth+(width/2),lineOff);glVertex2i(r*lineWidth+(width/2),lineOff+lineH);glEnd();//draw vertical wall
      float angleOffset = (float)fov/((float)fov*(float)LPA);
      ra=FixAng(ra-angleOffset);                                                              //go to next ray
    }
}//-----------------------------------------------------------------------------
