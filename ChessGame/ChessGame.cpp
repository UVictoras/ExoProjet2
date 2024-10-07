#include "pch.h"
#include <iostream>

Board board; 

int main()
{
    board.InitializeBoard();
    board.PrintBoard();

    reinterpret_cast<Pawn*>(board.m_cases[48])->Move(40);
    board.PrintBoard();
}