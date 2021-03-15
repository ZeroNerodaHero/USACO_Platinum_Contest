# Summary of Solutions:

## 1. 262144

This is interval DP.  It reminds me of the problem "Minimum Cost to Merge Stones", which can be solved in O(N<sup>2</sup>).  As **COST** is in the range [1,40], we can do DP optimization.  Assuming that the array contains 262144 (1<<18) number of 40, the final merged value is 58, which is maximum of all solutions.  It forms a complete binary merge tree in this case.

Now we generalize the formula.  Assume two consecutive intervals `[a, b)` and `[b, c)` have already been merged into value i.  Or we can say:

        `merged_value[a, b) = i`
        `merged_value[b, c) = i`

Then we can merge these two consecutive intervals into one interval `[a, c)`.  The new value is i+1 : `merged_value[a, c) = i+1`.  Now we can define state dp[i][j] as follows:

    `dp[i][j]` : the right index of the interval `[j, dp[i][j])`.  The merged value in this interval is i.

So the state `merged_value[a, b) = i` is `dp[i][a] = b`.

For initialization, any element a[i] can be treated as merged value in `[i, i+1)`.  So the initial state is `dp[a[i]][i] = i+1`.

The DP transition is as follows:

    dp[i][j] = dp[i-1][dp[i-1][j]] if dp[i][j] == 0;

In order to avoid boundary check, 0 is reserved for invalid range in [262144.cpp](262144.cpp).

As only 2<sup>n</sup> consecutive equal values can be merged, there is O(N) greedy algorithm, which checks if the small values can be merged to left or right value.

## 2. Bull in a China Shop

## 3. Landscaping
