#include <iostream>
using namespace std;

class Sudoku {
public:

   // Check if it's safe to place a digit at the given cell
   static bool isSafe(int sudoku[][9], int row, int col, int digit) {
       // Check column for the digit
       for (int i = 0; i < 9; i++) {
           if (sudoku[i][col] == digit) {
               return false;
           }
       }

       // Check row for the digit
       for (int j = 0; j < 9; j++) {
           if (sudoku[row][j] == digit) {
               return false;
           }
       }

       // Check 3x3 subgrid for the digit
       int sr = (row / 3) * 3;  // starting row of the grid
       int sc = (col / 3) * 3;  // starting column of the grid
       for (int i = sr; i < sr + 3; i++) {
           for (int j = sc; j < sc + 3; j++) {
               if (sudoku[i][j] == digit) {
                   return false;
               }
           }
       }

       return true; // Safe to place the digit
   }

   // Recursive function to solve the sudoku
   static bool sudokuSolver(int sudoku[][9], int row, int col) {
       // Base case: entire board is processed
       if (row == 9 && col == 0) {
           return true;
       }

       // Move to next cell
       int nxtrow = row;
       int nxtcol = col + 1;
       if (col + 1 == 9) {       // if end of row, move to next row
           nxtrow = row + 1;
           nxtcol = 0;
       }

       // If current cell is already filled, move to next cell
       if (sudoku[row][col] != 0) {
           return sudokuSolver(sudoku, nxtrow, nxtcol);
       }

       // Try placing digits from 1 to 9
       for (int digit = 1; digit <= 9; digit++) {
           if (isSafe(sudoku, row, col, digit)) {
               sudoku[row][col] = digit; // Place digit

               // Recur for next cell
               if (sudokuSolver(sudoku, nxtrow, nxtcol)) {
                   return true;
               }

               // Backtrack
               sudoku[row][col] = 0;
           }
       }

       return false; // No valid digit found
   }

   // Print the Sudoku grid
   static void printSudoku(int sudoku[][9]) {
       for (int i = 0; i < 9; i++) {
           for (int j = 0; j < 9; j++) {
               cout << sudoku[i][j] << " ";
           }
           cout << endl;
       }
   }
};

int main() {
   // Sample Sudoku puzzle with 0 representing empty cells
   int sudoku[9][9] = {
       {6, 8, 0, 0, 0, 5, 4, 3, 1},
       {0, 0, 7, 9, 0, 4, 2, 6, 5},
       {4, 2, 5, 1, 0, 0, 0, 7, 9},
       {2, 5, 8, 4, 0, 0, 0, 9, 3},
       {0, 0, 0, 5, 9, 0, 1, 0, 4},
       {0, 0, 0, 8, 6, 3, 0, 0, 7},
       {7, 1, 3, 2, 5, 8, 9, 4, 6},
       {0, 9, 0, 6, 0, 0, 0, 0, 8},
       {8, 0, 0, 0, 0, 0, 7, 0, 2}
   };

   // Try to solve the Sudoku
   if (Sudoku::sudokuSolver(sudoku, 0, 0)) {
       cout << "Solution Exists : " << endl;
       Sudoku::printSudoku(sudoku); // print the solution
   } else {
       cout << "Solution Does not Exist" << endl;
   }

   return 0;
}
