#include <iostream>
#include <utility>
#include <cstdlib> 

class chessPiece {
  public:
    char piece;
    chessPiece(char pieceClass);
    std::pair<int, int>* getMoveSet(std::pair<int, int> piecePosition);
    friend std::ostream& operator<< (std::ostream &out, const chessPiece &p);
};

chessPiece::chessPiece(char p) {
 piece = p;
}

std::ostream& operator<< (std::ostream &out, const chessPiece &p) {
  out << p.piece;
  return out;
}

std::pair<int, int>* chessPiece::getMoveSet(std::pair<int, int> piecePosition) {
  std::pair<int, int>* validMoves = (std::pair<int, int>*) malloc(sizeof(std::pair<int, int>) * 30);
  int i = 0, j = 0, c = 0;
  switch (piece) {
    case 'p':
      validMoves[0] = std::make_pair(piecePosition.first, piecePosition.second + 1);
      validMoves[1] = std::make_pair(piecePosition.first, piecePosition.second + 2);
      c = 2;
      break;
    case 'P':
      validMoves[0] = std::make_pair(piecePosition.first, piecePosition.second - 1);
      validMoves[1] = std::make_pair(piecePosition.first, piecePosition.second - 2);
      c = 2;
      break;
    case 'r': case 'R':
      while (piecePosition.first + i < 8) {
        validMoves[c] = std::make_pair(piecePosition.first + i, piecePosition.second);
        i++;
        c++;
      }
      while (piecePosition.first - i >= 0) {
        validMoves[c] = std::make_pair(piecePosition.first - i, piecePosition.second);
        i++;
        c++;
      }
      while (piecePosition.second + i < 8) {
        validMoves[c] = std::make_pair(piecePosition.first, piecePosition.second + i);
        i++;
        c++;
      }
      while (piecePosition.second - i >= 0) {
        validMoves[c] = std::make_pair(piecePosition.first, piecePosition.second - i);
        i++;
        c++;
      }
      break;
    case 'n': case 'N':
      if (piecePosition.first - 2 >= 0 && piecePosition.second - 1 >= 0) {
        validMoves[c] = std::make_pair(piecePosition.first - 2, piecePosition.second - 1);
        c++;
      }
      if (piecePosition.first - 1 >= 0 && piecePosition.second - 2 >= 0) {
        validMoves[c] = std::make_pair(piecePosition.first - 1, piecePosition.second - 2);
        c++;
      }
      if (piecePosition.first - 2 >= 0 && piecePosition.second + 1 < 8) {
        validMoves[c] = std::make_pair(piecePosition.first - 2, piecePosition.second + 1);
        c++;
      }
      if (piecePosition.first + 2 < 8 && piecePosition.second - 1 >= 0) {
        validMoves[c] = std::make_pair(piecePosition.first + 2, piecePosition.second - 1);
        c++;
      }
      if (piecePosition.first - 1 >= 0 && piecePosition.second + 2 < 8) {
        validMoves[c] = std::make_pair(piecePosition.first - 1, piecePosition.second + 2);
        c++;
      }
      if (piecePosition.first + 1 < 8 && piecePosition.second + 2 < 8) {
        validMoves[c] = std::make_pair(piecePosition.first + 1, piecePosition.second + 2);
        c++;
      }
      if (piecePosition.first + 2 < 8 && piecePosition.second + 1 < 8) {
        validMoves[c] = std::make_pair(piecePosition.first + 2, piecePosition.second + 1);
        c++;
      }
      if (piecePosition.first + 1 < 8 && piecePosition.second - 2 >= 0) {
        validMoves[c] = std::make_pair(piecePosition.first + 1, piecePosition.second - 2);
        c++;
      }
      break;
    case 'b': case 'B':
      while (piecePosition.first + i < 8 && piecePosition.second + i < 8) {
        validMoves[c] = std::make_pair(piecePosition.first + i, piecePosition.second + i);
        i++;
        c++;
      }
      while (piecePosition.first - i >= 0 && piecePosition.second + i < 8) {
        validMoves[c] = std::make_pair(piecePosition.first - i, piecePosition.second + i);
        i++;
        c++;
      }
      while (piecePosition.first + i < 8 && piecePosition.second - i >= 0) {
        validMoves[c] = std::make_pair(piecePosition.first + i, piecePosition.second - i);
        i++;
        c++;
      }
      while (piecePosition.first - i >= 0 && piecePosition.second - i >= 0) {
        validMoves[c] = std::make_pair(piecePosition.first - i, piecePosition.second - i);
        i++;
        c++;
      }
      break;
    case 'q': case 'Q':
      while (piecePosition.first + i < 8) {
        validMoves[c] = std::make_pair(piecePosition.first + i, piecePosition.second);
        i++;
        c++;
      }
      while (piecePosition.first - i >= 0) {
        validMoves[c] = std::make_pair(piecePosition.first - i, piecePosition.second);
        i++;
        c++;
      }
      while (piecePosition.second + i < 8) {
        validMoves[c] = std::make_pair(piecePosition.first, piecePosition.second + i);
        i++;
        c++;
      }
      while (piecePosition.second - i >= 0) {
        validMoves[c] = std::make_pair(piecePosition.first, piecePosition.second - i);
        i++;
        c++;
      }
      while (piecePosition.first + i < 8 && piecePosition.second + i < 8) {
        validMoves[c] = std::make_pair(piecePosition.first + i, piecePosition.second + i);
        i++;
        c++;
      }
      while (piecePosition.first - i >= 0 && piecePosition.second + i < 8) {
        validMoves[c] = std::make_pair(piecePosition.first - i, piecePosition.second + i);
        i++;
        c++;
      }
      while (piecePosition.first + i < 8 && piecePosition.second - i >= 0) {
        validMoves[c] = std::make_pair(piecePosition.first + i, piecePosition.second - i);
        i++;
        c++;
      }
      while (piecePosition.first - i >= 0 && piecePosition.second - i >= 0) {
        validMoves[c] = std::make_pair(piecePosition.first - i, piecePosition.second - i);
        i++;
        c++;
      }
      break;
    case 'k': case 'K':
      for (i = -1; i <= 1; i++) {
        for (j = -1; j <= 1; j++) {
          if (piecePosition.first  + i < 8 && piecePosition.first  + i >= 0 && 
              piecePosition.second + j < 8 && piecePosition.second + j >= 0) {
            validMoves[c] = std::make_pair(piecePosition.first + i, piecePosition.second + j);
            c++;
          }
        }
      }
      break;
    }
  validMoves[c] = std::make_pair(-1,-1);
  return validMoves;
}
  
