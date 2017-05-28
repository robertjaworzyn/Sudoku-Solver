#include <iostream>
#include <cstdio>
#include <ctime>
#include "sudoku.h"
#include <chrono>

using namespace std;

int main() {

  char board[9][9];

  /* This section illustrates the use of the pre-supplied helper functions. */
  cout << "============== Pre-supplied functions ==================" << endl << endl;

  cout << "Calling load_board():" << endl;
  load_board("easy.dat", board);

  cout << endl << "Displaying Sudoku board with display_board():" << endl;
  display_board(board);
  cout << "Done!" << endl << endl;
 
  cout << "====================== Question 1 ======================" << endl << endl;

  load_board("easy.dat", board);
  cout << "Board is ";
  if (!is_complete(board))
    cout << "NOT ";
  cout << "complete." << endl << endl;

  load_board("easy-solution.dat", board);
  cout << "Board is ";
  if (!is_complete(board))
    cout << "NOT ";
    cout << "complete." << endl << endl;
  
  
  cout << "====================== Question 2 ======================" << endl << endl;

  load_board("easy.dat", board);

  // Should be OK
  cout << "Putting '4' into A1 is ";
  if (!make_move("A1", '4', board))
    cout << "NOT ";
  cout << "a valid move. The board is:" << endl;
  display_board(board);

  // write more tests
  
  cout << "====================== Question 3 ======================" << endl << endl;

  load_board("easy.dat", board);
  if (save_board("easy-copy.dat", board))
    cout << "Save board to 'easy-copy.dat' successful." << endl;
  else
    cout << "Save board failed." << endl;
  cout << endl;
 
  cout << "====================== Question 4 ======================" << endl << endl;
  
  load_board("easy.dat", board);
  if (solve_board(board)) {
    cout << "The 'easy' board has a solution:" << endl;
    display_board(board);
  }
  else
  {
    cout << "A solution cannot be found." << endl;
    display_board(board);
  }
  cout << endl;
  
  load_board("medium.dat", board);
  if (solve_board(board)) {
    cout << "The 'medium' board has a solution:" << endl;
    display_board(board);
  }
  else
  {
    cout << "A solution cannot be found." << endl;
    display_board(board);
  }
  cout << endl;
  
  cout << "====================== Question 5 ======================" << endl << endl;

  load_board("mystery1.dat", board);
  
  chrono::time_point<chrono::system_clock> start, end;
  start = chrono::system_clock::now();
  
  if (solve_board(board)) {
    cout << "The 'mystery1' board has a solution:" << endl;
    display_board(board);
  }
  else
  {
    cout << "A solution cannot be found." << endl;
    display_board(board);
  }
  cout << endl;
  end = chrono::system_clock::now();
  chrono::duration<double> elapsed_seconds = end - start;

  cout << "Mystery Board 1 takes " << elapsed_seconds.count() << " seconds to solve." << endl;
  
  load_board("mystery2.dat", board);
  if (solve_board(board)) {
    cout << "The 'mystery2' board has a solution:" << endl;
    display_board(board);
  }
  else
  {
    cout << "A solution cannot be found." << endl;
    display_board(board);
  }
  cout << endl;
  
  load_board("mystery3.dat", board);

  start = chrono::system_clock::now();
  
  if (solve_board(board)) {
    cout << "The 'mystery3' board has a solution:" << endl;
    display_board(board);
  }
  else
  {
    cout << "A solution cannot be found." << endl;
    display_board(board);
  }
  cout << endl;
  end = chrono::system_clock::now();
  elapsed_seconds = end - start;
  cout << "Mystery Board 3 takes " << elapsed_seconds.count() << " seconds to solve." << endl;
  
  // write more tests

  return 0;
}
