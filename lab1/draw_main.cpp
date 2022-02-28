//draw_main.cpp: main loop of drawing program
#include <GL/gl.h>
#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "draw_util.h"

using namespace std;

//initialization
void init(void);
//does the drawing 
void display(void);
void keyboard(unsigned char key, int x, int y)
{
   switch (key) {
      case 27:
         exit(0);
         break;
   }
}

/*  Main Loop
 *  Open window with initial window size, title bar, 
 *  RGB display mode, single buffer.
 */
int main(int argc, char** argv)
{
  glutInit(&argc, argv);	//initialize toolkit
  glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB );	//set display mode: single bufferring, RGB model
  glutInitWindowSize(SCREENWIDTH, SCREENHEIGHT);		//set window size on screen
  glutInitWindowPosition( 100, 0 ); 	//set window position on screen
  //glutCreateWindow(argv[0]);		//open screen window
  glutCreateWindow( "Spencer's House" );		//open screen window
  init();
  glutDisplayFunc (display);		//points to display function
  glutKeyboardFunc (keyboard);
  glutMainLoop();			//go into perpetual loop
  return 0;
}


