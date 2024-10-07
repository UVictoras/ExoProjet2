#include "pch.h"
#include "Pawn.h"

bool Pawn::IsMoveValid(int pos)
{
    if (m_color == White)
    {
        if (board.m_cases[m_pos - 8] != nullptr)
        {
            return false;
        }

        if (board.m_cases[m_pos - 7] == nullptr || board.m_cases[m_pos - 9] == nullptr)
        {
            return false;
        }

        if (board.m_cases[m_pos - 7]->m_color == m_color || board.m_cases[m_pos - 9]->m_color == m_color)
        {
            return false;
        }
    }
    else
    {
        if (board.m_cases[m_pos + 8] != nullptr)
        {
            return false;
        }

        if (board.m_cases[m_pos + 7] == nullptr || board.m_cases[m_pos + 9] == nullptr)
        {
            return false;
        }

        if (board.m_cases[m_pos + 7]->m_color == m_color || board.m_cases[m_pos + 9]->m_color == m_color)
        {
            return false;
        }
    }

    return true;
}

bool Pawn::Move(int pos) 
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