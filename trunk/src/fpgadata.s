	.file	"fpgadata.cpp"
	.section	.rodata
	.type	_ZStL19piecewise_construct, @object
	.size	_ZStL19piecewise_construct, 1
_ZStL19piecewise_construct:
	.zero	1
.LC0:
	.string	"stoi"
	.section	.text._ZSt4stoiRKSsPmi,"axG",@progbits,_ZSt4stoiRKSsPmi,comdat
	.weak	_ZSt4stoiRKSsPmi
	.type	_ZSt4stoiRKSsPmi, @function
_ZSt4stoiRKSsPmi:
.LFB665:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movl	%edx, -20(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNKSs5c_strEv
	movl	-20(%rbp), %ecx
	movq	-16(%rbp), %rdx
	movl	%ecx, %r8d
	movq	%rdx, %rcx
	movq	%rax, %rdx
	movl	$.LC0, %esi
	movl	$strtol, %edi
	call	_ZN9__gnu_cxx6__stoaIlicIiEEET0_PFT_PKT1_PPS3_DpT2_EPKcS5_PmS9_
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE665:
	.size	_ZSt4stoiRKSsPmi, .-_ZSt4stoiRKSsPmi
	.local	_ZStL8__ioinit
	.comm	_ZStL8__ioinit,1,1
	.section	.text._ZSt4setwi,"axG",@progbits,_ZSt4setwi,comdat
	.weak	_ZSt4setwi
	.type	_ZSt4setwi, @function
_ZSt4setwi:
.LFB1320:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, -4(%rbp)
	movl	-4(%rbp), %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1320:
	.size	_ZSt4setwi, .-_ZSt4setwi
	.section	.text._ZN8yFramDat10get_lengthEv,"axG",@progbits,_ZN8yFramDat10get_lengthEv,comdat
	.align 2
	.weak	_ZN8yFramDat10get_lengthEv
	.type	_ZN8yFramDat10get_lengthEv, @function
_ZN8yFramDat10get_lengthEv:
.LFB1327:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	16(%rax), %rax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1327:
	.size	_ZN8yFramDat10get_lengthEv, .-_ZN8yFramDat10get_lengthEv
	.section	.text._ZN8yFramDat5clearEv,"axG",@progbits,_ZN8yFramDat5clearEv,comdat
	.align 2
	.weak	_ZN8yFramDat5clearEv
	.type	_ZN8yFramDat5clearEv, @function
_ZN8yFramDat5clearEv:
.LFB1328:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	$0, 16(%rax)
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1328:
	.size	_ZN8yFramDat5clearEv, .-_ZN8yFramDat5clearEv
	.section	.rodata
.LC1:
	.string	""
	.text
	.align 2
	.globl	_ZN8yOptLongC2EiPPc
	.type	_ZN8yOptLongC2EiPPc, @function
_ZN8yOptLongC2EiPPc:
.LFB1330:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -8(%rbp)
	movl	%esi, -12(%rbp)
	movq	%rdx, -24(%rbp)
	movq	-8(%rbp), %rax
	movq	-24(%rbp), %rdx
	movl	-12(%rbp), %ecx
	movl	%ecx, %esi
	movq	%rax, %rdi
	call	_ZN7yOptionC2EiPPc
	movq	-8(%rbp), %rax
	movq	$.LC1, 32(%rax)
	movq	-8(%rbp), %rax
	movq	$.LC1, 40(%rax)
	movq	-8(%rbp), %rax
	movq	$.LC1, 48(%rax)
	movq	-8(%rbp), %rax
	movb	$0, 56(%rax)
	movq	-8(%rbp), %rax
	movb	$0, 57(%rax)
	movq	-8(%rbp), %rax
	movb	$0, 58(%rax)
	movq	-8(%rbp), %rax
	movb	$0, 59(%rax)
	movq	-8(%rbp), %rax
	movb	$0, 60(%rax)
	movq	-8(%rbp), %rax
	movb	$0, 61(%rax)
	movq	-8(%rbp), %rax
	movb	$0, 62(%rax)
	movq	-8(%rbp), %rax
	movb	$0, 63(%rax)
	movq	-8(%rbp), %rax
	movl	$64, 64(%rax)
	movq	-8(%rbp), %rax
	movl	$1, 68(%rax)
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1330:
	.size	_ZN8yOptLongC2EiPPc, .-_ZN8yOptLongC2EiPPc
	.globl	_ZN8yOptLongC1EiPPc
	.set	_ZN8yOptLongC1EiPPc,_ZN8yOptLongC2EiPPc
	.section	.rodata
.LC2:
	.string	"--npix="
.LC3:
	.string	"--repeat="
.LC4:
	.string	"--prefix="
.LC5:
	.string	"--csv"
.LC6:
	.string	"--tab"
.LC7:
	.string	"--hex"
.LC8:
	.string	"--raw"
.LC9:
	.string	"--delta"
.LC10:
	.string	"--verbose"
.LC11:
	.string	"-v"
.LC12:
	.string	"--debug"
.LC13:
	.string	"--TESTOP"
.LC14:
	.string	"--help"
.LC15:
	.string	"-"
.LC16:
	.string	"--"
.LC17:
	.string	"unknown option:  "
.LC18:
	.string	"extra arguments:  "
	.text
	.align 2
	.globl	_ZN8yOptLong13parse_optionsEv
	.type	_ZN8yOptLong13parse_optionsEv, @function
_ZN8yOptLong13parse_optionsEv:
.LFB1332:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	.cfi_lsda 0x3,.LLSDA1332
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$72, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -72(%rbp)
	jmp	.L10
.L27:
	movq	-72(%rbp), %rax
	movl	$.LC2, %esi
	movq	%rax, %rdi
.LEHB0:
	call	_ZN7yOption2isEPKc
	testb	%al, %al
	je	.L11
	movq	-72(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7yOption3valEv
	movq	-72(%rbp), %rdx
	movq	%rax, 32(%rdx)
	jmp	.L10
.L11:
	movq	-72(%rbp), %rax
	movl	$.LC3, %esi
	movq	%rax, %rdi
	call	_ZN7yOption2isEPKc
	testb	%al, %al
	je	.L12
	movq	-72(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7yOption3valEv
	movq	-72(%rbp), %rdx
	movq	%rax, 40(%rdx)
	jmp	.L10
.L12:
	movq	-72(%rbp), %rax
	movl	$.LC4, %esi
	movq	%rax, %rdi
	call	_ZN7yOption2isEPKc
	testb	%al, %al
	je	.L13
	movq	-72(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7yOption3valEv
	movq	-72(%rbp), %rdx
	movq	%rax, 48(%rdx)
	jmp	.L10
.L13:
	movq	-72(%rbp), %rax
	movl	$.LC5, %esi
	movq	%rax, %rdi
	call	_ZN7yOption2isEPKc
	testb	%al, %al
	je	.L14
	movq	-72(%rbp), %rax
	movb	$1, 56(%rax)
	jmp	.L10
.L14:
	movq	-72(%rbp), %rax
	movl	$.LC6, %esi
	movq	%rax, %rdi
	call	_ZN7yOption2isEPKc
	testb	%al, %al
	je	.L15
	movq	-72(%rbp), %rax
	movb	$1, 57(%rax)
	jmp	.L10
.L15:
	movq	-72(%rbp), %rax
	movl	$.LC7, %esi
	movq	%rax, %rdi
	call	_ZN7yOption2isEPKc
	testb	%al, %al
	je	.L16
	movq	-72(%rbp), %rax
	movb	$1, 58(%rax)
	jmp	.L10
.L16:
	movq	-72(%rbp), %rax
	movl	$.LC8, %esi
	movq	%rax, %rdi
	call	_ZN7yOption2isEPKc
	testb	%al, %al
	je	.L17
	movq	-72(%rbp), %rax
	movb	$1, 59(%rax)
	jmp	.L10
.L17:
	movq	-72(%rbp), %rax
	movl	$.LC9, %esi
	movq	%rax, %rdi
	call	_ZN7yOption2isEPKc
	testb	%al, %al
	je	.L18
	movq	-72(%rbp), %rax
	movb	$1, 60(%rax)
	jmp	.L10
.L18:
	movq	-72(%rbp), %rax
	movl	$.LC10, %esi
	movq	%rax, %rdi
	call	_ZN7yOption2isEPKc
	testb	%al, %al
	je	.L19
	movq	-72(%rbp), %rax
	movb	$1, 61(%rax)
	jmp	.L10
.L19:
	movq	-72(%rbp), %rax
	movl	$.LC11, %esi
	movq	%rax, %rdi
	call	_ZN7yOption2isEPKc
	testb	%al, %al
	je	.L20
	movq	-72(%rbp), %rax
	movb	$1, 61(%rax)
	jmp	.L10
.L20:
	movq	-72(%rbp), %rax
	movl	$.LC12, %esi
	movq	%rax, %rdi
	call	_ZN7yOption2isEPKc
	testb	%al, %al
	je	.L21
	movq	-72(%rbp), %rax
	movb	$1, 62(%rax)
	jmp	.L10
.L21:
	movq	-72(%rbp), %rax
	movl	$.LC13, %esi
	movq	%rax, %rdi
	call	_ZN7yOption2isEPKc
	testb	%al, %al
	je	.L22
	movq	-72(%rbp), %rax
	movb	$1, 63(%rax)
	jmp	.L10
.L22:
	movq	-72(%rbp), %rax
	movl	$.LC14, %esi
	movq	%rax, %rdi
	call	_ZN7yOption2isEPKc
	testb	%al, %al
	je	.L23
	movq	-72(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN8yOptLong11print_usageEv
	movl	$0, %edi
	call	exit
.L23:
	movq	-72(%rbp), %rax
	movl	$.LC15, %esi
	movq	%rax, %rdi
	call	_ZN7yOption2isEPKc
	testb	%al, %al
	je	.L24
	jmp	.L25
.L24:
	movq	-72(%rbp), %rax
	movl	$.LC16, %esi
	movq	%rax, %rdi
	call	_ZN7yOption2isEPKc
	testb	%al, %al
	je	.L26
	movq	-72(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7yOption4nextEv
	jmp	.L25
.L26:
	movq	-72(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7yOption14current_optionEv
	movq	%rax, %rsi
	movl	$.LC17, %edi
	call	_ZN5Error3errEPKcS1_
.L10:
	movq	-72(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7yOption4nextEv
.LEHE0:
	testb	%al, %al
	jne	.L27
.L25:
	leaq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSaIcEC1Ev
	movq	-72(%rbp), %rax
	movq	32(%rax), %rcx
	leaq	-32(%rbp), %rdx
	leaq	-48(%rbp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
.LEHB1:
	call	_ZNSsC1EPKcRKSaIcE
.LEHE1:
	leaq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSaIcED1Ev
	leaq	-49(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSaIcEC1Ev
	movq	-72(%rbp), %rax
	movq	40(%rax), %rcx
	leaq	-49(%rbp), %rdx
	leaq	-32(%rbp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
.LEHB2:
	call	_ZNSsC1EPKcRKSaIcE
.LEHE2:
	leaq	-49(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSaIcED1Ev
	leaq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNKSs6lengthEv
	testq	%rax, %rax
	setne	%al
	testb	%al, %al
	je	.L28
	leaq	-48(%rbp), %rax
	movl	$10, %edx
	movl	$0, %esi
	movq	%rax, %rdi
.LEHB3:
	call	_ZSt4stoiRKSsPmi
	movq	-72(%rbp), %rdx
	movl	%eax, 64(%rdx)
.L28:
	leaq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNKSs6lengthEv
	testq	%rax, %rax
	setne	%al
	testb	%al, %al
	je	.L29
	leaq	-32(%rbp), %rax
	movl	$10, %edx
	movl	$0, %esi
	movq	%rax, %rdi
	call	_ZSt4stoiRKSsPmi
	movq	-72(%rbp), %rdx
	movl	%eax, 68(%rdx)
.L29:
	movq	-72(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7yOption8get_argcEv
	testl	%eax, %eax
	setg	%al
	testb	%al, %al
	je	.L30
	movq	-72(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7yOption8next_argEv
	movq	%rax, %rsi
	movl	$.LC18, %edi
	call	_ZN5Error3errEPKcS1_
.LEHE3:
.L30:
	leaq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSsD1Ev
	leaq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSsD1Ev
	jmp	.L38
.L35:
	movq	%rax, %rbx
	leaq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSaIcED1Ev
	movq	%rbx, %rax
	movq	%rax, %rdi
.LEHB4:
	call	_Unwind_Resume
.L36:
	movq	%rax, %rbx
	leaq	-49(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSaIcED1Ev
	jmp	.L33
.L37:
	movq	%rax, %rbx
	leaq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSsD1Ev
.L33:
	leaq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSsD1Ev
	movq	%rbx, %rax
	movq	%rax, %rdi
	call	_Unwind_Resume
.LEHE4:
.L38:
	addq	$72, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1332:
	.globl	__gxx_personality_v0
	.section	.gcc_except_table,"a",@progbits
.LLSDA1332:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE1332-.LLSDACSB1332
.LLSDACSB1332:
	.uleb128 .LEHB0-.LFB1332
	.uleb128 .LEHE0-.LEHB0
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB1-.LFB1332
	.uleb128 .LEHE1-.LEHB1
	.uleb128 .L35-.LFB1332
	.uleb128 0
	.uleb128 .LEHB2-.LFB1332
	.uleb128 .LEHE2-.LEHB2
	.uleb128 .L36-.LFB1332
	.uleb128 0
	.uleb128 .LEHB3-.LFB1332
	.uleb128 .LEHE3-.LEHB3
	.uleb128 .L37-.LFB1332
	.uleb128 0
	.uleb128 .LEHB4-.LFB1332
	.uleb128 .LEHE4-.LEHB4
	.uleb128 0
	.uleb128 0
.LLSDACSE1332:
	.text
	.size	_ZN8yOptLong13parse_optionsEv, .-_ZN8yOptLong13parse_optionsEv
	.section	.rodata
.LC19:
	.string	"--npix        = "
.LC20:
	.string	"--repeat      = "
.LC21:
	.string	"--prefix      = "
.LC22:
	.string	"--csv         = "
.LC23:
	.string	"--tab         = "
.LC24:
	.string	"--hex         = "
.LC25:
	.string	"--raw         = "
.LC26:
	.string	"--delta       = "
.LC27:
	.string	"--verbose     = "
.LC28:
	.string	"--debug       = "
.LC29:
	.string	"arg:          = "
.LC30:
	.string	"npix_n        = "
.LC31:
	.string	"repeat_n      = "
	.text
	.align 2
	.globl	_ZN8yOptLong18print_option_flagsEv
	.type	_ZN8yOptLong18print_option_flagsEv, @function
_ZN8yOptLong18print_option_flagsEv:
.LFB1333:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$40, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -40(%rbp)
	movq	-40(%rbp), %rax
	movq	32(%rax), %rbx
	movl	$.LC19, %esi
	movl	$_ZSt4cout, %edi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	movq	%rbx, %rsi
	movq	%rax, %rdi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	movl	$_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_, %esi
	movq	%rax, %rdi
	call	_ZNSolsEPFRSoS_E
	movq	-40(%rbp), %rax
	movq	40(%rax), %rbx
	movl	$.LC20, %esi
	movl	$_ZSt4cout, %edi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	movq	%rbx, %rsi
	movq	%rax, %rdi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	movl	$_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_, %esi
	movq	%rax, %rdi
	call	_ZNSolsEPFRSoS_E
	movq	-40(%rbp), %rax
	movq	48(%rax), %rbx
	movl	$.LC21, %esi
	movl	$_ZSt4cout, %edi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	movq	%rbx, %rsi
	movq	%rax, %rdi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	movl	$_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_, %esi
	movq	%rax, %rdi
	call	_ZNSolsEPFRSoS_E
	movq	-40(%rbp), %rax
	movzbl	56(%rax), %eax
	movzbl	%al, %ebx
	movl	$.LC22, %esi
	movl	$_ZSt4cout, %edi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	movl	%ebx, %esi
	movq	%rax, %rdi
	call	_ZNSolsEb
	movl	$_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_, %esi
	movq	%rax, %rdi
	call	_ZNSolsEPFRSoS_E
	movq	-40(%rbp), %rax
	movzbl	57(%rax), %eax
	movzbl	%al, %ebx
	movl	$.LC23, %esi
	movl	$_ZSt4cout, %edi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	movl	%ebx, %esi
	movq	%rax, %rdi
	call	_ZNSolsEb
	movl	$_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_, %esi
	movq	%rax, %rdi
	call	_ZNSolsEPFRSoS_E
	movq	-40(%rbp), %rax
	movzbl	58(%rax), %eax
	movzbl	%al, %ebx
	movl	$.LC24, %esi
	movl	$_ZSt4cout, %edi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	movl	%ebx, %esi
	movq	%rax, %rdi
	call	_ZNSolsEb
	movl	$_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_, %esi
	movq	%rax, %rdi
	call	_ZNSolsEPFRSoS_E
	movq	-40(%rbp), %rax
	movzbl	59(%rax), %eax
	movzbl	%al, %ebx
	movl	$.LC25, %esi
	movl	$_ZSt4cout, %edi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	movl	%ebx, %esi
	movq	%rax, %rdi
	call	_ZNSolsEb
	movl	$_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_, %esi
	movq	%rax, %rdi
	call	_ZNSolsEPFRSoS_E
	movq	-40(%rbp), %rax
	movzbl	60(%rax), %eax
	movzbl	%al, %ebx
	movl	$.LC26, %esi
	movl	$_ZSt4cout, %edi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	movl	%ebx, %esi
	movq	%rax, %rdi
	call	_ZNSolsEb
	movl	$_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_, %esi
	movq	%rax, %rdi
	call	_ZNSolsEPFRSoS_E
	movq	-40(%rbp), %rax
	movzbl	61(%rax), %eax
	movzbl	%al, %ebx
	movl	$.LC27, %esi
	movl	$_ZSt4cout, %edi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	movl	%ebx, %esi
	movq	%rax, %rdi
	call	_ZNSolsEb
	movl	$_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_, %esi
	movq	%rax, %rdi
	call	_ZNSolsEPFRSoS_E
	movq	-40(%rbp), %rax
	movzbl	62(%rax), %eax
	movzbl	%al, %ebx
	movl	$.LC28, %esi
	movl	$_ZSt4cout, %edi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	movl	%ebx, %esi
	movq	%rax, %rdi
	call	_ZNSolsEb
	movl	$_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_, %esi
	movq	%rax, %rdi
	call	_ZNSolsEPFRSoS_E
	jmp	.L40
.L41:
	movl	$.LC29, %esi
	movl	$_ZSt4cout, %edi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	movq	-24(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	movl	$_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_, %esi
	movq	%rax, %rdi
	call	_ZNSolsEPFRSoS_E
.L40:
	movq	-40(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7yOption8next_argEv
	movq	%rax, -24(%rbp)
	cmpq	$0, -24(%rbp)
	setne	%al
	testb	%al, %al
	jne	.L41
	movq	-40(%rbp), %rax
	movl	64(%rax), %ebx
	movl	$.LC30, %esi
	movl	$_ZSt4cout, %edi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	movl	%ebx, %esi
	movq	%rax, %rdi
	call	_ZNSolsEi
	movl	$_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_, %esi
	movq	%rax, %rdi
	call	_ZNSolsEPFRSoS_E
	movq	-40(%rbp), %rax
	movl	68(%rax), %ebx
	movl	$.LC31, %esi
	movl	$_ZSt4cout, %edi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	movl	%ebx, %esi
	movq	%rax, %rdi
	call	_ZNSolsEi
	movl	$_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_, %esi
	movq	%rax, %rdi
	call	_ZNSolsEPFRSoS_E
	addq	$40, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1333:
	.size	_ZN8yOptLong18print_option_flagsEv, .-_ZN8yOptLong18print_option_flagsEv
	.section	.rodata
	.align 8
.LC32:
	.string	"    FPGA data transfer on Raspberry Pi\nusage:  "
	.align 8
.LC33:
	.ascii	" [options]\n  output forms:  (default is none)\n    --csv   "
	.ascii	"            CSV format\n    --tab               tabular form"
	.ascii	"at\n    --hex               hex data dump\n    --raw        "
	.ascii	"       raw hex data\n    --delta             delta data in d"
	.ascii	"ecimal\n  o"
	.string	"ptions:\n    --npix=N            number of pixel to collect\n    --repeat=N          repeat data read loop N times\n    --help              show this usage\n    -v, --verbose       verbose output\n    --debug             debug output\n  (options with GNU= only)\n"
	.text
	.align 2
	.globl	_ZN8yOptLong11print_usageEv
	.type	_ZN8yOptLong11print_usageEv, @function
_ZN8yOptLong11print_usageEv:
.LFB1334:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$24, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -24(%rbp)
	movq	-24(%rbp), %rax
	movq	24(%rax), %rbx
	movl	$.LC32, %esi
	movl	$_ZSt4cout, %edi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	movq	%rbx, %rsi
	movq	%rax, %rdi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	movl	$.LC33, %esi
	movq	%rax, %rdi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	addq	$24, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1334:
	.size	_ZN8yOptLong11print_usageEv, .-_ZN8yOptLong11print_usageEv
	.align 2
	.globl	_ZN5yMainC2Ev
	.type	_ZN5yMainC2Ev, @function
_ZN5yMainC2Ev:
.LFB1336:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1336:
	.size	_ZN5yMainC2Ev, .-_ZN5yMainC2Ev
	.globl	_ZN5yMainC1Ev
	.set	_ZN5yMainC1Ev,_ZN5yMainC2Ev
	.align 2
	.globl	_ZN5yMainC2EP8yOptLong
	.type	_ZN5yMainC2EP8yOptLong, @function
_ZN5yMainC2EP8yOptLong:
.LFB1339:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-8(%rbp), %rax
	movq	-16(%rbp), %rdx
	movq	%rdx, (%rax)
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1339:
	.size	_ZN5yMainC2EP8yOptLong, .-_ZN5yMainC2EP8yOptLong
	.globl	_ZN5yMainC1EP8yOptLong
	.set	_ZN5yMainC1EP8yOptLong,_ZN5yMainC2EP8yOptLong
	.section	.rodata
.LC34:
	.string	"    gpio_read= "
.LC35:
	.string	"    gpio_set=  "
.LC36:
	.string	"    gpio_clr=  "
.LC37:
	.string	"    n_trans= "
	.align 8
.LC38:
	.string	"Error:  clock_gettime() failed"
.LC39:
	.string	"    delta_ns["
.LC40:
	.string	"]= "
.LC41:
	.string	"  "
.LC42:
	.string	" ns/xfer"
.LC43:
	.string	"caught something"
	.text
	.globl	main
	.type	main, @function
main:
.LFB1341:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	.cfi_lsda 0x3,.LLSDA1341
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%r15
	pushq	%r14
	pushq	%r13
	pushq	%r12
	pushq	%rbx
	subq	$248, %rsp
	.cfi_offset 15, -24
	.cfi_offset 14, -32
	.cfi_offset 13, -40
	.cfi_offset 12, -48
	.cfi_offset 3, -56
	movl	%edi, -276(%rbp)
	movq	%rsi, -288(%rbp)
	movq	-288(%rbp), %rdx
	movl	-276(%rbp), %ecx
	leaq	-128(%rbp), %rax
	movl	%ecx, %esi
	movq	%rax, %rdi
.LEHB5:
	call	_ZN8yOptLongC1EiPPc
	leaq	-128(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN8yOptLong13parse_optionsEv
	leaq	-128(%rbp), %rdx
	leaq	-256(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZN5yMainC1EP8yOptLong
	movzbl	-65(%rbp), %eax
	testb	%al, %al
	je	.L46
	leaq	-128(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN8yOptLong18print_option_flagsEv
	call	_ZN5Error3errEv
	testl	%eax, %eax
	je	.L47
	movl	$1, %eax
	jmp	.L48
.L47:
	movl	$0, %eax
.L48:
	movl	%eax, %ebx
	jmp	.L71
.L46:
	leaq	-160(%rbp), %rax
	movl	$10, %esi
	movq	%rax, %rdi
	call	_ZN8yFramDatC1Em
.LEHE5:
.LEHB6:
	call	_ZN5Error3errEv
	testl	%eax, %eax
	setne	%al
	testb	%al, %al
	je	.L50
	movl	$1, %ebx
	movl	$0, %r12d
	jmp	.L51
.L50:
	leaq	-240(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN8yRpiGpioC1Ev
	leaq	-240(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN8yRpiGpio13get_read_addrEv
	movq	%rax, -224(%rbp)
	leaq	-240(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN8yRpiGpio12get_set_addrEv
	movq	%rax, -216(%rbp)
	leaq	-240(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN8yRpiGpio12get_clr_addrEv
	movq	%rax, -208(%rbp)
	movzbl	-66(%rbp), %eax
	testb	%al, %al
	je	.L52
	movl	$.LC34, %esi
	movl	$_ZSt4cout, %edi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	movq	-224(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZNSolsEPKv
	movl	$_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_, %esi
	movq	%rax, %rdi
	call	_ZNSolsEPFRSoS_E
	movl	$.LC35, %esi
	movl	$_ZSt4cout, %edi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	movq	-216(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZNSolsEPKv
	movl	$_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_, %esi
	movq	%rax, %rdi
	call	_ZNSolsEPFRSoS_E
	movl	$.LC36, %esi
	movl	$_ZSt4cout, %edi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	movq	-208(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZNSolsEPKv
	movl	$_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_, %esi
	movq	%rax, %rdi
	call	_ZNSolsEPFRSoS_E
.L52:
	movl	-64(%rbp), %eax
	movl	%eax, %edx
	leaq	-160(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	_ZN8yFramDat6nlimitEj
	movl	%eax, -268(%rbp)
	movl	$.LC37, %esi
	movl	$_ZSt4cerr, %edi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	movl	-268(%rbp), %edx
	movl	%edx, %esi
	movq	%rax, %rdi
	call	_ZNSolsEi
	movl	$_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_, %esi
	movq	%rax, %rdi
	call	_ZNSolsEPFRSoS_E
	movl	$1, -272(%rbp)
	jmp	.L53
.L59:
	leaq	-160(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN8yFramDat5clearEv
	leaq	-192(%rbp), %rax
	movq	%rax, %rsi
	movl	$4, %edi
	call	clock_gettime
	movl	%eax, -264(%rbp)
	jmp	.L54
.L56:
	movq	-224(%rbp), %rax
	movl	(%rax), %eax
	movl	%eax, -260(%rbp)
	movq	-216(%rbp), %rax
	movl	$64, (%rax)
	movq	-216(%rbp), %rax
	movl	$64, (%rax)
	movq	-216(%rbp), %rax
	movl	$64, (%rax)
	movq	-216(%rbp), %rax
	movl	$64, (%rax)
	movq	-208(%rbp), %rax
	movl	$64, (%rax)
	movl	-260(%rbp), %eax
	andl	$134217728, %eax
	testl	%eax, %eax
	je	.L55
	jmp	.L54
.L55:
	movl	-260(%rbp), %eax
	shrl	$16, %eax
	movzwl	%ax, %eax
	movzbl	%al, %edx
	leaq	-160(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	_ZN8yFramDat8push_datEt
.L54:
	leaq	-160(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN8yFramDat10get_lengthEv
	cmpl	-268(%rbp), %eax
	setl	%al
	testb	%al, %al
	jne	.L56
	leaq	-176(%rbp), %rax
	movq	%rax, %rsi
	movl	$4, %edi
	call	clock_gettime
	movl	%eax, -264(%rbp)
	cmpl	$0, -264(%rbp)
	je	.L57
	movl	$.LC38, %esi
	movl	$_ZSt4cerr, %edi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	movl	$_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_, %esi
	movq	%rax, %rdi
	call	_ZNSolsEPFRSoS_E
.L57:
	movq	-176(%rbp), %rdx
	movq	-192(%rbp), %rax
	subq	%rax, %rdx
	movq	%rdx, %rax
	movq	%rax, -200(%rbp)
	movq	-168(%rbp), %rdx
	movq	-184(%rbp), %rax
	subq	%rax, %rdx
	movq	%rdx, %rax
	movq	%rax, -232(%rbp)
	cmpq	$0, -232(%rbp)
	jns	.L58
	addq	$1000000000, -232(%rbp)
	subq	$1, -200(%rbp)
.L58:
	movl	-268(%rbp), %eax
	movslq	%eax, %rcx
	movq	-232(%rbp), %rax
	cqto
	idivq	%rcx
	movq	%rax, %rbx
	movl	$4, %edi
	call	_ZSt4setwi
	movl	%eax, %r12d
	movl	$9, %edi
	call	_ZSt4setwi
	movl	%eax, %r13d
	movl	$2, %edi
	call	_ZSt4setwi
	movl	%eax, %r14d
	movl	$.LC39, %esi
	movl	$_ZSt4cerr, %edi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	movl	%r14d, %esi
	movq	%rax, %rdi
	call	_ZStlsIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_St5_Setw
	movl	-272(%rbp), %edx
	movl	%edx, %esi
	movq	%rax, %rdi
	call	_ZNSolsEi
	movl	$.LC40, %esi
	movq	%rax, %rdi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	movl	%r13d, %esi
	movq	%rax, %rdi
	call	_ZStlsIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_St5_Setw
	movq	-232(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZNSolsEl
	movl	$.LC41, %esi
	movq	%rax, %rdi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	movl	%r12d, %esi
	movq	%rax, %rdi
	call	_ZStlsIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_St5_Setw
	movq	%rbx, %rsi
	movq	%rax, %rdi
	call	_ZNSolsEl
	movl	$.LC42, %esi
	movq	%rax, %rdi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	movl	$_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_, %esi
	movq	%rax, %rdi
	call	_ZNSolsEPFRSoS_E
	addl	$1, -272(%rbp)
.L53:
	movl	-60(%rbp), %eax
	cmpl	-272(%rbp), %eax
	jge	.L59
	movzbl	-66(%rbp), %eax
	testb	%al, %al
	je	.L60
	leaq	-160(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN8yFramDat10show_debugEv
.L60:
	movzbl	-71(%rbp), %eax
	testb	%al, %al
	je	.L61
	leaq	-160(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN8yFramDat17print_coeff16_tabEv
	movl	$_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_, %esi
	movl	$_ZSt4cout, %edi
	call	_ZNSolsEPFRSoS_E
.L61:
	movzbl	-72(%rbp), %eax
	testb	%al, %al
	je	.L62
	leaq	-160(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN8yFramDat17print_coeff16_csvEv
	movl	$_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_, %esi
	movl	$_ZSt4cout, %edi
	call	_ZNSolsEPFRSoS_E
.L62:
	movzbl	-70(%rbp), %eax
	testb	%al, %al
	je	.L63
	leaq	-160(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN8yFramDat14print_hex_dumpEv
	movl	$_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_, %esi
	movl	$_ZSt4cout, %edi
	call	_ZNSolsEPFRSoS_E
.L63:
	movzbl	-69(%rbp), %eax
	testb	%al, %al
	je	.L64
	leaq	-160(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN8yFramDat16print_index_dataEv
	movl	$_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_, %esi
	movl	$_ZSt4cout, %edi
	call	_ZNSolsEPFRSoS_E
.L64:
	movzbl	-68(%rbp), %eax
	testb	%al, %al
	je	.L65
	leaq	-160(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN8yFramDat16print_delta_dataEv
	movl	$_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_, %esi
	movl	$_ZSt4cout, %edi
	call	_ZNSolsEPFRSoS_E
.LEHE6:
.L65:
	movl	$1, %r12d
	movl	%r15d, %ebx
.L51:
	leaq	-160(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN8yFramDatD1Ev
	cmpl	$1, %r12d
	je	.L80
	jmp	.L71
.L80:
	nop
.L67:
.LEHB7:
	call	_ZN5Error3errEv
.LEHE7:
	testl	%eax, %eax
	je	.L69
	movl	$1, %eax
	jmp	.L70
.L69:
	movl	$0, %eax
.L70:
	movl	%eax, %ebx
.L71:
	movl	%ebx, %eax
	jmp	.L79
.L75:
	movq	%rax, %rbx
	leaq	-160(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN8yFramDatD1Ev
	movq	%rbx, %rax
	jmp	.L73
.L77:
	movq	%rax, %rbx
	call	__cxa_end_catch
	movq	%rbx, %rax
	movq	%rax, %rdi
.LEHB8:
	call	_Unwind_Resume
.LEHE8:
.L76:
.L73:
	movq	%rax, %rdi
	call	__cxa_begin_catch
	movl	$.LC43, %esi
	movl	$_ZSt4cerr, %edi
.LEHB9:
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	movl	$_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_, %esi
	movq	%rax, %rdi
	call	_ZNSolsEPFRSoS_E
.LEHE9:
.LEHB10:
	call	__cxa_end_catch
.LEHE10:
	jmp	.L67
.L79:
	addq	$248, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1341:
	.section	.gcc_except_table
	.align 4
.LLSDA1341:
	.byte	0xff
	.byte	0x3
	.uleb128 .LLSDATT1341-.LLSDATTD1341
.LLSDATTD1341:
	.byte	0x1
	.uleb128 .LLSDACSE1341-.LLSDACSB1341
.LLSDACSB1341:
	.uleb128 .LEHB5-.LFB1341
	.uleb128 .LEHE5-.LEHB5
	.uleb128 .L76-.LFB1341
	.uleb128 0x1
	.uleb128 .LEHB6-.LFB1341
	.uleb128 .LEHE6-.LEHB6
	.uleb128 .L75-.LFB1341
	.uleb128 0x3
	.uleb128 .LEHB7-.LFB1341
	.uleb128 .LEHE7-.LEHB7
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB8-.LFB1341
	.uleb128 .LEHE8-.LEHB8
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB9-.LFB1341
	.uleb128 .LEHE9-.LEHB9
	.uleb128 .L77-.LFB1341
	.uleb128 0
	.uleb128 .LEHB10-.LFB1341
	.uleb128 .LEHE10-.LEHB10
	.uleb128 0
	.uleb128 0
.LLSDACSE1341:
	.byte	0x1
	.byte	0
	.byte	0
	.byte	0x7d
	.align 4
	.long	0

.LLSDATT1341:
	.text
	.size	main, .-main
	.section	.text._ZN9__gnu_cxx6__stoaIlicIiEEET0_PFT_PKT1_PPS3_DpT2_EPKcS5_PmS9_,"axG",@progbits,_ZN9__gnu_cxx6__stoaIlicIiEEET0_PFT_PKT1_PPS3_DpT2_EPKcS5_PmS9_,comdat
	.weak	_ZN9__gnu_cxx6__stoaIlicIiEEET0_PFT_PKT1_PPS3_DpT2_EPKcS5_PmS9_
	.type	_ZN9__gnu_cxx6__stoaIlicIiEEET0_PFT_PKT1_PPS3_DpT2_EPKcS5_PmS9_, @function
_ZN9__gnu_cxx6__stoaIlicIiEEET0_PFT_PKT1_PPS3_DpT2_EPKcS5_PmS9_:
.LFB1343:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$80, %rsp
	movq	%rdi, -40(%rbp)
	movq	%rsi, -48(%rbp)
	movq	%rdx, -56(%rbp)
	movq	%rcx, -64(%rbp)
	movl	%r8d, -68(%rbp)
	call	__errno_location
	movl	$0, (%rax)
	movl	-68(%rbp), %edx
	leaq	-16(%rbp), %rsi
	movq	-56(%rbp), %rcx
	movq	-40(%rbp), %rax
	movq	%rcx, %rdi
	call	*%rax
	movq	%rax, -8(%rbp)
	movq	-16(%rbp), %rax
	cmpq	-56(%rbp), %rax
	jne	.L82
	movq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	_ZSt24__throw_invalid_argumentPKc
.L82:
	call	__errno_location
	movl	(%rax), %eax
	cmpl	$34, %eax
	je	.L83
	cmpq	$-2147483648, -8(%rbp)
	jl	.L83
	cmpq	$2147483647, -8(%rbp)
	jle	.L84
.L83:
	movq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	_ZSt20__throw_out_of_rangePKc
.L84:
	movq	-8(%rbp), %rax
	movl	%eax, -20(%rbp)
	cmpq	$0, -64(%rbp)
	je	.L85
	movq	-16(%rbp), %rax
	movq	%rax, %rdx
	movq	-56(%rbp), %rax
	subq	%rax, %rdx
	movq	%rdx, %rax
	movq	%rax, %rdx
	movq	-64(%rbp), %rax
	movq	%rdx, (%rax)
.L85:
	movl	-20(%rbp), %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1343:
	.size	_ZN9__gnu_cxx6__stoaIlicIiEEET0_PFT_PKT1_PPS3_DpT2_EPKcS5_PmS9_, .-_ZN9__gnu_cxx6__stoaIlicIiEEET0_PFT_PKT1_PPS3_DpT2_EPKcS5_PmS9_
	.weak	_ZN9__gnu_cxx6__stoaIlicJiEEET0_PFT_PKT1_PPS3_DpT2_EPKcS5_PmS9_
	.set	_ZN9__gnu_cxx6__stoaIlicJiEEET0_PFT_PKT1_PPS3_DpT2_EPKcS5_PmS9_,_ZN9__gnu_cxx6__stoaIlicIiEEET0_PFT_PKT1_PPS3_DpT2_EPKcS5_PmS9_
	.text
	.type	_Z41__static_initialization_and_destruction_0ii, @function
_Z41__static_initialization_and_destruction_0ii:
.LFB1500:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	%edi, -4(%rbp)
	movl	%esi, -8(%rbp)
	cmpl	$1, -4(%rbp)
	jne	.L87
	cmpl	$65535, -8(%rbp)
	jne	.L87
	movl	$_ZStL8__ioinit, %edi
	call	_ZNSt8ios_base4InitC1Ev
	movl	$__dso_handle, %edx
	movl	$_ZStL8__ioinit, %esi
	movl	$_ZNSt8ios_base4InitD1Ev, %edi
	call	__cxa_atexit
.L87:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1500:
	.size	_Z41__static_initialization_and_destruction_0ii, .-_Z41__static_initialization_and_destruction_0ii
	.type	_GLOBAL__sub_I__ZN8yOptLongC2EiPPc, @function
_GLOBAL__sub_I__ZN8yOptLongC2EiPPc:
.LFB1501:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	$65535, %esi
	movl	$1, %edi
	call	_Z41__static_initialization_and_destruction_0ii
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1501:
	.size	_GLOBAL__sub_I__ZN8yOptLongC2EiPPc, .-_GLOBAL__sub_I__ZN8yOptLongC2EiPPc
	.section	.init_array,"aw"
	.align 8
	.quad	_GLOBAL__sub_I__ZN8yOptLongC2EiPPc
	.section	.rodata
	.align 8
	.type	_ZZL18__gthread_active_pvE20__gthread_active_ptr, @object
	.size	_ZZL18__gthread_active_pvE20__gthread_active_ptr, 8
_ZZL18__gthread_active_pvE20__gthread_active_ptr:
	.quad	_ZL28__gthrw___pthread_key_createPjPFvPvE
	.weakref	_ZL28__gthrw___pthread_key_createPjPFvPvE,__pthread_key_create
	.hidden	__dso_handle
	.ident	"GCC: (Ubuntu 4.8.4-2ubuntu1~14.04.3) 4.8.4"
	.section	.note.GNU-stack,"",@progbits
