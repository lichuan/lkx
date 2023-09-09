#ifndef __LKX__VM__
#define __LKX__VM__

typedef enum lkx_OPCODE {
  OPCODE_ADD_I64,
  OPCODE_ADD_DBL,
  OPCODE_SUB_I64,
  OPCODE_SUB_DBL,
  OPCODE_MUL_I64,
  OPCODE_MUL_DBL,
  OPCODE_DIV_I64,
  OPCODE_DIV_DBL,
  OPCODE_MOD_I64,
} lkx_OPCODE;

#endif
