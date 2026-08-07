#pragma once

#include "Board.h"
#include "Pieces.h"
#include "Random.h"
#include "SDLIO.h"

/* Constants */
constexpr int kBoardLimitLeft{ kBoardPosition - (kBlockSize * (kBoardWidth / 2)) };
constexpr int kBoardLimitRight{ kBoardPosition + (kBlockSize * (kBoardWidth / 2)) };
constexpr int kBoardLimitUp{ kScreenHeight - (kBlockSize * kBoardHeight) };

class Game
{
public:
	enum Colors {
		RED,
		GREEN,
		BLUE,
		MAX_COLORS,
	};

	Game();

	void createNewPiece();

	void renderPiece();

	void renderBoard();

	bool correctOutOfBounds(int newRotation);

	bool verticalRotationCheck(int newRotation);

	void handleEvent(SDL_Event *e);

	Board* getBoard();

	Pieces* getPieces();

	int mPosX, mPosY; // Position of the piece that is falling down
	int mPiece, mRotation; // Kind and rotation the piece that is falling down

private:

	Uint8 mColors[MAX_COLORS][MAX_COLORS]{
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