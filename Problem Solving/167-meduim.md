# 🧠 Problem Solve — Two Sum II (Input Array Is Sorted)

## 📌 Problem Information

- **Source:** [LeetCode 167](https://leetcode.com/problems/two-sum-ii-input-array-is-sorted/description/)
- **Difficulty:** Medium
- **Pattern Used:** Two Pointers
- **Tags:** `array` `two-pointers` `binary-search`

---

## 📝 Problem (In Plain English)

Given a sorted array of integers, find two numbers that add up to a target value. Return their 1-based indices. You cannot use the same element twice, and exactly one solution is guaranteed.

---

## 📥 Input / 📤 Output

- **Input:** sorted integer array `numbers`, integer `target`
- **Output:** `[index1, index2]` — 1-based, where `index1 < index2`

---

## ⚠️ Constraints

- `2 ≤ numbers.length ≤ 3 × 10⁴`
- `-1000 ≤ numbers[i] ≤ 1000`
- Array is sorted in non-decreasing order
- Exactly one solution exists
- Must use **O(1) extra space**

---

## 🔍 Example Walkthrough

### Example 1
```
Input:  numbers = [2, 7, 11, 15], target = 9
Output: [1, 2]
```
- `2 + 7 = 9` ✅ → indices 0 and 1 → return `[1, 2]`

### Example 2
```
Input:  numbers = [1, 2, 3, 4, 4], target = 8
Output: [4, 5]
```
- `4 + 4 = 8` ✅ → indices 3 and 4 → return `[4, 5]`

---

## 🧪 Edge Cases to Watch

- Negative numbers — a condition like `numbers[i] <= target` breaks here (your bug!)
- Duplicate values — e.g. `[4, 4]`, target `8`
- Target achieved at the very first and last elements
- All elements identical

---

## 🐛 The Bug You Hit

```js
if(numbers[i] <= target) { ... }  // ❌ WRONG
```

**Why it breaks:** When numbers are negative, a valid number like `-1` can be less than a negative target like `-2` is FALSE — so the iteration skips. The condition was meant to prune unnecessary iterations but it doesn't hold for negatives.

**Fix:** Remove the condition entirely. The binary search handles not finding a complement on its own by returning `-1`.

```js
// ✅ Just remove the guard — trust the binary search
for (let i = 0; i < numbers.length; i++) {
  secondNumberIndex = binary_search(numbers, target - numbers[i], i)
  ...
}
```

---

## 🚀 Approaches — Progressive Complexity

### 🐢 Approach 1 — Brute Force

**Idea:** For every pair `(i, j)` where `i < j`, check if `numbers[i] + numbers[j] === target`.

**Why it's suboptimal:** Checks every possible pair — doesn't exploit the sorted order at all.

| Complexity | Value |
|---|---|
| Time | O(n²) |
| Space | O(1) |

**Doc Reference:** [MDN Array iteration](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Array)

---

### 🚶 Approach 2 — Binary Search (Your Solution)

**Idea:** For each element at index `i`, binary search for its complement `target - numbers[i]` in the rest of the array. Pass `i` to avoid reusing the same index.

**Key insight over Approach 1:** Binary search reduces the inner scan from O(n) to O(log n) by exploiting sorted order.

**Bug to fix:** Remove the `numbers[i] <= target` guard — it incorrectly skips valid negative numbers.

| Complexity | Value |
|---|---|
| Time | O(n log n) |
| Space | O(1) |

**Doc Reference:** [Binary Search — Wikipedia](https://en.wikipedia.org/wiki/Binary_search_algorithm)

---

### 🚀 Approach 3 — Two Pointers (Optimal)

**Idea:** Place one pointer at the start (`left = 0`) and one at the end (`right = n-1`). Compute their sum:
- If sum === target → found it
- If sum < target → move `left` right (need a bigger number)
- If sum > target → move `right` left (need a smaller number)

**Why this is the ceiling:** Each pointer moves at most n times total — single pass, no extra space. Exploits sorted order maximally.

**Why it works:** Because the array is sorted, moving `left` right always increases the sum, and moving `right` left always decreases it. You're guaranteed to converge on the answer.

| Complexity | Value |
|---|---|
| Time | O(n) |
| Space | O(1) |

**Doc Reference:** [Two Pointers Technique — LeetCode Explore](https://leetcode.com/explore/learn/card/array-and-string/205/array-two-pointer-technique/)

---

## ✅ Chosen Approach — Two Pointers

Step-by-step logic:
1. Initialize `left = 0`, `right = numbers.length - 1`
2. While `left < right`:
   - Compute `sum = numbers[left] + numbers[right]`
   - If `sum === target` → return `[left+1, right+1]`
   - If `sum < target` → `left++` (need larger value)
   - If `sum > target` → `right--` (need smaller value)
3. Guaranteed to find answer — no need for a fallback return

---

## 🧩 Pseudocode

```
left = 0
right = length - 1

while left < right:
    sum = numbers[left] + numbers[right]
    if sum == target:
        return [left+1, right+1]
    else if sum < target:
        left++
    else:
        right--
```

---

## 💻 Implementations

### ☕ Java

```java
public int[] twoSum(int[] numbers, int target) {
    int left = 0, right = numbers.length - 1;

    while (left < right) {
        int sum = numbers[left] + numbers[right];

        if (sum == target) {
            return new int[]{left + 1, right + 1}; // 1-indexed
        } else if (sum < target) {
            left++;  // sum too small, move left pointer right
        } else {
            right--; // sum too big, move right pointer left
        }
    }

    return new int[]{}; // never reached — problem guarantees a solution
}
```

**Java Docs:** [Java Arrays](https://docs.oracle.com/en/java/docs/api/java.base/java/util/Arrays.html)

---

### 🟨 JavaScript

```js
var twoSum = function(numbers, target) {
    let left = 0, right = numbers.length - 1;

    while (left < right) {
        const sum = numbers[left] + numbers[right];

        if (sum === target) {
            return [left + 1, right + 1]; // 1-indexed
        } else if (sum < target) {
            left++;  // need a larger number
        } else {
            right--; // need a smaller number
        }
    }
};
```

**JS Docs:** [MDN Array](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Array)

---

### 🐍 Python

```python
def twoSum(numbers: list[int], target: int) -> list[int]:
    left, right = 0, len(numbers) - 1

    while left < right:
        s = numbers[left] + numbers[right]

        if s == target:
            return [left + 1, right + 1]  # 1-indexed
        elif s < target:
            left += 1   # need larger value
        else:
            right -= 1  # need smaller value
```

**Python Docs:** [Python list](https://docs.python.org/3/tutorial/datastructures.html)

---

## 📊 Complexity Summary

| Approach | Time | Space | Notes |
|---|---|---|---|
| Brute Force | O(n²) | O(1) | No use of sorted property |
| Binary Search | O(n log n) | O(1) | Your solution — valid, one bug fixed |
| Two Pointers | O(n) | O(1) | ✅ Recommended — optimal |

---

## 🧠 Mistakes & Traps

- **The `numbers[i] <= target` guard** — breaks on negatives. Never add pruning conditions without testing negative inputs.
- **`end = numbers.length` in binary search** — off-by-one, last valid index is `length - 1`
- **`findIndex` returning `-1` vs `undefined`** — always check what a search function returns on failure before comparing
- **Push order assumption** — `i` is not always the smaller index; always sort before pushing

---

## 📚 What This Problem Teaches

- **Two pointers** is the canonical pattern for sorted array pair problems
- Sorted order is an *exploitation opportunity* — always ask "what does sorted buy me?"
- Pruning conditions (like `<= target`) must be proven correct for all input domains — especially negatives
- O(n log n) via binary search is valid but O(n) via two pointers is the ceiling here

---

## 🔗 Related Problems

- [Two Sum (LeetCode 1)](https://leetcode.com/problems/two-sum/) — unsorted version, requires hashmap → O(n) time, O(n) space
- [3Sum (LeetCode 15)](https://leetcode.com/problems/3sum/) — extends two pointers to three elements
- [Container With Most Water (LeetCode 11)](https://leetcode.com/problems/container-with-most-water/) — two pointers on a different optimization axis

---

## 🎯 Comprehension Check

> In the two-pointer solution, why is it **safe** to permanently move a pointer inward and never reconsider it? What property of the array guarantees you won't miss the answer?