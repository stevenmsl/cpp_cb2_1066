#include <iostream>
#include <tuple>
#include <vector>
#include <string>
#include "solution.h"
#include "util.h"

using namespace std;
using namespace sol1066;

/*
Input: workers = [[0,0],[2,1]], bikes = [[1,2],[3,3]]
Output: 6
Explanation:
We assign bike 0 to worker 0, bike 1 to worker 1.
The Manhattan distance of both assignments is 3, so the output is 6.
*/
tuple<vector<vector<int>>, vector<vector<int>>, int>
testFixture1()
{
  auto ws = vector<vector<int>>{{0, 0}, {2, 1}};
  auto bs = vector<vector<int>>{{1, 2}, {3, 3}};

  return make_tuple(ws, bs, 6);
}

/*
Input: workers = [[0,0],[1,1],[2,0]], bikes = [[1,0],[2,2],[2,1]]
Output: 4
Explanation:
We first assign bike 0 to worker 0, then assign bike 1 to worker 1 or worker 2,
bike 2 to worker 2 or worker 1. Both assignments lead to sum of the Manhattan distances as 4.
*/
tuple<vector<vector<int>>, vector<vector<int>>, int>
testFixture2()
{
  auto ws = vector<vector<int>>{{0, 0}, {1, 1}, {2, 0}};
  auto bs = vector<vector<int>>{{1, 0}, {2, 2}, {2, 1}};

  return make_tuple(ws, bs, 4);
}
void test1()
{
  auto f = testFixture1();
  cout << "Test 1 - exepct to see " << to_string(get<2>(f)) << endl;
  auto result = Solution::assign(get<0>(f), get<1>(f));
  cout << "result: " << to_string(result) << endl;
}

void test2()
{
  auto f = testFixture2();
  cout << "Test 2 - exepct to see " << to_string(get<2>(f)) << endl;
  auto result = Solution::assign(get<0>(f), get<1>(f));
  cout << "result: " << to_string(result) << endl;
}

main()
{
  test1();
  test2();
  return 0;
}