#include "pch.h"
#include <iostream>
#include <vector>
#include <string>

Board board;

std::vector<Board> gameHistory;
int halfMoveClock = 0;

#if defined(_DEMO)
int MAX_TURN = 4;
#else
int MAX_TURN = 50;
#endif

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
#if defined(_COMPLETE) || defined(_DEMO)
    board.InitializeBoard(' ');
#elif defined(_LIGHT)
    srand(time(NULL));
    char letters[3] = { 'R', 'N', 'B' };
    int random = rand() % 3;
    char pieceToReplace = letters[random];
    board.InitializeBoard(pieceToReplace);
#endif
    Color currentPlayer = White;
    Graphics graphics;

    std::string startPosStr, targetPosStr;
    int startPos;
    int targetPos;
    bool isValidMove = false;

    Piece* piece;

    while (true)
    {
        graphics.DrawBoard();
        std::cout << (currentPlayer == White ? "White's turn" : "Black's turn") << std::endl;

        std::cout << "Enter move (startPos e.g., A7): ";
        std::cin >> startPosStr;
        std::cout << std::endl;

        startPos = ConvertChessNotationToIndex(startPosStr);

        graphics.DrawBoard(startPos);
        std::cout << "Enter where you want to move : ";
        std::cin >> targetPosStr;

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

        if (piece->m_inGameChar == 'P')
        {
            Pawn* pawn = dynamic_cast<Pawn*>(piece);
            if (pawn->Move(targetPos)) isValidMove = true;
        }
        else if (piece->m_inGameChar == 'N')
        {
            Knight* knight = dynamic_cast<Knight*>(piece);
            if (knight->Move(targetPos)) isValidMove = true;
        }
        else if (piece->m_inGameChar == 'B')
        {
            Bishop* bishop = dynamic_cast<Bishop*>(piece);
            if (bishop->Move(targetPos)) isValidMove = true;
        }
        else if (piece->m_inGameChar == 'R')
        {
            Rook* rook = dynamic_cast<Rook*>(piece);
            if (rook->Move(targetPos)) isValidMove = true;
        }
        else if (piece->m_inGameChar == 'Q')
        {
            Queen* queen = dynamic_cast<Queen*>(piece);
            if (queen->Move(targetPos)) isValidMove = true;
        }
        else if (piece->m_inGameChar == 'K')
        {
            King* king = dynamic_cast<King*>(piece);
            if (king->Move(targetPos)) isValidMove = true;
        }

        if (isValidMove == true)
        {
            board.m_lastMove = targetPos;

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

        system("cls");
        isValidMove = false;
    }

    return 0;
}
