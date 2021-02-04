# Summary of Solutions:

## 1. Sum of Distances

During contest, I defined one rule to traverse the graph G[i]: **every vertex in G[i] can only go forward (depth adds one), but not backward.  If there is no vertex in any G[i] to traverse, the traversal in G is done.**  The counting of the vertex in G is based on different rule: **As long as at least one vertex in G[i] goes forward, the vertex in G are different**.  It means we need to exclude all vertices in G[i] going backward.  If it is tree, definitely it works.  But multiple mixed cycles with even and odd steps causes the issue.

In order to fix this issue, we have to add additional rule for counting in G.  Here I use visited data structure to record all the vector vertices in G which has been traversed before.  For every traversal, the duplicate or visited vector vertices in G is excluded in previous step (step i-1).  But the visted vector vertices in previous traversal (before step i-1) should not be excluded. It can be done based on inclusion/exclusion principle:

    Intersection(A, B) = A + B - Union(A, B)

For every graph G[i], the depth of every vertex is approximately log[N[i]].  So the time complexity is sigma(N[i]*log[N[i]]*log[N[i]]).  

In [1sum.cpp](1sum.cpp), set or BST is used for duplicate removal and counting.  Actually I can use array, not set for this purpose.  Thus the The time complexity reduced to sigma(N[i]*log[N[i]]).

## 2. Minimum Cost Paths

The DP optimization is done by using the piecewise interval to narrow down the search.  The intervals are created by a set of **"best points"**.  We use the same way to store the best point during contest as (x,y,v) where v is the minimum cost to (x,y) from point (0,0). So the minimum cost of point x after best point f is deducted from the formula as follows:

    minimum-cost-path(x) = f.v + x*x*(y-f.y) + c[f.y]*(x-f.x)

Every query takes O(1) time to get the answer, but finding its best point in the set may take log(set size) time.

During contest, I used one set of **best points** in y-direction, which segments [1-M] into different small intervals [y0,y1).  But updating (finding) y0/y1 takes O(M) time even though I used binary search.  If I change **the set of best points** in x-direction as [x0, x1], the update takes less than O(log(N)) time.

The [2cost.cpp](2cost.cpp) uses the set of best points in x-direction, which creates piecewise intervals in x-direction.  The x co-ordinate alway increases in this set, otherwise it will be removed from the set.  The red-black tree is not needed.  Instead an array is used to maintain the set.

The set of best points in x-direction forms a convex hull even though it is not intended.  The similar problem is [Falling Portal](../2020_01Jan/falling.cpp), which is based on the least postive time of the intersetion of two lines.

There are still more room for optimization:

- The sorting is actually not needed.  I used quick sort during contest.  [Here](2cost.cpp) I use counting/bucket sort. So the time complexity is reduced to O(M) from O(MlogM).
- The square root can be used to assist removal of the points from set.  I prefer 
binary search to newton's method (division) only for this case. As I tested, for 10<sup>9</sup>, binary search takes 29 loop while newton method takes 19 loop. 
- The last best point has the same y value as query.  So we can skip binary search if x in query is bigger than the x value in best point.
- The input data contains a lot of duplicate queries.  If we sort every bucket, the duplicate queries can be skipped.

## 3. Paint by Letters

Initially I thought of segment tree to store the result.  Starting from 1X1 small box, grow it or union it with the small box through boundary of every smaller rectangle.  But union is very complicated.  It is challenging to get full credit.  Instead I used the simpler method.

I used one two dimensional prefix sum and four one dimensional prefix sum. For small box like 10X10, I just used union-find to get the answer.  For big box, I checked every head of connected components on four sides to make sure that it is the head, and planed to do the adjustment based on DFS or BFS-based flood fill.  The flood fill only needs to search the connected colors inside box (not outside the box).  For test case 6-11, the maximum depth is 3 as every connected component consisting of cells with the same desired color can be contained within a 3X3 square with sides parallel to the coordinate axes.  Thus the time complexity for every query is O(N) time.  But for test case 12-20, it may have TLE issue.


