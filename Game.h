#pragma once

#include "Board.h"
#include "Pieces.h"
#include "Random.h"
#include "SDLIO.h"

/* Constants */
constexpr int kBoardLimitLeft{ kBoardPosition - (kBlockSize * (kBoardWidth / 2)) - 1 };
constexpr int kBoardLimitRight{ kBoardPosition + (kBlockSize * (kBoardWidth / 2)) - 1 };
constexpr int kBoardLimitUp{ kScreenHeight - (kBlockSize * kBoardHeight) };

class Game
{
public:

	Game();

	void createNewPiece();

	void renderPiece(int x, int y);

	Board* getBoard();

	Pieces* getPieces();

	int mPosX, mPosY; // Position of the piece that is falling down
	int mPiece, mRotation; // Kind and rotation the piece that is falling down

private:

	int mNextPosX, mNextPosY; // Position of the next piece
	int mNextPiece, mNextRotation; // Kind and rotation of the next piece

	Board* mBoard{ Board::get() };
	Pieces* mPieces{ Pieces::get() };

	void initGame();
};