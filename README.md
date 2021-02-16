# USACO_Platinum_Contest
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

Now we add the number n to the permuation of n-1 objects.  There are n position which we can insert the nth object.  If it is appended at the end, it adds 0 more inversion.  WLOG assumes that there are n-1-i more inversions if nth object is added at position i.  Thus we get the DP transition formula as follows:

    dp[n][k] = sigma(dp[n-1][k-i]) for i=[0, min(n-1, k)]

The k could be very big, but it is not over n(n-1)/2.  If k is big than this number, dp[n][k] = 0.  So we can have the following values for DP table.

    dp[0][0] = 1, but dp[0][1]=0
    dp[1][0] = 1, but dp[1][1]=0
    dp[2][0] = 1, dp[2][1] =1, but dp[2][2] = 0.

For K inversions, we only care about (K-i) number of inversion at dp[n-1] level, which is a part of prefix sum.  So the time complexity is still O(NK) or O(N<sup>3</sup>).

### 4. Vague Definition

Sometimes we have to convert vague defintion to clear defintion.

For example, in [Sprinklers 2](2020_03Open/sprinklers.cpp), the transition line is above the read block or on the left side of blue block. It is not exactly at one point (i, j).  Another example is [Out of Sorts](2018_03Open/sort.cpp).  The partition point is between i and i+1, not at i or i+1. For these cases, the clear definition must be provided to complete the computation.


