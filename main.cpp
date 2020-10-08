#include <iostream>
#include <fstream>
#include <cmath>
#include <ctime>
#include <iomanip>
#include <cstdlib>
#include <array>
using namespace std;
//#include "GameOfLife.h"

//thi function calculates the next geneartion for a classic matrix
void nextGenerationClassic(int **a, int x, int y)
{
  int **future = new int*[x];
  for (int i = 0; i < x; ++i)
  {
    future[i] = new int[y];
  }
  //checking every row and column
  for(int l = 0; l < x; l++)
  {
    for (int m = 0; m < y; m++)
    {
      int aliveNeighbors = 0;
      //setting an offset for the row and columns
      for (int i = -1; i <= 1; i++)
        for (int j = -1; j <= 1; j++)
        {
          //checking boundaries of the matrix
          if((l+i <0) || (l+i > x-1) || (m+j <0) || (m+j > y))
            //skips the nieghbor
            continue;
          //increment counter for each live neighbor
          aliveNeighbors += a[l + i][m + j];
        }
      //remove counter
      aliveNeighbors -= a[l][m];
      //determining whether the selected cell will live or die
      //alive cell is lonely and dies
      if (a[l][m] == 1 && aliveNeighbors <= 1)
        future[l][m] = 0;
      //empty cell is created
      else if (a[l][m] == 0 && aliveNeighbors == 3)
        future[l][m] = 1;
      //alive cell stays stable
      else if (a[l][m] == 1 && aliveNeighbors == 3)
        future[l][m] = 1;
      //alive cell is dead
      else if (a[l][m] == 1 && aliveNeighbors >= 4)
        future[l][m] = 0;
      //alive cell is stable
      else if (a[l][m] == 1 && aliveNeighbors == 2)
        future[l][m] = a[l][m];
      //else if (a[l][m] == 0 && aliveNeighbors == 2)
        //future[l][m] = a[l][m];
    }
  }
  //prints the updated classic cell
  cout << "Next Generation Classic: " << endl;
  for (int i = 0; i < x; i++)
  {
    for (int j = 0; j < y; j++)
    {
      cout << future[i][j] << " ";
    }
    cout << endl;
  }
}

//calculates the next generation of a mirror or torus matrix
void nextGenerationAugmented(int **a, int s, int t)
{
  //new matrix for the next generation
  int **futureAug = new int*[s + 2];
  for (int i = 0; i < s + 2; ++i)
  {
    futureAug[i] = new int[t + 2];
  }
  //loops through the "inner matrix"
  for(int l = 1; l <= s; l++)
  {
    for (int m = 1; m <= t; m++)
    {
      int aliveNeighbors = 0;
      for (int i = -1; i <= 1; i++)
        for (int j = -1; j <= 1; j++)
        {
          aliveNeighbors += a[l + i][m + j];
        }

      aliveNeighbors -= a[l][m];

      //cell is lonely and dies
      if (a[l][m] == 1 && aliveNeighbors <= 1)
        futureAug[l][m] = 0;
      //cell is created
      else if (a[l][m] == 0 && aliveNeighbors == 3)
        futureAug[l][m] = 1;
      else if (a[l][m] == 1 && aliveNeighbors == 3)
        futureAug[l][m] = 1;
      //cell is dead
      else if (a[l][m] == 1 && aliveNeighbors >= 4)
        futureAug[l][m] = 0;
      //cell is stable
      else if (a[l][m] == 1 && aliveNeighbors == 2)
        futureAug[l][m] = a[l][m];
      //else if (a[l][m] == 0 && aliveNeighbors == 2)
        //future[l][m] = a[l][m];
    }
  }
  //prints the updated augmented matrix
  cout << "Next Generation Augmented: " << endl;
  for (int i = 1; i <= s; i++)
  {
    for (int j = 1; j <= t; j++)
    {
      cout << futureAug[i][j] << " ";
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

  //copies the original matrix into an "inner matrix" surrounded by a border of 0's
  for (int i = 0; i <= s - 1; i++)
  {
    for(int j = 0; j <= t - 1; j++)
    {
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
  //makes "outer" upper left corner the "inner" bottom right value
  donut[0][0] = donut[s][t];
  //makes "outer" bottom right corner the "inner" upper left value
  donut[t + 1][s + 1] = donut [1][1];
  //makes "outer" bottom left corner the "inner" upper right value
  donut[s + 1][0] = donut[1][t];
  //makes the "outer" upper right corner the "inner" lower left value
  donut[0][t + 1] = donut[s][1];
  /*
  cout << "Original Donut Matrix: " << endl;
  for (int i = 0; i < s + 2; i++)
  {
    for (int j = 0; j < t + 2; j++)
    {
      cout << donut[i][j] << " ";
    }
    cout << endl;
  }*/
  //passes the augmented matrix into the function to calulate its next gen
  nextGenerationAugmented(donut, s, t);
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

  //makes "outer" upper left corner the value of the "inner" upper left corner
  mirror[0][0] = mirror[1][1];
  //makes "outer" bottom right corner value of "inner" botom right corner
  mirror[t + 1][s + 1] = mirror [s][t];
  //makes "outer" bottom left corner the value of "inner bottom left corner"
  mirror[s + 1][0] = mirror[s][1];
  //makes "outer" upper right corner the value of "inner" upper right corner
  mirror[0][t + 1] = mirror[1][t];
  /*
  cout << "Original Mirror Matrix: " << endl;
  for (int i = 0; i < s + 2; i++)
  {
    for (int j = 0; j < t + 2; j++)
    {
      cout << mirror[i][j] << " ";
    }
    cout << endl;
  }*/
  nextGenerationAugmented(mirror, s, t);

  //nextGenerationClassic(mirror, s, t);
  //return mirror;
}

int main(/*int argc, char **argv*/)
{
  cout << "Do you want to provide a file map of the world, or would you like a random configuration?" << endl;
  cout << "If providing file map, type 'A' " << endl;
  cout << "If want random assignment, type 'B' " << endl;
  char userInputType;
  cin >> userInputType;
  //will pass in the txt file and convert it from - and * to 0 and 1
  if (userInputType == 'A' || userInputType == 'a')
  {
    string fileName;
    cout << "Enter file name to analyze: " << endl;
    cin >>fileName;

    ifstream myfile;
    int Rows, Cols;
    //char **arr;
    myfile.open(fileName);
    if (myfile.good())
    {
      myfile >> Rows >> Cols;
      char **arr = new char*[Rows];
      cout << Rows << endl;
      cout << Cols << endl;
      for (int g = 0; g < Rows; g++)
      {
        arr[g] = new char[Cols];
        for (int f = 0; f < Cols; f++)
        {
          myfile >> arr[g][f];
          //if(arr[g][f] == 'X')
            //arr[g][f] = 1;
          //cout << arr[g][f] << " ";
        }
        //cout << endl;
      }
      //copies the char 2d array into an int 2d array
      //replaces the 'X's with 1's and '-'s with 0's
      int **grid = new int*[Rows];
      for (int i = 0; i < Rows; i++)
      {
        grid[i] = new int[Cols];
      }
      for (int i = 0; i < Rows; i++)
      {
        for (int j = 0; j < Cols; j++)
        {
          //(int)arr[g][f]  = grid[i][j]
          if(arr[i][j] == 'X')
          {
            grid[i][j] = 1;
            //cout << arr[i][j] << "is x";
          }
          if(arr[i][j] == '-')
          {
            grid[i][j] = 0;
            //cout << arr[i][j] << "is 0";
          }
        }
      }
      for(int i = 0; i < Rows; i++)
      {
        for (int j = 0; j < Cols; j++)
        {
          cout << grid[i][j] << " ";
        }
        cout << endl;
      }
      //myfile.close(fileName);
      //delete [] arr;
      //convertCharArray(arr,Rows,Cols);
      cout << "What mode do you want to run the matrix in?" << endl;
      cout << "For Classic Mode, type 'CLASSIC': "<< endl;
      cout << "For Torus Mode, type 'TORUS' " << endl;
      cout << "For Mirror Mode, type 'MIRROR' " << endl;
      string modeType;
      cin >> modeType;

      if (modeType == "CLASSIC")
      {
        nextGenerationClassic(grid, Rows, Cols);
      }
      else if (modeType == "TORUS")
      {
        donutMatrix(grid, Rows, Cols);
      }
      else if (modeType == "MIRROR")
      {
        mirrorMatrix(grid, Rows, Cols);
      }
    }



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

    //creates a dynamic 2d array
    int **a = new int*[numRows];
    for (int i = 0; i < numRows; ++i)
    {
      a[i] = new int[numColumns];
    }

    //to find amount of full cells in the user generated matrix
    int amountFullCells;
    amountFullCells = (numRows * numColumns) * initialPopulationDensity;
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
      //checks to see if an index has already been plotted
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
    cout << "What mode do you want to run the matrix in?" << endl;
    cout << "For Classic Mode, type 'CLASSIC': "<< endl;
    cout << "For Torus Mode, type 'TORUS' " << endl;
    cout << "For Mirror Mode, type 'MIRROR' " << endl;
    string modeType;
    cin >> modeType;

    if (modeType == "CLASSIC")
    {
      nextGenerationClassic(a, numRows, numColumns);
    }
    else if (modeType == "TORUS")
    {
      donutMatrix(a, numRows, numColumns);
    }
    else if (modeType == "MIRROR")
    {
      mirrorMatrix(a, numRows, numColumns);
    }
    //delete [] a;
  } //end of if statement where user inputs their own data
  return 0;
}
