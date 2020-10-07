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
  //new matrix for the next generation
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

void donutMatrix(int **a, int s, int t)
{
  //creates a new matrix, with 2 extra rows and columns
  //fills the new outer border with zeros
  int **donut = new int*[s + 2];
  for (int i = 0; i <= s + 2; ++i)
  {
    donut[i] = new int[t + 2];
  }

  //copies the original matrix into the "inner matrix"

  for (int i = 0; i <= s - 1; i++)
  {
    for(int j = 0; j <= t - 1; j++)
    {
      //donut[c][d] = a[c][d];
      donut[i + 1][j + 1] = a[i][j];
    }
  }
  //this segment goes through and makes the sides of the outer donut
  //the oppsite of the inner border
  for (int i = 1; i < t + 1; i++)
  {
    donut[0][i] = donut[s][i];
    donut[s+1][i] = donut[1][i];
  }
  for (int j = 1; j < s + 1; j++)
  {
    donut[j][0] = donut[j][t];
    donut[j][t + 1] = donut[j][1];
  }
  //this segment calculates the out borders of the Matrix
  //makes those values the opposite corners of the inner matrix
  donut[0][0] = donut[s][t];
  donut[t + 1][s + 1] = donut [1][1];
  donut[s + 1][0] = donut[1][t];
  donut[0][t + 1] = donut[s][1];

  cout << "Original Donut Matrix: " << endl;
  for (int i = 0; i < s + 2; i++)
  {
    for (int j = 0; j < t + 2; j++)
    {
      cout << donut[i][j] << " ";
    }
    cout << endl;
  }
}

void mirrorMatrix(int **a, int s, int t)
{
  //creates a new matrix, with 2 extra rows and columns
  //fills the new outer border with zeros
  int **mirror = new int*[s + 2];
  for (int i = 0; i <= s + 2; ++i)
  {
    mirror[i] = new int[t + 2];
  }

  //copies the original matrix into the "inner matrix"

  for (int i = 0; i <= s - 1; i++)
  {
    for(int j = 0; j <= t - 1; j++)
    {
      //donut[c][d] = a[c][d];
      mirror[i + 1][j + 1] = a[i][j];
    }
  }
  //mirrors the outer rows of the "inner matrix"
  for (int i = 1; i < t + 1; i++)
  {
    mirror[0][i] = mirror[1][i];
    mirror[s+1][i] = mirror[s][i];
  }
  //mirrors the outer columns of the "inner matrix"
  for (int j = 1; j < s + 1; j++)
  {
    mirror[j][0] = mirror[j][1];
    mirror[j][t + 1] = mirror[j][t];
  }

  //this segment calculates the out borders of the Matrix
  //mirrors the corners of the inner matrix
  mirror[0][0] = mirror[1][1];
  mirror[t + 1][s + 1] = mirror [s][t];
  mirror[s + 1][0] = mirror[s][1];
  mirror[0][t + 1] = mirror[1][t];

  cout << "Original Mirror Matrix: " << endl;
  for (int i = 0; i < s + 2; i++)
  {
    for (int j = 0; j < t + 2; j++)
    {
      cout << mirror[i][j] << " ";
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
    //initializes the matrix with 0, representing empty cells
    //will use the initialPopulationDensity to determine how many Xs will be randomly initialized
    for (int i = 0; i < numRows; i++)
    {
      for (int j = 0; j < numColumns; j++)
      {
        //this line will initialize the matrix with 0, for empty cells
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
    donutMatrix(a, numRows, numColumns);
    mirrorMatrix(a, numRows, numColumns);
    //delete [] a;
  } //end of if statement where user inputs their own data
  //cout << endl;
  //a->nextGenerationClassic(*a,numRow,numColumns);

  return 0;
}
