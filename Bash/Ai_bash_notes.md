# 🐚 Bash Scripting — Study Notes

---

## Table of Contents

1. [Script Basics](#1-script-basics)
2. [Quotes — Single, Double, and Backticks](#2-quotes--single-double-and-backticks)
3. [Variables](#3-variables)
4. [Brackets Deep Dive](#4-brackets-deep-dive)
5. [Conditionals — `if` / `case`](#5-conditionals--if--case)
6. [Loops — `for` / `while` / `until` / `select`](#6-loops--for--while--until--select)
7. [Functions](#7-functions)
8. [Arrays](#8-arrays)
9. [Special Variables](#9-special-variables)
10. [sed & awk Quick Reference](#10-sed--awk-quick-reference)

---

## 1. Script Basics

```bash
#!/bin/bash          # Shebang — always the first line
# This is a comment

echo "Hello, World!" # Print to stdout
```

**Running a script:**
```bash
chmod +x myscript.sh   # Make executable
./myscript.sh          # Run it
bash myscript.sh       # Or run with bash directly
```

**Sourcing a script** (runs in current shell — shares variables):
```bash
source script.sh
. script.sh            # Same thing, shorthand
```

> 💡 `source` vs `./`: If script A sets `x=5`, calling `./B.sh` from A means B runs in a **child** shell and can't see `x`. To share it, use `export x=5` in A, or source B.

---

## 2. Quotes — Single, Double, and Backticks

This is one of the most important topics in bash. Getting quotes wrong causes subtle bugs.

### 2.1 Single Quotes `' '`

- **Everything is literal.** No variable expansion, no special characters.
- You **cannot** put a single quote inside single quotes.

```bash
name="Ahmed"
echo 'Hello $name'     # Output: Hello $name   ← literal, no expansion
echo 'It'\''s done'    # Trick to include a single quote: end, escape, reopen
```

### 2.2 Double Quotes `" "`

- **Variables expand.** Most special characters are interpreted.
- `$`, `` ` ``, `\`, and `!` are still special inside double quotes.
- Preserves **spaces and newlines** in values — critical for filenames with spaces.

```bash
name="Ahmed"
echo "Hello $name"         # Output: Hello Ahmed
echo "Today is $(date)"    # Output: Today is Tue Mar ...
echo "Price: \$5"          # Output: Price: $5  ← escaped dollar
```

**Why double-quote variables?**
```bash
file="my file.txt"
rm $file          # ❌ BAD  — shell sees: rm my file.txt (two arguments!)
rm "$file"        # ✅ GOOD — shell sees: rm "my file.txt" (one argument)
```

### 2.3 Backticks `` ` ` `` vs `$( )`

Both do **command substitution** — they run a command and use its output.

```bash
today=`date`           # Old style (backticks)
today=$(date)          # Modern style — preferred

echo "Logged in users: $(who | wc -l)"
```

**Prefer `$()` because:**
- Easier to read
- Can be nested: `$(outer $(inner))`
- No confusion with single quotes

### 2.4 Quote Comparison Table

| Syntax | Variable Expansion | Command Substitution | Spaces Preserved |
|--------|--------------------|----------------------|-----------------|
| `'...'` | ❌ No | ❌ No | ✅ Yes |
| `"..."` | ✅ Yes | ✅ Yes | ✅ Yes |
| No quotes | ✅ Yes | ✅ Yes | ❌ No (word split) |

### 2.5 When to Use Which

```bash
# Use single quotes for: regex patterns, literal strings, awk programs
grep 'lp' /etc/passwd
awk -F: '{print $1}' /etc/passwd

# Use double quotes for: any variable, paths, strings with spaces
echo "Hello $USER"
cp "$source" "$dest"

# Use no quotes only for: simple integers, controlled values
count=5
if [ $count -gt 3 ]; then ...
```

---

## 3. Variables

### 3.1 Assignment

```bash
name="Ahmed"        # No spaces around =
age=25
readonly PI=3.14    # Constant, cannot be changed
```

> ⚠️ `name = "Ahmed"` is **wrong** — bash treats `name` as a command!

### 3.2 Reading Variables

```bash
echo $name          # Simple expansion
echo ${name}        # Explicit — needed when followed by more text
echo ${name}Script  # Output: AhmedScript (not $nameScript which is empty)
```

### 3.3 typeset / declare

```bash
typeset -i n1       # Declare integer (ksh style, seen in labs)
declare -i n2       # Bash equivalent
declare -r PI=3.14  # Read-only
declare -a arr      # Array
declare -x VAR      # Export (same as export VAR)
```

### 3.4 Environment Variables & export

```bash
# Variables are LOCAL to current shell by default
x=5
bash             # new child shell
echo $x          # Empty! x not visible

# export makes it available to child shells
export x=5
bash
echo $x          # 5 ✓
```

### 3.5 User Input — `read`

```bash
echo "Enter your name:"
read username
echo "Hello, $username"

read -p "Enter name: " username   # Prompt inline
read -s password                  # Silent (no echo — for passwords)
```

---

## 4. Brackets Deep Dive

Brackets are the most confusing part of bash. Here's a clear breakdown.

### 4.1 `[ ]` — Single Brackets (test command)

- This is the **original POSIX `test` command**. Works in all shells.
- **Spaces inside are mandatory:** `[ -f file ]` ✅ — `[-f file]` ❌
- Use `-eq`, `-lt`, `-gt` for numbers. Use `=`, `!=` for strings.

```bash
# File tests
[ -f "$file" ]        # Is it a regular file?
[ -d "$dir" ]         # Is it a directory?
[ -r "$file" ]        # Is it readable?
[ -w "$file" ]        # Is it writable?
[ -x "$file" ]        # Is it executable?
[ -e "$file" ]        # Does it exist?
[ -s "$file" ]        # Is it non-empty?

# String tests
[ -z "$str" ]         # Is string empty?
[ -n "$str" ]         # Is string non-empty?
[ "$a" = "$b" ]       # String equality (use = not ==)
[ "$a" != "$b" ]      # String inequality

# Numeric tests
[ $n -eq 5 ]          # Equal
[ $n -ne 5 ]          # Not equal
[ $n -lt 10 ]         # Less than
[ $n -le 10 ]         # Less than or equal
[ $n -gt 0 ]          # Greater than
[ $n -ge 0 ]          # Greater than or equal

# Combining conditions
[ -f "$f" ] && [ -r "$f" ]    # AND (outside brackets)
[ -f "$f" ] || [ -d "$f" ]    # OR (outside brackets)
[ ! -f "$f" ]                 # NOT
```

### 4.2 `[[ ]]` — Double Brackets (bash built-in)

- **Bash-specific** (not POSIX). More powerful and safer.
- No word splitting, so quoting `$var` is optional (but still good practice).
- Supports `&&`, `||` **inside** the brackets.
- Supports `=~` for regex matching and `==` with glob patterns.

```bash
[[ -f "$file" && -r "$file" ]]     # AND inside brackets
[[ $str == Hello* ]]               # Glob pattern match
[[ $str =~ ^[0-9]+$ ]]            # Regex match (no quotes around regex!)
[[ $a == $b ]]                     # == works for strings (unlike [ ])
```

**`[ ]` vs `[[ ]]` — When to use which:**

| Feature | `[ ]` | `[[ ]]` |
|---------|-------|---------|
| Portable (POSIX) | ✅ | ❌ Bash only |
| `&&` / `||` inside | ❌ | ✅ |
| Regex `=~` | ❌ | ✅ |
| Glob `==` patterns | ❌ | ✅ |
| Safer with empty vars | ❌ | ✅ |

> 💡 **Rule of thumb:** Use `[[ ]]` in bash scripts. Use `[ ]` for portability.

### 4.3 `( )` — Subshell

Runs commands in a **child process**. Changes (like `cd` or variable changes) do **not** affect the parent.

```bash
(cd /tmp && ls)         # cd only affects the subshell
echo $PWD               # Still original directory

(x=100; echo $x)        # x=100 inside
echo $x                 # Empty outside
```

Also used for **command grouping** and **command substitution:**
```bash
result=$(ls -l | wc -l)    # Command substitution
```

### 4.4 `(( ))` — Arithmetic Evaluation

Used for **integer arithmetic**. No `$` needed on variables inside (though it works).
Returns exit code 0 if result is non-zero, 1 if zero (useful in conditions).

```bash
(( 3 + 5 ))             # Evaluates, result = 8
(( x = 5 + 3 ))         # Assigns x=8
(( x++ ))               # Increment
(( x-- ))               # Decrement
(( x *= 2 ))            # Multiply and assign

# In conditions:
if (( x > 5 )); then echo "big"; fi
while (( count < 10 )); do (( count++ )); done

# Arithmetic expansion — get the value:
result=$(( 10 * 3 ))     # result=30
echo $(( 2 ** 8 ))       # 256  (power)
```

**`$(( ))` vs `(( ))`:**
```bash
x=$(( 5 + 3 ))    # Expansion: captures value into x
(( x = 5 + 3 ))   # Evaluation: assigns directly, no $
```

### 4.5 `{ }` — Command Grouping (current shell)

Groups commands in **current shell** (unlike `( )` which uses a subshell).
```bash
{ echo "start"; ls; echo "end"; }    # Note: space after { and ; before }
```

Also used for **brace expansion:**
```bash
echo {a,b,c}           # a b c
echo file{1,2,3}.txt   # file1.txt file2.txt file3.txt
mkdir -p project/{src,bin,lib}
```

### 4.6 Summary Table

| Syntax | Purpose | Shell |
|--------|---------|-------|
| `[ ]` | Test / condition (POSIX) | All |
| `[[ ]]` | Test / condition (extended) | Bash |
| `( )` | Subshell / command grouping | All |
| `$( )` | Command substitution | All |
| `(( ))` | Arithmetic evaluation | Bash |
| `$(( ))` | Arithmetic expansion | Bash |
| `{ }` | Command grouping (current shell) | All |

---

## 5. Conditionals — `if` / `case`

### 5.1 if / elif / else

```bash
if [ condition ]; then
    # commands
elif [ other_condition ]; then
    # commands
else
    # commands
fi
```

**Real example — checking file type and permissions:**
```bash
#!/bin/bash
# mytest script from Lab 2

arg="$1"

if [ -f "$arg" ]; then
    echo "$arg is a regular file"
elif [ -d "$arg" ]; then
    echo "$arg is a directory"
else
    echo "$arg is something else"
fi

# Check permissions
[ -r "$arg" ] && echo "Readable"
[ -w "$arg" ] && echo "Writable"
[ -x "$arg" ] && echo "Executable"
```

### 5.2 case

Cleaner alternative to multiple `if/elif` blocks. Great for menus and character checking.

```bash
case "$variable" in
    pattern1)
        commands ;;
    pattern2 | pattern3)    # Multiple patterns with |
        commands ;;
    *)                      # Default (like else)
        commands ;;
esac
```

**Example — mycase (Lab 3): Check character type:**
```bash
#!/bin/bash
read -p "Enter a character: " char

case "$char" in
    [A-Z])  echo "Upper Case" ;;
    [a-z])  echo "Lower Case" ;;
    [0-9])  echo "Number"     ;;
    "")     echo "Nothing"    ;;
    *)      echo "Special character" ;;
esac
```

**Example — Menu (Lab 3):**
```bash
#!/bin/bash
while true; do
    echo "1) ls"
    echo "2) ls -a"
    echo "3) exit"
    read -p "Choice: " choice

    case "$choice" in
        1) ls ;;
        2) ls -a ;;
        3) exit 0 ;;
        *) echo "Invalid option" ;;
    esac
done
```

---

## 6. Loops — `for` / `while` / `until` / `select`

### 6.1 for loop

```bash
# Classic: iterate over a list
for item in one two three; do
    echo "$item"
done

# Iterate over files
for file in /home/$USER/*; do
    echo "$file"
done

# C-style for loop (bash)
for (( i=0; i<5; i++ )); do
    echo "$i"
done

# Loop over command output
for user in $(awk -F: '{print $1}' /etc/passwd); do
    echo "$user"
done
```

**Example — mychmod (Lab 3): Give execute permission to all files:**
```bash
#!/bin/bash
for item in ~/*; do
    chmod +x "$item"
done
```

**Example — mybackup (Lab 3): Backup only files:**
```bash
#!/bin/bash
backup_dir="/tmp/backup_$(date +%Y%m%d)"
mkdir -p "$backup_dir"

for file in ~/*; do
    if [ -f "$file" ]; then
        cp "$file" "$backup_dir/"
    fi
done
echo "Backup done in $backup_dir"
```

### 6.2 while loop

Runs **while** condition is **true**.

```bash
while [ condition ]; do
    commands
done
```

```bash
# Count down
n=5
while [ $n -gt 0 ]; do
    echo "$n"
    (( n-- ))
done

# Read file line by line
while IFS= read -r line; do
    echo "$line"
done < /etc/passwd
```

**Example — chkmail (Lab 3): Check for new mails every 10 seconds:**
```bash
#!/bin/bash
mailfile="/var/mail/$USER"
last_size=0

while true; do
    current_size=$(wc -c < "$mailfile" 2>/dev/null || echo 0)
    if [ "$current_size" -gt "$last_size" ]; then
        echo "You have new mail!"
        last_size=$current_size
    fi
    sleep 10
done
```

### 6.3 until loop

Runs **until** condition becomes **true** (opposite of while).

```bash
until [ condition ]; do
    commands
done
```

```bash
count=0
until [ $count -ge 5 ]; do
    echo "count = $count"
    (( count++ ))
done
```

### 6.4 Loop control

```bash
break       # Exit the loop immediately
continue    # Skip to next iteration
break 2     # Break out of 2 nested loops
```

### 6.5 select loop

Creates an **interactive numbered menu** automatically.

```bash
select item in option1 option2 quit; do
    case "$item" in
        option1) echo "You chose 1" ;;
        option2) echo "You chose 2" ;;
        quit)    break ;;
        *)       echo "Invalid" ;;
    esac
done
```

> 💡 `select` automatically displays a numbered menu and sets `$REPLY` to the number typed.

---

## 7. Functions

```bash
# Define a function
function_name() {
    commands
    return value    # Optional: return an exit code (0–255)
}

# Call it
function_name
function_name arg1 arg2    # With arguments
```

Inside a function, `$1`, `$2`... refer to the **function's arguments**, not the script's.

```bash
# Example — mysq (Lab 3): Calculate square of argument
mysq() {
    local num=$1               # 'local' keeps variable inside function
    echo $(( num * num ))
}

result=$(mysq 7)
echo "Square: $result"        # Output: Square: 49
```

**Local variables:**
```bash
myfunc() {
    local x=10      # Only exists inside this function
    echo $x
}
x=99
myfunc              # Prints 10
echo $x             # Prints 99 — unchanged
```

---

## 8. Arrays

```bash
# Declare and assign
arr=(one two three four)
arr[0]="first"               # Assign by index

# Access elements
echo ${arr[0]}               # first element
echo ${arr[@]}               # ALL elements
echo ${#arr[@]}              # Number of elements
echo ${arr[@]:1:2}           # Slice: 2 elements starting at index 1

# Loop over array
for element in "${arr[@]}"; do
    echo "$element"
done

# Add elements
arr+=("five")
arr[10]="ten"                # Sparse array — gaps are ok
```

**Example — myarr (Lab 3): Fill and print an array from user input:**
```bash
#!/bin/bash
read -p "How many elements? " n
arr=()

for (( i=0; i<n; i++ )); do
    read -p "Element $((i+1)): " val
    arr+=("$val")
done

echo "Array: ${arr[@]}"
```

**Example — myavg (Lab 3): Average of numbers:**
```bash
#!/bin/bash
echo "Enter numbers (empty line to stop):"
nums=()

while true; do
    read -p "> " num
    [ -z "$num" ] && break
    nums+=("$num")
done

total=0
for n in "${nums[@]}"; do
    (( total += n ))
done

count=${#nums[@]}
echo "Average: $(echo "scale=2; $total / $count" | bc)"
```

---

## 9. Special Variables

| Variable | Meaning |
|----------|---------|
| `$0` | Script name |
| `$1`, `$2` ... | Positional arguments |
| `$@` | All arguments (as separate words) |
| `$*` | All arguments (as one string) |
| `$#` | Number of arguments |
| `$$` | PID of current shell |
| `$?` | Exit status of last command (0 = success) |
| `$!` | PID of last background process |
| `$_` | Last argument of previous command |
| `$HOME` | Home directory |
| `$USER` | Current username |
| `$PWD` | Current directory |
| `$PATH` | Command search path |
| `$REPLY` | Input from `select` or `read` (no variable specified) |

**`$@` vs `$*`:**
```bash
# With args: "hello world" "foo"
for i in "$@"; do echo "$i"; done   # Prints: "hello world" then "foo" ✅
for i in "$*"; do echo "$i"; done   # Prints: "hello world foo" (all in one) ❌
```

> 💡 Almost always use `"$@"` when passing arguments around.

---

## 10. sed & awk Quick Reference

### 10.1 sed

```bash
# Syntax: sed 'command' file

sed -n '/lp/p' /etc/passwd          # Print lines containing "lp"   (Lab 1.1)
sed '3d' /etc/passwd                # Delete line 3                  (Lab 1.2)
sed '$d' /etc/passwd                # Delete last line               (Lab 1.3)
sed '/lp/d' /etc/passwd             # Delete lines with "lp"         (Lab 1.4)
sed 's/lp/mylp/g' /etc/passwd       # Replace all "lp" with "mylp"   (Lab 1.5)

# Key flags
-n          # Suppress auto-print (use with p)
-i          # Edit file in-place
s/old/new/  # Substitute (first occurrence per line)
s/old/new/g # Substitute all occurrences
/pattern/d  # Delete matching lines
```

### 10.2 awk

`/etc/passwd` fields separated by `:` → `$1`=login, `$3`=uid, `$4`=gid, `$5`=comment, `$6`=home

```bash
# Syntax: awk -F: 'pattern { action }' file

awk -F: '{print $5}' /etc/passwd               # Full name (Lab 2.1)
awk -F: '{print NR, $1, $5, $6}' /etc/passwd   # With line numbers (Lab 2.2)
awk -F: '$3 > 500 {print $1, $3, $5}' /etc/passwd   # uid > 500 (Lab 2.3)
awk -F: '$3 == 500 {print $1, $3, $5}' /etc/passwd  # uid == 500 (Lab 2.4)
awk -F: 'NR>=5 && NR<=15' /etc/passwd         # Lines 5–15 (Lab 2.5)
awk -F: '{gsub(/lp/, "mylp"); print}' /etc/passwd   # Replace (Lab 2.6)
awk -F: 'BEGIN{max=0} $3>max{max=$3; line=$0} END{print line}' /etc/passwd  # Max uid (Lab 2.7)
awk -F: '{sum += $3} END {print "Sum:", sum}' /etc/passwd   # Sum of IDs (Lab 2.8)
```

**awk special variables:**

| Variable | Meaning |
|----------|---------|
| `NR` | Current record (line) number |
| `NF` | Number of fields in current line |
| `FS` | Field separator (default: space) |
| `$0` | Entire current line |
| `$1`, `$2`... | Individual fields |

---

## Quick Syntax Cheatsheet

```
Quotes:
  'literal'          → no expansion
  "with $vars"       → variable expansion
  $(command)         → command substitution (modern)
  `command`          → command substitution (old)

Brackets:
  [ ]                → POSIX test
  [[ ]]              → Bash extended test (use this in bash)
  ( )                → subshell
  $( )               → command substitution
  (( ))              → arithmetic (no $, returns exit code)
  $(( ))             → arithmetic expansion (returns value)

Variables:
  var=value          → assign (NO spaces!)
  $var / ${var}      → read
  export var         → share with child shells
  local var          → scope to function

Tests ([ ] / [[ ]]):
  -f  file exists and is regular file
  -d  is directory
  -r/-w/-x  readable / writable / executable
  -z  string is empty
  -n  string is non-empty
  -eq / -ne / -lt / -le / -gt / -ge  numeric comparisons
  =  /  !=  string comparisons
```
$var
value of variable
${...}
value + logic
$(...)
value from command
$((...))
value from math
