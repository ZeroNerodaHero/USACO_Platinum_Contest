# Summary of Solutions:

## 1. Sum of Distances

During contest, I defined one rule to traverse the graph G[i]: every vertex in G[i] can only go forward (depth adds one), but not backward.  If there is no vertex in any G[i] to traverse, the traversal in G is done.  The counting of the vertex in G is based on different rule: As long as at least one vertex in G[i] goes forward, the vertex in G are different.  It means we need to exclude all vertices in G[i] going backward.  If it is tree, definitely it works.  But multiple cycles causes the issue.

In order to fix this issue, we have to add additional rule for counting in G.  Here I use visited data structure to record all the vector vertices in G which has been traversed before.  For every traversal, the duplicate or visited vector vertices in G is excluded.  But the visted vector vertices in previous traversal should not be excluded.

For every graph G[i], the depth of every vertex is approximately log[N[i]].  So the time complexity is sigma(N[i]*log[N[i]]*log[N[i]]).  

In [1sum.cpp](1sum.cpp), set is used for duplicate removal and counting.  Actually I can use array, not set for this purpose.  Thus the The time complexity reduced to sigma(N[i]*log[N[i]]).

## 2. Minimum Cost Paths

The DP optimization is done by using the piecewise interval to narrow down the search.

During contest, I used one set in y-direction, which segments [1-M] into different small intervals [y0,y1).  But updating (finding) y0/y1 takes O(M) time even though I used binary search.  If I change the interval in x-direction as [x0, x1], the update takes O(log(N)) time.

The [2cost.cpp](2cost.cpp) use the set of x-direction piecewise intervals.  The x co-ordinate alway increases in this set, otherwise it will be removed from the set.  The red-black tree is not needed.  Instead an array is used to maintain the set.

The set of x-direction piecewise interval forms a convex hull even though it is not intended.  The similar problem is [Falling Portal](../2020_01Jan/falling.cpp), which is based on the least postive time of the intersetion of two lines.

## 3. Paint by Letters

Initially I thought of segment tree to store the result.  Starting from 1X1 small box, grow it or union it with the small box through boundary of every smaller rectangle.  But union is very complicated.  It is challenging to get full credit.  Instead I used the simpler method.

I used one two dimensional prefix sum and four one dimensional prefix sum. For small box like 10X10, I just used union-find to get the answer.  For big box, I checked every head of connected components on four sides to make sure that it is the head, and planed to do the adjustment based on DFS.  DFS only needs to search the connected colors inside box (not outside the box).  For test case 6-11, the maximum depth is 3 as every connected component consisting of cells with the same desired color can be contained within a 3X3 square with sides parallel to the coordinate axes.  Thus the time complexity for every query is O(N) time.  But for test case 12-20, it may have TLE issue.


