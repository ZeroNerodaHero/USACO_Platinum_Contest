# Notes of Solutions:

## 1. Delegation

It is hard to find K, but it is easy to verify if the tree can be partitioned into the set of roads with minimum length K.  Then we can do binary search to find the maximum K, which is the answer.

For any non-root tree node, we must return one road if node has odd number of children.  Otherwise we could return 0 or one road if possible.  It means we must pair two roads so that it has minimum length K.  Otherwise return -1.  In case that we should be able to pair, we would like to return the longest road.  For root tree node, all edges can be paired.  But the road length must be at least K. Otherwise return -1.

In  [deleg.cpp](/2020_02Feb/deleg.cpp), I use STL vector to store the length of child edge.  Inserting a number to anywhere other than the end could affect the performance.  So I only use push_back() and pop_back() for vector operation.  In addition, I use pre-allocated vectors.  Thus memory allocation is not needed for vector.

## 2. Equilateral Triangles

In order to form a triangle with equal Manhattan distance, all the third points are in one 45-degree line for one horizontal or vertical side.  We first change **Manhattan distance** to **Chebyshev Distance**.  For one side (even number) on a squrare, the third point must lie in the opposite side of the sqaures. Then it is easy to count the number of triangles.  The counting can be done in two direction, but avoid over counting of the points in four corners of the square.  Use prefix sum to speed up the search, which can reduce the time complexity to O(N<sup>3</sup>).
 
As a lot of points have no cow in transitioned graph, we can do optimization by narrowing down the search range.  The [triangles.cpp](/2020_02Feb/triangles.cpp) is an improvement of [triangles1.cpp](/2020_02Feb/triangles1.cpp).

## 3. Help Yourself

This is DP problem.  The state dp[i] records the information of the subset which has the rightmost postion i.  The jth information dp[j][i] is **the sum of (c<sup>j</sup>) **where c is the complexity.  When complexity increases by one, the polynomial expansion formula can be used to update DP table.

First sort segments by left coordinate, and try placing the segment [l,r] into a subset in this order. So we only consider the relationship between the newly added segmenti [l,r] and the last segment, ending at i, in this subset.  We check the following three cases in order:
1. l > i, the complexity of new subset increses by 1, the rightmost point of the subset becomes r.
2. r > i, the complexity is not changed, but rightmost point of new subset is r.
3. the comlexity and rightmost point of this newly created subset is the same as old subset.

If we use array for DP state, the time complexity will be (N<sup>2</sup>K).  As segment tree can support range query, single point update, and range update with lazy propagation, we store the DP state into segment tree.  As there are only N (not 2N) rightmost point, the segment tree range is [0,N].

For polynomial expansion, we can do it on the fly instead of using pre-computed combination table.  Thus no mulitiplication is needed.
