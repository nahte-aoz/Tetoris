#pragma once

#include "Pieces.h"
#include "Constants.h"

/* Constants */
constexpr int kBoardWidth{ 10 };
constexpr int kBoardHeight{ 20 };
constexpr int kBoardLineWidth{ 6 }; // Width of each of the two lines that delimit the board
constexpr int kBoardPosition{ kScreenWidth / 2 };
constexpr int kBlockSize{ 32 };
constexpr int kMinVerticalMargin{ 20 };
constexpr int kMinHorizontalMargin{ 20 };
constexpr int mPieceBlocks{ 5 }; // Number of horizontal and vertical blocks of a matrix piece

// Board.h
class Board
{
public:

    static Board* get();

    bool isFreeBlock(int x, int y) const;

    // Would placing `piece` (in `rotation`) at board position (x, y)
    // collide with the walls, the floor, or an already-filled cell?
    bool isPossibleMovement(int piece, int rotation, int x, int y) const;

    // Bake the piece's filled cells into the board permanently.
    void storePiece(int piece, int rotation, int x, int y);

    // Find and remove any fully-filled rows, shifting everything above down.
    void deletePossibleLines();

    bool isGameOver() const;

    // Block coordinates -> pixel coordinates, for the renderer to use later.
    int getXPosInPixels(int blockX) const;
    int getYPosInPixels(int blockY) const;
    
    void initBoard();

    Board(const Board& board) = delete;
    Board& operator=(const Board& board) = delete;

    Board(Board&& board) = delete;
    Board& operator=(Board&& board) = delete;

    ~Board() = default;

private:
    static Board sBoard;

    Board();

    void deleteLine(int y);

    enum { POS_FREE, POS_FILLED };
    int mBoard[kBoardWidth][kBoardHeight];
    Pieces* mPieces{ Pieces::get() };
};