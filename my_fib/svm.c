/*
 * Permission is hereby granted, free of charge, to any person or
 * organization obtaining a copy of the software and accompanying
 * documentation covered by this license (the "Software") to use,
 * reproduce, display, distribute, execute, and transmit the Software,
 * and to prepare derivative works of the Software, and to permit
 * third-parties to whom the Software is furnished to do so, all subject
 * to the following:
 *
 * The copyright notices in the Software and this entire statement,
 * including the above license grant, this restriction and the following
 * disclaimer, must be included in all copies of the Software, in whole
 * or in part, and all derivative works of the Software, unless such
 * copies or derivative works are solely in the form of
 * machine-executable object code generated by a source language
 * processor.
 *
 * THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, TITLE AND
 * NON-INFRINGEMENT. IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR ANYONE
 * DISTRIBUTING THE SOFTWARE BE LIABLE FOR ANY DAMAGES OR OTHER
 * LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT
 * OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include <stdio.h>
#include <stdint.h>

#include "svm.h"
#include "interp.h"
#include "threaded_code.h"

CMD_IMPLEMENTATION(svm_add_uint) {
	unsigned b = (unsigned) *dsp--;
	unsigned a = (unsigned) *dsp;
	*dsp = (uintptr_t) (a + b);
} CMD_END

CMD_IMPLEMENTATION(svm_subtract_uint) {
	unsigned b = (unsigned) *dsp--;
	unsigned a = (unsigned) *dsp;
	*dsp = (uintptr_t) (a - b);
} CMD_END

CMD_IMPLEMENTATION(svm_println_uint) {
	unsigned value = (unsigned) *dsp--;
	printf("%u\n", value);
} CMD_END

CMD_IMPLEMENTATION(uni_println_charS) {
	const char* str = (const char*) *ip++;
	printf("%s\n", str);
} CMD_END

CMD_IMPLEMENTATION(svm_push) {
	uintptr_t value = *ip++;
	* ++dsp = value;
} CMD_END

CMD_IMPLEMENTATION(svm_push0) {
	* ++dsp = 0;
} CMD_END

CMD_IMPLEMENTATION(svm_drop) {
	--dsp;
} CMD_END

CMD_IMPLEMENTATION(svm_dup) {
	uintptr_t value = (uintptr_t) *dsp;
	* ++dsp = (uintptr_t)value;
} CMD_END

CMD_IMPLEMENTATION(svm_swap) {
	uintptr_t top = dsp[0];
	dsp[0] = dsp[-1];
	dsp[-1] = top;
} CMD_END

CMD_IMPLEMENTATION(svm_dec) {
	--dsp[0];
} CMD_END

CMD_IMPLEMENTATION(svm_eq) {
	uintptr_t b = *dsp--;
	uintptr_t a = *dsp;
	*dsp = (a == b);
} CMD_END

CMD_IMPLEMENTATION(svm_neq) {
	uintptr_t b = *dsp--;
	uintptr_t a = *dsp;
	*dsp = (a != b);
} CMD_END

CMD_IMPLEMENTATION(svm_nop) {
} CMD_END

#if IP_DSP_REGISTERS
void svm_call(uintptr_t* ip, uintptr_t* _dsp) { {
#else
CMD_IMPLEMENTATION(svm_call) {
#endif
	uintptr_t* jump_to = (uintptr_t*) *ip++;
#if DIRECT_THREADED_CODE
	uintptr_t* old_ip = ip;
	ip = jump_to;
	command_t func = (command_t) *ip++;
#if IP_DSP_REGISTERS
	func(ip, _dsp);
#else
	func();
#endif
	ip = old_ip;
#else
	* ++rsp = (uintptr_t) ip;
	ip = jump_to;
#endif
} CMD_END

CMD_IMPLEMENTATION(svm_jump) {
	uintptr_t* jump_to = (uintptr_t*) *ip++;
	ip = jump_to;
} CMD_END

CMD_IMPLEMENTATION(svm_jump_if_zero) {
	uintptr_t condition = *dsp--;
	uintptr_t jump_to = *ip++;
	if (!condition) {
		ip = (uintptr_t*) jump_to;
	}
} CMD_END

CMD_IMPLEMENTATION(svm_jump_and_drop_if_zero) {
	uintptr_t condition = *dsp;
	uintptr_t jump_to = *ip++;
	if (!condition) {
		--dsp; // remove known value from stack
		ip = (uintptr_t*) jump_to;
	}
} CMD_END

CMD_IMPLEMENTATION(svm_dup_jump_if_zero) {
	uintptr_t condition = *dsp;
	uintptr_t jump_to = *ip++;
	if (!condition) {
		ip = (uintptr_t*) jump_to;
	}
} CMD_END

CMD_IMPLEMENTATION(svm_jump_and_drop_if_eq_const) {
	uintptr_t top = *dsp;
	uintptr_t constant = *ip++;
	uintptr_t jump_to = *ip++;
	if (top == constant) {
		--dsp; // remove known value from stack
		ip = (uintptr_t*) jump_to;
	}
} CMD_END

CMD_IMPLEMENTATION(svm_dup_jump_if_eq_const) {
	uintptr_t top = *dsp;
	uintptr_t constant = *ip++;
	uintptr_t jump_to = *ip++;
	if (top == constant) {
		ip = (uintptr_t*) jump_to;
	}
} CMD_END

CMD_IMPLEMENTATION(svm_dup_jump_if_le_const) {
	uintptr_t top = *dsp;
	uintptr_t constant = *ip++;
	uintptr_t jump_to = *ip++;
	if (top <= constant) {
		ip = (uintptr_t*) jump_to;
	}
} CMD_END

CMD_IMPLEMENTATION(svm_jump_if_notzero) {
	uintptr_t condition = *dsp--;
	uintptr_t* jump_to = (uintptr_t*) *ip++;
	if (condition) {
		ip = jump_to;
	}
} CMD_END

#if IP_DSP_REGISTERS
void svm_push_ret(uintptr_t* ip, uintptr_t* _dsp) {
	uintptr_t value = (uintptr_t) *ip++;
	* ++_dsp = (uintptr_t)value;
	dsp = _dsp; // set global variable from register
}
#elif DIRECT_THREADED_CODE
void svm_push_ret(void) {
	uintptr_t value = (uintptr_t) *ip++;
	* ++dsp = (uintptr_t)value;
}
#else
CMD_IMPLEMENTATION(svm_push_ret) {
	uintptr_t value = (uintptr_t) *ip++;
	* ++dsp = (uintptr_t)value;
	ip = (uintptr_t*) *rsp--;
} CMD_END
#endif

#if IP_DSP_REGISTERS
void svm_exit(uintptr_t* ip, uintptr_t* _dsp) {
	dsp = _dsp; // set global variable from register
}

void svm_ret(uintptr_t* ip, uintptr_t* _dsp) {
	dsp = _dsp; // set global variable from register
}
#elif DIRECT_THREADED_CODE
void svm_exit(void) {
}
void svm_ret(void) {
}
#else
CMD_IMPLEMENTATION(svm_exit) {
	ip = NULL;
} CMD_END

CMD_IMPLEMENTATION(svm_ret) {
	ip = (uintptr_t*) *rsp--;
} CMD_END
#endif

CMD_IMPLEMENTATION(svm_drop_push) {
	uintptr_t value = *ip++;
	*dsp = (uintptr_t)value;
} CMD_END

CMD_IMPLEMENTATION(svm_drop_push0) {
	*dsp = 0;
} CMD_END
