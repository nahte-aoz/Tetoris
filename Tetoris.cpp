/* Welcome to Tetoris! */

#include <SDL3/SDL_main.h>
#include "SDLIO.h"
#include "Board.h"
#include "Constants.h"
#include "Globals.h"
#include "Pieces.h"
#include <iostream>

//int main(int argc, char* args[])
//{
//    //Final exit code
//    int exitCode{ 0 };
//
//    //Initialize
//    if (init() == false)
//    {
//        SDL_Log("Unable to initialize program!\n");
//        exitCode = 1;
//    }
//    else
//    {
//        //Load media
//        if (loadMedia() == false)
//        {
//            SDL_Log("Unable to load media!\n");
//            exitCode = 2;
//        }
//        else
//        {
//            //The quit flag
//            bool quit{ false };
//
//            //The event data
//            SDL_Event e;
//            SDL_zero(e);
//
//            //Timer to cap frame rate
//            LTimer capTimer;
//
//            //The main loop
//            while (quit == false)
//            {
//                //Start frame time
//                capTimer.start();
//
//                //Get event data
//                while (SDL_PollEvent(&e) == true)
//                {
//
//                    //Exit on quit
//                    if (e.type == SDL_EVENT_QUIT)
//                    {
//                        quit = true;
//                    }
//                }
//
//                //Fill the background
//                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
//                SDL_RenderClear(gRenderer);
//
//
//                //Update screen
//                SDL_RenderPresent(gRenderer);
//
//                //Cap frame rate
//                constexpr Uint64 nsPerFrame = 1000000000 / kScreenFps;
//                Uint64 frameNs{ capTimer.getTicksNS() };
//                if (frameNs < nsPerFrame)
//                {
//                    SDL_DelayNS(nsPerFrame - frameNs);
//                }
//            }
//        }
//    }
//
//    //Clean up
//    close();
//
//    return exitCode;
//}

/* Print pieces to console */
//int main(int argc, char* args[]) {
//	Pieces* pieces{ Pieces::get() };
//
//	for (int type{ }; type <= kType; ++type) {
//		for (int rotation{}; rotation <= kRotation; ++rotation) {
//			for (int row{}; row <= kRow - 1; ++row) {
//				for (int col{}; col <= kCol - 1; ++col) {
//					if (pieces->getBlockType(type, rotation, row, col) == 0) {
//						std::cout << '.';
//					}
//					if (pieces->getBlockType(type, rotation, row, col) == 1) {
//						std::cout << '#';
//					}
//					if (pieces->getBlockType(type, rotation, row, col) == 2) {
//						std::cout << '&';
//					}
//				}
//
//				std::cout << '\n';
//			}
//
//			std::cout << '\n';
//		}
//
//		std::cout << '\n';
//	}
//
//	return 0;
//}

/* Test Board */
int main(int argc, char* args[]) {
	Pieces* pieces{ Pieces::get() };
	Board* board{ Board::get() };

	if (board->isPossibleMovement(1, 0, 5, 5)) {
		board->storePiece(1, 0, 5, 5);
	}

	board->storePiece(0, 0, 0, 0);

	board->storePiece(3, 0, 5, 13);

	board->storePiece(6, 2, 0, 13);

	for (int y{}; y < kBoardHeight; ++y) {
		for (int x{}; x < kBoardWidth; ++x) {
			if (board->isFreeBlock(x, y)) {
				std::cout << '.';
			}
			if (!board->isFreeBlock(x, y)) {
				std::cout << '#';
			}
		}
		std::cout << '\n';
	}
	return 0;
}