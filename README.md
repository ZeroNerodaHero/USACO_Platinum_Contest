# USACO_Platinum_Contest

The main point of this repo is to track my learning process during USACO 2020-2021 season.  All the solutions have been verified at USACO contest website.  I learn for fun, for [a change, a change in problem, a change in solution, a change which leads to the discovery of new algorithm](/README.md#7-innovation-of-the-new-algorithm).
## Solutions to USACO Platinum problems.

### 1. New Concept Introduced

At Platinum level, I have to define new concepts sometimes. In Circus (USACO 2020 Open) problem, new definitions are given for virtual connected component and chain in order to describe my algorithm. The connected component (CC) is somewhat similar to but also different from connected component in graph.  It defines one domain where two cows could swap their positions.  The chain is like one weighted edge in tree or graph, which connects but also segments CCs. Similar to Boruvka’s algorithm, the algorithm is to merge CCs by removing or hiding chains when there are enough unoccupied vertices.  Here is the detailed description.

- [2020_03Open/Circus](/2020_03Open/README.md#3-circus)

Solutions to other two problems:

- [2020_03Open/Exercise](/2020_03Open/README.md#2-exercise)
- [2020_03Open/Sprinklers 2: Return of the Alfalfa](/2020_03Open/README.md#1-sprinklers-2-return-of-the-alfalfa)

### 2. Modification of Existing Algorithms

The [Sum of Distances](http://usaco.org/index.php?page=viewproblem2&cpid=1092) is a very interesting question.  During the contest, I realized that it is actually Dijkstra shortest path (SPF) problem.  But the vertex is a K-dimensional vector.  Every field in a vector vertex has its own rule to change in graph G[i].  There will be a lot of vertices in the connected graph starting from (0,0, ...0).  The key point is to find which vector vertex in G is visited.

The [1sumbfs.cpp](2021_01Jan/1sumbfs.cpp) is doing Dijkstra BFS traversal from this starting vertex.  The hash table is used to check which vector vertex is visited.

As the problem asks for the sum of all shortest distance, I defined one rule to visit all the vector vertices: never go back.  The detail of [1sum.cpp](2021_01Jan/1sum.cpp) can be found [here](2021_01Jan/README.md#1-sum-of-distances).

### 3. Dynamic Programming vs. Generating Function

The generating function is helpful to find the DP transition formula, or make DP unnecessary.  But not any DP transition can be deducted from generating function. For [Tree Depth, USACO 2019 December Contest, Platinum](http://www.usaco.org/index.php?page=viewproblem2&cpid=974), the solution is usually based on generating function of permutation statistics.  Here I provide one DP solution.

First the DP state is defined as follows:

    dp[n][k]: the total number of k inversions for all permutation with n objects.

Now we add the number n to the permutation of n-1 objects.  There are n position which we can insert the nth object.  If it is appended at the end, it adds 0 more inversion.  WLOG assumes that there are n-1-i more inversions if nth object is added at position i.  Thus we get the DP transition formula as follows:

    dp[n][k] = sigma(dp[n-1][k-i]) for i=[0, min(n-1, k)]

The k could be very big, but it is not over n(n-1)/2.  If k is big than this number, dp[n][k] = 0.  So we can have the following values for DP table.

    dp[0][0] = 1, but dp[0][1]=0
    dp[1][0] = 1, but dp[1][1]=0
    dp[2][0] = 1, dp[2][1] =1, but dp[2][2] = 0.

For K inversions, we only care about (K-i) number of inversion at dp[n-1] level, which is a part of prefix sum.  So the time complexity is still O(NK) or O(N<sup>3</sup>).

### 4. Vague Definition

Sometimes we have to convert vague definition to clear definition.

For example, in [Sprinklers 2](2020_03Open/sprinklers.cpp), the transition line is above the read block or on the left side of blue block. It is not exactly at one point (i, j).  Another example is [Out of Sorts](2018_03Open/sort.cpp).  The partition point is between i and i+1, not at i or i+1. For these cases, the clear definition must be provided to complete the computation.


### 5. Plug Dynamic Programming

I used PLUG DP to solve [van (USACO 6.1)](https://github.com/ZeroNerodaHero/USACO-Training-Gateway/blob/master/6.1/van.cpp) and [betsy (USACO 6.5)](https://github.com/ZeroNerodaHero/USACO-Training-Gateway/blob/master/6.5/betsy.cpp).  Here I modify the plug properties to solve the ["Compound Escape" problem](2019_03Open#2-compound-escape) again.

The [code](2019_03Open/escapeplug.cpp) is pretty much similar to other two problems.  The plug DP is used to solve the row-based, such as grid, problems when the size of one row is relatively small.  It greatly improves the performance of the Bellman-Held-Karp Algorithm for these special cases.  As the state space is small but scattered, we should have a way to store the state.  I used hash table in these cases.


### 6. DP Optimization

Here are some DP optimization techniques used for some USACO problems.

##### Monotonic queue/stack

Similar to the problem "Maximum value in sliding window", priority queue can be used to improve efficiency.  But montonic queue is more efficient.
- [Photo in 2013 Open]() : convert O(N<sup>2</sup>) to O(N) by using monotonic queue.
- [Trapped in the Haybales](/2015_03Open#3-trapped-in-the-haybales-gold) : We can not use monotonic queue as the monotonicity is subject to change.  Instead we use priority queue in solution.  Maybe red-black tree is better than priority queue.

##### Convex Hull Trick

    dp[j] = min(dp[k] + b[k] * a[j]) for k < j
    dp[i][j] = min(dp[i-1][k] + b[k] * a[j]} for k < j

USACO problems:
- [Falling Portals 202001]()
- [Minimum Cost Paths 202101](): [Find the set of best points](/2021_01Jan#2-minimum-cost-paths)

##### Divide and Conquer DP

    dp[i][j] = min(dp[i-1][k] + C[k][j]) for k < j

##### Knuth's optimization

    dp[i][j] = min(dp[i][k] + dp[k][j]) + C[i][j] for i < k < j

##### Quadrangle inequalities: C([a][c]+C[b][d]<=C[a][d]+C[b][c] for a<=b<=c<=d.
##### xD/yD dynamic programming


### 7. Innovation of the new algorithm

The USACO problems is very intriguing.  They lead me to think deeper and deeper into the possible change in problems and solutions:

- [No Time to Dry](/2021_02Feb/CHANGE.md#1-no-time-to-dry): If we change Q to be 2\*10<sup>6</sup>, my [online algorithm](/2021_02Feb/1dry.cpp) should still pass all the test cases.
- [Landscaping](/2016_03Open/README.md#3-landscaping): My [online solution](/2016_03Open/landscape.cpp) does not depends on the maximum value of (B<sub>i</sub> or A<sub>i</sub>), which is 10 in problem.
- [Minimizing Edges](/2021_02Feb/CHANGE.md#2-minimizing-edges): We could possibly have different changes in solutions and problem.

