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
    if (mPiece == 0 || mPiece == 3 || mPiece == 6)
        mPieceColor = 0;
    else if (mPiece == 1 || mPiece == 4)
        mPieceColor = 1;
    else if (mPiece == 2 || mPiece == 5)
        mPieceColor = 2;

    // Only set color if it's a new piece
    if (mNewPiece) {
        gSquareTexture.setColor(mColors[mPieceColor][red], mColors[mPieceColor][green], mColors[mPieceColor][blue]);
        mNewPiece = false;
    }

    // Hold the x, y, and indexes of the last square in the piece that was rendered
    // The x is initialized with the left pixels of the board + the initial starting point + one block to account for
    // me not being able to render the board precisely in the middle of the screen. Teehee
    int lastSquareX{ kBoardLimitLeft + (mPosX * kBlockSize) + kBlockSize };
    int lastSquareY{ kBoardLimitUp };
    int lastSquareRow{ 0 };
    int lastSquareCol{ 0 };

    for (int row{}; row < kRow; ++row) {
        for (int col{}; col < kCol; ++col) {
            if (mPieces->getBlockType(mPiece, mRotation, col, row) != 0) {
                if (row > lastSquareRow) {
                    lastSquareX += kBlockSize;
                }
                if (col > lastSquareCol) {
                    lastSquareY += kBlockSize;
                }

                lastSquareRow = row;
                lastSquareCol = col;


                gSquareTexture.render(static_cast<float>(lastSquareX), static_cast<float>(lastSquareY), nullptr, kBlockSize, kBlockSize);
            }
        }

        lastSquareRow = 0;
    }

}

void Game::renderBoard() {

    int rectX{ kBoardLimitLeft };
    int rectY{ kBoardLimitUp };

    gBorderTexture.setColor(0x0F, 0x0F, 0x0F);

    while (rectY < kScreenHeight - kBlockSize) {
        gBorderTexture.render(static_cast<float>(rectX), static_cast<float>(rectY), nullptr, kBlockSize, kBlockSize);
        rectX = kBoardLimitRight;
        gBorderTexture.render(static_cast<float>(rectX), static_cast<float>(rectY), nullptr, kBlockSize, kBlockSize);
        rectX = kBoardLimitLeft;
        rectY += kBlockSize;
    }

    rectY = kScreenHeight - kBlockSize;
    while (rectX <= kBoardLimitRight) {
        gBorderTexture.render(static_cast<float>(rectX), static_cast<float>(rectY), nullptr, kBlockSize, kBlockSize);
        rectX += kBlockSize;
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