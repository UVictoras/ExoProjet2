#include "pch.h"
#include "Graphics.h"

void Graphics::DrawBoard()
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
            std::cout << "\33[37m" << i / 8 + 1 <<  "\33[90m" << " |";
        }

        std::cout << (isBeigeSquare ? "\33[48;2;0;0;139m" : "\33[40m");

        if (board.m_cases[i] == nullptr)
        {
            std::cout << "   ";
            std::cout << "\33[40m" << "\33[90m" << "|";
        }
        else
        {
            std::cout << (board.m_cases[i]->m_color == White ? "\33[37m" : "\33[95m")
                << " " << board.m_cases[i]->m_inGameChar << " ";
            std::cout << "\33[40m" << "\33[90m" << "|";
        }

        if ((i + 1) % 8 == 0)
        {
            std::cout << "\n\33[90m  +---+---+---+---+---+---+---+---+\n";
        }
    }
    std::cout << "\33[37m\n";
}

void Graphics::DrawBoard(char piecePos)
{
    Piece* chosenPiece = board.m_cases[piecePos];
    chosenPiece->GetPossibleMoves();

    std::cout << "\33[37m    A   B   C   D   E   F   G   H\n";
    std::cout << "\33[90m  +---+---+---+---+---+---+---+---+\n";

    for (int i = 0; i < 64; i++)
    {
        bool isEvenRow = (i / 8) % 2 == 0;
        bool isEvenCol = (i % 8) % 2 == 0;
        bool isBeigeSquare = (isEvenRow && isEvenCol) || (!isEvenRow && !isEvenCol);

        if (i % 8 == 0)
        {
            std::cout << "\33[37m" << i / 8 + 1 << "\33[90m" << " |";
        }

        std::cout << (isBeigeSquare ? "\33[48;2;0;0;139m" : "\33[40m");

        if (std::find(std::begin(chosenPiece->m_possiblesMoves), std::end(chosenPiece->m_possiblesMoves), i) != std::end(chosenPiece->m_possiblesMoves))
        {
            if (board.m_cases[i] == nullptr) { std::cout << "\33[48;2;139;139;0m"; }
            else if (board.m_cases[i]->m_color != chosenPiece->m_color) { std::cout << "\33[48;2;139;0;0m"; }
        }
        if (i == piecePos) std::cout << "\33[48;2;0;139;0m";

        if (board.m_cases[i] == nullptr)
        {
            std::cout << "   ";
            std::cout << "\33[40m" << "\33[90m" << "|";
        }
        else
        {
            std::cout << (board.m_cases[i]->m_color == White ? "\33[37m" : "\33[95m")
                << " " << board.m_cases[i]->m_inGameChar << " ";
            std::cout << "\33[40m" << "\33[90m" << "|";
        }

        if ((i + 1) % 8 == 0)
        {
            std::cout << "\n\33[90m  +---+---+---+---+---+---+---+---+\n";
        }
    }
    std::cout << "\33[37m\n";
}