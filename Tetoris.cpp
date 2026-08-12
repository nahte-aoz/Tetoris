/* Welcome to Tetoris! */

#include <SDL3/SDL_main.h>
#include "SDLIO.h"
#include "Constants.h"
#include "Globals.h"
#include "Pieces.h"
#include "Board.h"
#include "Game.h"

int main(int argc, char* args[])
{
    //Final exit code
    int exitCode{ 0 };

    //Initialize
    if (init() == false)
    {
        SDL_Log("Unable to initialize program!\n");
        exitCode = 1;
    }
    else
    {
        //Load media
        if (loadMedia(gSquareTexture, "Square.png") == false || loadMedia(gBorderTexture, "SquareBorder.png") == false || loadMedia(gTeto, "tetoris.jpg") == false
          || loadMedia(gSquareRed, "SquareRed.png") == false || loadMedia(gSquareGreen, "SquareGreen.png") == false || loadMedia (gSquareBlue, "SquareBlue.png") == false)
        {
            SDL_Log("Unable to load media!\n");
            exitCode = 2;
        }
        else
        {
            //The quit flag
            bool quit{ false };

            //The event data
            SDL_Event e;
            SDL_zero(e);

            //Timer to cap frame rate
            LTimer capTimer;

            Game game{};

#ifdef _IOSTREAM_
            // Print board to console for testing
            for (int row{}; row < kBoardHeight; ++row) {
                for (int col{}; col < kBoardWidth; ++col) {
                    if (!game.getBoard()->isFreeBlock(col, row)) {
                        std::cout << '#';
                    }
                    else
                        std::cout << '.';
                }
                std::cout << '\n';
            }
            std::cout << '\n';
#endif

            int fps{ 0 };

            //The main loop
            while (quit == false)
            {
                //Start frame time
                capTimer.start();

                //Get event data
                while (SDL_PollEvent(&e) == true)
                {

                    game.handleEvent(&e);

                    //Exit on quit
                    if (e.type == SDL_EVENT_QUIT || e.key.key == SDLK_ESCAPE)
                    {
                        quit = true;
                    }
                        
                }

                // Drop block by 1 block every 800ms
                game.dropPiece(fps);

                // Delete possible cleared lines before rendering so the renderer doesn't register already cleared lines for unneccessary frames
                game.getBoard()->deletePossibleLines();
         
                //Fill the background
                SDL_SetRenderDrawColor(gRenderer, 0xB4, 0xB4, 0xB4, 0xFF);
                SDL_RenderClear(gRenderer);

                // Teto!
                gTeto.render(45, 215);

                game.renderPiece();
                game.renderBoard();
                if (game.getBoard()->isGameOver()) {
                    gGameOverText.render(240, kScreenHeight / 2);
                    quit = true;
                }

                //Update screen
                SDL_RenderPresent(gRenderer);

                //Cap frame rate
                constexpr Uint64 nsPerFrame = 1000000000 / kScreenFps;
                Uint64 frameNs{ capTimer.getTicksNS() };
                if (frameNs < nsPerFrame)
                {
                    SDL_DelayNS(nsPerFrame - frameNs);
                }

            }
        }
    }

    //Clean up
    close();

    return exitCode;
}