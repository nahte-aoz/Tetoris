#pragma once

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <string>
#include "Constants.h"
#include "Globals.h"

/* Class Prototypes */
class LTexture
{
public:
    //Symbolic constant
    static constexpr float kOriginalSize = -1.f;

    //Initializes texture variables
    LTexture();

    //Cleans up texture variables
    ~LTexture();

    //Loads texture from disk
    bool loadFromFile(std::string path);

#if defined(SDL_TTF_MAJOR_VERSION)
    //Creates texture from text
    bool loadFromRenderedText(std::string textureText, SDL_Color textColor);
#endif

    //Cleans up texture
    void destroy();

    //Sets color modulation
    void setColor(Uint8 r, Uint8 g, Uint8 b);

    //Sets opacity
    void setAlpha(Uint8 alpha);

    //Sets blend mode
    void setBlending(SDL_BlendMode blendMode);

    //Draws texture
    void render(float x, float y, SDL_FRect* clip = nullptr, float width = kOriginalSize, float height = kOriginalSize, double degrees = 0.0, SDL_FPoint* center = nullptr, SDL_FlipMode flipMode = SDL_FLIP_NONE);

    //Gets texture attributes
    int getWidth();
    int getHeight();
    bool isLoaded();

private:
    //Contains texture data
    SDL_Texture* mTexture;

    //Texture dimensions
    int mWidth;
    int mHeight;
};

class LTimer
{
public:
    //Initializes variables
    LTimer();

    //The various clock actions
    void start();
    void stop();
    void pause();
    void unpause();

    //Gets the timer's time
    Uint64 getTicksNS();

    //Checks the status of the timer
    bool isStarted();
    bool isPaused();

private:
    //The clock time when the timer started
    Uint64 mStartTicks;

    //The ticks stored when the timer was paused
    Uint64 mPausedTicks;

    //The timer status
    bool mPaused;
    bool mStarted;
};

//class IO {
//public:
//    void drawRectangle(int x, int y, int rectWidth, int rectHeight);
//
//    void destroy();
//
//    void setColor();
//
//    void setAlpha();
//
//    void setBlending();
//
//    void render();
//
//private:
//    SDL_FRect mRectangle;
//};

/* Function Prototypes */
//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//Check collision
bool checkCollision(SDL_Rect a, SDL_Rect b);

//Global square texture
extern LTexture gSquareTexture;