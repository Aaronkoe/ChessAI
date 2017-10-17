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

int getLen(string str);

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
  if (origination == make_pair(-1, -1)) {
    cout << "invalid move, try again\n";
    return;
  }
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
    return make_pair(-1, -1);
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
    return make_pair(-1, -1);
  } else if (c == 1) {
    pair<int, int> validMoveMatch;
    validMoveMatch.first = validMoveMatches[0].first;
    validMoveMatch.second = validMoveMatches[0].second;
    delete[] validMoveMatches;
    return validMoveMatch;
  } else if (c >  1) {
    delete[] validMoveMatches;
    return make_pair(-1, -1);
  }
}

bool chessBoard::destInMoveSet(pair<int, int> destination, pair<int, int> piecePosition) {
  pair<int, int>* validMoves = board[piecePosition.first][piecePosition.second].getMoveSet(board);
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
  int len;
  for (len = 0; move[len] != '\0'; len++);
  if (len < 3 || len > 5) {
    cout << "check validMove: False\n";
    return false;
  }
  if (len == 3) {
    char x = move[0];
    if (x != 'p' && x != 'r' && x != 'n' && x != 'b' && x != 'k' && x != 'q' &&
        x != 'P' && x != 'R' && x != 'N' && x != 'B' && x != 'K' && x != 'Q') {
      cout << "check validMove: False\n";
      return false;
    }
    x = move[1];
    if (x < 'a' || x > 'h') {
      cout << "check validMove: False\n";
      return false;
    }
    x = move[2];
    if (x < '0' || x > '8'){
      cout << "check validMove: False\n";
      return false;
    }
  } else if (len == 4) {
    char x = move[0];
    if (x != 'p' && x != 'r' && x != 'n' && x != 'b' && x != 'k' && x != 'q' &&
        x != 'P' && x != 'R' && x != 'N' && x != 'B' && x != 'K' && x != 'Q') {
      cout << "check validMove: False\n";
      return false;
    }
    x = move[1];
    if ((x < 'a' || x > 'h') && (x < '0' && x > '8')) {
      cout << "check validMove: False\n";
      return false;
    }
    x = move[2];
    if (x < 'a' || x > 'h') {
      cout << "check validMove: False\n";
      return false;
    }
    x = move[3];
    if (x < '0' || x > '8'){
      cout << "check validMove: False\n";
      return false;
    }
  } 
  return true;
}

pair<int, int> chessBoard::getDestination(string move) {
  int len = getLen(move);
  int col = move[len - 2] - 'a';
  int row = move[len - 1] - '0' - 1;
  return make_pair(col, row);
}

char chessBoard::getPiece(string move) {
  return move[0];
}

void chessBoard::manualWrite(int col, int row, char chr) {
  board[col][row].piece = chr;
  return;
}

int getLen(string str) {
  int len;
  for (len = 0; str[len] != '\0'; len++);
  return len;
}

int main() {
  chessBoard myBoard;
  myBoard.printBoard();
  string move;
  cin >> move;
  while (true) {
    myBoard.movePiece(move);
    myBoard.printBoard();
    cout <<"new move: ";
    cin >> move;
    if (!(myBoard.validMove(move))) {
      break;
    }
  }
  return 1;
}
