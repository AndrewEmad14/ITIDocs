# git init

    	•	Creates a hidden .git folder to track version control history

# git-status(1)

           Show the working tree status.

# git config

            change user name or password , global or local on the machine

# git log

            show log

# git restore

    Used to undo changes in the working directory or unstage files, without changing commit history.
    Examples:
    git restore file.txt           ← undo local file changes
    git restore --staged file.txt  ← remove a file from staging

# git reset --soft.     (unstaging)

    Moves HEAD to a previous commit and keeps all changes staged.
    Useful when you want to undo a commit but immediately recommit the same changes.
    git reset --soft HEAD~1

# git reset --mixed (default)

    Moves HEAD and unstages files while keeping working directory changes.
    Useful when you want to undo a commit but continue editing before committing again.
    git reset HEAD~1      ← same as mixed by default

# git reset --hard (removing all changes and commits) 84ama

    Completely resets commit history, staging, and working directory.
    Deletes all changes since the target commit. This is destructive.
    git reset --hard HEAD~1

# git revert

    Undoes a commit by creating a new commit that reverses its changes.
    This does not rewrite history and is safe for shared or public branches.
    git revert <commit>

# git commit

            -am             add . + message#

# git rm \*.log

    remove log files
