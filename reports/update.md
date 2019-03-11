# daalloc
Matthew Beaudouin, Seungin Lyu, Adam Novotny

## A dynamically sized array for C.

For this project, we implemented a dynamically sized vector `shvector`, running on a custom implementation of malloc `shmalloc`. To show off the power of these tools we created `shgrep`, an application that runs multiple regexes on a file and outputs the matches in separate lists.

Currently `shmalloc` is a naive re-implementation of `malloc`. We hope to optimize `shmalloc` for `shvectors`, which only grow in size in a geometric progression.

We are currently working on `shgrep`, and have a clear path to creating it.


#### Our learning goals:
- [x]Learn how malloc assigns system memory.
- [x]Learn how to implement dynamic arrays from a low-level perspective
- [x]Learn how to design an effective library API
- [x]Learn how to do testing and CI for a C codebase

At this point, we have made a solid progress towards meeting these initial goals as demonstrated in our project status section. 

## Project Status (as of March 12):

##### What we have done
- We have designed an [API](https://github.com/SeunginLyu/SoftSys-daalloc/blob/master/spec.md) for shvector.
- We have implemented our own dynamically size vector [`shvector`](https://github.com/SeunginLyu/SoftSys-daalloc/blob/master/src/shvec.c).
- We have implemented our own `malloc` called [`shvalloc`](https://github.com/SeunginLyu/SoftSys-daalloc/blob/master/src/shvalloc.c) after following a [tutorial](https://danluu.com/malloc-tutorial/). We used the TDD (Test Driven Development) framework and wrote down [tests](https://github.com/SeunginLyu/SoftSys-daalloc/blob/master/src/test_shvalloc.c) before the implementation. 
- We have setup up a CI (Continuous Integration) environment for the team which uses Github and TravisCI. It automatically runs tests whenever someone pushes the code to the online repository. Also, we have been adhering to the rule that a pull request must be reviewed and approved by at least one of the team members before it gets merged to master.
- We have created a [`Makefile`](https://github.com/SeunginLyu/SoftSys-daalloc/blob/master/src/Makefile) that links the relevant components together. 
##### What we had planned but haven't done yet
- We will write unit tests for `shvector`
- We will update shvalloc so that it passes all the tests. It currently does not pass the test when the size is `MAX_SIZE`. It should return NULL but now it returns an address.
- We will update `shvector` so that it internally uses `shvalloc` instead of `malloc` (after `shmalloc` passes all its tests)
- We will write the MVP of `shgrep`
    - Create the structure of the code (use [grep src code](https://savannah.gnu.org/git/?group=grep) for inspiration?)
    - Run multiple regexes against each line and append matches to its `shvector`
- Stretch:
    - Implement chunking to `shvector` to optimize it for `shvalloc`
    - Run performance comparisons of `shvector` vs `array` and `shchgrep` vs multiple `grep`s

## Current tasks:
For the sake of utilizing shvector in a creative manner, we are building a command-line tool called `shchgrp` (shitty chained grep) which returns lists of the values matching each regex. 

#### Example:
```
printf "abc\n123" | shchgrp "[0-9]" "[a-z]"
[0-9]:
    123
[a-z]:
    abc
```
