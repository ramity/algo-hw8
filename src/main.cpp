#include <fstream>//cout
#include <iostream>//ifstream
#include <cstdlib>//exit

#include "BarterSystem.cpp"

int main()
{
  std::ifstream inputFile;

  inputFile.open("./input1.txt");

  if(!inputFile)
  {
    std::cout << "Unable to open file" << std::endl;
    exit(1);
  }

  int productCount;
  inputFile >> productCount;

  // init barterSystem with productCount
  BarterSystem barterSystem(productCount);

  int check;
  //if the inputFile no longer has anything to output, exit loop
  while(inputFile >> check)
  {
    // init
    int productStart;
    int productEnd;
    double productStartAmount;
    double productEndAmount;
    double productMaxAmount;
    double productRatio;

    // populate
    productStart = check;
    inputFile >> productEnd;
    inputFile >> productStartAmount;
    inputFile >> productEndAmount;

    // calculate
    productRatio = productEndAmount / productStartAmount;
    productMaxAmount = std::max(productStartAmount, productEndAmount);

    // decrement to 0 indexed values
    productStart--;
    productEnd--;

    std::cout << "productStart: " << productStart << std::endl;
    std::cout << "productEnd: " << productEnd << std::endl;
    std::cout << "productStartAmount: " << productStartAmount << std::endl;
    std::cout << "productEndAmount: " << productEndAmount << std::endl;
    std::cout << "productRatio: " << productRatio << std::endl;
    std::cout << "productMaxAmount: " << productMaxAmount << std::endl;
    std::cout << "startingAmountBefore: " << barterSystem.startingAmount << std::endl;

    // update
    barterSystem.adjList[productStart].push_back(productEnd);
    barterSystem.exchangeRatio[productStart][productEnd] = productRatio;
    barterSystem.startingAmounts[productStart] = productStartAmount;
    barterSystem.endingAmounts[productEnd] = productEndAmount;
    barterSystem.startingAmount += productMaxAmount;

    std::cout << "startingAmountAfter: " << barterSystem.startingAmount << std::endl;
    std::cout << std::endl;
  }

  std::cout << std::endl;

  inputFile.close();

  barterSystem.traverse(0, "0", barterSystem.startingAmount);

  std::cout << "DONE!" << std::endl;

  return 0;
}
