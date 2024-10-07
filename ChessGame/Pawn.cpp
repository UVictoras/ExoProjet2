#include "pch.h"
#include "Pawn.h"

bool Pawn::IsMoveValid(int pos)
{
    int diff = m_pos - pos;
    int direction = (m_color == White) ? 1 : -1;

    if (diff != 8 * direction &&
        diff != 7 * direction &&
        diff != 9 * direction &&
        !(diff == 16 * direction && !m_hasMoved))
        return false;

    if ((diff == 8 * direction || (diff == 16 * direction && !m_hasMoved)) &&
        board.m_cases[m_pos - 8 * direction] != nullptr)
        return false;

    if (diff == 16 * direction &&
        (board.m_cases[m_pos - 8 * direction] != nullptr ||
            board.m_cases[m_pos - 16 * direction] != nullptr))
        return false;

    if ((diff == 7 * direction || diff == 9 * direction) &&
        (board.m_cases[m_pos - diff] == nullptr ||
            board.m_cases[m_pos - diff]->m_color == m_color))
        return false;

    return true;
}

bool Pawn::Move(int pos)
{
    if (!IsMoveValid(pos))
    {
        return false;
    }

    if (abs(m_pos - pos) == 7 || abs(m_pos - pos) == 9) 
    {
        int targetPos = m_pos + ((m_color == White) ? -8 : 8);
        if (board.m_cases[targetPos] != nullptr &&
            board.m_cases[targetPos]->IsPawn() &&
            board.m_cases[targetPos]->m_color != m_color &&
            !board.m_cases[targetPos]->m_hasMoved)
        {
            board.m_cases[targetPos] = nullptr;
        }
    }

    board.m_cases[m_pos] = nullptr;
    m_pos = pos;
    board.m_cases[m_pos] = this;
    m_hasMoved = true;

    return true;
}