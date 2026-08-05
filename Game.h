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
	enum Colors {
		red,
		green,
		blue,
		maxColors,
	};

	Game();

	void createNewPiece();

	void renderPiece();

	void renderBoard();

	Board* getBoard();

	Pieces* getPieces();

	int mPosX, mPosY; // Position of the piece that is falling down
	int mPiece, mRotation; // Kind and rotation the piece that is falling down

private:

	Uint8 mColors[maxColors][maxColors]{
		/* Red */   {0x9F, 0x00, 0x00},
		/* Green */ {0x00, 0x9F, 0x00},
		/* Blue */  {0x00, 0x00, 0x9F}
	};

	int mNextPosX, mNextPosY; // Position of the next piece
	int mNextPiece, mNextRotation; // Kind and rotation of the next piece

	//Used to set color of the piece if it's a new piece
	bool mNewPiece;
	int mPieceColor;

	Board* mBoard{ Board::get() };
	Pieces* mPieces{ Pieces::get() };

	void initGame();
};