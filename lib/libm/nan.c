/* This file has been put into the public domain by its author.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
   IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
   OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
   ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
   OTHER DEALINGS IN THE SOFTWARE.
*/

/* nan, nanf, nanl - return quiet NaN

   AUTHOR: Gregory Pietsch

   DESCRIPTION:

   The functionality described on this reference page is aligned with the 
   ISO C standard. Any conflict between the requirements described here and 
   the ISO C standard is unintentional. This volume of POSIX.1-2008 defers 
   to the ISO C standard. 

   The function call nan("n-char-sequence") shall be equivalent to:

   strtod("NAN(n-char-sequence)", (char **) NULL);

   The function call nan("") shall be equivalent to:

   strtod("NAN()", (char **) NULL)

   If tagp does not point to an n-char-sequence or an empty string, the 
   function call shall be equivalent to:

   strtod("NAN", (char **) NULL)

   Function calls to nanf() and nanl() are equivalent to the corresponding 
   function calls to strtof() and strtold().

   RETURN VALUE:

   These functions shall return a quiet NaN, if available, with content 
   indicated through tagp.

   If the implementation does not support quiet NaNs, these functions shall 
   return zero.

   ERRORS:

   No errors are defined.

   ALGORITHM:
   
   The argument is currently ignored. The values returned are constants.
*/

#include "xmath.h"

double (nan) (const char *tagp)
{
  return _Dbl->_Nan._D;
}

float (nanf) (const char *tagp)
{
  return _Flt->_Nan._F;
}

long double (nanl) (const char *tagp)
{
  return _Ldbl->_Nan._L;
}

/* END OF FILE */
