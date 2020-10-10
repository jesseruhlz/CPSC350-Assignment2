#include <iostream>
#include <fstream>
#include <cmath>
#include <ctime>
#include <iomanip>
#include <cstdlib>
#include <array>
#include <string>
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif
using namespace std;

//outputs the given grid out to an outfile
void writeMessage(string message, string fileName)
{
  if (fileName != "")
  {
    ofstream outfile(fileName, fstream::app);
    if (outfile.is_open())
    {
      outfile << message << endl;
      outfile.close();
    }
  }
  else
  {
    cout << message << endl;
  }
}

//this function calculates the next geneartion for a classic matrix of original size
int ** nextGenerationClassic(int **a, int x, int y, string fileName)
{

  cout << "input: " << endl;
  for (int i = 0; i < x; i++)
  {
    for (int j = 0; j < y; j++)
    {
      cout << a[i][j] << " ";
    }
    cout << endl;
  }


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
            //skips the neighbor
            continue;
          if (i == 0 & j == 0)
            continue;
          //increment counter for each live neighbor
          aliveNeighbors += a[l + i][m + j];
        }

      //remove counter
      //aliveNeighbors -= a[l][m];
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
      {
        future[l][m] = 1;
      }
    }
  }


  cout << "Next Generation Classic: " << endl;
  for (int i = 0; i < x; i++)
  {
    for (int j = 0; j < y; j++)
    {
      cout << future[i][j] << " ";
    }
    cout << endl;
  }
  //prints the updated classic cell to outfile
  string line= "";
  for (int i = 0; i < x; i++)
  {
    for (int j = 0; j < y; j++)
    {
      //cout << futureAug[i][j] << " ";
      if(future[i][j] == 0)
        line +=  "-";
      else
        line += "X";
    }
    //cout << endl;
    writeMessage(line,fileName);
    line = "";
  }
  return future;
}

//calculates the next generation of a mirror or torus matrix
int ** nextGenerationAugmented(int **a, int s, int t, string fileName)
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
          // skip the center cell
          if (i == 0 & j == 0)
            continue;

          aliveNeighbors += a[l + i][m + j];
        }

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
    }
  }
  //outputs grid to text file by writing it as a string
  string line= "";
  for (int i = 1; i <= s; i++)
  {
    for (int j = 1; j <= t; j++)
    {
      //cout << futureAug[i][j] << " ";
      if(futureAug[i][j] == 0)
        line +=  "-";
      else
        line += "X";
    }
    //cout << endl;
    writeMessage(line,fileName);
    line = "";
  }
  return futureAug;
}
//creates a new matrix, with 2 extra rows and columns
//calculates what the borders should now be filled with
int ** donutMatrix(int **a, int s, int t, string fileName)
{
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
  //this segment goes through and makes the top and bottom of the outer donut
  //the oppsite of the inner border
  for (int i = 1; i < t + 1; i++)
  {
    donut[0][i] = donut[s][i];
    donut[s+1][i] = donut[1][i];
  }
  //this segment goes through and makes the sides of the outer donut
  //the oppsite of the inner border
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
  //passes the augmented matrix into the function to calulate its next gen



  return donut;
  //nextGenerationAugmented(donut, s, t, fileName);
}

int ** mirrorMatrix(int **a, int s, int t, string fileName)
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
  return mirror;
  //nextGenerationAugmented(mirror, s, t, fileName);
  //nextGenerationClassic(mirror, s, t);
}

//converts a given string to be all upper case
string toUpperFunction(string value)
{
  //char str[value.length()] = value;
  string rtn = "";
  for (int i = 0; i < value.length(); i++)
  {
    rtn += toupper(value[i]);
  }
  return rtn;
}

//tests if the cell will ever be full of 1's or 0's
//if so it terminates the program
int testIfStable(int **grid,int genCount, int numRows, int numColumns)
{
  int count;
  //counts the sum of all the elements in the 2d array
  for (int i = 0; i < numRows; i++)
  {
    for(int j = 0; j < numColumns; j++)
    {
      count += grid[i][j];
    }
  }
  //if the sum is zero, it means that the grid comprises of all zeros
  if (count == 0)
  {
    cout << "All cells within the matrix have died. It is stable." << endl;
    return 1;
  }
  //if rows * columns is 1, then that means that all the elements are a 1
  //due to 1^n
  if (count == numRows * numColumns)
  {
    cout << "All cells within the matrix are alive. It is stable." << endl;
    return 1;
  }
  return 0;
}
int testIfStableAug(int **grid,int genCount, int numRows, int numColumns)
{
  int count;
  //counts the sum of all the elements in the 2d array
  for (int i = 1; i <= numRows; i++)
  {
    for(int j = 1; j <= numColumns; j++)
    {
      count += grid[i][j];
    }
  }
  //if the sum is zero, it means that the grid comprises of all zeros
  if (count == 0)
  {
    cout << "All cells within the matrix have died. It is stable." << endl;
    return 1;
  }
  //if rows * columns is 1, then that means that all the elements are a 1
  //due to 1^n
  if (count == numRows * numColumns)
  {
    cout << "All cells within the matrix are alive. It is stable." << endl;
    return 1;
  }
  return 0;
}



int main(/*int argc, char **argv*/)
{
  string outputFile = "";
  string fileName = "";
  string userInputType;
  int genCount, numRows, numColumns;
  genCount = 0;
  float initialPopulationDensity;
  //ask the user what type of grid they want
  cout << "Do you want to provide a file map of the world, or would you like a random configuration?" << endl;
  cout << "If providing file map, type 'A' " << endl;
  cout << "If want random assignment, type 'B' " << endl;

  cin >> userInputType;

  //cout << userInputType << endl;
  if (!(toUpperFunction(userInputType) == "A" || toUpperFunction(userInputType) == "B"))
  {
    cout << "INVALID ENTRY FOR " + userInputType << endl;
    return 0;
  }

  //asks the mode user wants to run in
  //if invalid mode terminate the program
  cout << "What mode do you want to run the matrix in?" << endl;
  cout << "For Classic Mode, type 'CLASSIC': "<< endl;
  cout << "For Torus Mode, type 'TORUS' " << endl;
  cout << "For Mirror Mode, type 'MIRROR' " << endl;
  string modeType;
  cin >> modeType;
  if (!(toUpperFunction(modeType) == "CLASSIC" || toUpperFunction(modeType) == "TORUS" || toUpperFunction(modeType) == "MIRROR"))
  {
    cout << "INVALID ENTRY FOR " + modeType << endl;
    return 0;
  }

  //asks the user if they want to directly output all generations to a txt files
  //or if they want to print it to the screen and pause in between each generation
  cout << "Type 'PAUSE' to pause in between the generations. " << endl;
  cout << "Or output to a file by typing 'OUTPUT'." << endl;
  string runCase;
  cin >> runCase;
  //if user input is not of the key word, terminate the program
  if (!(toUpperFunction(runCase) == "PAUSE" || toUpperFunction(runCase) == "OUTPUT"))
  {
    cout << "INVALID ENTRY FOR " + runCase << endl;
    return 0;
  }
  if (toUpperFunction(runCase) == "OUTPUT")
  {
    cout << "Enter a file name to output to: " << endl;
    cin >> outputFile;
  }

  //opens the given txt file and reads in the grid
  ifstream myfile;
  if (toUpperFunction(userInputType) == "A")
  {
    cout << "Enter file name to analyze: " << endl;
    cin >>fileName;
    myfile.open(fileName);
    if (myfile.good())
    {
      myfile >> numRows >> numColumns;
      cout <<numRows << endl;
      cout << numColumns << endl;
    }
  }
  //reads in the user data for the random grid
  else if (toUpperFunction(userInputType) == "B")
  {
    cout << "Enter the amount of rows you want in the world: " << endl;
    cin >> numRows;
    cout << "Enter the amount of columns you want in the world: " << endl;
    cin >> numColumns;
    //This will determine how full the randomly generated matrix will be
    cout << "Choose a decimal number (to the hundredth place) between 0 and 1: " << endl;

    cin >> initialPopulationDensity;
    if(initialPopulationDensity == 0 || initialPopulationDensity == 1)
    {
      cout << "Error" << endl;
      cout << "Enter a valid number: "<< endl;
    }
  }

  //creates a dynamic 2d array
  int **grid = new int*[numRows];
  for (int i = 0; i < numRows; ++i)
  {
    grid[i] = new int[numColumns];
  }
  for (int i = 0; i < numRows; i++)
  {
    for (int j = 0; j < numColumns; j++)
    {
      //initializes the 2d array to be full of zeros
      grid[i][j] = 0;
    }
  }

  if (toUpperFunction(userInputType) == "A")
  {
    //copies the char 2d array into an int 2d array
    char **arr = new char*[numRows];
    //read in elements from txt and allocates it to char array
    for (int g = 0; g < numRows; g++)
    {
      arr[g] = new char[numColumns];
      for (int f = 0; f < numColumns; f++)
      {
        myfile >> arr[g][f];
      }
    }
    //converts arr to grid, therefore changing its value
    //replaces the 'X's with 1's and '-'s with 0's
    //passes the grid into out txt file or to screen
    writeMessage("Generation " + to_string(genCount), outputFile);
    string line= "";
    for (int i = 0; i < numRows; i++)
    {
      grid[i] = new int[numColumns];
    }
    for (int i = 0; i < numRows; i++)
    {
      for (int j = 0; j < numColumns; j++)
      {
        line += arr[i][j];
        if(arr[i][j] == 'X')
        {
          grid[i][j] = 1;
        }
        if(arr[i][j] == '-')
        {
          grid[i][j] = 0;
        }
        //cout << arr[i][j] << " ";
      }
      writeMessage(line,outputFile);
      line = "";
      //cout << endl;
    }
  }

  else if (toUpperFunction(userInputType) == "B")
  {
    //to find amount of full cells in the user generated matrix
    int amountFullCells;
    amountFullCells = (numRows * numColumns) * initialPopulationDensity;
    cout << numRows << endl;
    cout << numColumns << endl;

    srand((unsigned)time(NULL));

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
            if (grid[i][j] == 1)
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
          grid[x][y] = 1;
      }
      plottedFullCells++;
    }

    writeMessage("Generation: " + to_string(genCount), outputFile);
    string line= "";
    for (int i = 0; i < numRows; i++)
    {
      for (int j = 0; j < numColumns; j++)
      {
        if(grid[i][j] == 0)
          line +=  "-";
        else
          line += "X";
      }
      cout << endl;
      writeMessage(line,outputFile);
      line = "";
    }
  }
  //takes the return grids and copies them to be able to be used in main
  int **donutGrid = donutMatrix(grid, numRows, numColumns, outputFile);
  int ** mirrorGrid = mirrorMatrix(grid, numRows, numColumns, outputFile);


  //loops through the functions to create the future generations
  int isStable = 0;
  while(isStable == 0)
  {
    genCount++;
    string msg = (string)"Generation: " + to_string(genCount);
    writeMessage(msg, outputFile);
    if (toUpperFunction(modeType) == "CLASSIC")
    {
      //passes the original generation into nextGenerationClassic
      grid = nextGenerationClassic(grid, numRows, numColumns, outputFile);
      //checks to see if the grid is full of zeros or ones
      //if not, proceed with the loop
      isStable = testIfStable(grid, genCount, numRows,numColumns);
    }
    else if (toUpperFunction(modeType) == "TORUS")
    {
      if (genCount > 1)
      {
        donutGrid = donutMatrix(donutGrid, numRows, numColumns, outputFile);
      }
      //passes in the original generation of the augmented grid to nextGenerationAugmented
      donutGrid = nextGenerationAugmented(donutGrid, numRows, numColumns, outputFile);
      isStable = testIfStableAug(donutGrid, genCount, numRows, numColumns);
    }
    else if (toUpperFunction(modeType) == "MIRROR")
    {
      if (genCount > 1)
      {
        mirrorGrid = mirrorMatrix(mirrorGrid, numRows, numColumns, outputFile);
      }
      //passes in the original generation of the augmented grid to nextGenerationAugmented
      mirrorGrid = nextGenerationAugmented(mirrorGrid, numRows, numColumns, outputFile);
      isStable = testIfStableAug(mirrorGrid, genCount, numRows, numColumns);
    }
    //pauses the while loop for 5 seconds if the user wants to view each generation
    if(toUpperFunction(runCase) == "PAUSE")
    {
      //system("pause") would not work so using sleep() instead
      sleep(5);
    }
  }
  return 0;
}
