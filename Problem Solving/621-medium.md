# 🧠 Problem Solve — Task Scheduler

## 📌 Problem Information

- **Source:** [LeetCode 621 — Task Scheduler](https://leetcode.com/problems/task-scheduler/description/)
- **Difficulty:** Medium
- **Pattern Used:** Greedy + Frequency Counting
- **Tags:** `greedy` `array` `hash-map` `math` `sorting`

---

## 📝 Problem (In Plain English)

You have a list of CPU tasks labeled A–Z. Each task takes one interval to complete. The constraint: the same task cannot run again until at least `n` intervals have passed since it last ran. You can run tasks in any order, and insert idle intervals when nothing is available. Find the minimum total intervals to finish all tasks.

---

## 📥 Input / 📤 Output

- **Input:** `tasks` — array of characters (A–Z), `n` — integer cooldown period
- **Output:** Integer — minimum number of CPU intervals to complete all tasks

---

## ⚠️ Constraints

- `1 ≤ tasks.length ≤ 10⁴`
- `0 ≤ n ≤ 100`
- Tasks are uppercase English letters `A–Z` (at most 26 distinct tasks)

---

## 🔍 Example Walkthrough

### Example 1
```
Input:  tasks = ["A","A","A","B","B","B"], n = 2
Output: 8
```

Step by step:
```
Interval:  1    2    3    4    5    6    7    8
Task:      A  → B  → idle → A  → B  → idle → A  → B
```
- A runs at 1. Can't run again until interval 4 (gap of 2).
- B runs at 2. Can't run again until interval 5.
- Interval 3: neither A nor B is available → idle.
- Pattern repeats. Total = 8.

### Example 2
```
Input:  tasks = ["A","C","A","B","D","B"], n = 1
Output: 6
```
```
A → C → A → B → D → B
```
With `n=1`, only one interval gap needed — other tasks fill it naturally. No idle time. Total = 6 = tasks.length.

---

## 🧪 Edge Cases to Watch

- `n = 0` → no cooldown, answer is always `tasks.length`
- All tasks are the same letter → maximum idle time forced
- Multiple tasks tied for max frequency → `numTasksWithMaxFreq > 1`
- Many diverse tasks → formula result < `tasks.length`, use `tasks.length`
- Single task → `(1-1)*(n+1) + 1 = 1` ✅

---

## 🚀 Approaches — Progressive Complexity

### 🐢 Approach 1 — Simulation with Priority Queue

**Idea:** At each interval, greedily pick the available task with the highest remaining frequency using a max-heap. Track cooldowns with a queue of `[frequency, availableAtTime]`. Advance a timer and release tasks back to the heap once their cooldown expires.

**Why it's suboptimal:** Simulates every single interval. Heap operations add log factor. More complex to implement correctly.

| Complexity | Value |
|---|---|
| Time | O(n log k) where k ≤ 26 |
| Space | O(k) |

**Doc Reference:** [MDN — Priority Queue concept via sorting](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Array/sort) | [Java PriorityQueue](https://docs.oracle.com/en/java/docs/api/java.base/java/util/PriorityQueue.html)

---

### 🚀 Approach 2 — Greedy Math (Optimal)

**Idea:** The most frequent task dictates the skeleton of the schedule. It creates `(maxFreq - 1)` "chunks", each of size `(n + 1)`. The final chunk only contains the tasks tied at max frequency. If other tasks overflow the idle slots completely, the answer is just `tasks.length`.

**Key insight:** You don't need to simulate anything. The minimum time is a direct mathematical consequence of the frequency distribution.

| Complexity | Value |
|---|---|
| Time | O(n) — one pass to build freq map, one pass to find max |
| Space | O(1) — at most 26 keys in the map |

**Doc Reference:** [Greedy Algorithms — GeeksForGeeks](https://www.geeksforgeeks.org/greedy-algorithms/)

---

## ✅ Chosen Approach

**Greedy Math** — optimal time and space, and directly models the reasoning:

Step-by-step logic:
1. Count frequency of each task into a map
2. Find `maxFreq` (highest frequency) and `numTasksWithMaxFreq` (how many tasks share it)
3. Compute `formula = (maxFreq - 1) * (n + 1) + numTasksWithMaxFreq`
4. Return `max(formula, tasks.length)`

**Why the max?** The formula computes the minimum time assuming idle slots exist. But if enough diverse tasks exist to fill every slot, no idling is needed and the answer collapses to just the total task count.

---

## 🧩 Pseudocode

```
1. Build frequency map: task → count
2. Find maxFreq = max value in map
3. Find numMax = count of entries with value == maxFreq
4. formula = (maxFreq - 1) * (n + 1) + numMax
5. return max(formula, tasks.length)
```

---

## 💻 Implementations

### ☕ Java

```java
public int leastInterval(char[] tasks, int n) {
    int[] freq = new int[26]; // fixed-size array since tasks are A-Z only
    for (char t : tasks) freq[t - 'A']++;

    int maxFreq = 0;
    for (int f : freq) maxFreq = Math.max(maxFreq, f);

    // count how many tasks share the maximum frequency
    int numMax = 0;
    for (int f : freq) if (f == maxFreq) numMax++;

    // the frame formula vs total tasks — take the larger
    int formula = (maxFreq - 1) * (n + 1) + numMax;
    return Math.max(formula, tasks.length);
}
```

**Java Docs:**
- [Arrays — Oracle](https://docs.oracle.com/en/java/docs/api/java.base/java/util/Arrays.html)
- [Math.max — Oracle](https://docs.oracle.com/en/java/docs/api/java.base/java/lang/Math.html#max(int,int))

---

### 🟨 JavaScript

```js
var leastInterval = function(tasks, n) {
    const freq = new Map();
    for (const t of tasks) freq.set(t, (freq.get(t) || 0) + 1);

    let maxFreq = 0;
    for (const v of freq.values()) maxFreq = Math.max(maxFreq, v);

    // count tasks tied at max frequency — they all land in the final chunk
    let numMax = 0;
    for (const v of freq.values()) if (v === maxFreq) numMax++;

    // frame formula: (maxFreq-1) full chunks of size (n+1), plus the final chunk
    const formula = (maxFreq - 1) * (n + 1) + numMax;
    return Math.max(formula, tasks.length);
};
```

**JS Docs:**
- [MDN — Map](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Map)
- [MDN — Math.max](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Math/max)

---

### 🐍 Python

```python
def leastInterval(tasks: list[str], n: int) -> int:
    from collections import Counter

    freq = Counter(tasks)        # O(n) frequency count
    max_freq = max(freq.values())

    # how many tasks appear max_freq times
    num_max = sum(1 for v in freq.values() if v == max_freq)

    # frame formula vs raw task count
    formula = (max_freq - 1) * (n + 1) + num_max
    return max(formula, len(tasks))
```

**Python Docs:**
- [collections.Counter — Python](https://docs.python.org/3/library/collections.html#collections.Counter)
- [Built-in max — Python](https://docs.python.org/3/library/functions.html#max)

---

## 📊 Complexity Summary

| Approach | Time | Space | Notes |
|---|---|---|---|
| Simulation (Heap) | O(n log k) | O(k) | k ≤ 26 |
| Greedy Math | O(n) | O(1) | ✅ Recommended |

---

## 🧠 Mistakes & Traps

- **Forgetting the `+numMax` at the end** — the last chunk isn't empty, it holds all tasks tied at max frequency
- **Using just `tasks.length` as the answer** — ignores idle time entirely
- **Using just the formula** — breaks when tasks are so diverse that idle slots disappear completely
- **Writing `(maxFreq-1)*n` instead of `(maxFreq-1)*(n+1)`** — forgets to count the task slot itself inside each chunk, not just the cooldown gap

---

## 📚 What This Problem Teaches

- **Greedy scheduling via dominant constraint:** The bottleneck (most frequent task) determines the shape of the entire solution. Fill around it, not the other way.
- **Math over simulation:** When a greedy insight reduces the problem to a formula, simulation becomes unnecessary overhead.
- **Generalizes to:** Rate limiting systems, OS round-robin scheduling, API throttling, reorganize string problems.
- **How to recognize it:** Any problem with "cooldown between identical elements" + "minimize total time/length" is a Task Scheduler variant.

---

## 🔗 Related Problems

- [LeetCode 767 — Reorganize String](https://leetcode.com/problems/reorganize-string/) — Task Scheduler where `n=1` and you must produce the actual string, not just the length
- [LeetCode 2365 — Task Scheduler II](https://leetcode.com/problems/task-scheduler-ii/) — Tasks must be completed in given order (not freely reorderable)
- [LeetCode 358 — Rearrange String k Distance Apart](https://leetcode.com/problems/rearrange-string-k-distance-apart/) — Same core problem, framed as string rearrangement

---

## 🎯 Comprehension Check

> The formula uses `(maxFreq - 1) * (n + 1) + numMax`. If you increase `n` by 1, the formula value increases by `(maxFreq - 1)`. But increasing `n` by 1 when tasks are already filling all idle slots produces **no change** in the answer. Why?