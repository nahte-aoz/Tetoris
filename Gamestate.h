#pragma once

#include "SDLIO.h"
#include <string>

class GameState
{
public:
    //State transitions
    virtual bool enter() = 0;
    virtual bool exit() = 0;

    //Main loop functions
    virtual void handleEvent(SDL_Event& e) = 0;
    virtual void update() = 0;
    virtual void render() = 0;

    //Make sure to call child destructors
    virtual ~GameState() = default;
};

class IntroState : public GameState
{
public:
    //Static accessor
    static IntroState* get();

    //Transitions
    bool enter() override;
    bool exit() override;

    //Main loop functions
    void handleEvent(SDL_Event& e) override;
    void update() override;
    void render() override;

private:
    //Static instance
    static IntroState sIntroState;

    //Private constructor
    IntroState();

    //Intro background
    LTexture mBackgroundTexture;

    //Intro message
    LTexture mMessageTexture;
};


class TitleState : public GameState
{
public:
    //Static accessor
    static TitleState* get();

    //Transitions
    bool enter() override;
    bool exit() override;

    //Main loop functions
    void handleEvent(SDL_Event& e) override;
    void update() override;
    void render() override;

private:
    //Static instance
    static TitleState sTitleState;

    //Private constructor
    TitleState();

    //Intro background
    LTexture mBackgroundTexture;

    //Intro message
    LTexture mMessageTexture;
};

class ExitState : public GameState
{
public:
    //Static accessor
    static ExitState* get();

    //Transitions
    bool enter() override;
    bool exit() override;

    //Main loop functions
    void handleEvent(SDL_Event& e) override;
    void update() override;
    void render() override;

private:
    //Static instance
    static ExitState sExitState;

    //Private constructor
    ExitState();
};

class OverWorldState : public GameState
{
public:
    //Static accessor
    static OverWorldState* get();

    //Transitions
    bool enter() override;
    bool exit() override;

    //Main loop functions
    void handleEvent(SDL_Event& e) override;
    void update() override;
    void render() override;

private:
    //Level dimensions
    static constexpr int kLevelWidth = kScreenWidth * 2;
    static constexpr int kLevelHeight = kScreenHeight * 2;

    //Static instance
    static OverWorldState sOverWorldState;

    //Private constructor
    OverWorldState();

    //Overworld textures
    LTexture mBackgroundTexture;
    LTexture mRedHouseTexture;
    LTexture mBlueHouseTexture;

    //Game objects
};