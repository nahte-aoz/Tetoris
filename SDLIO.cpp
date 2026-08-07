#include "SDLIO.h"

/* Class Implementations */
//LTexture Implementation
LTexture::LTexture() :
    //Initialize texture variables
    mTexture{ nullptr },
    mWidth{ 0 },
    mHeight{ 0 }
{

}

LTexture::~LTexture()
{
    //Clean up texture
    destroy();
}

bool LTexture::loadFromFile(std::string path)
{
    //Clean up texture if it already exists
    destroy();

    //Load surface
    if (SDL_Surface* loadedSurface = IMG_Load(path.c_str()); loadedSurface == nullptr)
    {
        SDL_Log("Unable to load image %s! SDL_image error: %s\n", path.c_str(), SDL_GetError());
    }
    else
    {
        //Color key image
        if (SDL_SetSurfaceColorKey(loadedSurface, true, SDL_MapSurfaceRGB(loadedSurface, 0xFF, 0xD9, 0x52)) == false)
        {
            SDL_Log("Unable to color key! SDL error: %s", SDL_GetError());
        }
        else
        {
            //Create texture from surface
            if (mTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface); mTexture == nullptr)
            {
                SDL_Log("Unable to create texture from loaded pixels! SDL error: %s\n", SDL_GetError());
            }
            else
            {
                //Get image dimensions
                mWidth = loadedSurface->w;
                mHeight = loadedSurface->h;
            }
        }

        //Clean up loaded surface
        SDL_DestroySurface(loadedSurface);
    }

    //Return success if texture loaded
    return mTexture != nullptr;
}

#if defined(SDL_TTF_MAJOR_VERSION)
bool LTexture::loadFromRenderedText(std::string textureText, SDL_Color textColor)
{
    //Clean up existing texture
    destroy();

    //Load text surface
    if (SDL_Surface* textSurface = TTF_RenderText_Blended(gFont, textureText.c_str(), 0, textColor); textSurface == nullptr)
    {
        SDL_Log("Unable to render text surface! SDL_ttf Error: %s\n", SDL_GetError());
    }
    else
    {
        //Create texture from surface
        if (mTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface); mTexture == nullptr)
        {
            SDL_Log("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
        }
        else
        {
            mWidth = textSurface->w;
            mHeight = textSurface->h;
        }

        //Free temp surface
        SDL_DestroySurface(textSurface);
    }

    //Return success if texture loaded
    return mTexture != nullptr;
}
#endif

void LTexture::destroy()
{
    //Clean up texture
    SDL_DestroyTexture(mTexture);
    mTexture = nullptr;
    mWidth = 0;
    mHeight = 0;
}

void LTexture::setColor(Uint8 r, Uint8 g, Uint8 b)
{
    SDL_SetTextureColorMod(mTexture, r, g, b);
}

void LTexture::setAlpha(Uint8 alpha)
{
    SDL_SetTextureAlphaMod(mTexture, alpha);
}

void LTexture::setBlending(SDL_BlendMode blendMode)
{
    SDL_SetTextureBlendMode(mTexture, blendMode);
}

void LTexture::render(float x, float y, SDL_FRect* clip, float width, float height, double degrees, SDL_FPoint* center, SDL_FlipMode flipMode)
{
    //Set texture position
    SDL_FRect dstRect{ x, y, static_cast<float>(mWidth), static_cast<float>(mHeight) };

    //Default to clip dimensions if clip is given
    if (clip != nullptr)
    {
        dstRect.w = clip->w;
        dstRect.h = clip->h;
    }

    //Resize if new dimensions are given
    if (width > 0)
    {
        dstRect.w = width;
    }
    if (height > 0)
    {
        dstRect.h = height;
    }

    //Render texture
    SDL_RenderTextureRotated(gRenderer, mTexture, clip, &dstRect, degrees, center, flipMode);
}

int LTexture::getWidth()
{
    return mWidth;
}

int LTexture::getHeight()
{
    return mHeight;
}

bool LTexture::isLoaded()
{
    return mTexture != nullptr;
}

//LTimer Implementation
LTimer::LTimer() :
    mStartTicks{ 0 },
    mPausedTicks{ 0 },

    mPaused{ false },
    mStarted{ false }
{

}

void LTimer::start()
{
    //Start the timer
    mStarted = true;

    //Unpause the timer
    mPaused = false;

    //Get the current clock time
    mStartTicks = SDL_GetTicksNS();
    mPausedTicks = 0;
}

void LTimer::stop()
{
    //Stop the timer
    mStarted = false;

    //Unpause the timer
    mPaused = false;

    //Clear tick variables
    mStartTicks = 0;
    mPausedTicks = 0;
}

void LTimer::pause()
{
    //If the timer is running and isn't already paused
    if (mStarted && !mPaused)
    {
        //Pause the timer
        mPaused = true;

        //Calculate the paused ticks
        mPausedTicks = SDL_GetTicksNS() - mStartTicks;
        mStartTicks = 0;
    }
}

void LTimer::unpause()
{
    //If the timer is running and paused
    if (mStarted && mPaused)
    {
        //Unpause the timer
        mPaused = false;

        //Reset the starting ticks
        mStartTicks = SDL_GetTicksNS() - mPausedTicks;

        //Reset the paused ticks
        mPausedTicks = 0;
    }
}

Uint64 LTimer::getTicksNS()
{
    //The actual timer time
    Uint64 time{ 0 };

    //If the timer is running
    if (mStarted)
    {
        //If the timer is paused
        if (mPaused)
        {
            //Return the number of ticks when the timer was paused
            time = mPausedTicks;
        }
        else
        {
            //Return the current time minus the start time
            time = SDL_GetTicksNS() - mStartTicks;
        }
    }

    return time;
}

bool LTimer::isStarted()
{
    //Timer is running and paused or unpaused
    return mStarted;
}

bool LTimer::isPaused()
{
    //Timer is running and paused
    return mPaused && mStarted;
}

/* Function Implementations */
bool init()
{
    //Initialization flag
    bool success{ true };

    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) == false)
    {
        SDL_Log("SDL could not initialize! SDL error: %s\n", SDL_GetError());
        success = false;
    }
    else
    {
        //Create window with renderer
        if (SDL_CreateWindowAndRenderer("Tetoris", kScreenWidth, kScreenHeight, 0, &gWindow, &gRenderer) == false)
        {
            SDL_Log("Window could not be created! SDL error: %s\n", SDL_GetError());
            success = false;
        }
        else
        {
            //Initialize font loading
            if (TTF_Init() == false)
            {
                SDL_Log("SDL_ttf could not initialize! SDL_ttf error: %s\n", SDL_GetError());
                success = false;
            }
        }
    }

    return success;
}

bool loadMedia(LTexture& gTexture, std::string filepath)
{
    //File loading flag
    bool success{ true };

    //Load glocal assets
    if (gTexture.loadFromFile(filepath) == false)
    {
        SDL_Log("Unable to dot image!\n");
        success = false;
    }
    //Load scene font
    std::string fontPath{ "Tetris.ttf" };
    if (gFont = TTF_OpenFont(fontPath.c_str(), 28); gFont == nullptr)
    {
        SDL_Log("Could not load %s! SDL_ttf Error: %s\n", fontPath.c_str(), SDL_GetError());
        success = false;
    }
    else
    {
        const SDL_Color textColor{ 0x00, 0x00, 0x00, 0xFF };
        if (gGameOverText.loadFromRenderedText("Game over", textColor) == false)
        {
            SDL_Log("Could not load game over text texture %s! SDL_ttf Error: %s\n", fontPath.c_str(), SDL_GetError());
            success = false;
        }
    }

    return success;
}

void close()
{
    //Clean up textures
    gSquareTexture.destroy();
    gBorderTexture.destroy();

    //Free font
    TTF_CloseFont(gFont);
    gFont = nullptr;

    //Destroy window
    SDL_DestroyRenderer(gRenderer);
    gRenderer = nullptr;
    SDL_DestroyWindow(gWindow);
    gWindow = nullptr;

    //Quit SDL subsystems
    TTF_Quit();
    SDL_Quit();
}

bool checkCollision(SDL_Rect a, SDL_Rect b)
{
    //Calculate the sides of rect A
    int aMinX{ a.x };
    int aMaxX{ a.x + a.w };
    int aMinY{ a.y };
    int aMaxY{ a.y + a.h };

    //Calculate the sides of rect B
    int bMinX{ b.x };
    int bMaxX{ b.x + b.w };
    int bMinY{ b.y };
    int bMaxY{ b.y + b.h };

    //If left side of A is the the right of B
    if (aMinX >= bMaxX)
    {
        return false;
    }

    //If the right side of A to the left of B
    if (aMaxX <= bMinX)
    {
        return false;
    }

    //If the top side of A is below B
    if (aMinY >= bMaxY)
    {
        return false;
    }

    //If the bottom side of A is above B
    if (aMaxY <= bMinY)
    {
        return false;
    }

    //If none of the sides from A are outside B
    return true;
}

LTexture gTeto;
LTexture gSquareTexture;
LTexture gBorderTexture;
LTexture gSquareRed;
LTexture gSquareGreen;
LTexture gSquareBlue;
LTexture gGameOverText;