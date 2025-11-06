/* This file has been put into the public domain by its author.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
   IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
   OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
   ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
   OTHER DEALINGS IN THE SOFTWARE.
*/

/* yvals.h - user-defined values */

#ifndef _YVALS_H
#define _YVALS_H

#ifndef __BYTE_ORDER
#define __LITTLE_ENDIAN 	(0)	/* XINU - IBM PCs */
#define __BIG_ENDIAN    	(1)	/* UNIX */
#define __PDP_ENDIAN    	(2)	/* IXUN */
#define __MIDDLE_ENDIAN  	(3)	/* NUXI */
#define __BYTE_ORDER		__LITTLE_ENDIAN
#endif

#if __BYTE_ORDER == __LITTLE_ENDIAN
#define _BYTE(_S,_X)	((_S)-(_X)-1)
#elif __BYTE_ORDER == __BIG_ENDIAN
#define _BYTE(_S,_X)	(_X)
#elif __BYTE_ORDER == __PDP_ENDIAN
#define _BYTE(_S,_X)	(((_S)-(_X)-1)^1)
#elif __BYTE_ORDER == __MIDDLE_ENDIAN
#define _BYTE(_S,_X)	((_X)^1)
#endif

/* The rounding mode for floating-point addition is characterized by the
   implementation-defined value of FLT_ROUNDS:

   -1	Indeterminable.
   0	Toward zero.
   1	To nearest.
   2	Toward positive infinity.
   3	Toward negative infinity.

   All other values for FLT_ROUNDS characterize implementation-defined
   rounding behavior.

   The values of operations with floating operands and values subject to the
   usual arithmetic conversions and of floating constants are evaluated to a
   format whose range and precision may be greater than required by the type.
   The use of evaluation formats is characterized by the implementation-defined
   value of FLT_EVAL_METHOD:

   -1	Indeterminable.
   0    Evaluate all operations and constants just to the range and precision
        of the type.
   1	Evaluate operations and constants of type float and double to the range
        and precision of the double type; evaluate long double operations and
        constants to the range and precision of the long double type.
   2	Evaluate all operations and constants to the range and precision of the
        long double type.

   All other negative values for FLT_EVAL_METHOD characterize implementation-
   defined behavior.
*/

#define _FLTROUNDS	1
#define _FLTEVALMETHOD	0

#endif	/* _YVALS_H */
