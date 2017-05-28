#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cstdlib>
#include "sudoku.h"

// global variable to count how many times solve_board is called for q5
// int count(0);

using namespace std;

/* You are pre-supplied with the functions below. Add your own 
   function definitions to the end of this file. */

/* pre-supplied function to load a Sudoku board from a file */
void load_board(const char* filename, char board[9][9]) {

  cout << "Loading Sudoku board from file '" << filename << "'... ";

  ifstream in(filename);
  if (!in)
    cout << "Failed!" << endl;
  assert(in);

  char buffer[512];

  int row = 0;
  in.getline(buffer,512);
  while (in && row < 9) {
    for (int n=0; n<9; n++) {
      assert(buffer[n] == '.' || isdigit(buffer[n]));
      board[row][n] = buffer[n];
    }
    row++;
    in.getline(buffer,512);
  }
  in.close();
  cout << ((row == 9) ? "Success!" : "Failed!") << endl;
  assert(row == 9);
}

/* internal helper function */
void print_frame(int row) {
  if (!(row % 3))
    cout << "  +===========+===========+===========+" << endl;
  else
    cout << "  +---+---+---+---+---+---+---+---+---+" << endl;
}

/* internal helper function */
void print_row(const char* data, int row) {
  cout << (char) ('A' + row) << " ";
  for (int i=0; i<9; i++) {
    cout << ( (i % 3) ? ':' : '|' ) << " ";
    cout << ( (data[i]=='.') ? ' ' : data[i]) << " ";
  }
  cout << "|" << endl;
}

/* pre-supplied function to display a Sudoku board */
void display_board(const char board[9][9]) {
  cout << "    ";
  for (int r=0; r<9; r++) 
    cout << (char) ('1'+r) << "   ";
  cout << endl;
  for (int r=0; r<9; r++) {
    print_frame(r);
    print_row(board[r],r);
  }
  print_frame(9);

}

/* function to check whether every cell in the board is filled with a digit */ 
bool is_complete(const char board[9][9])
{
  // loop over every element in the board array
  for (int i = 0; i < 9; i++)
  {
    for (int j = 0; j < 9; j++)
    {
      // if the element is not a digit return false
      if (!isdigit(board[i][j]))
	return false;
    }
  }
  // return true if there are no non-digit characters in the array
  return true;
}

/* internal helper function converting character input to
   board coordinate */
int char_to_board_position(char character)
{
  if (isalpha(character))
    return (int)(character - 'A');
  else if (isdigit(character))
    return (int)(character - '1');
  else
  {
    cerr << "INPUT IS NOT LETTER OR NUMBER" << endl;
    exit(1);
  }
}

/* checks a potential move is legal within the rules of sudoku.
   and carries it out if so */
bool make_move(char position[2], char digit, char board[9][9])
{
  int row, col, row_sector, col_sector;
  
  row = char_to_board_position(position[0]);
  col = char_to_board_position(position[1]);
  //calculate which subgrid to check
  row_sector = (row/3) * 3;
  col_sector = (col/3) * 3;

  //check position is within the sudoku grid
  if (row < 0 || row > 9 || col < 0 || col > 9)
  {
    cout << "Position out of bounds" << endl;
    return false;
  }

  //check row and column for that digit
  for (int i = 0; i < 9; i ++)
  {
    if (board[row][i] == digit || board[i][col] == digit)
      return false;
  }

  //check subgrid for repeat digit
  //TODO: FIGURE OUT WAY TO IGNORE ALREADY TESTED CELLS
  for (int r = row_sector; r < row_sector + 3; r++)
  {
    for (int c = col_sector; c < col_sector + 3; c++)
    {
      if (board[r][c] == digit)
	return false;
    }
  }
  // if it passes these tests place digit into selected position
  board[row][col] = digit;
  return true;
}

// saves board to file 
bool save_board(const char* filename, const char board[9][9])
{
  ofstream out;
  out.open(filename);

  if (!out)
  {
    cerr << "File did not open to write to" << endl;
    return false;
  } 

  for (int row = 0; row < 9; row++)
  {
    for (int col = 0; col < 9; col++)
    {
      out.put(board[row][col]);
    }
    out.put('\n');
  }
  out.close();
  return true;

}

bool solve_board(char board[9][9])
{
  // count++;
  char position[2];

  //for each cell on the board
  for (int row = 0; row < 9; row++)
  {
      for (int col = 0; col < 9; col++)
      {
	//skip cells that already have a number assigned
	if (isdigit(board[row][col]))
	  continue;

	//convert board position to character array
	position[0] = (char)('A' + row);
	position[1] = (char)('1' + col);

	//loops over the characters '1' to '9'
        for (int number = 49; number < 58; number++)
	{
	  if (make_move(position, (char)(number), board))
	  {
	    //count++;
	    /*recursively call function to check the next cell along
	      and if it solves the board eventually returns true */
	    if (solve_board(board))
	      return true;
	    //if no number in a certain cell won't solve the board, fill it with an empty space
	    else board[row][col] = (char)(32);
	  }
	    
	}
	//if no number can be placed in a cell, moves up to the previous function call
	return false;
	
      }
      
  }
  //cout << count << endl;
  return true;
  
}
