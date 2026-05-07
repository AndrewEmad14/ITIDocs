# 🧠 Problem Solve — Pancake Sorting

## 📌 Problem Information

- **Source:** [LeetCode 969 — Pancake Sorting](https://leetcode.com/problems/pancake-sorting/)
- **Difficulty:** Medium
- **Pattern Used:** Greedy Simulation (Selection Sort variant)
- **Tags:** `array` `sorting` `greedy` `simulation`

---

## 📝 Problem (In Plain English)

You're given an array that is a permutation of integers 1 to n. Your only allowed operation is a **pancake flip**: pick a number `k` and reverse the first `k` elements of the array. Return the sequence of `k` values used such that the array ends up fully sorted. Any valid sequence under `10 * n` flips is accepted.

---

## 📥 Input / 📤 Output

- **Input:** `arr` — an integer array, permutation of `[1, 2, ..., n]`
- **Output:** array of integers — the `k` values of each flip performed, in order

---

## ⚠️ Constraints

- `1 <= arr.length <= 100`
- `1 <= arr[i] <= arr.length`
- All integers are unique (permutation of 1 to n)
- Answer accepted if it sorts within `10 * arr.length` flips

---

## 🔍 Example Walkthrough

### Example 1
Input: `[3, 2, 4, 1]`
Output: `[4, 2, 4, 3]`

| Step | k | Operation | Result |
|---|---|---|---|
| 1 | 4 | Reverse first 4 | `[1, 4, 2, 3]` |
| 2 | 2 | Reverse first 2 | `[4, 1, 2, 3]` |
| 3 | 4 | Reverse first 4 | `[3, 2, 1, 4]` |
| 4 | 3 | Reverse first 3 | `[1, 2, 3, 4]` ✅ |

### Example 2
Input: `[1, 2, 3]`
Output: `[]` — already sorted, no flips needed.

---

## 🧪 Edge Cases to Watch

- Already sorted array → should return `[]` (or handle 0 flips gracefully)
- Single element array → nothing to sort
- Max element already at end of unsorted region → still emits two flips unless you add a skip condition
- Off-by-one on the flip range → passing `k = arrayLength` instead of `arrayLength - 1` causes out-of-bounds access

---

## 🚀 Approaches — Progressive Complexity

### 🐢 Approach 1 — Brute Force (Random Flips)

**Idea:** Randomly pick a `k`, flip, check if sorted, repeat until sorted.

**Why it's suboptimal:** No guarantee of termination in reasonable time. No deterministic bound on flip count. Unpredictable performance.

| Complexity | Value |
|---|---|
| Time | Unbounded / O(n! ) worst case |
| Space | O(1) |

**Doc Reference:** [Array.prototype.reverse — MDN](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Array/reverse)

---

### 🚶 Approach 2 — Greedy Simulation (Optimal for this problem)

**Idea:** Place the largest unsorted element into its correct position using at most 2 flips per element. Shrink the unsorted window by 1 each round. This is conceptually identical to **Selection Sort**, but the only swap mechanism available is a prefix reversal.

**Key insight over Approach 1:** You always know exactly which element to place next (the current max in the unsorted region) and exactly where it needs to go (end of unsorted region). This gives a deterministic 2n flip bound.

**Two-flip mechanic:**
1. Flip `0 → maxIndex` → brings max to index 0
2. Flip `0 → end of unsorted region` → places max at its final position

| Complexity | Value |
|---|---|
| Time | O(n²) — n rounds × O(n) per flip |
| Space | O(n) — for the result array |

**Doc Reference:** [Selection Sort — Wikipedia](https://en.wikipedia.org/wiki/Selection_sort) · [Array destructuring — MDN](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Operators/Destructuring_assignment)

---

### 🚀 Approach 3 — Same Complexity, Cleaner Skip

**Idea:** Same as Approach 2, but skip both flips when the max is already in its correct position (`maxIndex === arrayLength - 1`). Reduces unnecessary flips in partially sorted inputs.

**Why this is the ceiling:** The problem's constraint (permutation of 1..n, answer within 10n flips) fits O(n²) perfectly. No sub-quadratic solution is required or meaningfully applicable here given n ≤ 100.

| Complexity | Value |
|---|---|
| Time | O(n²) |
| Space | O(n) |

---

## ✅ Chosen Approach

**Greedy Simulation with skip condition** — best fit given constraints and the two-flip placement mechanic.

Step-by-step logic:
1. Start with `size = n` (full array is unsorted)
2. Find index of maximum element in `arr[0..size-1]`
3. If max is already at `size - 1`, skip — no flips needed
4. Otherwise: flip `0 → maxIndex` to bring max to front
5. Then flip `0 → size - 1` to move max to its final position
6. Record both `k` values in result
7. Decrement `size` and repeat until `size = 1`

---

## 🧩 Pseudocode

```
function pancakeSort(arr):
    result = []
    size = arr.length

    while size > 1:
        maxIndex = index of max in arr[0..size-1]

        if maxIndex == size - 1:
            size -= 1
            continue

        flip(arr, maxIndex)        // bring max to front
        result.push(maxIndex + 1)

        flip(arr, size - 1)        // send max to final position
        result.push(size)

        size -= 1

    return result
```

---

## 💻 Implementations

### ☕ Java

```java
class Solution {
    public List<Integer> pancakeSort(int[] arr) {
        List<Integer> result = new ArrayList<>();
        int size = arr.length;

        while (size > 1) {
            // find index of max in unsorted region
            int maxIdx = 0;
            for (int i = 1; i < size; i++) {
                if (arr[i] > arr[maxIdx]) maxIdx = i;
            }

            // skip if already in place
            if (maxIdx == size - 1) { size--; continue; }

            // flip 1: bring max to index 0
            flip(arr, maxIdx);
            result.add(maxIdx + 1); // k is 1-indexed

            // flip 2: send max to its final position
            flip(arr, size - 1);
            result.add(size);

            size--;
        }
        return result;
    }

    // reverses arr[0..k] inclusive
    private void flip(int[] arr, int k) {
        int left = 0, right = k;
        while (left < right) {
            int tmp = arr[left];
            arr[left++] = arr[right];
            arr[right--] = tmp;
        }
    }
}
```

**Java Docs:** [ArrayList — Java SE](https://docs.oracle.com/en/java/docs/api/java.base/java/util/ArrayList.html) · [Arrays — Java SE](https://docs.oracle.com/en/java/docs/api/java.base/java/util/Arrays.html)

---

### 🟨 JavaScript

```js
// helper: reverses arr[0..k] inclusive
const flipMe = function(arr, k) {
    for (let i = 0; i < (k + 1) / 2; i++) {
        [arr[i], arr[k - i]] = [arr[k - i], arr[i]]; // destructured swap
    }
};

var pancakeSort = function(arr) {
    const flips = [];
    let size = arr.length;

    while (size > 1) {
        // find index of max in unsorted region arr[0..size-1]
        let maxIndex = 0;
        for (let i = 1; i < size; i++) {
            if (arr[i] > arr[maxIndex]) maxIndex = i;
        }

        // skip if max is already in its final position
        if (maxIndex === size - 1) { size--; continue; }

        // flip 1: bring max to index 0
        flipMe(arr, maxIndex);
        flips.push(maxIndex + 1); // k values are 1-indexed

        // flip 2: place max at end of unsorted region
        flipMe(arr, size - 1);   // size-1, NOT size (0-indexed last element)
        flips.push(size);

        size--;
    }
    return flips;
};
```

**JS Docs:** [Array destructuring — MDN](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Operators/Destructuring_assignment) · [Array.prototype.push — MDN](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Array/push)

---

### 🐍 Python

```python
class Solution:
    def pancakeSort(self, arr: List[int]) -> List[int]:
        result = []
        size = len(arr)

        while size > 1:
            # find index of max in unsorted region
            max_idx = arr.index(max(arr[:size]))

            # skip if already in final position
            if max_idx == size - 1:
                size -= 1
                continue

            # flip 1: bring max to index 0
            arr[:max_idx + 1] = arr[:max_idx + 1][::-1]
            result.append(max_idx + 1)

            # flip 2: place max at end of unsorted region
            arr[:size] = arr[:size][::-1]
            result.append(size)

            size -= 1

        return result
```

**Python Docs:** [list.index — Python](https://docs.python.org/3/tutorial/datastructures.html) · [Slice notation — Python](https://docs.python.org/3/reference/expressions.html#slicings) · [typing.List — Python](https://docs.python.org/3/library/typing.html)

---

## 📊 Complexity Summary

| Approach | Time | Space | Notes |
|---|---|---|---|
| Brute Force | Unbounded | O(1) | Never use |
| Greedy Simulation | O(n²) | O(n) | ✅ Recommended |
| Greedy + Skip | O(n²) | O(n) | Minor optimization |

---

## 🧠 Mistakes & Traps

- **Off-by-one on flip range:** passing `k = arrayLength` instead of `k = arrayLength - 1` causes out-of-bounds access — arrays are 0-indexed, last valid index is `length - 1`
- **Forgetting the skip condition:** if max is already at the end of the unsorted region, doing two flips still "works" but adds unnecessary entries to the result
- **Conflating k (1-indexed) with index (0-indexed):** the problem asks for `k` values which are 1-indexed flip lengths, but your array indices are 0-indexed — `maxIndex + 1` and `size` are the correct `k` values to push

---

## 📚 What This Problem Teaches

- **Greedy placement:** you don't need a global plan — greedily placing the largest unsorted element each round is sufficient
- **Constraint-driven creativity:** when your only operation is limited (prefix reversal only), you adapt a known algorithm (Selection Sort) to work within that constraint
- **Two-step positioning:** a common pattern — move element to a known anchor point (index 0), then use a second operation to place it at the target. Appears in problems involving stacks, rotations, and linked list manipulation

---

## 🔗 Related Problems

- [LeetCode 206 — Reverse Linked List](https://leetcode.com/problems/reverse-linked-list/) — same two-pointer reversal mechanic
- [LeetCode 75 — Sort Colors](https://leetcode.com/problems/sort-colors/) — in-place sorting with constrained swaps
- [LeetCode 215 — Kth Largest Element in an Array](https://leetcode.com/problems/kth-largest-element-in-an-array/) — finding max/kth element efficiently

---

## 🎯 Comprehension Check

> You added a skip condition when `maxIndex === size - 1`. What happens to the **correctness** of the result if you remove that skip — and what happens to the **output array** of `k` values?