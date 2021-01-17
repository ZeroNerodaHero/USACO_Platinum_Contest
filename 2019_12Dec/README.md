# Summary of Solutions:

## 1. Greedy Pie Eaters

This is typically one interval DP, transition from small interval [i,j] to biggest interval [1,N], which is also the answer.  The trick for this DP is who eats the last one piece of pie k.  Here is the state transition:

    dp[i][j] = max(dp[i][k-1] + dp[k+1][j] + z[k][i][j]) for all k between [i,j]

Where z[k][i][j] is the cow who can eat k, and has the maximum weight over interval [i,j].

- The [pieaters.cpp](/2019_12Dec/pieaters.cpp) computes z while doing DP transition. It should be fastest as its time complexity is O(N<sup>2</sup>).  I include the execution time in the code.
- The [pieaters0.cpp](/2019_12Dec/pieaters0.cpp) is similar to the [pieaters.cpp](/2019_12Dec/pieaters.cpp). It starts transition from the intervals from left side. 
- The [pieaters1.cpp](/2019_12Dec/pieaters1.cpp) pre-computes z first.  Then it does DP state transition.  It is slower than [pieaters.cpp](/2019_12Dec/pieaters.cpp) as its time complexity is O(N<sup>3</sup>).
- The [pieaters_dp_bitmask.cpp](/2019_12Dec/pieaters_dp_bitmask.cpp) is one bitmask DP.  It could pass some cases, but not all the cases.  Thus I do not use bitset or other bit data structure. It can also be bottom-up, like the one in hamiltonian path given by Bellman, Held, and Karp.
- The [pieaters_perm.cpp](/2019_12Dec/pieaters_perm.cpp) and [pieaters_perm1.cpp](/2019_12Dec/pieaters_perm1.cpp) is brute-force solution.  It uses the permuation.  It could pass only the basic test case.

## 2. Bessie's Snow Cow

A ***special node*** is defined as a node with c, but its ancestor is not colored c.  All descendants are also colored c.  So for each query, the answer is:
    (tree size) * (# of special ancestor nodes including me) + (# other colors in my subtree )

It involves in three tasks:
1. compute the number of special ancestor nodes
2. compute the number of other colors not in ancestor
3. maintain the list of special nodes: If any descendant has the same color, remove it from the list.  If any ancestor has the color, do nothing.

For task 1 and 2, segment tree or BIT tree can be used.  For simplicity, Fenwick trees are used.
For task 3, red-black tree is used for fast search.

The segment tree is more powerful than Fenwick tree.  If we use the segment tree, the time complxity remains the same. But in case that segment tree be used, we could only store the #colors in my subtree instead of special nodes in ancestor.  So the sub-tasks becomes two:
1. Store the number of colors in my subtree: range update
2. maintain the list of special nodes as in previous algorithm

For range update, lazy propogation must be used.  Even though time complexity remains the same, but it should need more time.  I will do it later.

## 3. Tree Depth

Here is the generating function of reverse order

