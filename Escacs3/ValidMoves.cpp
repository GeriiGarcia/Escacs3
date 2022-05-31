#include "ChessBoard.h"


VecOfPositions Chessboard::GetValidMoves(const ChessPosition& pos)
{
	/*
	REI:			REINA:			TORRE:			CABALL			ALFIL:		 	PEO
	- - - - -		X - X - X		- - X - -		- X - X -		X - - - X		- - - - -
	- X X X -		- X X X -		- - X - -		X - - - X		- X - X -		- - X - -
	- X R X -		X X R X X		X X T X X		- - C - -		- - A - -		- X X X -
	- X X X -		- X X X -		- - X - -		X - - - X		- X - X -		- - P - -
	- - - - -		X - X - X		- - X - -		- X - X -		X - - - X		- - - - -
	*/

	VecOfPositions vectorPos;
	ChessPosition posAuxiliar;

	switch (m_tauler[pos.getPosicioX()][pos.getPosicioY()].getTipus())
	{
	case CPT_King:
		// analitzem cada posició que hi ha al voltant del rei i ens quedem amb les vàlides
		for (int i = -1; i <= 1; i++)
		{
			posAuxiliar.setPosicioX(pos.getPosicioX() + i);

			for (int j = -1; j <= 1; j++)
			{
				posAuxiliar.setPosicioY(pos.getPosicioY() + j);

				if (posicioValida(posAuxiliar, pos))
					vectorPos.push_back(posAuxiliar);
			}
		}

		break;

	case CPT_Queen: //amb diagonal NE em refereixo a la diagonal de adalt a la dreta ns  si m'entens rbro v 
		analisiDiagonals(pos, vectorPos);
		analisiHoritzontals(pos, vectorPos);
		analisiVerticals(pos, vectorPos);

		break;

	case CPT_Rook:
		analisiHoritzontals(pos, vectorPos);
		analisiVerticals(pos, vectorPos);

		break;

	case CPT_Knight: // ----------------------------------------------- CAVALL
		analisiCavall(pos, vectorPos);

		break;

	case CPT_Bishop:

		analisiDiagonals(pos, vectorPos);

		break;


	case CPT_Pawn: // -------------------------------------------------- PEO
		analisiPeo(pos, vectorPos);
		break;
	}
	return vectorPos;
}


// funcions per analitzar les posicions vàlides
void Chessboard::analisiPeo(const ChessPosition& pos, VecOfPositions& vectorPos)
{
	//posAuxiliar
	ChessPosition posAuxiliar;
	posAuxiliar.setPosicioX(pos.getPosicioX());

	// Fem una variable que guarda el color contrari
	ChessPieceColor colorOposat = CPC_Black;
	if (GetPieceColorAtPos(pos) == CPC_Black)
		colorOposat = CPC_White;

	// fem una variable direcció que ens indiqui a quina direccio es mou el peo (depenent del color)
	int direccio = 1;
	if (GetPieceColorAtPos(pos) == CPC_White)
		direccio = -1;

	// analitzem la posició frontal
	posAuxiliar.setPosicioY((pos.getPosicioY() + 1 * direccio));
	if (posicioValida(posAuxiliar, pos) && GetPieceColorAtPos(posAuxiliar) == CPC_NONE)
	{
		vectorPos.push_back(posAuxiliar);

		// analitzem la 2a posició frontal
		posAuxiliar.setPosicioY((pos.getPosicioY() + 2 * direccio));
		if (posicioValida(posAuxiliar, pos) && GetPieceColorAtPos(posAuxiliar) == CPC_NONE && !getMogudaPiece(pos))
			vectorPos.push_back(posAuxiliar);
	}

	// analitzem les posicions diagonals frontals 

	posAuxiliar.setPosicioY((pos.getPosicioY() + 1 * direccio));
	posAuxiliar.setPosicioX(pos.getPosicioX() - 1);
	if (posicioValida(posAuxiliar, pos) && GetPieceColorAtPos(posAuxiliar) == colorOposat)
		vectorPos.push_back(posAuxiliar);

	posAuxiliar.setPosicioX(pos.getPosicioX() + 1);
	if (posicioValida(posAuxiliar, pos) && GetPieceColorAtPos(posAuxiliar) == colorOposat)
		vectorPos.push_back(posAuxiliar);


}

void Chessboard::analisiDiagonals(const ChessPosition& pos, VecOfPositions& vectorPos)
{
	ChessPosition posAuxiliar;

	// Fem una variable que guarda el color contrari
	ChessPieceColor colorOposat = CPC_Black;
	if (GetPieceColorAtPos(pos) == CPC_Black)
		colorOposat = CPC_White;


	// Diagonal NE
	int i = 1;
	bool fiLinea = false;
	posAuxiliar.setPosicioX(pos.getPosicioX() + i);
	posAuxiliar.setPosicioY(pos.getPosicioY() - i);

	while (posicioValida(posAuxiliar, pos) && !fiLinea)
	{
		// afegim la posicio al vector
		vectorPos.push_back(posAuxiliar);

		// mirem que la posicio no sigui del conor oposat
		if (GetPieceColorAtPos(posAuxiliar) == colorOposat)
			fiLinea = true;

		// cambiem posAuxiliar
		i++;
		posAuxiliar.setPosicioX(pos.getPosicioX() + i);
		posAuxiliar.setPosicioY(pos.getPosicioY() - i);
	}

	// Diagonal NO
	i = 1;
	fiLinea = false;
	posAuxiliar.setPosicioX(pos.getPosicioX() - i);
	posAuxiliar.setPosicioY(pos.getPosicioY() - i);

	while (posicioValida(posAuxiliar, pos) && !fiLinea)
	{
		vectorPos.push_back(posAuxiliar);

		if (GetPieceColorAtPos(posAuxiliar) == colorOposat)
			fiLinea = true;

		i++;
		posAuxiliar.setPosicioX(pos.getPosicioX() - i);
		posAuxiliar.setPosicioY(pos.getPosicioY() - i);
	}

	// Diagonal SO
	i = 1;
	fiLinea = false;
	posAuxiliar.setPosicioX(pos.getPosicioX() - i);
	posAuxiliar.setPosicioY(pos.getPosicioY() + i);

	while (posicioValida(posAuxiliar, pos) && !fiLinea)
	{
		vectorPos.push_back(posAuxiliar);

		if (GetPieceColorAtPos(posAuxiliar) == colorOposat)
			fiLinea = true;

		i++;
		posAuxiliar.setPosicioX(pos.getPosicioX() - i);
		posAuxiliar.setPosicioY(pos.getPosicioY() + i);
	}

	// Diagonal SE
	i = 1;
	fiLinea = false;
	posAuxiliar.setPosicioX(pos.getPosicioX() + i);
	posAuxiliar.setPosicioY(pos.getPosicioY() + i);

	while (posicioValida(posAuxiliar, pos) && !fiLinea)
	{
		vectorPos.push_back(posAuxiliar);

		if (GetPieceColorAtPos(posAuxiliar) == colorOposat)
			fiLinea = true;

		i++;
		posAuxiliar.setPosicioX(pos.getPosicioX() + i);
		posAuxiliar.setPosicioY(pos.getPosicioY() + i);
	}

}

void Chessboard::analisiHoritzontals(const ChessPosition& pos, VecOfPositions& vectorPos)
{
	ChessPosition posAuxiliar;
	posAuxiliar.setPosicioY(pos.getPosicioY());

	ChessPieceColor colorOposat = CPC_Black;
	if (GetPieceColorAtPos(pos) == CPC_Black)
		colorOposat = CPC_White;

	// Horitzontal E
	int i = 1;
	bool fiLinea = false;
	posAuxiliar.setPosicioX(pos.getPosicioX() + i);

	while (posicioValida(posAuxiliar, pos) && !fiLinea)
	{
		// Afegim la posicio al vector
		vectorPos.push_back(posAuxiliar);

		// Comprovem que no sigui del color oposat
		if (GetPieceColorAtPos(posAuxiliar) == colorOposat)
			fiLinea = true;

		// Movem la posicio a analitzar
		i++;
		posAuxiliar.setPosicioX(pos.getPosicioX() + i);
	}


	// Horitzontal O
	i = 1;
	fiLinea = false;
	posAuxiliar.setPosicioX(pos.getPosicioX() - i);

	while (posicioValida(posAuxiliar, pos) && !fiLinea)
	{
		vectorPos.push_back(posAuxiliar);

		if (GetPieceColorAtPos(posAuxiliar) == colorOposat)
			fiLinea = true;

		i++;
		posAuxiliar.setPosicioX(pos.getPosicioX() - i);
	}
}

void Chessboard::analisiVerticals(const ChessPosition& pos, VecOfPositions& vectorPos)
{
	ChessPosition posAuxiliar;
	posAuxiliar.setPosicioX(pos.getPosicioX());

	ChessPieceColor colorOposat = CPC_Black;
	if (GetPieceColorAtPos(pos) == CPC_Black)
		colorOposat = CPC_White;

	//Vertical N
	int i = 1;
	bool fiLinea = false;
	posAuxiliar.setPosicioY(pos.getPosicioY() + i);

	while (posicioValida(posAuxiliar, pos) && !fiLinea)
	{
		vectorPos.push_back(posAuxiliar);

		if (GetPieceColorAtPos(posAuxiliar) == colorOposat)
			fiLinea = true;

		i++;
		posAuxiliar.setPosicioY(pos.getPosicioY() + i);
	}


	//Vertical S
	i = 1;
	fiLinea = false;
	posAuxiliar.setPosicioY(pos.getPosicioY() - i);

	while (posicioValida(posAuxiliar, pos) && !fiLinea)
	{
		vectorPos.push_back(posAuxiliar);

		if (GetPieceColorAtPos(posAuxiliar) == colorOposat)
			fiLinea = true;

		i++;
		posAuxiliar.setPosicioY(pos.getPosicioY() - i);
	}
}

void Chessboard::analisiCavall(const ChessPosition& pos, VecOfPositions& vectorPos)
{
	ChessPosition posAuxiliar;

	// analitzem les posicions per columnes i només en les que es pot moure el cavall
	for (int i = -2; i <= 2; i++)
	{
		posAuxiliar.setPosicioX(pos.getPosicioX() + i);

		if (i == -2 || i == 2)
		{
			posAuxiliar.setPosicioY(pos.getPosicioY() - 1);
			if (posicioValida(posAuxiliar, pos))
				vectorPos.push_back(posAuxiliar);

			posAuxiliar.setPosicioY(pos.getPosicioY() + 1);
			if (posicioValida(posAuxiliar, pos))
				vectorPos.push_back(posAuxiliar);
		}
		else if (i == -1 || i == 1)
		{
			posAuxiliar.setPosicioY(pos.getPosicioY() - 2);
			if (posicioValida(posAuxiliar, pos))
				vectorPos.push_back(posAuxiliar);

			posAuxiliar.setPosicioY(pos.getPosicioY() + 2);
			if (posicioValida(posAuxiliar, pos))
				vectorPos.push_back(posAuxiliar);
		}
	}
}


// Aquest procediment analitza una posició i mira si aquesta entra dins del tauler i si hi ha una fitxa del mateix color
bool Chessboard::posicioValida(ChessPosition posAuxiliar, ChessPosition pos)
{
	bool esValida = true;

	if (posAuxiliar.getPosicioX() > NUM_COLS - 1 || posAuxiliar.getPosicioX() < 0 || posAuxiliar.getPosicioY() > NUM_ROWS - 1 || posAuxiliar.getPosicioY() < 0)
		esValida = false;
	else if (GetPieceTypeAtPos(posAuxiliar) != CPT_EMPTY && GetPieceColorAtPos(posAuxiliar) == GetPieceColorAtPos(pos))
		esValida = false;

	return esValida;

}
