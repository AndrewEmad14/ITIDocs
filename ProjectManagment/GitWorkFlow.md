Daily cycle


1. git clone [repo]

2. git checkout release/vxx

3. git checkout -b [branch-name] //create new branch

Pushing

1.git add .    [. adds all your files ]

2.git commit -m commit -m “your message“

3.git push origin [your-branch-name]

After Merging in github remote

if you will make a brand new branch pull the releases then make a new branch

1. git checkout release/vxx

2. git pull origin release/vxx //pull changes

3. git checkout -b [branch-name] //create new branch

if you will make a brand new branch pull the releases then make a new branch

1. git checkout [your-old-branch]

2. git pull origin release/vxx // pull recent changes



# Naming convention Summary

feature/description          # New features

fix/description             # Alternative to bugfix

release/version             # Release preparation

refactor/description        # Code refactoring
## Versioning
Major.Minor.Patch
## Branch naming rules(kebab)

Use lowercase

Use hyphens (not underscores or spaces)

Be descriptive but concise

No special characters

ex: feature/user-authentication

## Commit naming rules

feat: new feature

fix: bug fix

docs: documentation changes

style: code formatting (no logic change)
refactor: code restructuring (no feature/fix)
test: adding/updating tests

revert: reverting previous commit



Use imperative mood: "add" not "added"

Don't capitalize first letter after type

## Examples
 commit -m "feat: add user authentication"

git commit -m "feat: add email notifications" -m "- Send welcome email

Add password reset template

Configure SMTP settings"