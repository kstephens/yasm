/* $IdPath$
 * Integer number functions header file.
 *
 *  Copyright (C) 2001  Peter Johnson
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND OTHER CONTRIBUTORS ``AS IS''
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR OTHER CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef YASM_INTNUM_H
#define YASM_INTNUM_H

void yasm_intnum_initialize(void);
/* Clean up internal allocations */
void yasm_intnum_cleanup(void);

/*@only@*/ yasm_intnum *yasm_intnum_new_dec(char *str, unsigned long lindex);
/*@only@*/ yasm_intnum *yasm_intnum_new_bin(char *str, unsigned long lindex);
/*@only@*/ yasm_intnum *yasm_intnum_new_oct(char *str, unsigned long lindex);
/*@only@*/ yasm_intnum *yasm_intnum_new_hex(char *str, unsigned long lindex);
/* convert character constant to integer value, using NASM rules */
/*@only@*/ yasm_intnum *yasm_intnum_new_charconst_nasm(const char *str,
						       unsigned long lindex);
/*@only@*/ yasm_intnum *yasm_intnum_new_uint(unsigned long i);
/*@only@*/ yasm_intnum *yasm_intnum_new_int(long i);
/*@only@*/ yasm_intnum *yasm_intnum_copy(const yasm_intnum *intn);
void yasm_intnum_delete(/*@only@*/ yasm_intnum *intn);

/* calculation function: acc = acc op operand */
void yasm_intnum_calc(yasm_intnum *acc, yasm_expr_op op, yasm_intnum *operand);

/* simple value checks (for catching identities and the like) */
int yasm_intnum_is_zero(yasm_intnum *acc);
int yasm_intnum_is_pos1(yasm_intnum *acc);
int yasm_intnum_is_neg1(yasm_intnum *acc);

/* The get functions truncate intn to the size specified; they don't check
 * for overflow.  Use intnum_check_size() to check for overflow.
 */

/* Return a 32-bit value in "standard" C format (eg, of unknown endian).
 * intnum_get_uint() treats intn as an unsigned integer (and returns as such).
 * intnum_get_int() treats intn as a signed integer (and returns as such).
 */
unsigned long yasm_intnum_get_uint(const yasm_intnum *intn);
long yasm_intnum_get_int(const yasm_intnum *intn);

/* ptr will point to the Intel-format little-endian byte string after
 * call (eg, [0] should be the first byte output to the file).
 */
void yasm_intnum_get_sized(const yasm_intnum *intn, unsigned char *ptr,
			   size_t size);

/* Check to see if intn will fit without overflow in size bytes.
 * If is_signed is 1, intn is treated as a signed number.
 * Returns 1 if it will, 0 if not.
 */
int yasm_intnum_check_size(const yasm_intnum *intn, size_t size,
			   int is_signed);

void yasm_intnum_print(FILE *f, const yasm_intnum *intn);

#endif