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
};