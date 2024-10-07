#pragma once

#include "Piece.h"

class Queen : public Piece
{
public:

	Queen() { };
	~Queen() { };

	bool IsMoveValid(int pos) override;
	bool Move(int pos) override;
};