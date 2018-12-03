#include <string>//string
#include <iostream>//cout
#include <vector>//vector
#include <stdio.h>//sprintf
#include <algorithm>//sort

#include "BarterSystem.h"

BarterSystem::BarterSystem(int productCount)
{
  this->productCount = productCount;
  this->startingAmount = 1.0;
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

bool BarterSystem::containsCycle(std::string sequence)
{
  // check if the sequence is large enough for a cycle
  if(sequence.size() < 1)
  {
    return false;
  }

  // sort the sequence
  std::sort(sequence.begin(), sequence.end());

  for(int z = 0;z < sequence.length();z++)
  {
    if(sequence[z] == sequence[z + 1])
    {
      return true;
    }
  }

  return false;
}

void BarterSystem::traverse(int vertex, std::string sequence, double runningAmount, std::vector<std::vector<int> > localAdjList)
{
  std::cout << "Checking vertex: " << vertex << std::endl;
  std::cout << "Current sequence: " << sequence << std::endl;

  //check if a recursive instance has already found the market to be inefficient
  if(this->stopSignal)
  {
    return;
  }

  //check if a loop has occured
  if(this->containsCycle(sequence))
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


  while(localAdjList[vertex].size() > 0 && !this->stopSignal)
  {
    //get the first element
    int newVertex = localAdjList[vertex].front();
    std::string newSequence = sequence + this->intToString(newVertex);
    double newRunningAmount = runningAmount * this->exchangeRatio[vertex][newVertex];

    //remove newVertex from adjList to prevent endlessly looping
    localAdjList[vertex].erase(localAdjList[vertex].begin());

    this->traverse(newVertex, newSequence, newRunningAmount, localAdjList);
  }
}
