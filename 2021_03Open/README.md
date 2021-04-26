# Summary of Solutions:

## 1. United

Here is [my algorithm](1united.cpp) during contest:

    1. Find the range of every unique number, based on father's location, in the similar way as union-find.
    2. Iterate from index 1, execute the following using the segment tree:
    3. find the range [l,r] or [f[i], i].
    4. Suppose I am the rightmost leader, query the number of leftmost-middle pair. Add to the solution.
    5. Suppose I am the middle leader, add 1 to all the unique number in the range [f[i], i] as they are the left-most leader
    6. Subtract the number of left-most leader at f[i], and add -1 to all the unique number in the range [f[f[i]], f[i]]
    7. Goto step 3

The time complexity is O(N<sup>2</sup>) due to range update.  For range update, lazy propagation must be used to reduce the time complexity to O(NlogN).


## 2. Route

It should be DP similar to USACO 5.4.1 Canada Tour.  Except for sender (source) and receiver(sink) vertices, the in-degree must be equal to out-degree for every vertex.  If we add one to the in-degree for all source vertices and one to the out-degree for all sink vertices, then in-degree equals to the out-degree for all vertices.  It is easy to count the number of routing schemes if there is no backward edges. Here are the three different cases:

- If K=0, this is a DAG.  The answer is the product of permutation of in or out degree of every vertex.
- If K=1, the backward edge could create one loop, we need to exclude all these loops.
- If K=2, we need to include all single loop created by two backward edges separately. If two loops are created simultaneousely, they must be excluded to avoid over counting.

In [my algrithm 2route.cpp](2route.cpp), the input data is assumed valid.  If data is not valid, the solution would be wrong.  And we can use either in-degree or out-degree in the computation as they are equal for all vertices.

## 3. Grass

[My algorithm 3grass.cpp](3grass.cpp) counts the different ways to renion the different blocks in the next layer when doing flood fill. The VALID blocks are like a convex hull.  In [3grass.cpp](3grass.cpp), hash table is used for dynamic programming.  The time complexity is O(N<sup>5</sup>).


The prefix sum is used for optimization.  Thus the time complexity is reduced to O(N<sup>3</sup>);

