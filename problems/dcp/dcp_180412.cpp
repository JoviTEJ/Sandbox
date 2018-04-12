/******************************************************************************/
/*!
\file   dcp_180412.cpp
\author JoviTEJ
\par    url: https://github.com/JoviTEJ
\date   12/04/18
\brief
This problem was asked by Uber.
Given an array of integers, return a new array such that each element at index i of the new array is the product of all the numbers in the original array except the one at i.
For example, if our input was[1, 2, 3, 4, 5], the expected output would be[120, 60, 40, 30, 24].If our input was[3, 2, 1], the expected output would be[2, 3, 6].
Follow - up: what if you can't use division?

*/
/******************************************************************************/

#include <iostream>
#include <vector>
#include <random>
#include <functional>
#include <algorithm>

std::vector<int> GenerateVectorOfRandomNumbers(int n = 100, int lower_bound = 0, int upper_bound = 99)
{
  std::random_device rnd_device;
  std::mt19937 mersenne_engine(rnd_device());
  std::uniform_int_distribution<int> dist(lower_bound, upper_bound);

  auto gen = std::bind(dist, mersenne_engine);
  std::vector<int> vec(n);
  std::generate(begin(vec), end(vec), gen);

  return vec;
}

int main()
{
  std::vector<int> numbers = GenerateVectorOfRandomNumbers(5, 1, 10);

  std::cout << "Input : [ ";
  for (const auto &elem : numbers)
  {
    std::cout << elem << ", ";
  }
  std::cout << "]" << std::endl;

  int product = 1;
  for (const auto &elem : numbers)
  {
    product *= elem;
  }
  std::cout << "Product of Inputs: " << product << std::endl;

  std::cout << "Output : [ ";
  std::vector<int> ret = numbers;
  for (auto &elem : ret)
  {
    elem = product / elem;
    std::cout << elem << ", ";
  }
  std::cout << "]" << std::endl;

  return 0;
}