/* This file has been put into the public domain by its author.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
   IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
   OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
   ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
   OTHER DEALINGS IN THE SOFTWARE.
*/

/* float.c - constants for float.h

   AUTHOR: Gregory Pietsch

*/

#include "xmath.h"

/* define __BYTE_ORDER */
#ifndef __BYTE_ORDER
#define __LITTLE_ENDIAN	(0)
#define __BIG_ENDIAN	(1)
#define __PDP_ENDIAN	(2)
#define __MIDDLE_ENDIAN	(3)
#define __BYTE_ORDER	__LITTLE_ENDIAN	/* change if not a PC... */
#endif
#if __BYTE_ORDER == __LITTLE_ENDIAN
#define _F4(_0,_1,_2,_3)\
	_3,_2,_1,_0
#define _F8(_0,_1,_2,_3,_4,_5,_6,_7)\
	_7,_6,_5,_4,_3,_2,_1,_0
#define _F10(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9)\
	_9,_8,_7,_6,_5,_4,_3,_2,_1,_0
#define _F16(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_A,_B,_C,_D,_E,_F)\
	_F,_E,_D,_C,_B,_A,_9,_8,_7,_6,_5,_4,_3,_2,_1,_0
#elif __BYTE_ORDER == __BIG_ENDIAN
#define _F4(_0,_1,_2,_3)\
	_0,_1,_2,_3
#define _F8(_0,_1,_2,_3,_4,_5,_6,_7)\
	_0,_1,_2,_3,_4,_5,_6,_7
#define _F10(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9)\
	_0,_1,_2,_3,_4,_5,_6,_7,_8,_9
#define _F16(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_A,_B,_C,_D,_E,_F)\
	_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_A,_B,_C,_D,_E,_F
#elif __BYTE_ORDER == __PDP_ENDIAN
#define _F4(_0,_1,_2,_3)\
	_2,_3,_0,_1
#define _F8(_0,_1,_2,_3,_4,_5,_6,_7)\
	_6,_7,_4,_5,_2,_3,_0,_1
#define _F10(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9)\
	_8,_9,_6,_7,_4,_5,_2,_3,_0,_1
#define _F16(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_A,_B,_C,_D,_E,_F)\
	_E,_F,_C,_D,_A,_B,_8,_9,_6,_7,_4,_5,_2,_3,_0,_1
#elif __BYTE_ORDER == __MIDDLE_ENDIAN
#define _F4(_0,_1,_2,_3)\
	_1,_0,_3,_2
#define _F8(_0,_1,_2,_3,_4,_5,_6,_7)\
	_1,_0,_3,_2,_5,_4,_7,_6
#define _F10(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9)\
	_1,_0,_3,_2,_5,_4,_7,_6,_9,_8
#define _F16(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_A,_B,_C,_D,_E,_F)\
	_1,_0,_3,_2,_5,_4,_7,_6,_9,_8,_B,_A,_D,_C,_F,_E
#endif

_FP_METRIC_T _FP4 = {
	4,	/* _Size */
	8,	/* _Ebits */
	0,	/* _Explicit1bit */
	24,	/* _Mant_dig */
	6,	/* _Dig */
	-126,	/* _Min_exp */
	127,	/* _Max_exp */
	-38,	/* _Min_10_exp */
	38,	/* _Max_10_exp */
	/* _Max */
	{ _F4( '\x7F', '\x7F', '\xFF', '\xFF') },
	/* _Epsilon */
	{ _F4( '\x34', '\x00', '\x00', '\x00') },
	/* _Min */
	{ _F4( '\x00', '\x80', '\x00', '\x00') },
	/* _Inf */
	{ _F4( '\x7F', '\x80', '\x00', '\x00') },
	/* _NaN */
	{ _F4( '\x7F', '\xC0', '\x00', '\x00') }
};

_FP_METRIC_T _FP8 = {
	8,	/* _Size */
	11,	/* _Ebits */
	0,	/* _Explicit1bit */
	53,	/* _Mant_dig */
	15,	/* _Dig */
	-1022,	/* _Min_exp */
	1023,	/* _Max_exp */
	-307,	/* _Min_10_exp */
	307,	/* _Max_10_exp */
	/* _Max */
	{ _F8( '\x7F', '\xEF', '\xFF', '\xFF', '\xFF', '\xFF', '\xFF', '\xFF') },
	/* _Epsilon */
	{ _F8( '\x3C', '\xB0', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00') },
	/* _Min */
	{ _F8( '\x00', '\x10', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00') },
	/* _Inf */
	{ _F8( '\x7F', '\xF0', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00') },
	/* _NaN */
	{ _F8( '\x7F', '\xF8', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00') }
};

_FP_METRIC_T _FP10 = {
	10,	/* _Size */
	15,	/* _Ebits */
	1,	/* _Explicit1bit */
	64,	/* _Mant_dig */
	18,	/* _Dig */
	-16382,	/* _Min_exp */
	16383,	/* _Max_exp */
	-4931,	/* _Min_10_exp */
	4931,	/* _Max_10_exp */
	/* _Max */
	{ _F10( '\x7F', '\xFE', '\xFF', '\xFF', '\xFF', '\xFF', '\xFF', '\xFF',
	'\xFF', '\xFF') },
	/* _Epsilon */
	{ _F10( '\x3F', '\xC0', '\x80', '\x00', '\x00', '\x00', '\x00', '\x00',
	'\x00', '\x00') },
	/* _Min */
	{ _F10( '\x00', '\x01', '\x80', '\x00', '\x00', '\x00', '\x00', '\x00',
	'\x00', '\x00') },
	/* _Inf */
	{ _F10( '\x7F', '\xFF', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00',
	'\x00', '\x00') },
	/* _NaN */
	{ _F10( '\x7F', '\xFF', '\x40', '\x00', '\x00', '\x00', '\x00', '\x00',
	'\x00', '\x00') }
};

_FP_METRIC_T _FP16 = {
	16,	/* _Size */
	15,	/* _Ebits */
	0,	/* _Explicit1bit */
	113,	/* _Mant_dig */
	33,	/* _Dig */
	-16382,	/* _Min_exp */
	16383,	/* _Max_exp */
	-4931,	/* _Min_10_exp */
	4931,	/* _Max_10_exp */
	/* _Max */
	{ _F16( '\x7F', '\xFE', '\xFF', '\xFF', '\xFF', '\xFF', '\xFF', '\xFF',
	'\xFF', '\xFF', '\xFF', '\xFF', '\xFF', '\xFF', '\xFF', '\xFF') },
	/* _Epsilon */
	{ _F16( '\x3F', '\x8F', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00',
	'\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00') },
	/* _Min */
	{ _F16( '\x00', '\x01', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00',
	'\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00') },
	/* _Inf */
	{ _F16( '\x7F', '\xFF', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00',
	'\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00') },
	/* _NaN */
	{ _F16( '\x7F', '\xFF', '\x80', '\x00', '\x00', '\x00', '\x00', '\x00',
	'\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00') }
};

/*
 * TODO:
 *
 * Originally these values were dependant on defines,
 * but neither those defines or their values are part
 * of any standard so frankly I don't know what to
 * test for. This works for x86_64 though, so it works
 * for now until the library is ready to be cross
 * platform.
 */

//#if _FLT_SIZE == 4
const _FP_METRIC_T * const _Flt = (&_FP4);
//#elif _FLT_SIZE == 8
//const _FP_METRIC_T * const _Flt = (&_FP8);
//#elif _FLT_SIZE == 10
//const _FP_METRIC_T * const _Flt = (&_FP10);
//#elif _FLT_SIZE == 16
//const _FP_METRIC_T * const _Flt = (&_FP16);
//#endif

//#if _DBL_SIZE == 8
const _FP_METRIC_T * const _Dbl = (&_FP8);
//#elif _DBL_SIZE == 10
//const _FP_METRIC_T * const _Dbl = (&_FP10);
//#elif _DBL_SIZE == 16
//const _FP_METRIC_T * const _Dbl = (&_FP16);
//#endif

//#if _LDBL_SIZE == 8
//const _FP_METRIC_T * const _Ldbl = (&_FP8);
//#elif _LDBL_SIZE == 10
const _FP_METRIC_T * const _Ldbl = (&_FP10);
//#elif _LDBL_SIZE == 16
//const _FP_METRIC_T * const _Ldbl = (&_FP16);
//#endif

/* END OF FILE */
