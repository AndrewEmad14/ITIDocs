# git init

    	•	Creates a hidden .git folder to track version control history

# git-status(1)

           Show the working tree status.

# git config

            change user name or password , global or local on the machine

# git log

            show commit log

# git restore (unstaging or undo)

    Used to undo changes in the working directory or unstage files, without changing commit history.
    Examples:
    git restore file.txt           ← undo local file changes
    git restore --staged file.txt  ← remove a file from staging

# git reset --soft. (unstaging) BUT i am editing the commit history

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


    some caveates:
    if you revert a commit instead of the head , it may result in a conflict since it will see that you are trying to revert two things
    for example
    hello andrew
    commit A
    hello seif
    commit B
    hello david
    commit C
    revert commit B
        //reverts works by reversing the commit
        //it will try to reverse B
        // andrew->seif to reverse it seif -> andrew
        // but wait the head is currently point ing at david
        //where is the seif so i could change him?
        //the conflict in here would be like this
        >>>>>head
        hello david
        ===========
        hello seif
        hello andrew
        >>>>>revert form commit number
        you will have to decide how to resolve the conflict
        commit it
        and the enter revert continue

# git commit

            -am             add . + message#

# git rm \*.log

    remove log files

# git rebase

    git rebase is a command used to integrate changes from one branch into another by moving or combining a sequence of commits to a new base commit
    git checkout feature-branch
    git rebase main
    This replays all commits from feature-branch on top of the latest main branch.
    Example:
    # You're working locally
        git checkout feature
        git commit -m "WIP"
        git commit -m "Fix bug"

        # Later, update from main and rebase (all local)
        git fetch origin
        git rebase origin/main   # ← still local only!

        # Then push (if never pushed before, or if you own the branch)
        git push origin feature

    dont use rebase in public commits because it can cause problems to other collaborators (you will have a new history while they will have the old history resulting in a conflict)


    -i lets you enter interactive mode
    HEAD~n                              //last n commits

# git merge

    --squash
    merge your changes locally
    it creates a commit automatically if there are no conflicts
    if there conflicts
    resolve conflict
    git add .
    git commit

# git fetch

    fetch chnages for the remote repo but it doesnt merge

# git pull

    pull and merge changes in your branch
    now if  you have local commits AND the remote has new commits
    git asks you to specify the type of merge
    git pull --rebase=false (merge):
    git pull --rebase=true (rebase):
    git pull --ff-only (fast-forward only):

# forking

    clonnig vs forking
        CLONNING
        create local copy of your repo , link it to the remote repo
        you can push if you have right accesss

        FORKING
        create Remote copy of your repo , it lives on github
        you can push and pull as you like since it is a copy

# GIT CONVENTIONS QUICK REFERENCE

## BRANCH NAMING CONVENTIONS

    feature/description          # New features
    bugfix/description          # Bug fixes
    fix/description             # Alternative to bugfix
    hotfix/description          # Urgent production fixes
    release/version             # Release preparation
    chore/description           # Maintenance tasks
    docs/description            # Documentation only
    test/description            # Testing
    refactor/description        # Code refactoring

# With ticket numbers

    feature/JIRA-123-description
    bugfix/GH-456-description

# Branch naming rules

    - Use lowercase
    - Use hyphens (not underscores or spaces)
    - Be descriptive but concise
    - No special characters

# Examples

    feature/user-authentication
    bugfix/login-redirect-error
    hotfix/security-patch
    release/v1.2.0
    chore/update-dependencies
    docs/api-guide

## COMMIT MESSAGE CONVENTIONS

    feat: new feature
    fix: bug fix
    docs: documentation changes
    style: code formatting (no logic change)
    refactor: code restructuring (no feature/fix)
    test: adding/updating tests
    chore: maintenance tasks
    perf: performance improvements
    build: build system changes
    ci: CI/CD changes
    revert: reverting previous commit

# With scope

    feat(auth): add OAuth support
    fix(api): handle null response
    style(header): adjust spacing

# With breaking changes

    feat!: remove deprecated endpoints

# Commit message rules

    - Use imperative mood: "add" not "added"
    - Don't capitalize first letter after type
    - No period at end
    - Keep subject under 50-72 characters
    - Explain WHY in body, not just WHAT

# Simple examples

    git commit -m "feat: add user authentication"
    git commit -m "fix: resolve login redirect issue"
    git commit -m "docs: update README"
    git commit -m "refactor: simplify error handling"
    git commit -m "test: add unit tests for auth"

# With body

    git commit -m "feat: add email notifications" -m "- Send welcome email
    - Add password reset template
    - Configure SMTP settings"

# With issue reference

    git commit -m "fix: resolve timeout issue

    Closes #123"

# ANTI-PATTERNS (DON'T DO THIS)

    ❌ "fixed stuff"
    ❌ "updates"
    ❌ "WIP"
    ❌ "Final fix"
    ❌ feature/My_New_Feature
    ❌ feature/new feature (spaces)

# git reflog

    git keeps all of your history changes in reflog

# git stach

    git stash               Save changes temporarily
    git stash save "msg"    Save with description
    git stash list          View all stashes
    git stash pop           Apply and remove latest stash
    git stash apply         Apply but keep stash
    git stash drop          Delete latest stash
    git stash clear         Delete all stashes
    git stash show -p       View stash contents
    git stash -u            Include untracked files
    git stash branch name   Create branch from stash
