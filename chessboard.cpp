//HELLO
/*TODO
split code into headers and .cpp file
implement a piece class instead of using chars
replace malloc commands with new
close memory leaks using free(ptr*)
implement special move rules (castling/en pasante)
check/checkmate
complex input, used to distinguish multiple different possible piece movements
first player/second player input
move invalids if moving through any piece or onto friendly piece
*/

#include <iostream>
#include <cstdlib>
#include <stdexcept>
#include "chessboard.h"

using namespace std;


chessBoard::chessBoard() {
  int col, row;
  for (col = 0; col <= 7; col++) {
    for (row = 0; row <= 7; row++) {
      if (row == 1) {
        board[col][row] = 'p';
      } else if (row == 0) {
          switch (col) {
            case 0:
            case 7:
              board[col][row] = 'r';
              break;
            case 1:
            case 6:
              board[col][row] = 'n';
              break;
            case 2:
            case 5:
              board[col][row] = 'b';
              break;
            case 3:
              board[col][row] = 'q';
              break;
            case 4:
              board[col][row] = 'k';
              break;
          }
      } else if (row == 6) {
        board[col][row] = 'P';
      } else if (row == 7) {
          switch (col) {
            case 0:
            case 7:
              board[col][row] = 'R';
              break;
            case 1:
            case 6:
              board[col][row] = 'N';
              break;
            case 2:
            case 5:
              board[col][row] = 'B';
              break;
            case 3:
              board[col][row] = 'Q';
              break;
            case 4:
              board[col][row] = 'K';
              break;
          }
      } else {
        board[col][row] = ' ';
      }
    }
  }
}

void chessBoard::printBoard() {
  int col, row;
  for (col = 0; col <= 7; col++){
    cout << "  +===============================+\n";
    cout << col + 1;
    cout << " |";
    for (row = 0; row <= 7; row++){
      cout << " ", cout << board[row][col], cout << " ";
      cout << "|";
    }
    cout << "\n";
  }
  cout << "  +===============================+\n";
  cout << "    a   b   c   d   e   f   g   h\n";
}

void chessBoard::movePiece(string move) {
  char piece = getPiece(move);
  pair<int, int> destination = getDestination(move);
  pair<int, int> origination = findPiece(piece, destination);
  changeSpot(destination, origination);
  return;
}

pair<int, int> chessBoard::findPiece(char piece, pair<int, int> destination) {
  cout << "destination = " << destination.first << ", "<< destination.second << endl;
  int c = 0;
  int col, row;
  pair<int, int>* matches = (pair<int, int>*) malloc(sizeof(pair<int,int>) * 9);
  matches[8] = make_pair(-1, -1);
  for (col = 0; col <= 7; col++) {
    for (row = 0; row <= 7; row++) {
      if (board[col][row] == piece) {
        matches[c] = make_pair(col, row);
        cout<<matches[c].first<<", "<<matches[c].second<<" || ";
        c++;
      }
    }
  }
  matches[c] = make_pair(-1,-1);
  cout<<endl;
  if (c <= 0) {
    throw invalid_argument("Could not find piece position: err 1");
  } else if (c == 1) {
    return  matches[0];
  } else {
    return findCorrectPiece(destination, matches);
  }
}

pair<int, int> chessBoard::findCorrectPiece(pair<int, int> destination, pair<int, int> matches[]) {
  int i = 0;
  int c = 0;
  pair<int, int>* validMoveMatches = (pair<int,int>*) malloc(sizeof(pair<int,int>) * 11);
  validMoveMatches[10] = make_pair(-1,-1);
  while (matches[i].first != -1) {
    if (destInMoveSet(destination, matches[i])) {
      validMoveMatches[c] = matches[i];
      c++;
    }
  i++;
  }
  if (c < 1) {
    throw invalid_argument("Could not find piece position");
  } else if (c == 1) {
    return validMoveMatches[0];
  } else if (c >  1) {
    throw invalid_argument("Too many piece matches, possible invalid syntax, try adding an identifier");
  }
}

bool chessBoard::destInMoveSet(pair<int, int> destination, pair<int, int> piecePosition) {
  pair<int, int>* validMoves = getMoveSet(piecePosition);
  int i = 0;
  int c = 0;
  while (validMoves[c].first >= 0) {
    if (destination == validMoves[c]) {
      return true;
    }
    c++;
  }
return false;
}

pair<int, int>* chessBoard::getMoveSet(pair<int, int> piecePosition) {
  char piece = board[piecePosition.first][piecePosition.second];
  pair<int, int>* validMoves = (pair<int, int>*) malloc(sizeof(pair<int, int>) * 30);
  int i = 1, j = 0, c = 0;
  switch (piece) {
    case 'p':
      validMoves[0] = make_pair(piecePosition.first, piecePosition.second + 1);
      validMoves[1] = make_pair(piecePosition.first, piecePosition.second + 2);
      c = 2;
      break;
    case 'P':
      validMoves[0] = make_pair(piecePosition.first, piecePosition.second - 1);
      validMoves[1] = make_pair(piecePosition.first, piecePosition.second - 2);
      c = 2;
      break;
    case 'r': case 'R':
      while (piecePosition.first + i < 8) {
        validMoves[c] = make_pair(piecePosition.first + i, piecePosition.second);
        i++;
        c++;
      }
      i = 0;
      while (piecePosition.first - i >= 0) {
        validMoves[c] = make_pair(piecePosition.first - i, piecePosition.second);
        i++;
        c++;
      }
      i = 0;
      while (piecePosition.second + i < 8) {
        validMoves[c] = make_pair(piecePosition.first, piecePosition.second + i);
        i++;
        c++;
      }
      i = 0;
      while (piecePosition.second - i >= 0) {
        validMoves[c] = make_pair(piecePosition.first, piecePosition.second - i);
        i++;
        c++;
      }
      i = 0;
      break;
    case 'n': case 'N':
      if (piecePosition.first - 2 >= 0 && piecePosition.second - 1 >= 0) {
        validMoves[c] = make_pair(piecePosition.first - 2, piecePosition.second - 1);
        c++;
      }
      if (piecePosition.first - 1 >= 0 && piecePosition.second - 2 >= 0) {
        validMoves[c] = make_pair(piecePosition.first - 1, piecePosition.second - 2);
        c++;
      }
      if (piecePosition.first - 2 >= 0 && piecePosition.second + 1 < 8) {
        validMoves[c] = make_pair(piecePosition.first - 2, piecePosition.second + 1);
        c++;
      }
      if (piecePosition.first + 2 < 8 && piecePosition.second - 1 >= 0) {
        validMoves[c] = make_pair(piecePosition.first + 2, piecePosition.second - 1);
        c++;
      }
      if (piecePosition.first - 1 >= 0 && piecePosition.second + 2 < 8) {
        validMoves[c] = make_pair(piecePosition.first - 1, piecePosition.second + 2);
        c++;
      }
      if (piecePosition.first + 1 < 8 && piecePosition.second + 2 < 8) {
        validMoves[c] = make_pair(piecePosition.first + 1, piecePosition.second + 2);
        c++;
      }
      if (piecePosition.first + 2 < 8 && piecePosition.second + 1 < 8) {
        validMoves[c] = make_pair(piecePosition.first + 2, piecePosition.second + 1);
        c++;
      }
      if (piecePosition.first + 1 < 8 && piecePosition.second - 2 >= 0) {
        validMoves[c] = make_pair(piecePosition.first + 1, piecePosition.second - 2);
        c++;
      }
      break;
    case 'b': case 'B':
      while (piecePosition.first + i < 8 && piecePosition.second + i < 8) {
        validMoves[c] = make_pair(piecePosition.first + i, piecePosition.second + i);
        i++;
        c++;
      }
      i = 0;
      while (piecePosition.first - i >= 0 && piecePosition.second + i < 8) {
        validMoves[c] = make_pair(piecePosition.first - i, piecePosition.second + i);
        i++;
        c++;
      }
      i = 0;
      while (piecePosition.first + i < 8 && piecePosition.second - i >= 0) {
        validMoves[c] = make_pair(piecePosition.first + i, piecePosition.second - i);
        i++;
        c++;
      }
      i = 0;
      while (piecePosition.first - i >= 0 && piecePosition.second - i >= 0) {
        validMoves[c] = make_pair(piecePosition.first - i, piecePosition.second - i);
        i++;
        c++;
      }
      i = 0;
      break;
    case 'q': case 'Q':
      while (piecePosition.first + i < 8) {
        validMoves[c] = make_pair(piecePosition.first + i, piecePosition.second);
        i++;
        c++;
      }
      i = 0;
      while (piecePosition.first - i >= 0) {
        validMoves[c] = make_pair(piecePosition.first - i, piecePosition.second);
        i++;
        c++;
      }
      i = 0;
      while (piecePosition.second + i < 8) {
        validMoves[c] = make_pair(piecePosition.first, piecePosition.second + i);
        i++;
        c++;
      }
      i = 0;
      while (piecePosition.second - i >= 0) {
        validMoves[c] = make_pair(piecePosition.first, piecePosition.second - i);
        i++;
        c++;
      }
      i = 0;
      while (piecePosition.first + i < 8 && piecePosition.second + i < 8) {
        validMoves[c] = make_pair(piecePosition.first + i, piecePosition.second + i);
        i++;
        c++;
      }
      i = 0;
      while (piecePosition.first - i >= 0 && piecePosition.second + i < 8) {
        validMoves[c] = make_pair(piecePosition.first - i, piecePosition.second + i);
        i++;
        c++;
      }
      i = 0;
      while (piecePosition.first + i < 8 && piecePosition.second - i >= 0) {
        validMoves[c] = make_pair(piecePosition.first + i, piecePosition.second - i);
        i++;
        c++;
      }
      i = 0;
      while (piecePosition.first - i >= 0 && piecePosition.second - i >= 0) {
        validMoves[c] = make_pair(piecePosition.first - i, piecePosition.second - i);
        i++;
        c++;
      }
      break;
    case 'k': case 'K':
      for (i = -1; i <= 1; i++) {
        for (j = -1; j <= 1; j++) {
          if (piecePosition.first + i < 8 && piecePosition.first + i >= 0 && piecePosition.second + j < 8 && piecePosition.second + j >= 0) {
            validMoves[c] = make_pair(piecePosition.first + i, piecePosition.second + j);
            c++;
          }
        }
      }
      break;
    }
  validMoves[c] = make_pair(-1,-1);
  printMoveSet(validMoves);
  return validMoves;
}

void chessBoard::printMoveSet(pair<int, int> moveSet[]) {
  int i = 0;
  while (moveSet[i].first >= 0) {
    cout << "moveSet[" << i << "] = "<<moveSet[i].first<<", "<<moveSet[i].second<<endl;
    i++;
  }
  cout << "moveSet[" << i << "] = "<<moveSet[i].first<<", "<<moveSet[i].second<<endl;
  return;
}

void chessBoard::changeSpot(pair<int, int> destination, pair<int, int> origination) {
  board[destination.first][destination.second] = board[origination.first][origination.second];
  board[origination.first][origination.second] = ' ';
  return;
}

bool chessBoard::validMove(string move) {
  if (int(move[0]) > 'z' || int(move[0]) < 'A') {
    cout << "check validMove: False\n";
    return false;
  }
  if (int(move[0]) > 'z' || int(move[0]) < 'A') {
    cout << "check validMove: False\n";
    return false;
  }
  if (int(move[2]) > '9' || int(move[2]) < '0') {
    cout << "check validMove: False\n";
    return false;
  }
  return true;
}

pair<int, int> chessBoard::getDestination(string move) {
  int col = move[1] - 'a';
  int row = move[2] - '0' - 1;
  return make_pair(col, row);
}

char chessBoard::getPiece(string move) {
  return move[0];
}

void chessBoard::manualWrite(int col, int row, char chr) {
  board[col][row] = chr;
  return;
}

int main() {
  chessBoard myBoard;
  myBoard.printBoard();
  string move;
  cout << "enter a move: ";
  cin >> move;
  do {
    myBoard.movePiece(move);
    myBoard.printBoard();
    cout <<endl<<"enter a move: ";
    cin >> move;
  } while (myBoard.validMove(move));
  return 1;
}
