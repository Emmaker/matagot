/* This file has been put into the public domain by its author.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
   IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
   OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
   ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
   OTHER DEALINGS IN THE SOFTWARE.
*/

/* signbit.c - test sign

   AUTHOR: Gregory Pietsch

   DESCRIPTION:

   The functionality described on this reference page is aligned with the 
   ISO C standard. Any conflict between the requirements described here and 
   the ISO C standard is unintentional. This volume of POSIX.1-2008 defers 
   to the ISO C standard.

   The signbit() macro shall determine whether the sign of its argument 
   value is negative. NaNs, zeros, and infinities have a sign bit.

   RETURN VALUE:

   The signbit() macro shall return a non-zero value if and only if the sign 
   of its argument value is negative.

   ERRORS:

   No errors are defined.
*/

#include "xmath.h"

int
_Signbit (double d)
{
  return _Getsign ((unsigned char *) &d, _Dbl);
}

int
_Signbitf (float f)
{
  return _Getsign ((unsigned char *) &f, _Flt);
}

int
_Signbitl (long double l)
{
  return _Getsign ((unsigned char *) &l, _Ldbl);
}

/* END OF FILE */
