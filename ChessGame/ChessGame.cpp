#include "pch.h"
#include <iostream>
#include <vector>
#include <string>

Board board;

std::vector<Board> gameHistory;  
int halfMoveClock = 0;  

int ConvertChessNotationToIndex(const std::string& position)
{
    if (position.length() != 2)
        return -1;

    char column = position[0];
    char row = position[1];

    if (column < 'A' || column > 'H' || row < '1' || row > '8')
        return -1;

    int colIndex = column - 'A';
    int rowIndex = row - '1';
    return rowIndex * 8 + colIndex;
}

int main()
{
    board.InitializeBoard();
    Color currentPlayer = White;

    std::string startPosStr, targetPosStr; 
    int startPos;
    int targetPos; 

    Piece* piece;

    while (true)
    {
        board.PrintBoard();
        std::cout << (currentPlayer == White ? "White's turn" : "Black's turn") << std::endl;

        startPosStr, targetPosStr;
        std::cout << "Enter move (startPos targetPos, e.g., A2 A3): ";
        std::cin >> startPosStr >> targetPosStr;
        std::cout << std::endl;

        startPos = ConvertChessNotationToIndex(startPosStr);
        targetPos = ConvertChessNotationToIndex(targetPosStr);

        if (startPos == -1 || targetPos == -1)
        {
            std::cout << "Invalid input. Try again." << std::endl;
            continue;
        }

        piece = board.m_cases[startPos];
        if (piece == nullptr || piece->m_color != currentPlayer)
        {
            std::cout << "Invalid move. Try again." << std::endl;
            continue;
        }

        if (piece->IsMoveValid(targetPos))
        {
            if (Pawn* pawn = dynamic_cast<Pawn*>(piece))
            {
                pawn->Move(targetPos);
            }
            else if (Knight* knight = dynamic_cast<Knight*>(piece))
            {
                knight->Move(targetPos);
            }
            else if (Bishop* bishop = dynamic_cast<Bishop*>(piece))
            {
                bishop->Move(targetPos);
            }
            else if (Rook* rook = dynamic_cast<Rook*>(piece))
            {
                rook->Move(targetPos);
            }
            else if (Queen* queen = dynamic_cast<Queen*>(piece))
            {
                queen->Move(targetPos);
            }
            else if (King* king = dynamic_cast<King*>(piece))
            {
                king->Move(targetPos);
            }

            currentPlayer = (currentPlayer == White) ? Black : White;
            halfMoveClock++;  

            gameHistory.push_back(board);
        }
        else
        {
            std::cout << "Invalid move. Try again." << std::endl;
        }

        if (board.IsCheckmate(currentPlayer))
        {
            std::cout << (currentPlayer == White ? "Black wins by checkmate!" : "White wins by checkmate!") << std::endl;
            break;
        }
        else if (board.IsStalemate(currentPlayer))
        {
            std::cout << "The game is a draw by stalemate!" << std::endl;
            break;
        }
        else if (board.IsInsufficientMaterial())
        {
            std::cout << "The game is a draw by insufficient material!" << std::endl;
            break;
        }
        else if (board.IsThreefoldRepetition())
        {
            std::cout << "The game is a draw by threefold repetition!" << std::endl;
            break;
        }
        else if (board.IsFiftyMoveRule())
        {
            std::cout << "The game is a draw by the 50-move rule!" << std::endl;
            break;
        }
    }

    return 0;
}