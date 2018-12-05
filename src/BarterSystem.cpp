#include <string>//string
#include <iostream>//cout
#include <vector>//vector
#include <stdio.h>//sprintf
#include <algorithm>//sort
#include <fstream>//fstream::out

#include "BarterSystem.h"

BarterSystem::BarterSystem(int productCount, std::string outputFilePath)
{
  this->productCount = productCount;
  this->outputFilePath = outputFilePath;

  this->startingAmount = 1.0;
  this->adjList.resize(productCount,std::vector<int>());
  this->exchangeRatio.resize(productCount,std::vector<double>(productCount, 0));
  this->startingAmounts.resize(productCount,std::vector<double>(productCount, 0));
  this->endingAmounts.resize(productCount,std::vector<double>(productCount, 0));
  this->stopSignal = false;
}

// converts an int to string - allows for the usage of this file without c++11
std::string BarterSystem::intToString(int integer)
{
    char characters[32];
    sprintf(characters, "%d", integer);
    return (std::string) characters;
}

bool vectorCompare(int i, int j)
{
  return (i < j);
}

bool BarterSystem::containsCycle(std::vector<int> sequence)
{
  // check if the sequence is large enough for a cycle
  if(sequence.size() < 3)
  {
    return false;
  }

  // std::cout << "sequence.front()" << std::endl;
  // std::cout << sequence.front() << std::endl;
  // std::cout << "sequence.back()" << std::endl;
  // std::cout << sequence.back() << std::endl;

  // sort the sequence
  std::sort(sequence.begin(), sequence.end(), vectorCompare);

  for(int z = 0;z < sequence.size();z++)
  {
    if(sequence[z] == sequence[z + 1])
    {
      // std::cout << "sequence[z]" << std::endl;
      // std::cout << sequence[z+1] << std::endl;
      // std::cout << "sequence[z+1]" << std::endl;
      // std::cout << sequence[z+1] << std::endl;

      return true;
    }
  }

  return false;
}

void BarterSystem::traverse(int vertex, std::vector<int> sequence, double runningAmount, std::vector<std::vector<int> > localAdjList)
{
  std::cout << "*Checking vertex: " << vertex << std::endl;
  std::cout << "Current sequence: ";

  for(int z = 0;z < sequence.size();z++)
  {
    std:: cout << sequence[z];
  }

  std::cout << std::endl;
  std::cout << "Running amount: " << runningAmount << std::endl;

  // check if the sequence contains a cycle
  if(this->containsCycle(sequence))
  {
    // std::cout << "containsCycle!!!" << std::endl;

    if(runningAmount > this->startingAmount)
    {
      std::vector<int> localSequence;
      double localRunningAmount;

      if(sequence.front() != sequence.back())
      {
        // the sequence does not start at 0
        bool start = false;
        localRunningAmount = 1.0;

        // prove that the cycle is profitable
        for(int key = 0;key < sequence.size() - 1;key++)
        {
          if(sequence[key] == sequence.back() || start)
          {
            start = true;

            int localVertex = sequence[key];
            int localNewVertex = sequence[key + 1];
            localSequence.push_back(sequence[key]);

            localRunningAmount = localRunningAmount * this->exchangeRatio[localVertex][localNewVertex];
          }
        }

        localSequence.push_back(sequence[sequence.size() - 1]);
      }
      else
      {
        // the sequence starts at 0
        localSequence = sequence;
        localRunningAmount = runningAmount;
      }

      if(localRunningAmount > this->startingAmount)
      {
        this->stopSignal = true;

        std::cout << "Inefficient market detected:" << std::endl;

        for(int z = 0;z < localSequence.size();z++)
        {
          std:: cout << localSequence[z];
        }

        std::cout << std::endl;
        std::cout << localRunningAmount << std::endl;

        std::ofstream outputFile;
        outputFile.open(outputFilePath.c_str(), std::fstream::out);

        outputFile << "yes" << std::endl;

        for(int z = 0;z < localSequence.size();z++)
        {
          if(z < localSequence.size() - 1)
          {
            outputFile << (localSequence[z] + 1) << " ";
            outputFile << (localSequence[z + 1] + 1) << " ";
            outputFile << this->startingAmounts[localSequence[z]][localSequence[z + 1]] << " ";
            outputFile << this->endingAmounts[localSequence[z]][localSequence[z + 1]] << " ";
            outputFile << std::endl;
          }
          else
          {
            outputFile << "one kg of product " << (localSequence[z + 1] + 1) << " ";
            outputFile << "gets " << localRunningAmount << " ";
            outputFile << "kg of product " << (localSequence[z + 1] + 1) << " ";
            outputFile << "from the above sequence." << std::endl;
          }
        }

        outputFile.close();
      }
    }

    // prevent further execution
    return;
  }

  // std::cout << "VERTEX: " << vertex << " SIZE: " << localAdjList[vertex].size() << std::endl;

  while(localAdjList[vertex].size() > 0 && !this->stopSignal)
  {
    // get the first element
    int newVertex = localAdjList[vertex].front();

    std::vector<int> newSequence = sequence;
    newSequence.push_back(newVertex);

    double newRunningAmount = runningAmount * this->exchangeRatio[vertex][newVertex];

    // remove newVertex from adjList to prevent endlessly looping
    localAdjList[vertex].erase(localAdjList[vertex].begin());

    this->traverse(newVertex, newSequence, newRunningAmount, localAdjList);
  }
}
