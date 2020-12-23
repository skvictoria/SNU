#----------------------------------------------------------------
#
#  4190.308 Computer Architecture (Fall 2020)
#
#  Project #3: RISC-V Assembly Programming
#
#  October 26, 2020
#  author : Seulgi Kim
#  Injae Kang (abcinje@snu.ac.kr)
#  Sunmin Jeong (sunnyday0208@snu.ac.kr)
#  Systems Software & Architecture Laboratory
#  Dept. of Computer Science and Engineering
#  Seoul National University
#
#----------------------------------------------------------------
	.text
	.align	2

#---------------------------------------------------------------------
#  int decode(const char *inp, int inbytes, char *outp, int outbytes)
#---------------------------------------------------------------------
	.globl	decode

decode:
	beq 	a1, x0, inp0
	addi	sp, sp, -64
	addi	a4, sp, 0
	addi 	sp, sp, -48
	sw 		ra, 36(sp)
	sw 		a0, 32(sp)	# Inbuf stream top
	sw 		a1, 28(sp)	# byte number of input stream
	sw 		a2, 24(sp)	# OutBuf top
	sw 		a4, 20(sp)	# Store Table Bottom Address
	add 	a2, a2, a3
	sw		a2, 0(sp)	# OutBuf Top
	sw		x0, 16(sp)	# Old Input bit Stream Pointer
	#sw		x0, 40(sp)	# Buffer for old bit Stream (Low)
	#sw		x0, 44(sp)	# Buffer for old bit Stream (High)
	
	lw a5, 0(a0)
	
	addi	a0, sp, 12
	li		a1, 0
	
	lw a3, 20(sp)
mk8symbol:
	andi a2, a5, 0xf0 ## make 8 symbol start!
	srli a2, a2, 4
	sw a2, 0(a3)
	
	addi a1, a1, 1
	
	andi a2, a5, 0x0f
	sw a2, 4(a3)
	addi a1, a1, 1

	srli a5, a5, 8
	addi a3, a3, 8
	addi a4, x0, 8 #for comparing
	bne a4, a1, mk8symbol #end to make 8 symbol
	
	addi a3, x0, 0 #a3 =0
	addi a4, x0, 8 #a4=8
	lw a5, 32(sp)
	lw a5, 0(a5)
mklookuptbl:
	andi a1, a5, 0x0f	# mklookuptbl:
	srli a5, a5, 4
	addi a2, x0, 1 #a2 = 1
	sll a2, a2, a1
	add a3, a3, a2
	addi a4, a4, -1
	bne a4, x0, mklookuptbl
	addi a4, x0, 16 # a3 has lookuptable
	lw a0, 20(sp)
	addi a0, a0, 32
	
mk16symbol:
	andi a2, a3, 0x01 #start make 16 symbol
	beq a2, x0, loop_mk16symbol
	srli a3, a3, 1
	addi a4, a4, -1
	bne a4, x0, mk16symbol
	beq x0, x0, parsing
loop_mk16symbol:
	addi a5, x0, 16
	sub a2, a5, a4
	sw a2, 0(a0)
	
	addi a0, a0, 4
	
	srli a3, a3, 1
	addi a4, a4, -1
	beq a4, x0, parsing # corner case
	beq x0, x0, mk16symbol # always make last 16 symbols
	
parsing:
	sw x0, 4(sp)	# parsing: now decode @-----@
	sw x0, 8(sp)
	
	lw a2, 32(sp)	# a2 <- InBuf Top
	addi	a2, a2, 4	# InBuf Top + 4
	sw	a2, 32(sp)	
	lw a4, 28(sp)	# a4 <- Test Count
	sw	x0,28(sp)	# Initialize non 8-multiple counter
	
	lw		a0,0(a2)	# get InBuf stream very first val
	slli	a0,a0,24
	srli	a0,a0,28
	addi	a0,a0,36
	slli a4, a4, 3
	sub		a4, a4, a0
	
	addi a0, x0, 4  # do not touch a4, a0; a0=4 bit
	beq x0, x0, realL6
		
L6:	
	lw a5, 4(sp)	# L6: 	@@<---
	addi a5, a5, 1	# decode counter
	sw a5, 4(sp)
	
	slli	a5, a5, 29
	bne		a5, x0, realL60	# if not 8-multiples,
	
	sw	x0,28(sp)	# clear non 8-multiple Counter
	
	lw a2, 24(sp)	# Write DECODED value to OutBuf
	lw a5, 0(sp)
	bge a2, a5, faill
	addi a5, sp, 8
	
	#call SaveCode

	lw a1, 0(a5)
	slli a3, a1, 24		# First
	srli a1, a1, 8
	slli	a1, a1, 24
	srli	a1, a1, 8
	or	a3, a3, a1		# second
	lw	a1, 0(a5)
	slli	a1, a1, 8
	srli	a1, a1, 24
	slli	a1, a1, 8
	or	a3, a3, a1		# third
	lw	a1, 0(a5)
	srli	a1, a1, 24
	or	a3, a3, a1		# last
	sw	a3, 0(a2)

	addi a2, a2, 4	# OutBuf + 4 (Next Pointer)
	sw a2, 24(sp)
	
	sw	x0,8(sp)	# clear Decode Buffer

	j	realL6

realL60:
	lw	a3,28(sp)	# realL60: non 8-multiple Counter
	addi	a3, a3, 1
	sw	a3,28(sp)	

realL6:
	beq		a4, x0, L7	# realL6:
	lw		a2, 32(sp)	# a2 <- Input Top (!!) a0 must have Test Top!
	li		a1, 5		# 5bit
	call	ReqBitStream	# a3 <-- Return val
	
	andi	a5, a3, 0x10
	beq		a5, x0, parse3	# first bit == 0, parse3
	andi	a5, a3, 0x08
	beq		a5, x0, parse4	# second bit == 0 parse4
	j		parse5			# second bit == 1 parse5
	
parse3:
	srli	a3, a3, 2		# 5 bit -> 3 bit
	addi	a0, a0, -2		# bit pointer - 2
	addi a4, a4, -3
	
	lw a1, 20(sp)
	slli a3, a3, 2
	add a1, a1, a3 #debug point
	lw a1, 0(a1)
	
	lw a5, 8(sp)
	slli a5, a5, 4
	add a5, a5, a1
	sw a5, 8(sp)  # <---
	
	j		L6
	
parse4:
	srli	a3, a3, 1		# 5 bit -> 4 bit
	addi	a0, a0, -1		# bit pointer - 1
	addi a4, a4, -4
	
	addi	a3, a3, -4	# a3 <- Recalc Pos(0~15)
	
	lw a1, 20(sp)
	slli a3, a3, 2
	add a1, a1, a3 #debug point
	lw a1, 0(a1)
	
	lw a5, 8(sp)
	slli a5, a5, 4
	add a5, a5, a1
	sw a5, 8(sp)  # <---
	
	j	L6

parse5:
	addi a4, a4, -5
	
	addi	a3, a3, -16
	
	lw a1, 20(sp)
	slli a3, a3, 2
	add a1, a1, a3 #debug point
	lw a1, 0(a1)
	
	lw a5, 8(sp)
	slli a5, a5, 4
	add a5, a5, a1
	sw a5, 8(sp)		# <---
	
	j	L6
	
## All bits are completed
L7:
	lw	a3, 28(sp)	# L7: check non 8-multiple counter
	beq	a3,x0,L70
	li	a2, 8
	sub	a3, a2, a3
	slli	a3,a3,2
	lw	a5, 8(sp)
	sll	a5, a5,a3
	sw	a5, 8(sp) 
	
	lw a2, 24(sp)	# Write uncompleted DECODED value to OutBuf
	lw a5, 0(sp)
	bge a2, a5, faill
	addi a5, sp, 8
	# 
	#call SaveCode	

	lw a1, 0(a5)
	slli a3, a1, 24		# First
	srli a1, a1, 8
	slli	a1, a1, 24
	srli	a1, a1, 8
	or	a3, a3, a1		# second
	lw	a1, 0(a5)
	slli	a1, a1, 8
	srli	a1, a1, 24
	slli	a1, a1, 8
	or	a3, a3, a1		# third
	lw	a1, 0(a5)
	srli	a1, a1, 24
	or	a3, a3, a1		# last
	sw	a3, 0(a2)


	addi a2, a2, 4	# OutBuf + 4 (Next Pointer)
	sw a2, 24(sp)

L70:
	lw	a0, 4(sp)	# L70:
	srli	a0,a0,1	# /2
	
L8:
	lw ra, 36(sp)	# L8: @@<---
	addi sp, sp, 48
	addi	sp, sp, 64
	ret
	
inp0:
	add a0, x0, x0
	ret
faill:
	addi a0, x0, -1
	lw ra, 36(sp)
	addi sp, sp, 48
	addi	sp, sp, 64
	ret

	
# Input: 
#   a0 = bit pointer
#   a1 = req bits
#   a2 = Input TOP address
# Output:
#   a0 = bit pointer, updated
#   a3 = return value
# Stack Use: 16
ReqBitStream:
	addi	sp, sp, -16	# ReqBitStream:
	sw		a2, 0(sp)
	sw		a4, 4(sp)
	# Make data pointer
	srli	a3, a0, 5	# Make byte pointer from bit pointer
	slli	a3, a3, 2	# Cause 32bit = 4 byte, x 4 must be done
	add		a2, a2, a3	# get real address
	#
	lw		a5, 32(sp)	# 32 = 16 + 16
	beq		a5, a2, ReqBitNonLoad
	sw		a2, 32(sp)	# If not equal, updata it.
	#
	lw		a5, 0(a2)	# take value
	#call	SaveCode2	# a5 <= convert big endian to little endian
	slli	a3, a5, 24	# first
	srli	a4, a5, 8
	slli	a4, a4, 24
	srli	a4, a4, 8
	or		a3, a3, a4	# second
	slli	a4, a5, 8
	srli	a4, a4, 24
	slli	a4, a4, 8
	or		a3, a3, a4	# third
	srli	a5, a5, 24
	or		a5, a3, a5	# last
	#
	sw		a5, 56(sp)	# temp save (56 = 16 + 40) #8
	lw		a5, 4(a2)	# take next word value
	#call	SaveCode2	# a5 <= convert big endian to little endian
	slli	a3, a5, 24	# first
	srli	a4, a5, 8
	slli	a4, a4, 24
	srli	a4, a4, 8
	or		a3, a3, a4	# second
	slli	a4, a5, 8
	srli	a4, a4, 24
	slli	a4, a4, 8
	or		a3, a3, a4	# third
	srli	a5, a5, 24
	or		a5, a3, a5	# last
	#
	sw		a5, 60(sp)	# temp save (60 = 16 + 44) #12
	#
ReqBitNonLoad:
	srli	a4, a0, 5	# Get Reminder
	slli	a4, a4, 5
	sub		a4, a0, a4
	lw		a5, 56(sp)	# a5 has required bits
	beq		a4, x0, ReqBitStreamSkip
	#
	sll		a5, a5, a4
	li		a3, 32
	sub		a4, a3, a4
	lw		a3, 60(sp)
	srl		a3, a3, a4
	or		a5, a5, a3

ReqBitStreamSkip:
	#
	li		a3, 32
	sub		a3, a3, a1	# make right shift value
	srl		a3, a5, a3	# a3 <- required bits
	#
	lw		a4, 4(sp)
	lw		a2, 0(sp)
	add		a0, a0, a1	# update next bit pointer
	addi	sp, sp, 16
	ret
	
