#pragma once

enum Color;

class Piece
{
public:
	int m_pos;

	char m_inGameChar;

	Color m_color;

	bool m_hasMoved;

	Piece() : m_pos(0), m_inGameChar(' '), m_color(), m_hasMoved(false) { };
	~Piece() { };

	void InitializePiece(int pos, char inGameChar, Color color);
	virtual bool IsMoveValid(int pos);
	virtual bool Move(int pos);
	bool IsPawn() const;
	bool IsRook() const;
	virtual std::vector<int> GetPossibleMoves();
};