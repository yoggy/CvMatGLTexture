#include "stdafx.h"
#include "cylinder.h"
#include "CvMatGLTexture.h"

Cylinder cylinder;

int window_width  = 640;
int window_height = 480;

SDL_Window *main_window = NULL;
SDL_GLContext main_glcontext = NULL;

cv::VideoCapture capture;
CvMatGLTexture texture;

bool init_sdl()
{
	SDL_Init(SDL_INIT_VIDEO);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	main_window = SDL_CreateWindow(
		"test", 0, 0, window_width, window_height, 
		SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_BORDERLESS);
	SDL_ShowCursor(SDL_DISABLE);

	main_glcontext = SDL_GL_CreateContext(main_window);

	return true;
}

void finish_sdl()
{
	if (main_glcontext != NULL) {
		SDL_GL_DeleteContext(main_glcontext);
		main_glcontext = NULL;
	}
	if (main_window != NULL) {
		SDL_DestroyWindow(main_window);
		main_window = NULL;
	}
	SDL_Quit();
}

void init_opengl()
{
	glViewport(0, 0, window_width, window_height);
    glClearColor(0.0f, 0.0f, 0.2f, 0.0f);
    glEnable(GL_DEPTH_TEST);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (double)window_width / (double)window_height, 1.0, 500.0);
}

void finish_opengl()
{

}

bool init_opencv()
{
	if (capture.open(0) == false) {
		printf("error : init_opencv() capture.open() failed...\n");
	}
	return true;
}

void finish_opencv()
{
	capture.release();
}

void draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION_MATRIX);
	gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// capture image
	cv::Mat capture_img;
	capture >> capture_img;

	// rotate cylinder
	static float r = 0;
	r = r + 1;
	glRotatef( 30, 1.0f, 0.0f, 0.0f);
	glRotatef( r, 0.0f, 1.0f, 0.0f);

	// draw cylinder
	glEnable(GL_TEXTURE_2D);
	texture.image(capture_img);
	texture.bind_texture();
	cylinder.draw();
	glDisable(GL_TEXTURE_2D);

	SDL_GL_SwapWindow(main_window);
}

void main_loop()
{
	SDL_Event evt;
	bool loop_flag = true;
	while(loop_flag) {
		while(SDL_PollEvent(&evt)) {
			switch(evt.type){
				case SDL_KEYUP:
					switch(evt.key.keysym.sym) {
						case SDLK_ESCAPE:
							loop_flag = false;
							break;
						case SDLK_LEFT:
							break;
						case SDLK_RIGHT:
							break;
						default:
							break;
					}					
					break;
				case SDL_QUIT:
					loop_flag = false;
					break;
				default:
					break;
			}
		}
		draw();
	}
}

int main(int argc, char* argv[])
{
	if (init_sdl() == false) {
		printf("error : init_sdl() failed...\n");
		return -1;
	}
	init_opengl();

	if (init_opencv() == false) {
		printf("error : init_opencv() failed...\n");
		return -1;
	}

	main_loop();

	finish_opencv();
	finish_opengl();
	finish_sdl();

	return 0;
}
