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

std::vector<int> Pawn::GetPossibleMoves()
{
    std::vector<int> moves;
    int direction = (m_color == White) ? -8 : 8;
    int forwardPos = m_pos + direction;

    if (board.m_cases[forwardPos] == nullptr)
    {
        moves.push_back(forwardPos);

        if ((m_color == White && m_pos >= 48 && m_pos <= 55) ||
            (m_color == Black && m_pos >= 8 && m_pos <= 15))
        {
            int doubleForwardPos = m_pos + (direction * 2);
            if (board.m_cases[doubleForwardPos] == nullptr)
            {
                moves.push_back(doubleForwardPos);
            }
        }
    }

    int captureLeft = m_pos + direction - 1;
    int captureRight = m_pos + direction + 1;

    if (captureLeft >= 0 && captureLeft < 64 && (m_pos % 8 != 0) &&
        board.m_cases[captureLeft] != nullptr && board.m_cases[captureLeft]->m_color != m_color)
    {
        moves.push_back(captureLeft);
    }

    if (captureRight >= 0 && captureRight < 64 && ((m_pos + 1) % 8 != 0) &&
        board.m_cases[captureRight] != nullptr && board.m_cases[captureRight]->m_color != m_color)
    {
        moves.push_back(captureRight);
    }

    return moves;
}
