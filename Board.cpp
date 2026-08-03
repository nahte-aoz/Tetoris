#include "Board.h"
#include <cassert>

Board* Board::get() {
	return &sBoard;
}

bool Board::isFreeBlock(int x, int y) const {
	return mBoard[x][y] == POS_FREE;
}

bool Board::isPossibleMovement(int piece, int rotation, int x, int y) const {
	for (int boardX = x, piecesRowIndex{ 0 }; boardX < x + mPieceBlocks; ++boardX, ++piecesRowIndex) {
		for (int boardY = y, piecesColIndex{ 0 }; boardY < y + mPieceBlocks; ++boardY, ++piecesColIndex) {
			if (boardX < 0 || boardX > kBoardWidth || boardY > kBoardHeight) {
				if (mPieces->getBlockType(piece, rotation, piecesColIndex, piecesRowIndex) != 0)
					return false;
			}
			if (boardY >= 0) {
				if (mPieces->getBlockType(piece, rotation, piecesColIndex, piecesRowIndex) != 0 && !isFreeBlock(boardX, boardY)) {
					return false;
				}
			}
		}
	}

	return true;
}

void Board::storePiece(int piece, int rotation, int x, int y) {
	assert(piece < 7 && "Piece type index bigger than number of types!");
	assert(rotation < 4 && "Rotation index bigger than number of rotations!");

	for (int boardX = x, piecesRowIndex{ 0 }; boardX < x + mPieceBlocks; ++boardX, ++piecesRowIndex) {
		for (int boardY = y, piecesColIndex{ 0 }; boardY < y + mPieceBlocks; ++boardY, ++piecesColIndex) {
			if (mPieces->getBlockType(piece, rotation, piecesColIndex, piecesRowIndex) != 0)
				mBoard[boardX][boardY] = POS_FILLED;
		}
	}
}

void Board::deletePossibleLines() {
	for (int boardY{ 0 }; boardY < kBoardHeight; ++boardY) {
		int boardX{};
		while (boardX < kBoardWidth) {
			if (mBoard[boardX][boardY] != POS_FILLED) break;
			++boardX;
		}

		if (boardX == kBoardWidth) Board::deleteLine(boardY);
	}
}

bool Board::isGameOver() const {
	for (int boardX = 0; boardX < kBoardWidth; boardX++) {
		if (mBoard[boardX][0] == POS_FILLED)
			return true;
	}

	return false;
}

int Board::getXPosInPixels(int blockX) const {
	return ((kBoardPosition - (kBlockSize * (kBoardWidth / 2))) + (blockX * kBlockSize));
}

int Board::getYPosInPixels(int blockY) const {
	return ((kScreenHeight - (kBoardHeight * kBlockSize)) + (blockY * kBlockSize));
}

void Board::initBoard() {
	for (int boardX{}; boardX < kBoardWidth; ++boardX) {
		for (int boardY{}; boardY < kBoardHeight; ++boardY) {
			mBoard[boardX][boardY] = POS_FREE;
		}
	}
}

void Board::deleteLine(int y) {
	for (int boardY =  y ; boardY > 0; ++boardY) {
		for (int boardX{}; boardX < kBoardWidth; ++boardX) {
			mBoard[boardX][boardY] = mBoard[boardX][boardY - 1];
		}
	}
}

Board Board::sBoard{};

Board::Board() { Board::initBoard(); }