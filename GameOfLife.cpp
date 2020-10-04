/*#include "GameOfLife.h"

//default constructor
GameOfLife::GameOfLife()
{
  //my2DArray = new char[128][128];
  //mSize = 128;
}

//overloaded constructor
GameOfLife::GameOfLife(int maxRow, int maxCol)
{
  my2DArray = new char[maxRow][maxCol];
}

GameOfLife::~GameOfLife()
{
  delete my2DArray;
}



/*void GameOfLife::nextGenerationClassic(char *a, int numRow, int numColumns)
{
  future = new char[numRows][numColumns];
  //char future[numRows][numColumns];
  for(int l = 1; l < numRows - 1; l++)
  {
    for (int m = 1; m < numColumns - 1; m++)
    {
      int aliveNeighbors = 0;
      for (int i = -1; i <= 1; i++)
        for (int j = -1; j <= 1; j++)
          aliveNeighbors += a[l + i][m + j];
      aliveNeighbors -= a[l][m];
      cout<< "aliveNeighbors" << aliveNeighbors;

      //cell is lonely and dies
      if (a[l][m] == 'X' && aliveNeighbors < 1)
        future[l][m] = '-';
      //cell is created
      else if (a[l][m] == '-' && aliveNeighbors == 3)
        future[l][m] == 'X';
      //cell is dead
      else if (a[l][m] == 'X' && aliveNeighbors >= 4)
        future[l][m] = 'X';
      else
        future[l][m] = a[l][m];
    }
  }
  cout << "Next Generation: " << endl;
  for (int i = 0; i < numRows; i++)
  {
    for (int j = 0; j < numColumns; j++)
    {
      cout << future[i][j] << " ";
    }
    cout << endl;
  }
}*/
