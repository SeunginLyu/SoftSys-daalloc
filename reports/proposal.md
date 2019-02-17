# daalloc
Matthew Beaudouin, Seungin Lyu, Adam Novotny

## A dynamically allocated array for C.

The goal of this project is to make a dynamically allocated array. For out MVP, we will use regular malloc to implement a dynamically allocated array. Then for our MAP(Most Awesome Product), we will go under the hood and use system calls to allocate memory, with an implementation of malloc called 'daalloc' specifically optimized for dynamic arrays.

#### Our learning goals:
- Learn how malloc works. 
- Learn how to implement dynamic arrays from a low-level persepctive
  - We have found [blog posts](http://gee.cs.oswego.edu/dl/html/malloc.html) about writing a custom memory allocator, and multiple implementations of dynamic arrays. We will find other resources as needed.

#### First steps:
1. We will all read the stdlib malloc implementation to have a shared understanding of the material.
2. Each of us will find and understand an implementation of a dynamically allocated array.
3. We will compare and choose an architecture to start implementing daalloc.