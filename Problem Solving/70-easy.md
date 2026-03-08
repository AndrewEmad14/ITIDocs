# 🧠 Problem Solving Note

## 📌 Problem Information

-   **Title:** Climbing Stairs
-   **Source:** LeetCode
-   **Difficulty:** Easy
-   **Link:** https://leetcode.com/problems/climbing-stairs/
-   **Status:** Solved

**Tags:**\
`dynamic-programming` `recursion` `memoization`

**Pattern Used:**\
Dynamic Programming / Fibonacci Pattern

------------------------------------------------------------------------

# 📝 Problem Statement

You are climbing a staircase. It takes **n steps** to reach the top.

Each time you can climb:

-   **1 step**
-   **2 steps**

Return the **number of distinct ways** to reach the top.

------------------------------------------------------------------------

# 📥 Input

    n

-   `n` = number of steps in the staircase.

------------------------------------------------------------------------

# 📤 Output

Return an integer representing **the total number of distinct ways to
reach the top**.

------------------------------------------------------------------------

# ⚠️ Constraints

-   `1 ≤ n ≤ 45`

------------------------------------------------------------------------

# 🔍 Examples

### Example 1

Input

    n = 2

Output

    2

Explanation

    1 + 1
    2

------------------------------------------------------------------------

### Example 2

Input

    n = 3

Output

    3

Explanation

    1 + 1 + 1
    1 + 2
    2 + 1

------------------------------------------------------------------------

# 💡 Initial Thoughts

Observations:

-   From any step we can come from:
    -   **1 step before**
    -   **2 steps before**

So:

    ways(n) = ways(n-1) + ways(n-2)

This is exactly the **Fibonacci sequence**.

------------------------------------------------------------------------

# 🧪 Edge Cases

-   `n = 1`
-   `n = 2`
-   Very large recursion calls if not optimized

------------------------------------------------------------------------

# 🚀 Possible Approaches

# Approach 1 --- Brute Force Recursion

Idea:

At each step we try:

-   climb **1 step**
-   climb **2 steps**

Recursively explore both possibilities.

Pseudo idea:

    ways(n) = ways(n-1) + ways(n-2)

However, this recomputes the same states many times.

Example recursion tree:

    f(5)
    ├─ f(4)
    │  ├─ f(3)
    │  │  ├─ f(2)
    │  │  └─ f(1)
    │  └─ f(2)
    └─ f(3)

Many repeated computations.

### Time Complexity

    O(2^n)

### Space Complexity

    O(n)

(recursion stack)

------------------------------------------------------------------------

# Approach 2 --- Memoized Recursion (Dynamic Programming)

Idea:

Store already computed results in a **memoization map**.

When we compute `ways(n)`:

-   first check if we already solved it
-   if yes → return stored value
-   if not → compute and store it

This avoids repeated work.

------------------------------------------------------------------------

# 🧩 Algorithm (Pseudo Code)

    create memo map

    function helper(n):

        if n <= 2
            return n

        if n exists in memo
            return memo[n]

        result = helper(n-1) + helper(n-2)

        store result in memo

        return result

------------------------------------------------------------------------

# 💻 Implementation (Your Solution)

### JavaScript

``` javascript
/**
 * @param {number} n
 * @return {number}
 */
var climbStairs = function(n) {
    const memo = new Map();

    const helper = (steps) => {
        if (steps <= 2) return steps;

        if (memo.has(steps)) return memo.get(steps);

        const result = helper(steps - 1) + helper(steps - 2);

        memo.set(steps, result);

        return result;
    };

    return helper(n);
};
```

------------------------------------------------------------------------

# 📊 Complexity Analysis

### Time Complexity

    O(n)

Each state from `1 → n` is computed once.

------------------------------------------------------------------------

### Space Complexity

    O(n)

-   memo storage
-   recursion stack

------------------------------------------------------------------------

# 🧠 Key Insight

This problem is a **classic Fibonacci Dynamic Programming problem**.

    f(n) = f(n-1) + f(n-2)

------------------------------------------------------------------------

# 📚 What I Learned

-   Recognizing **Fibonacci patterns in DP**
-   Using **memoization to reduce exponential recursion**
-   Turning **O(2\^n)** recursion into **O(n)** dynamic programming

------------------------------------------------------------------------

# 🔗 Related Problems

-   Fibonacci Number
-   Min Cost Climbing Stairs
-   House Robber
-   Tribonacci Number

------------------------------------------------------------------------

# 🔁 Review Notes

Possible improvements:

-   **Bottom-up DP**
-   **Constant space solution**
