#include "Pieces.h"

Pieces* Pieces::get() {
	return &sPieces;
}

int Pieces::getBlockType(int piece, int rotation, int x, int y) const { 
	return mPieces[piece][rotation][x][y];
}
int Pieces::getXInitialPosition(int piece, int rotation) const {
	return mPiecesInitialPosition[piece][rotation][0];
}

int Pieces::findTopRow(int piece, int rotation) const {
    for (int row = 0; row < kRow; ++row)
        for (int col = 0; col < kCol; ++col)
            if (mPieces[piece][rotation][row][col] != 0)
                return row;
    return 0; // every rotation has at least one filled cell, so this shouldn't hit
}

int Pieces::getYInitialPosition(int piece, int rotation) const {
	return -findTopRow(piece, rotation);
}

Pieces Pieces::sPieces;

Pieces::Pieces() {}