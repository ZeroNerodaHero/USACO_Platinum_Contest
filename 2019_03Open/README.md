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

## 3.  Valleys

The problem is similar to [Cave Paintings](../2020_01Jan#1--cave-paintings).  The river flows through a valley.  Then continuous rain leads the river to rise steadily, causing flooding. Then the connected components are created.  The problem is to find these connected components when the river is rising.

For this question, if there is a hole inside the connected component, it has no contribution to the answer.  We have to find if one connected component has a hole.  One approach is to track the "curvature" of each connected component. Every corner of a component can be assigned a curvature (either 1 or −1).  Based on [the Gauss-Bonnet theorem](https://en.wikipedia.org/wiki/Gauss%E2%80%93Bonnet_theorem), the total curvature of one connected component is 4−4h, where h is the number of holes. So if we can maintain the curvature of each component throughout the process of inserting cells and union-find, then we can determine for each component whether it has any holes. 

In [valleys.cpp](valleys.cpp), I use the Euler's formula for planar graph, which is also used in [Paint by Letters](../2021_01Jan/README.md#3-paint-by-letters).

    V - E + F = 1 (connected component) + 1 = 2

Every cell is one vertex (V). Every two neighboring cells create one edge (E).  Every 2X2 square creates one circular region (C) inside this sqaure. H is the total holes inside the connected component.  Then the total face (F) is:

    F = 1 (unbounded region) + C + H
    H = E - V  + 2 - C - 1 (unbounded region) = E-V-C+1

I use the same union-find algorithm as in [Cave Paintings](../2020_01Jan/cave.cpp).  The vertices, edges, and circular regions in the old CC are merged to newly created CC.  Thus we only need to find the parent of the old CC.

  
