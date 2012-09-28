#ifndef __DCPU_16
#define __DCPU_16

#include <stdint.h>

struct DCPU_16_STATE
{
    uint16_t RAM[0x10000];
    uint64_t TIMESTEP;
    uint16_t INSTR;
    uint16_t OVERF;
    uint16_t PC;
    uint16_t SP;

    uint16_t REG_A;
    uint16_t REG_B;
    uint16_t REG_C;
    uint16_t REG_X;
    uint16_t REG_Y;
    uint16_t REG_Z;
    uint16_t REG_I;
    uint16_t REG_J;
};

/* memory from 0x00000 - 0x10000 */

enum VALUE
{
    /* registers */
    A = 0x00, B = 0x01, C = 0x02, X = 0x03,
    Y = 0x04, Z = 0x05, I = 0x06, J = 0x07,

    /* [register] */
    D_A = 0x08, D_B = 0x09, D_C = 0x0a, D_X = 0x0b,
    D_Y = 0x0c, D_Z = 0x0d, D_I = 0x0e, D_J = 0x0f,

    /* [next word + register] */
    /* next word == [PC++] */
    ND_A = 0x10, ND_B = 0x11, ND_C = 0x12, ND_X = 0x13,
    ND_Y = 0x14, ND_Z = 0x15, ND_I = 0x16, ND_J = 0x17,

    POP  = 0x18, /* [SP++] */
    PEEK = 0x19, /* [SP] */
    PUSH = 0x1a, /* [--SP] */
    SP   = 0x1b,
    PC   = 0x1c,
    OVER = 0x1d,
    NW   = 0x1e, /* [next word] == [PC++] */
    NW_L = 0x1f  /* next word literal */
                 /* 0x20 - 0x3f == 0x00-0x1f literals */ 
};

enum OPCODES
{
    NB  = 0x00, /* non-basic instruction - see below */
    SET = 0x01, /* SET a, b - sets a to b */
    ADD = 0x02, /* ADD a, b - sets a to a+b, sets O to 0x0001 if there's an
                              overflow, 0x0 otherwise */
    SUB = 0x03, /* SUB a, b - sets a to a-b, sets O to 0xffff if there's an
                   underflow, 0x0 otherwise */
    MUL = 0x04, /* MUL a, b - sets a to a*b, sets O to ((a*b)>>16)&0xffff */
    DIV = 0x05, /* DIV a, b - sets a to a/b, sets O to ((a<<16)/b)&0xffff. if
                          b==0, sets a and O to 0 instead. */
    MOD = 0x06, /* MOD a, b - sets a to a%b. if b==0, sets a to 0 instead. */
    SHL = 0x07, /* SHL a, b - sets a to a<<b, sets O to ((a<<b)>>16)&0xffff */
    SHR = 0x08, /* SHR a, b - sets a to a>>b, sets O to ((a<<16)>>b)&0xffff */
    AND = 0x09, /* AND a, b - sets a to a&b */
    BOR = 0x0a, /* BOR a, b - sets a to a|b */
    XOR = 0x0b, /* XOR a, b - sets a to a^b */
    IFE = 0x0c, /* IFE a, b - performs next instruction only if a==b */
    IFN = 0x0d, /* IFN a, b - performs next instruction only if a!=b */
    IFG = 0x0e, /* IFG a, b - performs next instruction only if a>b */
    IFB = 0x0f  /* IFB a, b - performs next instruction only if (a&b)!=0 */
};

enum NB_OPCODES
{
                /* 0x00: reserved for future expansion */
    JSR = 0x01  /* JSR a - pushes the address of the next instruction to the
                           stack, then sets PC to a */
                /* 0x02-0x3f: reserved */
};

int dcpu_16_execute(uint16_t* binary, uint16_t len);

#endif
