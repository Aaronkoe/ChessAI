/*TODO
implement special move rules (castling/en pasante)
check/checkmate
complex input, used to distinguish multiple different possible piece movements
first player/second player input
move invalids if moving through any piece or onto friendly piece
allow file input, with two options:
  skip to latest board state
  step through game, slowly or by user input
*/

#include <iostream>
#include <cstdlib>
#include <stdexcept>
#include "chessboard.h"


using namespace std;


chessBoard::chessBoard() {
  int col, row;
  pair<int, int> piecePosition;
  for (col = 0; col <= 7; col++) {
    for (row = 0; row <= 7; row++) {
      piecePosition.first = col;
      piecePosition.second = row;
      if (row == 1) {
        board[col][row] = chessPiece('p', piecePosition);
      } else if (row == 0) {
          switch (col) {
            case 0:
            case 7:
              board[col][row] = chessPiece('r', piecePosition);
              break;
            case 1:
            case 6:
              board[col][row] = chessPiece('n', piecePosition);
              break;
            case 2:
            case 5:
              board[col][row] = chessPiece('b', piecePosition);
              break;
            case 3:
              board[col][row] = chessPiece('q', piecePosition);
              break;
            case 4:
              board[col][row] = chessPiece('k', piecePosition);
              break;
          }
      } else if (row == 6) {
        board[col][row] = chessPiece('P', piecePosition);
      } else if (row == 7) {
          switch (col) {
            case 0:
            case 7:
              board[col][row] = chessPiece('R', piecePosition);
              break;
            case 1:
            case 6:
              board[col][row] = chessPiece('N', piecePosition);
              break;
            case 2:
            case 5:
              board[col][row] = chessPiece('B', piecePosition);
              break;
            case 3:
              board[col][row] = chessPiece('Q', piecePosition);
              break;
            case 4:
              board[col][row] = chessPiece('K', piecePosition);
              break;
          }
      } else {
        board[col][row] = chessPiece(' ', piecePosition);
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
  int c = 0;
  int col, row;
  pair<int, int>* matches = new pair<int, int> [9];
  matches[8] = make_pair(-1, -1);
  for (col = 0; col <= 7; col++) {
    for (row = 0; row <= 7; row++) {
      if (board[col][row].piece == piece) {
        matches[c] = make_pair(col, row);
        c++;
      }
    }
  }
  matches[c] = make_pair(-1,-1);
  if (c <= 0) {
    delete[] matches;
    throw invalid_argument("Could not find piece position: err 1");
  } else if (c == 1) {
    pair<int, int> piecePosition;
    piecePosition.first = matches[0].first;
    piecePosition.second = matches[0].second;
    delete[] matches;
    return piecePosition;
  } else {
    return findCorrectPiece(destination, matches);
  }
}

pair<int, int> chessBoard::findCorrectPiece(pair<int, int> destination, pair<int, int> matches[]) {
  int i = 0;
  int c = 0;
  pair<int, int>* validMoveMatches = new pair<int, int> [11];
  validMoveMatches[10] = make_pair(-1,-1);
  while (matches[i].first != -1) {
    if (destInMoveSet(destination, matches[i])) {
      validMoveMatches[c] = matches[i];
      c++;
    }
  i++;
  }
  if (c < 1) {
    delete[] validMoveMatches;
    throw invalid_argument("Could not find piece position");
  } else if (c == 1) {
    pair<int, int> validMoveMatch;
    validMoveMatch.first = validMoveMatches[0].first;
    validMoveMatch.second = validMoveMatches[0].second;
    delete[] validMoveMatches;
    return validMoveMatch;
  } else if (c >  1) {
    delete[] validMoveMatches;
    throw invalid_argument("Too many piece matches, possible invalid syntax, try adding an identifier");
  }
}

bool chessBoard::destInMoveSet(pair<int, int> destination, pair<int, int> piecePosition) {
  pair<int, int>* validMoves = board[piecePosition.first][piecePosition.second].getMoveSet();
  //validMoves = checkMoveConflicts(validMoves);
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

//pair<int, int>* chessBoard::checkMoveConflicts(pair<int, int> moveSet) {
 // }TODO change the end moveset signifier to -2, and make a end current manouver
   //move set to -1. then, have this function check each moveset subset up until
   //-1, removing any values that occur after a square that has a non ' ' character.
void chessBoard::printMoveSet(pair<int, int> moveSet[]) {
  int i = 0;
  while (moveSet[i].first >= 0) {
    cout << "moveSet[" << i << "] = "<<moveSet[i].first<<", "<<moveSet[i].second<<endl;
    i++;
  }
  cout << "moveSet[" << i << "] = "<<moveSet[i].first<<", "<<moveSet[i].second<<endl;
  return;
}

void chessBoard::changeSpot(pair<int, int> dest, pair<int, int> orig) {
  board[orig.first][orig.second].changePiecePosition(dest);
  board[dest.first][dest.second] = board[orig.first][orig.second];
  board[orig.first][orig.second].piece = ' ';
  board[orig.first][orig.second].whiteOrBlack = 0;
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
  board[col][row].piece = chr;
  return;
}

int main() {
  chessBoard myBoard;
  myBoard.printBoard();
  string move;
  cin >> move;
  do {
    myBoard.movePiece(move);
    myBoard.printBoard();
    cin >> move;
  } while (myBoard.validMove(move));
  int possess = myBoard.board[1][1].getPlayerPossession();
  cout << "\nplayer: " << possess;
  return 1;
}
