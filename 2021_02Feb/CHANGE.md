# Possible Change in Problem and/or Solution:

## 1. No Time to Dry

If we scale Q up to 2\*10<sup>6</sup>, O(Q) algorithm is needed.  [1dry.cpp](1dry.cpp) can avoid TLE issue with problem change.

## 2. Minimizing Edges

First I provide several defintions here: 
    
- **root**: In a connected undirected graph/tree, any node can be designated as root.  Any vertex, including root, has infinite number of distances from root.  There could be two shortest distances with even and/or odd number.
- **left/right shortest distance**: If there are two even/odd shortest distances, the left shortest distance is small while the right one is bigger.  If there is only one odd or even shortest distance, the left SF is shortest distance while the right one is 0 or -1 or INF.
- **team**: a group of vertices with the same left and right shortest distances.  This is similar to [the chain definition](/2020_03Open/README.md#3-circus) in Circus problem.  The team is a group of vertices while the chain is a group of edge.  This is different from weight.  All the vertices in team vertex may or may not be directly connected.  With team concept, the self-loop and cross connection can be processed in the same way.

Here I outline the different solution to this problem.  Some solution does not require problem change.  Some must have the problem change.  

### 1. Greedy Algorithm

This depends on the valid edge definition.

- In [2graph.cpp](2graph.cpp), the valid edge is based on d1 value. There are two connectivity cases: mandatory connection and optional connection.  To process one team vertex, it answers three questions:
    1. Can I get help from my left team parent?
    2. Must/Should I help my right team parent?
    3. Can I get help myself with self-loop/cross-connection?
- Benjamin Qi and Danny Mittal defines type A/B/C edge, the algorithm use (d1-1) vertex in both upper layer and lower layer to re-contstruct graph.
- Could algorithm be based on earliest "copy loop"?  Only "copy loop", the self-loop or cross connect, needs extra edges.  In the diamond graph (1-2, 1-3, 2-4, 3-4), there is no "copy loop".  The graph becomes a tree after being processed.  The algorithm could be based on first traversal and second traversal.  The first traversal will ignore any loop while the second traversal will only consider loop.


### 2. Dijkstra Algorithm Without Re-construction

We can do shortest path search for only one time.  


### 3. Build New Undirected Graph, Do Another Dijkstra Algorithm.

We first build the new directed graph based on valid edge.  Can we solve it with another SPF traversal?

### 4. Directed Forest/Graph

We first build one directed forest or graph based on **d1** value.  After that can we find one algorithm to collect the mandatory edge? 

### 5. MST algorithm

Even with the problem change, I can not image the MST solution to this kind of problem.

### 6. PLUG DP

This problem is related to connectivity problem.  It could possibly solved by plug DP.  

The plug definition is complicated for this problem.  The encoding of plug (or space) can be limited to one 32-bit integer. Similar to [sleeping cow](/2020_12Dec#1-sleeping-cows), the plug should have the following property

    1. optional plug (o)
    2. mandatory plug (m)

### Extended Max-Flow Method

The flow is a positive integer.  In this problem, could it be a negative integer or some special object?  We need to find minimum flow, not minimum cut, level by level to make the graph still connected in the original way.

### Enhanced Union-Find Algorithm

As this is connectivity problem, can we use union-find, but with some special property?

## 3.  Counting Graphs

For [](), I borrow the idea from Danny Mittal and Benjamin Qi.  It could be solved in the similar way as I used in problem 2: []().  It could save a lot of inclusion-exclusion operation.


There are three cases we should take care: mandatory case, general case, optional case, or negative case in []().


There are two team vertex (d, d1, n) and (d-1, d1+1, m).  In order to maintain the original connectivity, it becomes a sub-task as follows:

- children has no parent (d-1, d+1): Every one of n children must be connected to at least one of m parents. Every one of m parents must have at least one of n children.
- children has parent (d-1, d+1, x): Every one of n children must be connected to at least one of (m+x) parents. Every one of m parents must have at least one of n children.

This is permuation problem.


With permutation, we could possibly increase N to 1000 in the problem.  If all similar vertices are group into one team vertex, the graph becomes very small.  The following is the team graph taken from case 2 in Problem 2.

    /home/billy/usaco$ ./a.out < 20.in 
    case 2:
     1: (16, 1) 
     2: (15, 5) (17, 2) 
     3: (14, 7) (16, 1) (18, 6) 
     4: (13, 4) (15, 1) (17, 5) (19, 2) 
     5: (12,10) (14, 1) (16, 4) (18, 1) (20, 7) 
     6: (11, 5) (15, 3) (19, 8) (21, 1) 
     7: (10, 5) (12, 1) (14, 7) (18, 4) 
     8: ( 9, 3) (11, 2) (13, 9) (15, 1) (17, 2) 
     9: (10, 1) (12, 4) (14, 1) (16, 5) (18, 1) 
    10: (15, 5) (17, 1) 
    11: (14, 4) 
    12: (13, 4) (15, 1) 
    
    2 todo list: (16, 1) 
    2: 15, 5 ans 134
        must : push to next  5
        must : 15, 5 ans 134
    2: 15, 5 ans 134
    2: 17, 2 ans 134
        best : 16, 1 ans 134
    2: 17, 2 ans 134
    3 todo list: (15, 5) 
    3: 14, 7 ans 134
        must : push to next  7
        must : 14, 7 ans 134
    3: 14, 7 ans 134
    3: 16, 1 ans 134
        best : 15, 5 ans 134
    3: 16, 1 ans 134
    3: 18, 6 ans 134
        best : 17, 2 ans 134
    3: 18, 6 ans 134
    4 todo list: (14, 7) 
    4: 13, 4 ans 134
        must : 14, 7 add more 3
        must : push to next  4
        must : 13, 4 ans 137
    4: 13, 4 ans 137
    4: 15, 1 ans 137
        best : 14, 7 ans 137
    4: 15, 1 ans 137
    4: 17, 5 ans 137
        best : 16, 1 ans 137
    4: 17, 5 ans 137
    4: 19, 2 ans 137
        best : 18, 6 ans 137
    4: 19, 2 ans 137
    5 todo list: (13, 4) 
    5: 12, 10 ans 137
        must : push to next  10
        must : 12, 10 ans 137
    5: 12, 10 ans 137
    5: 14, 1 ans 137
        best : 13, 4 ans 137
    5: 14, 1 ans 137
    5: 16, 4 ans 137
        best : 15, 1 ans 137
    5: 16, 4 ans 137
    5: 18, 1 ans 137
        best : 17, 5 ans 137
    5: 18, 1 ans 137
    5: 20, 7 ans 137
        best : 19, 2 ans 137
    5: 20, 7 ans 137
    6 todo list: (12, 10) 
    6: 11, 5 ans 137
        must : 12, 10 add more 5
        must : push to next  5
        must : 11, 5 ans 142
    6: 11, 5 ans 142
    6: 15, 3 ans 142
        best : 14, 1 ans 142
    6: 15, 3 ans 142
    6: 19, 8 ans 142
        best : 18, 1 ans 142
    6: 19, 8 ans 142
    6: 21, 1 ans 142
        best : 20, 7 ans 142
    6: 21, 1 ans 142
    7 todo list: (11, 5) 
    7: 10, 5 ans 142
        must : push to next  5
        must : 10, 5 ans 142
    7: 10, 5 ans 142
    7: 12, 1 ans 142
        best : 11, 5 ans 142
    7: 12, 1 ans 142
    7: 14, 7 ans 142
        must : push to next  7
        must : 14, 7 ans 142
    7: 14, 7 ans 142
    7: 18, 4 ans 142
        must : push to next  4
        must : 18, 4 ans 142
    7: 18, 4 ans 142
    8 todo list: (10, 5) (14, 7) (18, 4) 
    8: 9, 3 ans 142
        must : 10, 5 add more 2
        must circle : add 2
        must : 9, 3 ans 146
    8: 9, 3 ans 146
    8: 11, 2 ans 146
        best : 10, 5 ans 146
    8: 11, 2 ans 146
    8: 13, 9 ans 146
        best : 12, 1 ans 146
        best : 14, 7 add more 7
        best : push to next  -7 ans 153
        best : must 14, 7 ans 153
    8: 13, 9 ans 153
    8: 15, 1 ans 153
        best : 14, 7 ans 153
    8: 15, 1 ans 153
    8: 17, 2 ans 153
        must : 18, 4 add more 2
        must : push to next  2
        must : 17, 2 ans 155
    8: 17, 2 ans 155
    9 todo list: (13, -7) (17, 2) 
    9: 10, 1 ans 155
        best : 9, 3 ans 155
    9: 10, 1 ans 155
    9: 12, 4 ans 155
        best : 11, 2 ans 155
        best : push to next  -4 ans 155
        best : must 13, -7 ans 155
    9: 12, 4 ans 155
    9: 14, 1 ans 155
        best : 13, 9 ans 155
    9: 14, 1 ans 155
    9: 16, 5 ans 155
        best : 15, 1 ans 155
        best : 17, 2 add more 2
        best : push to next  -2 ans 157
        best : must 17, 2 ans 157
    9: 16, 5 ans 157
    9: 18, 1 ans 157
        best : 17, 2 ans 157
    9: 18, 1 ans 157
    10 todo list: (12, -4) (16, -2) 
    10: 15, 5 ans 157
        best : 14, 1 ans 157
        best : push to next  -2 ans 157
        best : must 16, -2 ans 157
    10: 15, 5 ans 157
    10: 17, 1 ans 157
        best : 16, 5 ans 157
    10: 17, 1 ans 157
    11 todo list: (15, -2) 
    11: 14, 4 ans 157
        must : 15, -2 sub more 2
        must : push to next  4
        must : 14, 4 ans 155
    11: 14, 4 ans 155
    12 todo list: (14, 4) 
    12: 13, 4 ans 155
        must circle : add 2
        must : 13, 4 ans 157
    12: 13, 4 ans 157
    12: 15, 1 ans 157
        best : 14, 4 ans 157
    12: 15, 1 ans 157
    157
