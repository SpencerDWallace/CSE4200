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
  mapS = mapSpace->x * mapSpace->y;
}

void Raycast::Tick()
{

//  printf("made it to raycast tick\n");
  drawMap2D();
//  printf("made it from drawMap\n");
  drawPlayer2D();
//  printf("made it from drawPlayer\n");
  drawRays2D();
//  printf("made it from drawRays\n");
}

void Raycast::lookUp(){
  printf("movement is %f %f\n", movement->x, movement->y);
  lookAngle = 90.f;
}

void Raycast::lookDown(){
  printf("movement is %f %f\n", movement->x, movement->y);
  lookAngle = 270.f;
}

void Raycast::lookLeft(){
  printf("movement is %f %f\n", movement->x, movement->y);
  lookAngle = 180.f;
}

void Raycast::lookRight(){
  printf("movement is %f %f\n", movement->x, movement->y);
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
	  if(map[y*(int)mapSpace->x+x]==1){ glColor3f(1,1,1);} else{ glColor3f(0,0,0);}

	  xo=x*width; yo=y*width;
	  glBegin(GL_QUADS);
	  glVertex2i( 0   +xo+1, 0   +yo+1);
	  glVertex2i( 0   +xo+1, width+yo-1);
	  glVertex2i( width+xo-1, width+yo-1);
	  glVertex2i( width+xo-1, 0   +yo+1);
	  glEnd();
	}
    }
};


void Raycast::drawPlayer2D()
{
//  Vector2D playerPosition = player->GetPosition();
  int w = (((int)(screenSize->x))>>1)/mapSpace->x;
  float px = position->x*w + w/2; float py = position->y*w - w/2;
  float pdx = movement->x*w;
  float pdy = movement->y*w;
  //  float pdx = playerPosition.x - player->GetNextPosition().x;
  //float pdy = playerPosition.y - player->GetNextPosition().y;
  //  float px = position->x*mapS; float py = position->y*mapS;
  //  float pdx = position->x; float pdy = movement->y*mapS;
  //  float pdx = movement->x*moveAmount; float pdy = movement->y*moveAmount;
  //  float pdx = movement->x - px; float pdy = movement->y - py;
  glColor3f(0,0.8,0);   glPointSize(w);    glLineWidth(1);
  glBegin(GL_POINTS); glVertex2i(px,py); glEnd();
  glColor3f(0,0.8,0.8);
  glBegin(GL_LINES);  glVertex2i(px,py); glVertex2i(px+pdx,py+pdy); glEnd();
};

void Raycast::drawRays2D()
{
  int height = screenSize->y;
  int width = screenSize->x;
  glColor3f(0,1,1); glBegin(GL_QUADS); glVertex2i(width>>1,  0); glVertex2i(width,  0); glVertex2i(width,height>>1); glVertex2i(width>>1,height>>1); glEnd();	
  glColor3f(0,0,1); glBegin(GL_QUADS); glVertex2i(width>>1,height>>1); glVertex2i(width,height>>1); glVertex2i(width,height); glVertex2i(width>>1,height); glEnd();	 	


 // int offset = 512/mapSpace->x;
 //float px = position->x*offset; float py = position->y*offset;
 //float pdx = movement->x*offset;
 //float pdy = movement->y*offset;
  int w = (((int)(screenSize->x))>>1)/mapSpace->x;
  float px = position->x*w; float py = position->y*w;
  float pdx = movement->x*w;
  float pdy = movement->y*w;
  // float px = position->x*mapS; float py = position->y*mapS;
  //float pdx = movement->x*mapS;
  //float pdy = movement->y*mapS;
 int mapX = 16; int mapY = 16;
 int r,mx,my,mp,dof,side; float vx,vy,rx,ry,ra,xo,yo,disV,disH;
 int fov = 90;
 
 ra=FixAng(lookAngle+(fov>>1));                                                              //ray set back 30 degrees
 
 for(r=0;r<fov;r++)
 {
  //---Vertical--- 
  dof=0; side=0; disV=100000;
  float Tan=tan(degToRad(ra));
       if(cos(degToRad(ra))> 0.01){ rx=(((int)px>>5)<<5)+32;      ry=(px-rx)*Tan+py; xo= 32; yo=-xo*Tan;}//looking left
  else if(cos(degToRad(ra))<-0.01){ rx=(((int)px>>5)<<5) -0.01; ry=(px-rx)*Tan+py; xo=-32; yo=-xo*Tan;}//looking right
  else { rx=px; ry=py; dof=16;}                                                  //looking up or down. no hit  

  while(dof<16) 
  { 
   mx=(int)(rx)>>5; my=(int)(ry)>>5; mp=my*mapX+mx;                     
   if(mp>0 && mp<mapX*mapY && map[mp]==1){ dof=16; disV=cos(degToRad(ra))*(rx-px)-sin(degToRad(ra))*(ry-py);}//hit         
   else{ rx+=xo; ry+=yo; dof+=1;}                                               //check next horizontal
  } 
  vx=rx; vy=ry;

  //---Horizontal---
  dof=0; disH=100000;
  Tan=1.0/Tan; 
       if(sin(degToRad(ra))> 0.01){ ry=(((int)py>>5)<<5) -0.01; rx=(py-ry)*Tan+px; yo=-32; xo=-yo*Tan;}//looking up 
  else if(sin(degToRad(ra))<-0.01){ ry=(((int)py>>5)<<5)+32;      rx=(py-ry)*Tan+px; yo= 32; xo=-yo*Tan;}//looking down
  else{ rx=px; ry=py; dof=16;}                                                   //looking straight left or right
 
  while(dof<16) 
  { 
   mx=(int)(rx)>>5; my=(int)(ry)>>5; mp=my*mapX+mx;                          
   if(mp>0 && mp<mapX*mapY && map[mp]==1){ dof=16; disH=cos(degToRad(ra))*(rx-px)-sin(degToRad(ra))*(ry-py);}//hit         
   else{ rx+=xo; ry+=yo; dof+=1;}                                               //check next horizontal
  } 
  
  glColor3f(0.5,0.5,0.5);
  if(disV<disH){ rx=vx; ry=vy; disH=disV;}                  //horizontal hit first
  //  glLineWidth(2); glBegin(GL_LINES); glVertex2i(px,py); glVertex2i(rx,ry); glEnd();//draw 2D ray
    
  int ca=FixAng(lookAngle-ra); disH=disH*cos(degToRad(ca));                            //fix fisheye 
  int lineH = (32*height/2)/(disH); if(lineH>height){ lineH=height;}                     //line height and limit
  int lineOff = (height>>1) - (lineH>>1);                                               //line offset
  float lineWidth = ((int)(screenSize->x)>>1)/fov;
  glLineWidth(6);glBegin(GL_LINES);glVertex2i(r*6+(width/2),lineOff);glVertex2i(r*6+(width/2),lineOff+lineH);glEnd();//draw vertical wall  

  ra=FixAng(ra-1);                                                              //go to next ray
 }
}//-----------------------------------------------------------------------------



/*
void Raycast::drawRays2D()
{
 glColor3f(0,1,1); glBegin(GL_QUADS); glVertex2i(526,  0); glVertex2i(1006,  0); glVertex2i(1006,160); glVertex2i(526,160); glEnd();	
 glColor3f(0,0,1); glBegin(GL_QUADS); glVertex2i(526,160); glVertex2i(1006,160); glVertex2i(1006,320); glVertex2i(526,320); glEnd();	 	

 float px = position->x*mapS; float py = position->y*mapS;
 float pdx = movement->x*mapS;
 float pdy = movement->y*mapS;
 
 int r,mx,my,mp,dof,side; float vx,vy,rx,ry,ra,xo,yo,disV,disH; 
 int mapX = mapSpace->x;
 int mapY = mapSpace->y;
 int mapSize = mapX*mapY;
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
   mx=(int)(rx)>>6; my=(int)(ry)>>6; mp=my*mapX+mx;                     
   if(mp>0 && mp<mapX*mapY && map[mp]==1){ dof=8; disV=cos(degToRad(ra))*(rx-px)-sin(degToRad(ra))*(ry-py);}//hit         
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
   mx=(int)(rx)>>6; my=(int)(ry)>>6; mp=my*mapX+mx;                          
   if(mp>0 && mp<mapX*mapY && map[mp]==1){ dof=8; disH=cos(degToRad(ra))*(rx-px)-sin(degToRad(ra))*(ry-py);}//hit         
   else{ rx+=xo; ry+=yo; dof+=1;}                                               //check next horizontal
  } 
  
  glColor3f(0,0.8,0);
  if(disV<disH){ rx=vx; ry=vy; disH=disV; glColor3f(0,0.6,0);}                  //horizontal hit first
  glLineWidth(2); glBegin(GL_LINES); glVertex2i(px,py); glVertex2i(rx,ry); glEnd();//draw 2D ray
    
  int ca=FixAng(lookAngle-ra); disH=disH*cos(degToRad(ca));                            //fix fisheye 
  int lineH = (mapSize*320)/(disH); if(lineH>320){ lineH=320;}                     //line height and limit
  int lineOff = 160 - (lineH>>1);                                               //line offset
  
  glLineWidth(8);glBegin(GL_LINES);glVertex2i(r*8+530,lineOff);glVertex2i(r*8+530,lineOff+lineH);glEnd();//draw vertical wall  

  ra=FixAng(ra-1);                                                              //go to next ray
 }
}//----


/*

void Raycast::drawRays2D()
{

/*********************************************************************************
     r is the iteration count for the loop
     mx is used for the column px is in, my is used for the row py is in,
     mp is used for the block (index of map array) that the player is in,
     dof is for depth of field, rx is ray's x, ry is ray's y, ra is ray's angle,
     MS is the squared size of each block, disH and disV are the distance
     the rays had to travel before hitting an object, set to 10000 as default, distFinal
     is the lesser value between disH and disV.
     hx and hy are the x and y coordinates of the ray checking for horizontal contact,
     vx and vy are the x and y coordinates of the ray checking for vertical contact
*********************************************************************************/
/*
  float r, mx, my, mp, dof, rx, ry, ra, xOffset, yOffset, aTan, nTan;
  ra =  ((lookAngle - 30)*PI)/180.0;
  
  float px = position->x*mapS; float py = position->y*mapS;
  float pdx = movement->x*mapS;
  float pdy = movement->y*mapS;

  int numOfRays = 60;
  int mapX = mapSpace->x; int mapY = mapSpace->y;
  int MS = mapSpace->x*mapSpace->y;
    
  int disH = 10000; int disV = 10000; float distFinal; float hx = px; float vx = px; float hy = py; float vy = py;
  
  for(r = 0; r < numOfRays; r++) {
    if(ra > 2*PI)
      ra -= 2*PI;
    if(ra <0)
      ra += 2*PI;
    
    //checking horizontals
    dof = 0;
    aTan = -(1 / tan(ra));
  // looking down
    if (ra < PI && ra > 0) {
      ry = ((int)(py / MS) + 1) * MS +0.01;
    rx = (py - ry) * aTan + px;
    yOffset = MS;
    xOffset = -1* yOffset * aTan;
    }
    //looking up
    else if (ra > PI && ra < 2*PI) {
      ry = (int)(py / MS) * MS - 0.01;
      rx = (py - ry) * aTan + px;
      yOffset = -MS;
      xOffset = -1 * yOffset * aTan;
    } else {
      rx = px;
      ry = py;
      dof = mapX;
  }
    
  if(rx >= MS*mapX || ry >= MS*mapX)
    dof= mapX;
  while (dof < mapX) {
    mx = (int)(rx / MS);
    my = (int)(ry / MS);
    mp = (int)(my * mapX + mx);
    
    if (mp >= 0 && mp < mapX * mapY && map[(int)mp] > 0) {
      //log("mp horiz is: " + mp);
      hx = rx;
      hy = ry;
      disH = distt(px - hx, py - hy);
      dof = mapX;
    } else {
      rx += xOffset;
      ry += yOffset;
      dof += 1;
    }
  }
  
  //checking verticals
  nTan = -1 * (tan(ra));
  dof = 0;
  //looking left
  if (ra > PI / 2 && ra < (3 * PI / 2)) {
    rx = (int)(px / MS) * MS - 0.001;
    ry = (px - rx) * nTan + py;
    xOffset = -MS;
    yOffset = -xOffset * nTan;
    
  }
  //looking right
  else if (ra < PI / 2 || ra > (3 * PI / 2)) {
    rx = (int)(px / MS) * MS + MS;
    ry = (px - rx) * nTan + py;
    xOffset = MS;
    yOffset = -xOffset * nTan;
  } else {
    rx = px;
    ry = py;
    dof = mapX;
  }
  while (dof < mapX) {
    
    mx = (int)(rx / MS);
    
    my = (int)(ry / MS);
    mp = (int)(my * mapX + mx);
    if (mp >= 0 && mp < mapX * mapY && map[(int)mp] > 0) {
      vx = rx;
      vy = ry;
      disV = distt(px - vx, py - vy);
      dof = mapX;
    } else {
      rx += xOffset;
      ry += yOffset;
      dof += 1;
    }
  }
  
  if (disV <= disH) {
    rx = vx; ry = vy;
    distFinal = disV;
    glColor3f(0,0.8,0);
  } else if (disH < disV){
    rx = hx;
    ry = hy;
    distFinal = disH;
    glColor3f(0,0.6,0);
  }
  
  //Render 3D
  float ca = ((lookAngle)*PI/180) - ra; if(ca < 0) ca += 2*PI; if (ca > 2*PI) ca -= 2*PI;
  distFinal = distFinal*cos(ca);
  float height = screenSize->y;
  float lineH = (MS*height)/distFinal; if(lineH > height) lineH = height;
  float lineOff = height/2 - lineH/2;

  //r*lineWidth + screenSize->x/2, 0 | r*lineWidth + screenSize->x/2, screenSize->y
  float lineWidth = (screenSize->x/(2*numOfRays));
  glLineWidth(8);glBegin(GL_LINES);glVertex2i(r*lineWidth + screenSize->x/2,lineOff);glVertex2i(r*lineWidth + screenSize->x/2,lineH);glEnd();//draw vertical wall  

  ra += PI/180;
  if(ra > 2*PI)
    ra -= 2*PI;
  if(ra <0)
    ra += 2*PI;

  disH = 10000, disV = 10000;
  
 }
  
}


void Raycast::drawRays2D()
{
  printf("screen dim are %f %f\n", mapSpace->x, mapSpace->y);
  Vector2D playerPosition = player->GetPosition();
  float px = position->x*mapS; float py = position->y*mapS;
  float pdx = movement->x*mapS;
  float pdy = movement->y*mapS;
  //float moveAmount = 0.001;
  //float px = position->x; float py = position->y;
  //float pdx = movement->x*moveAmount; float pdy = movement->y*moveAmount;
  //  float pdx = movement->x - px; float pdy = movement->y - py;
  
  glColor3f(0,1,1); glBegin(GL_QUADS); glVertex2i(526,  0); glVertex2i(1006,  0); glVertex2i(1006,160); glVertex2i(526,160); glEnd();
  glColor3f(0,0,1); glBegin(GL_QUADS); glVertex2i(526,0); glVertex2i(1006,0); glVertex2i(1006,screenSize->y); glVertex2i(526,screenSize->y); glEnd();
  
  int r,mx,my,mp,dof,side; float vx,vy,rx,ry,ra,xo,yo,disV,disH;
  int fov = 60;
  float width = screenSize->x/(fov*2);
  ra=FixAng(lookAngle+30);                                                              //ray set back 30 degrees
  
  for(r=0;r<fov;r++)
    {
      //---Vertical---
      dof=0; side=0; disV=100000;
      float Tan=tan(degToRad(ra));
      if(cos(degToRad(ra))> 0.001){ rx=(((int)px>>6)<<6)+64;      ry=(px-rx)*Tan+py; xo= 64; yo=-xo*Tan;}//looking left
      else if(cos(degToRad(ra))<-0.001){ rx=(((int)px>>6)<<6) -0.0001; ry=(px-rx)*Tan+py; xo=-64; yo=-xo*Tan;}//looking right
      else { rx=px; ry=py; dof=12;}                                                  //looking up or down. no hit
      
      while(dof<12)
	{
	  mx=(int)(rx)>>6; my=(int)(ry)>>6; mp=my*mapSpace->x+mx;
	  if(mp>0 && mp<mapSpace->x*mapSpace->y && map[mp]==1){ dof=12; disV=cos(degToRad(ra))*(rx-px)-sin(degToRad(ra))*(ry-py);}//hit
	  else{ rx+=xo; ry+=yo; dof+=1;}                                               //check next horizontal
	}
      vx=rx; vy=ry;
      
      //---Horizontal---
      dof=0; disH=100000;
      Tan=1.0/Tan;
      if(sin(degToRad(ra))> 0.001){ ry=(((int)py>>6)<<6) -0.0001; rx=(py-ry)*Tan+px; yo=-64; xo=-yo*Tan;}//looking up
      else if(sin(degToRad(ra))<-0.001){ ry=(((int)py>>6)<<6)+64;      rx=(py-ry)*Tan+px; yo= 64; xo=-yo*Tan;}//looking down
      else{ rx=px; ry=py; dof=12;}                                                   //looking straight left or right
      
      while(dof<12)
	{
	  mx=(int)(rx)>>6; my=(int)(ry)>>6; mp=my*mapSpace->x+mx;
	  if(mp>0 && mp<mapSpace->x*mapSpace->y && map[mp]==1){ dof=12; disH=cos(degToRad(ra))*(rx-px)-sin(degToRad(ra))*(ry-py);}//hit
	  else{ rx+=xo; ry+=yo; dof+=1;}                                               //check next horizontal
	}
      
      glColor3f(0,0.8,0);
      if(disV<disH){ rx=vx; ry=vy; disH=disV; glColor3f(0,0.6,0);}                  //horizontal hit first
      //glLineWidth(2); glBegin(GL_LINES); glVertex2i(px,py); glVertex2i(rx,ry); glEnd();//draw 2D ray
      
      int ca=FixAng(lookAngle-ra); disH=disH*cos(degToRad(ca));//fix fisheye

      int lineH = (mapSpace->x*mapSpace->y*screenSize->y)/(disH); if(lineH > screenSize->y){ lineH = screenSize->y;}                     //line height and limit
      int lineOff = screenSize->y/2 - (lineH>>1);                                               //line offset
      
      //      glLineWidth(8);glBegin(GL_LINES);glVertex2i(r*8+530,lineOff);glVertex2i(r*8+530,lineOff+lineH);glEnd();//draw vertical wall  
      //int lineH = (mapSpace->x*mapSpace->y*screenSize->y)/(disH); if(lineH>screenSize->y){ lineH=screenSize->y;}                     //line height and limit
      //int lineOff = 0 - (lineH>>1);                                               //line offset
      
      glLineWidth(width);glBegin(GL_LINES);glVertex2i(r*width+screenSize->x/2,lineOff + lineH);glVertex2i(r*width+screenSize->x/2, lineH - lineOff);glEnd();//draw vertical wall
      
      ra=FixAng(ra-1);                                                              //go to next ray
    }
}

*/
