# 🧠 Problem Solve — Queue Reconstruction by Height

## 📌 Problem Information

- **Source:** [LeetCode 406](https://leetcode.com/problems/queue-reconstruction-by-height/)
- **Difficulty:** Medium
- **Pattern Used:** Greedy + Sort
- **Tags:** `greedy` `sorting` `array`

---

## 📝 Problem (In Plain English)

You're given a scrambled list of people, each described as `[h, k]` — their height and the count of people who should stand in front of them in the final queue who are at least as tall. Reconstruct the queue so every person's `k` constraint is satisfied.

---

## 📥 Input / 📤 Output

- **Input:** `people[][]` — an unordered array of `[height, k]` pairs
- **Output:** The reconstructed queue as a 2D array where every person's position satisfies their `k` value

---

## ⚠️ Constraints

- `1 ≤ people.length ≤ 2000`
- `0 ≤ hi ≤ 10^6`
- `0 ≤ ki < people.length`
- A valid reconstruction is always guaranteed

---

## 🔍 Example Walkthrough

### Example
```
Input:  [[7,0],[4,4],[7,1],[5,0],[6,1],[5,2]]
Output: [[5,0],[7,0],[5,2],[6,1],[4,4],[7,1]]
```

Verify each person in the output:

| Index | Person | Who's in front & ≥ h | k satisfied? |
|-------|--------|----------------------|--------------|
| 0 | [5,0] | nobody | k=0 ✅ |
| 1 | [7,0] | [5,0] — but 5 < 7, doesn't count | k=0 ✅ |
| 2 | [5,2] | [5,0] and [7,0] both ≥ 5 | k=2 ✅ |
| 3 | [6,1] | only [7,0] ≥ 6 | k=1 ✅ |
| 4 | [4,4] | [5,0],[7,0],[5,2],[6,1] all ≥ 4 | k=4 ✅ |
| 5 | [7,1] | [7,0] is ≥ 7 | k=1 ✅ |

---

## 🧪 Edge Cases to Watch

- Single person → trivially correct, return as-is
- All same height → sort only by `k` ascending; insertion index = `k`
- `k=0` for multiple people → they all go as early as possible
- Ties in height → wrong tiebreak order breaks the entire reconstruction
- Large `k` values → person belongs near the end; must have enough people already placed

---

## 🚀 Approaches — Progressive Complexity

---

### 🐢 Approach 1 — Brute Force (Try All Permutations)

**Idea:** Generate every possible permutation of the input array, then validate each one until you find an arrangement that satisfies all `k` constraints.

**Why it's suboptimal:** `n!` permutations — with `n=2000`, this is astronomically large and completely infeasible.

| Complexity | Value |
|---|---|
| Time | O(n! × n) |
| Space | O(n) |

**Doc Reference:** [Permutation generation — Wikipedia](https://en.wikipedia.org/wiki/Permutation#Generation_in_lexicographic_order)

---

### 🚶 Approach 2 — Sort Shortest First + Scan (Your Instinct)

**Idea:** Sort ascending by height. For each person, scan the result array counting empty or shorter slots until you've exhausted `k`, then insert there.

**Why it breaks down:** When you insert a shorter person, they can shift taller people already placed, invalidating `k` values that were already correct. You're constantly fighting the positions of previously placed people. This is the core flaw in your pseudocode — the mutation of the array mid-loop corrupts earlier placements.

| Complexity | Value |
|---|---|
| Time | O(n²) |
| Space | O(n) |

**Doc Reference:** [Array insertion complexity — MDN Array.splice](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Array/splice)

---

### 🚀 Approach 3 — Optimal: Sort Tallest First + Insert at Index k

**Idea:** Sort descending by height (ties broken by `k` ascending). Then insert each person directly at index `k` into a result list.

**The core insight:** If you process tallest people first, every person already in the result list when you insert the next person is **at least as tall**. So inserting at index `k` is always correct — there are exactly `k` people in front, and all of them are ≥ current height. Shorter people inserted later cannot violate this, because they are invisible to taller people's `k` constraint.

**Why ties break ascending on k:** Among people of equal height, the one with smaller `k` must come first. If `[7,1]` were inserted before `[7,0]`, placing `[7,0]` at index 0 afterward would push `[7,1]` to index 2, making its actual count wrong.

| Complexity | Value |
|---|---|
| Time | O(n² ) — insertion into list is O(n) per element |
| Space | O(n) |

**Doc Reference:**
- [Java LinkedList.add(index, element)](https://docs.oracle.com/en/java/se/17/docs/api/java.base/java/util/LinkedList.html#add(int,E))
- [Python list.insert](https://docs.python.org/3/tutorial/datastructures.html#more-on-lists)
- [MDN Array.splice](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Array/splice)

---

## ✅ Chosen Approach — Sort Tallest First, Insert at k

**Why:** The greedy insight is airtight. Tallest-first guarantees that every insertion sees only people who count toward the constraint. The O(n²) cost is unavoidable for list-based insertion but well within the n=2000 constraint.

**Step-by-step logic:**

1. Sort `people` descending by `h`. For equal `h`, sort ascending by `k`.
2. Initialize an empty result list.
3. For each person `[h, k]` in the sorted order:
   - Insert them at index `k` in the result list.
   - Everyone already in the list is ≥ current height, so there are exactly `k` people in front.
4. Return the result list.

---

## 🧩 Pseudocode

```
sort people by: height DESC, then k ASC (for ties)

result = []

for each person [h, k] in sorted people:
    result.insert(at index k, person)

return result
```

---

## 💻 Implementations

### ☕ Java

```java
import java.util.Arrays;
import java.util.LinkedList;
import java.util.List;

class Solution {
    public int[][] reconstructQueue(int[][] people) {
        // Sort: tallest first; ties broken by k ascending
        Arrays.sort(people, (a, b) ->
            a[0] == b[0] ? a[1] - b[1] : b[0] - a[0]
        );

        // LinkedList gives O(1) node re-linking; index traversal is still O(n)
        List<int[]> result = new LinkedList<>();

        for (int[] person : people) {
            // k is the exact index where this person belongs
            // everyone already in result is >= current height
            result.add(person[1], person);
        }

        return result.toArray(new int[people.length][2]);
    }
}
```

**Java Docs:**
- [Arrays.sort with Comparator](https://docs.oracle.com/en/java/se/17/docs/api/java.base/java/util/Arrays.html#sort(T%5B%5D,java.util.Comparator))
- [LinkedList.add(int index, E element)](https://docs.oracle.com/en/java/se/17/docs/api/java.base/java/util/LinkedList.html#add(int,E))

---

### 🟨 JavaScript

```js
var reconstructQueue = function(people) {
    // Sort: height descending, k ascending for ties
    people.sort((a, b) => a[0] !== b[0] ? b[0] - a[0] : a[1] - b[1]);

    const result = [];

    for (const person of people) {
        // splice(index, 0, item) inserts without removing anything
        // person[1] is k — the exact position this person belongs
        result.splice(person[1], 0, person);
    }

    return result;
};
```

**JS Docs:**
- [Array.prototype.sort — MDN](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Array/sort)
- [Array.prototype.splice — MDN](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Array/splice)

---

### 🐍 Python

```python
from typing import List

class Solution:
    def reconstructQueue(self, people: List[List[int]]) -> List[List[int]]:
        # Sort: height desc (-x[0] flips order), k asc for ties (x[1])
        people.sort(key=lambda x: (-x[0], x[1]))

        result = []

        for person in people:
            # list.insert(i, x) places x at index i, shifting everything right
            # person[1] is k — valid because all existing entries are >= current height
            result.insert(person[1], person)

        return result
```

**Python Docs:**
- [list.sort with key](https://docs.python.org/3/howto/sorting.html#key-functions)
- [list.insert](https://docs.python.org/3/tutorial/datastructures.html#more-on-lists)

---

## 📊 Complexity Summary

| Approach | Time | Space | Notes |
|---|---|---|---|
| Brute Force | O(n! × n) | O(n) | Completely infeasible |
| Sort Shortest First | O(n²) | O(n) | Corrupts placements on mutation |
| Sort Tallest First + Insert at k | O(n²) | O(n) | ✅ Recommended — greedy insight is clean and correct |

---

## 🧠 Mistakes & Traps

- **Sorting ascending instead of descending:** Processing shorter people first means taller people placed later will violate already-placed constraints — the entire greedy argument falls apart.
- **Wrong tiebreak direction:** For equal heights, sorting `k` descending instead of ascending causes same-height people to land at wrong indices.
- **Mutating the input array mid-loop (your approach):** Shifting elements in-place while iterating invalidates index references and corrupts previously correct placements — the root flaw in the pseudocode you designed.
- **Off-by-one on insertion index:** `k` is zero-indexed in the result. Inserting at `k+1` would give one too many people in front.

---

## 📚 What This Problem Teaches

- **Greedy ordering unlocks simplicity:** The right sort order can reduce a complex constraint-satisfaction problem to a single linear pass with trivial insertions. This is the greedy pattern — make locally optimal choices that are globally safe.
- **Process the most constrained elements first:** Tallest people have the fewest valid positions. Locking them in first gives shorter people a stable, immutable frame to insert into.
- **Generalizes to:** Any problem where you have two variables, one of which you can "freeze" by ordering, and the other becomes the direct answer once ordering is fixed.

---

## 🔗 Related Problems

- [LeetCode 354 — Russian Doll Envelopes](https://leetcode.com/problems/russian-doll-envelopes/) — same "sort one dimension, operate on the other" greedy structure, but requires patience sort / LIS for optimal
- [LeetCode 1353 — Maximum Number of Events That Can Be Attended](https://leetcode.com/problems/maximum-number-of-events-that-can-be-attended/) — greedy scheduling with ordering
- [LeetCode 179 — Largest Number](https://leetcode.com/problems/largest-number/) — custom comparator greedy sort

---

## 🎯 Comprehension Check

> You process `[5,2]` and insert it at index 2. At that moment, the result list contains `[[7,0],[7,1],[6,1]]`. After insertion, it becomes `[[7,0],[7,1],[5,2],[6,1]]`.
>
> **Now `[4,4]` is next. Why is it still safe to insert `[4,4]` at index 4 — even though shorter people like `[5,2]` are already in the list and will be in front of `[4,4]`?**



Great question — this is about building **problem-solving instincts**, not just recognizing answers.

Let me walk you through the exact reasoning chain.

---

### Step 1 — Identify What Makes This Hard

You have two variables per person: `h` and `k`. Both need to be satisfied simultaneously. Trying to place everyone correctly at once is what makes it feel impossible.

**The instinct:** Can I freeze one variable and solve only for the other?

---

### Step 2 — Ask Which Variable Is "Safer" to Fix First

Look at `k`. It says *"count the people in front of me who are ≥ h"*. That count **depends on who else is placed** — it's relative. You can't lock it in until the people around you are settled.

Look at `h`. It's absolute. It doesn't change based on placement.

**Conclusion:** Fix height order first. Let `k` sort itself out after.

---

### Step 3 — Ask What "Fixing Height" Buys You

If you process **tallest first**, ask yourself:

> When I'm placing person X, does anyone not yet placed affect X's `k`?

Shorter people haven't been inserted yet. And shorter people **don't count** toward X's `k` — because `k` only counts people ≥ `h`.

**Conclusion:** Shorter people, wherever they end up, are invisible to X's constraint. So you can place X now, permanently, without worrying about future insertions.

---

### Step 4 — Now Ask What `k` Becomes

You're inserting into a list where **everyone already there is ≥ current height**. The list has, say, 5 people. You need exactly `k` people in front.

There's only one thing to do — **put this person at position `k`**. Not scan for it. Not count toward it. Just place directly at index `k`.

**Conclusion:** `k` stops being a constraint to satisfy and becomes a direct coordinate.

---

### The Reasoning Chain in One Flow

```
Two variables → freeze the absolute one (h) first
         ↓
Sort descending by h → tallest processed first
         ↓
At each insertion, everyone in result is ≥ current h
         ↓
Shorter people not yet inserted → invisible to current k
         ↓
k = exact insertion index, always
```

---

### The Meta-Skill Here

Whenever you see a problem with **two coupled constraints**, ask:

> If I sort by one, does the other become trivial?

That single question is what cracks this problem — and a whole family of greedy problems like it.

