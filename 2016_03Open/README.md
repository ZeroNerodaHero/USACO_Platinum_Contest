# Summary of Solutions:

## 1. 262144

This is interval DP.  It reminds me of the problem "Minimum Cost to Merge Stones", which can be solved in O(N<sup>2</sup>).  As **COST** is in the range [1,40], we can do DP optimization.  Assuming that the array contains 262144 (1<<18) number of 40, the final merged value is 58, which is maximum of all solutions.  It forms a complete binary merge tree in this case.

Now we generalize the formula.  Assume two consecutive intervals `[a, b)` and `[b, c)` have already been merged into value i.  Or we can say:

        merged_value[a, b) = i
        merged_value[b, c) = i

Then we can merge these two consecutive intervals into one interval `[a, c)`.  The new value is i+1 : `merged_value[a, c) = i+1`.  Now we can define state dp[i][j] as follows:

        dp[i][j] : the right index of the interval [j, dp[i][j]).  The merged value in this interval is i.

So the state `merged_value[a, b) = i` is `dp[i][a] = b`.

For initialization, any element a[i] can be treated as merged value in `[i, i+1)`.  So the initial state is `dp[a[i]][i] = i+1`.

The DP transition is as follows:

        dp[i][j] = dp[i-1][dp[i-1][j]] if dp[i][j] == 0;

In order to avoid boundary check, 0 is reserved for invalid range in [262144.cpp](262144.cpp).

#### Other Solution:

- As only 2<sup>n</sup> consecutive equal values can be merged, there is O(N) greedy algorithm, which checks if the small values can be merged to left or right value.


## 2. Bull in a China Shop

The problem involves two sub-tasks:
- Choose one subset of three from K pieces. The time complexity is C(K, 3) or O(K<sup>3</sup>).
- Check if the subset could be glued back together to mend his broken figurine.  Considering flipping and rotation, the time complexity is O(8N<sup>2</sup>)<sup>3</sup>.

The total time complexity is O(K<sup>3</sup> * N<sup>2</sup>).  We can decrease the number of subset in the first sub-task.  Here I outline different ways:
- We count number of figurine in the original glass cow and K pieces.  If the set could be glued back together to mend his broken figurine, it satisfies : c=c1+c2+c3
we can 

Similar to Rabin–Karp Algorithm, we can try to find which sub-set of 3 tuples could possibly be glued back together to mend his broken figurine based on hash, for example, hash based on the count of different low-case characters.  But it still has TLE issue as second sub-task takes very long times.


## 3. Landscaping

For this problem, X,Y are constant.  The only variable is |i-j|Z. And it is related to shortest distance |i-j|.  If we have to remove dirt at location i, we always find the closed location j which we should add dirt, and vice versa.  Thus we get the **Optimal Substructure Property** for greedy algorithm:

    If |i-j|*Z<(X+Y) do the move, otherwise we purchase or ship away the dirt.

We can greedily check if we can make current location i have B<sub>i</sub> unit of dirt.  I change **Optimal Substructure Property** to be accumulated cost (X or Y + the new cost in i) instead of fix cost (X+Y).  I use two priority queues to store the cost of each unit and the amount of dirt.  [My algorithm](landscape.cpp) is as follows: 

- First check if we need to add/remove dirt by (B<sub>i</sub>-A<sub>i</sub>).  If not, continue.
- In case that the dirt be removed, we check if we could move it to some early location with cost reduction.  If not, just ship away the dirt. In addition, push the index into the un-needed stack.
- In case that the dirt be added, we check if we could take the dirt from some early location with cost reduction.  If not, just purchase the dirt. In addition, push the index into the needed stack.

Both time complexity and space complexity are O(N * α(N)) in [landscape.cpp](landscape.cpp).  It takes less time than USACO official solution.  If we can design one priority queue with pop_back() operation, [landscape.cpp](landscape.cpp) could run a bit faster.

The [online greedy algorithm](landscape.cpp) does not depends on K, the maximum value of (B<sub>i</sub> or A<sub>i</sub>).  In the problem, K is 10 maximumly. We can also have other solutions.

#### DP solution

- edit distance (TLE) : convert landscape height to sequence with length NK.  The time complexity is O((NK)<sup>2</sup>).
- USACO official solution.

#### maximum flow and minimum cost solution

This definitely has TLE issue as there could be O(N<sup>2</sup>) edges. There are several ways to build flow network with cost in the form of (capacity, cost).

Here is one way to build flow network.  First split any location i into two vertices (i, I).  Then construct one flow network as follows
- From s to location i has the (A<sub>i</sub>, 0)
- From location i to t has the (INF, X)
- From s to location I has the (INF, Y)
- From location I to t has the (B<sub>i</sub>, 0)
- From location i to all J has (INF, |i-j|Z)

We can also build a flow network without splitting vertices.  The directed edge is based on capacity=(B<sub>i</sub>-A<sub>i</sub>) in [landscape.cpp](landscape.cpp).  The vertex with capacity 0 can be filtered out out flow network.

Can we build one weighted bipartite graph by using Hungarian Algorithm?
- Set U of vertices need to purchase dirt
- Set V of vertices need to ship away dirt

