#include <string>//string
#include <iostream>//cout
#include <vector>//vector
#include <stdio.h>//sprintf

#include "BarterSystem.h"

BarterSystem::BarterSystem(int productCount)
{
  this->productCount = productCount;
  this->adjList.resize(productCount,std::vector<int>());
  this->exchangeRatio.resize(productCount,std::vector<double>(productCount, 0));
  this->startingAmounts.resize(productCount, 0);
  this->endingAmounts.resize(productCount, 0);
  this->stopSignal = false;
}

// converts an int to string - allows for the usage of this file without c++11
std::string BarterSystem::intToString(int integer)
{
    char characters[32];
    sprintf(characters, "%d", integer);
    return (std::string) characters;
}

void BarterSystem::traverse(int vertex, std::string sequence, double runningAmount)
{
  //check if a recursive instance has already found the market to be inefficient
  if(this->stopSignal)
  {
    return;
  }

  std::cout << "OUT " << vertex << std::endl;

  //check if a loop has occured
  if((sequence[0] - '0') == vertex && sequence.size() > 1)
  {
    if(runningAmount > this->startingAmount)
    {
      this->stopSignal = true;

      std::cout << "Inefficient market detected:" << std::endl;
      std::cout << sequence << std::endl;
      std::cout << runningAmount << std::endl;
    }

    //prevent further execution
    return;
  }

  while(this->adjList[vertex].size() > 0)
  {
    //get the first element
    int newVertex = this->adjList[vertex].front();
    std::cout << "IN " << newVertex << std::endl;
    std::string newSequence = sequence + this->intToString(newVertex);
    double newRunningAmount = runningAmount * this->exchangeRatio[vertex][newVertex];

    //remove newVertex from adjList to prevent endlessly looping
    this->adjList[vertex].erase(this->adjList[vertex].begin());

    this->traverse(newVertex, newSequence, newRunningAmount);
  }
}
