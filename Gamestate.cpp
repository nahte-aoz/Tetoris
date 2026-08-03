#include "Gamestate.h"

//IntoState Implementation
IntroState* IntroState::get()
{
    //Get static instance
    return &sIntroState;
}

bool IntroState::enter()
{
    //Loading success flag
    bool success = true;

    //Load background
    if (mBackgroundTexture.loadFromFile("19-state-machines/intro-bg.png") == false)
    {
        SDL_Log("Failed to intro background!\n");
        success = false;
    }

    //Load text
    SDL_Color textColor{ 0x00, 0x00, 0x00, 0xFF };
    if (mMessageTexture.loadFromRenderedText("Lazy Foo' Productions Presents...", textColor) == false)
    {
        SDL_Log("Failed to render intro text!\n");
        success = false;
    }

    return success;
}

bool IntroState::exit()
{
    //Free background and text
    mBackgroundTexture.destroy();
    mMessageTexture.destroy();

    return true;
}

void IntroState::handleEvent(SDL_Event& e)
{
    //If the user pressed enter
    if ((e.type == SDL_EVENT_KEY_DOWN) && (e.key.key == SDLK_RETURN))
    {
        //Move onto title state
        setNextState(TitleState::get());
    }
}

void IntroState::update()
{

}

void IntroState::render()
{
    //Show the background
    mBackgroundTexture.render(0, 0);

    //Show the message
    mMessageTexture.render((kScreenWidth - mMessageTexture.getWidth()) / 2.f, (kScreenHeight - mMessageTexture.getHeight()) / 2.f);
}

//Declare static instance
IntroState IntroState::sIntroState;

IntroState::IntroState()
{
    //No public instantiation
}


//TitleState Implementation
TitleState* TitleState::get()
{
    //Get static instance
    return &sTitleState;
}

bool TitleState::enter()
{
    //Loading success flag
    bool success = true;

    //Load background
    if (mBackgroundTexture.loadFromFile("19-state-machines/title-bg.png") == false)
    {
        SDL_Log("Failed to title background!\n");
        success = false;
    }

    //Load text
    SDL_Color textColor{ 0x00, 0x00, 0x00, 0xFF };
    if (mMessageTexture.loadFromRenderedText("A State Machine Demo", textColor) == false)
    {
        SDL_Log("Failed to render title text!\n");
        success = false;
    }

    return success;
}

bool TitleState::exit()
{
    //Free background and text
    mBackgroundTexture.destroy();
    mMessageTexture.destroy();

    return true;
}

void TitleState::handleEvent(SDL_Event& e)
{
    //If the user pressed enter
    if ((e.type == SDL_EVENT_KEY_DOWN) && (e.key.key == SDLK_RETURN))
    {
        //Move to overworld
        setNextState(OverWorldState::get());
    }
}

void TitleState::update()
{

}

void TitleState::render()
{
    //Show the background
    mBackgroundTexture.render(0, 0);

    //Show the message
    mMessageTexture.render((kScreenWidth - mMessageTexture.getWidth()) / 2.f, (kScreenHeight - mMessageTexture.getHeight()) / 2.f);
}

//Declare static instance
TitleState TitleState::sTitleState;

TitleState::TitleState()
{
    //No public instantiation
}

//Hollow exit state
ExitState* ExitState::get()
{
    return &sExitState;
}

bool ExitState::enter()
{
    return true;
}

bool ExitState::exit()
{
    return true;
}

void ExitState::handleEvent(SDL_Event& e)
{

}

void ExitState::update()
{

}

void ExitState::render()
{

}

ExitState ExitState::sExitState;

ExitState::ExitState()
{

}

//OverWorldState Implementation
OverWorldState* OverWorldState::get()
{
    //Get static instance
    return &sOverWorldState;
}

bool OverWorldState::enter()
{
    //Loading success flag
    bool success = true;

    //Load background
    if (mBackgroundTexture.loadFromFile("19-state-machines/green-overworld.png") == false)
    {
        SDL_Log("Failed to load overworld background!\n");
        success = false;
    }
  
    return success;
}

bool OverWorldState::exit()
{
    //Free textures
    mBackgroundTexture.destroy();
    mRedHouseTexture.destroy();
    mBlueHouseTexture.destroy();

    return true;
}

void OverWorldState::handleEvent(SDL_Event& e)
{
    //Handle dot input
    gDot.handleEvent(e);
}

void OverWorldState::update()
{
    //Move dot
    gDot.move(kLevelWidth, kLevelHeight);

    //On red house collision
    if (checkCollision(gDot.getCollider(), mRedHouse.getCollider()) == true)
    {
        //Got to red room
        setNextState(RedRoomState::get());
    }
    //On blue house collision
    else if (checkCollision(gDot.getCollider(), mBlueHouse.getCollider()) == true)
    {
        //Go to blue room
        setNextState(BlueRoomState::get());
    }
}

void OverWorldState::render()
{
    //Render background
    SDL_FRect bgClip{ static_cast<float>(camera.x), static_cast<float>(camera.y), static_cast<float>(camera.w), static_cast<float>(camera.h) };
    mBackgroundTexture.render(0, 0, &bgClip);

    //Render objects
    gDot.render(camera);
}

//Declare static instance
OverWorldState OverWorldState::sOverWorldState;

OverWorldState::OverWorldState()
{
    //No public instantiation
}

