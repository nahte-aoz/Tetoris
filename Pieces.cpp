#include "Pieces.h"

Pieces* Pieces::get() {
	return &sPieces;
}

int Pieces::getBlockType(int piece, int rotation, int x, int y) { 
	return mPieces[piece][rotation][x][y];
}
int Pieces::getXInitialPosition(int piece, int rotation) {
	return mPiecesInitialPosition[piece][rotation][0];
}
int Pieces::getYInitialPosition(int piece, int rotation) {
	return mPiecesInitialPosition[piece][rotation][1];
}

Pieces Pieces::sPieces;

Pieces::Pieces() {}