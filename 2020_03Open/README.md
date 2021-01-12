# Summary of Solutions:

## 1. Sprinklers 2: Return of the Alfalfa

**Transition line** is defined as a zigzag line, which moves only down and forward, to divide the whole field into two parts.  The corn sprinkler must be placed at the corner when it turns down while an alfalfa sprinkler must be placed at the corner where it turns forward.

In [sprinklers.cpp](/2020_03Open/sprinklers.cpp) uses bottom-up dynamic programming.
In [sprinklers0_dp_topdown.cpp](/2020_03Open/sprinklers0_dp_topdown.cpp) uses top-down DP.
In [prinklers_modint.cpp](/2020_03Open/sprinklers_modint.cpp) uses modular integer data structure.

All three program above can pass all test cases.  The [sprinklersdfs.cpp](/2020_03Open/sprinklersdfs.cpp) is brute-force depth first search (DFS).  It could pass only the basic test case.  But it shows how we convert the dfs algorithm into powerful DP algorithm.


## 2. Exercise

Every permutation can be partitioned into permutation group(s) of sizes c1,c2,c3,…,ck such that c1+c2+…+ck<=N.  The minimum steps to return to the same order is actually lcm(c1,c2,…,ck).  Any composite number can be factorized into multiples of primes or prime power.If we can count the number of prime factors by using stirling number, we can get the answer by multiplying all the prime factors together.

## 3. Circus

In order to describe the algorithm, I first provide some defintions here:
#### Definitions

- **vertex**: a node in the tree. occupied/unoccupied vertex.
- **intermediate vertex/endpoint vertex**: An intermediate vertex has a degree of two while an endpoint has a degree other than two. 
- **occupied vertex/unoccupied vertex**: Occupied vertex has a cow while an unoccupied doesn't have a cow.
- **free node/fixed node/hidden node**: All of these nodes are unoccupied vertices. A free node can be anywhere in the tree. A fixed node is a root vertex of a connected component.  A hidden node is a vertex of a hidden chain.
- **chain**: chain (a, b) is one path from vertex **a** to vertex **b**. Vertex a and b are the only two **endpoint vertices** while all other vertices between a and b are **intermediate vertices**. Chain can be represented as **(a, b, l)** where **l** is the count of vertices along the path, include vertex a and b.
- **visible chain/hidden chain**: All the chains are visible initially. When there are enough free nodes (l+1), a visible chain becomes a hidden chain.
- **virtual connected component (VCC)**: **VCC** is a sub-tree with one root, which is an endpoint vertex. The sub-tree has a star topology.  The cows could possibly swap their positions only within one connected component.  It is represented as (root, number of visible chains, the nubmer of nodes in all hidden chains belonging to the CC).  Initially the number of visible chains is the degree of root.  And there is no hidden chain in this **CC**.
- **Cyclic sub-group**: One VCC can be treated as one cyclic sub-group as cows can swap their positions within CC.  The cows in different CCs could not swap their positions. As VCC has star topology, the root must be fixed endpoint.  All other (K-1) free nodes can be in one visible chain. Then cows on other visible chains can swap their positions, so the total number of cows is (k-1) * (#visible chain - 1). In addition, all the hidden nodes can temporarily used for storing cows.  So the total number of cows could swap their positions is (k-1)*(#visible chain -1) + (#hidden nodes).
- **Rule to merge two VCCs**: Two **CCs** are connected via (or blocked by) a visible chain **(a, b, l)**.  When there are **(l+1)** free nodes, the cows in **CC a** and **CC b** can change their positions.  Thus this visible chain becomes hidden. And two **CCs** are merged into one as the result.  The two roots **(vertex a nd b)** of two CCs are virtuallly become one root.  We can choose either a or b as the new root of merged CC. Here we choose a as the root of new CC.  So total number of visible chains in new CC will be sum of (#visible chains in CC a and b)-2.  The new CC will have  **(l-1)** more hidden nodes as either a or b becomes the root of newly merged CC.
- **normalization/de-normalization**: In normalization state, vertex 1..K does not have free/fixed node but cows. In denomalization state, free node and fix node can be anywhere.

#### Solution: 
The tree can be treated as a graph of CCs which are connected with (or segmented by) visible chains.  Here are the steps to take:

1. Pick up one endpoint vertex, do a DFS to collect all the visible chains (c) and all the connected components (cc)
2.  add free node one by one.  Recursively merge the connected componets (cc) until all becomes one, or until there is no visible chain.

#### Optimization

- Union-by-rank: Currently recursively union shortest and outmost chains first. Union-by-rank (number of unions) should not improve the performance a lot.
- Early exit: when there are enough CCs to do the exchanges, we can stop as all answers are 1.





## References:

#### 1. Sprinklers 2: Return of the Alfalfa

[Modular multiplicative inverse]( https://en.wikipedia.org/wiki/Modular_multiplicative_inverse)

#### 2. Exercise

[Permutation group]( https://en.wikipedia.org/wiki/Permutation_group)

[Fermat's little theorem]( https://en.wikipedia.org/wiki/Fermat%27s_little_theorem)


#### 3. Circus

[Discrete mathematics]( https://en.wikipedia.org/wiki/Discrete_mathematics)

[Equivalent class : 等价类/isomorphism](https://en.wikipedia.org/wiki/Equivalence_class )

[Union find]( https://en.wikipedia.org/wiki/Disjoint-set_data_structure)





