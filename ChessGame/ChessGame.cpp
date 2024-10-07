#include "pch.h"
#include <iostream>

Board board; 

int main()
{
    board.InitializeBoard();
    board.PrintBoard();

    reinterpret_cast<Pawn*>(board.m_cases[48])->Move(32);
    board.PrintBoard();
    reinterpret_cast<Pawn*>(board.m_cases[32])->Move(16);
    board.PrintBoard();

    reinterpret_cast<Pawn*>(board.m_cases[51])->Move(43);
    board.PrintBoard();

    reinterpret_cast<Knight*>(board.m_cases[62])->Move(45); 
    board.PrintBoard();

    reinterpret_cast<Bishop*>(board.m_cases[58])->Move(23);  
    board.PrintBoard();
    reinterpret_cast<Bishop*>(board.m_cases[23])->Move(14); 
    board.PrintBoard();

    reinterpret_cast<Pawn*>(board.m_cases[52])->Move(44);
    board.PrintBoard();

    reinterpret_cast<Bishop*>(board.m_cases[61])->Move(52);
    board.PrintBoard();
    
    reinterpret_cast<Rook*>(board.m_cases[56])->Move(40);
    board.PrintBoard();

    reinterpret_cast<King*>(board.m_cases[60])->Move(62);
    board.PrintBoard();
}