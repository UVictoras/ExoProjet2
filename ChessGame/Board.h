#pragma once
#include <iostream>
#include <vector>

#include "Piece.h"

class Board
{
public:
	Piece* m_cases[64];

	Board() { };
	~Board() { };

	void InitializeBoard();
	void InitializeBlackPieces();
	void InitializeWhitePieces();

	void PrintBoard();
	bool IsMinorPiece(Piece* piece);
	bool IsCheckmate(Color playerColor);
	bool IsStalemate(Color playerColor);
	bool IsInsufficientMaterial();
	bool operator==(const Board& other) const;
	bool IsThreefoldRepetition();
	bool IsFiftyMoveRule();
};