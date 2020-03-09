	.thumb
	.syntax unified
.text

//function for a TOOM-COOK in assembly
//*************************************************
// toom_cook_4way_mem_asm(&a1, &b1, &result);
//*************************************************
.global toom_cook_4way_mem_asm
.func toom_cook_4way_mem_asm, toom_cook_4way_mem_asm
.type toom_cook_4way_mem_asm, %function
toom_cook_4way_mem_asm:
	stmdb	sp!, {r3, r4, r5, r6, r7, r8, r9, r10, r11, r12, lr}
	subw	sp, sp, #3076
	mov 	r3, sp
	mov 	r11, r2
	add 	r2, r3, #1792
//r0=&a1[i] r1=b1 r2=&w_m[896+i]
//loop1
	add 	r12, r0, #128
toom_cook_4way_mem_asm_loop1:
	ldr 	r6, [r0, #384]
	ldr 	r4, [r0, #128]
	ldr 	r5, [r0, #256]
	ldr 	r3, [r0], #4
	cmp 	r0, r12
	uadd16 	r8, r4, r6
	uadd16 	r7, r3, r5
	uadd16 	r9, r7, r8
	usub16 	r10, r7, r8
	str 	r9, [r2, #128]
	str 	r10, [r2, #256]
	uadd16 	r7, r3, r3
	uadd16	r7, r7, r7
	uadd16	r7, r7, r5
	uadd16 	r7, r7, r7
	uadd16 	r8, r4, r4
	uadd16 	r8, r8, r8
	uadd16 	r8, r8, r6
	uadd16 	r9, r7, r8
	usub16 	r10, r7, r8
	str 	r9, [r2, #384]
	str 	r10, [r2, #512]
	uadd16 	r7, r6, r6
	uadd16 	r7, r7, r5
	uadd16 	r7, r7, r7
	uadd16 	r7, r7, r4
	uadd16 	r7, r7, r7
	uadd16 	r7, r7 ,r3
	str 	r7, [r2], #4
	bne 	toom_cook_4way_mem_asm_loop1
//loop2
	add 	r12, r1, #128
	add 	r2, r2, #512
toom_cook_4way_mem_asm_loop2:
	ldr 	r6, [r1, #384]
	ldr 	r4, [r1, #128]
	ldr 	r5, [r1, #256]
	ldr 	r3, [r1], #4
	cmp 	r1, r12
	uadd16 	r8, r4, r6
	uadd16 	r7, r3, r5
	uadd16 	r9, r7, r8
	usub16 	r10, r7, r8
	str 	r9, [r2, #128]
	str 	r10, [r2, #256]
	uadd16 	r7, r3, r3
	uadd16	r7, r7, r7
	uadd16	r7, r7, r5
	uadd16 	r7, r7, r7
	uadd16 	r8, r4, r4
	uadd16 	r8, r8, r8
	uadd16 	r8, r8, r6
	uadd16 	r9, r7, r8
	usub16 	r10, r7, r8
	str 	r9, [r2, #384]
	str 	r10, [r2, #512]
	uadd16 	r7, r6, r6
	uadd16 	r7, r7, r5
	uadd16 	r7, r7, r7
	uadd16 	r7, r7, r4
	uadd16 	r7, r7, r7
	uadd16 	r7, r7 ,r3
	str 	r7, [r2], #4
	bne 	toom_cook_4way_mem_asm_loop2
//r0=&a1[i+64] r1=&b1[i+64] r2=&w_m[896+320+64+i] r3-r10 r12
	mov 	r9, r11
	mov 	r11, r0
	mov 	r12, r1
	sub 	r0, r2, #2560
	mov 	r1, #0
	mov 	r2, #1792
	bl 		memset
	mov 	r10, r0
	sub 	r2, r11, #128
	sub 	r1, r12, #128
	add		r0, r10, #1536
	# mov 	r3, #32
	stmdb	sp!, {r9, r10, r11, r12}
	#bl 		unrolled_kara_mem
	bl 		karatsuba_64x64
	ldmia.w	sp!, {r9, r10, r11, r12}
	add 	r2, r11, #256
	add 	r1, r12, #256
	mov 	r0, r10
	# mov 	r3, #32
	stmdb	sp!, {r9, r10}
	#bl 		unrolled_kara_mem
	bl 		karatsuba_64x64
	ldmia.w	sp!, {r9, r10}
	add 	r2, r10, #2304
	add 	r1, r10, #2944
	add 	r0, r10, #1280
	# mov 	r3, #32
	stmdb	sp!, {r9, r10}
	#bl 		unrolled_kara_mem
	bl 		karatsuba_64x64
	ldmia.w	sp!, {r9, r10}
	add 	r2, r10, #2176
	add 	r1, r10, #2816
	add 	r0, r10, #1024
	# mov 	r3, #32
	stmdb	sp!, {r9, r10}
	#bl 		unrolled_kara_mem
	bl 		karatsuba_64x64
	ldmia.w	sp!, {r9, r10}
	add 	r2, r10, #2048
	add 	r1, r10, #2688
	add 	r0, r10, #768
	# mov 	r3, #32
	stmdb	sp!, {r9, r10}
	#bl 		unrolled_kara_mem
	bl 		karatsuba_64x64
	ldmia.w	sp!, {r9, r10}
	add 	r2, r10, #1920
	add 	r1, r10, #2560
	add 	r0, r10, #512
	# mov 	r3, #32
	stmdb	sp!, {r9, r10}
	#bl 		unrolled_kara_mem
	bl 		karatsuba_64x64
	ldmia.w	sp!, {r9, r10}
	add 	r2, r10, #1792
	add 	r1, r10, #2432
	add 	r0, r10, #256
	# mov 	r3, #32
	stmdb	sp!, {r9, r10}
	#bl 		unrolled_kara_mem
	bl 		karatsuba_64x64
	ldmia.w	sp!, {r9, r10}
	# add 	r2, r11, #256
	# add 	r1, r12, #256
	# mov 	r0, r10
	# # mov 	r3, #32
	# stmdb	sp!, {r9, r10, r11, r12, lr}
	# #bl 		unrolled_kara_mem
	# bl 		karatsuba_64x64
	# ldmia.w	sp!, {r9, r10, r11, r12, lr}
//r0=i r9=result r10=w_m
//loop3
	movw	r14, #0x1fff
	mov 	r0, #0
	mov 	r11, #128
	add 	r14, r14, r14, lsl #16
toom_cook_4way_mem_asm_loop3:
	ldr 	r5, [r10, #1024]
	ldr 	r3, [r10, #512]
	ldr 	r2, [r10, #256]
	ldr 	r7, [r10, #1536]
	ldr 	r6, [r10, #1280]
	ldr 	r4, [r10, #768]
	ldr 	r1, [r10], #4
	uadd16	r2, r2, r5
	usub16	r6, r6, r5
	usub16	r4, r4, r3
	usub16	r5, r5, r1
	lsr 	r11, r7, #16
	lsl		r12, r7, #6
	pkhbt	r8, r12, r11, lsl #22
	usub16	r5, r5, r8
	lsl		r11, r4, #16
	lsr	 	r12, r4, #1
	pkhtb 	r4, r12, r11, asr #17
	uadd16	r3, r3, r4
	lsr 	r11, r5, #16
	lsl		r12, r5, #1
	pkhbt	r8, r12, r11, lsl #17
	uadd16	r5, r6, r8
	lsr 	r11, r3, #16
	lsl		r12, r3, #6
	pkhbt	r8, r12, r11, lsl #22
	uadd16	r8, r3, r8
	usub16	r2, r2, r8
	usub16	r3, r3, r7
	usub16 	r3, r3, r1
	mov 	r8, #45
	smulbb 	r11, r3, r8
	smultb 	r12, r3, r8
	pkhbt 	r8, r11, r12, lsl #16
	uadd16	r2, r2, r8
	lsr 	r11, r3, #16
	lsl		r12, r3, #3
	pkhbt	r8, r12, r11, lsl #19
	usub16	r5, r5, r8
	movw 	r8, #43691
	smulbb 	r11, r5, r8
	smultb 	r12, r5, r8
	pkhbt 	r8, r11, r12, lsl #16
	lsl		r11, r8, #16
	lsr	 	r12, r8, #3
	pkhtb 	r5, r12, r11, asr #19
	uadd16 	r6, r2, r6
	lsr 	r11, r4, #16
	lsl		r12, r4, #4
	pkhbt	r8, r12, r11, lsl #20
	uadd16	r2, r2, r8
	movw 	r8, #36409
	smulbb 	r11, r2, r8
	smultb 	r12, r2, r8
	pkhbt 	r8, r11, r12, lsl #16
	lsl		r11, r8, #16
	lsr	 	r12, r8, #1
	pkhtb 	r2, r12, r11, asr #17
	usub16	r3, r3, r5
	uadd16	r4, r4, r2
	mov		r8, #0
	usub16	r4, r8, r4
	mov 	r8, #30
	smulbb 	r11, r2, r8
	smultb 	r12, r2, r8
	pkhbt 	r8, r11, r12, lsl #16
	usub16	r6, r8, r6
	movw 	r8, #61167
	smulbb 	r11, r6, r8
	smultb 	r12, r6, r8
	pkhbt 	r8, r11, r12, lsl #16
	lsl		r11, r8, #16
	lsr	 	r12, r8, #1
	pkhtb 	r6, r12, r11, asr #17
//r0=i r9=result r10=w_m
	usub16	r7, r7, r3
	usub16	r6, r6, r2
	usub16	r5, r5, r1
	ldr 	r3, [r9]
	ldr 	r2, [r9, #128]
	ldr 	r1, [r9, #256]
	uadd16	r7, r7, r3
	uadd16	r6, r6, r2
	uadd16	r5, r5, r1
	#ubfx	r7, r7, #0, #13
	#ubfx	r6, r6, #0, #13
	#ubfx	r5, r5, #0, #13
	and		r7, r7, r14
	and		r6, r6, r14
	and 	r5, r5, r14
	cmp 	r0, #63
	add		r0, r0, #2
	sub 	r1, r9, #128
	it 		ls
	addls	r1, r1, #512
	ldr 	r8, [r1]
	str 	r5, [r9, #256]
	str 	r6, [r9, #128]
	str 	r7, [r9], #4
	usub16	r3, r8, r4
	it 		ls
	uadd16ls r3, r8, r4
	cmp 	r0, #126
	#ubfx 	r3, r3, #0, #13
	and 	r3, r3, r14
	str 	r3, [r1]
	bne		toom_cook_4way_mem_asm_loop3
//for(i=0;i<2*(SABER_N/4)-1;i++){ last iteration only halfword!!!
	ldrh 	r5, [r10, #1024]
	ldrh 	r3, [r10, #512]
	ldrh 	r2, [r10, #256]
	ldrh 	r7, [r10, #1536]
	ldrh 	r6, [r10, #1280]
	ldrh 	r4, [r10, #768]
	ldrh 	r1, [r10], #4
	uadd16	r2, r2, r5
	usub16	r6, r6, r5
	usub16	r4, r4, r3
	usub16	r5, r5, r1
	lsl 	r8, r7, #6
	usub16	r5, r5, r8
	lsr		r4, r4, #1
	uadd16	r3, r3, r4
	lsl		r8, r5, #1
	uadd16	r5, r6, r8
	lsl		r8, r3, #6
	uadd16	r8, r3, r8
	usub16	r2, r2, r8
	usub16	r3, r3, r7
	usub16 	r3, r3, r1
	mov 	r8, #45
	smulbb 	r8, r3, r8
	uadd16	r2, r2, r8
	lsl		r8, r3, #3
	usub16	r5, r5, r8
	movw 	r8, #43691
	smulbb 	r8, r5, r8
	lsr		r5, r8, #3
	uadd16 	r6, r2, r6
	lsl		r8, r4, #4
	uadd16	r2, r2, r8
	movw 	r8, #36409
	smulbb 	r8, r2, r8
	lsr 	r2, r8, #1
	usub16	r3, r3, r5
	uadd16	r4, r4, r2
	mov		r8, #0
	usub16	r4, r8, r4
	mov 	r8, #30
	smulbb 	r8, r2, r8
	usub16	r6, r8, r6
	movw 	r8, #61167
	smulbb 	r8, r6, r8
	lsr		r6, r8, #1
//r0=i r9=result r10=w_m
	usub16	r7, r7, r3
	usub16	r6, r6, r2
	usub16	r5, r5, r1
	ldrh 	r3, [r9]
	ldrh 	r2, [r9, #128]
	ldrh 	r1, [r9, #256]
	uadd16	r7, r7, r3
	uadd16	r6, r6, r2
	uadd16	r5, r5, r1
	ubfx	r7, r7, #0, #13
	ubfx	r6, r6, #0, #13
	ubfx	r5, r5, #0, #13
	cmp 	r0, #63
	add		r0, r0, #2
	sub 	r1, r9, #128
	it 		ls
	addls	r1, r1, #512
	ldr 	r8, [r1]
	strh 	r5, [r9, #256]
	strh 	r6, [r9, #128]
	strh 	r7, [r9], #4
	usub16	r3, r8, r4
	it 		ls
	uadd16ls r3, r8, r4
	cmp 	r0, #126
	ubfx 	r3, r3, #0, #13
	strh 	r3, [r1]
exit_toom_cook_4way_mem_asm:
	addw	sp, sp, #3076
	ldmia.w	sp!, {r3, r4, r5, r6, r7, r8, r9, r10, r11, r12, pc}
	bx	lr
	nop
.endfunc

//function for classical Karatsuba in assembly
//*************************************************
// karatsuba_asm(&a, &b, &result);
//*************************************************
.global karatsuba_asm
.func karatsuba_asm, karatsuba_asm
.type karatsuba_asm, %function
karatsuba_asm:
	stmdb	sp!, {r3, r4, r5, r6, r7, r8, r9, r10, r11, r12, lr}
	mov 	r10, r0
	mov 	r11, r1
	mov 	r12, r2
	subw	sp, sp, #636
	mov 	r9, sp
//array allocated
	mov 	r0, r9
	mov 	r1, #0
	movw 	r2, #312
	bl 		memset
//r10=&a[i] r11=&b[i] r12=&result[i] r9=&result_m[i+156] r0=&b[16]
	add 	r9, r9, #312
	add 	r0, r11, #32
//loop1
karatsuba_asm_loop1:
	ldr 	r1, [r11, #96]
	ldr 	r2, [r11, #64]
	ldr 	r4, [r11, #32]
	ldr 	r5, [r11], #4
	uadd16 	r6, r1, r2
	uadd16 	r7, r1, r4
	uadd16 	r8, r2, r5
	uadd16 	r3, r4, r5
	uadd16 	r5, r7, r8
	str 	r8, [r9, #160]
	str 	r7, [r9, #224]
	str 	r6, [r9, #96]
	str 	r5, [r9, #288]
	str 	r3, [r9, #32]
	cmp 	r11, r0
	ldr 	r1, [r10, #96]
	ldr 	r2, [r10, #64]
	ldr 	r4, [r10, #32]
	ldr 	r5, [r10], #4
	uadd16 	r6, r1, r2
	uadd16 	r7, r1, r4
	uadd16 	r8, r2, r5
	uadd16 	r3, r4, r5
	uadd16 	r5, r7, r8
	str 	r8, [r9, #128]
	str 	r7, [r9, #192]
	str 	r6, [r9, #64]
	str 	r5, [r9, #256]
	str 	r3, [r9], #4
	bne 	karatsuba_asm_loop1
//r10=&a[i+16] r11=&b[i+16] r12=&result[i] r9=&result_m[i+156+16] r0=&b[16]
	sub 	r0, r10, #32
	sub 	r1, r11, #32
	mov 	r2, r12
	bl 		school_book_mul2_16_fast
	add 	r1, r1, #32
	add 	r2, r2, #32
	bl 		school_book_mul2_16_fast
	sub 	r0, r9, #32
	mov 	r1, r9
	sub 	r2, r0, #312
	bl 		school_book_mul2_16_fast
	add 	r0, r10, #32
	add 	r1, r11, #32
	add 	r2, r12, #128
	bl 		school_book_mul2_16_fast
	add 	r1, r1, #32
	add 	r2, r2, #32
	bl 		school_book_mul2_16_fast
	add 	r0, r9, #32
	add 	r1, r0, #32
	sub 	r2, r0, #314
	bl 		school_book_mul2_16_fast
	add 	r0, r9, #96
	add 	r1, r0, #32
	sub 	r2, r1, #286
	bl 		school_book_mul2_16_fast
	add 	r0, r0, #32
	add 	r1, r0, #32
	add 	r2, r2, #32
	bl 		school_book_mul2_16_fast
	add 	r0, r0, #32
	add 	r1, r0, #32
	sub 	r2, r2, #158
	bl 		school_book_mul2_16_fast
//r10=&a[i+16] r11=&b[i+16] r12=&result[i] r9=&result_m[i+156+16]
	sub 	r11, r9, #344
	add 	r10, r12, #60
//r10=&result[30] r11=&res_m[i] r12=&result[i]
karatsuba_asm_loop2:
	ldr 	r0, [r11, #62]
	ldr 	r1, [r12, #128]
	ldr 	r2, [r12, #192]
	ldr 	r3, [r11, #124]
	ldr 	r4, [r11, #186]
	ldr 	r5, [r11, #250]
	ldr 	r6, [r11]
	ldr 	r7, [r12], #4
	ldr 	r8, [r12, #60]
	uadd16 	r1, r1, r2
	uadd16 	r4, r4, r5
	uadd16 	r7, r7, r8
	usub16 	r0, r0, r1
	usub16 	r3, r3, r4
	usub16 	r6, r6, r7
	cmp 	r10, r12
	str 	r0, [r11, #62]
	str 	r3, [r11, #124]
	str 	r6, [r11], #4
	bne 	karatsuba_asm_loop2
	ldrh 	r0, [r11, #62]
	ldrh 	r1, [r12, #128]
	ldrh 	r2, [r12, #192]
	ldrh 	r3, [r11, #124]
	ldrh 	r4, [r11, #186]
	ldrh 	r5, [r11, #250]
	ldrh 	r6, [r11]
	ldrh 	r7, [r12], #-28
	ldrh 	r8, [r12, #92]
	uadd16 	r1, r1, r2
	uadd16 	r4, r4, r5
	uadd16 	r7, r7, r8
	usub16 	r0, r0, r1
	usub16 	r3, r3, r4
	usub16 	r6, r6, r7
	strh 	r0, [r11, #62]
	strh 	r3, [r11, #124]
	strh 	r6, [r11], #-60
//r10=&result[46] r11=&res_m[i] r12=&result[i+16]
	add 	r10, r10, #32
karatsuba_asm_loop3:
	ldr 	r0, [r12, #128]
	ldr 	r1, [r11, #62]
	ldr 	r4, [r11, #218]
	ldr 	r5, [r11, #124]
	ldr 	r2, [r12], #4
	ldr 	r3, [r11], #4
	uadd16 	r0, r0, r1
	uadd16 	r4, r4, r5
	uadd16 	r2, r2, r3
	cmp 	r10, r12
	str 	r0, [r12, #124]
	str 	r2, [r12, #-4]
	str 	r4, [r11, #214]
	bne 	karatsuba_asm_loop3
	ldrh 	r0, [r12, #128]
	ldrh 	r1, [r11, #62]
	ldrh 	r4, [r11, #218]
	ldrh 	r5, [r11, #124]
	ldrh 	r2, [r12], #-92
	ldrh 	r3, [r11], #126
	uadd16 	r0, r0, r1
	uadd16 	r4, r4, r5
	uadd16 	r2, r2, r3
	strh 	r0, [r12, #220]
	strh 	r2, [r12, #92]
	strh 	r4, [r11, #92]
//r10=&res_m[i+93+60] r11=&res_m[i+93] r12=&result[i]
	add 	r10, r11, #120
karatsuba_asm_loop4:
	ldr 	r2, [r12, #128]
	ldr 	r1, [r12], #4
	ldr 	r0, [r11], #4
	ldr 	r5, [r12, #128]
	ldr 	r4, [r12], #4
	ldr 	r3, [r11], #4
	uadd16 	r1, r1, r2
	usub16 	r0, r0, r1
	uadd16 	r4, r4, r5
	usub16 	r3, r3, r4
	cmp 	r10, r11
	str 	r0, [r11, #-8]
	str 	r3, [r11, #-4]
	bne 	karatsuba_asm_loop4
	ldr 	r2, [r12, #128]
	ldr 	r1, [r12], #4
	ldr 	r0, [r11], #4
	ldr 	r5, [r12, #128]
	ldr 	r4, [r12], #-60
	ldr 	r3, [r11], #-124
	uadd16 	r1, r1, r2
	usub16 	r0, r0, r1
	uadd16 	r4, r4, r5
	usub16 	r3, r3, r4
	str 	r0, [r11, #120]
	strh 	r3, [r11, #124]
//r10=&res_m[i+93+60] r11=&res_m[i+93] r12=&result[i+32]
karatsuba_asm_loop5:
	ldr 	r0, [r11], #4
	ldr 	r1, [r12], #4
	ldr 	r2, [r11], #4
	ldr 	r3, [r12], #4
	uadd16 	r0, r0, r1
	cmp 	r10, r11
	uadd16 	r2, r2, r3
	str 	r0, [r12, #-8]
	str 	r2, [r12, #-4]
	bne 	karatsuba_asm_loop5
	ldr 	r0, [r11], #4
	ldr 	r1, [r12], #4
	ldr 	r2, [r11], #4
	ldr 	r3, [r12], #4
	uadd16 	r0, r0, r1
	cmp 	r10, r11
	uadd16 	r2, r2, r3
	str 	r0, [r12, #-8]
	strh 	r2, [r12, #-4]
exit_karatsuba_asm:
	addw	sp, sp, #636
	ldmia.w	sp!, {r3, r4, r5, r6, r7, r8, r9, r10, r11, r12, pc}
	bx	lr
	nop
.endfunc

.global school_book_mul2_16_fast
.func school_book_mul2_16_fast, school_book_mul2_16_fast
.type school_book_mul2_16_fast, %function
.align 2
school_book_mul2_16_fast:
	stmdb	sp!, {r3, r4, r5, r6, r7, r8, r9, r10, r11, r12, lr}
	#push {lr}
	ldr r6, [r1, #0]
	ldr.w ip, [r1, #4]
	ldr.w r3, [r1, #8]
	ldr.w sl, [r1, #12]
	ldr.w r7, [r0, #0]
	ldr.w r8, [r0, #4]
	ldr.w r4, [r0, #8]
	ldr.w lr, [r0, #12]
	smulbb r9, r7, r6
	smuadx fp, r7, r6
	pkhbt r9, r9, fp, lsl #16
	str.w r9, [r2]
	smuadx fp, r7, ip
	smulbb r5, r7, ip
	pkhbt r9, r8, r7
	smladx fp, r8, r6, fp
	smlad r5, r9, r6, r5
	pkhbt fp, r5, fp, lsl #16
	str.w fp, [r2, #4]
	smulbb r5, r3, r7
	smuadx fp, r3, r7
	smlad r5, r9, ip, r5
	pkhbt r9, r4, r8
	smlad r5, r9, r6, r5
	smladx fp, r8, ip, fp
	smladx fp, r4, r6, fp
	pkhbt fp, r5, fp, lsl #16
	str.w fp, [r2, #8]
	smulbb r5, sl, r7
	smuadx fp, sl, r7
	smlad r5, ip, r9, r5
	pkhbt r9, r8, r7
	smlad r5, r3, r9, r5
	pkhbt r9, lr, r4
	smlad r5, r6, r9, r5
	smladx fp, r3, r8, fp
	smladx fp, ip, r4, fp
	smladx fp, r6, lr, fp
	pkhbt fp, r5, fp, lsl #16
	str.w fp, [r2, #12]
	smultt r5, r6, lr
	smuadx fp, sl, r8
	smlad r5, ip, r9, r5
	pkhbt r9, r8, r7
	smlad r5, sl, r9, r5
	pkhbt r9, r4, r8
	smlad r5, r3, r9, r5
	smladx fp, r3, r4, fp
	smladx fp, ip, lr, fp
	pkhbt fp, r5, fp, lsl #16
	str.w fp, [r2, #16]
	smultt r5, ip, lr
	smuadx fp, sl, r4
	smlad r5, sl, r9, r5
	pkhbt r9, lr, r4
	smlad r5, r3, r9, r5
	smladx fp, r3, lr, fp
	pkhbt fp, r5, fp, lsl #16
	str.w fp, [r2, #20]
	smuad r5, sl, r9
	smuadx fp, sl, lr
	smlatt r5, r3, lr, r5
	pkhbt fp, r5, fp, lsl #16
	str.w fp, [r2, #24]
	smultt fp, sl, lr
	movt fp, #0
	str.w fp, [r2, #28]
	ldr.w r7, [r0, #16]
	ldr.w r8, [r0, #20]
	ldr.w r4, [r0, #24]
	ldr.w lr, [r0, #28]
	ldr.w r9, [r2, #16]
	ldr.w r5, [r2, #20]
	mov.w fp, r9, lsr #16
	smlabb r9, r7, r6, r9
	smladx fp, r7, r6, fp
	pkhbt r9, r9, fp, lsl #16
	str.w r9, [r2, #16]
	mov.w fp, r5, lsr #16
	smladx fp, r7, ip, fp
	smlabb r5, r7, ip, r5
	pkhbt r9, r8, r7
	smladx fp, r8, r6, fp
	smlad r5, r9, r6, r5
	pkhbt fp, r5, fp, lsl #16
	ldr.w r5, [r2, #24]
	str.w fp, [r2, #20]
	mov.w fp, r5, lsr #16
	smlabb r5, r3, r7, r5
	smladx fp, r3, r7, fp
	smlad r5, r9, ip, r5
	pkhbt r9, r4, r8
	smlad r5, r9, r6, r5
	smladx fp, r8, ip, fp
	smladx fp, r4, r6, fp
	pkhbt fp, r5, fp, lsl #16
	ldr.w r5, [r2, #28]
	str.w fp, [r2, #24]
	mov.w fp, r5, lsr #16
	smlabb r5, sl, r7, r5
	smladx fp, sl, r7, fp
	smlad r5, ip, r9, r5
	pkhbt r9, r8, r7
	smlad r5, r3, r9, r5
	pkhbt r9, lr, r4
	smlad r5, r6, r9, r5
	smladx fp, r3, r8, fp
	smladx fp, ip, r4, fp
	smladx fp, r6, lr, fp
	pkhbt fp, r5, fp, lsl #16
	str.w fp, [r2, #28]
	smultt r5, r6, lr
	smuadx fp, sl, r8
	smlad r5, ip, r9, r5
	pkhbt r9, r8, r7
	smlad r5, sl, r9, r5
	pkhbt r9, r4, r8
	smlad r5, r3, r9, r5
	smladx fp, r3, r4, fp
	smladx fp, ip, lr, fp
	pkhbt fp, r5, fp, lsl #16
	str.w fp, [r2, #32]
	smultt r5, ip, lr
	smuadx fp, sl, r4
	smlad r5, sl, r9, r5
	pkhbt r9, lr, r4
	smlad r5, r3, r9, r5
	smladx fp, r3, lr, fp
	pkhbt fp, r5, fp, lsl #16
	str.w fp, [r2, #36]
	smuad r5, sl, r9
	smuadx fp, sl, lr
	smlatt r5, r3, lr, r5
	pkhbt fp, r5, fp, lsl #16
	str.w fp, [r2, #40]
	smultt fp, sl, lr
	movt fp, #0
	str.w fp, [r2, #44]
	ldr.w r6, [r1, #16]
	ldr.w ip, [r1, #20]
	ldr.w r3, [r1, #24]
	ldr.w sl, [r1, #28]
	ldr.w r9, [r2, #32]
	ldr.w r5, [r2, #36]
	mov.w fp, r9, lsr #16
	smlabb r9, r7, r6, r9
	smladx fp, r7, r6, fp
	pkhbt r9, r9, fp, lsl #16
	str.w r9, [r2, #32]
	mov.w fp, r5, lsr #16
	smladx fp, r7, ip, fp
	smlabb r5, r7, ip, r5
	pkhbt r9, r8, r7
	smladx fp, r8, r6, fp
	smlad r5, r9, r6, r5
	pkhbt fp, r5, fp, lsl #16
	ldr.w r5, [r2, #40]
	str.w fp, [r2, #36]
	mov.w fp, r5, lsr #16
	smlabb r5, r3, r7, r5
	smladx fp, r3, r7, fp
	smlad r5, r9, ip, r5
	pkhbt r9, r4, r8
	smlad r5, r9, r6, r5
	smladx fp, r8, ip, fp
	smladx fp, r4, r6, fp
	pkhbt fp, r5, fp, lsl #16
	ldr.w r5, [r2, #44]
	str.w fp, [r2, #40]
	mov.w fp, r5, lsr #16
	smlabb r5, sl, r7, r5
	smladx fp, sl, r7, fp
	smlad r5, ip, r9, r5
	pkhbt r9, r8, r7
	smlad r5, r3, r9, r5
	pkhbt r9, lr, r4
	smlad r5, r6, r9, r5
	smladx fp, r3, r8, fp
	smladx fp, ip, r4, fp
	smladx fp, r6, lr, fp
	pkhbt fp, r5, fp, lsl #16
	str.w fp, [r2, #44]
	smultt r5, r6, lr
	smuadx fp, sl, r8
	smlad r5, ip, r9, r5
	pkhbt r9, r8, r7
	smlad r5, sl, r9, r5
	pkhbt r9, r4, r8
	smlad r5, r3, r9, r5
	smladx fp, r3, r4, fp
	smladx fp, ip, lr, fp
	pkhbt fp, r5, fp, lsl #16
	str.w fp, [r2, #48]
	smultt r5, ip, lr
	smuadx fp, sl, r4
	smlad r5, sl, r9, r5
	pkhbt r9, lr, r4
	smlad r5, r3, r9, r5
	smladx fp, r3, lr, fp
	pkhbt fp, r5, fp, lsl #16
	str.w fp, [r2, #52]
	smuad r5, sl, r9
	smuadx fp, sl, lr
	smlatt r5, r3, lr, r5
	pkhbt fp, r5, fp, lsl #16
	str.w fp, [r2, #56]
	smultt fp, sl, lr
	strh.w fp, [r2, #60]
	ldr.w r7, [r0, #0]
	ldr.w r8, [r0, #4]
	ldr.w r4, [r0, #8]
	ldr.w lr, [r0, #12]
	ldr.w r9, [r2, #16]
	ldr.w r5, [r2, #20]
	mov.w fp, r9, lsr #16
	smlabb r9, r7, r6, r9
	smladx fp, r7, r6, fp
	pkhbt r9, r9, fp, lsl #16
	str.w r9, [r2, #16]
	mov.w fp, r5, lsr #16
	smladx fp, r7, ip, fp
	smlabb r5, r7, ip, r5
	pkhbt r9, r8, r7
	smladx fp, r8, r6, fp
	smlad r5, r9, r6, r5
	pkhbt fp, r5, fp, lsl #16
	ldr.w r5, [r2, #24]
	str.w fp, [r2, #20]
	mov.w fp, r5, lsr #16
	smlabb r5, r3, r7, r5
	smladx fp, r3, r7, fp
	smlad r5, r9, ip, r5
	pkhbt r9, r4, r8
	smlad r5, r9, r6, r5
	smladx fp, r8, ip, fp
	smladx fp, r4, r6, fp
	pkhbt fp, r5, fp, lsl #16
	ldr.w r5, [r2, #28]
	str.w fp, [r2, #24]
	mov.w fp, r5, lsr #16
	smlabb r5, sl, r7, r5
	smladx fp, sl, r7, fp
	smlad r5, ip, r9, r5
	pkhbt r9, r8, r7
	smlad r5, r3, r9, r5
	pkhbt r9, lr, r4
	smlad r5, r6, r9, r5
	smladx fp, r3, r8, fp
	smladx fp, ip, r4, fp
	smladx fp, r6, lr, fp
	pkhbt fp, r5, fp, lsl #16
	ldr.w r5, [r2, #32]
	str.w fp, [r2, #28]
	mov.w fp, r5, lsr #16
	smlatt r5, r6, lr, r5
	smladx fp, sl, r8, fp
	smlad r5, ip, r9, r5
	pkhbt r9, r8, r7
	smlad r5, sl, r9, r5
	pkhbt r9, r4, r8
	smlad r5, r3, r9, r5
	smladx fp, r3, r4, fp
	smladx fp, ip, lr, fp
	pkhbt fp, r5, fp, lsl #16
	ldr.w r5, [r2, #36]
	str.w fp, [r2, #32]
	mov.w fp, r5, lsr #16
	smlatt r5, ip, lr, r5
	smladx fp, sl, r4, fp
	smlad r5, sl, r9, r5
	pkhbt r9, lr, r4
	smlad r5, r3, r9, r5
	smladx fp, r3, lr, fp
	pkhbt fp, r5, fp, lsl #16
	ldr.w r5, [r2, #40]
	str.w fp, [r2, #36]
	mov.w fp, r5, lsr #16
	smlad r5, sl, r9, r5
	smladx fp, sl, lr, fp
	smlatt r5, r3, lr, r5
	pkhbt fp, r5, fp, lsl #16
	ldrh.w r5, [r2, #44]
	str.w fp, [r2, #40]
	smlatt fp, sl, lr, r5
	strh.w fp, [r2, #44]
	ldmia.w	sp!, {r3, r4, r5, r6, r7, r8, r9, r10, r11, r12, pc}
	#ldr.w lr, [sp], #4
	#bx lr
.endfunc
