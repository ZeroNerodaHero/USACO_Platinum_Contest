# Summary of Solutions:

## 1. Tree Boxes

## 2. Compound Escape

## 3.  Valleys

The problem is similar to [Cave Paintings](../2020_01Jan#1--cave-paintings).  The river flows through a valley.  Then continuous rain leads the river to rise steadily, causing flooding. Then the connected components are created.  The problem is to find these connected components when the river is rising.

For this question, if there is a hole inside the connected component, it has no contribution to the answer.  We have to find if one connected component has a hole.  One approach is to track the "curvature" of each connected component. Every corner of a component can be assigned a curvature (either 1 or −1).  Based on [the Gauss-Bonnet theorem](https://en.wikipedia.org/wiki/Gauss%E2%80%93Bonnet_theorem), the total curvature of one connected component is 4−4h, where h is the number of holes. So if we can maintain the curvature of each component throughout the process of inserting cells and union-find, then we can determine for each component whether it has any holes. 

In [valleys.cpp](valleys.cpp), I use the Euler's formula for planar graph, which is also used in [Paint by Letters](../2021_01Jan/README.md#3-paint-by-letters).

    V - E + F = 1 (connected component) + 1 = 2

Every cell is one vertex (V). Every two neighboring cells create one edge (E).  Every 2X2 square creates one circular region (C) inside this sqaure. H is the total holes inside the connected component.  Then the total face (F) is:

    F = 1 (unbounded region) + C + H
    H = E - V  + 2 - C - 1 (unbounded region) = E-V-C+1

I use the same union-find algorithm as in [Cave Paintings](../2020_01Jan/cave.cpp).  The vertices, edges, and circular regions in the old CC are merged to newly created CC.  Thus we only need to find the parent of the old CC.

  
