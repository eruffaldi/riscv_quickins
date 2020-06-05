#include <stdio.h>

//https://github.com/riscv/riscv-opcodes/blob/master/opcodes-rv32f
// reg-reg (MSB to LSB): func7=[31..25] rs2 rs1 func3=[14..12] rd opcode7=[6..0]
// fadd.s    rd rs1 rs2      31..27=0x00 rm       26..25=0 6..2=0x14 1..0=3
// rm is 3 bit at 12
//		0=rne 1=rtz 2=rdn 3=rup 4=rmm 7=CURRENT
//
// equiv: add	a0,s1,s2
// 
float testfadd(float a, float b) {
  register float p1 asm ("fa0") = a;  // 
  register float p2 asm ("fa1") = b;  // 
  register float result asm("fa0");
  __asm__(
      ""
      ".set rfa0,10\n"
      ".set rfa1,11\n"
      ".set rfa2,12\n"
      ".set op,0x53\n"
      ".set oprm,7\n"
      ".set opf2,0\n"
      // "fadd.s %[result],%1,%2\n"
      ".byte op|((r%[result]&1) <<7),  ((r%[result]>>1)&0xF)|(oprm<<4)|((r%1 "
      "&1) <<7),  ((r%2&0xF) << 4) | ((r%1>>1)&0xF),  ((r%2>>4)&0x1)|opf2\n"
      : [result] "=f"(result)
      : "f"(p1), "f"(p2), "[result]"(result));
  return result;
}

//https://github.com/riscv/riscv-opcodes/blob/master/opcodes-rv32i
// reg-reg (MSB to LSB): func7=[31..25] rs2 rs1 func3=[14..12] rd opcode7=[6..0]
//add     rd rs1 rs2 31..25=0  14..12=0 6..2=0x0C 1..0=3
int testiadd(long a, long b) {
  register int p1 = a;  // asm ("a0")
  register int p2 = b;  // asm ("a1")
  register int result asm("a0");
  __asm__(
      ""
      ".set rs0,8\n"
      ".set rs1,9\n"
      ".set rs2,18\n"
      ".set ra0,10\n"
      ".set ra1,11\n"
      ".set ra2,12\n"
      ".set op,0x33\n"
      ".set opf1,0\n"
      ".set opf2,0\n"
      // "add %[result],%1,%2\n"
      ".byte op|((r%[result]&1) <<7),  ((r%[result]>>1)&0xF)|(opf1<<4)|((r%1 "
      "&1) <<7),  ((r%2&0xF) << 4) | ((r%1>>1)&0xF),  ((r%2>>4)&0x1)|opf2\n"
      : [result] "=r"(result)
      : "r"(p1), "r"(p2), "[result]"(result));
  return result;
}

int main(int argc, char const *argv[])
{
	printf("Hello %d %f\n",testiadd(1,2),testfadd(1.2f,1.3f));
	return 0;
}
