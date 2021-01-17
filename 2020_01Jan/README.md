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

As this is grid problem, I can also use the method, similar to **PLUG DP**, to solve this problem. But union and find is still needed.
1. initially DP state is empty, and id for each block is 0
2. go through each empty square at layer i-1, if there is empty and unidentified square at row i, group all the connected squares in row i.  If any square is not in the group, merge them (union-find to merge it). 
3. go through each square at layer i, if there is no group, create a new group.
4. fill the water at layer i.
5. repeat from step 2

This is not faster even time complexity is the same.  But it should get full credit.
 

## 2. Non-Decreasing Subsequences


For the longest increasing subsequence (LIS) problem, the DP state dp[i] is the length of LIS at i.  The dp[i+1] will search previous longest subsequence ending at a number less than a[i].  The time complexity is O(N2).  Of course, we can use binary search to reduce it to O(NlogN).  

In our problem, the number is in the range [1,K], or \[0,K).  And K is smaller enough. Instead of using binary search, we can use an array to save the number of sub-sequence ending at j which is in \[0,K) range.
Similar to LIS,

the DP state dp[i][j] can be the number of non-decreasing subsequence at i, but last number is j.
Thus the DP transition can be:

    a[i] not included: dp[i][j] = dp[i-1][j] for all j
    a[i] included: dp[i][j] += sum(dp[i-1][k]) for all k<=j, where j=a[i];

Actually we only need dp[K] to store the count.  In order to complete one query, it takes O(NK) time.  The total time comlexity is O(QNK).  You could not get full credit.  But the optimization is based on this DP transition.  Here is the code for one query [1,N].

    <pre>
    dp[0] =1; 
    for (int i =1; i<=N; ++i) 
        for (int j = a[i]; j>= 0; --j) dp[a[i]] += dp[j];
    ans = 0; for(int j=0; j<=K; ++j) ans += dp[j];
    </pre>
    
If we use matrix multiplication for DP transition, it can be expressed as a product of matrix.
Thus we can maintain a prefix product of matrix and also the product of inverse matrix.  It takes O(NK<sup>3</sup>) to build the prefix product.  It takes O(QK<sup>2</sup>) to get the answer.

In [nondec.cpp](nondec.cpp), we can still do more optimization.  Since this is sparse matrix and has special struture, the matrix multiplication is reduced to O(K<sup>2</sup>).  And it takes O(K) time to find solution to one query.

**Note: I just feel that we could use different ways other than matrix to do optimization.  But prefix sum/product should be used.  I will investigate it later.**

