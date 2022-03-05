#include "solution.h"
#include "util.h"
#include <queue>
#include <map>
#include <algorithm>
#include <string>
#include <queue>
#include <sstream>
#include <functional>
#include <math.h>

using namespace sol1066;
using namespace std;

/*takeaways
  - assign the bikes (via a state sequence) top-down starting from w0 to wN.
  - calculate the min distance bottom-up from wN back to w0.
  - use example 2
    - w0 <- b0, the sequence passed down is 1
      - w1 <- b1, the sequence passed down is 11 (3)
        - w2 <- b2 as this the only choice,
          the sequence is now 011 (3), so memo[3] = 1.
        - the sequence 011 denotes that b2 is the very
          last bike to assign to the very last worker.
        - this is the tricky part as you might be
          tempted to think why not assign the distance
          1 to 111(7) like memo[7] = 1? well, everything
          will end up as 111 once all the bikes are
          assigned. So doing that won't work.

      - w1 <- b2, the sequence passwd down is 101 (5)
        - w2 <- b1 memo[5] = 2

      - now back to w1, we have two choices to set
        the value for sequence 1, which denotes the
        first bike has been assigned and is not
        available for me to choose.
        option 1: pick bike 1 : 2 + memo[3] = 3
        option 2: pick bike 1 : 2 + memo[5] = 4
        - so for sequence 1, we set memo[1] = 3 (min)

    - now back to w0
      - we evaluated one option w0 <- b0, and the
        distance is 1 + memo[1] = 4
      - we still need to evaluate other options
        to find the min among the options
        - w0 <- b1
        - w0 <- b2
*/

int Solution::assign(vector<vector<int>> &ws, vector<vector<int>> &bs)
{
  auto dist = [&](int i, int j)
  {
    return abs(ws[i][0] - bs[j][0]) + abs(ws[i][1] - bs[j][1]);
  };
  const int wSize = ws.size();
  const int bSize = bs.size();

  /*state mask
     - the key is a sequence that represents
       a state of how bikes have been assigned
     - the value is the min distance of all the
       different distances cover by that sequence
  */
  auto memo = vector<int>(1 << bSize, 0);

  function<int(int, int)> visit = [&](int state, int w)
  {
    if (w == wSize)
      return 0;
    if (memo[state] != 0)
      return memo[state];
    auto result = INT_MAX;
    for (auto b = 0; b < bSize; b++)
      if ((state & (1 << b)) == 0)
        /*for w0, you are passing down 1, 10 (2) , or 100 (4) */
        result = min(result, dist(w, b) + visit(state | 1 << b, w + 1));
    memo[state] = result;
    return memo[state];
  };

  return visit(0, 0);
}