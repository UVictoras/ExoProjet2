// pch.h: Precompiled header file
#pragma once

#ifdef _DEBUG
#define DEBUG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DEBUG_NEW
#endif

#define _CRT_SECURE_NO_WARNINGS
#include "Board.h"
#include "Pawn.h"
#include "Bishop.h"
#include "Knight.h"
#include "King.h"
#include "Queen.h"
#include "Rook.h"
#include "Graphics.h"

enum Color
{
	White,
	Black
};

extern Board board;
extern std::vector<Board> gameHistory;  
extern int halfMoveClock; 
extern int MAX_TURN;