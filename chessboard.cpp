/*TODO
implement special move rules (castling/en pasante)
check/checkmate
complex input, used to distinguish multiple different possible piece movements
first player/second player input
allow file input, with two options:
  skip to latest board state
  step through game, slowly or by user input
*/

#include <iostream>
#include <cstdlib>
#include <stdexcept>
#include "chessboard.h"


using namespace std;

/*used to validate the length of the input string move
 *outputs the int length of the string*/
int getLen(string str);

/*creates a chessboard object with the standard setup of pieces.
 *lowercase symbols represent black pieces, uppercase represents white.
 *black pieces are placed in board coordinates [0, 0] - [1, 7]
 *white pieces are placed in board coordinates [6, 0] - [7, 7]
 */
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

/*printBoard() displays the board on the screen*/
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

void chessBoard::playGame() {
  string move;
  while (true) {
    printBoard();
    do {
      cout << "Player 1, what is your move: ";
      cin >> move;
    } while (!(validMove(move, 1, 0)));
    movePiece(move);
    printBoard();
    do {
      cout << "Player 2, what is your move: ";
      cin >> move;
    } while (!(validMove(move, 1, 1)));
    movePiece(move);
  }
  return;
}

/*movePiece: the main part of the program
 *precondition: string move is a string describing the desired move based on 
 *Algebraic Chess Game notation 
 *the move based on the rules of chess may or may not be valid.

 *invariant: if the move is a valid move, (regardless of whose turn it is, as
 *that functionality is not yet implemented) it will modify the board so that
 *the input move has taken place. Any opposing pieces in the destination of
 *the move will be eliminated from the game*/
void chessBoard::movePiece(string move) {
  char piece = getPiece(move);
  pair<int, int> identifier = getIdentifier(move);
  pair<int, int> destination = getDestination(move);
  pair<int, int> origination = findPiece(piece, destination, identifier);
  if (origination == make_pair(-1, -1)) {
    cout << "invalid move, try again\n";
    return;
  }
  changeSpot(destination, origination);
  return;
}

/*findPiece is an auxillary method for movePiece()
 *precondition: findPiece takes in a character that represents the piece to be
 *moved, and a destination for that piece to be moved to
 *further implementation will make use of the ident parameter, which will be
 *used to solve ambiguity in moves, i.e. two knights that could move to the
 *same space.

 *invariant: findPiece returns a pair<int, int> with the location of the
 *piece desired to be moved by logical deduction. If no piece was found, or
 *more than one piece is found, int pair (-1, -1) is returned*/
pair<int, int> chessBoard::findPiece(char piece, pair<int, int> destination,
                                                       pair<int, int> ident) {
  int c = 0;
  int col, row;
  pair<int, int>* matches = new pair<int, int> [9];
  matches[8] = make_pair(-1, -1);
  if (ident != make_pair(-1, -1)) {
    if (ident.second == -1) {
      for (row = 0; row <= 7; row++) {
        if (board[ident.first][row].piece == piece) {
          matches[c] = make_pair(ident.first, row);
          c++;
        }
      }
    } else if (ident.first == -1) {
      for (col = 0; col <= 7; col++) {
        if (board[col][ident.second].piece == piece) {
          matches[c] = make_pair(col, ident.second);
          c++;
        }
      }
    } else {
      if (board[ident.first][ident.second].piece == piece) {
        matches[c] = make_pair(ident.first, ident.second);
        c++;
      }
    }
  } else {
    for (col = 0; col <= 7; col++) {
      for (row = 0; row <= 7; row++) {
        if (board[col][row].piece == piece) {
          matches[c] = make_pair(col, row);
          c++;
        }
      }
    }
  }
  matches[c] = make_pair(-1,-1);
  if (c <= 0) {
    delete[] matches;
    return make_pair(-1, -1);
  } else {
    return findCorrectPiece(destination, ident, matches);
  }
}

/*findCorrectPiece ensures implements the logical deduction in order to find 
 *the desired piece to be moved
 *precondition: matches[] is an array created by the callee of this function, 
 *findPiece(), that contains the coordinates of the possible matches.
 
 *invariant: by cross checking the destination with the possible moves of a 
 *piece at each location stored in matches[], findCorrectPiece either returns
 *the coordinates of the desired piece to be moved, or the pair (-1, -1) if
 *it did not successfully narrow down the possibilities*/
pair<int, int> chessBoard::findCorrectPiece(pair<int, int> destination, pair<int, int> ident, pair<int, int> matches[]) {
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
  validMoveMatches[c] = make_pair(-1, -1);
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

/*destInMoveSet checks whether the destination of a desired move is in the move
 *set of the piece getting checked
 *precondition: there is a piece located on the board at the coordinate of 
 *piecePosition
 *invariant: returns a bool, true if the destination is in the move set of a the
 *piece at piecePosition, else false*/
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

/*debugging function, prints the moveset passed to it in a readable manner*/
void chessBoard::printMoveSet(pair<int, int> moveSet[]) {
  int i = 0;
  while (moveSet[i].first >= 0) {
    cout << "moveSet[" << i << "] = "<<moveSet[i].first<<", "<<moveSet[i].second<<endl;
    i++;
  }
  cout << "moveSet[" << i << "] = "<<moveSet[i].first<<", "<<moveSet[i].second<<endl;
  return;
}

/*changeSpot takes care of the actual movement of a piece from one spot to another
 *as well as the destruction of a piece if necessary
 *precondition: origination is the starting coordinates of the piece to be moved,
 *dest is the destination to move the piece to

 *invariant: changeSpot modifies the values held by the board so that the desired
 *change is realized*/
void chessBoard::changeSpot(pair<int, int> dest, pair<int, int> orig) {
  board[orig.first][orig.second].changePiecePosition(dest);
  board[dest.first][dest.second] = board[orig.first][orig.second];
  board[orig.first][orig.second].piece = ' ';
  board[orig.first][orig.second].whiteOrBlack = 0;
  return;
}

/*validMove is a priliminary validation function that checks to make sure the 
 *input string is the correct length and is made up of the correct characters
 */
bool chessBoard::validMove(string move, int checkCase, int playerTurn) {
  int len;
  if (checkCase) {
    if (playerTurn) {
      if (move[0] < 'a') {
        cout << "check validMove: False err 11";
        return false;
      }
    } else {
      if (move[0] > 'Z') {
        cout << "check validMove: False err 12";
        return false;
      }
    }
  }
  char x;
  for (len = 0; move[len] != '\0'; len++);
  if (len < 3 || len > 5) {
    cout << "check validMove: False err 1\n";
    return false;
  }
  if (len == 3) {
    x = move[0];
    if (x != 'p' && x != 'r' && x != 'n' && x != 'b' && x != 'k' && x != 'q' &&
        x != 'P' && x != 'R' && x != 'N' && x != 'B' && x != 'K' && x != 'Q') {
      cout << "check validMove: False err 2\n";
      return false;
    }
    x = move[1];
    if (x < 'a' || x > 'h') {
      cout << "check validMove: False err 3\n";
      return false;
    }
    x = move[2];
    if (x < '0' || x > '8'){
      cout << "check validMove: False err 4\n";
      return false;
    }
  } else if (len == 4) {
    char x = move[0];
    if (x != 'p' && x != 'r' && x != 'n' && x != 'b' && x != 'k' && x != 'q' &&
        x != 'P' && x != 'R' && x != 'N' && x != 'B' && x != 'K' && x != 'Q') {
      cout << "check validMove: False err 5\n";
      return false;
    }
    x = move[1];
    if ((x < 'a' || x > 'h') && (x < '0' && x > '8')) {
      cout << "check validMove: False err 6\n";
      return false;
    }
    x = move[2];
    if (x < 'a' || x > 'h') {
      cout << "check validMove: False err 7\n";
      return false;
    }
    x = move[3];
    if (x < '0' || x > '8'){
      cout << "check validMove: False err 8\n";
      return false;
    }
  } else {
    x = move[0];
    if (x != 'p' && x != 'r' && x != 'n' && x != 'b' && x != 'k' && x != 'q' &&
        x != 'P' && x != 'R' && x != 'N' && x != 'B' && x != 'K' && x != 'Q') {
      cout << "check validMove: False err 9\n";
      return false;
    }
    x = move[1];
    if ((x < 'a' || x > 'h') && (x < '0' && x > '8')) {
      cout << "check validMove: False err 10\n";
      return false;
    }
    x = move[2];
    if ((x < 'a' || x > 'h') && (x < '0' && x > '8')) {
      cout << "check validMove: False err 11\n";
      return false;
    }
    x = move[3];
    if (x < 'a' || x > 'h') {
      cout << "check validMove: False err 12\n";
      return false;
    }
    x = move[4];
    if (x < '0' || x > '8'){
      cout << "check validMove: False err 13\n";
      return false;
    }
  }
  return true;
}

/*getDestination returns the destination as a pair of ints based on the input
 *string move*/
pair<int, int> chessBoard::getDestination(string move) {
  int len = getLen(move);
  int col = move[len - 2] - 'a';
  int row = move[len - 1] - '0' - 1;
  cout << endl<<endl<<"destination is: "<<col<<", "<<row<<endl;
  return make_pair(col, row);
}

/*getIdentifier returns the identifiers as a pair of ints. this fucntion is
 *not yet used*/
pair<int, int> chessBoard::getIdentifier(string move) {
  int len = getLen(move);
  if (len == 4) {
    if (int(move[1]) >= 'a') {
      return make_pair(int(move[1] - 'a'), -1);
    } else {
      return make_pair(-1, int(move[1] - '1'));
    }
  } else if (len == 5) {
    return make_pair(move[1] - 'a', move[2] - '1');
  }
  return make_pair(-1, -1);
}

/*getPiece returns the piece character as a char based on the input string move
 */
char chessBoard::getPiece(string move) {
  return move[0];
}

/*manualWrite is a debugging function used to force the board state to change so
 *that the character chr is at the coordinate specified by col and row*/
void chessBoard::manualWrite(int col, int row, char chr) {
  board[col][row].piece = chr;
  return;
}

/*getLen returns the lenght of an input string as an int*/
int getLen(string str) {
  int len;
  for (len = 0; str[len] != '\0'; len++);
  return len;
}

/*driver of the chess program*/
int main() {
  chessBoard myBoard;
  myBoard.playGame();
  return 1;
}
