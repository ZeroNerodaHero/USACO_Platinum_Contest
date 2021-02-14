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

For permutation with inversion K, we can get the number of permutation by using the generating function. Here we define the generating function as follows.  The g(0,n) is the generating function of permuation with n objects.

    g(s, n) = product (sigma(x<sup>i</sup>) for i=0, k-1) for k=s, n

We can also use Dynamic Programming (DP) to get the number of permutation.  The DP state is defined as the number of permuation with k inversion for the first n objects.

    dp[n][k] = sigma(dp[n-1][k-i]) for i=[0, min(n-1, k)]

We introduce dp1[n][k], which represents the number of permuation with k inversion for last n objects in total N objects.

As the problem asks for permutation with inversion K, we only need to compute the number of permutation with inversion from max(0,K-N) to K.  And one hidden prefix sum is used to speed up the counting.

Now we consider the depth.  We still use the generating function.  The necessary and sufficient condition is that j is an ancestor of i if a[j]=min(a[i…j]). Just like DP, we add the object from small to big.  For a[i], adding a[j] contributes j−i inversions regardless of how many inversions a[i…j−1] has.

    G(n) = g(0, i) * g(i+1, n)

This looks like a backpack of prefix and suffix.  Here we define the state for g(0,i) and g(i+1,n) as follows:

    dp[n][k] : first n objects with k inversion
    dp1[n][k] : last n objects with k inversion

As we only care permutation with K inversion, the convolution of i items only needs to do selected items like this:

    a[i] = sum(dp[i-1][j]*dp1[i+1][K-j])          only compute K items
    b[i] = sum(dp[i-1][j]*dp1[i+1][K-(i-1)-j])    only compute K-(i-1) items

After that, we can use prefix sum to speed up the computation of answer.  

    *Note: The index is in the range of[1,N] so that we can ignore any check of i=>0 or i<=N.*


