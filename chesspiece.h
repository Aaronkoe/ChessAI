#include <iostream>
class chessPiece {
  public:
    char piece;
    std::pair<int, int> location;
    chessPiece();
    chessPiece(char pieceClass, std::pair<int, int> location);
    void changePieceSpot(std::pair<int, int> destination);
    std::pair<int, int>* getMoveSet();
    friend std::ostream& operator<< (std::ostream &out, const chessPiece &p);
};
