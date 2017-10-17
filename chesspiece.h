#include <iostream>
class chessPiece {
  public:
    char piece;
    int whiteOrBlack;
    std::pair<int, int> location;
    chessPiece();
    chessPiece(char pieceClass, std::pair<int, int> location);
    void changePiecePosition(std::pair<int, int> destination);
    std::pair<int, int>* getMoveSet(chessPiece board[8][8]);
    int checkConflict(std::pair<int, int> dest, chessPiece board[8][8]);
    int getPlayerPossession();
    friend std::ostream& operator<< (std::ostream &out, const chessPiece &p);
};
