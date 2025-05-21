# Instructions And Layout
## 📝 Registers
| Register | Purpose |
|----------|---------|
| A | General purpose register |
| B | General purpose register |
| C | General purpose register |
| D | General purpose register |
| E | General purpose register |
| F | General purpose register |
| SF | Status flag register |
| R0 | General purpose register |
| R1 | General purpose register | 
| R2 | General purpose register | 
| R3 | General purpose register | 
| R4 | General purpose register | 
| R5 | General purpose register | 
| R6 | General purpose register | 
| R7 | General purpose register | 

## 🔧 Instructions
| Instruction | Description |
|-------------|-------------|
| `mov` | Move data between registers |
| `add` | Add values |
| `sub` | Subtracts values |
| `push` | Push to stack |
| `pop` | Pop from stack |
| `call` | Transfer control to other routine |
| `ret` | Give back control passed on by `call` |
| `inc` | Increase the value in a register by 1 |
| `dec` | Reduce the value in a register by 1 |
| `int` | Standard interrupt to use different hardware routines |
| `je` | Conditional jump |
| `jne` | Conditional jump |
| `jmp` | Jump |
| `cmp` | Compare bytes |
| `halt` | Stop execution |

## 📚 Stack
```
+----------+
|    ...   | <- Stack grows downward
+----------+
```

## 🖥️ How a SYSCALL works
A syscall requires the use of registers:

- It requires a minimum of one register (`A`)
- The first register, A, takes the library for which the syscall is called
    - A = 1 -> Standard file operations
    - etc.
- The second, third and so on, registers take in arguments
- Almost always, the return value will be stored in register A

## Status Flag Register (SF)
1 byte long

* Starting from MSB
    * .0 = CF (carry flag)
    * .1 = PF (parity flag)
    * .2 = AF (Auxiliary flag)
    * .3 = ZF (Zero flag)
    * .4 = SF (Sign flag)
    * .5 = OF (OVerflow flag)
    * .6 = User definable
    * .7 = User definable