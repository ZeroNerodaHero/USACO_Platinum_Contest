# Notes of Solutions:

## 1. Googol

The tree is similar to AVL, but not BST.  It is similar to complete binary tree, but last row might be different.  At least it is highly balanced binary tree. Suppose the tree height is h, the h-1 level binary tree is one complete binary tree with (2<sup>h</sup>-1) nodes.  

There are different ways to do the counting:
- Count the size of subtree.  We can count the right tree first.  Then use the size information to count the size of left tree.
- We can count the left tree first.  Then use the size information to count the size of right tree.
- We can count the size of last level.  The solution is (2<sup>h</sup>-1) + (total in the level h).

As N is 10<sup>100</sup> maximumly, the maximum h is 334.  We should use big number to store the number of nodes.  But input data seems very small in USACO website.


## 2. Palindromic Paths

First, we make an observation about palindromic routes which Bessie could take.
- The length is 2N-1
- The middle character must be one point on secondary diagonal of the square matrix.

This reminds me of interval DP like longest palindromic subsequence.  We define the DP state as follows:

    dp[l][a][b][c][d]: number of palindromic routes from point (a,b) to (c,d) with lenght 2*l+1
    initial state: dp[0][1][N][1][N] = ... = dp[0][N][1][N][1] = 1
    transition: dp[l][a][b][c][d] = sum (4 pair of neighboring points dp[l-1][A][B][C][D]) if a[A][B]=a[C][D], A>=C, B<=D
    answer: dp[N-1][1][1][N][N]

The time complexity is O(N<sup>5</sup>).  The 4 pairs of points a[A][B] and a[C][D] are constrained.  Their Manhattan distances to **the same point** on the secondary diagonal equals to l-1.  We can start constructing palindromic string from the points on in the secondary diagonal.  There are different ways to define the DP state.  Here is the one in [palpath.cpp](palpath.cpp).

    dp[l][a][b] : number of palindromic string with length (2l+1) from row a to row b
    initial state: dp[0][1][1] = ... = dp[0][N][N] = 1
    the answer: dp[N-1][1][N]

The time complexity is O(N<sup>3</sup>).  If we use memory rotation to store the result, the space complexity can be reduced to O(N<sup>2</sup>).

In current solution we start constructing the palindromic strings from the point on secondary diagonal.  We can also do it in the different way.  Here are more solutions:
- Construct the palindromic strings (2N-1) from column a to column: dp[l][a][b].
- Construct the palindromic strings (2N-1) from line s parallel to the secondary diagonal: dp[l][s][i] where i is the row number.  The answer is dp[N-1][N-1][0].
- Construct the palindromic strings (2N-1) starting from both ends: point [1][1] and [N][N].  After reaching the point in secondary diagonal.  We add all the number together to get the answer.

All of these solutions take advantage of the palindromic string constraint on two points (a,b) and (c,d).

## 3. Trapped in the Haybales (Gold)

This problem requires to find the trapped boundary of any interval [l,r].  If the interval could break leftmost or rightmost haybale, it should not be counted.  If we greedily check each interval separately, the time complexity would be O(N<sup>2</sup>).  For certain interval, we can save the check result for some or all interval which have been checked. 
- 1. For certain interval (l,r), we greedily and repeatedly check if the distance is enough to break left or right haybale.
- 2. If Bessie could not escape, she could not escape if she is in any of the checked intervals on the right side.
- 3. If Bessie could escape, she could escape if any right interval could break **haybale l**.
- 4. Save the parent of the l so that we do not need to check the interval [f[l], l] again for next loop. 

The [greedy algorithm](trapped.cpp) uses union-find algorithm to store the boundary information on left side.  And in addition, it uses one trapped array or right boundary information to store the all intervals where Bessie could or could not escape.

