#include "../include/jit.h"

/* cl /I ..\sljit /DSLJIT_CONFIG_AUTO=1 add3.c ..\sljit\sljitLir.c */

typedef int (*func_add3_t)(int a, int b, int c); 

func_add3_t generate_code(struct sljit_compiler *C)
{
    /* To support almost all architechtures */
    sljit_emit_enter(C, 0,
        SLJIT_ARG1(SW) | SLJIT_ARG2(SW) | SLJIT_ARG3(SW),
        6,  /* scratch  : temporary R0-R5   */
        6,  /* saved    : safety    S0-S5   */
        6,  /* fscratch : temporary FR0-FR5 */
        0,  /* fsaved   : safety    -       */
        0   /* local    :                   */
    );

    /* Arguments are SLJIT_S0, SLJIT_S1, and SLJIT_S2 */
    sljit_emit_op2(C, SLJIT_ADD, SLJIT_R0, 0, SLJIT_S0, 0, SLJIT_S1, 0);
    sljit_emit_op2(C, SLJIT_ADD, SLJIT_R0, 0, SLJIT_R0, 0, SLJIT_S2, 0);

    /* end of code */
    sljit_emit_return(C, SLJIT_MOV, SLJIT_R0, 0);
    return (func_add3_t)finalize_code(C);
}

int main(void)
{
    /* set up */
    struct sljit_compiler *C = new_compiler();

    /* generate code */
    func_add3_t code = generate_code(C);
    int r = code(1, 2, 3);
    printf("r = %d\n", r);

    /* clean up */
    free_code(code);
    return 0;
}
