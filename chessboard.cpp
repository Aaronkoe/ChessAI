#include <iostream>
#include <stdexcept>

using namespace std;

class chessBoard {
  private:
    pair<int, int> findPiece(string move);
    pair<int, int> findCorrectPiece(string move, pair<int, int> matches[]);
    void movePiece (const string move);
    void changeSpot(string move, pair<int, int> spot);
    pair<int, int> getDestination(string move);
    char getPiece(string move);
  public:
    char board[8][8];
    chessBoard();
    void printBoard(void);
    void movePiece(const string move);
};

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
              board[col][row] = 'k';
              break;
            case 4:
              board[col][row] = 'q';
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
              board[col][row] = 'K';
              break;
            case 4:
              board[col][row] = 'Q';
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
    cout << "+===============================+\n";
    cout << "|";
    for (row = 0; row <= 7; row++){
      cout << " ", cout << board[row][col], cout << " ";
      cout << "|";
    }
    cout << "\n";
  }
  cout << "+===================================+\n";
}

void chessBoard::movePiece(const string move) {
  char piece = getPiece(move);
  pair<int, int> destination = getDestination(move);
  pair<int, int> origination = findPiece(piece, destination);
  changeSpot(destination, origination);
}

pair<int, int> chessBoard::findPiece(char piece, pair<int, int> destination) {
  int c = 0;
  int col, row
  pair<int, int> matches[8];
  for (col = 0; col <= 7; col++) {
    for (row = 0; row <= 7; row++) {
      if (board[col][row] == piece) {
        matches[c] = make_pair(col, row);
        c++;
      }
    }
  }
  if (c <= 0) {
    throw invalid_argument("Could not find piece position");
  } else if (c == 1) {
    return matches[0];
  } else {
    return matches[findCorrectPiece(destination, matches)];
  }
}

int chessBoard::findCorrectPiece(pair<int, int> destination, pair<int, int>[] matches) {
  int i;
  int c = 0;
  pair<int, int> validMoveMatches[10];
  for (i = 0; i < 10; i++) {
    if (destInValidMoves(destination, matches[i]) {
      validMoveMatches[c] = matches[i];
      c++;
    }
  }
  if (c < 1) {
    throw invalid_argument("Could not find piece position");
  } else if (c == 1) {
    return validMoveMatches[0];
  } else if (c >  1) {
    throw invalid_argument("Too many piece matches, possible invalid syntax, try adding an identifier");
  }
}

pair<int, int> chessBoard::getDestination(string move) {
  int col = move[1] - 'a';
  int row = move[2] - '0';
  return make_pair(col, row);
}

char chessBoard::getPiece(string move) {
  return move[0];
}

int main() {
  chessBoard myBoard;
  myBoard.printBoard();
  return 1;
}

      
