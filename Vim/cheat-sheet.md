Here is a concise list of essential Vim commands for your keyboard-only workflow. You can save this as `vim_cheat_sheet.md`.

---

# Essential Vim Commands

### 1. Navigation (Normal Mode)

* **`h` `j` `k` `l**` : Move Left, Down, Up, Right (instead of arrows)
* **`w`** : Jump to the start of the next **word**
* **`b`** : Jump to the previous **word**
* **`0`** : Jump to the **start** of the line
* **`$`** : Jump to the **end** of the line
* **`gg`** : Go to the **top** of the file
* **`G`** : Go to the **bottom** of the file

---

### 2. Editing & Selection

* **`i`** : Enter **Insert Mode** (to type)
* **`v`** : Enter **Visual Mode** (to highlight text)
* **`Esc`** : Return to **Normal Mode** (stop typing/selecting)
* **`x`** : Delete a single character
* **`dd`** : Delete (Cut) the **entire line**
* **`yy`** : Yank (Copy) the **entire line**
* **`p`** : Paste after the cursor

---

### 3. Clipboard & Undo

* **`u`** : Undo last action
* **`Ctrl` + `r**` : Redo last action
* **`"+y`** : Copy selection to **System Clipboard** (if configured)
* **`"+p`** : Paste from **System Clipboard**

---

### 4. Search & Replace

* **`/word`** : Search for "word" (Press `n` for next match, `N` for previous)
* **`:%s/old/new/g`** : Replace **all** occurrences of "old" with "new"

---

### 5. Saving & Exiting

* **`:w`** : Save (Write)
* **`:q!`** : Quit **without** saving
* **`:wq`** : Save and Quit (same as `ZZ`)
* **`:x`** : Save and Quit (only if changes were made)

---

### 6. Power Moves

* **`.`** : Repeat the last editing command
* **`:%d`** : Delete the **entire content** of the file
* **`:earlier 5m`** : Go back to the file state from **5 minutes ago**


