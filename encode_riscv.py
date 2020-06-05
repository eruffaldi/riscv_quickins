
#import pandas as pd
#import numpy as np
import argparse
import os
import sys
import binascii

def main():
	parser = argparse.ArgumentParser(description='Process some integers.')
	parser.add_argument('r')
	#parser.add_argument('output')
	parser.add_argument('-x',action="store_true")
	args = parser.parse_args()

regs = dict(a0=10,a1=11,s1=12,s2=18,x1=1,x2=2,x3=3)
ops = dict(add=(0x33,0))
#add     rd rs1 rs2 31..25=0  14..12=0 6..2=0x0C 1..0=3
#b3 04 a9 00
#
#add	s1,s2,a0
def encode(opm,rd,r1,r2):
	op,func = ops[opm]
	rdi = regs[rd]
	r1i = regs[r1]
	r2i = regs[r2]
	#
	w = (rdi & 0x1f) << 7 | (r1i & 0x1f) << 15 | (r2i & 0x1f) << 20
	# func is 7+3
	f1 = func & 7
	f2 = func & ~7

	# byte0: op | rdi[0:1]@7
	# byte1: rid[1:]@0 | func[0:3]
	alt = op|  ((rdi&1) <<7) ,  ((rdi>>1)&0xF)|(f1<<4)|((r1i&1) <<7),  ((r2i&0xF) << 4) | ((r1i>>1)&0xF),  ((r2i>>4)&0x1)|f2
	r = w | op | (f1 << 12) | (f2<<25)
	a = [hex(x) for x in alt]
	a.reverse()
	print(hex(r),a)

	return r
if __name__ == '__main__':
	#a0,s1,s2 = 33852401
	#a0,x1,x2 = 33852000
	print(hex(encode("add","a0","x1","x2")))

#as --64 -o test.o test.S
#ld -Ttext 200000 --oformat binary-o test.bin test.o
#