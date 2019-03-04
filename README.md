# Bomberman

## Workflow

### Feature

##### Create a branch for your work
```
    git checkout master // or the branch where you starting from
    git checkout -b features/[FEATURE NAME]
```

##### Adding and commiting work on your branch
```
    git add file1.c file2.c ...
    git commit -m "[CHANGES YOU'VE MADE]"
    git push origin features/[FEATURE NAME]
```

##### After your work is done

- Synchronize with master with `git rebase -i master` or `git pull origin master`
- Go to http://github.com/jbourdale/Bomberman
- Create a pull request on master
- Describe what you've made and **how to test it**
- Check if CircleCI workflow passed (will be show on the PR page)
    - If it doesn't pass, fix the problems ;)
- Ask for someone of the team to review your work because you can't merge it by yourself ;)

##### As a reviewer

- Pull the feature branch
- Test it as described in the PR comment
- If it seems ok to you
- Mark the PR as approved
- If your not sure at 100% about the work, ask (on fb/slack...) to someone else to review it too
- Else Merge it

##### Why are you cassing me les couilles

If we follow that workflow and if everyone review some PR, everybody will know about
the others work and everybody will improve.

## Seting up dev environment

### Install

##### On Ubuntu 18.10
```
    sudo apt-get update
    sudo apt-get install -y build-essential gcc
    git clone git@github.com:jbourdale/Bomberman.git
```

### Compiling

##### On Ubuntu 18.10
```
    make
```

### Linting

##### On Ubuntu 18.10

###### Installation
```
    cd /opt && wget -c https://github.com/oclint/oclint/releases/download/v0.13.1/oclint-0.13.1-x86_64-linux-4.4.0-112-generic.tar.gz -O - | tar -xz
```

###### Running
```
    /opt/oclint-0.13.1/bin/oclint `find -name *.c` -- -c
```

### Running

##### On Ubuntu 18.10
```
    ./Bomberman
```
