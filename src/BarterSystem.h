#ifndef BARTERSYSTEM_H
#define BARTERSYSTEM_H

#include <string>
#include <iostream>
#include <vector>

class BarterSystem
{
public:
  //define variables
  int productCount;
  double startingAmount;

  //special var to signal recursive instances to stop
  int stopSignal;

  //[from][to]
  std::vector<std::vector<int> > adjList;
  std::vector<std::vector<double> > exchangeRatio;
  std::vector<double> startingAmounts;
  std::vector<double> endingAmounts;

  //define constructor
  BarterSystem(int productCount);

  //define methods
  void traverse(int vertex, std::string sequence, double runningAmount);

  //define helper methods
  std::string intToString(int integer);
};

#endif
