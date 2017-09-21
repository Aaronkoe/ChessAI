#include <iostream>

using namespace std;

class chessBoard {
  public:
    char board[9][9];
    chessBoard();
    void printBoard(void);
};

chessBoard::chessBoard() {
  int col, row;
  for (col = 0; col <= 7; col++) {
    for (row = 0; row <= 7; row++) {
      if (row == 1 || row == 6) {
        board[col][row] = 'p';
      } else if (row == 0 || row == 7) {
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


int main() {
  chessBoard myBoard;
  myBoard.printBoard();
  return 1;
}

      
