# Meeting Notes

## 2/24:
### Agenda:
- Make API and block diagram of dalloc
- What will be our pull request process?
  - Peer programming + 3rd reviewer?
  - [x] Independent implementations + 2 peer reviewers?
  - Anything goes just merge it in?
- Create kanban cards and assign them
- How to continually write `update.md`?
```
typedef enum {
    CHAR,
    INT,
    FLOAT,
    DOUBLE
} TYPE;

void foo(TYPE t, void* x){
    switch(t){
        case CHAR:
            (char*)x;
            break;
        case INT:
            (int*)x;
            break;
         ...
    }
}
```

![image1](./Feb_24_1.png)
![image2](./Feb_24_2.png)
### Next Meeting (3/1):
- Plan to polish `update.md` (continually?)
- Expand scope of project
