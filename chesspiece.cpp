#include <iostream>
#include <utility>
#include <cstdlib> 
#include "chesspiece.h"

chessPiece::chessPiece() { }

chessPiece::chessPiece(char pieceClass, std::pair<int, int> loc) {
  piece = pieceClass;
  if (piece == ' ') whiteOrBlack = 0;
  if (piece > 'a') {
    whiteOrBlack = 2;
  } else {
    whiteOrBlack = 1;
  }
  location.first = loc.first;
  location.second = loc.second;
}

std::ostream& operator<< (std::ostream &out, const chessPiece &p) {
  out << p.piece;
  return out;
}

std::pair<int, int>* chessPiece::getMoveSet(chessPiece board[8][8]) {
  std::pair<int, int> dest;
  dest.first = location.first;
  dest.second = location.second;
  std::pair<int, int>* validMoves = (std::pair<int, int>*) malloc(sizeof(std::pair<int, int>) * 30);
  int i = 1, j = 1, c = 0;
  switch (piece) {
    case 'p':
      if (checkConflict(std::make_pair(dest.first, dest.second + 1), board) == 0) {
        validMoves[c] = std::make_pair(dest.first, dest.second + 1);
        c++;
      }
      if (dest.second = 1) {
        if (checkConflict(std::make_pair(dest.first, dest.second + 2), board) == 0) {
          validMoves[c] = std::make_pair(dest.first, dest.second + 2);
          c++;
        }
      }
      break;
    case 'P':
      if (checkConflict(std::make_pair(dest.first, dest.second - 1), board) == 0) {
        validMoves[c] = std::make_pair(dest.first, dest.second - 1);
        c++;
      }
      if (dest.second = 6) {
        if (checkConflict(std::make_pair(dest.first, dest.second - 2), board) == 0) {
          validMoves[c] = std::make_pair(dest.first, dest.second - 2);
          c++;
        }
      }
      break;
    case 'r': case 'R':
      while (checkConflict(std::make_pair(dest.first + i, dest.second), board) == 0) {
        validMoves[c] = std::make_pair(dest.first + i, dest.second);
        i++;
        c++;
      }
      if (checkConflict(std::make_pair(dest.first + i, dest.second), board) == 1) {
        validMoves[c] = std::make_pair(dest.first + i, dest.second);
        i++;
        c++;
      }
      i = 1;
      while (checkConflict(std::make_pair(dest.first - i, dest.second), board) == 0) {
        validMoves[c] = std::make_pair(dest.first - i, dest.second);
        i++;
        c++;
      }
      if (checkConflict(std::make_pair(dest.first - i, dest.second), board) == 1) {
        validMoves[c] = std::make_pair(dest.first - i, dest.second);
        i++;
        c++;
      }
      i = 1;
      while (checkConflict(std::make_pair(dest.first, dest.second + i), board) == 0) {
        validMoves[c] = std::make_pair(dest.first, dest.second + i);
        i++;
        c++;
      }
      if (checkConflict(std::make_pair(dest.first, dest.second + i), board) == 1) {
        validMoves[c] = std::make_pair(dest.first, dest.second + i);
        i++;
        c++;
      }
      i = 1;
      while (checkConflict(std::make_pair(dest.first, dest.second - i), board) == 0) {
        validMoves[c] = std::make_pair(dest.first, dest.second - i);
        i++;
        c++;
      }
      if (checkConflict(std::make_pair(dest.first, dest.second - i), board) == 1) {
        validMoves[c] = std::make_pair(dest.first, dest.second - i);
        i++;
        c++;
      }
      break;
    case 'n': case 'N':
      if (checkConflict(std::make_pair(dest.first - 2, dest.second - 1), board) < 2) {
        validMoves[c] = std::make_pair(dest.first - 2, dest.second - 1);
        c++;
      }
      if (checkConflict(std::make_pair(dest.first - 1, dest.second - 2), board) < 2) {
        validMoves[c] = std::make_pair(dest.first - 1, dest.second - 2);
        c++;
      }
      if (checkConflict(std::make_pair(dest.first - 2, dest.second + 1), board) < 2) {
        validMoves[c] = std::make_pair(dest.first - 2, dest.second + 1);
        c++;
      }
      if (checkConflict(std::make_pair(dest.first + 2, dest.second - 1), board) < 2) {
        validMoves[c] = std::make_pair(dest.first + 2, dest.second - 1);
        c++;
      }
      if (checkConflict(std::make_pair(dest.first - 1, dest.second + 2), board) < 2) {
        validMoves[c] = std::make_pair(dest.first - 1, dest.second + 2);
        c++;
      }
      if (checkConflict(std::make_pair(dest.first + 1, dest.second + 2), board) < 2) {
        validMoves[c] = std::make_pair(dest.first + 1, dest.second + 2);
        c++;
      }
      if (checkConflict(std::make_pair(dest.first + 2, dest.second + 1), board) < 2) {
        validMoves[c] = std::make_pair(dest.first + 2, dest.second + 1);
        c++;
      }
      if (checkConflict(std::make_pair(dest.first + 1, dest.second - 2), board) < 2) {
        validMoves[c] = std::make_pair(dest.first + 1, dest.second - 2);
        c++;
      }
      break;
    case 'b': case 'B':
      while (checkConflict(std::make_pair(dest.first + i, dest.second + i), board) == 0) {
        validMoves[c] = std::make_pair(dest.first + i, dest.second + i);
        i++;
        c++;
      }
      if (checkConflict(std::make_pair(dest.first + i, dest.second + i), board) == 1) {
        validMoves[c] = std::make_pair(dest.first + i, dest.second + i);
        i++;
        c++;
      }
      i = 1;
      while (checkConflict(std::make_pair(dest.first - i, dest.second + i), board) == 0) {
        validMoves[c] = std::make_pair(dest.first - i, dest.second + i);
        i++;
        c++;
      }
      if (checkConflict(std::make_pair(dest.first - i, dest.second + i), board) == 1) {
        validMoves[c] = std::make_pair(dest.first - i, dest.second + i);
        i++;
        c++;
      }
      i = 1;
      while (checkConflict(std::make_pair(dest.first + i, dest.second - i), board) == 0) {
        validMoves[c] = std::make_pair(dest.first + i, dest.second - i);
        i++;
        c++;
      }
      if (checkConflict(std::make_pair(dest.first + i, dest.second - i), board) == 1) {
        validMoves[c] = std::make_pair(dest.first + i, dest.second - i);
        i++;
        c++;
      }
      i = 1;
      while (checkConflict(std::make_pair(dest.first - i, dest.second - i), board) == 0) {
        validMoves[c] = std::make_pair(dest.first - i, dest.second - i);
        i++;
        c++;
      }
      if (checkConflict(std::make_pair(dest.first - i, dest.second - i), board) == 1) {
        validMoves[c] = std::make_pair(dest.first - i, dest.second - i);
        i++;
        c++;
      }
      break;
    case 'q': case 'Q':
      while (checkConflict(std::make_pair(dest.first + i, dest.second), board) == 0) {
        validMoves[c] = std::make_pair(dest.first + i, dest.second);
        i++;
        c++;
      }
      if (checkConflict(std::make_pair(dest.first + i, dest.second), board) == 1) {
        validMoves[c] = std::make_pair(dest.first + i, dest.second);
        i++;
        c++;
      }
      i = 1;
      while (checkConflict(std::make_pair(dest.first - i, dest.second), board) == 0) {
        validMoves[c] = std::make_pair(dest.first - i, dest.second);
        i++;
        c++;
      }
      if (checkConflict(std::make_pair(dest.first - i, dest.second), board) == 1) {
        validMoves[c] = std::make_pair(dest.first - i, dest.second);
        i++;
        c++;
      }
      i = 1;
      while (checkConflict(std::make_pair(dest.first, dest.second + i), board) == 0) {
        validMoves[c] = std::make_pair(dest.first, dest.second + i);
        i++;
        c++;
      }
      if (checkConflict(std::make_pair(dest.first, dest.second + i), board) == 1) {
        validMoves[c] = std::make_pair(dest.first, dest.second + i);
        i++;
        c++;
      }
      i = 1;
      while (checkConflict(std::make_pair(dest.first, dest.second - i), board) == 0) {
        validMoves[c] = std::make_pair(dest.first, dest.second - i);
        i++;
        c++;
      }
      if (checkConflict(std::make_pair(dest.first, dest.second - i), board) == 1) {
        validMoves[c] = std::make_pair(dest.first, dest.second - i);
        i++;
        c++;
      }
      while (checkConflict(std::make_pair(dest.first + i, dest.second + i), board) == 0) {
        validMoves[c] = std::make_pair(dest.first + i, dest.second + i);
        i++;
        c++;
      }
      if (checkConflict(std::make_pair(dest.first + i, dest.second + i), board) == 1) {
        validMoves[c] = std::make_pair(dest.first + i, dest.second + i);
        i++;
        c++;
      }
      i = 1;
      while (checkConflict(std::make_pair(dest.first - i, dest.second + i), board) == 0) {
        validMoves[c] = std::make_pair(dest.first - i, dest.second + i);
        i++;
        c++;
      }
      if (checkConflict(std::make_pair(dest.first - i, dest.second + i), board) == 1) {
        validMoves[c] = std::make_pair(dest.first - i, dest.second + i);
        i++;
        c++;
      }
      i = 1;
      while (checkConflict(std::make_pair(dest.first + i, dest.second - i), board) == 0) {
        validMoves[c] = std::make_pair(dest.first + i, dest.second - i);
        i++;
        c++;
      }
      if (checkConflict(std::make_pair(dest.first + i, dest.second - i), board) == 1) {
        validMoves[c] = std::make_pair(dest.first + i, dest.second - i);
        i++;
        c++;
      }
      i = 1;
      while (checkConflict(std::make_pair(dest.first - i, dest.second - i), board) == 0) {
        validMoves[c] = std::make_pair(dest.first - i, dest.second - i);
        i++;
        c++;
      }
      if (checkConflict(std::make_pair(dest.first - i, dest.second - i), board) == 1) {
        validMoves[c] = std::make_pair(dest.first - i, dest.second - i);
        i++;
        c++;
      }
      break;
    case 'k': case 'K':
      for (i = -1; i <= 1; i++) {
        for (j = -1; j <= 1; j++) {
          if (checkConflict(std::make_pair(dest.first + i, dest.second + j), board) < 2) {
            validMoves[c] = std::make_pair(dest.first + i, dest.second + j);
            c++;
          }
        }
      }
      break;
    }
  validMoves[c] = std::make_pair(-1,-1);
  return validMoves;
}

/*checkConflict takes a destination pair<int, int>, and the current boardstate
 *checkConflict is used to determine how far a piece can move before it-
    A. runs into a friendly piece
    B. tries to go over any piece
 *checkConflict will return an int from 0,1,2
   0: there are no conflicts
   1: there is a conflict with an enemy piece, therefore the moving piece can land on the current
        tile but go no farther
   2: there is a conflict with a friendly piece or the move is out of bounds, 
        therefore the moving piece cannot land on the current tile
*/
int chessPiece::checkConflict(std::pair<int, int> dest, chessPiece board[8][8]) {
  if (dest.first < 0 || dest.first > 8 || dest.second < 0 || dest.second > 8) {
    return 2;
  }
  if (board[dest.first][dest.second].piece == ' ') {
    return 0;
  }
  if (board[dest.first][dest.second].whiteOrBlack != whiteOrBlack) {
    return 1;
  } else {
    return 2;
  }
}

void chessPiece::changePiecePosition(std::pair<int, int> destination) {
  location.first = destination.first;
  location.second = destination.second;
  return;
}  

int chessPiece::getPlayerPossession() {
  return whiteOrBlack;
}
