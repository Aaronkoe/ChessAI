#include <iostream>

using namespace std;

class chessBoard {
  private:
    pair<int, int> findPiece(char* move);
    void changeSpot(char* move, pair<int, int> spot);
  public:
    char board[9][9];
    chessBoard();
    void printBoard(void);
    void movePiece(const char* move);
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

void movePiece(const char* move) {
  pair<int, int> spot = findPiece(move);
  changeSpot(move, spot);
}

pair<int, int> findPiece(char* move) {
  int c = 0;
  int col, row;
  for (col = 0; col <= 7; col++) {
    for (row = 0; row <= 7; row++) {
      if (board[col][row] == move[0]) {
        c++;
      }
    }
  }
}
      

int main() {
  chessBoard myBoard;
  myBoard.printBoard();
  return 1;
}

      
