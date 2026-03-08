# 🧠 Problem Solving Study Template

## 📌 Problem Information
- **Title:** Intersection of Two Arrays
- **Source:** LeetCode
- **Difficulty:** Easy
- **Date Solved:** 
- **Status:** Solved
- **link** https://leetcode.com/problems/intersection-of-two-arrays/description/

**Tags:**  
`array` `hash-table` `set` `two-pointers`

**Pattern Used:**  
Hash Set / Set Intersection

---

# 📝 Problem Statement

Given two integer arrays `nums1` and `nums2`, return an array of their **intersection**.

Rules:
- Each element in the result must be **unique**.
- The result can be returned **in any order**.  

The intersection of two arrays means the values that appear in **both arrays**.

---

# 📥 Inputs

- `nums1` → integer array
- `nums2` → integer array

Example:

nums1 = [1,2,2,1]
nums2 = [2,2]

---

# 📤 Output

Return an array containing **unique elements present in both arrays**.

Example output:

[2]

---

# ⚠️ Constraints

- `1 ≤ nums1.length, nums2.length ≤ 1000`
- `0 ≤ nums1[i], nums2[i] ≤ 1000`  [oai_citation:1‡leetcode.doocs.org](https://leetcode.doocs.org/en/lc/349/?utm_source=chatgpt.com)

---

# 🔍 Examples

## Example 1

Input

nums1 = [1,2,2,1]
nums2 = [2,2]

Output

[2]

Explanation  
The number `2` appears in both arrays. Even though it appears multiple times, the result must contain **unique values only**.  [oai_citation:2‡AlgoMonster](https://algo.monster/liteproblems/349?utm_source=chatgpt.com)

---

## Example 2

Input

nums1 = [4,9,5]
nums2 = [9,4,9,8,4]

Output

[9,4]

Explanation  
Both `4` and `9` appear in both arrays.

---

# 💡 Initial Thoughts

Observations:

- We only care about **unique elements**.
- Order **does not matter**.
- Fast lookup would help.

Ideas:
- Brute force comparison
- Use a **hash set**
- Convert both arrays to sets and find intersection

---

# 🧪 Edge Cases

- No common elements → return `[]`
- All elements same
- One array much larger than the other
- Arrays contain duplicates
- Arrays with only one element

---

# 🚀 Possible Approaches

## Approach 1 — Brute Force

Idea  
Compare each element in `nums1` with each element in `nums2`.

Pseudo idea:

for num1 in nums1:
for num2 in nums2:
if num1 == num2

Time Complexity

O(n * m)

Space Complexity

O(1)

Problem:
- Slow for large arrays.

---

## Approach 2 — Hash Set (Optimal)

Idea  

1. Convert `nums1` into a set.
2. Iterate through `nums2`.
3. If element exists in set → add to result set.
4. Convert result set to list.

Sets automatically remove duplicates and provide **O(1)** lookup.  [oai_citation:3‡leetcodee.com](https://leetcodee.com/problems/intersection-of-two-arrays/?utm_source=chatgpt.com)

Time Complexity

O(n + m)

Space Complexity

O(min(n, m))

---

# ✅ Chosen Approach

Use **set intersection**.

Reason:
- Automatically removes duplicates
- Constant lookup time
- Very concise solution

Steps:

1. Convert both arrays into sets.
2. Compute intersection using set operation.
3. Convert result to list.

---

# 🧩 Algorithm (Pseudo Code)

convert nums1 to set1
convert nums2 to set2

result = set1 ∩ set2

return list(result)

---

# 💻 Implementation

## Python

```python
class Solution:
    def intersection(self, nums1, nums2):
        set1 = set(nums1)
        set2 = set(nums2)

        return list(set1 & set2)


⸻

C++

class Solution {
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {

        unordered_set<int> set1(nums1.begin(), nums1.end());
        unordered_set<int> result;

        for(int num : nums2){
            if(set1.count(num)){
                result.insert(num);
            }
        }

        return vector<int>(result.begin(), result.end());
    }
};


⸻

📊 Complexity Analysis

Time Complexity

O(n + m)

Where:
	•	n = length of nums1
	•	m = length of nums2

⸻

Space Complexity

O(min(n, m))

Extra space used by the hash set.

⸻

🧠 Mistakes / Debug Notes

Common mistakes:
	•	Returning duplicates
	•	Forgetting to convert result to list
	•	Using list instead of set → slower lookup

⸻

📚 What I Learned
	•	Using hash sets for fast lookup
	•	Set operations (intersection)
	•	Removing duplicates automatically

⸻

🔗 Related Problems
	•	Intersection of Two Arrays II
	•	Two Sum
	•	Contains Duplicate
	•	Find the Difference of Two Arrays

⸻

🔁 Review Notes

Questions to revisit later:
	•	Can this be solved with two pointers + sorting?
	•	When should I use set vs hashmap?
	•	What if duplicates were allowed in output?

---

If you want, I can also show you **how experienced LeetCode users write these notes faster (a 30-second MD template)** so you can document **100+ problems without spending too much time writing notes.**