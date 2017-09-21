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
  for (col = 2; col <= 6; col++) {
    for (row = 0; row <= 8; row++) {
      board[col][row] = ' ';
    }
  }
}

void chessBoard::printBoard() {
  int col, row;
  for (col = 0; col <= 8; col++){
    cout << "+===================================+\n";
    cout << "|";
    for (row = 0; row <= 8; row++){
      cout << " ", cout << board[col][row], cout << " ";
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

      
