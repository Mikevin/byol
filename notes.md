#Notes

## General
* Using CMAKE instead of commandline usage of cc to learn a bit of CMAKE and increase productivity in CLion.

## Chapter 7

### Ast struct 

```c
typedef struct mpc_ast_t {
  char* tag;
  char* contents;
  mpc_state_t state;
  int children_num;
  struct mpc_ast_t** children;
} mpc_ast_t;
```

| Field        | Use           | Example  |
| ------------- |:-------------:| -----:|
| tag     | Shows rules used to parse type | expr&#124;number&#124;regex |
| contents      | actual content of node       |   '*' |
| state | unused      |     |
| 

tag

Use: Shows rules used to parse type
Example: expr|number|regex

contents
Example