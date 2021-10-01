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
	mov 	r4, r1
	sub 	r0, r2, #2560
	mov 	r1, #0
	mov 	r2, #1792
	bl 		memset
	mov 	r10, r0
	sub 	r2, r11, #128
	sub 	r1, r4, #128
	add		r0, r10, #1536
	# mov 	r3, #32
	stmdb	sp!, {r4, r9, r10, r11}
	#bl 		unrolled_kara_mem
	bl 		karatsuba_64x64
	ldmia.w	sp!, {r4, r9, r10, r11}
	add 	r2, r11, #256
	add 	r1, r4, #256
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
