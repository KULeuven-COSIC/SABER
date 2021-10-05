#!/usr/bin/env python3

import sys
from functools import wraps
from math import ceil, floor
from collections import defaultdict


def toomcook_256(pntA, pntB, pntC):
	instructions = toomcook_256_64(pntA, pntB, pntC)
	for ins in instructions:
		yield ins

def toomcook_256_64(pntA, pntB, pntC):
	r0 = "r4"; r1 = "r5"; r2 = "r6"; r3 = "r7";
	r4 = "r8"; r5 = "r9"; r6 = "r10"; r7 = "r11";
	r8 = "r12"; r9 = "r14";
	tmp0 = "r0"; tmp1 = "r3";
	sp = "sp";

	# TOOM COOK EVALUATION
	for i in range(32):
		# A
		yield f"ldr {r0},[{pntA},#{i*16}]"
		yield f"ldr {r2},[{pntA},#{i*16+8}]"
		yield f"ldr {r1},[{pntA},#{i*16+4}]"
		yield f"ldr {r3},[{pntA},#{i*16+12}]"
		yield f"pkhbt {r8}, {r0}, {r2}, lsl #16"
		yield f"pkhtb {r2}, {r2}, {r0}, asr #16"
		yield f"pkhbt {r9}, {r1}, {r3}, lsl #16"
		yield f"pkhtb {r3}, {r3}, {r1}, asr #16"
		yield f"uadd16 {r4}, {r8}, {r2}"
		yield f"uadd16 {r5}, {r9}, {r3}"
		yield f"uadd16 {r6}, {r4}, {r5}"
		yield f"usub16 {r7}, {r4}, {r5}"
		yield f"str {r6}, [{sp}, #{256+i*4}]"
		yield f"str {r7}, [{sp}, #{384+i*4}]"
		yield f"uadd16 {r4}, {r8}, {r8}"
		yield f"uadd16 {r4}, {r4}, {r4}"
		yield f"uadd16 {r4}, {r4}, {r2}"
		yield f"uadd16 {r4}, {r4}, {r4}"
		yield f"uadd16 {r5}, {r9}, {r9}"
		yield f"uadd16 {r5}, {r5}, {r5}"
		yield f"uadd16 {r5}, {r5}, {r3}"
		yield f"uadd16 {r6}, {r4}, {r5}"
		yield f"usub16 {r7}, {r4}, {r5}"
		yield f"str {r6}, [{sp}, #{512+i*4}]"
		yield f"str {r7}, [{sp}, #{640+i*4}]"
		yield f"uadd16 {r4}, {r3}, {r3}"
		yield f"uadd16 {r4}, {r4}, {r2}"
		yield f"uadd16 {r4}, {r4}, {r4}"
		yield f"uadd16 {r4}, {r4}, {r9}"
		yield f"uadd16 {r4}, {r4}, {r4}"
		yield f"uadd16 {r4}, {r4}, {r8}"
		yield f"str {r4}, [{sp}, #{128+i*4}]"
		yield f"str {r8}, [{sp}, #{768+i*4}]"
		yield f"str {r3}, [{sp}, #{0+i*4}]"
	#yield f"add {sp}, {sp}, #{896}"
	for i in range(32):
		# B
		yield f"ldr {r0},[{pntB},#{i*16}]"
		yield f"ldr {r2},[{pntB},#{i*16+8}]"
		yield f"ldr {r1},[{pntB},#{i*16+4}]"
		yield f"ldr {r3},[{pntB},#{i*16+12}]"
		yield f"pkhbt {r8}, {r0}, {r2}, lsl #16"
		yield f"pkhtb {r2}, {r2}, {r0}, asr #16"
		yield f"pkhbt {r9}, {r1}, {r3}, lsl #16"
		yield f"pkhtb {r3}, {r3}, {r1}, asr #16"
		yield f"uadd16 {r4}, {r8}, {r2}"
		yield f"uadd16 {r5}, {r9}, {r3}"
		yield f"uadd16 {r6}, {r4}, {r5}"
		yield f"usub16 {r7}, {r4}, {r5}"
		yield f"str {r6}, [{sp}, #{1024+i*4}]"
		yield f"str {r7}, [{sp}, #{1152+i*4}]"
		yield f"uadd16 {r4}, {r8}, {r8}"
		yield f"uadd16 {r4}, {r4}, {r4}"
		yield f"uadd16 {r4}, {r4}, {r2}"
		yield f"uadd16 {r4}, {r4}, {r4}"
		yield f"uadd16 {r5}, {r9}, {r9}"
		yield f"uadd16 {r5}, {r5}, {r5}"
		yield f"uadd16 {r5}, {r5}, {r3}"
		yield f"uadd16 {r6}, {r4}, {r5}"
		yield f"usub16 {r7}, {r4}, {r5}"
		yield f"str {r6}, [{sp}, #{1280+i*4}]"
		yield f"str {r7}, [{sp}, #{1408+i*4}]"
		yield f"uadd16 {r4}, {r3}, {r3}"
		yield f"uadd16 {r4}, {r4}, {r2}"
		yield f"uadd16 {r4}, {r4}, {r4}"
		yield f"uadd16 {r4}, {r4}, {r9}"
		yield f"uadd16 {r4}, {r4}, {r4}"
		yield f"uadd16 {r4}, {r4}, {r8}"
		yield f"str {r4}, [{sp}, #{896+i*4}]"
		yield f"str {r8}, [{sp}, #{1536+i*4}]"
		yield f"str {r3}, [{pntB}, #{0+i*4}]"
	#yield f"sub {sp}, {sp}, #{896}"
	# POINT-VALUE MULTIPLICATION
	yield f"mov r3, {sp}"
	yield f"push {{r0-r2}}"
	yield f"mov r0, r3"
	yield f"add r2, r1, #128"
	yield f"add r3, r1, #256"
	yield f"bl kara_strd_mem_asm"
	yield f"mov r2, r1"
	yield f"add r1, r0, #896"
	yield f"add r0, r0, #128"
	yield f"bl kara_strd_mem_asm"
	yield f"mov r2, r1"
	yield f"add r1, r1, #128"
	yield f"add r0, r0, #128"
	yield f"bl kara_strd_mem_asm"
	yield f"mov r2, r1"
	yield f"add r1, r1, #128"
	yield f"add r0, r0, #128"
	yield f"bl kara_strd_mem_asm"
	yield f"mov r2, r1"
	yield f"add r1, r1, #128"
	yield f"add r0, r0, #128"
	yield f"bl kara_strd_mem_asm"
	yield f"mov r2, r1"
	yield f"add r1, r1, #128"
	yield f"add r0, r0, #128"
	yield f"bl kara_strd_mem_asm"
	yield f"mov r2, r1"
	yield f"add r1, r1, #128"
	yield f"add r0, r0, #128"
	yield f"bl kara_strd_mem_asm"
	yield f"pop {{r0-r2}}"
	# TOOM COOK INTERPOLATION
	#yield f"add {sp}, {sp}, #{896}"
	for i in range(32):
		if i == 0:
			yield f"eor r9, r9, r9"
			yield f"eor r8, r8, r8"
		yield f"ldr {r0},[{pntB},#{128+i*4}]"
		yield f"ldr {r1},[{pntB},#{i*4}]"
		yield f"ldr {r2},[{sp},#{896+i*4}]"
		yield f"ldr {r3},[{sp},#{1024+i*4}]"
		yield f"ldr {r4},[{sp},#{1152+i*4}]"
		yield f"ldr {r5},[{sp},#{1280+i*4}]"
		yield f"ldr {r6},[{sp},#{1408+i*4}]"
		yield f"uadd16 {r1}, {r1}, {r4}"
		yield f"usub16 {r5}, {r5}, {r4}"
		yield f"usub16 {r3}, {r3}, {r2}"
		yield f"usub16 {r4}, {r4}, {r0}"
		yield f"lsr {tmp0}, {r6}, #16"
		yield f"lsl {tmp1}, {r6}, #6"
		yield f"pkhbt {tmp1}, {tmp1}, {tmp0}, lsl #22"
		yield f"usub16 {r4}, {r4}, {tmp1}"
		yield f"lsl {tmp0}, {r3}, #16"
		yield f"lsr {tmp1}, {r3}, #1"
		yield f"pkhtb {r3}, {tmp1}, {tmp0}, asr #17"
		yield f"uadd16 {r2}, {r2}, {r3}"
		yield f"lsr {tmp0}, {r4}, #16"
		yield f"lsl {tmp1}, {r4}, #1"
		yield f"pkhbt {tmp1}, {tmp1}, {tmp0}, lsl #17"
		yield f"uadd16 {r4}, {r5}, {tmp1}"
		yield f"lsr {tmp0}, {r2}, #16"
		yield f"lsl {tmp1}, {r2}, #6"
		yield f"pkhbt {tmp1}, {tmp1}, {tmp0}, lsl #22"
		yield f"uadd16 {tmp1}, {r2}, {tmp1}"
		yield f"usub16 {r1}, {r1}, {tmp1}"
		yield f"usub16 {r2}, {r2}, {r6}"
		yield f"usub16 {r2}, {r2}, {r0}"
		yield f"mov {tmp1}, #45"
		yield f"smulbb {tmp0}, {r2}, {tmp1}"
		yield f"smultb {tmp1}, {r2}, {tmp1}"
		yield f"pkhbt {tmp1}, {tmp0}, {tmp1}, lsl #16"
		yield f"uadd16 {r1}, {r1}, {tmp1}"
		yield f"lsr {tmp0}, {r2}, #16"
		yield f"lsl {tmp1}, {r2}, #3"
		yield f"pkhbt {tmp1}, {tmp1}, {tmp0}, lsl #19"
		yield f"usub16 {r4}, {r4}, {tmp1}"
		yield f"movw {tmp1}, #43691"
		yield f"smulbb {tmp0}, {r4}, {tmp1}"
		yield f"smultb {tmp1}, {r4}, {tmp1}"
		yield f"pkhbt {tmp1}, {tmp0}, {tmp1}, lsl #16"
		yield f"lsl {tmp0}, {tmp1}, #16"
		yield f"lsr {tmp1}, {tmp1}, #3"
		yield f"pkhtb {r4}, {tmp1}, {tmp0}, asr #19"
		yield f"uadd16 {r5}, {r1}, {r5}"
		yield f"lsr {tmp0}, {r3}, #16"
		yield f"lsl {tmp1}, {r3}, #4"
		yield f"pkhbt {tmp1}, {tmp1}, {tmp0}, lsl #20"
		yield f"uadd16 {r1}, {r1}, {tmp1}"
		yield f"movw {tmp1}, #36409"
		yield f"smulbb {tmp0}, {r1}, {tmp1}"
		yield f"smultb {tmp1}, {r1}, {tmp1}"
		yield f"pkhbt {tmp1}, {tmp0}, {tmp1}, lsl #16"
		yield f"lsl {tmp0}, {tmp1}, #16"
		yield f"lsr {tmp1}, {tmp1}, #1"
		yield f"pkhtb {r1}, {tmp1}, {tmp0}, asr #17"
		yield f"usub16 {r2}, {r2}, {r4}"
		yield f"uadd16 {r3}, {r3}, {r1}"
		yield f"mov {tmp1}, #0"
		yield f"usub16 {r3}, {tmp1}, {r3}"
		yield f"mov {tmp1}, #30"
		yield f"smulbb {tmp0}, {r1}, {tmp1}"
		yield f"smultb {tmp1}, {r1}, {tmp1}"
		yield f"pkhbt {tmp1}, {tmp0}, {tmp1}, lsl #16"
		yield f"usub16 {r5}, {tmp1}, {r5}"
		yield f"movw {tmp1}, #61167"
		yield f"smulbb {tmp0}, {r5}, {tmp1}"
		yield f"smultb {tmp1}, {r5}, {tmp1}"
		yield f"pkhbt {tmp1}, {tmp0}, {tmp1}, lsl #16"
		yield f"lsl {tmp0}, {tmp1}, #16"
		#r5 = ((30*r1 - r5)*SABER_TC_INV15>>2);
		yield f"lsr {tmp1}, {tmp1}, #2"
		yield f"pkhtb {r5}, {tmp1}, {tmp0}, asr #18"
		yield f"usub16 {r1}, {r1}, {r5}"
		# ACCUMULATE RESULT
		yield f"pkhbt {tmp0}, {r6}, {r5}, lsl #16"
		yield f"pkhbt {tmp1}, {r4}, {r3}, lsl #16"
		yield f"uadd16 {tmp0}, {tmp0}, {r9}"
		yield f"uadd16 {tmp1}, {tmp1}, {r8}"
		yield f"pkhtb {r9}, {r1}, {r2}, asr #16"
		yield f"pkhtb {r8}, {r8}, {r0}, asr #16"
		yield f"pkhbt {r1}, {r2}, {r1}, lsl #16"
		yield f"pkhbt {r0}, {r0}, {r8}"
		yield f"pkhtb {r5}, {r5}, {r6}, asr #16"
		yield f"pkhtb {r6}, {r3}, {r4}, asr #16"
		yield f"uadd16 {r5}, {r5}, {r1}"
		yield f"uadd16 {r6}, {r6}, {r0}"
		yield f"ldr {r0}, [{pntC}, #{i*16}]"
		yield f"ldr {r1}, [{pntC}, #{i*16+4}]"
		yield f"ldr {r2}, [{pntC}, #{i*16+8}]"
		yield f"ldr {r7}, [{pntC}, #{i*16+12}]"
		yield f"uadd16 {r0}, {r0}, {tmp0}"
		yield f"str {r0}, [{pntC}, #{i*16}]"
		yield f"uadd16 {r1}, {r1}, {tmp1}"
		yield f"str {r1}, [{pntC}, #{i*16+4}]"
		yield f"uadd16 {r2}, {r2}, {r5}"
		yield f"str {r2}, [{pntC}, #{i*16+8}]"
		yield f"uadd16 {r7}, {r7}, {r6}"
		yield f"str {r7}, [{pntC}, #{i*16+12}]"
	# res[0] -= r2; res[1] -= r1; res[2] -= r0;
	yield f"ldr {tmp0}, [{pntC}, #{0}]"
	yield f"ldr {tmp1}, [{pntC}, #{4}]"
	yield f"usub16 {tmp0}, {tmp0}, {r9}"
	yield f"str {tmp0}, [{pntC}, #{0}]"
	yield f"usub16 {tmp1}, {tmp1}, {r8}"
	yield f"str {tmp1}, [{pntC}, #{4}]"
	#yield f"sub {sp}, {sp}, #{896}"


def schoolbook_from8x8(SRC1, SRC2, DEST, n):
	instructions = schoolbook_from_next_8x8(SRC1, SRC2, DEST, 8*ceil(n / 8))
	for ins in instructions:
		yield ins

def schoolbook_from_next_8x8(SRC1, SRC2, DEST, n):
	a0 = "r6"; a1 = "r12"; a2 = "r3"; a3 = "r10";
	b0 = "r7"; b1 = "r8"; b2 = "r4"; b3 = "r14";
	tmp1 = "r9"; c = "r5";
	tmp0 = "r11";
	tmp2 = "r2";
	tmp3 = "r1";

	# {DEST} cannot be assumed to be zeroed
	# to improve performance, we initialize them on-the-fly by
	# keeping track which coeffs have already been set
	is_initialized = dict()

	for i in range(n//8):
		yield f"ldr {a0},[{SRC1},#{i*16}]"
		yield f"ldr {a1},[{SRC1},#{i*16+4}]"
		yield f"ldr {a2},[{SRC1},#{i*16+8}]"
		yield f"ldr {a3},[{SRC1},#{i*16+12}]"

		#	   --- ---				 --- ---
		#	  | 3 | 1 |				| 4 | 1 |
		#   --- --- ---  -->	 --- --- ---
		#  | 4 | 2 |			| 3 | 2 |
		#   --- ---				--- ---
		# so we can keep the coeffs of {SRC2} = {SRC1+32} in registers when 2->3
		if i%2 == 0:
			r = range(n//8)
		else:
			r = range(n//8-1,-1, -1)
		for j in r:
			if i == 0 or (i%2 == 0 and j != 0) or (i%2 == 1 and j != n//8-1):
				yield f"ldr {b0}, [{SRC1},#{j*16+2*n}]"
				yield f"ldr {b1}, [{SRC1},#{j*16+4+2*n}]"
				yield f"ldr {b2}, [{SRC1},#{j*16+8+2*n}]"
				yield f"ldr {b3}, [{SRC1},#{j*16+12+2*n}]"
			yield f"push {{{SRC1}}}"  # this clears up r1

			index = i*16+j*16;

			# c0, c1
			if index % (2*n) in is_initialized:
				if index % (2*n) == index:
					yield f"ldr {tmp1}, [{DEST},#{index % (2*n)}]"
				else:
					yield f"ldr {tmp2}, [{DEST},#{index % (2*n)}]"


			if (index+4) % (2*n) in is_initialized:
				if (index+4) % (2*n) == (index+4):
					yield f"ldr {c}, [{DEST},#{(index+4) % (2*n)}]"
				else:
					yield f"ldr {tmp3}, [{DEST},#{(index+4) % (2*n)}]"

			if (index % (2*n) in is_initialized) and (index % (2*n) == index):
				yield f"lsr {tmp0}, {tmp1}, #16"
				yield f"smlabb {tmp1}, {b0}, {a0}, {tmp1}"
				yield f"smladx {tmp0}, {b0}, {a0}, {tmp0}"
			else:
				yield f"smulbb {tmp1}, {b0}, {a0}"
				yield f"smuadx {tmp0}, {b0}, {a0}"
				is_initialized[index % (2*n)] = True

			yield f"pkhbt {tmp1}, {tmp1}, {tmp0}, lsl#16"
			if (index % (2*n) in is_initialized) and (index % (2*n) != index):
				yield f"usub16 {tmp1}, {tmp2}, {tmp1}"
			yield f"str {tmp1}, [{DEST}, #{index % (2*n)}]"

			# c2, c3
			if ((index+4) % (2*n) in is_initialized) and ((index+4) % (2*n) == (index+4)):
				yield f"lsr {tmp0},{c},#16"
				yield f"smladx {tmp0}, {b0}, {a1}, {tmp0}"
				yield f"smlabb {c}, {b0}, {a1}, {c}"
			else:
				yield f"smuadx {tmp0}, {b0}, {a1}"
				yield f"smulbb {c}, {b0}, {a1}"
				is_initialized[(index+4) % (2*n)] = True

			yield f"pkhbt {tmp1}, {b1}, {b0}"
			yield f"smladx {tmp0}, {b1}, {a0}, {tmp0}"
			yield f"smlad {c}, {tmp1}, {a0}, {c}"
			yield f"pkhbt {tmp0}, {c}, {tmp0}, lsl #16"

			if ((index+4) % (2*n) in is_initialized) and ((index+4) % (2*n) != (index+4)):
				yield f"usub16 {tmp0}, {tmp3}, {tmp0}"

			if (index+8) % (2*n) in is_initialized:
				if (index+8) % (2*n) == (index+8):
					yield f"ldr {c}, [{DEST},#{(index+8) % (2*n)}]"
				else:
					yield f"ldr {tmp3}, [{DEST},#{(index+8) % (2*n)}]"

			# stores after loads are pipelined and thus take 1 instead of 2 cycles
			yield f"str {tmp0}, [{DEST},#{(index+4) % (2*n)}]"


			# c4, c5
			if ((index+8) % (2*n) in is_initialized) and ((index+8) % (2*n) == (index+8)):
				yield f"lsr {tmp0},{c},#16"
				yield f"smlabb {c}, {a2}, {b0}, {c}"
				yield f"smladx {tmp0}, {a2}, {b0}, {tmp0}"
			else:
				yield f"smulbb {c}, {a2}, {b0}"
				yield f"smuadx {tmp0}, {a2}, {b0}"
				is_initialized[(index+8) % (2*n)] = True


			yield f"smlad {c}, {tmp1}, {a1}, {c}"
			yield f"pkhbt {tmp2}, {b2}, {b1}"
			yield f"smlad {c}, {tmp2}, {a0}, {c}"

			yield f"smladx {tmp0}, {b1}, {a1}, {tmp0}"
			yield f"smladx {tmp0}, {b2}, {a0}, {tmp0}"
			yield f"pkhbt {tmp0}, {c}, {tmp0}, lsl #16"
			if ((index+8) % (2*n) in is_initialized) and ((index+8) % (2*n) != (index+8)):
				yield f"usub16 {tmp0}, {tmp3}, {tmp0}"
			if ((index+12) % (2*n) in is_initialized) and ((index+12) % (2*n) == (index+12)):
				yield f"ldr {c}, [{DEST},#{(index+12) % (2*n)}]"
			yield f"str {tmp0}, [{DEST},#{(index+8) % (2*n)}]"

			# c6, c7

			if ((index+12) % (2*n) in is_initialized) and ((index+12) % (2*n) == (index+12)):
				yield f"lsr {tmp0}, {c}, #16"
				yield f"smlabb {c}, {a3}, {b0}, {c}"
				yield f"smladx {tmp0}, {a3}, {b0}, {tmp0}"
			else:
				yield f"smulbb {c}, {a3}, {b0}"
				yield f"smuadx {tmp0}, {a3}, {b0}"
				is_initialized[(index+12) % (2*n)] = True

			yield f"smlad {c}, {a1}, {tmp2}, {c}"
			#yield f"pkhbt {tmp1}, {b1}, {b0}"
			yield f"smlad {c}, {a2}, {tmp1}, {c}"
			yield f"pkhbt {tmp3}, {b3}, {b2}"
			yield f"smlad {c}, {a0}, {tmp3}, {c}"

			if ((index+12) % (2*n) in is_initialized) and ((index+12) % (2*n) != (index+12)):
				yield f"ldr {tmp1}, [{DEST},#{(index+12) % (2*n)}]"

			yield f"smladx {tmp0}, {a2}, {b1}, {tmp0}"
			yield f"smladx {tmp0}, {a1}, {b2}, {tmp0}"
			yield f"smladx {tmp0}, {a0}, {b3}, {tmp0}"
			yield f"pkhbt {tmp0}, {c}, {tmp0}, lsl #16"
			if ((index+12) % (2*n) in is_initialized) and ((index+12) % (2*n) != (index+12)):
				yield f"usub16 {tmp0}, {tmp1}, {tmp0}"
			if ((index+16) % (2*n) in is_initialized) and ((index+16) % (2*n) == (index+16)):
				yield f"ldr {c}, [{DEST},#{(index+16) % (2*n)}]"

			yield f"str {tmp0}, [{DEST},#{(index+12) % (2*n)}]"

			# c8,c9
			if ((index+16) % (2*n) in is_initialized) and ((index+16) % (2*n) == (index+16)):
				yield f"lsr {tmp0}, {c}, #16"
				yield f"smlatt {c}, {a0},{b3},{c}"
				yield f"smladx {tmp0}, {a3}, {b1}, {tmp0}"
			else:
				yield f"smultt {c}, {a0},{b3}"
				yield f"smuadx {tmp0}, {a3}, {b1}"
				is_initialized[(index+16) % (2*n)] = True

			yield f"smlad {c}, {a1},{tmp3},{c}"
			if ((index+12) % (2*n) in is_initialized) and ((index+12) % (2*n) != (index+12)):
				yield f"pkhbt {tmp1}, {b1}, {b0}"
			yield f"smlad {c}, {a3},{tmp1},{c}"
			#yield f"pkhbt {tmp1}, {b2}, {b1}"
			yield f"smlad {c}, {a2},{tmp2},{c}"

			if ((index+16) % (2*n) in is_initialized) and ((index+16) % (2*n) != (index+16)):
				yield f"ldr {tmp1}, [{DEST},#{(index+16) % (2*n)}]"

			yield f"smladx {tmp0}, {a2}, {b2}, {tmp0}"
			yield f"smladx {tmp0}, {a1}, {b3}, {tmp0}"
			yield f"pkhbt {tmp0}, {c}, {tmp0}, lsl #16"

			if ((index+16) % (2*n) in is_initialized) and ((index+16) % (2*n) != (index+16)):
				yield f"usub16 {tmp0}, {tmp1}, {tmp0}"

			if (index+20) % (2*n) in is_initialized:
				if (index+20) % (2*n) == (index+20):
					yield f"ldr {c}, [{DEST},#{(index+20) % (2*n)}]"
				else:
					yield f"ldr {tmp1}, [{DEST},#{(index+20) % (2*n)}]"
			yield f"str {tmp0}, [{DEST},#{(index+16) % (2*n)}]"

			# c10,c11
			if ((index+20) % (2*n) in is_initialized) and ((index+20) % (2*n) == (index+20)):
				yield f"lsr {tmp0}, {c}, #16"
				yield f"smlatt {c}, {a1},{b3},{c}"
				yield f"smladx {tmp0}, {a3}, {b2}, {tmp0}"
			else:
				yield f"smultt {c}, {a1},{b3}"
				yield f"smuadx {tmp0}, {a3}, {b2}"
				is_initialized[(index+20) % (2*n)] = True

			yield f"smlad {c},{a3},{tmp2},{c}"
			#yield f"pkhbt {tmp1}, {b3}, {b2}"
			yield f"smlad {c},{a2},{tmp3},{c}"

			yield f"smladx {tmp0}, {a2}, {b3}, {tmp0}"
			yield f"pkhbt {tmp0}, {c}, {tmp0}, lsl #16"

			if ((index+20) % (2*n) in is_initialized) and ((index+20) % (2*n) != (index+20)):
				yield f"usub16 {tmp0}, {tmp1}, {tmp0}"

			if (index+24) % (2*n) in is_initialized:
				if (index+24) % (2*n) == (index+24):
					yield f"ldr {c}, [{DEST},#{(index+24) % (2*n)}]"
				else:
					yield f"ldr {tmp1}, [{DEST},#{(index+24) % (2*n)}]"
			yield f"str {tmp0}, [{DEST},#{(index+20) % (2*n)}]"

			# c12,c13
			if ((index+24) % (2*n) in is_initialized) and ((index+24) % (2*n) == (index+24)):
				yield f"lsr {tmp0}, {c}, #16"
				yield f"smlad {c},{a3},{tmp3},{c}"
				yield f"smladx {tmp0},{a3},{b3},{tmp0}"
			else:
				yield f"smuad {c},{a3},{tmp3}"
				yield f"smuadx {tmp0},{a3},{b3}"
				is_initialized[(index+24) % (2*n)] = True

			yield f"smlatt {c}, {a2},{b3},{c}"
			yield f"pkhbt {tmp0}, {c}, {tmp0}, lsl #16"

			if ((index+24) % (2*n) in is_initialized) and ((index+24) % (2*n) != (index+24)):
				yield f"usub16 {tmp0}, {tmp1}, {tmp0}"

			if (index+28) % (2*n) in is_initialized:
				if (index+28) % (2*n) == (index+28):
					yield f"ldr {c}, [{DEST}, #{(index+28) % (2*n)}]"
				else:
					yield f"ldr {tmp1}, [{DEST}, #{(index+28) % (2*n)}]"
			yield f"pop {{{SRC1}}}"  # restores r1 for the next iteration, here to pipeline the str instruction
			yield f"str {tmp0}, [{DEST},#{(index+24) % (2*n)}]"

			# c14
			if ((index+28) % (2*n) in is_initialized) and ((index+28) % (2*n) == (index+28)):
				yield f"smlatt {tmp0},{a3},{b3},{c}"
				yield f"str {tmp0}, [{DEST}, #{(index+28) % (2*n)}]"
			else:
				yield f"smultt {tmp0},{a3},{b3}"
				yield f"movt {tmp0}, #0"
				if ((index+28) % (2*n) in is_initialized) and ((index+28) % (2*n) != (index+28)):
					yield f"usub16 {tmp0}, {tmp1}, {tmp0}"
				yield f"str {tmp0}, [{DEST}, #{(index+28) % (2*n)}]"
				is_initialized[(index+28) % (2*n)] = True

DEST = "r0"
SRC1 = "r1"
SRC2 = "r2"

def schoolbook(t, n):

	if n == 16:
		yield from schoolbook_from8x8(SRC1, SRC2, DEST, n)
	elif n == 32:
		yield from schoolbook_from8x8(SRC1, SRC2, DEST, n)
	else:
		yield f"###   -   ONLY 16 and 32 supported   -   ###"
		exit(1)


def karatsuba_16(pntA, pntB, pntC, pntX):
	instructions = karatsuba_64_16(pntA, pntB, pntC, pntX)
	for ins in instructions:
		yield ins

def karatsuba_64_16(pntA, pntB, pntC, pntX):
	a0 = "r4"; a1 = "r5"; a2 = "r6"; a3 = "r7";
	a4 = "r8"; a5 = "r9"; a6 = "r10"; a7 = "r11";
	tmp0 = "r12"; tmp1 = "r14";

	# EVALUATION OF A - TOP LEVEL KARATSUBA
	for i in range(4):
		yield f"ldr {a0},[{pntA},#{i*32}]"
		yield f"ldr {a1},[{pntA},#{i*32+4}]"
		yield f"ldr {a2},[{pntA},#{i*32+8}]"
		yield f"ldr {a3},[{pntA},#{i*32+12}]"
		yield f"ldr {a4},[{pntA},#{i*32+16}]"
		yield f"ldr {a5},[{pntA},#{i*32+20}]"
		yield f"ldr {a6},[{pntA},#{i*32+24}]"
		yield f"ldr {a7},[{pntA},#{i*32+28}]"

		yield f"pkhbt {tmp0}, {a0}, {a1}, lsl#16"
		yield f"str {tmp0}, [{pntA}, #{i*16}]"
		yield f"pkhtb {tmp1}, {a1}, {a0}, asr#16"
		yield f"str {tmp1}, [{pntC}, #{i*16+64}]"
		yield f"uadd16 {tmp0}, {tmp0}, {tmp1}"
		yield f"str {tmp0}, [{pntC}, #{i*16}]"

		yield f"pkhbt {tmp0}, {a2}, {a3}, lsl#16"
		yield f"str {tmp0}, [{pntA}, #{i*16+4}]"
		yield f"pkhtb {tmp1}, {a3}, {a2}, asr#16"
		yield f"str {tmp1}, [{pntC}, #{i*16+64+4}]"
		yield f"uadd16 {tmp0}, {tmp0}, {tmp1}"
		yield f"str {tmp0}, [{pntC}, #{i*16+4}]"

		yield f"pkhbt {tmp0}, {a4}, {a5}, lsl#16"
		yield f"str {tmp0}, [{pntA}, #{i*16+8}]"
		yield f"pkhtb {tmp1}, {a5}, {a4}, asr#16"
		yield f"str {tmp1}, [{pntC}, #{i*16+64+8}]"
		yield f"uadd16 {tmp0}, {tmp0}, {tmp1}"
		yield f"str {tmp0}, [{pntC}, #{i*16+8}]"

		yield f"pkhbt {tmp0}, {a6}, {a7}, lsl#16"
		yield f"str {tmp0}, [{pntA}, #{i*16+12}]"
		yield f"pkhtb {tmp1}, {a7}, {a6}, asr#16"
		yield f"str {tmp1}, [{pntC}, #{i*16+64+12}]"
		yield f"uadd16 {tmp0}, {tmp0}, {tmp1}"
		yield f"str {tmp0}, [{pntC}, #{i*16+12}]"

	# EVALUATION OF B - TOP LEVEL KARATSUBA
	for i in range(4):
		yield f"ldr {a0},[{pntB},#{i*32}]"
		yield f"ldr {a1},[{pntB},#{i*32+4}]"
		yield f"ldr {a2},[{pntB},#{i*32+8}]"
		yield f"ldr {a3},[{pntB},#{i*32+12}]"
		yield f"ldr {a4},[{pntB},#{i*32+16}]"
		yield f"ldr {a5},[{pntB},#{i*32+20}]"
		yield f"ldr {a6},[{pntB},#{i*32+24}]"
		yield f"ldr {a7},[{pntB},#{i*32+28}]"

		yield f"pkhbt {tmp0}, {a0}, {a1}, lsl#16"
		yield f"str {tmp0}, [{pntB}, #{i*16}]"
		yield f"pkhtb {tmp1}, {a1}, {a0}, asr#16"
		yield f"str {tmp1}, [{pntX}, #{i*16}]"
		yield f"uadd16 {tmp0}, {tmp0}, {tmp1}"
		yield f"str {tmp0}, [{pntA}, #{i*16+64}]"

		yield f"pkhbt {tmp0}, {a2}, {a3}, lsl#16"
		yield f"str {tmp0}, [{pntB}, #{i*16+4}]"
		yield f"pkhtb {tmp1}, {a3}, {a2}, asr#16"
		yield f"str {tmp1}, [{pntX}, #{i*16+4}]"
		yield f"uadd16 {tmp0}, {tmp0}, {tmp1}"
		yield f"str {tmp0}, [{pntA}, #{i*16+64+4}]"

		yield f"pkhbt {tmp0}, {a4}, {a5}, lsl#16"
		yield f"str {tmp0}, [{pntB}, #{i*16+8}]"
		yield f"pkhtb {tmp1}, {a5}, {a4}, asr#16"
		yield f"str {tmp1}, [{pntX}, #{i*16+8}]"
		yield f"uadd16 {tmp0}, {tmp0}, {tmp1}"
		yield f"str {tmp0}, [{pntA}, #{i*16+64+8}]"

		yield f"pkhbt {tmp0}, {a6}, {a7}, lsl#16"
		yield f"str {tmp0}, [{pntB}, #{i*16+12}]"
		yield f"pkhtb {tmp1}, {a7}, {a6}, asr#16"
		yield f"str {tmp1}, [{pntX}, #{i*16+12}]"
		yield f"uadd16 {tmp0}, {tmp0}, {tmp1}"
		yield f"str {tmp0}, [{pntA}, #{i*16+64+12}]"
# 1 - second layer karatsuba
	# BOTTOM LEVEL KARATSUBA - A
	for i in range(2):
		yield f"ldr {a0},[{pntA},#{i*32}]"
		yield f"ldr {a1},[{pntA},#{i*32+4}]"
		yield f"ldr {a2},[{pntA},#{i*32+8}]"
		yield f"ldr {a3},[{pntA},#{i*32+12}]"
		yield f"ldr {a4},[{pntA},#{i*32+16}]"
		yield f"ldr {a5},[{pntA},#{i*32+20}]"
		yield f"ldr {a6},[{pntA},#{i*32+24}]"
		yield f"ldr {a7},[{pntA},#{i*32+28}]"

		yield f"pkhbt {tmp0}, {a0}, {a1}, lsl#16"
		yield f"str {tmp0}, [{pntA}, #{i*16}]"
		yield f"pkhtb {tmp1}, {a1}, {a0}, asr#16"
		yield f"str {tmp1}, [{pntX}, #{i*16+64}]"
		yield f"uadd16 {tmp0}, {tmp0}, {tmp1}"
		yield f"str {tmp0}, [{pntB}, #{i*16+64}]"

		yield f"pkhbt {tmp0}, {a2}, {a3}, lsl#16"
		yield f"str {tmp0}, [{pntA}, #{i*16+4}]"
		yield f"pkhtb {tmp1}, {a3}, {a2}, asr#16"
		yield f"str {tmp1}, [{pntX}, #{i*16+64+4}]"
		yield f"uadd16 {tmp0}, {tmp0}, {tmp1}"
		yield f"str {tmp0}, [{pntB}, #{i*16+64+4}]"

		yield f"pkhbt {tmp0}, {a4}, {a5}, lsl#16"
		yield f"str {tmp0}, [{pntA}, #{i*16+8}]"
		yield f"pkhtb {tmp1}, {a5}, {a4}, asr#16"
		yield f"str {tmp1}, [{pntX}, #{i*16+64+8}]"
		yield f"uadd16 {tmp0}, {tmp0}, {tmp1}"
		yield f"str {tmp0}, [{pntB}, #{i*16+64+8}]"

		yield f"pkhbt {tmp0}, {a6}, {a7}, lsl#16"
		yield f"str {tmp0}, [{pntA}, #{i*16+12}]"
		yield f"pkhtb {tmp1}, {a7}, {a6}, asr#16"
		yield f"str {tmp1}, [{pntX}, #{i*16+64+12}]"
		yield f"uadd16 {tmp0}, {tmp0}, {tmp1}"
		yield f"str {tmp0}, [{pntB}, #{i*16+64+12}]"

	# BOTTOM LEVEL KARATSUBA - B
	for i in range(2):
		yield f"ldr {a0},[{pntB},#{i*32}]"
		yield f"ldr {a1},[{pntB},#{i*32+4}]"
		yield f"ldr {a2},[{pntB},#{i*32+8}]"
		yield f"ldr {a3},[{pntB},#{i*32+12}]"
		yield f"ldr {a4},[{pntB},#{i*32+16}]"
		yield f"ldr {a5},[{pntB},#{i*32+20}]"
		yield f"ldr {a6},[{pntB},#{i*32+24}]"
		yield f"ldr {a7},[{pntB},#{i*32+28}]"

		yield f"pkhbt {tmp0}, {a0}, {a1}, lsl#16"
		yield f"str {tmp0}, [{pntA}, #{i*16+32}]"
		yield f"pkhtb {tmp1}, {a1}, {a0}, asr#16"
		yield f"str {tmp1}, [{pntX}, #{i*16+64+32}]"
		yield f"uadd16 {tmp0}, {tmp0}, {tmp1}"
		yield f"str {tmp0}, [{pntB}, #{i*16+64+32}]"

		yield f"pkhbt {tmp0}, {a2}, {a3}, lsl#16"
		yield f"str {tmp0}, [{pntA}, #{i*16+32+4}]"
		yield f"pkhtb {tmp1}, {a3}, {a2}, asr#16"
		yield f"str {tmp1}, [{pntX}, #{i*16+64+32+4}]"
		yield f"uadd16 {tmp0}, {tmp0}, {tmp1}"
		yield f"str {tmp0}, [{pntB}, #{i*16+64+32+4}]"

		yield f"pkhbt {tmp0}, {a4}, {a5}, lsl#16"
		yield f"str {tmp0}, [{pntA}, #{i*16+32+8}]"
		yield f"pkhtb {tmp1}, {a5}, {a4}, asr#16"
		yield f"str {tmp1}, [{pntX}, #{i*16+64+32+8}]"
		yield f"uadd16 {tmp0}, {tmp0}, {tmp1}"
		yield f"str {tmp0}, [{pntB}, #{i*16+64+32+8}]"

		yield f"pkhbt {tmp0}, {a6}, {a7}, lsl#16"
		yield f"str {tmp0}, [{pntA}, #{i*16+32+12}]"
		yield f"pkhtb {tmp1}, {a7}, {a6}, asr#16"
		yield f"str {tmp1}, [{pntX}, #{i*16+64+32+12}]"
		yield f"uadd16 {tmp0}, {tmp0}, {tmp1}"
		yield f"str {tmp0}, [{pntB}, #{i*16+64+32+12}]"

	# SCHOOLBOOK CALLS
	yield f"push {{r0-r3}}"
	yield f"mov {tmp0}, {pntA}"
	yield f"mov {pntA}, {pntB}"
	yield f"mov {pntB}, {tmp0}"
	yield f"bl schoolbook_gen"
	yield f"add {pntB}, {pntA}, #{64}"
	yield f"add {pntA}, {pntA}, #{32}"
	yield f"bl schoolbook_gen"
	yield f"ldr {tmp0}, [sp, #12]"
	yield f"mov {pntA}, {pntB}"
	yield f"add {pntB}, {tmp0}, #{64}"
	yield f"bl schoolbook_gen"
	yield f"pop {{r0-r3}}"

	# BOTTOM KARATSUBA - INTERPOLATION
	for i in range(4):
		yield f"ldr {a0},[{pntB},#{i*8}]"
		yield f"ldr {a1},[{pntB},#{i*8+4}]"
		yield f"ldr {a2},[{pntB},#{i*8+32}]"
		yield f"ldr {a3},[{pntB},#{i*8+36}]"
		yield f"ldr {a4},[{pntB},#{i*8+64}]"
		yield f"ldr {a5},[{pntB},#{i*8+68}]"
		if i != 0:
			yield f"ldr {a6},[{pntB},#{i*8+62}]"
		yield f"ldr {a7},[{pntB},#{i*8+66}]"

		yield f"usub16 {a2}, {a2}, {a0}"
		yield f"usub16 {a3}, {a3}, {a1}"
		yield f"usub16 {a2}, {a2}, {a4}"
		yield f"usub16 {a3}, {a3}, {a5}"
		if i == 0:
			yield f"lsl {a6}, {a4}, #{16}"
		yield f"uadd16 {a0}, {a0}, {a6}"
		yield f"uadd16 {a1}, {a1}, {a7}"
		yield f"pkhbt {tmp0}, {a0}, {a2}, lsl#16"
		yield f"str {tmp0}, [{pntA}, #{i*16}]"
		yield f"pkhtb {tmp0}, {a2}, {a0}, asr#16"
		yield f"str {tmp0}, [{pntA}, #{i*16+4}]"
		#last iteration a[0] - r2
		if i == 3:
			yield f"ldrh {a0}, [{pntA}, #{0}]"
		yield f"pkhbt {tmp0}, {a1}, {a3}, lsl#16"
		yield f"str {tmp0}, [{pntA}, #{i*16+8}]"
		yield f"pkhtb {tmp0}, {a3}, {a1}, asr#16"
		yield f"str {tmp0}, [{pntA}, #{i*16+12}]"
		if i == 3:
			yield f"sub {tmp0}, {a0}, {a5}, asr#16"
			yield f"strh {tmp0}, [{pntA}, #{0}]"
# 2 - second layer karatsuba
	# BOTTOM LEVEL KARATSUBA - A
	for i in range(2):
		yield f"ldr {a0},[{pntC},#{i*32}]"
		yield f"ldr {a1},[{pntC},#{i*32+4}]"
		yield f"ldr {a2},[{pntC},#{i*32+8}]"
		yield f"ldr {a3},[{pntC},#{i*32+12}]"
		yield f"ldr {a4},[{pntC},#{i*32+16}]"
		yield f"ldr {a5},[{pntC},#{i*32+20}]"
		yield f"ldr {a6},[{pntC},#{i*32+24}]"
		yield f"ldr {a7},[{pntC},#{i*32+28}]"

		yield f"pkhbt {tmp0}, {a0}, {a1}, lsl#16"
		yield f"str {tmp0}, [{pntB}, #{i*16}]"
		yield f"pkhtb {tmp1}, {a1}, {a0}, asr#16"
		yield f"str {tmp1}, [{pntX}, #{i*16+64}]"
		yield f"uadd16 {tmp0}, {tmp0}, {tmp1}"
		yield f"str {tmp0}, [{pntB}, #{i*16+64}]"

		yield f"pkhbt {tmp0}, {a2}, {a3}, lsl#16"
		yield f"str {tmp0}, [{pntB}, #{i*16+4}]"
		yield f"pkhtb {tmp1}, {a3}, {a2}, asr#16"
		yield f"str {tmp1}, [{pntX}, #{i*16+64+4}]"
		yield f"uadd16 {tmp0}, {tmp0}, {tmp1}"
		yield f"str {tmp0}, [{pntB}, #{i*16+64+4}]"

		yield f"pkhbt {tmp0}, {a4}, {a5}, lsl#16"
		yield f"str {tmp0}, [{pntB}, #{i*16+8}]"
		yield f"pkhtb {tmp1}, {a5}, {a4}, asr#16"
		yield f"str {tmp1}, [{pntX}, #{i*16+64+8}]"
		yield f"uadd16 {tmp0}, {tmp0}, {tmp1}"
		yield f"str {tmp0}, [{pntB}, #{i*16+64+8}]"

		yield f"pkhbt {tmp0}, {a6}, {a7}, lsl#16"
		yield f"str {tmp0}, [{pntB}, #{i*16+12}]"
		yield f"pkhtb {tmp1}, {a7}, {a6}, asr#16"
		yield f"str {tmp1}, [{pntX}, #{i*16+64+12}]"
		yield f"uadd16 {tmp0}, {tmp0}, {tmp1}"
		yield f"str {tmp0}, [{pntB}, #{i*16+64+12}]"

	# BOTTOM LEVEL KARATSUBA - B
	for i in range(2):
		yield f"ldr {a0},[{pntA},#{i*32+64}]"
		yield f"ldr {a1},[{pntA},#{i*32+64+4}]"
		yield f"ldr {a2},[{pntA},#{i*32+64+8}]"
		yield f"ldr {a3},[{pntA},#{i*32+64+12}]"
		yield f"ldr {a4},[{pntA},#{i*32+64+16}]"
		yield f"ldr {a5},[{pntA},#{i*32+64+20}]"
		yield f"ldr {a6},[{pntA},#{i*32+64+24}]"
		yield f"ldr {a7},[{pntA},#{i*32+64+28}]"

		yield f"pkhbt {tmp0}, {a0}, {a1}, lsl#16"
		yield f"str {tmp0}, [{pntB}, #{i*16+32}]"
		yield f"pkhtb {tmp1}, {a1}, {a0}, asr#16"
		yield f"str {tmp1}, [{pntX}, #{i*16+64+32}]"
		yield f"uadd16 {tmp0}, {tmp0}, {tmp1}"
		yield f"str {tmp0}, [{pntB}, #{i*16+64+32}]"

		yield f"pkhbt {tmp0}, {a2}, {a3}, lsl#16"
		yield f"str {tmp0}, [{pntB}, #{i*16+32+4}]"
		yield f"pkhtb {tmp1}, {a3}, {a2}, asr#16"
		yield f"str {tmp1}, [{pntX}, #{i*16+64+32+4}]"
		yield f"uadd16 {tmp0}, {tmp0}, {tmp1}"
		yield f"str {tmp0}, [{pntB}, #{i*16+64+32+4}]"

		yield f"pkhbt {tmp0}, {a4}, {a5}, lsl#16"
		yield f"str {tmp0}, [{pntB}, #{i*16+32+8}]"
		yield f"pkhtb {tmp1}, {a5}, {a4}, asr#16"
		yield f"str {tmp1}, [{pntX}, #{i*16+64+32+8}]"
		yield f"uadd16 {tmp0}, {tmp0}, {tmp1}"
		yield f"str {tmp0}, [{pntB}, #{i*16+64+32+8}]"

		yield f"pkhbt {tmp0}, {a6}, {a7}, lsl#16"
		yield f"str {tmp0}, [{pntB}, #{i*16+32+12}]"
		yield f"pkhtb {tmp1}, {a7}, {a6}, asr#16"
		yield f"str {tmp1}, [{pntX}, #{i*16+64+32+12}]"
		yield f"uadd16 {tmp0}, {tmp0}, {tmp1}"
		yield f"str {tmp0}, [{pntB}, #{i*16+64+32+12}]"

	# SCHOOLBOOK CALLS
	yield f"push {{r0-r3}}"
	yield f"mov {pntA}, {pntC}"
	yield f"bl schoolbook_gen"
	yield f"add {pntB}, {pntB}, #{64}"
	yield f"add {pntA}, {pntA}, #{32}"
	yield f"bl schoolbook_gen"
	yield f"ldr {tmp0}, [sp, #12]"
	yield f"sub {pntA}, {pntB}, #{64}"
	yield f"add {pntB}, {tmp0}, #{64}"
	yield f"bl schoolbook_gen"
	yield f"pop {{r0-r3}}"

	# BOTTOM KARATSUBA - INTERPOLATION
	for i in range(4):
		yield f"ldr {a0},[{pntC},#{i*8}]"
		yield f"ldr {a1},[{pntC},#{i*8+4}]"
		yield f"ldr {a2},[{pntC},#{i*8+32}]"
		yield f"ldr {a3},[{pntC},#{i*8+36}]"
		yield f"ldr {a4},[{pntB},#{i*8}]"
		yield f"ldr {a5},[{pntB},#{i*8+4}]"
		if i != 0:
			yield f"ldr {a6},[{pntB},#{i*8-2}]"
		yield f"ldr {a7},[{pntB},#{i*8+2}]"

		yield f"usub16 {a2}, {a2}, {a0}"
		yield f"usub16 {a3}, {a3}, {a1}"
		yield f"usub16 {a2}, {a2}, {a4}"
		yield f"usub16 {a3}, {a3}, {a5}"
		if i == 0:
			yield f"lsl {a6}, {a4}, #{16}"
		yield f"uadd16 {a0}, {a0}, {a6}"
		yield f"uadd16 {a1}, {a1}, {a7}"
		yield f"pkhbt {tmp0}, {a0}, {a2}, lsl#16"
		yield f"str {tmp0}, [{pntA}, #{i*16+64}]"
		yield f"pkhtb {tmp0}, {a2}, {a0}, asr#16"
		yield f"str {tmp0}, [{pntA}, #{i*16+64+4}]"
		#last iteration a[32] - r2
		if i == 3:
			yield f"ldrh {a0}, [{pntA}, #{64}]"
		yield f"pkhbt {tmp0}, {a1}, {a3}, lsl#16"
		yield f"str {tmp0}, [{pntA}, #{i*16+64+8}]"
		yield f"pkhtb {tmp0}, {a3}, {a1}, asr#16"
		yield f"str {tmp0}, [{pntA}, #{i*16+64+12}]"
		if i == 3:
			yield f"sub {tmp0}, {a0}, {a5}, asr#16"
			yield f"strh {tmp0}, [{pntA}, #{64}]"
# 3 - second layer karatsuba
	# BOTTOM LEVEL KARATSUBA - A
	for i in range(2):
		yield f"ldr {a0},[{pntC},#{i*32+64}]"
		yield f"ldr {a1},[{pntC},#{i*32+64+4}]"
		yield f"ldr {a2},[{pntC},#{i*32+64+8}]"
		yield f"ldr {a3},[{pntC},#{i*32+64+12}]"
		yield f"ldr {a4},[{pntC},#{i*32+64+16}]"
		yield f"ldr {a5},[{pntC},#{i*32+64+20}]"
		yield f"ldr {a6},[{pntC},#{i*32+64+24}]"
		yield f"ldr {a7},[{pntC},#{i*32+64+28}]"

		yield f"pkhbt {tmp0}, {a0}, {a1}, lsl#16"
		yield f"str {tmp0}, [{pntB}, #{i*16}]"
		yield f"pkhtb {tmp1}, {a1}, {a0}, asr#16"
		yield f"str {tmp1}, [{pntX}, #{i*16+64}]"
		yield f"uadd16 {tmp0}, {tmp0}, {tmp1}"
		yield f"str {tmp0}, [{pntB}, #{i*16+64}]"

		yield f"pkhbt {tmp0}, {a2}, {a3}, lsl#16"
		yield f"str {tmp0}, [{pntB}, #{i*16+4}]"
		yield f"pkhtb {tmp1}, {a3}, {a2}, asr#16"
		yield f"str {tmp1}, [{pntX}, #{i*16+64+4}]"
		yield f"uadd16 {tmp0}, {tmp0}, {tmp1}"
		yield f"str {tmp0}, [{pntB}, #{i*16+64+4}]"

		yield f"pkhbt {tmp0}, {a4}, {a5}, lsl#16"
		yield f"str {tmp0}, [{pntB}, #{i*16+8}]"
		yield f"pkhtb {tmp1}, {a5}, {a4}, asr#16"
		yield f"str {tmp1}, [{pntX}, #{i*16+64+8}]"
		yield f"uadd16 {tmp0}, {tmp0}, {tmp1}"
		yield f"str {tmp0}, [{pntB}, #{i*16+64+8}]"

		yield f"pkhbt {tmp0}, {a6}, {a7}, lsl#16"
		yield f"str {tmp0}, [{pntB}, #{i*16+12}]"
		yield f"pkhtb {tmp1}, {a7}, {a6}, asr#16"
		yield f"str {tmp1}, [{pntX}, #{i*16+64+12}]"
		yield f"uadd16 {tmp0}, {tmp0}, {tmp1}"
		yield f"str {tmp0}, [{pntB}, #{i*16+64+12}]"

	# BOTTOM LEVEL KARATSUBA - B
	for i in range(2):
		yield f"ldr {a0},[{pntX},#{i*32}]"
		yield f"ldr {a1},[{pntX},#{i*32+4}]"
		yield f"ldr {a2},[{pntX},#{i*32+8}]"
		yield f"ldr {a3},[{pntX},#{i*32+12}]"
		yield f"ldr {a4},[{pntX},#{i*32+16}]"
		yield f"ldr {a5},[{pntX},#{i*32+20}]"
		yield f"ldr {a6},[{pntX},#{i*32+24}]"
		yield f"ldr {a7},[{pntX},#{i*32+28}]"

		yield f"pkhbt {tmp0}, {a0}, {a1}, lsl#16"
		yield f"str {tmp0}, [{pntB}, #{i*16+32}]"
		yield f"pkhtb {tmp1}, {a1}, {a0}, asr#16"
		yield f"str {tmp1}, [{pntX}, #{i*16+64+32}]"
		yield f"uadd16 {tmp0}, {tmp0}, {tmp1}"
		yield f"str {tmp0}, [{pntB}, #{i*16+64+32}]"

		yield f"pkhbt {tmp0}, {a2}, {a3}, lsl#16"
		yield f"str {tmp0}, [{pntB}, #{i*16+32+4}]"
		yield f"pkhtb {tmp1}, {a3}, {a2}, asr#16"
		yield f"str {tmp1}, [{pntX}, #{i*16+64+32+4}]"
		yield f"uadd16 {tmp0}, {tmp0}, {tmp1}"
		yield f"str {tmp0}, [{pntB}, #{i*16+64+32+4}]"

		yield f"pkhbt {tmp0}, {a4}, {a5}, lsl#16"
		yield f"str {tmp0}, [{pntB}, #{i*16+32+8}]"
		yield f"pkhtb {tmp1}, {a5}, {a4}, asr#16"
		yield f"str {tmp1}, [{pntX}, #{i*16+64+32+8}]"
		yield f"uadd16 {tmp0}, {tmp0}, {tmp1}"
		yield f"str {tmp0}, [{pntB}, #{i*16+64+32+8}]"

		yield f"pkhbt {tmp0}, {a6}, {a7}, lsl#16"
		yield f"str {tmp0}, [{pntB}, #{i*16+32+12}]"
		yield f"pkhtb {tmp1}, {a7}, {a6}, asr#16"
		yield f"str {tmp1}, [{pntX}, #{i*16+64+32+12}]"
		yield f"uadd16 {tmp0}, {tmp0}, {tmp1}"
		yield f"str {tmp0}, [{pntB}, #{i*16+64+32+12}]"

	# SCHOOLBOOK CALLS
	yield f"push {{r0-r3}}"
	yield f"mov {pntA}, {pntC}"
	yield f"bl schoolbook_gen"
	yield f"add {pntB}, {pntB}, #{64}"
	yield f"add {pntA}, {pntA}, #{32}"
	yield f"bl schoolbook_gen"
	yield f"ldr {tmp0}, [sp, #12]"
	yield f"sub {pntA}, {pntB}, #{64}"
	yield f"add {pntB}, {tmp0}, #{64}"
	yield f"bl schoolbook_gen"
	yield f"pop {{r0-r3}}"

	# BOTTOM KARATSUBA - INTERPOLATION
	for i in range(4):
		yield f"ldr {a0},[{pntC},#{i*8}]"
		yield f"ldr {a1},[{pntC},#{i*8+4}]"
		yield f"ldr {a2},[{pntC},#{i*8+32}]"
		yield f"ldr {a3},[{pntC},#{i*8+36}]"
		yield f"ldr {a4},[{pntB},#{i*8}]"
		yield f"ldr {a5},[{pntB},#{i*8+4}]"
		if i != 0:
			yield f"ldr {a6},[{pntB},#{i*8-2}]"
		yield f"ldr {a7},[{pntB},#{i*8+2}]"

		yield f"usub16 {a2}, {a2}, {a0}"
		yield f"usub16 {a3}, {a3}, {a1}"
		yield f"usub16 {a2}, {a2}, {a4}"
		yield f"usub16 {a3}, {a3}, {a5}"
		if i == 0:
			yield f"lsl {a6}, {a4}, #{16}"
		yield f"uadd16 {a0}, {a0}, {a6}"
		yield f"uadd16 {a1}, {a1}, {a7}"
		yield f"pkhbt {tmp0}, {a0}, {a2}, lsl#16"
		yield f"str {tmp0}, [{pntB}, #{i*16+64}]"
		yield f"pkhtb {tmp0}, {a2}, {a0}, asr#16"
		yield f"str {tmp0}, [{pntB}, #{i*16+64+4}]"
		#last iteration b[32] - r2
		if i == 3:
			yield f"ldrh {a0}, [{pntB}, #{64}]"
		yield f"pkhbt {tmp0}, {a1}, {a3}, lsl#16"
		yield f"str {tmp0}, [{pntB}, #{i*16+64+8}]"
		yield f"pkhtb {tmp0}, {a3}, {a1}, asr#16"
		yield f"str {tmp0}, [{pntB}, #{i*16+64+12}]"
		if i == 3:
			yield f"sub {tmp0}, {a0}, {a5}, asr#16"
			yield f"strh {tmp0}, [{pntB}, #{64}]"

	#------------------------------------------------
	# INTERPOLATION - TOP KARATSUBA
	for i in range(8):
		yield f"ldr {a0},[{pntA},#{i*8}]"
		yield f"ldr {a1},[{pntA},#{i*8+4}]"
		yield f"ldr {a2},[{pntA},#{i*8+64}]"
		yield f"ldr {a3},[{pntA},#{i*8+68}]"
		yield f"ldr {a4},[{pntB},#{i*8+64}]"
		yield f"ldr {a5},[{pntB},#{i*8+64+4}]"
		if i != 0:
			yield f"ldr {a6},[{pntB},#{i*8+62}]"
		yield f"ldr {a7},[{pntB},#{i*8+66}]"

		yield f"usub16 {a2}, {a2}, {a0}"
		yield f"usub16 {a3}, {a3}, {a1}"
		yield f"usub16 {a2}, {a2}, {a4}"
		yield f"usub16 {a3}, {a3}, {a5}"
		if i == 0:
			yield f"lsl {a6}, {a4}, #{16}"
		yield f"uadd16 {a0}, {a0}, {a6}"
		yield f"uadd16 {a1}, {a1}, {a7}"
		yield f"pkhbt {tmp0}, {a0}, {a2}, lsl#16"
		yield f"str {tmp0}, [{pntC}, #{i*16}]"
		yield f"pkhtb {tmp0}, {a2}, {a0}, asr#16"
		yield f"str {tmp0}, [{pntC}, #{i*16+4}]"
		#last iteration res[0] - r2
		if i == 7:
			yield f"ldrh {a0}, [{pntC}, #{0}]"
		yield f"pkhbt {tmp0}, {a1}, {a3}, lsl#16"
		yield f"str {tmp0}, [{pntC}, #{i*16+8}]"
		yield f"pkhtb {tmp0}, {a3}, {a1}, asr#16"
		yield f"str {tmp0}, [{pntC}, #{i*16+12}]"
		if i == 7:
			yield f"sub {tmp0}, {a0}, {a5}, asr#16"
			yield f"strh {tmp0}, [{pntC}, #{0}]"

def karatsuba_32(pntA, pntB, pntC, pntX):
	instructions = karatsuba_64_32(pntA, pntB, pntC, pntX)
	for ins in instructions:
		yield ins

def karatsuba_64_32(pntA, pntB, pntC, pntX):
	a0 = "r4"; a1 = "r5"; a2 = "r6"; a3 = "r7";
	a4 = "r8"; a5 = "r9"; a6 = "r10"; a7 = "r11";
	tmp0 = "r12"; tmp1 = "r14";

	# EVALUATION OF A - TOP LEVEL KARATSUBA
	for i in range(4):
		yield f"ldr {a0},[{pntA},#{i*32}]"
		yield f"ldr {a1},[{pntA},#{i*32+4}]"
		yield f"ldr {a2},[{pntA},#{i*32+8}]"
		yield f"ldr {a3},[{pntA},#{i*32+12}]"
		yield f"ldr {a4},[{pntA},#{i*32+16}]"
		yield f"ldr {a5},[{pntA},#{i*32+20}]"
		yield f"ldr {a6},[{pntA},#{i*32+24}]"
		yield f"ldr {a7},[{pntA},#{i*32+28}]"

		yield f"pkhbt {tmp0}, {a0}, {a1}, lsl#16"
		yield f"str {tmp0}, [{pntA}, #{i*16}]"
		yield f"pkhtb {tmp1}, {a1}, {a0}, asr#16"
		yield f"str {tmp1}, [{pntX}, #{i*16}]"
		yield f"uadd16 {tmp0}, {tmp0}, {tmp1}"
		yield f"str {tmp0}, [{pntC}, #{i*16}]"

		yield f"pkhbt {tmp0}, {a2}, {a3}, lsl#16"
		yield f"str {tmp0}, [{pntA}, #{i*16+4}]"
		yield f"pkhtb {tmp1}, {a3}, {a2}, asr#16"
		yield f"str {tmp1}, [{pntX}, #{i*16+4}]"
		yield f"uadd16 {tmp0}, {tmp0}, {tmp1}"
		yield f"str {tmp0}, [{pntC}, #{i*16+4}]"

		yield f"pkhbt {tmp0}, {a4}, {a5}, lsl#16"
		yield f"str {tmp0}, [{pntA}, #{i*16+8}]"
		yield f"pkhtb {tmp1}, {a5}, {a4}, asr#16"
		yield f"str {tmp1}, [{pntX}, #{i*16+8}]"
		yield f"uadd16 {tmp0}, {tmp0}, {tmp1}"
		yield f"str {tmp0}, [{pntC}, #{i*16+8}]"

		yield f"pkhbt {tmp0}, {a6}, {a7}, lsl#16"
		yield f"str {tmp0}, [{pntA}, #{i*16+12}]"
		yield f"pkhtb {tmp1}, {a7}, {a6}, asr#16"
		yield f"str {tmp1}, [{pntX}, #{i*16+12}]"
		yield f"uadd16 {tmp0}, {tmp0}, {tmp1}"
		yield f"str {tmp0}, [{pntC}, #{i*16+12}]"

	# EVALUATION OF B - TOP LEVEL KARATSUBA
	for i in range(4):
		yield f"ldr {a0},[{pntB},#{i*32}]"
		yield f"ldr {a1},[{pntB},#{i*32+4}]"
		yield f"ldr {a2},[{pntB},#{i*32+8}]"
		yield f"ldr {a3},[{pntB},#{i*32+12}]"
		yield f"ldr {a4},[{pntB},#{i*32+16}]"
		yield f"ldr {a5},[{pntB},#{i*32+20}]"
		yield f"ldr {a6},[{pntB},#{i*32+24}]"
		yield f"ldr {a7},[{pntB},#{i*32+28}]"

		yield f"pkhbt {tmp0}, {a0}, {a1}, lsl#16"
		yield f"str {tmp0}, [{pntA}, #{i*16+64}]"
		yield f"pkhtb {tmp1}, {a1}, {a0}, asr#16"
		yield f"str {tmp1}, [{pntX}, #{i*16+64}]"
		yield f"uadd16 {tmp0}, {tmp0}, {tmp1}"
		yield f"str {tmp0}, [{pntC}, #{i*16+64}]"

		yield f"pkhbt {tmp0}, {a2}, {a3}, lsl#16"
		yield f"str {tmp0}, [{pntA}, #{i*16+64+4}]"
		yield f"pkhtb {tmp1}, {a3}, {a2}, asr#16"
		yield f"str {tmp1}, [{pntX}, #{i*16+64+4}]"
		yield f"uadd16 {tmp0}, {tmp0}, {tmp1}"
		yield f"str {tmp0}, [{pntC}, #{i*16+64+4}]"

		yield f"pkhbt {tmp0}, {a4}, {a5}, lsl#16"
		yield f"str {tmp0}, [{pntA}, #{i*16+64+8}]"
		yield f"pkhtb {tmp1}, {a5}, {a4}, asr#16"
		yield f"str {tmp1}, [{pntX}, #{i*16+64+8}]"
		yield f"uadd16 {tmp0}, {tmp0}, {tmp1}"
		yield f"str {tmp0}, [{pntC}, #{i*16+64+8}]"

		yield f"pkhbt {tmp0}, {a6}, {a7}, lsl#16"
		yield f"str {tmp0}, [{pntA}, #{i*16+64+12}]"
		yield f"pkhtb {tmp1}, {a7}, {a6}, asr#16"
		yield f"str {tmp1}, [{pntX}, #{i*16+64+12}]"
		yield f"uadd16 {tmp0}, {tmp0}, {tmp1}"
		yield f"str {tmp0}, [{pntC}, #{i*16+64+12}]"

	# SCHOOLBOOK CALLS
	yield f"push {{r0-r3}}"
	yield f"mov {tmp0}, {pntA}"
	yield f"mov {pntA}, {pntB}"
	yield f"mov {pntB}, {tmp0}"
	#yield f"push {{r0-r12, r14}}"
	yield f"bl schoolbook_gen"
	#yield f"pop {{r0-r12, r14}}"
	yield f"ldr {pntB}, [sp, #8]"
	yield f"add {pntA}, {pntA}, #{32}"
	#yield f"push {{r0-r12, r14}}"
	yield f"bl schoolbook_gen"
	#yield f"pop {{r0-r12, r14}}"
	yield f"ldr {pntA}, [sp, #0]"
	yield f"ldr {pntB}, [sp, #12]"
	#yield f"push {{r0-r12, r14}}"
	yield f"bl schoolbook_gen"
	#yield f"pop {{r0-r12, r14}}"
	yield f"pop {{r0-r3}}"

	# INTERPOLATION - TOP KARATSUBA
	for i in range(8):
		yield f"ldr {a0},[{pntB},#{i*8}]"
		yield f"ldr {a1},[{pntB},#{i*8+4}]"
		yield f"ldr {a2},[{pntB},#{i*8+64}]"
		yield f"ldr {a3},[{pntB},#{i*8+68}]"
		yield f"ldr {a4},[{pntA},#{i*8}]"
		yield f"ldr {a5},[{pntA},#{i*8+4}]"
		if i != 0:
			yield f"ldr {a6},[{pntA},#{i*8-2}]"
		yield f"ldr {a7},[{pntA},#{i*8+2}]"

		yield f"usub16 {a2}, {a2}, {a0}"
		yield f"usub16 {a3}, {a3}, {a1}"
		yield f"usub16 {a2}, {a2}, {a4}"
		yield f"usub16 {a3}, {a3}, {a5}"
		if i == 0:
			yield f"lsl {a6}, {a4}, #{16}"
		yield f"uadd16 {a0}, {a0}, {a6}"
		yield f"uadd16 {a1}, {a1}, {a7}"
		yield f"pkhbt {tmp0}, {a0}, {a2}, lsl#16"
		yield f"str {tmp0}, [{pntC}, #{i*16}]"
		yield f"pkhtb {tmp0}, {a2}, {a0}, asr#16"
		yield f"str {tmp0}, [{pntC}, #{i*16+4}]"
		#last iteration res[0] - r2
		if i == 7:
			yield f"ldrh {a0}, [{pntC}, #{0}]"
		yield f"pkhbt {tmp0}, {a1}, {a3}, lsl#16"
		yield f"str {tmp0}, [{pntC}, #{i*16+8}]"
		yield f"pkhtb {tmp0}, {a3}, {a1}, asr#16"
		yield f"str {tmp0}, [{pntC}, #{i*16+12}]"
		if i == 7:
			yield f"sub {tmp0}, {a0}, {a5}, asr#16"
			yield f"strh {tmp0}, [{pntC}, #{0}]"


pntA = "r0"
pntB = "r1"
pntC = "r2"
pntX = "r3"

def karatsuba(n):

	if n == 16:
		yield from karatsuba_16(pntA, pntB, pntC, pntX)
	elif n == 32:
		yield from karatsuba_32(pntA, pntB, pntC, pntX)
	else:
		exit(1)


def toomcook4():

	yield from toomcook_256(pntA, pntB, pntC)


p = print

if __name__ == '__main__':
	if len(sys.argv) != 2:
		exit(1)

	n = int(sys.argv[1])
	threshold = n
	p(".syntax unified")
	p(".cpu cortex-m4")


	outermult = list(schoolbook(threshold, n))

	p(".global schoolbook_gen")
	p(".type schoolbook_gen, %function")
	p(".align 2")
	p("schoolbook_gen:")
	p("push {r14}")

	for statement in outermult:
		p(statement)

	p("pop {r14}")
	p("bx lr")


	outermult = list(karatsuba(n))

	p(".global kara_strd_mem_asm")
	p(".type kara_strd_mem_asm, %function")
	p(".align 2")
	p("kara_strd_mem_asm:")
	p("push {r4-r11, r14}")
	#p("push {r14}")


	for statement in outermult:
		p(statement)

	p("pop {r4-r11, r14}")
	#p("pop {r14}")
	p("bx lr")


	outermult = list(toomcook4())

	p(".global toom_cook_4way_striding_asm")
	p(".type toom_cook_4way_striding_asm, %function")
	p(".align 2")
	p("toom_cook_4way_striding_asm:")
	p("push {r4-r11, r14}")
	p("sub sp, sp, #1664")

	for statement in outermult:
		p(statement)

	p("add sp, sp, #1664")
	p("pop {r4-r11, r14}")
	p("bx lr")
