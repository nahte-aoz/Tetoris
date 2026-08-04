#include "Game.h"

void Game::createNewPiece() {
	mPiece = mNextPiece;
	mRotation = mNextRotation;
	mPosX = (kBoardWidth / 2) + mPieces->getXInitialPosition(mPiece, mRotation);
	mPosY = mPieces->getYInitialPosition(mPiece, mRotation);

	mNextPiece = Random::get(0, 6);
	mNextRotation = Random::get(0, 3);
}

void Game::renderPiece(int x, int y) {
    int lastSquareX{ x };
    int lastSquareY{ y };
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


                gSquareTexture.render(static_cast<float>(lastSquareX), static_cast<float>(lastSquareY));
            }
        }

        lastSquareRow = 0;
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