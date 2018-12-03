#include <string>//string
#include <iostream>//cout
#include <fstream>//ifstream
#include <cstdlib>//exit

#include "BarterSystem.cpp"

// converts an int to string - allows for the usage of this file without c++11
std::string intToString(int integer)
{
    char characters[32];
    sprintf(characters, "%d", integer);
    return (std::string) characters;
}

int main()
{
  // pretty newline
  std::cout << std::endl;

  std::ifstream inputFile;

  for(int z = 1;z <= 4;z++)
  {
    // debugging output - denote the start of an inputFile test
    std::cout << "TEST: " << z << " start" << std::endl;

    // generate filePath and utilize to open inputFile
    std::string filePath = "./input" + intToString(z) + ".txt";
    inputFile.open(filePath.c_str());

    // check if inputFile open operation succeeded
    if(!inputFile)
    {
      std::cout << "Unable to open file" << std::endl;
      exit(1);
    }

    // pull the productCount from the inputFile
    int productCount;
    inputFile >> productCount;

    // init barterSystem with productCount
    BarterSystem barterSystem(productCount);

    // temp var for while loop conditional
    int check;

    // if the inputFile no longer has anything to output, exit loop
    while(inputFile >> check)
    {
      // init
      int productStart;
      int productEnd;
      double productStartAmount;
      double productEndAmount;
      double productRatio;

      // populate
      productStart = check;
      inputFile >> productEnd;
      inputFile >> productStartAmount;
      inputFile >> productEndAmount;

      // calculate
      productRatio = productEndAmount / productStartAmount;

      // decrement to 0 indexed values
      productStart--;
      productEnd--;

      // debugging output for verifying data pulled from from inputFile
      // std::cout << "productStart: " << productStart << std::endl;
      // std::cout << "productEnd: " << productEnd << std::endl;
      // std::cout << "productStartAmount: " << productStartAmount << std::endl;
      // std::cout << "productEndAmount: " << productEndAmount << std::endl;
      // std::cout << "productRatio: " << productRatio << std::endl;
      // std::cout << "productMaxAmount: " << productMaxAmount << std::endl;

      // update
      barterSystem.adjList[productStart].push_back(productEnd);
      barterSystem.exchangeRatio[productStart][productEnd] = productRatio;
      barterSystem.startingAmounts[productStart] = productStartAmount;
      barterSystem.endingAmounts[productEnd] = productEndAmount;
    }

    // close the file
    inputFile.close();

    // begin custom recursive DFS traversal
    barterSystem.traverse(0, "0", barterSystem.startingAmount, barterSystem.adjList);

    if(!barterSystem.stopSignal)
    {
      // efficient market - worst case
    }

    // debugging output - denote the end of a inputFile test
    std::cout << "TEST: " << z << " end" << std::endl << std::endl;
  }

  return 0;
}
