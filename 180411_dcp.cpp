/*
Given a list of numbers, return whether any two sums to k.

For example, given [10, 15, 3, 7] and k of 17, return true since 10 + 7 is 17.

Bonus: Can you do this in one pass?
*/

#include <vector>
#include <random>
#include <iostream>
#include <functional>
#include <algorithm>

class Increment
{
public:
  Increment(int a) : current(a) {}
  int operator()()
  {
    return current++;
  }

private:
  int current;
};

// Returns a vector of unique numbers between a(inclusive) and b(exclusive)
std::vector<int> GenerateVectorOfUniqueNumbers(int a, int b)
{
  std::vector<int> vec(b - a);
  Increment inc(a);
  std::generate(vec.begin(), vec.end(),inc);
  std::random_shuffle(vec.begin(), vec.end());

  return vec;
}

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

int GetPossibleSum(const std::vector<int> &vec)
{
  // A bit much
  std::vector<int> random_unique_indices = GenerateVectorOfUniqueNumbers(0, vec.size());

  int possible_sum = vec[random_unique_indices[0]] + vec[random_unique_indices[1]];

  return possible_sum;
}

void PossibleSumsHelper(const std::vector<int> &vec, const std::vector<int> &partial, int target_sum, int minimum_set_size, int maximum_set_size)
{
  int sum = 0;
  for (auto elem : partial)
  {
    sum += elem;
  }
  if (sum == target_sum && partial.size() >= minimum_set_size)
  {
    std::cout << "[ ";
    for (auto elem : partial)
    {
      std::cout << elem << ", ";
    }
    std::cout << "]" << std::endl;
  }
  if (sum >= target_sum)
  {
    return;
  }

  for (std::vector<int>::const_iterator i = vec.cbegin(); i != vec.cend(); i++)
  {
    int current = *i;
    std::vector<int> remaining;
    for (std::vector<int>::const_iterator j = i; j != vec.cend(); j++)
    {
      if (i == j) continue;
      remaining.push_back(*j);
    }

    std::vector<int> updated_partial = partial;
    updated_partial.push_back(current);
    if (updated_partial.size() > maximum_set_size) return;
    PossibleSumsHelper(remaining, updated_partial, target_sum, minimum_set_size, maximum_set_size);
  }
}

void PossibleSums(const std::vector<int> &vec, int target_sum, size_t minimum_set_size, size_t maximum_set_size)
{
  PossibleSumsHelper(vec, std::vector<int>(), target_sum, minimum_set_size, maximum_set_size);
}

int main()
{
  std::vector<int> v = GenerateVectorOfRandomNumbers(10, 1, 10);
  int k = GetPossibleSum(v);

  std::cout << "k: " << k << std::endl;

  for (auto i : v) std::cout << i << " ";
  std::cout << std::endl;

  PossibleSums(v, k, 2, 2);

  return 0;
}