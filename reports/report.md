# daalloc
Matthew Beaudouin, Seungin Lyu, Adam Novotny

## A dynamically sized array for C.

For this project, we implemented a dynamically sized vector `shvector`, running on a custom implementation of malloc called `shmalloc`. To show off the power of these tools we created `shchgrp`, an application that runs multiple regexes on a file and outputs the matches in separate lists.

Currently `shmalloc` is a functional, though naive, re-implementation of `malloc`.


#### Our learning goals:
- [x]Learn how malloc assigns system memory.
- [x]Learn how to implement dynamic arrays from a low-level perspective
- [x]Learn how to design an effective library API
- [x]Learn how to do testing and CI for a C codebase

We have made significant progress towards meeting these initial goals as demonstrated in our project status section. 

## Project Status (as of March 26):

##### What we have done
- We have implemented our own dynamically size vector [`shvector`](https://github.com/SeunginLyu/SoftSys-daalloc/blob/master/src/shvec.c).
- We have designed an [API](https://github.com/SeunginLyu/SoftSys-daalloc/blob/master/spec.md) for shvector.
- We have implemented our own `malloc` called [`shvalloc`](https://github.com/SeunginLyu/SoftSys-daalloc/blob/master/src/shvalloc.c) after following a [tutorial](https://danluu.com/malloc-tutorial/). We used the TDD (Test Driven Development) framework and wrote down [tests](https://github.com/SeunginLyu/SoftSys-daalloc/blob/master/src/test_shvalloc.c) before the implementation. 
- We have setup up a CI (Continuous Integration) environment for the team which uses Github and TravisCI. It automatically runs tests whenever someone pushes the code to the online repository. Also, we have been adhering to the rule that a pull request must be reviewed and approved by at least one of the team members before it gets merged to master.
- We have created a [`Makefile`](https://github.com/SeunginLyu/SoftSys-daalloc/blob/master/src/Makefile) that links the relevant components together. 
- We wrote unit tests for `shvector`
- `shvector` uses `shvalloc` instead of `malloc`, and everything works!
- We made a demo app `shchgrp` that uses `shvectors` to match multiple regexes against stdin.


##### What we had planned but haven't done yet
- We will update shvalloc so that it passes all the tests. It currently does not pass the test when the size is `MAX_SIZE`. It should return NULL but now it returns an address.
- Stretch:
    - Implement chunking to `shvector` to optimize it for `shvalloc`
    - Run performance comparisons of `shvector` vs `array` and `shchgrep` vs multiple `grep`s

## Shvector:
#### Implementation
Shvecs are stored as arrays on the heap. It starts with a small size, and after it fills up it reallocates space for a larger array.

A Shvector holds three types

We picked 2 as a growth factor after comparing other implementations. Most dynamically sized lists use 2 as a growth factor, though there were some arguments for 1.25 and 1.5. We decided that unused memory is not that big of an issue and went with the standard 2.

#### Design Decision
We designed the api to address shvectors with a unique id (which increments from 0). We hold all shvectors in an array, and the id corresponds to the index of the shvector in that array.

There are a few advantages to this approach, mainly that it was easy to implement. It hides the actual data from the rest of the application, forcing programmers to use the api, and it keeps track of the memory locations internally, so memory can never be lost.

There are two main disadvantages to this approach, there are a limited number of shvectors the application can use, and it must pre-allocate memory for all shvectors. Fortunately each shvector is only 16 bytes, so allocating 128 shvectors consumes 'only' 2kB of memory. The better way to do this would be to use a root shvector to hold all other shvectors, which would address both problems but add complexity to the library.

Another way we considered addressing new shvectors was to allocate memory for each shvector independently, and then refer to it by its memory address. The disadvantage to this is that we would have to change the api from using `int id` to `long id`. We would also expose the data to the programmers, which might make them misuse the library and be sad if we introduce breaking changes internally.


## Shmalloc:
#### Implementation
#### Design decision

## Shchgrp:
To demo our `shvector` library, we made a command-line tool called `shchgrp` (**sh**itty **ch**ained **gr**e**p**) which returns lists of the values matching each regex.

#### Example:
```
printf "abc\n123\n456def" | shchgrp "[0-9]" "[a-z]"
Matches to [0-9]:
    123
    456def
Matches to [a-z]:
    abc
    456def
```

#### Implementation:
First, shchgrp sets up a shvector for each regex, and then iterates through stdin line-by-line. Each line is compared against all regexes, and any matches are stored in the respective shvector (delimited by `\n`). After reaching the EOF, each shvector is printed to stdout.



## Resources:
- The [GNU grep code](https://savannah.gnu.org/git/?group=grep) was interesting to read, but way too complicated to use for an implementation reference.
- [This tutorial](https://www.happybearsoftware.com/implementing-a-dynamic-array) on dynamically sized arrays was very useful to reference when implementing shvector.
- \< Insert link to a malloc reference here \>

```
1) What is the goal of your project; for example, what do you plan to make, and what should it do?

2) What are your learning goals; that is, what do you intend to achieve by working on this project?

3) What resources did you find that were useful to you.  If you found any resources you think I should add to the list on the class web page, please email them to me.

4) What were you able to get done?  Include in the report whatever evidence is appropriate to demonstrate the outcome of the project.  Consider including snippets of code with explanation; do not paste in large chunks of unexplained code.  Consider including links to relevant files.  And do include output from the program(s) you wrote.

5) Explain at least one design decision you made.  Were there several ways to do something?  Which did you choose and why?

6) You will probably want to present a few code snippets that present the most important parts of your implementation.  You should not paste in large chunks of code or put them in the Appendix.  You can provide a link to a code file, but the report should stand alone; I should not have to read your code files to understand what you did.

7) Reflect on the outcome of the project in terms of your learning goals.  Between the lower and upper bounds you identified in the proposal, where did your project end up?  Did you achieve your learning goals?

Audience: Target an external audience that wants to know what you did and why.  More specifically, think about students in future versions of SoftSys who might want to work on a related project.  Also think about people who might look at your online portfolio to see what you know, what you can do, and how well you can communicate.
```