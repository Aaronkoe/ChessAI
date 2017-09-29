
#include <iostream>
#include <stdexcept>
using namespace std;


pair<int, int> getDestination(string move) {
  int col = move[1] - 'a';
  int row = move[2] - '0';
  return make_pair(col, row);
}


int main() {
  string move = "pc6";
  pair<int, int> destination = getDestination(move);
  cout << "pair = " << destination.first << ", " << destination.second;
  return 0;
}
