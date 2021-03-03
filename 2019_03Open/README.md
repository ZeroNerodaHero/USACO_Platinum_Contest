# Summary of Solutions:

## 1. Tree Boxes

The problem has two sub-tasks:

- Any tree path can be covered by one or two axis-aligned rectangles.
- Embed the tree in a 2-D plane

Any tree and its subtrees can be split into two parts such that both parts consist of a vertical chain in the tree.  Assume C is LCA(A,B), then any arbitrary path from A to B can be split into one path from A to C and the other path from B to its ancestor that is one level below C. If C=B, there will be only one path.

For second task, we can put the root at (1,1).  Then recursively put the subtrees in the squares, which are on the diagonal from left to right, or (2,N) to (N,2).  I wrote one demo program to show the embedded tree on 2-D plane and the result of query.

Visual of the tree created from [sample input](treeboxinput)
<pre>
    0
             3
         2
            8
           7
          9
     1
        5
       4
      6
</pre>

Visual of the query of farms 4-7:
<pre>
    +***
    *  *     3
    *  * +**
    *  * * *8
    *  * **-
    *  *  9
    *1 *
    *  *5
    ***-
      6
</pre>


USACO official solution uses an array to store the ancestors, which degrades the performance.  If we change the order of ancestors, it could improve the performance. The [optimized solution](treeboxoptim.cpp) uses binary search to find LCA and trims the graph to a tree.

We can also put all the squares in the diagonal from right to left.  The root should be at point (N, N) in this case.


## 2. Compound Escape

This problem can be solved with PLUG DP.  I use the same way as I solved [van.cpp](https://github.com/ZeroNerodaHero/USACO-Training-Gateway/blob/master/6.1/van.cpp) and [betsy.cpp](https://github.com/ZeroNerodaHero/USACO-Training-Gateway/blob/master/6.5/betsy.cpp).

As this problem is not a hamiltonian path, the state is different. The state is the set of connected components. When we have the same state, we need to choose the minimum cost.  If costs are the same, just add the count to the state.

The plug is defined as (state, minimun cost, count), where state is the one row connectivity state.  The plug for this problem has the following peroperties:

- the plug from upper layer can be optionally taken.  But at least one plug must be taken for one connected component.
- the plug from the left side must be taken.
- if plug from both upper layer and left side are taken, there must be no cycle.  In this case, two connected components are united into one.

We use two hash tables to store all the plugs for two consecutive rows.  We use union-find to process the plugs in each state at layer i-1.  For cells from [0, K-1], union of two connected components take the smallest cell number. With this encoding scheme, here is the inital state and answer:

- the inital state or plug is (0x543210, 0, 1)
- the answer is (0x000000, mincost, count)

The time complexity of plug DP is O(NC<sub>k</sub> * O(dfs)).  As the time complexity of dfs() takes O(8<sup>K</sup>), the [escapeplug.cpp](escapeplug.cpp) has the TLE issue when K increases.  If I change one of the plug properties as optionally taking left plug,  the time complexity of dfs() will be O(4<sup>K</sup>).

As I debug the code, I find the state of each row does not change. The [escapeplugprofiling.cpp](escapeplugprofiling.cpp) is used to get the transition table.  All the states forms a state group.  The total number of CC is 203 for K=6.  But the state like (1,2,1,2) are invalid as cross connection is not allowed.  If we use the bracket to represent the state, it looks like "([)]", which is invalid.  It also means that the case (1,2,1,2) is acutally one connected componets (1,1,1,1) instead of two.  The total number of valid state is reduced to 132 when K is 6.

I can use dfs() function in [escapeplug.cpp](escapeplug.cpp), which does state transition, to get the state.  But we can get the state in simpler way, without doing any state trasition.  The [escape_get_number.cpp](escape_get_number.cpp) prints all the state when K is 6.  I use this simpler dfs to get all the state in [escape.cpp](escape.cpp).

As state transition for each row is exactly the same, no multiple dfs() calls are needed.  We can do some pre-computation.  Here is the [escape.cpp](escape.cpp) algorithm:

- Do one dfs() to get all the states for number K
- Set the transition table, which used by each row.
- Do a transition row by row

The state space is very small.  So I can use perfect hash to find the state.  In [escapeplug.cpp](escapeplug.cpp) I use (0,1,2,3,4,5) to represent the connected components.  As one CC is always tagged as 0, I use 4 bits for each connected components for easy debugging. The total bits will be 20.  But in [escape.cpp](escape.cpp), I use (1,2,3,4,5,6) to represent the connected components for easy coding.  So I change to 3 bits so that the total bits of one state is 18 bits.  Thus (1<<18) is enough to build one perfect hash table.

I combined left plug and down plug into one complex plug for transition for fast processing. We can also split complex plug into left plug and down plug.  In that case, we need two simpler transition (tx) table.

## 3.  Valleys

The problem is similar to [Cave Paintings](../2020_01Jan#1--cave-paintings).  The river flows through a valley.  Then continuous rain leads the river to rise steadily, causing flooding. Then the connected components are created.  The problem is to find these connected components when the river is rising.

For this question, if there is a hole inside the connected component, it has no contribution to the answer.  We have to find if one connected component has a hole.  One approach is to track the "curvature" of each connected component. Every corner of a component can be assigned a curvature (either 1 or −1).  Based on [the Gauss-Bonnet theorem](https://en.wikipedia.org/wiki/Gauss%E2%80%93Bonnet_theorem), the total curvature of one connected component is 4−4h, where h is the number of holes. So if we can maintain the curvature of each component throughout the process of inserting cells and union-find, then we can determine for each component whether it has any holes.

In [valleys.cpp](valleys.cpp), I use the Euler's formula for planar graph, which is also used in [Paint by Letters](../2021_01Jan/README.md#3-paint-by-letters).

    V - E + F = 1 (connected component) + 1 = 2

Every cell is one vertex (V). Every two neighboring cells create one edge (E).  Every 2X2 square creates one circular region (C) inside this sqaure. H is the total holes inside the connected component.  Then the total face (F) is:

    F = 1 (unbounded region) + C + H
    H = E - V  + 2 - C - 1 (unbounded region) = E-V-C+1

I use the same union-find algorithm as in [Cave Paintings](../2020_01Jan/cave.cpp).  The vertices, edges, and circular regions in the old CC are merged to newly created CC.  Thus we only need to find the parent of the old CC.


