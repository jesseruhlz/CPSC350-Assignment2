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

    //creating matrix with user Input
    // needs to randomly allocate '-' and 'X'
    // with 'X' being placed randomly using the population density
    char a[numRows][numColumns];

    srand((unsigned)time(NULL));
    for (int i = 0; i < numRows; i++)
    {
      for (int j = 0; j < numColumns; j++)
      {
        //a[numRows][numColumns] = (rand() % (int)initialPopulationDensity);

        //this line will initialize the matrix with '-', for empty cells
        a[numRows][numColumns] = '-';

      }
    }

    for (int i = 0; i < numRows; i++)
    {
      for (int j = 0; j < numColumns; j++)
      {
        cout << a[numRows][numColumns] << " ";
      }
      cout << endl;
    }


  }

  return 0;
}
