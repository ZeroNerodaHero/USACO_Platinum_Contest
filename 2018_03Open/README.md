# Summary of Solutions:

## 1. Out of Sorts

This looks like block/bucket sort.  After each round of bubble sort, we have to sort each block or bucket.  This effectively adds block size (>1) to the answer.  Or we can say that every element in the subarray contributes 1 to the answer in each pass of bubble sort until it is partitioned from its neighbors on both sides.  If we have N-1 **partition point**.  The whole array is sorted.

So our algorithm is to find the number of passes of each element until it is partitioned from its neighbors on both sides.  For first or last element, we just assume that it is already partitioned from left side or right side respectively.  After the array is sorted,  the count for each element is the maximum of the counts of its neighboring partition points.  So we just calculate the number of bubblesort passes for each of the N-1 (+2 pseudo)  partition points, after which the array is partitioned by these partition points.

First we need to represent the partion point between i and i+1, which we define it as t[i] in [sort.cpp](sort.cpp).

    c[i]: the initial index of element i (a[i]) in sorted order
    t[i]: the number of passes at partition point between [i, i+1].

Now we consider the position **i** in sorted order.  Let mx be the initially maximum index of any of the smallest i elements. Then the number of bubblesort passes required before the array is partitioned between i and i+1 is exactly mx−i. In each pass, the maximum index will decrease by exactly 1 as index i increases by one.  For each element, we count the maximum number of passes from the partition points on both sides.  

There is a special case.  Even though it is sorted array, every element must be checked once, which mean the minimum contribution of every point is 1 except that N is 1.  So for those elements with 0 pass to make it sorted, it actually adds one to the answer. Here is one example:

    a[i] : 5 6 7 8 ==> sorted array
    c[i] : 1 2 3 4
    t[i] : 0 0 0 0 ==> there are already N-1 partition point
    answer: 1+1+1+1 = 4

## 2. Train Tracking

This is a sliding window mimimum problem, which can be solved by using double-ended monotonic queue.  But the total global memory can be used is only 5500 integers.  We use square root decomposition to improve the space complexity in [train.cpp](train.cpp).  We also use monotonic queue data structure to improve the time complexity.

The [trainglobal.cpp](trainglobal.cpp) uses global variables.  It can pass all the test cases, but no credit can be claimed.

## 3. Disruption

This is a tree edge cutting problem.  Only one tree edge is cut, find an replacement edge to re-connect the two trees if possible.  This reminds of some MST algorithms like Prim, Krusal or even Boruvka’s algorithm.

For every tree vertex, we maintain a set of replacement edges.  We can start from disconnecting the leaf edge by traversing the tree.  When one tree edge is cut, there would be two connected components.  We find one replacement edge with minimum weight if possible, which is the answer.  After that we re-connect and merge the replacement edges of child vertex with parent's.  If we find the replacement edge between two vertex within this subtree, remove it from the set.  It looks like the subtree becomes one marco-vertex. The internally connected edge within this macro-vertex is removed.

For replacement edge merge, we merge small set to big set in [disrupt.cpp](disrupt.cpp).  The time complexity is O(Nlog(M)).

The problem can also be solved by LCA + sgement tree.  The time complexity remains the same or a bit worse as current complexity is actually O(Nα(M)) where α() is the inverse Ackermann function.
