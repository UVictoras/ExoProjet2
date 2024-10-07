#pragma once

enum Color;

class Piece
{
public:
	int m_pos;

	char m_inGameChar;

	Color m_color;

	Piece() : m_pos(0), m_inGameChar(' '), m_color() { };
	~Piece() { };

	void InitializePiece(int pos, char inGameChar, Color color);
	virtual bool IsMoveValid(int pos);
	virtual bool Move(int pos);
};