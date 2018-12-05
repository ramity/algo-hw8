#ifndef BARTERSYSTEM_H
#define BARTERSYSTEM_H

#include <string>
#include <iostream>
#include <vector>

class BarterSystem
{
public:
  // define variables
  int productCount;

  // generated path to which the output will be placed
  std::string outputFilePath;

  // amount of the given start product
  double startingAmount;


  // special var to signal recursive instances to stop
  int stopSignal;

  // [from][to]
  std::vector<std::vector<int> > adjList;
  std::vector<std::vector<double> > exchangeRatio;
  std::vector<std::vector<double> > startingAmounts;
  std::vector<std::vector<double> > endingAmounts;


  // define constructor
  BarterSystem(int productCount, std::string outputFilePath);

  // define methods
  void traverse(int vertex, std::vector<int> sequence, double runningAmount, std::vector<std::vector<int> > localAdjList);

  // define helper methods
  std::string intToString(int integer);
  bool containsCycle(std::vector<int> sequence);
};

#endif
