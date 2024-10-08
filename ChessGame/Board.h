#pragma once
#include <iostream>
#include <vector>

#include "Piece.h"

class Board
{
public:
	Piece* m_cases[64];
	int m_lastMove;

	Board() : m_lastMove(0) { };
	~Board() { };

	void InitializeBoard(char pieceToReplace);
	void InitializeBlackPieces(char pieceToReplace);
	void InitializeWhitePieces(char pieceToReplace);

	bool IsMinorPiece(Piece* piece);
	bool IsCheckmate(Color playerColor);
	bool IsStalemate(Color playerColor);
	bool IsInsufficientMaterial();
	bool operator==(const Board& other) const;
	bool IsThreefoldRepetition();
	bool IsFiftyMoveRule();
};