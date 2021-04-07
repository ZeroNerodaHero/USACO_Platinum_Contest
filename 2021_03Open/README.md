# Summary of Solutions:

## 1. United

Here is the algorithm:

    1. Find the range of every unique number, based on father's location, in the similar way as union-find.
    2. Iterate from index 1, execute the following using the segment tree: 
    3. find the range [l,r] or [f[i], i].
    4. Suppose I am the rightmost leader, query the number of leftmost-middle pair. Add to the solution.
    5. Suppose I am the middle leader, add 1 to all the unique number in the range [f[i], i] as they are the left-most leader
    6. Subtract the number of left-most leader at f[i], and add -1 to all the unique number in the range [f[f[i]], f[i]]
    7. Goto step 3

I did not use lazy propagation in the contest to do optimization.


## 2. Route

It should be DP similar to USACO 5.4.1 Canada Tour.  The graph is like a dag, but two backward edge is hard to deal.  I use "team vertex" to do the brute force traversal. It has TLE issue.

## 3. Grass

It counts the different ways to renion the different blocks in the next layer when doing flood fill. The new block is like a convex hull. 

