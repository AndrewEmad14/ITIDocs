# 🧠 Problem Solve — Kth Largest Element in an Array

## 📌 Problem Information

- **Source:** [LeetCode #215](https://leetcode.com/problems/kth-largest-element-in-an-array/)
- **Difficulty:** Medium
- **Pattern Used:** Heap (Min-Heap / Top-K), Quickselect
- **Tags:** `array` `heap` `priority-queue` `quickselect` `divide-and-conquer`

---

## 📝 Problem (In Plain English)

Given an unsorted array of integers and a number `k`, return the element that sits at position `k` when the array is sorted in descending order. Duplicates count — this is not the kth *distinct* element.

---

## 📥 Input / 📤 Output

- **Input:** `int[] nums` (unsorted, may contain duplicates), `int k` (1-indexed rank)
- **Output:** A single integer — the kth largest element

---

## ⚠️ Constraints

- `1 <= k <= nums.length <= 10^5`
- `-10^4 <= nums[i] <= 10^4`

---

## 🔍 Example Walkthrough

### Example 1
```
Input:  nums = [3, 2, 1, 5, 6, 4], k = 2
Output: 5
```
Sorted descending → [6, 5, 4, 3, 2, 1]  
Position 1 = 6, Position 2 = **5** ✅

### Example 2
```
Input:  nums = [3, 2, 3, 1, 2, 4, 5, 5, 6], k = 4
Output: 4
```
Sorted descending → [6, 5, 5, 4, 3, 3, 2, 2, 1]  
Position 4 = **4** ✅

---

## 🧪 Edge Cases to Watch

- `k = 1` → just return the maximum
- `k = n` → just return the minimum
- All elements identical → any element is the answer
- Negative numbers → heap comparisons still work correctly
- Duplicates → they count as separate positions (not distinct)

---

## 🚀 Approaches — Progressive Complexity

### 🐢 Approach 1 — Sort and Index

**Idea:** Sort the array in descending order, return `nums[k-1]`.

**Why it's suboptimal:** You sort *everything* even though you only need position `k`. Wasteful when `k` is small relative to `n`.

| Complexity | Value |
|---|---|
| Time | O(n log n) |
| Space | O(1) in-place sort, O(n) if a copy is made |

**Doc Reference:** [Java Arrays.sort](https://docs.oracle.com/javase/8/docs/api/java/util/Arrays.html#sort-int:A-) | [Python list.sort](https://docs.python.org/3/library/stdtypes.html#list.sort)

---

### 🚶 Approach 2 — Min-Heap of Size K (Top-K Pattern)

**Idea:** Maintain a min-heap of exactly `k` elements as you scan the array. If a new element is larger than the heap's minimum (the root), evict the root and insert the new element. After processing all elements, the root is the kth largest.

**Key insight over Approach 1:** You never store more than `k` elements. The heap root is *always* the smallest of the k largest seen so far — which is exactly the kth largest by definition.

Think of it like this: you're running a "top-k leaderboard." The player at the bottom of the leaderboard (heap root) is always one eviction away. If a new player beats them, they're out.

| Complexity | Value |
|---|---|
| Time | O(n log k) |
| Space | O(k) |

**Doc Reference:** [Java PriorityQueue](https://docs.oracle.com/javase/8/docs/api/java/util/PriorityQueue.html) | [Python heapq](https://docs.python.org/3/library/heapq.html)

---

### 🚀 Approach 3 — Quickselect (Optimal Average Case)

**Idea:** A derivative of Quicksort. Pick a pivot, partition the array into elements greater than and less than the pivot. After partitioning, the pivot lands at its *sorted position*. If that position equals `k-1` (0-indexed from the right), you're done. Otherwise recurse only on the relevant half — you never touch the other side.

**Key insight:** Unlike Quicksort, you don't recurse both halves. You recurse *one* side — the side that contains rank `k`. On average you eliminate half the array each time: n + n/2 + n/4 + ... = O(2n) = **O(n)**.

**Why this is the ceiling:** Selection from an unsorted array has a proven lower bound of O(n) — you must read every element at least once. Quickselect matches this on average. The worst case is O(n²) with a bad pivot (e.g., already sorted input), which is why **randomizing the pivot** is critical in practice.

| Complexity | Value |
|---|---|
| Time | O(n) average, O(n²) worst case |
| Space | O(1) in-place, O(log n) stack for recursion |

**Doc Reference:** [Wikipedia — Quickselect](https://en.wikipedia.org/wiki/Quickselect) | [CLRS — Chapter 9: Medians and Order Statistics](https://en.wikipedia.org/wiki/Introduction_to_Algorithms)

---

## ✅ Chosen Approach

**For interviews: Min-Heap (Approach 2)** — clean, predictable O(n log k), no worst-case risk, and maps directly to the "Top-K" pattern that generalizes to dozens of other problems.

**For optimal theoretical performance: Quickselect (Approach 3)** — O(n) average. Use when `k` is large or you're processing streaming data.

### Step-by-step logic (Min-Heap):
1. Create an empty min-heap
2. For each number in `nums`:
   - Push it onto the heap
   - If heap size exceeds `k`, pop the minimum (evict the smallest)
3. After all elements processed, the heap root = kth largest

---

## 🧩 Pseudocode

```
function findKthLargest(nums, k):
    heap = new MinHeap()

    for num in nums:
        heap.push(num)
        if heap.size() > k:
            heap.pop()          // evict the smallest — it can't be kth largest

    return heap.peek()          // smallest of the k largest = kth largest
```

---

## 💻 Implementations

### ☕ Java

```java
import java.util.PriorityQueue;

class Solution {
    public int findKthLargest(int[] nums, int k) {
        // PriorityQueue is a min-heap by default in Java
        PriorityQueue<Integer> minHeap = new PriorityQueue<>();

        for (int num : nums) {
            minHeap.offer(num);          // push current element

            // Evict smallest if we exceed k — it can't be in top-k
            if (minHeap.size() > k) {
                minHeap.poll();
            }
        }

        // Root of the min-heap = smallest of the k largest = kth largest
        return minHeap.peek();
    }
}
```

**Java Docs:**
- [PriorityQueue](https://docs.oracle.com/javase/8/docs/api/java/util/PriorityQueue.html) — min-heap by default
- [PriorityQueue.offer / poll / peek](https://docs.oracle.com/javase/8/docs/api/java/util/PriorityQueue.html#offer-E-)

---

### 🟨 JavaScript

```js
// JS has no built-in heap — use a MinHeap class or a sorted structure
// Here we use a clean O(n log k) approach with a simulated min-heap via sorted array
// In real interviews, clarify if you can use a library (e.g., @datastructures-js/priority-queue)

var findKthLargest = function(nums, k) {
    // Min-heap simulated: keep a sorted array of size k
    // For production JS, use: https://github.com/datastructures-js/priority-queue
    let heap = [];

    const heapPush = (val) => {
        heap.push(val);
        heap.sort((a, b) => a - b);   // maintain min at index 0
    };

    for (let num of nums) {
        heapPush(num);
        if (heap.length > k) heap.shift(); // evict the minimum
    }

    return heap[0]; // smallest of the k largest = kth largest
};
```

> ⚠️ Note: `Array.sort` makes this O(n · k log k) — not optimal. In a real interview, implement a proper binary heap or use the `@datastructures-js/priority-queue` npm package for true O(n log k).

**JS Docs:**
- [MDN Array.prototype.sort](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Array/sort)
- [@datastructures-js/priority-queue](https://github.com/datastructures-js/priority-queue) — production-grade heap for JS

---

### 🐍 Python

```python
import heapq

class Solution:
    def findKthLargest(self, nums: list[int], k: int) -> int:
        min_heap = []

        for num in nums:
            heapq.heappush(min_heap, num)   # push to min-heap

            # If we have more than k elements, evict the smallest
            if len(min_heap) > k:
                heapq.heappop(min_heap)

        # Root = smallest of the k largest = kth largest
        return min_heap[0]
```

> 💡 Python also offers `heapq.nlargest(k, nums)` as a one-liner — but know it's O(n log k) under the hood and not appropriate if the interviewer wants you to implement the logic.

**Python Docs:**
- [heapq — Heap queue algorithm](https://docs.python.org/3/library/heapq.html)
- [heapq.nlargest](https://docs.python.org/3/library/heapq.html#heapq.nlargest)

---

## 📊 Complexity Summary

| Approach | Time | Space | Notes |
|---|---|---|---|
| Sort + Index | O(n log n) | O(1) | Simple but wasteful |
| Min-Heap (size k) | O(n log k) | O(k) | ✅ Recommended for interviews |
| Quickselect | O(n) avg / O(n²) worst | O(log n) | Best theoretical, risky without pivot randomization |

---

## 🧠 Mistakes & Traps

- **Confusing kth largest with kth smallest.** They're inverses. kth largest = `(n - k + 1)`th smallest. Sketch a small example before coding.
- **Forgetting duplicates count.** `[3,3,3]` with `k=2` → answer is `3`, not "no second distinct."
- **Quickselect worst case.** If the array is already sorted and you always pick the first element as pivot, every partition step removes only one element → O(n²). Always randomize the pivot.
- **Using a max-heap of size n.** You can find the answer by popping k times from a max-heap — but that's O(n + k log n), not better than the min-heap approach when k is small.
- **JS has no native heap.** Failing to mention this in an interview looks like a blind spot.

---

## 📚 What This Problem Teaches

- **The Top-K pattern** — one of the most reusable interview patterns. Anytime you see "find top k", "find k closest", "find k most frequent" → min-heap of size k.
- **Heap as a filter** — a min-heap of size k acts as a filter: it only keeps the k best elements seen so far, and the worst of those is always instantly accessible at the root.
- **Quickselect intuition** — the same partition logic from Quicksort, applied selectively. This is the foundation for median-of-medians and order statistics.

---

## 🔗 Related Problems

- [LeetCode #703 — Kth Largest Element in a Stream](https://leetcode.com/problems/kth-largest-element-in-a-stream/) — same heap pattern, but data arrives incrementally
- [LeetCode #347 — Top K Frequent Elements](https://leetcode.com/problems/top-k-frequent-elements/) — Top-K + frequency counting
- [LeetCode #973 — K Closest Points to Origin](https://leetcode.com/problems/k-closest-points-to-origin/) — Top-K with a custom comparator
- [LeetCode #295 — Find Median from Data Stream](https://leetcode.com/problems/find-median-from-data-stream/) — two-heap technique, direct extension

---

## 🎯 Comprehension Check

> The min-heap solution runs in O(n log k). If `k = n`, what does the complexity collapse to — and what does that tell you about when the heap approach stops being an improvement over just sorting?