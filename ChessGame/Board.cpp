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
    for (int i = 0; i < 16; i++)
    {
        Piece* piece = nullptr;
        char inGameChar;
        int position = i + 48;

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
    std::cout << "   A B C D E F G H\n";
    std::cout << "\33[90m  p---------------q\n";

    for (int i = 0; i < 64; i++)
    {
        if (i % 8 == 0) std::cout << i / 8 << " ";
        std::cout << "\33[90m|";

        if (m_cases[i] == nullptr)
        {
            std::cout << " ";
        }
        else
        {
            std::cout << (m_cases[i]->m_color == White ? "\33[37m" : "\33[95m");
            std::cout << m_cases[i]->m_inGameChar;
        }

        if ((i + 1) % 8 == 0)
        {
            std::cout << "\33[90m|\n";
            if (i != 63) std::cout << "  |-+-+-+-+-+-+-+-|\n";
        }
    }
    std::cout << "\33[90m  b---------------d\n\n\33[37m";
}