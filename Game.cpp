#include "Game.h"

void Game::createNewPiece() {
	mPiece = mNextPiece;
	mRotation = mNextRotation;
	mPosX = (kBoardWidth / 2) + mPieces->getXInitialPosition(mPiece, mRotation);
	mPosY = mPieces->getYInitialPosition(mPiece, mRotation);

	mNextPiece = Random::get(0, 6);
	mNextRotation = Random::get(0, 3);

    mNewPiece = true;
}

void Game::renderPiece() {

    // Set color based off piece type
    if (mPiece == Pieces::SQUARE_BLOCK  || mPiece == Pieces::L_REVERSE || mPiece == Pieces::T_BLOCK)
        mPieceColor = RED;
    else if (mPiece == Pieces::I_BLOCK || mPiece == Pieces::N_BLOCK)
        mPieceColor = GREEN;
    else if (mPiece == Pieces::L_BLOCK || mPiece == Pieces::N_REVERSE)
        mPieceColor = BLUE;

    // Only set color if it's a new piece
    if (mNewPiece) {
        gSquareTexture.setColor(mColors[mPieceColor][RED], mColors[mPieceColor][GREEN], mColors[mPieceColor][BLUE]);
        mNewPiece = false;
    }

    int squareX{};
    int squareY{};

    for (int col{}; col < kCol; ++col) {
        for (int row{}; row < kRow; ++row) {
            if (mPieces->getBlockType(mPiece, mRotation, row, col) != 0) {
                squareX = mBoard->getXPosInPixels(mPosX + col);
                squareY = mBoard->getYPosInPixels(mPosY + row);

                gSquareTexture.render(static_cast<float>(squareX), static_cast<float>(squareY), nullptr, kBlockSize, kBlockSize);
            }
        }

    }

}

void Game::renderBoard() {

    int rectX{ mBoard->getXPosInPixels(-1) };
    int rectY{ mBoard->getYPosInPixels(0) };

    // Set colors for all the texture
    gBorderTexture.setColor(0x0F, 0x0F, 0x0F);
    gSquareRed.setColor(mColors[RED][RED], mColors[RED][GREEN], mColors[RED][BLUE]);
    gSquareGreen.setColor(mColors[GREEN][RED], mColors[GREEN][GREEN], mColors[GREEN][BLUE]);
    gSquareBlue.setColor(mColors[BLUE][RED], mColors[BLUE][GREEN], mColors[BLUE][BLUE]);

    // Render the outline of the board
    while (rectY < mBoard->getYPosInPixels(kBoardHeight)) {
        gBorderTexture.render(static_cast<float>(rectX), static_cast<float>(rectY), nullptr, kBlockSize, kBlockSize);
        rectX = mBoard->getXPosInPixels(kBoardWidth);
        gBorderTexture.render(static_cast<float>(rectX), static_cast<float>(rectY), nullptr, kBlockSize, kBlockSize);
        rectX = mBoard->getXPosInPixels(-1);
        rectY += 1;
    }
    rectY = mBoard->getYPosInPixels(kBoardHeight);
    while (rectX <= mBoard->getXPosInPixels(kBoardWidth)) {
        gBorderTexture.render(static_cast<float>(rectX), static_cast<float>(rectY), nullptr, kBlockSize, kBlockSize);
        rectX += 1;
    }

    // Render any pieces that are stored in the board
    for (int row{}; row < kBoardHeight; ++row) {
        for (int col{}; col < kBoardWidth; ++col) {
            if (!getBoard()->isFreeBlock(col, row)) {
                rectX = mBoard->getXPosInPixels(col);
                rectY = mBoard->getYPosInPixels(row);

                if (mBoard->indexBoard(col, row) == Pieces::SQUARE_BLOCK || mBoard->indexBoard(col, row) == Pieces::L_REVERSE || mBoard->indexBoard(col, row) == Pieces::T_BLOCK)
                    gSquareRed.render(static_cast<float>(rectX), static_cast<float>(rectY), nullptr, kBlockSize, kBlockSize);
                else if (mBoard->indexBoard(col, row) == Pieces::I_BLOCK || mBoard->indexBoard(col, row) == Pieces::N_BLOCK)
                    gSquareGreen.render(static_cast<float>(rectX), static_cast<float>(rectY), nullptr, kBlockSize, kBlockSize);
                else if (mBoard->indexBoard(col, row) == Pieces::L_BLOCK || mBoard->indexBoard(col, row) == Pieces::N_REVERSE)
                    gSquareBlue.render(static_cast<float>(rectX), static_cast<float>(rectY), nullptr, kBlockSize, kBlockSize);
            }

        }

    }

    // Render the next piece
    int squareX{};
    int squareY{};
    for (int col{}; col < kCol; ++col) {
        for (int row{}; row < kRow; ++row) {
            if (mPieces->getBlockType(mNextPiece, mNextRotation, row, col) != 0) {
                squareX = mBoard->getXPosInPixels(mNextPosX + col);
                squareY = mBoard->getYPosInPixels(mNextPosY + row);

                if (mNextPiece == Pieces::SQUARE_BLOCK || mNextPiece == Pieces::L_REVERSE || mNextPiece == Pieces::T_BLOCK)
                    gSquareRed.render(static_cast<float>(squareX), static_cast<float>(squareY), nullptr, kBlockSize, kBlockSize);
                else if (mNextPiece == Pieces::I_BLOCK || mNextPiece == Pieces::N_BLOCK)
                    gSquareGreen.render(static_cast<float>(squareX), static_cast<float>(squareY), nullptr, kBlockSize, kBlockSize);
                else if (mNextPiece == Pieces::L_BLOCK || mNextPiece == Pieces::N_REVERSE)
                    gSquareBlue.render(static_cast<float>(squareX), static_cast<float>(squareY), nullptr, kBlockSize, kBlockSize);
            }
        }

    }
}

// If the piece rotates out of bounds, push it back in bounds in it's new rotation.
// Only accounts for rotation moves because user shouldn't be able to move a piece left or right
// out of bounds on their own.
bool Game::correctOutOfBounds(int newRotation) {
    int tempRotation{ newRotation };
    int tempPosX{ mPosX };
    int tempPosY{ mPosY };

    int corrections{};
    while (!mBoard->isPossibleMovement(mPiece, tempRotation, tempPosX, tempPosY)) {
        if (tempPosX > kBoardWidth)
            --tempPosX;
        else if (mPosX < 0)
            ++tempPosX;


        ++corrections;
        if (corrections >= 5)
            return false;
    }

    mRotation = tempRotation;
    mPosX = tempPosX;
    mPosY = tempPosY;
    return true;
}

void Game::handleEvent(SDL_Event *e) {
    if (e->type == SDL_EVENT_KEY_DOWN && e->key.repeat == 0)
    {
        switch (e->key.key) {
        case SDLK_DOWN:
        {
            if (!mBoard->isPossibleMovement(mPiece, mRotation, mPosX, mPosY + 1)) break;
            mPosY += 1; break;
        }
        case SDLK_LEFT:
        {
            if (!mBoard->isPossibleMovement(mPiece, mRotation, mPosX - 1, mPosY)) break;
            mPosX -= 1; break;
        }
        case SDLK_RIGHT:
        {
            if (!mBoard->isPossibleMovement(mPiece, mRotation, mPosX + 1, mPosY)) break;
            mPosX += 1; break;
        }
        case SDLK_X:
        {
            if (mRotation + 1 < kRotation) {
                if (!correctOutOfBounds(mRotation + 1)) break;
                break;
            }
            else {
                if (!correctOutOfBounds(0)) break;
                break;
            }
        }
        case SDLK_Z:
        {
            while (true) {
                if (mBoard->isPossibleMovement(mPiece, mRotation, mPosX, mPosY + 1)) {
                    ++mPosY;
                }
                else if (!mBoard->isPossibleMovement(mPiece, mRotation, mPosX, mPosY + 1)) {
                    mBoard->storePiece(mPiece, mRotation, mPosX, mPosY);
                    createNewPiece();
                    break;
                }
            }
        }
#ifdef _IOSTREAM_
        case SDLK_P: {
            getBoard()->storePiece(mPiece, mRotation, mPosX, mPosY);
            std::cout << "Current block type: " << mPiece << '\n';
            std::cout << "Current rotation: " << mRotation << '\n';
            for (int row{}; row < kBoardHeight; ++row) {
                for (int col{}; col < kBoardWidth; ++col) {
                    if (!getBoard()->isFreeBlock(col, row)) {
                        std::cout << '#';
                    }
                    else
                        std::cout << '.';
                }
                std::cout << '\n';
            }

            std::cout << '\n';
        }
#endif
        }
    }
}

void Game::dropPiece(int& fps) {
    ++fps;
    if (fps == 52)
        if (mBoard->isPossibleMovement(mPiece, mRotation, mPosX, mPosY + 1))
            mPosY += 1;
        else {
            mBoard->storePiece(mPiece, mRotation, mPosX, mPosY);
            createNewPiece();
        }

    if (fps > 60)
        fps = 0;
}

Board* Game::getBoard() { return mBoard; }

Pieces* Game::getPieces() { return mPieces; }

void Game::initGame() {
	// Initial piece
	mPiece = Random::get(0, 6);
	mRotation = Random::get(0, 3);
	mPosX = (kBoardWidth / 2) + mPieces->getXInitialPosition(mPiece, mRotation);
	mPosY = mPieces->getYInitialPosition(mPiece, mRotation);

	//Next piece
	mNextPiece = Random::get(0, 6);
	mNextRotation = Random::get(0, 3);
	mNextPosX = kBoardWidth + 5;
	mNextPosY = 5;

    mNewPiece = true;
}

Game::Game() {
	initGame();
}