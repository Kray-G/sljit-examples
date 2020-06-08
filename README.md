# sljit-examples

## What is this?

This is just my reminder project.
I will write how to use sljit and a sample code as a useful code.

## Basic Usage

### Template

Here is the template to use sljit.

```c
#include "sljitLir.h"

int main(void)
{
    /* set up */
    struct sljit_compiler *C = sljit_create_compiler();

    /* To support almost all architechtures */
    sljit_emit_enter(C, 0,
        SLJIT_ARG1(SW),         /* argument type */
        6,  /* scratch  : temporary R0-R5   */
        6,  /* saved    : safety    S0-S5   */
        6,  /* fscratch : temporary FR0-FR6 */
        0,  /* fsaved   : safety    -       */
        0   /* local    :                   */
    );

    /* end of code */
    sljit_emit_return(C, SLJIT_MOV, SLJIT_IMM, 0);

    /* generate code */
    void *code = sljit_generate_code(C);

    /* clean up */
    sljit_free_compiler(C);
    sljit_free_code(code);
    return 0;
}
```

### Registers

|   Registers    |                                                      Meaning                                                       |
| -------------- | ------------------------------------------------------------------------------------------------------------------ |
| `SLJIT_S[0-9]` | **Saved registers** means 'safe' registers. registers whose preserve their values across function calls.           |
| `SLJIT_R[0-9]` | **Scratch registers** means 'temporary used'. Registers whose may not preserve their values across function calls. |

### Operands


|  First parameter   | Second parameter |                                                         Meaning                                                          |
| ------------------ | ---------------- | ------------------------------------------------------------------------------------------------------------------------ |
| SLJIT_R*, SLJIT_S* | 0                | Temp/saved registers                                                                                                     |
| SLJIT_IMM          | Number           | Immediate number                                                                                                         |
| SLJIT_MEM          | Address          | In-mem data with Absolute address                                                                                        |
| SLJIT_MEM1(r)      | Offset           | In-mem data in [R + offset]                                                                                              |
| SLJIT_MEM2(r1, r2) | Shift(size)      | In-mem array, R1 as base address, R2 as index,<br />Shift as size(0 for bytes, 1 for shorts, 2 for 4bytes, 3 for 8bytes) |




### Instructions

#### sljit_emit_op1

|SLJIT_MOV|

#### sljit_emit_op2

|SLJIT_ADD|
|SLJIT_SUB|
|SLJIT_MUL|

#### sljit_emit_fop1

#### sljit_emit_fop2
