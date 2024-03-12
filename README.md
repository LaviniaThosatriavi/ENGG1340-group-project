# ENGG1340-group-project

## first time:
```bash
git clone https://github.com/tracy308/ENGG1340-group-project.git
```

## to update files:
``` bash
git pull 
# pull from the main branch to update any file changes from other people

git add -A
# add files to commit

git status
# to see which file are modified/created

git commit -m "<short summary of what you did>"
# write a short message, usually starting with fix: (fix bug), feat: (feature), etc.

git push
# push your changes to the branch
```

## Run File
``` bash
mkdir build
g++ -Wall hello.cpp -o build/hello
# go to build directory
./hello
```