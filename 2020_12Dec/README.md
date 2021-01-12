# Summary of Solutions:

## 1. Sleeping Cows

In dynamic programming, the state definition is very important. In [sleep.cpp](/2020_12Dec/1sleep.cpp), DP state dp(b, c,  flag) is defined as the number of cows which must be placed and the flag to indicate whether all cows have been placed till now.  The number of DP state is greatly reduced.

In [sleep0.cpp](/2020_12Dec/sleep0.cpp), DP state (b, m, o) is defined as the number of cows which must be placed (m) and the number of cows which can optionally be placed (o).  The number of DP state is increased a lot to about one million.  As DP state has two different integers, I can only use hash table to store the state.  And some state gradually becomes invalid state, it wasted a lot of computation power.  It works for all cases, but it needs more time than allowed.


## 2. Spaceship

This is also a dynamic programming.  The state dp(a,b,k) is defined as total number of sequences of rooms from a to b, but only involve pressing buttons with numbers at most k. Then we get the state transition formula which is similar to Floyd–Warshall algorithm.
 
    dp(a, b, k) = dp(a, m, k-1) * dp(m, b, k-1) for all intermediate room m.

In order to support all queries, the room number a and b in query is changed to (a+N) and (b+N).

## 3. Cowmistry

The problem shares some similarity with [Cow XOR problem in USACO Training Gateway Section 6.1](https://github.com/ZeroNerodaHero/USACO-Training-Gateway/blob/master/6.1/xor.cpp).  But in this problem, the number of mixtures of **THREE** different cows must be found.

The trick here is to divide the box into two parts based on **K**. In each part, (x xor y) is less than K if x and y in the same part.  For (x xor y >= K), Without Loss of Generality (WLOG), we can assume that one cow is in first part while the other two cows are in the second part.  Recursively find them by dividing each box into two parts, based on the same technique in Cow XOR problem.

