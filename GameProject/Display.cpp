#include "Display.h"
#include "StaticInput.h"
#include "SDL\SDL.h"
#include "GL\glew.h"
#include "SDL_ttf.h"
#include <iostream>


Display::Display(int width, int height, const std::string & title)
{
	this->height = height;
	this->width = width;
	SDL_Init(SDL_INIT_EVERYTHING);

	//Color
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	
	m_window = SDL_CreateWindow(title.c_str(),SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,width,height,SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
	m_glContext = SDL_GL_CreateContext(m_window);

	GLenum status = glewInit();

	if (status != GLEW_OK) {
		std::cerr << "Glew failed to initilize" << std::endl;
	}
	TTF_Init();


	glEnable(GL_DEPTH);
	glDisable(GL_SCISSOR_TEST);
	
}

void Display::Clear(float r, float b, float g, float a)
{
	glClearColor(r,b,g,a);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Display::Update()
{
	if (StaticInput::getKeyboardData().letters.P == InputData::PRESSED) {
		SDL_Quit();
		this->Close();
	}
	SDL_GL_SwapWindow(m_window);
	SDL_WarpMouseInWindow(m_window, width / 2, height / 2);
	
}

bool Display::IsClosed()
{
	return m_isClosed;
}

Display::~Display()
{
	SDL_GL_DeleteContext(m_glContext);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}