#include "ChessBoard.h"

Chessboard::Chessboard()
{
	/*ns fins a quin punt cal aixo, ja que la única cosa que hi ha per inicialitzar
	es una fixa que ja s'inicialitza sola*/
}

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


// ---------------------------------------------------------------------------------------- llegir arxiu
void Chessboard::LoadBoardFromFile(const string& nomFitxer)
{

	ifstream fitxer(nomFitxer);
	string linea;

	ChessPosition pos;
	int posVertical, posHoritzontal;

	ChessPieceType tipus;
	ChessPieceColor color;

	do {

		getline(fitxer, linea);



		// Mirem de quin color es
		if (linea.at(0) == '0')
			color = CPC_White;
		else if (linea.at(0) == '1')
			color = CPC_Black;
		else
			color = CPC_NONE;



		// Mirem quin tipus de fitxa es
		switch (linea.at(3))
		{
		case 'R':
			tipus = CPT_King;
			break;

		case 'D':
			tipus = CPT_Queen;
			break;

		case 'T':
			tipus = CPT_Rook;
			break;

		case 'A':
			tipus = CPT_Bishop;
			break;

		case 'C':
			tipus = CPT_Knight;
			break;

		case 'P':
			tipus = CPT_Pawn;
			break;
		}

		// Mirem la seva posició Horitzontal
		switch (linea.at(4))
		{
		case 'a':
			posHoritzontal = 0;
			break;
		case 'b':
			posHoritzontal = 1;
			break;
		case 'c':
			posHoritzontal = 2;
			break;
		case 'd':
			posHoritzontal = 3;
			break;
		case 'e':
			posHoritzontal = 4;
			break;
		case 'f':
			posHoritzontal = 5;
			break;
		case 'g':
			posHoritzontal = 6;
			break;
		case 'h':
			posHoritzontal = 7;
			break;
		}

		// Mirem la seva posició vertical
		switch (linea.at(5))
		{
		case '1':
			posVertical = 7;
			break;
		case '2':
			posVertical = 6;
			break;
		case '3':
			posVertical = 5;
			break;
		case '4':
			posVertical = 4;
			break;
		case '5':
			posVertical = 3;
			break;
		case '6':
			posVertical = 2;
			break;
		case '7':
			posVertical = 1;
			break;
		case '8':
			posVertical = 0;
			break;
		}

		pos.setPosicioX(posHoritzontal);
		pos.setPosicioY(posVertical);

		m_tauler[posHoritzontal][posVertical].setColor(color);
		m_tauler[posHoritzontal][posVertical].setTipus(tipus);

	} while (!fitxer.eof());

	fitxer.close();
}


// ---------------------------------------------------------------------------------------- moure fitxa
bool Chessboard::MovePiece(const ChessPosition& posFrom, const ChessPosition& posTo)
{
	bool esPot = false;
	if (GetPieceColorAtPos(posFrom) != CPC_NONE && posicioDinsVector(posTo, GetValidMoves(posFrom)))
	{
		setNovaPiece(posTo, m_tauler[posTo.getPosicioX()][posTo.getPosicioY()].getColor(), m_tauler[posTo.getPosicioX()][posTo.getPosicioY()].getTipus(), m_tauler[posTo.getPosicioX()][posTo.getPosicioY()].getMoguda());
		setNovaPiece(posFrom, CPC_NONE, CPT_EMPTY, 0);

		esPot = true;
	}

	return esPot;
}

bool Chessboard::posicioDinsVector(const ChessPosition& pos, VecOfPositions vectorPos)
{
	int i = 0;
	bool trobat = false;

	while (!trobat && i < vectorPos.size())
	{
		if (pos == vectorPos.at(i))
			trobat = true;
		else
			i++;
	}

	return trobat;
}

// ---------------------------------------------------------------------------------------- taula to string
string Chessboard::taulaToString() const
{
	string taulaStr = "";

	for (int fila = 0; fila < NUM_ROWS; fila++)
	{
		// afegim els noms de la fila
		taulaStr.append(to_string(8 - fila));

		// afegim columna a columna les fitxes
		for (int columna = 0; columna < NUM_COLS; columna++)
		{
			taulaStr.append(" ");
			taulaStr.append(m_tauler[fila][columna].pieceToString());
		}

		taulaStr.append("\n");

	}

	// afegim els noms de les files
	taulaStr.append("  a  b  c  d  e  f  g  h");
	return taulaStr;
}



// funcions auxiliars que ens permeten jugar amb les fitxes amb l'objectiu d'acotar codi
ChessPieceColor Chessboard::GetPieceColorAtPos(ChessPosition pos) const
{
	return m_tauler[pos.getPosicioX()][pos.getPosicioY()].getColor();
}

ChessPieceType Chessboard::GetPieceTypeAtPos(ChessPosition pos) const
{
	return m_tauler[pos.getPosicioX()][pos.getPosicioY()].getTipus();
}

bool Chessboard::getMogudaPiece(ChessPosition pos)
{
	return m_tauler[pos.getPosicioX()][pos.getPosicioY()].getMoguda();
}

void Chessboard::setNovaPiece(ChessPosition pos, ChessPieceColor color, ChessPieceType tipus, int moguda)
{
	m_tauler[pos.getPosicioX()][pos.getPosicioY()].setColor(color);
	m_tauler[pos.getPosicioX()][pos.getPosicioY()].setTipus(tipus);
	m_tauler[pos.getPosicioX()][pos.getPosicioY()].setMoguda(moguda);
}


// funcions per analitzar les posicions vàlides
void Chessboard::analisiPeo(const ChessPosition& pos, VecOfPositions& vectorPos)
{
	//posAuxiliar
	ChessPosition posAuxiliar;
	posAuxiliar.setPosicioX(pos.getPosicioX());

	// Fem una variable que guarda el color contrari
	ChessPieceColor colorOposat = CPC_Black;
	if(GetPieceColorAtPos(pos) == CPC_White)
		colorOposat = CPC_White;

	// fem una variable direcció que ens indiqui a quina direccio es mou el peo (depenent del color)
	int direccio = 1;
	if (GetPieceColorAtPos(pos) == CPC_White)
		direccio = -1;

	// analitzem la posició frontal
	posAuxiliar.setPosicioY((pos.getPosicioY() + 1 * direccio) );
	if (posicioValida(posAuxiliar, pos) && GetPieceColorAtPos(posAuxiliar) == CPC_NONE)
		vectorPos.push_back(posAuxiliar);


	// analitzem les posicions diagonals frontals 
	posAuxiliar.setPosicioX(pos.getPosicioX() - 1);
	if (posicioValida(posAuxiliar, pos) && GetPieceColorAtPos(posAuxiliar) == colorOposat)
		vectorPos.push_back(posAuxiliar);

	posAuxiliar.setPosicioX(pos.getPosicioX() + 1);
	if (posicioValida(posAuxiliar, pos) && GetPieceColorAtPos(posAuxiliar) == colorOposat)
		vectorPos.push_back(posAuxiliar);


	// analitzem la 2a posició frontal
	posAuxiliar.setPosicioX(pos.getPosicioX());
	posAuxiliar.setPosicioY((pos.getPosicioY() + 2 * direccio) );
	if (posicioValida(posAuxiliar, pos) && GetPieceColorAtPos(posAuxiliar) == CPC_NONE && !getMogudaPiece(pos))
		vectorPos.push_back(posAuxiliar);
}

void Chessboard::analisiDiagonals(const ChessPosition& pos, VecOfPositions& vectorPos)
{
	ChessPosition posAuxiliar;
	
	// Fem una variable que guarda el color contrari
	ChessPieceColor colorOposat = CPC_Black;
	if(GetPieceColorAtPos(pos) == CPC_White)
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
	if(GetPieceColorAtPos(pos) == CPC_White)
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
	if(GetPieceColorAtPos(pos) == CPC_White)
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
