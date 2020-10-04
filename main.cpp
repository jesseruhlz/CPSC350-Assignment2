#include <iostream>
#include <fstream>
#include <cmath>
#include <ctime>
#include <iomanip>
#include <cstdlib>
#include <array>
using namespace std;
//#include "GameOfLife.h"
void nextGenerationClassic(int **a, int x, int y)
{
  //char[][] future = new char[numRows][numColumns];
  //char future[x][y];
  int **future = new int*[x];
  for (int i = 0; i < x; ++i)
  {
    future[i] = new int[y];
  }
  for(int l = 0; l < x; l++)
  {
    for (int m = 0; m < y; m++)
    {
      int aliveNeighbors = 0;
      for (int i = -1; i <= 1; i++)
        for (int j = -1; j <= 1; j++)
        {
          if((l+i <0) || (l+i > x-1) || (m+j <0) || (m+j > y))
            continue;
          aliveNeighbors += a[l + i][m + j];
        }

      aliveNeighbors -= a[l][m];

      //cell is lonely and dies
      if (a[l][m] == 1 && aliveNeighbors <= 1)
        future[l][m] = 0;
      //cell is created
      else if (a[l][m] == 0 && aliveNeighbors == 3)
        future[l][m] = 1;
      else if (a[l][m] == 1 && aliveNeighbors == 3)
        future[l][m] = 1;
      //cell is dead
      else if (a[l][m] == 1 && aliveNeighbors >= 4)
        future[l][m] = 0;
      //cell is stable
      else if (a[l][m] == 1 && aliveNeighbors == 2)
        future[l][m] = a[l][m];
      //else if (a[l][m] == 0 && aliveNeighbors == 2)
        //future[l][m] = a[l][m];
    }
  }
  cout << "Next Generation: " << endl;
  for (int i = 0; i < x; i++)
  {
    for (int j = 0; j < y; j++)
    {
      cout << future[i][j] << " ";
    }
    cout << endl;
  }
}




int main(/*int argc, char **argv*/)
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

    //  char a[numRows][numColumns];
    //creates a dynamic 2d array
    int **a = new int*[numRows];
    for (int i = 0; i < numRows; ++i)
    {
      a[i] = new int[numColumns];
    }


    //to find amount of full cells in the user generated matrix
    int amountFullCells;
    amountFullCells = (numRows * numColumns) * initialPopulationDensity;
    //cout << amountFullCells << endl;
    cout << numRows << endl;
    cout << numColumns << endl;

    srand((unsigned)time(NULL));
    //creates the matrix with the given input to form the size
    //initializes the matrix with '-', representing empty cells
    //will use the initialPopulationDensity to determine how many Xs will be randomly initialized
    for (int i = 0; i < numRows; i++)
    {
      for (int j = 0; j < numColumns; j++)
      {
        //this line will initialize the matrix with '-', for empty cells
        a[i][j] = 0;

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
            if (a[i][j] == 1)
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
          a[x][y] = 1;
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
    /*for(int i = 0; i < numRows; ++i)
    {
      delete [] a[i];
    }
    */
    nextGenerationClassic(a, numRows, numColumns);
    //delete [] a;
  } //end of if statement where user inputs their own data
  //cout << endl;
  //a->nextGenerationClassic(*a,numRow,numColumns);

  return 0;
}
