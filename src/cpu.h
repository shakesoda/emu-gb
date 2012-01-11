#include <stdint.h>

typedef uint8_t byte;
typedef uint16_t word;

struct {
  /*
   * (adapted from the GB CPU manual)
   * /-------\
   * | A |[F]|
   * |---|---|
   * | B + C |
   * |---|---|
   * | D + E |
   * |---|---|
   * | H + L |
   * \-------/
   * 
   * Registers A, B, C, D, E, H, and L can all be used as regular data stores;
   * however it is important to note that side-by-side registers can be
   * (fairly inexpensively) used as pairs (i.e. BC, DE, HL) to act as pseudo
   * 16-bit registers.
   *
   * The F register stores flags set by previous ops (i.e. carry, compare)
   *
   * /------------------------\
   * | 7 | 6 | 5 | 4 | [3-0]  | (bit)
   * | Z | N | H | C | unused | (flag)
   * \------------------------/
   *
   * Flag descriptions:
   * Z zero - set when result of math op is zero or values match using cp
   * N subtract - set if subtraction was performed in the last math op
   * H half carry - set if a carry occurred from the lower nb in last math op
   * C carry - set if carry occurred from the last math op or register A is
   *   the smaller value when execuring the CP instruction.
   *
   * (nb = nibble, half byte)
   */

  /* general registers */
  byte a, f, b, c, d, e, h, l;

  /* stack pointer and program counter */
  word sp, pc;
} r;

int cpu_init()
{
  r.pc = 0x0100;
  r.sp = 0xFFFE;

  return 0;
}
