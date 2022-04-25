#include <iostream>
#include <algorithm>
#include <sstream>
#include "ChessBoard.h"
using namespace std;

const int MAX_MOVIMENTS = 28;


bool CheckPositions(const VecOfPositions& vec_test,
    const VecOfPositions& vec_res)
{
    if (vec_test.size() != vec_res.size()) {
        return false;
    }
    bool iguals = true;
    int i = 0;
    while ((i < (int)vec_test.size()) and (iguals))
    {
        iguals = false;
        int j = 0;
        while ((j < (int)vec_res.size()) && !iguals)
        {
            if (vec_test[i] == vec_res[j])
                iguals = true;
            else
                j++;
        }
        i++;
    }
    return iguals;
}


string colorToString(ChessPieceColor color)
{
    string symbol = "_";
    if (color != CPC_NONE)
    {
        if (color == CPC_Black)
        {
            symbol = "b";
        }
        else
        {
            symbol = "w";
        }
    }
    return symbol;
}


string tipusToString(ChessPieceType tipus)
{
    string symbol = "_";
    switch (tipus)
    {
    case CPT_King:
        symbol = "R";
        break;
    case CPT_Queen:
        symbol = "D";
        break;
    case CPT_Rook:
        symbol = "T";
        break;
    case CPT_Bishop:
        symbol = "A";
        break;
    case CPT_Knight:
        symbol = "C";
        break;
    case CPT_Pawn:
        symbol = "P";
        break;
    case CPT_EMPTY:
        symbol = "_";
        break;
    }
    return symbol;
}


string positionToString(int fila, int columna)
{
    char lletra = 'a' + columna;
    return lletra + std::to_string(NUM_ROWS - fila);
}


float checkEstatChessboard(const Chessboard& board, ChessPieceType tipus[NUM_ROWS][NUM_COLS], ChessPieceColor colors[NUM_ROWS][NUM_COLS],
    bool resultat[NUM_ROWS][NUM_COLS])
{
    float reduccio = 0.0;
    for (int i = 0; i < NUM_ROWS; i++)
        for (int j = 0; j < NUM_COLS; j++)
        {
            string pos_str = positionToString(i, j);
            ChessPosition pos(pos_str);
            if ((board.GetPieceColorAtPos(pos) != colors[i][j]) ||
                (board.GetPieceTypeAtPos(pos) != tipus[i][j]))
            {
                resultat[i][j] = false;
                reduccio += 1.0;
            }
            else
                resultat[i][j] = true;
        }
    return reduccio;
}


float testBoard(const string& nomFitxer, ChessPieceType tipus[NUM_ROWS][NUM_COLS], ChessPieceColor colors[NUM_ROWS][NUM_COLS])
{
    cout << "Comment :=>>" << endl;
    cout << "Comment :=>> Carregant estat inicial del tauler des del fitxer '" << nomFitxer << "'" << endl;
    cout << "Comment :=>> --------" << endl;

    Chessboard board;
    board.LoadBoardFromFile("C:/Users/gerar/source/repos/Escacs3/x64/Debug/" + nomFitxer);

    cout << "Comment :=>>" << endl;
    cout << "Comment :=>> Comprovant del tauler despres d'inicialitzar" << endl;
    cout << "Comment :=>> --------" << endl;

    bool resultat[NUM_ROWS][NUM_COLS];
    float reduccio = checkEstatChessboard(board, tipus, colors, resultat);

    if (fabs(reduccio) < 0.1)
    {
        cout << "Comment :=>> CORRECTE" << endl;
        cout << "Comment :=>> --------------------------------------------" << endl;

    }
    else
    {
        for (int i = 0; i < NUM_ROWS; i++)
            for (int j = 0; j < NUM_COLS; j++)
            {
                if (!resultat[i][j])
                {
                    string pos_str = positionToString(i, j);
                    ChessPosition pos(pos_str);
                    cout << "Comment :=>> Error a la posicio " << pos_str << endl;
                    cout << "Comment :=>> Color i tipus esperats: " << colorToString(colors[i][j]) << tipusToString(tipus[i][j]) << endl;
                    cout << "Comment :=>> Color i tipus obtinguts: " << colorToString(board.GetPieceColorAtPos(pos)) << tipusToString(board.GetPieceTypeAtPos(pos)) << endl;
                    cout << "Comment :=>> --------" << endl;
                }
            }

    }
    return reduccio;
}

float testLoadBoard()
{
    float reduccio = 0.0;

    cout << "Comment :=>>" << endl;
    cout << "Comment :=>> ===============================================================" << endl;
    cout << "Comment :=>> Iniciant Test 1: Carrega estat inicial del tauler des de fitxer" << endl;
    cout << "Comment :=>> ===============================================================" << endl;

    ChessPieceType tipus_test1[NUM_ROWS][NUM_COLS] =
    {
        {CPT_EMPTY, CPT_EMPTY, CPT_EMPTY, CPT_EMPTY, CPT_Rook, CPT_EMPTY, CPT_King, CPT_EMPTY},
        {CPT_EMPTY, CPT_Pawn, CPT_EMPTY, CPT_EMPTY, CPT_EMPTY, CPT_Pawn, CPT_Pawn, CPT_Pawn},
        {CPT_Pawn, CPT_EMPTY, CPT_EMPTY, CPT_EMPTY, CPT_EMPTY, CPT_EMPTY, CPT_EMPTY, CPT_EMPTY},
        {CPT_EMPTY, CPT_EMPTY, CPT_Pawn, CPT_EMPTY, CPT_EMPTY, CPT_EMPTY, CPT_Knight, CPT_EMPTY},
        {CPT_EMPTY, CPT_EMPTY, CPT_EMPTY, CPT_EMPTY, CPT_EMPTY, CPT_Pawn, CPT_EMPTY, CPT_Queen},
        {CPT_EMPTY, CPT_Queen, CPT_Knight, CPT_EMPTY, CPT_EMPTY, CPT_EMPTY, CPT_EMPTY, CPT_EMPTY},
        {CPT_Pawn, CPT_EMPTY, CPT_EMPTY, CPT_EMPTY, CPT_EMPTY, CPT_EMPTY, CPT_Pawn, CPT_EMPTY},
        {CPT_EMPTY, CPT_EMPTY, CPT_Bishop, CPT_EMPTY, CPT_EMPTY, CPT_Rook, CPT_King, CPT_EMPTY}
    };
    ChessPieceColor color_test1[NUM_ROWS][NUM_COLS] =
    {
        {CPC_NONE, CPC_NONE, CPC_NONE, CPC_NONE, CPC_Black, CPC_NONE, CPC_Black, CPC_NONE},
        {CPC_NONE, CPC_Black, CPC_NONE, CPC_NONE, CPC_NONE, CPC_Black, CPC_Black, CPC_Black},
        {CPC_Black, CPC_NONE, CPC_NONE, CPC_NONE, CPC_NONE, CPC_NONE, CPC_NONE, CPC_NONE},
        {CPC_NONE, CPC_NONE, CPC_White, CPC_NONE, CPC_NONE, CPC_NONE, CPC_White, CPC_NONE},
        {CPC_NONE, CPC_NONE, CPC_NONE, CPC_NONE, CPC_NONE, CPC_White, CPC_NONE, CPC_Black},
        {CPC_NONE, CPC_White, CPC_Black, CPC_NONE, CPC_NONE, CPC_NONE, CPC_NONE, CPC_NONE},
        {CPC_White, CPC_NONE, CPC_NONE, CPC_NONE, CPC_NONE, CPC_NONE, CPC_White, CPC_NONE},
        {CPC_NONE, CPC_NONE, CPC_White, CPC_NONE, CPC_NONE, CPC_White, CPC_White, CPC_NONE}
    };

    ChessPieceType tipus_test2[NUM_ROWS][NUM_COLS] =
    {
        {CPT_Rook, CPT_EMPTY, CPT_Bishop, CPT_EMPTY, CPT_EMPTY, CPT_EMPTY, CPT_EMPTY, CPT_Rook},
        {CPT_EMPTY, CPT_Pawn, CPT_EMPTY, CPT_King, CPT_EMPTY, CPT_Knight, CPT_Pawn, CPT_Pawn},
        {CPT_EMPTY, CPT_EMPTY, CPT_Pawn, CPT_EMPTY, CPT_EMPTY, CPT_Knight, CPT_EMPTY, CPT_EMPTY},
        {CPT_EMPTY, CPT_Bishop, CPT_EMPTY, CPT_EMPTY, CPT_EMPTY, CPT_EMPTY, CPT_EMPTY, CPT_EMPTY},
        {CPT_EMPTY, CPT_EMPTY, CPT_EMPTY, CPT_Pawn, CPT_EMPTY, CPT_EMPTY, CPT_EMPTY, CPT_EMPTY},
        {CPT_Bishop, CPT_Knight, CPT_EMPTY, CPT_EMPTY, CPT_EMPTY, CPT_EMPTY, CPT_EMPTY, CPT_EMPTY},
        {CPT_Pawn, CPT_EMPTY, CPT_EMPTY, CPT_EMPTY, CPT_EMPTY, CPT_Pawn, CPT_Pawn, CPT_Pawn},
        {CPT_EMPTY, CPT_EMPTY, CPT_EMPTY, CPT_EMPTY, CPT_Rook, CPT_EMPTY, CPT_King, CPT_EMPTY}
    };
    ChessPieceColor color_test2[NUM_ROWS][NUM_COLS] =
    {
        {CPC_Black, CPC_NONE, CPC_Black, CPC_NONE, CPC_NONE, CPC_NONE, CPC_NONE, CPC_Black},
        {CPC_NONE, CPC_Black, CPC_NONE, CPC_Black, CPC_NONE, CPC_White, CPC_Black, CPC_Black},
        {CPC_NONE, CPC_NONE, CPC_Black, CPC_NONE, CPC_NONE, CPC_Black, CPC_NONE, CPC_NONE},
        {CPC_NONE, CPC_White, CPC_NONE, CPC_NONE, CPC_NONE, CPC_NONE, CPC_NONE, CPC_NONE},
        {CPC_NONE, CPC_NONE, CPC_NONE, CPC_Black, CPC_NONE, CPC_NONE, CPC_NONE, CPC_NONE},
        {CPC_White, CPC_Black, CPC_NONE, CPC_NONE, CPC_NONE, CPC_NONE, CPC_NONE, CPC_NONE},
        {CPC_White, CPC_NONE, CPC_NONE, CPC_NONE, CPC_NONE, CPC_White, CPC_White, CPC_White},
        {CPC_NONE, CPC_NONE, CPC_NONE, CPC_NONE, CPC_White, CPC_NONE, CPC_White, CPC_NONE}
    };

    reduccio += testBoard("tauler_1.txt", tipus_test1, color_test1);
    reduccio += testBoard("tauler_2.txt", tipus_test2, color_test2);
    return reduccio;
}

void mostraPosicions(VecOfPositions& posicions)
{
    vector<string> posicions_str;
    for (int i = 0; i < posicions.size(); i++)
    {
        stringstream output_str;
        output_str << posicions[i];
        posicions_str.push_back(output_str.str());
    }
    std::sort(posicions_str.begin(), posicions_str.end());
    cout << "Comment :=>> ";
    for (int i = 0; i < posicions_str.size(); i++)
        cout << posicions_str[i] << " ";
    cout << endl;
}

float testValid(const string& nomFitxer, string posicions[], string moviments[][MAX_MOVIMENTS], int nPosicions,
    int nMoviments[])
{
    float reduccio = 0.0;

    cout << "Comment :=>>" << endl;
    cout << "Comment :=>> ----------------------------------------------------------------" << endl;
    cout << "Comment :=>> Carregant estat inicial del tauler des del fitxer '" << nomFitxer << "'" << endl;
    cout << "Comment :=>> ----------------------------------------------------------------" << endl;
    cout << "Comment :=>>" << endl;

    Chessboard board;
    board.LoadBoardFromFile("C:/Users/gerar/source/repos/Escacs3/x64/Debug/" + nomFitxer);

    for (int i = 0; i < nPosicions; i++)
    {
        ChessPosition pos(posicions[i]);
        VecOfPositions movimentsEsperats;
        for (int j = 0; j < nMoviments[i]; j++)
            movimentsEsperats.push_back(ChessPosition(moviments[i][j]));

        cout << "Comment :=>> Comprovant moviments de la fitxa a la posicio: " << posicions[i] << endl;
        cout << "Comment :=>> Color i tipus de la fitxa: " << colorToString(board.GetPieceColorAtPos(pos)) << tipusToString(board.GetPieceTypeAtPos(pos)) << endl;
        cout << "Comment :=>> Moviments valids esperats: " << endl;
        mostraPosicions(movimentsEsperats);
        cout << "Comment :=>> ----" << endl;

        VecOfPositions movimentsObtinguts = board.GetValidMoves(pos);
        cout << "Comment :=>> Moviments valids obtinguts: " << endl;
        mostraPosicions(movimentsObtinguts);
        cout << "Comment :=>> ----" << endl;

        if (CheckPositions(movimentsEsperats, movimentsObtinguts))
            cout << "Comment :=>> CORRECTE" << endl;
        else
        {
            cout << "Comment :=>> ERROR" << endl;
            reduccio += 1.0;
        }
        cout << "Comment :=>> ------------------------------------" << endl;
    }
    return reduccio;
}

float testValidMoves()
{
    float reduccio = 0.0;

    cout << "Comment :=>>" << endl;
    cout << "Comment :=>> ================================================" << endl;
    cout << "Comment :=>> Iniciant Test 2: Comprovacio de moviments valids" << endl;
    cout << "Comment :=>> ================================================" << endl;

    const int NUM_PROVES1 = 10;
    string posicions1[NUM_PROVES1] = { "e8", "g8", "b7", "g5", "h4", "b3", "c3", "c1", "f1", "g1" };
    string movimentsValids1[NUM_PROVES1][MAX_MOVIMENTS] =
    {
        {"a8", "b8", "c8", "d8", "e1", "e2", "e3", "e4", "e5", "e6", "e7", "f8"},
        {"f8", "h8"},
        {"b5", "b6"},
        {"e4", "e6", "f3", "f7", "h3", "h7"},
        {"e1", "f2", "f4", "g3", "g4", "g5", "h1", "h2", "h3", "h5", "h6"},
        {"a3", "a4", "b1", "b2", "b4", "b5", "b6", "b7", "c2", "c3", "c4", "d1", "d5", "e6", "f7"},
        {"a2", "a4", "b1", "b5", "d1", "d5", "e2", "e4"},
        {"a3", "b2", "d2", "e3"},
        {"d1", "e1", "f2", "f3"},
        {"f2", "h1", "h2"}
    };
    int nMovimentsValids1[NUM_PROVES1] = { 12, 2, 2, 6, 11, 15, 8, 4, 4, 3 };

    reduccio += testValid("tauler_1.txt", posicions1, movimentsValids1, NUM_PROVES1, nMovimentsValids1);

    const int NUM_PROVES2 = 10;
    string posicions2[NUM_PROVES1] = { "a8", "c8", "f7", "g7", "f6", "d4", "a3", "b3", "a2", "f2" };
    string movimentsValids2[NUM_PROVES1][MAX_MOVIMENTS] =
    {
        {"a3", "a4", "a5", "a6", "a7", "b8"},
        {},
        {"d6", "d8", "e5", "g5", "h6", "h8"},
        {"g5", "g6"},
        {"d5", "e4", "e8", "g4", "g8", "h5"},
        {"d3"},
        {"b2", "b4", "c1", "c5", "d6", "e7", "f8"},
        {"a1", "a5", "c1", "c5", "d2"},
        {"b3"},
        {"f3", "f4"}
    };
    int nMovimentsValids2[NUM_PROVES2] = { 6, 0, 6, 2, 6, 1, 7, 5, 1, 2 };

    reduccio += testValid("tauler_2.txt", posicions2, movimentsValids2, NUM_PROVES2, nMovimentsValids2);


    return reduccio;
}


bool CheckMoviment(Chessboard& board, ChessPosition& posOrigen, ChessPosition& posDesti, bool resultatEsperat,
    bool resultatObtingut, ChessPieceColor colorOrigen, ChessPieceType tipusOrigen,
    ChessPieceColor colorDesti, ChessPieceType tipusDesti)
{
    bool correcte = false;
    if (resultatEsperat == resultatObtingut)
        if (resultatEsperat)
        {
            if ((board.GetPieceTypeAtPos(posOrigen) == CPT_EMPTY) && (board.GetPieceColorAtPos(posOrigen) == CPC_NONE) &&
                (board.GetPieceTypeAtPos(posDesti) == tipusOrigen) && (board.GetPieceColorAtPos(posDesti) == colorOrigen))
                correcte = true;
        }
        else
        {
            if ((board.GetPieceTypeAtPos(posOrigen) == tipusOrigen) && (board.GetPieceColorAtPos(posOrigen) == colorOrigen) &&
                (board.GetPieceTypeAtPos(posDesti) == tipusDesti) && (board.GetPieceColorAtPos(posDesti) == colorDesti))
                correcte = true;

        }
    return correcte;
}

float testMovePiece()
{
    float reduccio = 0.0;

    cout << "Comment :=>>" << endl;
    cout << "Comment :=>> ======================================================" << endl;
    cout << "Comment :=>> Iniciant Test 3: Comprovaci� del moviment de les peces" << endl;
    cout << "Comment :=>> ======================================================" << endl;

    cout << "Comment :=>>" << endl;
    cout << "Comment :=>> ----------------------------------------------------------------" << endl;
    cout << "Comment :=>> Carregant estat inicial del tauler des del fitxer 'tauler_2.txt'" << endl;
    cout << "Comment :=>> ----------------------------------------------------------------" << endl;
    cout << "Comment :=>>" << endl;

    Chessboard board;
    board.LoadBoardFromFile("C:/Users/gerar/source/repos/Escacs3/x64/Debug/tauler_2.txt");


    const int NUM_PROVES = 6;
    string posicions[NUM_PROVES][2] = { {"e1", "e2"}, {"a8", "a3"}, {"c8", "f8"}, {"c8", "d7"}, {"a2", "b3"}, {"g1", "f1"} };
    bool resultat[NUM_PROVES] = { true, true, false, false, true, true };

    for (int i = 0; i < NUM_PROVES; i++)
    {
        ChessPosition posOrigen(posicions[i][0]);
        ChessPieceColor colorOrigen = board.GetPieceColorAtPos(posOrigen);
        ChessPieceType tipusOrigen = board.GetPieceTypeAtPos(posOrigen);
        ChessPosition posDesti(posicions[i][1]);
        ChessPieceColor colorDesti = board.GetPieceColorAtPos(posDesti);
        ChessPieceType tipusDesti = board.GetPieceTypeAtPos(posDesti);

        cout << "Comment :=>> Realitzant moviment de la posicio " << posicions[i][0] << " a la posicio " << posicions[i][1] << endl;
        cout << "Comment :=>> Color i tipus de la fitxa a la posicio origen: " << colorToString(colorOrigen) << tipusToString(tipusOrigen) << endl;
        cout << "Comment :=>> Color i tipus de la fitxa a la posicio desti: " << colorToString(colorDesti) << tipusToString(tipusDesti) << endl;
        cout << "Comment :=>> Resultat esperat: ";
        if (resultat[i])
            cout << "MOVIMENT VALID" << endl;
        else
            cout << "MOVIMENT NO VALID" << endl;
        cout << "Comment :=>> ----" << endl;

        bool valid = board.MovePiece(posOrigen, posDesti);

        cout << "Comment :=>> Resultat obtingut: ";
        if (valid)
            cout << "MOVIMENT VALID" << endl;
        else
            cout << "MOVIMENT NO VALID" << endl;
        cout << "Comment :=>> Color i tipus de la fitxa a la posicio origen: " << colorToString(board.GetPieceColorAtPos(posOrigen)) << tipusToString(board.GetPieceTypeAtPos(posOrigen)) << endl;
        cout << "Comment :=>> Color i tipus de la fitxa a la posicio desti: " << colorToString(board.GetPieceColorAtPos(posDesti)) << tipusToString(board.GetPieceTypeAtPos(posDesti)) << endl;
        cout << "Comment :=>> ----" << endl;

        if (CheckMoviment(board, posOrigen, posDesti, resultat[i], valid, colorOrigen, tipusOrigen, colorDesti, tipusDesti))
            cout << "Comment :=>> CORRECTE" << endl;
        else
        {
            cout << "Comment :=>> ERROR" << endl;
            reduccio += 1.0;
        }
        cout << "Comment :=>> --------------------------------------------------------" << endl;
    }

    return reduccio;
}

int main(int argc, const char* argv[])
{

    float grade = 0.0;

    cout << endl << endl;
    cout << "Comment :=>> INICIANT TESTS" << endl;
    cout << "Comment :=>> ==============" << endl;
    cout << "Comment :=>> " << endl;
    cout << "Grade :=>> " << grade << endl;



    float reduccio = 0;
    // -------------------------------------------------
    // TEST 1: Carregar el tauler inicial de fitxer
    reduccio = testLoadBoard();
    grade = grade + (2 - reduccio);
    if (grade < 0)
        grade = 0;
    cout << "Grade :=>> " << grade << endl;

    // -------------------------------------------------
    // TEST 2: Comprovar moviments v�lids
    reduccio = testValidMoves();
    if (reduccio > 6)
        reduccio = 6;
    grade = grade + (6 - reduccio);
    cout << "Grade :=>> " << grade << endl;

    // -------------------------------------------------
    // TEST 3: Comprovar moviment peces
    reduccio = testMovePiece();
    if (reduccio > 2)
        reduccio = 2;
    grade = grade + (2 - reduccio);
    cout << "Grade :=>> " << grade << endl;
    if (grade == 10.0)
        cout << "Comment :=>> Final del test sense errors" << endl;

    return 0;
}