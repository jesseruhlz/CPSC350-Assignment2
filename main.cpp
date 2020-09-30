#include <iostream>
#include <fstream>
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
    cout << "Enter the amount of rows you want in the world: " << endl;
    int numRows, numColumns;
    cin >> numRows;
    cout << "Enter the amount of columns you want in the world: " << endl;
    cin >> numColumns;
    cout << "Choose a decimal number (to the hundredth place) between 0 and 1: " << endl;
    float initalPopulationDensity;
    cin >> initalPopulationDensity;
    if(initalPopulationDensity == 0 || initalPopulationDensity == 1)
    {
      cout << "Error" << endl;
      cout << "Enter a valid number: "<< endl;
    }

    char a[numRows][numColumns];
    
  }

  return 0;
}
