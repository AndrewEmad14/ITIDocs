# 🐧 Linux & Red Hat System Administration — Complete Study Guide

> A consolidated reference covering navigation, permissions, processes, archiving, and more.

---

## Table of Contents

1. [File System Overview](#1-file-system-overview)
2. [Paths — Absolute vs Relative](#2-paths--absolute-vs-relative)
3. [Essential Commands](#3-essential-commands)
4. [File & Directory Operations](#4-file--directory-operations)
5. [Wildcards & Metacharacters](#5-wildcards--metacharacters)
6. [Redirection & Pipelines](#6-redirection--pipelines)
7. [Text Processing](#7-text-processing)
8. [Permissions & Ownership](#8-permissions--ownership)
9. [Vi Editor](#9-vi-editor)
10. [Users & Groups](#10-users--groups)
11. [Environment Variables & Initialization Files](#11-environment-variables--initialization-files)
12. [Processes & Job Control](#12-processes--job-control)
13. [Inodes, Hard Links & Soft Links](#13-inodes-hard-links--soft-links)
14. [Archiving & Compression](#14-archiving--compression)
15. [Mounting](#15-mounting)
16. [Lab Solutions](#16-lab-solutions)
17. [Top Assignment](#17-top-assignment)

---

## 1. File System Overview

| Directory | Purpose |
|-----------|---------|
| `/` | Root — start of the file hierarchy |
| `/bin` | User command binaries |
| `/sbin` | Superuser command binaries (link to `/usr/sbin`) |
| `/boot` | Boot-related files (e.g., GRUB) |
| `/root` | Home directory for the root user |
| `/home` | Home directories for regular users |
| `/dev` | Device files — special files that interface with hardware |
| `/etc` | System-wide configuration files |
| `/tmp` | Temporary files (size changes dramatically) |
| `/var` | Variable data: logs, cache, spool |
| `/lib` | System libraries |
| `/proc` | Process directory (virtual filesystem) |
| `/opt` | Optional/add-on software packages |
| `/usr/sbin` | Link to `/sbin` |
| `/media` | Automatic mounting point |
| `/mnt` | Manual mounting point |

---

## 2. Paths — Absolute vs Relative

### Absolute Path
- Starts from `/` (root) or `~` (home directory, equivalent to `/home/username` or `$HOME`)
- Examples:
  ```bash
  cd /usr/bin
  cd /home/mina/Documents/
  cd $HOME/Desktop/
  ```

### Relative Path
- Starts from your current location (`.` = current dir, `..` = parent dir)
- Examples:
  ```bash
  cd ../../../../../usr/bin
  cd ../../Documents/
  cd Documents/        # or cd ./Documents/
  ```

> **Note:** `~` is always the absolute path to the current logged-in user's home directory.

---

## 3. Essential Commands

### Navigation

| Command | Description |
|---------|-------------|
| `pwd` | Print Working Directory |
| `cd path` | Change directory |
| `cd ~` or `cd` | Go to home directory |
| `cd ..` | Go to parent directory |
| `cd -` | Go to previously visited directory |
| `ls` | List directory contents |
| `ls -l` | Long listing format |
| `ls -la` | Long listing including hidden files |
| `ls -lA` | Long listing with hidden files, excluding `.` and `..` |
| `ls -lh` | Human-readable file sizes |
| `ls -lSh` | Sort by size (human-readable) |
| `ls -lth` | Sort by modification time |
| `ls -R /` | Recursive listing |
| `ls -d` | Info on directories only |
| `ls -F` | Append type indicator (`/` = dir, `*` = executable, `@` = symlink) |

### Viewing Files

| Command | Description |
|---------|-------------|
| `cat file` | Display full file contents |
| `cat -n file` | Display with line numbers |
| `more file` | Page through file one screen at a time |
| `less file` | Page through file (backwards supported) |
| `head -n N file` | Display first N lines (default: 10) |
| `tail -n N file` | Display last N lines (default: 10) |
| `tail +N file` | Display from line N to end |
| `tail -f file` | Actively follow file changes in real time |

> **Tip — Display lines 50 to 56:**
> ```bash
> cat -n /etc/passwd | head -56 | tail +50
> # or
> cat -n /etc/passwd | head -56 | tail -7   # (56 - 50 + 1 = 7)
> ```

### Disk & System Info

| Command | Description |
|---------|-------------|
| `du -sh path` | Size of a folder or file |
| `df -h /` | Free space and partition size |
| `uptime` | How long the system has been running |
| `w` or `who` | Who is currently logged in |
| `whoami` | Display current username |
| `id [user]` | Display user identity information |

### Finding Files

| Command | Description |
|---------|-------------|
| `find / -name filename` | Search live filesystem by name |
| `find ~ -iname filename` | Case-insensitive name search |
| `find ~ -atime 2` | Files accessed 2 days ago |
| `find /etc -user 0` | Files owned by UID 0 (root) |
| `find ~ -type d` | Find directories only |
| `find / -inum N` | Find by inode number |
| `find / -size +10M` | Find files larger than 10 MB |
| `locate filename` | Search a pre-built database (fast) |
| `updatedb` | Update the `locate` database |
| `whereis command` | Location of a command or its man page |

> **Note:** `locate` reads from a database — new files won't appear until `updatedb` is run.

### `man` — Manual Pages

```bash
man command          # Manual for a command
man -k "keyword"     # Search globally across all man pages
man -a passwd        # All manual pages for passwd
man -s 5 passwd      # Manual for passwd in section 5 (file formats)
man 5 passwd         # Same as above
man -f passwd        # Show which sections contain passwd (like `whatis`)
whatis passwd        # Short description of passwd
apropos "ownership"  # Search by keyword in descriptions
```

**Man page sections:**

| Section | Content |
|---------|---------|
| 1 | Executable programs / shell commands |
| 2 | System calls |
| 3 | Library calls |
| 4 | Special files (`/dev`) |
| 5 | File formats (e.g., `/etc/passwd`) |
| 6 | Games |
| 7 | Miscellaneous |
| 8 | System administration commands (root only) |
| 9 | Kernel routines |

---

## 4. File & Directory Operations

### Creating Files

```bash
touch file1 file2 file3         # Create files (or update timestamps)
touch ~/Documents/file{1..3}    # Create file1, file2, file3
echo "content" > file           # Create file with content (overwrite)
echo "content" >> file          # Append to file
cat > file                      # Type content, press Ctrl+D to save
> emptyfile                     # Create an empty file
```

### Creating Directories

```bash
mkdir dirname                   # Create a directory
mkdir -p parent/child           # Create nested directories
mkdir dir{1..3}                 # Create dir1, dir2, dir3
mkdir {dir,data}.txt            # Create dir.txt and data.txt
```

### Copying Files

```bash
cp source dest          # Copy a file
cp -r sourcedir dest    # Copy a directory recursively
cp file1 file2 destdir  # Copy multiple files into a directory
```

> **Rules for `cp`:**
> - Last argument must be a directory when copying multiple files.
> - `cp file1 file2` → overwrites `file2`.
> - `cp file dir/` → copies into `dir`.
> - If destination doesn't exist → copies and renames.

### Moving & Renaming

```bash
mv source dest          # Move or rename
mv file1 file2          # Rename file1 to file2
mv -i source dest       # Prompt before overwriting
```

> **Rule:** `mv` with 2 arguments = move **or** rename. With 3+ arguments = move.

### Deleting

```bash
rm file                 # Delete a file
rm -r directory         # Delete directory recursively
rm -i file              # Prompt before deletion
rm -f file              # Force delete (no prompt)
rm -r ~/folder/*        # Delete all files and folders inside a folder
rmdir emptydir          # Delete an empty directory (FOREVER)
```

### `wc` — Word Count

```bash
wc file                 # Lines, words, bytes
wc -l file              # Count lines
wc -w file              # Count words
wc -c file              # Count bytes/characters
```

### `history`

```bash
history                 # Show command history for the session
```

---

## 5. Wildcards & Metacharacters

| Wildcard | Meaning | Example |
|----------|---------|---------|
| `*` | Zero or more characters | `ls /etc/*.conf` |
| `?` | Exactly one character | `ls file?` |
| `[a-z]` | One character from the range | `ls [a-f]*` |
| `[!abc]` | One character NOT in the set | `ls [!a-z]*` |

> **Note:** Wildcards do **not** match hidden files (those starting with `.`).

```bash
ls [a-zA-Z]*            # Files starting with a letter
ls ~/Music/*.txt        # All .txt files in ~/Music
ls -F ~/Music/ | grep '/'       # List only directories
ls -l ~/Music/ | grep '^d'      # List only directories
ls -l ~/Music/ | grep '^-'      # List only regular files
```

---

## 6. Redirection & Pipelines

### Standard Streams

| Stream | FD | Symbol |
|--------|----|--------|
| stdin | 0 | `<` or `0<` |
| stdout | 1 | `>` or `1>` (overwrite), `>>` or `1>>` (append) |
| stderr | 2 | `2>` (overwrite), `2>>` (append) |

```bash
command > file          # Redirect stdout (overwrite)
command >> file         # Redirect stdout (append)
command 2> errors.txt   # Redirect stderr
command > out 2> err    # Redirect stdout and stderr separately
command > out 2>&1      # Redirect both stdout and stderr to same file
command 2>/dev/null     # Discard errors (/dev/null = trash)
```

### Here-Documents & Here-Strings

```bash
# Here-document: multi-line input from keyboard
cat << EOF > file.txt
line one
line two
EOF

# Here-string: single string as input
tr 'a-z' 'A-Z' <<< "welcome"       # outputs: WELCOME
tr 'a-z' 'A-Z' <<< $var
```

### Pipelines

```bash
command1 | command2 | command3
ls | wc -l              # Count files in directory
echo "hello" | tr 'a-z' 'A-Z'      # Convert to uppercase
echo $var | tr 'a-z' 'A-Z'
```

### `tee` — Split Output

```bash
echo "Hello" | tee file.txt     # Output to terminal AND write to file
```

### `diff` — Compare Files

```bash
diff file1 file2        # Show differences (instructions to make file1 look like file2)
cmp file1 file2         # Byte-by-byte comparison
```

> **`diff` output symbols:**
> - `<` — line in file1 only
> - `>` — line in file2 only
> - `c` — changed, `a` — added, `d` — deleted

---

## 7. Text Processing

### `grep` — Search / Filter Rows

```bash
grep 'pattern' file             # Search for pattern
grep '^root' /etc/passwd        # Lines starting with "root"
grep 'bash$' /etc/passwd        # Lines ending with "bash"
grep -i 'mina' /etc/passwd      # Case-insensitive search
grep -r 'keyword' /dir          # Recursive search
grep -v 'pattern' file          # Invert match (exclude pattern)
```

### `cut` — Filter Columns

```bash
cut -d: -f1 /etc/passwd         # Extract field 1 (login name)
cut -d: -f1,5 /etc/passwd       # Extract fields 1 and 5
cut -d: -f5-7 /etc/passwd       # Extract fields 5 through 7
```

### `tr` — Translate / Replace Characters

```bash
echo "hello" | tr 'a-z' 'A-Z'      # Convert to uppercase
tr 'a-z' 'A-Z' <<< "welcome"
tr -d '/'                           # Delete a character
```

### `sort` — Sort Lines

```bash
sort file                           # Alphabetical sort
sort -n file                        # Numeric sort
sort -r file                        # Reverse sort
sort -k3 -t: file                   # Sort by column 3, delimiter ":"
sort -n -t: -k3 -r /etc/passwd      # Sort passwd by UID descending

# Get the maximum UID:
sort -n -t: -k3 -r /etc/passwd | head -1 | cut -d: -f3
```

---

## 8. Permissions & Ownership

### Understanding Permissions

```
-rwxrw-r--  1  user  group  size  date  filename
│└──┴──┴──┘
│  u   g   o
│ owner group others
└─ file type (- = file, d = directory, l = symlink)
```

### Permission Table

| Permission | On File | On Directory |
|-----------|---------|-------------|
| `r` (4) | Display / copy file | `ls` the directory |
| `w` (2) | Modify file content | Add, delete, rename files (needs `x` too) |
| `x` (1) | Execute the file | `cd` into directory; `ls -l` (needs `r` too) |

### Minimum Permissions Required

| Operation | File | Source Dir | Destination Dir |
|-----------|------|------------|----------------|
| Copy | `r--` | `--x` | `-wx` |
| Move | `---` | `-wx` | `-wx` |
| Delete | `---` | `-wx` | — |
| Rename | `---` | `-wx` | — |
| View content | `r--` | — | — |
| Edit content | `rw-` | — | — |
| Run script | `r-x` | — | — |

### `chmod` — Change Permissions

```bash
# Symbolic mode
chmod u+x file              # Add execute for owner
chmod go+r file             # Add read for group and others
chmod u+x,go+r file         # Combined
chmod a+r file              # Add read for all
chmod o-w file              # Remove write from others
chmod u=rw file             # Set owner to exactly rw

# Octal mode (r=4, w=2, x=1)
chmod 755 file              # u=rwx, g=r-x, o=r-x
chmod 760 file              # u=rwx, g=rw-, o=---
chmod 644 file              # u=rw-, g=r--, o=r--
```

> **Important:** `chmod` is NOT recursive by default. Use `-R` for recursive permission changes.

> **Vi & permissions:** Vi reads before it writes, so it needs `rw` permission. With only `w`, you can still override using `:wq!`. To append with only `w`, use shell redirection (`>>`).

### `umask` — Default Permission Mask

```bash
umask                   # Show current umask (e.g., 0022)
umask -S                # Show in symbolic form (e.g., u=rwx,g=rx,o=rx)
umask 022               # Set umask
```

> **How umask works:**
> - Default max for files: `666`
> - Default max for directories: `777`
> - `Default Permission = Max - umask` (removing execute from files by default)
> - `umask` only affects the **current user** and **current session** unless set in a profile file.

### Changing Ownership

```bash
sudo chown user file            # Change file owner
sudo chown :group file          # Change file group
sudo chown user:group file      # Change both owner and group
sudo chgrp groupname file       # Change group only
```

### Access Decision Logic

```
If user == file owner   → apply owner (u) permissions
Else if user is in the file's group → apply group (g) permissions
Else → apply other (o) permissions
```

---

## 9. Vi Editor

### Modes

| Mode | How to Enter |
|------|-------------|
| Normal (Command) | `Esc` |
| Insert | `i` |
| Last-line | `Esc` then `:` |

### Navigation (Normal Mode)

| Key | Action |
|-----|--------|
| `h` | Move left |
| `l` | Move right |
| `j` | Move down |
| `k` | Move up |
| `w` | Forward one word |
| `b` | Back one word |
| `e` | End of current word |
| `0` | Beginning of line |
| `Ctrl+F` | Page forward |
| `Ctrl+B` | Page back |

### Editing (Normal Mode)

| Key | Action |
|-----|--------|
| `i` | Insert before cursor |
| `a` | Append after cursor |
| `A` (Shift+A) | Append at end of line |
| `I` (Shift+I) | Insert at beginning of line |
| `o` | Open new line below |
| `O` (Shift+O) | Open new line above |
| `dd` | Delete current line |
| `u` | Undo |
| `Ctrl+R` | Redo |

### Last-line Mode (`:`)

| Command | Action |
|---------|--------|
| `:w` | Save |
| `:wq` | Save and quit |
| `:q` | Quit |
| `:q!` | Force quit without saving |
| `:wq!` | Force save and quit (useful with write-only permission) |
| `:n` | Go to line N |
| `:set nu` | Show line numbers |
| `:set ic` | Ignore case sensitivity in searches |
| `:set showmode` | Show current mode |

### Searching in Vi

```bash
/pattern        # Search forward for pattern
n               # Next match
N               # Previous match
```

```bash
vi -R file      # Open file in read-only mode
vi -i           # Read-only mode (alternative flag)
```

---

## 10. Users & Groups

### Key Configuration Files

#### `/etc/passwd`
```
login-name:x:uid:gid:comment:home-directory:login-shell
```

#### `/etc/shadow`
```
username:encrypted-passwd:last-changed:min:max:warn:inactive:expire:future-use
```
- **inactive**: Number of days after password expires before the account is disabled.

#### `/etc/group`
```
groupname:x:gid:comma-separated-members
```

#### `/etc/gshadow`
Stores secure group account information.

#### `/etc/skel`
Files placed here are automatically copied to a new user's home directory on creation.

### User Types

| Type | UID Range |
|------|-----------|
| Root | 0 |
| Service/System users | 1–999 |
| Normal users | 1000+ |

### User Management Commands

```bash
useradd username            # Create user
useradd -u UID username     # Specify UID
useradd -g group username   # Specify primary group
useradd -G g1,g2 username   # Specify secondary groups
useradd -c "comment" username
useradd -md /path username  # Create home directory at specific path
useradd -s /bin/bash username   # Specify shell

usermod -g group user       # Change primary group
usermod -G g1,g2 user       # Change secondary groups
usermod -aG group user      # Append to secondary groups (important: use -a)
usermod -l newname user     # Change login name
usermod -L user             # Lock password
usermod -U user             # Unlock password

userdel user                # Delete user
userdel -r user             # Delete user AND home directory

passwd user                 # Change password
passwd -n N user            # Min days between changes
passwd -x N user            # Max days between changes
passwd -w N user            # Warning days before expiry
passwd -l user              # Lock account
passwd -u user              # Unlock account

newusers file               # Create multiple users from a file
id [user]                   # Display user UID, GID, groups
```

### Group Management Commands

```bash
groupadd groupname          # Create group
groupadd -r groupname       # Create system group (low GID)
groupdel groupname          # Delete group
gpasswd groupname           # Change group password
newgrp groupname            # Temporarily switch primary group
chage -l user               # List password aging info
chage -E date user          # Set account expiration date
chage -M days user          # Set max password age
chage -m days user          # Set min password age
chage -W days user          # Set warning days
```

### Switching Users

```bash
su user             # Switch user (keeps current environment)
su - user           # Switch user and reset ALL environment variables
su -c "cmd" user    # Run a command as another user and exit
sudo command        # Run as root (using current user's password)
sudo -i             # Interactive root shell (resets environment)
sudo -s             # Root shell (keeps environment)
```

> **Difference: `su` vs `su -`**
> | | `su` | `su -` |
> |---|---|---|
> | Environment | Keeps current env | Resets all env variables |
> | Files sourced | `~/.bashrc`, `/etc/bashrc` | `~/.bashrc`, `/etc/bashrc`, `~/.profile`, `/etc/profile` |

### Sudo Configuration

```bash
visudo                          # Safely edit /etc/sudoers
```

In `/etc/sudoers`:
```
username ALL=(ALL) ALL          # Full root access for a user
%groupname ALL=(ALL) ALL        # Full root access for a group
```

```bash
sudo usermod mina -aG wheel     # Add user to wheel group (sudoers)
```

> `%wheel` is the default group with full root access.

---

## 11. Environment Variables & Initialization Files

### Common Environment Variables

| Variable | Description |
|----------|-------------|
| `$HOME` | Current user's home directory |
| `$PWD` | Present working directory |
| `$SHELL` | Current user's shell |
| `$PATH` | Directories searched for commands |
| `$0` | Name/path of the current shell |
| `$USER` | Current username |
| `PS1` | Primary prompt string |
| `PS2` | Continuation prompt (default `>`) |

```bash
printenv                    # Show all environment variables
echo $SHELL                 # Print current shell
echo $VAR                   # Print a variable
PATH=$PATH:/new/directory   # Add directory to PATH

# PS2 (continuation prompt after backslash-newline)
# Change for current session only:
PS2=":"
# Change permanently for all login terminals:
# Add to /etc/profile
# Change permanently for all terminals:
# Add to /etc/bashrc
```

### Alias

```bash
alias c=clear               # Create alias
alias ls='ls -l'            # Override command with options
unalias c                   # Remove alias
```

> **Note:** Aliases defined inside `sudo` are in ALL CAPS by default.

### Initialization Files

| File | When It Runs |
|------|-------------|
| `/etc/profile` | Login terminal — all users |
| `~/.profile` or `~/.bash_profile` | Login terminal — current user |
| `/etc/bash.bashrc` | Every new terminal — all users |
| `~/.bashrc` | Every new terminal — current user |

> A **login terminal** (e.g., `su -`, SSH, physical login) sources all 4 files.  
> A **non-login terminal** (e.g., opening a new terminal window) sources only the `bashrc` files.

---

## 12. Processes & Job Control

### Key Concepts

- The system starts **daemons** — background processes that provide services.
- Every process has a unique **PID** (Process ID).
- The CPU runs one process at a time (time-slicing creates the illusion of parallel execution).
- **Niceness** ranges from `-20` (highest priority) to `+19` (lowest priority).

### Process Commands

```bash
ps                          # Processes on current terminal
ps -l                       # Detailed description
ps aux                      # All processes, all users
ps -ef                      # All processes with PPID (Parent Process ID)
ps -u username              # Processes of a specific user
ps -p PID                   # Info on a specific process
ps -d                       # All processes except session leaders

pstree                      # Display process tree
top                         # Dynamic system monitor (like Task Manager)
```

### Background & Foreground

```bash
command &                   # Run process in background
jobs                        # List background/stopped jobs
fg %jobID                   # Bring job to foreground
bg %jobID                   # Resume stopped job in background
Ctrl+Z                      # Stop (pause) current foreground process
```

### `kill` — Send Signals

```bash
kill PID                    # Terminate process (default: SIGTERM)
kill -l                     # List all signal names
kill -STOP %jobID           # Stop a process
kill -CONT PID              # Resume a stopped process
kill -9 PID                 # Force kill (SIGKILL)
```

| Signal Number | Name | Action |
|---|---|---|
| 9 | SIGKILL | Force kill (cannot be caught) |
| 15 | SIGTERM | Graceful termination (default) |
| 18 | SIGCONT | Continue a stopped process |
| 19 | SIGSTOP | Stop a process (cannot be caught) |

### `pgrep` / `pkill` / `killall`

```bash
pgrep sleep                 # Find PID(s) of processes named "sleep"
pgrep -l processname        # List PIDs with names
pgrep -x processname        # Exact match
pgrep -u username -l        # All processes by user
pgrep -l -v "mina"         # All processes except those matching "mina"
pkill SIGNAL processname    # Kill by name
killall processname         # Kill all processes with that name
```

### Priority Control

```bash
nice -n 10 sleep 200000 &       # Start process with nice value 10
renice -n 5 -p PID              # Change priority of running process (needs sudo to increase)
sudo renice -n -5 -p PID        # Increase priority (lower nice value)
```

> **Remember:** Lower nice value = higher priority.

---

## 13. Inodes, Hard Links & Soft Links

### Inodes

- Linux identifies every file by a number called an **inode** (index node).
- Inode numbers are **unique per partition** — they may duplicate across different partitions.
- If inodes run out, you cannot create new files even if there's disk space.
- Any directory you create has **2 links** by default: one for itself and one for `.`.
- `..` is the parent directory link.

```bash
ls -i file          # Show inode number of a file
df -h /             # Show partition size
```

### Soft Links (Symbolic Links)

```bash
ln -s /path/to/target /path/to/link    # Create soft link
```

- Acts like a shortcut.
- Gets a **new inode number**.
- Default permissions: `777`.
- If the original file is deleted → the link becomes **broken** (dangling link).
- Does **not** increase the link count of the original file.
- Works across different partitions.
- Can link to **files or directories**.

### Hard Links

```bash
ln /path/to/target /path/to/link       # Create hard link
```

- Points to the **same inode** — no new inode created.
- Any change in either file is reflected in the other.
- **Only works on files**, not directories (to prevent recursive loops via `.` and `..`).
- **Cannot span across different partitions** (because inode numbers are partition-specific).
- Deleting one hard link does not remove the data — the data persists until all hard links are removed.

---

## 14. Archiving & Compression

### `tar` — Tape Archive

```bash
tar -cvf archive.tar /path          # Create archive (verbose)
tar -xvf archive.tar                # Extract archive
tar -cvzf archive.tar.gz /path      # Create + gzip compress
tar -cvjf archive.tar.bz2 /path     # Create + bzip2 compress
tar -xvzf archive.tar.gz            # Extract gzip archive
tar -cvf backup_etc /etc            # Archive /etc
```

| Flag | Meaning |
|------|---------|
| `-c` | Create archive |
| `-x` | Extract archive |
| `-v` | Verbose (show what's being processed) |
| `-f` | Use a file (not tape device) |
| `-z` | gzip compression |
| `-j` | bzip2 compression |

### Compression Tools

| Tool | Compress | Decompress | View Compressed |
|------|----------|-----------|-----------------|
| `compress` | `compress -v file` | `uncompress file` | `zcat file.Z` |
| `gzip` | `gzip -v file` | `gunzip -v file` | `zcat file.gz` |
| `bzip2` | `bzip2 -v file` | `bunzip2 file` | `bzcat file.bz2` |
| `zip` | `zip archive.zip file` | `unzip archive.zip` | — |

> **Note:** File extensions don't affect how Linux treats files — they are just conventions.
>
> **`tar.Z`** = tarball that has been compressed (archive + compress).

### Environment Variables Related to Archives

```bash
echo $SHELL         # e.g., /bin/bash
echo $0             # Current shell name
```

---

## 15. Mounting

```bash
/media      # Automatic mounting (e.g., USB drives, CDs)
/mnt        # Manual mounting point
```

---

## 16. Lab Solutions

### Lab 1

```bash
# Difference between cat and more:
# cat: displays full file contents at once
# more: displays content one screen at a time (paginated)

# Difference between rmdir and rm:
# rmdir: removes empty directories only
# rm -r: removes directories recursively (files and folders inside)
# rm -i: prompts for confirmation before each deletion
# rm -f: force removes without prompting

# Create directory structure and files:
mkdir -p dir1/dir11 && touch file1 && cd dir1 && mkdir dir12

# Absolute path example:
/home/andrew/docs/mycv

# Relative path example (from home):
docs

# Navigation shortcuts:
cd ~                        # Go home
cd -                        # Go to previous directory
cd /home/username           # Absolute path
cd ../../username           # Relative path

# View specific lines of /etc/passwd:
head -n 4 /etc/passwd
tail -n 7 /etc/passwd

# Man pages for passwd:
man -a passwd               # All sections
man passwd                  # Default (section 1)
man -K passwd               # Global keyword search
```

> **Bonus — What does `+` do with `tail`?**
> `tail +N file` outputs from line N to the end of the file (rather than the last N lines).

### Lab 2

```bash
# Create directory with specific permissions:
mkdir myteam
chmod 455 myteam

# Switch user:
su - user1

# Access issue explanation:
# Attempting cd /home/andrew/myteam fails because even though myteam
# has execute permission for others, the parent /home/andrew only
# grants permissions to its owner — so you can't traverse into it.

# Octal permission changes:
chmod 631 oldpasswd
chmod g-r+wx,o-r+x oldpasswd

# umask example:
umask 146

# Permission analysis summary:
# source dir: u=r    → target dir: u=wx   → file: u=r
# You don't need any permissions to delete a file —
# you need write+execute on the PARENT DIRECTORY.
# cd into a dir: requires execute (x)
# ls a dir: requires read (r)
# view file content: requires read (r)
# modify file content: requires read+write (rw)
```

### Lab 3

```bash
# Vi navigation:
# Move down 1 line: j
# Move up 1 line: k
# Search for "age": /age
# Go to line 5: :5
# Delete line: dd

# List available shells:
cat /etc/shells

# Show all environment variables:
printenv

# Man bash for all bash variables:
man bash

# Echo a variable:
echo $Var
echo $SHELL

# PS1 and PS2:
# PS1 is the main prompt
# PS2 is the continuation prompt (appears after \ + Enter)
# The ">" symbol you see on continuation is controlled by PS2

# Set PS2 to ":"
PS2=":"                     # Current session only
# Add to /etc/profile for login persistence
# Add to /etc/bashrc for all-terminal persistence

# Alias:
alias ls='ls -l'
```

### Lab 4

```bash
# 1. List /usr/bin commands to file:
echo `ls /usr/bin` > /tmp/commands.list

# 2. Count words in the list:
wc -w commands.list

# 3. Users starting with 'g':
cut -d: -f1 /etc/passwd | grep ^g

# 4. Users and full names starting with 'g':
cut -d: -f1,5 /etc/passwd | grep ^g

# 5. Sort and filter:
sort -t: -k5 /etc/passwd | grep ^g > file0

# 6. List all files recursively, sort, save result in background:
(ls -R / | sort) 2>error >result &
# Alternative:
ls -R / 2>/dev/null | sort > result &

# 7. Count logged-in users:
who | wc -l
# or
who -q

# 8. Lines 7 to 10 of /etc/passwd:
head -n 10 /etc/passwd | tail -n 4

# 9. Expected outputs:
# a) nothing will happen (empty pipe)
# b) missing operand error
# c) 1

# 10-19: Process control:
sleep 100 &
pgrep sleep
kill -STOP <PID>
kill -CONT <PID>
jobs
fg 1
kill -STOP <PID>
bg 1
kill <PID>
id
ps -U 1000
ps -d
pgrep -u 1000
pkill -n -u 1000
```

### Lab 5

```bash
# 1. Archiving and compression comparison:
tar -cvf trial1 /etc/passwd
compress -v trial1          # Compression: 80.24%  → trial1.Z
uncompress trial1.Z

gzip -v trial1              # Compression: 87.2%   → trial1.gz

zip trial1.zip trial1       # Compression: 87%
unzip trial1.zip

# 2. View compressed file:
zcat compressed_file.Z

# 3. Archive entire /etc directory:
tar -cvf backup_etc /etc

# 4. Files accessed exactly 2 days ago:
find ~ -atime 2

# 5. Files in /etc owned by root (UID 0):
find /etc -user 0

# 6. Find only directories in home:
find ~ -type d

# 7. Find .profile anywhere on system:
find / -name .profile

# 8. File types:
# /etc/passwd     → ASCII text
# /dev/pts/0      → character special (136/0)
# /dev/sda        → block special (8/0)

# 9. Inode numbers:
# /              → 128
# /etc           → 67240065
# /etc/hosts     → 67625392

# 10. Comparing files:
cp /etc/passwd .
diff /etc/passwd passwd         # No output (files are identical)
cmp /etc/passwd passwd          # No output (files are identical)
# After editing local copy:
diff /etc/passwd passwd
# 38d37
# < user1:x:1001:1001::/home/user1:/bin/bash
cmp /etc/passwd passwd
# cmp: EOF on passwd after byte 2207, line 37

# 11. Create soft link across partitions (works):
ln -s /etc/passwd /boot/passwd_link

# 12. Create hard link across partitions (FAILS):
ln /etc/passwd /boot/passwd_link
# Hard links cannot span different partitions because inode
# numbers are only unique within a single partition.
```

---

## 17. Top Assignment

**Task:** Sort processes by memory usage, run for 2 minutes, refresh every 30 seconds.

```bash
timeout 120s top -d 30 -o %MEM
```

| Option | Meaning |
|--------|---------|
| `timeout 120s` | Automatically stop after 120 seconds (2 minutes) |
| `-d 30` | Refresh delay of 30 seconds |
| `-o %MEM` | Sort output by memory usage |

---

## 📝 Quick Reference Card

### Permissions — Octal Cheat Sheet

| Octal | Binary | Symbolic |
|-------|--------|----------|
| 7 | 111 | `rwx` |
| 6 | 110 | `rw-` |
| 5 | 101 | `r-x` |
| 4 | 100 | `r--` |
| 3 | 011 | `-wx` |
| 2 | 010 | `-w-` |
| 1 | 001 | `--x` |
| 0 | 000 | `---` |

### Common Permission Sets

| Octal | Meaning |
|-------|---------|
| `755` | Owner: full; Group & Others: read+execute |
| `644` | Owner: read+write; Group & Others: read only |
| `700` | Owner: full; Group & Others: no access |
| `777` | Everyone: full access |
| `000` | No one has any access |

### Important Notes

- Files do **not** have executable permission by default.
- `vi` is the only editor that works if the system crashes.
- `chmod` is **not** recursive — use `-R` flag for directories.
- Hard links work **only on files**, not directories.
- Hard links **cannot span partitions**.
- Soft links **can span partitions** and **can link directories**.
- `su` doesn't reset the environment; `su -` resets all environment variables.
- `/dev/null` discards all data written to it (the system "trash").
- Switching inside a terminal is **not** the same as logging in.

---

*This guide was compiled from Red Hat System Administration course notes, labs, and supplementary materials.*
