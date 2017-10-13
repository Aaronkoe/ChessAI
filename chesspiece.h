#include <iostream>
class chessPiece {
  public:
    char piece;
    int whiteOrBlack;
    std::pair<int, int> location;
    chessPiece();
    chessPiece(char pieceClass, std::pair<int, int> location);
    void changePiecePosition(std::pair<int, int> destination);
    std::pair<int, int>* getMoveSet();
    int getPlayerPossession();
    friend std::ostream& operator<< (std::ostream &out, const chessPiece &p);
};
