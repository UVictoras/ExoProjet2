#pragma once

#include "Piece.h"

class Knight : public Piece
{
public:

	Knight() { };
	~Knight() { };

	bool IsMoveValid(int pos) override;
	bool Move(int pos) override;
};