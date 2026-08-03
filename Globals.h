#pragma once

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

/* Global Variables */
//The window we'll be rendering to
extern SDL_Window* gWindow;

//The renderer used to draw to the window
extern SDL_Renderer* gRenderer;

//Global assets
extern TTF_Font* gFont;

//Global game objects
