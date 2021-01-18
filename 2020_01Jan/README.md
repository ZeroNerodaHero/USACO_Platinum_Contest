# Summary of Solutions:

## 1.  Cave Paintings
We can emulate the water rising from the bottom layer, i.e. (N-1)th layer.

#### Definition: 
- connected block (CB) at row i: the collection of empty sqaures at row i and below.  If any empty square at row i is filled with water, all other squares at row i and below will be filled with water, following the constraints in the problem.

- merge of connected blocks: when two **CBs** with c1 and c2 ways are merged, the merged CB will have c1 * c2 ways.

- Fill water at row i: Following the constraints in the problem, if any empty square is filled with water, then the entire connected block is bound to fill up. So the contribution of the new layer to each connected block is 1 more.

#### Algorithm Description

Initially all id for sqaures are 0.  Now start DP from the bottom (N-1)th layer.

1. For every empty square, create a new CB if the square on the left is a rock. If the left square is empty, the id of this square is the same as left (j-1) one.
2. Check the square below.  If it is empty square, merge two CBs if the they're not the same CB.
3. Repeat until the whole row is processed.
4. Fill the water for every CB at row i.
5. Repeat until all rows are processed.
6. Go through each CB, multiply all the numbers together, which is the answer.


#### Trick to do union-by-rank

We always merge the CB to the newly created one, the biggest one.  Thus we only need to do one find(), instead of two.

#### Another PLUG DP algorithm

As this is grid problem, I can also use the method, similar to [**PLUG DP**](https://github.com/ZeroNerodaHero/USACO-Training-Gateway/blob/master/6.5/betsy.cpp), to solve this problem. But union and find is still needed.
1. initially DP state is empty, and id for each block is 0
2. go through each empty square at layer i-1, if there is empty and unidentified square at row i, group all the connected squares in row i.  If any square is not in the group, merge them (union-find to merge it). 
3. go through each square at layer i, if there is no group, create a new group.
4. fill the water at layer i.
5. repeat from step 2

This is not faster even though time complexity is the same.  But it should get full credit.
 

## 2. Non-Decreasing Subsequences


For the longest increasing subsequence (LIS) problem, the DP state dp[i] is the length of LIS at i.  The dp[i+1] will search previous longest subsequence ending at a number less than a[i].  The time complexity is O(N2).  Of course, we can use binary search to reduce it to O(NlogN).  

In our problem, the number is in the range [1,K], or \[0,K).  And K is smaller enough. Instead of using binary search, we can use an array to save the number of sub-sequence ending at j which is in \[0,K) range.
Similar to LIS,

the DP state dp[i][j] can be the number of non-decreasing subsequence at i, but last number is j.
Thus the DP transition can be:

    a[i] not included: dp[i][j] = dp[i-1][j] for all j
    a[i] included: dp[i][j] += sum(dp[i-1][k]) for all k<=j, where j=a[i];

Actually we only need dp[K] to store the count.  In order to complete one query, it takes O(NK) time.  The total time comlexity is O(QNK).  You could not get full credit.  But the optimization is based on this DP transition.  Here is the code for one query [l,r].


    dp[0] =1; 
    for (int i =l; i<=r; ++i) 
        for (int j = a[i]; j>= 0; --j) dp[a[i]] += dp[j];
    ans = 0; for(int j=0; j<=K; ++j) ans += dp[j];

    
If we use matrix multiplication for DP transition, it can be expressed as a product of matrix as follows.

    ans=S*M[Al]*...*M[Ar]*T

    where S is 1*K matrix (1,0..0), T is K*1 matrix (1,1,...1). M is K*K matrix.

Thus we can maintain a prefix product of matrix and also the product of inverse matrix.  It takes O(NK<sup>3</sup>) to build the prefix product.  It takes O(QK<sup>2</sup>) to get the answer for query(l, r). In [nondec.cpp](nondec.cpp), I define prefix product as follows.

    The prefix prouduc v[x] is M[A1]*..*M[Ax]*T.
    The prefix product iv[x] is S*IM[Ax]*..*IM[A1].
    IM[Ax] is the inverse matrix of M[Ax].

In [nondec.cpp](nondec.cpp), I do more optimization.  M and IM are sparse matrix and have special strutures.  Here **I** is defined as identity matrix in linear space of KxK matrix.

    M = I + A
    IM = I + B
    where A/B has only (Ax+1) 1/(-1/2) at column Ax.

The matrix multiplication is reduced to O(K<sup>2</sup>).  And it takes O(K) time to find solution to one query.

Note: I just feel that there is still room to do optimization, or we could use different ways other than matrix to do optimization.  But prefix sum/product should be used.  I will investigate it later.


## 3. Falling Portals

The y location of cow i is changed with time t as this line: y[i] = a[i] - i * t.  The journey length for cow i to word Qi is the **positive** t-coordinate of intersection of the two lines.  But cow i can jump to other world to make the journey shorter. Thus we need to find another world for a smallest t-coordinate of intersection if possible.  As all A[i] are distinct numbers, there are only two cases: A[Qi] < A[i] and A[Qi]> A[i].

1.  In case of A[Qi] < Ai, we should find a world **j** falling faster than **max((i-1), Qi)** to catch Qi if possible. First we sort all Ai in decreasing order.  Then we maintain a set of worlds which fall faster.  Then we can do binary search to find j.  The answer is the t-coordinate of the intersection of line Qi and j.

2. In case of A[Qi] > Ai, we should find a world falling slower to wait for Qi.

This is actually a greedy algorithm.  The [falling.cc](falling.cc) is somewhat similar to [Graham Scan Algorithm](https://github.com/ZeroNerodaHero/Competitive/blob/master/21-Convex-Hull/graham2.cpp) to build a convex hull.


