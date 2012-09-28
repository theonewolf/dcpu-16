#include "dcpu.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

uint16_t* __dcpu_16_pointer_value(struct DCPU_16_STATE* cpu, enum VALUE val)
{
    switch(val)
    {
        case A:
            return &cpu->REG_A;
        case B:
            return &cpu->REG_B;
        case C:
            return &cpu->REG_C;
        case X:
            return &cpu->REG_X;
        case Y:
            return &cpu->REG_Y;
        case Z:
            return &cpu->REG_Z;
        case I:
            return &cpu->REG_I;
        case J:
            return &cpu->REG_J;
        case D_A:
            return &cpu->RAM[cpu->REG_A];
        case D_B:
            return &cpu->RAM[cpu->REG_B];
        case D_C:
            return &cpu->RAM[cpu->REG_C];
        case D_X:
            return &cpu->RAM[cpu->REG_X];
        case D_Y:
            return &cpu->RAM[cpu->REG_Y];
        case D_Z:
            return &cpu->RAM[cpu->REG_Z];
        case D_I:
            return &cpu->RAM[cpu->REG_I];
        case D_J:
            return &cpu->RAM[cpu->REG_J];
        case ND_A:
            return &cpu->RAM[cpu->RAM[cpu->PC++] + cpu->REG_A];
        case ND_B:
            return &cpu->RAM[cpu->RAM[cpu->PC++] + cpu->REG_B];
        case ND_C:
            return &cpu->RAM[cpu->RAM[cpu->PC++] + cpu->REG_C];
        case ND_X:
            return &cpu->RAM[cpu->RAM[cpu->PC++] + cpu->REG_X];
        case ND_Y:
            return &cpu->RAM[cpu->RAM[cpu->PC++] + cpu->REG_Y];
        case ND_Z:
            return &cpu->RAM[cpu->RAM[cpu->PC++] + cpu->REG_Z];
        case ND_I:
            return &cpu->RAM[cpu->RAM[cpu->PC++] + cpu->REG_I];
        case ND_J:
            return &cpu->RAM[cpu->RAM[cpu->PC++] + cpu->REG_J];
        case POP:
            return &cpu->RAM[cpu->SP++];
        case PEEK:
            return &cpu->RAM[cpu->SP];
        case PUSH:
            return &cpu->RAM[cpu->SP--];
        case SP:
            return &cpu->SP;
        case PC:
            return &cpu->PC;
        case OVER:
            return NULL;
        case NW:
            return &cpu->RAM[cpu->RAM[cpu->PC++]];
        case NW_L:
            return NULL;
        default:
            if (val > 0x20 && val < 0x1f)
                return NULL;
            else
            {
                fprintf(stderr, "Major error getting value.\n");
                exit(1);
            }
    };

    return NULL;
}

uint16_t __dcpu_16_resolve_value(struct DCPU_16_STATE* cpu, enum VALUE val)
{
    switch(val)
    {
        case A:
            return cpu->REG_A;
        case B:
            return cpu->REG_B;
        case C:
            return cpu->REG_C;
        case X:
            return cpu->REG_X;
        case Y:
            return cpu->REG_Y;
        case Z:
            return cpu->REG_Z;
        case I:
            return cpu->REG_I;
        case J:
            return cpu->REG_J;
        case D_A:
            return cpu->RAM[cpu->REG_A];
        case D_B:
            return cpu->RAM[cpu->REG_B];
        case D_C:
            return cpu->RAM[cpu->REG_C];
        case D_X:
            return cpu->RAM[cpu->REG_X];
        case D_Y:
            return cpu->RAM[cpu->REG_Y];
        case D_Z:
            return cpu->RAM[cpu->REG_Z];
        case D_I:
            return cpu->RAM[cpu->REG_I];
        case D_J:
            return cpu->RAM[cpu->REG_J];
        case ND_A:
            return cpu->RAM[cpu->RAM[cpu->PC++] + cpu->REG_A];
        case ND_B:
            return cpu->RAM[cpu->RAM[cpu->PC++] + cpu->REG_B];
        case ND_C:
            return cpu->RAM[cpu->RAM[cpu->PC++] + cpu->REG_C];
        case ND_X:
            return cpu->RAM[cpu->RAM[cpu->PC++] + cpu->REG_X];
        case ND_Y:
            return cpu->RAM[cpu->RAM[cpu->PC++] + cpu->REG_Y];
        case ND_Z:
            return cpu->RAM[cpu->RAM[cpu->PC++] + cpu->REG_Z];
        case ND_I:
            return cpu->RAM[cpu->RAM[cpu->PC++] + cpu->REG_I];
        case ND_J:
            return cpu->RAM[cpu->RAM[cpu->PC++] + cpu->REG_J];
        case POP:
            return cpu->RAM[cpu->SP++];
        case PEEK:
            return cpu->RAM[cpu->SP];
        case PUSH:
            return cpu->RAM[cpu->SP--];
        case SP:
            return cpu->SP;
        case PC:
            return cpu->PC;
        case OVER:
            return cpu->OVERF;
        case NW:
            return cpu->RAM[cpu->RAM[cpu->PC++]];
        case NW_L:
            return cpu->RAM[cpu->PC++];
        default:
            if (val > 0x20 && val < 0x1f)
                return val - 0x20;
            else
            {
                fprintf(stderr, "Major error getting value.\n");
                exit(1);
            }
    };

    return 0xffff;
}

int __set(struct DCPU_16_STATE* cpu, enum VALUE a, enum VALUE b)
{
    uint16_t* pa = __dcpu_16_pointer_value(cpu, a);

    if (pa)
        *pa = __dcpu_16_resolve_value(cpu, b);

    return EXIT_SUCCESS;
}

int __add(struct DCPU_16_STATE* cpu, enum VALUE a, enum VALUE b)
{
    uint16_t* pa = __dcpu_16_pointer_value(cpu, a);

    if (pa)
        *pa = __dcpu_16_resolve_value(cpu, a) +
              __dcpu_16_resolve_value(cpu, b);

    return EXIT_SUCCESS;
}

int __sub(struct DCPU_16_STATE* cpu, enum VALUE a, enum VALUE b)
{
    uint16_t* pa = __dcpu_16_pointer_value(cpu, a);

    if (pa)
        *pa = __dcpu_16_resolve_value(cpu, a) -
              __dcpu_16_resolve_value(cpu, b);

    return EXIT_SUCCESS;
}

int __mul(struct DCPU_16_STATE* cpu, enum VALUE a, enum VALUE b)
{
    uint16_t* pa = __dcpu_16_pointer_value(cpu, a);

    if (pa)
        *pa = __dcpu_16_resolve_value(cpu, a) *
              __dcpu_16_resolve_value(cpu, b);

    return EXIT_SUCCESS;
}

int __div(struct DCPU_16_STATE* cpu, enum VALUE a, enum VALUE b)
{
    uint16_t* pa = __dcpu_16_pointer_value(cpu, a);

    if (pa)
        *pa = __dcpu_16_resolve_value(cpu, a) /
              __dcpu_16_resolve_value(cpu, b);

    return EXIT_SUCCESS;
}

int __mod(struct DCPU_16_STATE* cpu, enum VALUE a, enum VALUE b)
{
    uint16_t* pa = __dcpu_16_pointer_value(cpu, a);

    if (pa)
        *pa = __dcpu_16_resolve_value(cpu, a) %
              __dcpu_16_resolve_value(cpu, b);

    return EXIT_SUCCESS;
}

int __shl(struct DCPU_16_STATE* cpu, enum VALUE a, enum VALUE b)
{
    uint16_t* pa = __dcpu_16_pointer_value(cpu, a);

    if (pa)
        *pa = __dcpu_16_resolve_value(cpu, a) << 
              __dcpu_16_resolve_value(cpu, b);

    return EXIT_SUCCESS;
}

int __shr(struct DCPU_16_STATE* cpu, enum VALUE a, enum VALUE b)
{
    uint16_t* pa = __dcpu_16_pointer_value(cpu, a);

    if (pa)
        *pa = __dcpu_16_resolve_value(cpu, a) >> 
              __dcpu_16_resolve_value(cpu, b);

    return EXIT_SUCCESS;
}

int __and(struct DCPU_16_STATE* cpu, enum VALUE a, enum VALUE b)
{
    uint16_t* pa = __dcpu_16_pointer_value(cpu, a);

    if (pa)
        *pa = __dcpu_16_resolve_value(cpu, a) & 
              __dcpu_16_resolve_value(cpu, b);

    return EXIT_SUCCESS;
}

int __bor(struct DCPU_16_STATE* cpu, enum VALUE a, enum VALUE b)
{
    uint16_t* pa = __dcpu_16_pointer_value(cpu, a);

    if (pa)
        *pa = __dcpu_16_resolve_value(cpu, a) | 
              __dcpu_16_resolve_value(cpu, b);

    return EXIT_SUCCESS;
}

int __xor(struct DCPU_16_STATE* cpu, enum VALUE a, enum VALUE b)
{
    uint16_t* pa = __dcpu_16_pointer_value(cpu, a);

    if (pa)
        *pa = __dcpu_16_resolve_value(cpu, a) ^ 
              __dcpu_16_resolve_value(cpu, b);

    return EXIT_SUCCESS;
}

int __ife(struct DCPU_16_STATE* cpu, enum VALUE a, enum VALUE b)
{
    if (__dcpu_16_resolve_value(cpu, a) != 
        __dcpu_16_resolve_value(cpu, b))
        cpu->PC++;

    return EXIT_SUCCESS;
}

int __ifn(struct DCPU_16_STATE* cpu, enum VALUE a, enum VALUE b)
{
    if (__dcpu_16_resolve_value(cpu, a) == 
        __dcpu_16_resolve_value(cpu, b))
        cpu->PC++;

    return EXIT_SUCCESS;
}

int __ifg(struct DCPU_16_STATE* cpu, enum VALUE a, enum VALUE b)
{
    if (__dcpu_16_resolve_value(cpu, a) < 
        __dcpu_16_resolve_value(cpu, b))
        cpu->PC++;

    return EXIT_SUCCESS;
}

int __ifb(struct DCPU_16_STATE* cpu, enum VALUE a, enum VALUE b)
{
    if ((__dcpu_16_resolve_value(cpu, a) & 
        __dcpu_16_resolve_value(cpu, b)) == 0)
        cpu->PC++;

    return EXIT_SUCCESS;
}

int __dcpu_16_execute_instr(struct DCPU_16_STATE* cpu)
{
    enum OPCODES opcode = 0x000f & cpu->INSTR;
    enum VALUE a        = 0x03f0 & cpu->INSTR;
    enum VALUE b        = 0xfc00 & cpu->INSTR;

    switch(opcode)
    {
        case NB:
            /* handoff */
            break;
        case SET:
            __set(cpu, a, b);
            break;
        case ADD:
            __add(cpu, a, b);
            break;
        case SUB:
            __sub(cpu, a, b);
            break;
        case MUL:
            __mul(cpu, a, b);
            break;
        case DIV:
            __div(cpu, a, b);
            break;
        case MOD:
            __mod(cpu, a, b);
            break;
        case SHL:
            __shl(cpu, a, b);
            break;
        case SHR:
            __shr(cpu, a, b);
            break;
        case AND:
            __and(cpu, a, b);
            break;
        case BOR:
            __bor(cpu, a, b);
            break;
        case XOR:
            __xor(cpu, a, b);
            break;
        case IFE:
            __ife(cpu, a, b);
            break;
        case IFN:
            __ifn(cpu, a, b);
            break;
        case IFG:
            __ifg(cpu, a, b);
            break;
        case IFB:
            __ifb(cpu, a, b);
            break;
        default:
            fprintf(stderr, "Major Exception: Unknown OPCODE encountered.\n");
            return EXIT_FAILURE;
    };

    return EXIT_SUCCESS;
}

int dcpu_16_execute(uint16_t* binary, uint16_t len)
{
    struct DCPU_16_STATE cpu = { 
                                 .TIMESTEP = 0x0000,
                                 .OVERF    = 0x0000,
                                 .PC       = 0x0000,
                                 .SP       = 0xffff,
                                 .REG_A    = 0x0000,
                                 .REG_B    = 0x0000,
                                 .REG_C    = 0x0000,
                                 .REG_X    = 0x0000,
                                 .REG_Y    = 0x0000,
                                 .REG_Z    = 0x0000,
                                 .REG_I    = 0x0000,
                                 .REG_J    = 0x0000
                               };

    memcpy(cpu.RAM, binary, sizeof(*binary) * len);

    for (; cpu.PC < len;)
    {
        cpu.INSTR = cpu.RAM[cpu.PC];
        cpu.PC++;
        if (__dcpu_16_execute_instr(&cpu))
            return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

int main(int argc, char* argv[])
{
    return EXIT_SUCCESS;
}
