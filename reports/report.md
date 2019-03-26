# daalloc

#### Software Systems, Olin College of Engineering, SP19
#### Matthew Beaudouin-Lafon, Seungin Lyu, Adam Novotny 


## A dynamically sized array for C.
Our main goal throughout this project was to rewrite existing functionality in an impractical an over-engineered way as a learning experience. As a result, we put a large emphasis on our workflow, and prioritized avoiding existing functionality (such as malloc) over a broad set of features.
For this project, we made three interconnected applications. We implemented a dynamically sized vector `shvector`, running on a custom implementation of malloc called `shvalloc`. To show off the power of these tools we created `shchgrp`, an application that runs multiple regexes on a file and outputs the matches in separate lists. We used the 'sh' prefix to indicate our spirit of unnecessary(perhaps sh-itty) re-engineering attempts. All of these work, and writing them has improved our understanding of C at a low level (memory allocation), API design (to make the applications generalized while talking nicely to each other), and improved our ability to write C.


### Learning Goals

- Learn how to implement dynamic arrays from a low-level perspective
- Learn how malloc assigns system memory
- Learn how to design an effective library API
- Learn how to do testing and CI for a C codebase


## Project Workflow
We did most of our work together through pair programming. We often used the Live Share extension of Visual Studio Code on Seungin's machine to pair program (in part due to Matt's issues with RSI). So the commit history is not the most accurate representation of each member's contribution to this project. We believe the Trello board is a better source of our contribution history. We followed the TDD principles throughout the course of this project. We made sure each pull request gets at least one peer review and an approval before it gets merged to master. Adhering to a rather strict integration rules for a small project, we learned that such restrictions help us stay in tuned with each other's contribution and made sure everyone in the team was fully aware of the team's ongoing process.

## Shvector:
The original idea for the project was to write a version of malloc specifically designed for an application. We decided to choose dynamic vectors as it seemed like ripe with memory allocations opportunities. We modelled shvec after the C++ vector class, which automatically "grows" when a value is written past its largest index.

### Implementation

A Shvector holds three values:
```
typedef struct {
    int size;       // number of initialized values
    int max_size;   // currently allocated space
    int *data;      // array of values
} Shvector;
```

The data array is initialized with a small size. After it fills up, memory twice its current size is reallocated for it. We picked 2 as a growth factor after comparing other implementations. Most dynamically sized lists use 2 as a growth factor, though there were some arguments for 1.25 and 1.5 being 'optimal'. We decided that unused memory is not that big of an issue and went with the standard 2.

The api is defined with these four functions:
```
/*
 * Creates a new Shvec
 * Returns a new Shvec id (Returns -1 on failure)
 */
int shvec_create();

/*
 * Sets the value at 'index' in the shvec with 'id' to 'value'
 * Appends 0s if the index is larger than the current size
 * Returns 0 on success and 1 on failure
 */
int shvec_set(int id, int index, int value);

/*
* Returns the value at 'index' of shvec 'id'
* If out of bounds, returns 0
*/
int shvec_get(int id, int index);               // Gets the value at 'index' of shvector 'id' (Returns int value, or 0 on failure)

/*
 * Frees the shvec with given 'id' from heap
 * Returns 0 on success, -1 on error
 */
int shvec_free(int id);
```

These four functions are all you need to use shvectors to store data.

Internally, if it needs to write past the current size, `shvec_set()` calls `shvec_append()` to pad the array with 0s and increment `size`. `shvec_append()` checks if it has reached `max_size` and calls `shvec_expand()` (which resizes the shvector) if necessary.

### Design Decisions
An important design decision was to make the library robust and minimize the user's ability to misuse it. For example, if the user treated it like a standard array, when writing past the last element they would write to arbitrary memory instead of growing the array. 
We designed the api to address shvectors with a unique id (which increments from 0). We hold all shvectors in an array, and the id corresponds to the index of the shvector in that array.

There are a few advantages to this approach, mainly that it was easy to implement. It hides the data location from the rest of the application, forcing programmers to use the api, and it keeps track of the memory locations internally, so memory can never be lost.

There are two main disadvantages to this approach. There are a limited number of shvectors the application can use, and it must pre-allocate memory for all shvectors. Fortunately each shvector is only 16 bytes, so allocating 128 shvectors consumes 'only' 2kB of memory. The better way to do this would be to use a root shvector to hold all other shvectors, which would address both problems but add complexity to the library.

Another way we considered addressing new shvectors was to allocate memory for each shvector independently, and then refer to it by its memory address. The disadvantage to this is that we would have to change the api from using `int id` to `long id`. We would also expose the data to the programmers, which might make them misuse the library and be sad if we introduce breaking changes internally.

## Shvalloc:

To write a custom version of malloc, we heavily followed a [tutorial](https://danluu.com/malloc-tutorial/) by Dan Luu. We read through the article and made sure we understood it. Then we ended up pretty much using the code the tutorial provided without much modification; but we believe we learned a lot by following the tutorial line-by-line.

### Implementation

We used the `sbrk` syscall to manipulate the heap size. For example, `sbrk(0)` will increase the heap size by zero then return the heap pointer (which is equivalent to the current heap pointer). `sbrk(sizeof(int))` will increase the heap size by `sizeof(int)` then return the new heap pointer. If sbrk fails(usually due to not enough memory), then it returns `(void *) -1`. 

 `shvalloc` returns a void pointer that points to the region immediately after(+1) of the last block_meta in the heap. To return the pointer, we check whether there is already a free block available to use (by calling the `find_free_block` function which checks the `free` metadata). If not, we call the `request_space` function which allocates a new `block_meta` using the `sbrk` call.
```
void* shvalloc(size_t size)
```
```
struct block_meta *find_free_block(struct block_meta **last, size_t size)
```
```
struct block_meta *request_space(struct block_meta *last, size_t size)
```

`block_meta` is a struct that with a metadata including the `size` of the block, a pointer to the next block, a `free` flag that indicates whether the block is free to use or not, and a `magic` integer for bound-checking and debugging purposes. 
```
struct block_meta {
    size_t size;
    struct block_meta *next;
    int free;
    int magic; 
};
```
`shvfree` function checks the block given by `*ptr` and updates the `free` metadata so that now it's available for future memory allocation.

```
void shvfree(void *ptr)
```

`shvrealloc` checks if the block `*ptr` points at has enough memory left the the reallocation. If the block does have enought space, then it will just return the `*ptr`. If not, it calls shvalloc to allocate a new block, then `memcpy` the data from the old block to the new block.
```
void* shvrealloc(void *ptr, size_t size)
```

## Shchgrp:
To demo our `shvector` library, we made a command-line tool called `shchgrp` (**sh**itty **ch**ained **gr**e**p**) which returns lists of the values matching each regex. We got the inspiration from the unix-command line tool `grep` "for searching plain-text data sets for lines that match a regular expression". Check the [man](https://linux.die.net/man/1/grep) page if you are interested in learning more about the original `grep` tool.

### Example

Below is the code snippet that demonstrates what our `shchgrp` can do. 

```
printf "abc\n123\n456def" | shchgrp "[0-9]" "[a-z]"
Matches to [0-9]:
    123
    456def
Matches to [a-z]:
    abc
    456def
```
### Implementation
First, shchgrp sets up a shvector for each regex (so from the example `[0-9]` and `[a-z]` will each have a shvector that dynamically grows), and then iterates through `stdin` line-by-line. Each line is compared against all regexes provided, and any matches are stored in the respective shvector (delimited by `\n`). After reaching the EOF, each shvector is printed to stdout.

## Project Outcome (as of March 26, 2019):

### *What we have done*

- We have implemented our own dynamically size vector [`shvector`](https://github.com/SeunginLyu/SoftSys-daalloc/blob/master/src/shvec.c).
- We have designed an [API](https://github.com/SeunginLyu/SoftSys-daalloc/blob/master/spec.md) for shvector.
- We have implemented our own `malloc` called [`shvalloc`](https://github.com/SeunginLyu/SoftSys-daalloc/blob/master/src/shvalloc.c) after following a [tutorial](https://danluu.com/malloc-tutorial/). We used the TDD (Test Driven Development) framework and wrote down [tests](https://github.com/SeunginLyu/SoftSys-daalloc/blob/master/src/test_shvalloc.c) before the implementation. 
- We have setup up a CI (Continuous Integration) environment for the team which uses Github and TravisCI. It automatically runs tests whenever someone pushes the code to the online repository. Also, we have been adhering to the rule that a pull request must be reviewed and approved by at least one of the team members before it gets merged to master.
- We have created a [`Makefile`](https://github.com/SeunginLyu/SoftSys-daalloc/blob/master/src/Makefile) that links the relevant components together.
- We have travisCI run all tests when submitting a pull request, and it blocks merging when tests fail.
- We also created a git workflow that requires a code review and approval from a second person before merging into master.
- We wrote unit tests for `shvector` and `shvalloc`
- We made a demo app `shchgrp` that uses `shvectors` to match multiple regexes against stdin.

### *What we wish we had done*

- We wish `shvector` used `shvalloc` instead of `malloc` and passed all our tests. Sadly, shvector throws segmentation faults with our current `shvalloc` implementation. `shvector` is currently using the default `malloc` C provides.
- We wish to update `shvalloc` so that it passes all the tests. It currently does not pass the test when the size is `MAX_SIZE`. It should return NULL but now it returns an address.
- We wish to optimize shvalloc specifically for `shvector`.
- We wish to implement chunking to `shvector` to optimize it for `shvalloc`
- We wish to run performance comparisons of `shvector` vs `array` and `shchgrep` vs multiple `grep`s


## Project Reflection

We have made a solid progress towards our original goals of this project, as demonstrated in our project outcome section. It should be noted that we were more interested in the learning outcomes than the project results.
The main problem with our project as it stands is that we were not able to make shvec use shvalloc, perhaps mostly because we were not able to test shvalloc as well as we would like (for instance, there is no good way to test whether free works, let alone shvfree). Additionally, debugging memory allocation is rather difficult. While we got better at it with this project, we weren't able to fix the particular bug with shvrealloc as it seems to pertain to subtleties around sbrk (which happens to be deprecated on OSX, which might be part of the problem). In retrospect, we could have spent more time making sure that our memory allocation was rock solid before moving to applications.
One interesting aspect of this project was planning. We started with a general direction for the project, but consistently adapted what we chose to do based on our learning goals and feasibility. This "freeform jazz" approach to project definition was helpful to get the most learning out of our project (for example by leading our focus towards workflow), but was not as effective towards making a working or novel project. This feels right for a mid-semester project, and all told we feel like we learned what we set out to learn. 
As we had expected, Trello was not a very helpful planning tool. For a small project like this with biweekly meetings, work getting done during those meetings, and project direction changing often, it was easier to hold what needs to get done in our heads than to deal with the additional overhead of updating the board. Larger projects tend to benefit more

## Resources:

- The [GNU grep code](https://savannah.gnu.org/git/?group=grep) was interesting to read, but way too complicated to use for an implementation reference.
- [A tutorial](https://www.happybearsoftware.com/implementing-a-dynamic-array) on dynamically sized arrays was very useful to reference when implementing shvector.
- [A tutorial](https://danluu.com/malloc-tutorial/) by Dan Luu on writing a custom malloc using sbrk. By following this tutorial, we were able to get a concise and an easy overview of how malloc could be implemented.