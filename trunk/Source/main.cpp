//============================================================================
// Name        : main.cpp
// Author      : murugan89@gmail.com
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <vector>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GL/glfw.h>
#include <Application.h>


#define SCREEN_WIDTH 600
#define SCREEN_HEIGHT 400

///Physics variables
#define Camera
//#define Debug

int quit_the_program;

void custom_fbsize_callback( int width, int height)
{
	Application::Instance()->init(width, height/*,1.0f,"Data/"*/);
}

void GLFWCALL Key_Callback(int key, int action)
{
	if(action==GLFW_PRESS)
		Application::Instance()->keyDown((unsigned char)key);
	else if(action == GLFW_RELEASE)
		Application::Instance()->keyUp((unsigned char)key);

}

void GLFWCALL Mouse_Callback(int key, int action)
{

	int xpos, ypos;

	glfwGetMousePos(&xpos, &ypos);
	if(action==GLFW_PRESS)
		Application::Instance()->mousePressed(xpos,ypos);
	else if(action == GLFW_RELEASE)
		Application::Instance()->mouseReleased(xpos,ypos);
	else
		Application::Instance()->mouseMoved(xpos,ypos);

}

int main( void )
{
	Application *pGame = Application::Instance();
	// Initialise GLFW
	if( !glfwInit() )
	{
		fprintf( stderr, "Failed to initialize GLFW\n" );
		return -1;
	}

	glfwOpenWindowHint(GLFW_FSAA_SAMPLES, 4);
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 2);
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 1);

	// Open a window and create its OpenGL context
	if( !glfwOpenWindow( SCREEN_WIDTH, SCREEN_HEIGHT, 0,0,0,0, 32,0, GLFW_WINDOW ) )
	{
		fprintf( stderr, "Failed to open GLFW window.\n" );
		glfwTerminate();
		return -1;
	}

	// Initialize GLEW
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return -1;
	}

	glfwSetWindowTitle( "Shooting" );

	glfwEnable( GLFW_STICKY_KEYS );
	glfwSetMousePos(SCREEN_WIDTH/2, SCREEN_HEIGHT/2);


	glfwSetKeyCallback(Key_Callback);
	glfwSetWindowSizeCallback(custom_fbsize_callback);

	glfwSetMouseButtonCallback(Mouse_Callback);
glfwSetMousePosCallback(Mouse_Callback);

	char const* path="Data/";
	Application::Instance()->init(SCREEN_WIDTH, SCREEN_HEIGHT/*,1.0f,path*/);


	do{


		Application::Instance()->update();

		Application::Instance()->draw();
		// Swap buffers
		glfwSwapBuffers();

	}
	while( (glfwGetKey( GLFW_KEY_ESC ) != GLFW_PRESS &&
		   glfwGetWindowParam( GLFW_OPENED ) ) );

	glfwTerminate();

//Application::Instance()->terminateWindow();
delete pGame;
	return 0;
}

