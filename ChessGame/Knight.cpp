#include "pch.h"
#include "Knight.h"

bool Knight::IsMoveValid(int pos)
{
    int currentRow = m_pos / 8; 
    int currentCol = m_pos % 8; 
    int targetRow = pos / 8;
    int targetCol = pos % 8;

    int rowDiff = abs(currentRow - targetRow);
    int colDiff = abs(currentCol - targetCol);

    if (!((rowDiff == 2 && colDiff == 1) || (rowDiff == 1 && colDiff == 2)))
        return false;

    if (board.m_cases[pos] != nullptr && board.m_cases[pos]->m_color == m_color)
        return false;

    return true;
}

bool Knight::Move(int pos)
{
    if (!IsMoveValid(pos))
    {
        return false;
    }

    board.m_cases[m_pos] = nullptr;

    m_pos = pos;
    board.m_cases[m_pos] = this;

    return true;
}