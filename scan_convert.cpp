#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <math.h>

#if defined(__APPLE__)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "config.h"
#include "polygon_manager.h"
#include "clipping_window.h"

/******************************************************************
 Notes:
 Image size is 400 by 400 by default.  You may adjust this if
 you want to.
 You can assume the window will NOT be resized.
 Call clearFramebuffer to clear the entire framebuffer.
 Call setFramebuffer to set a pixel.  This should be the only
 routine you use to set the color (other than clearing the
 entire framebuffer).  drawit() will cause the current
 framebuffer to be displayed.
 As is, your scan conversion should probably be called from
 within the display function.  There is a very short sample
 of code there now.
 You may add code to any of the subroutines here,  You probably
 want to leave the drawit, clearFramebuffer, and
 setFramebuffer commands alone, though.
 *****************************************************************/

int window;

float framebuffer[HEIGHT][WIDTH][3];

PolygonManager polygon_manager;

ClippingWindow clipping_window;

// Draws the scene
void drawit( void ) {
	glDrawPixels( HEIGHT, WIDTH, GL_RGB, GL_FLOAT, framebuffer );
	glFlush();
}

// Clears framebuffer to black
void clearFramebuffer() {
	int i, j;

	for ( i = 0; i < HEIGHT; i++ ) {
		for ( j = 0; j < WIDTH; j++ ) {
			framebuffer[i][j][0] = 0.0;
			framebuffer[i][j][1] = 0.0;
			framebuffer[i][j][2] = 0.0;
		}
	}
}

// Sets pixel x,y to the color RGB
// I've made a small change to this function to make the pixels match
// those returned by the glutMouseFunc exactly - Scott Schaefer
void setFramebuffer( int x, int y, float R, float G, float B ) {
	// changes the origin from the lower-left corner to the upper-left corner
	y = HEIGHT - 1 - y;
	if ( R <= 1.0 )
		if ( R >= 0.0 )
			framebuffer[y][x][0] = R;
		else
			framebuffer[y][x][0] = 0.0;
	else
		framebuffer[y][x][0] = 1.0;
	if ( G <= 1.0 )
		if ( G >= 0.0 )
			framebuffer[y][x][1] = G;
		else
			framebuffer[y][x][1] = 0.0;
	else
		framebuffer[y][x][1] = 1.0;
	if ( B <= 1.0 )
		if ( B >= 0.0 )
			framebuffer[y][x][2] = B;
		else
			framebuffer[y][x][2] = 0.0;
	else
		framebuffer[y][x][2] = 1.0;
}

void display( void ) {
	clearFramebuffer();

	polygon_manager.draw_verticies( framebuffer );

	polygon_manager.draw_fill( framebuffer, clipping_window );

	drawit();
}

void onMouse( int button, int state, int x, int y ) {
	if ( state == GLUT_DOWN ) {

		// can only add poly's if clipping is OFF
		if ( !clipping_window.can_clip() ) {
			if ( button == GLUT_LEFT_BUTTON ) {
				polygon_manager.add_point( x, y );
			}

			if ( button == GLUT_RIGHT_BUTTON ) {
				polygon_manager.add_final_point( x, y );
			}
		}else{
			clipping_window.set_start_points(x, y);
		}
		glutPostRedisplay();
	}

}

void onMouseMove( int x, int y ) {
	if(clipping_window.can_clip()){
		clipping_window.set_end_points(x, y);
		glutPostRedisplay();
	}
}

/**
 * Callback that is registered to GLUT to handle all
 *  keyboard events for this program
 */
void onKeyPress( unsigned char key, int x, int y ) {
	switch ((char) key) {
	case 'q':
	case 27: // esc key
		glutDestroyWindow (window);
		exit( 0 );
	case 'c':
		clipping_window.toggle_clip();
		clipping_window.reset();
		if ( clipping_window.can_clip() ) {
			cout << "Click and drag on the screen to create a clipping window."
					<< endl;
		}else{
			cout << "Clipping disabled, you may add more polygons."
								<< endl;
		}
		break;
	default:
		break;
	}
	glutPostRedisplay();
	return;
}

void init( void ) {
	clearFramebuffer();
}

int main( int argc, char** argv ) {
	glutInit( &argc, argv );
	glutInitDisplayMode( GLUT_SINGLE | GLUT_RGB );
	glutInitWindowSize( WIDTH, HEIGHT );
	glutInitWindowPosition( 100, 100 );
	window = glutCreateWindow( "Robert Timm - Homework 3" );
	init();
	glutMouseFunc( onMouse );
	glutMotionFunc( onMouseMove );
	glutKeyboardFunc( onKeyPress );
	glutDisplayFunc( display );
	glutMainLoop();
	return 0;
}
