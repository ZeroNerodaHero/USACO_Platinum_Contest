# Summary of Solutions:

## 1.  Modern Art

I borrow the idea from Brian Dean.  First we find the rectangle frames for all visible colors.

We use two dimensioanl prefix sum p[MX][MX] to record the number of colors having appeared at location (i,j).  First, for every visible frame, we increase the value of p[i][j] by 1 at the top-left and bottom-right corner of each frame, while we decrease the value of p[i][j] by 1 at the bottom-left and top-right corner. Then we compute the prefix sums p[MX][MX].

Now in prefix sum **p**, each value p[i][j] will be equal to the number of visible frames covered at that point (i,j). Thus visible color a[i][j] will not be the first to be drawn if multiple colors have appeared at (i,j).  So we deduct these visble colors from the total colors **(N * N)**, or we increase the total **invisible** colors **(N * N - M)** if the visible color can be drawn first. 

## 2. Switch Grass

To find the shortest path two vertices (a, b) of different colors. We have the following observations:

- There are must be one path between vertices a and b.  On the path, there must exist an edge whose vertices (u, v) are different colors.  So the distance of (u, v) is shorter than (a,b).  So the shortest path must always be a single edge in the graph.
- On the path from a to b, the edge (u, v) is shortest means that it must be one edge in minimum spanning tree.  So our solution must be an valid edge, which both vertices are of different colors, of the minimum spanning tree in the graph.

Now the algorithm has to find the edge with minimum weight in MST, but exclude the edge whose two vertices have the same color.  For each **"update"**, it must be able to include/exclude the edges which we are searching for minimum weight in MST and track the change of minimum weight in MST. This is an online algorithm.

My algorithm is like this:

- Every edge in MST has a parent and child.  The parent vertex is responsible to maintain all the edges and local valid minimum weight among all the edges.  One MST link is uniquely tied to a child vertex.
- Use segment tree or set to maintain the local and global minimum weight.

In [grassoptim.cpp](grassoptim.cpp), I use too many STL set with a lot of insert/erase operations.  The memory allocation/free causes a huge perfomance drop.  But there is still room for optimization:

- Use a heap instead of set to avoid too much memory allocation.
- Check if some insert/erase/query operations are needed by storing the best minimum value somewhere.

The online algorithm is more straightforward.  But [the offline algorithm](grass.cpp) is much faster.  The offline algorithm inspects every edge first while online algorithm processes every query in order.  Both algorithm make use of Kruskal's algorithm to collect the edges in MST.  The offline algorithm is based on the followoing observation:

- I define the valid edge again.  For valid edge, both endpoint vertices have different colors.  It could possibly be the answer to the query.
- If a shortest edge with weight **w** become valid at query i and invalid at query j, any query in the range of [i, j-1] has **w** as the answer. 

Here is the algorithm:
- 1. First collect all the queries of color changes.  Append the query to that specific vertex.
- 2. Process every edge in sorted order.
- 3. For every edge, process the all the pending queries related to two vertices, based on our observation.
- 4. After, process the queries and merge it.
- 5. Loop to step 2

I use the same disjoint set in MST algorithm to skip the processed query.  I also uses the doubly linked (p,n) list to skip the query for each node.  There are still room for optimization.

- Early exit: If all the Q queries are answered, it is done.

Actually it is not necessary to run MST algorithm, but not doing so may cause it to be slower.  We can store the ranges of minimum values into a segment tree.  After that we do Q queries of segment tree.

## 3 COWBASIC

The loop can be up to 100K. But there could be multiple loops.  The stack or recursive call can be used to simulate multiple loop.  For single loop, the matrix can be used to reduce the time complexity, similar to solving the fibonacci sequence with matrix exponentiation.

