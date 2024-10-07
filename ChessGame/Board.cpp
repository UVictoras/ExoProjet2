#include "pch.h"
#include "Board.h"

void Board::InitializeBoard()
{
    std::fill(std::begin(m_cases), std::end(m_cases), nullptr);
    InitializeBlackPieces();
    InitializeWhitePieces();
}

void Board::InitializeBlackPieces()
{
    for (int i = 0; i < 16; i++)
    {
        Piece* piece = nullptr;
        char inGameChar;
        int position = i;

        if (i == 0 || i == 7) { inGameChar = 'R'; piece = new Rook(); }
        else if (i == 1 || i == 6) { inGameChar = 'N'; piece = new Knight(); }
        else if (i == 2 || i == 5) { inGameChar = 'B'; piece = new Bishop(); }
        else if (i == 3) { inGameChar = 'Q'; piece = new Queen(); }
        else if (i == 4) { inGameChar = 'K'; piece = new King(); }
        else { inGameChar = 'P'; piece = new Pawn(); }

        piece->InitializePiece(position, inGameChar, Black);
        m_cases[position] = piece;
    }
}

void Board::InitializeWhitePieces()
{
    Piece* piece = nullptr;
    char inGameChar;
    int position;

    for (int i = 0; i < 16; i++)
    {
        position = i + 48;

        if (i < 8) { inGameChar = 'P'; piece = new Pawn(); }
        else if (i == 8 || i == 15) { inGameChar = 'R'; piece = new Rook(); }
        else if (i == 9 || i == 14) { inGameChar = 'N'; piece = new Knight(); }
        else if (i == 10 || i == 13) { inGameChar = 'B'; piece = new Bishop(); }
        else if (i == 11) { inGameChar = 'Q'; piece = new Queen(); }
        else { inGameChar = 'K'; piece = new King(); }

        piece->InitializePiece(position, inGameChar, White);
        m_cases[position] = piece;
    }
}

void Board::PrintBoard()
{
    std::cout << "\33[37m    A   B   C   D   E   F   G   H\n";
    std::cout << "\33[90m  +---+---+---+---+---+---+---+---+\n";

    for (int i = 0; i < 64; i++)
    {
        bool isEvenRow = (i / 8) % 2 == 0;
        bool isEvenCol = (i % 8) % 2 == 0;
        bool isBeigeSquare = (isEvenRow && isEvenCol) || (!isEvenRow && !isEvenCol);

        if (i % 8 == 0)
        {
            std::cout << "\33[37m" << i / 8 + 1 << " |";
        }

        std::cout << (isBeigeSquare ? "\33[48;2;139;0;0m" : "\33[40m");

        if (m_cases[i] == nullptr)
        {
            std::cout << "   ";
            std::cout << "\33[40m" << "\33[90m" << "|";
        }
        else
        {
            std::cout << (m_cases[i]->m_color == White ? "\33[37m" : "\33[96m")
                << " " << m_cases[i]->m_inGameChar << " ";
            std::cout << "\33[40m" << "\33[90m" << "|";
        }

        if ((i + 1) % 8 == 0)
        {
            std::cout << "\n\33[90m  +---+---+---+---+---+---+---+---+\n";
        }
    }
    std::cout << "\33[37m\n";
}

bool Board::IsMinorPiece(Piece* piece)
{
    return reinterpret_cast<Knight*>(piece) != nullptr || reinterpret_cast<Bishop*>(piece) != nullptr;
}

bool Board::IsCheckmate(Color playerColor)
{
    King* king = nullptr;
    int kingPos = -1;

    for (int i = 0; i < 64; i++)
    {
        if (m_cases[i] != nullptr && m_cases[i]->m_color == playerColor)
        {
            king = dynamic_cast<King*>(m_cases[i]);
            if (king != nullptr)
            {
                kingPos = i;
                break;
            }
        }
    }

    if (king == nullptr)
        return false;

    if (!king->IsUnderAttack(kingPos / 8, kingPos % 8))
        return false;

    for (int i = 0; i < 64; i++)
    {
        Piece* piece = m_cases[i];
        if (piece != nullptr && piece->m_color == playerColor)
        {
            std::vector<int> possibleMoves = piece->GetPossibleMoves();
            for (int targetPos : possibleMoves)
            {
                Piece* capturedPiece = m_cases[targetPos];
                piece->Move(targetPos);

                if (!king->IsUnderAttack(kingPos / 8, kingPos % 8))
                {
                    piece->Move(i); 
                    m_cases[targetPos] = capturedPiece;
                    return false;
                }

                piece->Move(i);
                m_cases[targetPos] = capturedPiece;
            }
        }
    }

    return true;
}


bool Board::IsStalemate(Color playerColor)
{
    King* king = nullptr;
    int kingPos = -1;

    for (int i = 0; i < 64; i++)
    {
        if (m_cases[i] != nullptr && m_cases[i]->m_color == playerColor)
        {
            king = dynamic_cast<King*>(m_cases[i]);
            if (king != nullptr)
            {
                kingPos = i;
                break;
            }
        }
    }

    if (king == nullptr)
        return false; 

    if (king->IsUnderAttack(kingPos / 8, kingPos % 8))
        return false;

    for (int i = 0; i < 64; i++)
    {
        Piece* piece = m_cases[i];
        if (piece != nullptr && piece->m_color == playerColor)
        {
            std::vector<int> possibleMoves = piece->GetPossibleMoves();
            for (int targetPos : possibleMoves)
            {
                Piece* capturedPiece = m_cases[targetPos];
                piece->Move(targetPos);

                if (!king->IsUnderAttack(kingPos / 8, kingPos % 8))
                {
                    piece->Move(i);
                    m_cases[targetPos] = capturedPiece; 
                    return false;
                }

                piece->Move(i);
                m_cases[targetPos] = capturedPiece;
            }
        }
    }

    return true; 
}


bool Board::IsInsufficientMaterial()
{
    int whitePieces = 0, blackPieces = 0;
    bool whiteHasMinorPiece = false, blackHasMinorPiece = false;

    for (int i = 0; i < 64; i++)
    {
        if (m_cases[i] != nullptr)
        {
            if (m_cases[i]->m_color == White)
            {
                whitePieces++;
                if (IsMinorPiece(m_cases[i])) whiteHasMinorPiece = true;
            }
            else
            {
                blackPieces++;
                if (IsMinorPiece(m_cases[i])) blackHasMinorPiece = true;
            }
        }
    }

    if ((whitePieces == 1 && blackPieces == 1) ||
        (whitePieces == 2 && whiteHasMinorPiece && blackPieces == 1) ||
        (blackPieces == 2 && blackHasMinorPiece && whitePieces == 1))
    {
        return true;
    }

    return false;
}

bool Board::operator==(const Board& other) const
{
    for (int i = 0; i < 64; i++)
    {
        Piece* thisPiece = m_cases[i];
        Piece* otherPiece = other.m_cases[i];

        if ((thisPiece == nullptr && otherPiece != nullptr) ||
            (thisPiece != nullptr && otherPiece == nullptr))
        {
            return false;
        }

        if (thisPiece != nullptr && otherPiece != nullptr)
        {
            if (thisPiece->m_inGameChar != otherPiece->m_inGameChar ||
                thisPiece->m_color != otherPiece->m_color)
            {
                return false;
            }
        }
    }
    return true;
}

bool Board::IsThreefoldRepetition()
{
    int count = 0;

    for (const auto& previousBoardState : gameHistory)
    {
        if (board == previousBoardState)
        {
            count++;
        }
    }

    return count >= 3;
}

bool Board::IsFiftyMoveRule()
{
    return halfMoveClock >= 50;
}
