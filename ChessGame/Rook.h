#pragma once

#include "Piece.h"

class Rook : public Piece
{
public:

	Rook() { };
	~Rook() { };

	bool IsMoveValid(int pos) override;
	bool Move(int pos) override;
};