#include <iostream>
#include <fstream>
#include <cmath>
#include <ctime>
#include <iomanip>
#include <cstdlib>
using namespace std;

//just doing work in main for now to test code
int main(int argc, char ** argv)
{
  cout << "Do you want to provide a file map of the world, or would you like a random configuration?" << endl;
  cout << "If providing file map, type 'A' " << endl;
  cout << "If want random assignment, type 'B' " << endl;
  char userInputType;
  cin >> userInputType;

  if (userInputType == 'A' || userInputType == 'a')
  {
    string fileName;
    cout << "Enter file name to analyze: " << endl;
    cin >>fileName;
  }


  if (userInputType == 'B' || userInputType == 'b')
  {
    int numRows, numColumns;
    cout << "Enter the amount of rows you want in the world: " << endl;
    cin >> numRows;
    cout << "Enter the amount of columns you want in the world: " << endl;
    cin >> numColumns;
    //This will determine how full or empty the randomly generated matrix will be
    cout << "Choose a decimal number (to the hundredth place) between 0 and 1: " << endl;
    float initialPopulationDensity;
    cin >> initialPopulationDensity;
    if(initialPopulationDensity == 0 || initialPopulationDensity == 1)
    {
      cout << "Error" << endl;
      cout << "Enter a valid number: "<< endl;
    }


    char a[numRows][numColumns];

    //to find amount of full cells in the user generated matrix
    int amountFullCells;
    amountFullCells = (numRows * numColumns) * initialPopulationDensity;
    cout << amountFullCells << endl;

    srand((unsigned)time(NULL));
    //creates the matrix with the given input to form the size
    //initializes the matrix with '-', representing empty cells
    //will use the initialPopulationDensity to determine how many Xs will be randomly initialized
    for (int i = 0; i < numRows; i++)
    {
      for (int j = 0; j < numColumns; j++)
      {
        //this line will initialize the matrix with '-', for empty cells
        a[i][j] = '-';

      }
    }

    //loop to randomly plot the full cells (X)
    int plottedFullCells = 0;
    while (plottedFullCells < amountFullCells)
    {
      //randomly generates a point in the matrix to receive the full cell (X)
      int x = rand() % numRows;
      int y = rand() % numColumns;
      int is_plotted = 0;

      for(int i = 0; i < numRows; i++)
      {
        for(int j = 0; j < numColumns; j++)
        {
          if (i == x && j == y)
          {
            if (a[i][j] == 'X')
            {
              is_plotted = 1;
              break;
            }
          }
        }
      }

      //plots the X at randomly generated element
      if(is_plotted == 0)
      {
          a[x][y] = 'X';
      }
      plottedFullCells++;
    }

    for (int i = 0; i < numRows; i++)
    {
      for (int j = 0; j < numColumns; j++)
      {
        cout << a[i][j] << " ";
      }
      cout << endl;
    }


  }

  return 0;
}
