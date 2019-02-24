# daalloc
Matthew Beaudouin, Seungin Lyu, Adam Novotny

## A dynamically allocated array for C.

The goal of this project is to make a dynamically allocated array. For out MVP, we will use regular malloc to implement a dynamically allocated array. Then for our MAP(Most Awesome Product), we will go under the hood and use system calls to allocate memory, with an implementation of malloc called 'daalloc' specifically optimized for dynamic arrays.

#### Our learning goals:
- Learn how malloc assigns system memory.
- Learn how to implement dynamic arrays from a low-level persepctive
- Learn how to design an effective library api

#### Process:
1. ~~We will all read the stdlib malloc implementation to have a shared understanding of the material.~~
2. ~~Each of us will find and understand an implementation of a dynamically allocated array.~~
3. We will compare and choose an architecture to start implementing daalloc.
4. Split up tasks and assign them

## API Design:
- What do we call our dynamically allocated array?
- What type will the array hold (int or void*?)
  - void * on the inside, with type in the struct?
- What values does our dalloc need to have in the struct?
- Referencing a dalloc with the struct variable itself or just with an arbitrary int?
- What functions do we need exposed:
  - Create
  - Set
  - Get
  - Free
  - Info (size, type?, ...)
- What function do we need internally:
  - Reallocate space


## Performance comparison:
What metrics do we test to compare the performance of dalloc vs array?
- sequential writes
- sequential reads
- random writes
- random reads

# Assignment:
```
Your project update should answer the following questions (note that some are the same as in the proposal):

1) What is the goal of your project; for example, what do you plan to make, and what should it do?  Identify a lower bound you are confident you can achieve and a stretch goal that is more ambitious.

2) What are your learning goals; that is, what do you intend to achieve by working on this project?

3) What have you done to get started?  Have you found the resources you need, do you have a plan to find them, or do you need help?  If you found any resources you think I should add to the list on the class web page, please email them to me.

4) What are you working on now?  Describe at least three concrete tasks that you are working on, and identify which members of the team are working on them.  For each one, what is the "definition of done"; that is, what will you produce to demonstrate that the task is done?

Audience: Think of your update as a rough draft of your final report.  Target an external audience that wants to know what you did and why.  More specifically, think about students in future versions of SoftSys who might want to work on a related project.  Also think about people who might look at your online portfolio to see what you know, what you can do, and how well you can communicate.
```
