#include "Piece.h"

// ----------------------- Constructors 
Piece::Piece()
{
	m_color = CPC_NONE;
	m_tipus = CPT_EMPTY;
	m_moguda = false;
}


// ----------------------- Metodes
string Piece::pieceToString() const
{
	string str = "";

	switch (m_color)
	{
	case CPC_White:
		str.append("w");
		break;

	case CPC_Black:
		str.append("b");
		break;

	default:
		str.append("_");
	}

	switch (m_tipus)
	{
	case CPT_King:
		str.append("K");
		break;

	case CPT_Queen:
		str.append("Q");
		break;

	case CPT_Rook:
		str.append("T");
		break;

	case CPT_Knight:
		str.append("H");
		break;

	case CPT_Bishop:
		str.append("B");
		break;

	case CPT_Pawn:
		str.append("P");
		break;

	default:
		str.append("_");
	}

	return str;
}


