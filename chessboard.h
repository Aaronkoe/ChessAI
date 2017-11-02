#include <iostream>
#include <cstdlib>
#include <stdexcept>
#include "chesspiece.cpp"

class chessBoard {
  public:
    //printing functions
    void printMoveSet(std::pair<int, int> moveSet[]);

    //game administration functions
    void playGame();

    //piece moving functions
    void changeSpot(std::pair<int, int> dest, std::pair<int, int> orig);

    //piece finding functions
    std::pair<int, int> findPiece(char piece, std::pair<int, int> destination, std::pair<int, int> ident);
    std::pair<int, int> findCorrectPiece(std::pair<int, int> destination, std::pair<int, int> ident, std::pair<int, int> matches[]);

    //information parsing functions
    char                 getPiece       (std::string move);
    std::pair<int, int>  getDestination (std::string move);
    std::pair<int, int>  getIdentifier  (std::string move);
    std::pair<int, int>* getMoveSet(std::pair<int, int> piecePosition);
    bool destInMoveSet(std::pair<int, int> destination, std::pair<int, int> piecePosition);
    //member variables
    chessPiece board[8][8];
    //constructor
    chessBoard();

    //functions
    void printBoard(void);
    bool movePiece(std::string move);
    void manualWrite(int col, int row, char chr);
    bool validMove(std::string move, int checkCase, int playerTurn);
//    std::pair<int, int>* checkMoveConflicts(std::pair<int, int>* moveSet);
};

