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

    gBorderTexture.setColor(0x0F, 0x0F, 0x0F);

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

    for (int row{}; row < kBoardHeight; ++row) {
        for (int col{}; col < kBoardWidth; ++col) {
            if (!getBoard()->isFreeBlock(col, row)) {
                rectX = mBoard->getXPosInPixels(col);
                rectY = mBoard->getYPosInPixels(row);

                if (mBoard->indexBoard(col, row) == Pieces::SQUARE_BLOCK || mBoard->indexBoard(col, row) == Pieces::L_REVERSE || mBoard->indexBoard(col, row) == Pieces::T_BLOCK)
                {
                    gSquareRed.setColor(mColors[RED][RED], mColors[RED][GREEN], mColors[RED][BLUE]);
                    gSquareRed.render(static_cast<float>(rectX), static_cast<float>(rectY), nullptr, kBlockSize, kBlockSize);
                }
                else if (mBoard->indexBoard(col, row) == Pieces::I_BLOCK || mBoard->indexBoard(col, row) == Pieces::N_BLOCK)
                {
                    gSquareGreen.setColor(mColors[GREEN][RED], mColors[GREEN][GREEN], mColors[GREEN][BLUE]);
                    gSquareGreen.render(static_cast<float>(rectX), static_cast<float>(rectY), nullptr, kBlockSize, kBlockSize);
                }
                else if (mBoard->indexBoard(col, row) == Pieces::L_BLOCK || mBoard->indexBoard(col, row) == Pieces::N_REVERSE)
                {
                    gSquareBlue.setColor(mColors[BLUE][RED], mColors[BLUE][GREEN], mColors[BLUE][BLUE]);
                    gSquareBlue.render(static_cast<float>(rectX), static_cast<float>(rectY), nullptr, kBlockSize, kBlockSize);
                }
            }

        }

    }
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
}

Game::Game() {
	initGame();
}