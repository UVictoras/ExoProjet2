#include "pch.h"
#include "Board.h"

void Board::InitializeBoard()
{
	for (int i = 0; i < 64; i++)
	{
		m_cases[i] = nullptr;
	}

	InitializeBlackPieces();
	InitializeWhitePieces();
};

void Board::InitializeBlackPieces()
{	
	Rook* rook;
	Knight* knight;
	Pawn* pawn;
	Queen* queen;
	King* king;
	Bishop* bishop;

	for (int i = 0; i < 16; i++)
	{
		if (i == 0 || i == 7)
		{
			rook = new Rook();
			rook->InitializePiece(i, 'R', Black);
			m_cases[i] = rook;
		}
		else if (i == 1 || i == 6)
		{
			knight = new Knight();
			knight->InitializePiece(i, 'N', Black);
			m_cases[i] = knight; 
		}
		else if (i == 2 || i == 5)
		{
			bishop = new Bishop();
			bishop->InitializePiece(i, 'B', Black);
			m_cases[i] = bishop; 
		}
		else if (i == 3)
		{
			queen = new Queen();
			queen->InitializePiece(i, 'Q', Black);
			m_cases[i] = queen;  
		}
		else if (i == 4)
		{
			king = new King();
			king->InitializePiece(i, 'K', Black);
			m_cases[i] = king;   
		}
		else
		{
			pawn = new Pawn();
			pawn->InitializePiece(i, 'P', Black);
			m_cases[i] = pawn;   
		}
	}
}

void Board::InitializeWhitePieces()
{
	Pawn* pawn;
	Rook* rook;
	Knight* knight;
	Bishop* bishop;
	Queen* queen;
	King* king;

	for (int i = 0; i < 16; i++)
	{
		if (i < 8)
		{
			pawn = new Pawn();
			pawn->InitializePiece(i + 48, 'P', White);
			m_cases[i + 48] = pawn;
		}
		else if (i == 8 || i == 15)
		{
			rook = new Rook();
			rook->InitializePiece(i + 48, 'R', White);
			m_cases[i + 48] = rook;
		}
		else if (i == 9 || i == 14)
		{
			knight = new Knight();
			knight->InitializePiece(i + 48, 'N', White);
			m_cases[i + 48] = knight;
		}
		else if (i == 10 || i == 13)
		{
			bishop = new Bishop();
			bishop->InitializePiece(i + 48, 'B', White);
			m_cases[i + 48] = bishop;
		}
		else if (i == 11)
		{
			queen = new Queen();
			queen->InitializePiece(i + 48, 'Q', White);
			m_cases[i + 48] = queen;
		}
		else
		{
			king = new King();
			king->InitializePiece(i + 48, 'K', White);
			m_cases[i + 48] = king;
		}
	}
}

void Board::PrintBoard()
{
	std::cout << "\33[90m";
	std::cout << "p---------------q" << std::endl;
	for (int i = 0; i < 64; i++)
	{
		std::cout << "\33[90m";
		std::cout << "|";
		if (m_cases[i] == nullptr)
		{
			std::cout << " ";
		}
		else 
		{
			if (m_cases[i]->m_color == White)
			{
				std::cout << "\33[37m";
				std::cout << m_cases[i]->m_inGameChar;
			}
			else
			{
				std::cout << "\33[95m";
				std::cout << m_cases[i]->m_inGameChar;
			}
		}
		if ((i + 1) % 8 == 0)
		{
			std::cout << "\33[90m";
			std::cout << "|" << std::endl;
			if (i != 63)
				std::cout << "|-+-+-+-+-+-+-+-|" << std::endl;
		}
	}
	std::cout << "\33[90m";
	std::cout << "b---------------d" << std::endl;

	std::cout << "\33[37m";
}













































// bz moi