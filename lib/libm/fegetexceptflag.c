/* This file has been put into the public domain by its author.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
   IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
   OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
   ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
   OTHER DEALINGS IN THE SOFTWARE.
*/

/* fegetexceptflag - get floating-point status flags

   AUTHOR: Gregory Pietsch

   DESCRIPTION:

   The functionality described on this reference page is aligned with the 
   ISO C standard. Any conflict between the requirements described here and 
   the ISO C standard is unintentional. This volume of POSIX.1-2008 defers 
   to the ISO C standard.

   The fegetexceptflag() function shall attempt to store an implementation-
   defined representation of the states of the floating-point status flags 
   indicated by the argument excepts in the object pointed to by the argument 
   flagp.

   RETURN VALUE:

   If the representation was successfully stored, fegetexceptflag() shall 
   return zero. Otherwise, it shall return a non-zero value.

   ERRORS:

   No errors are defined.
*/

#include <fenv.h>

int (fegetexceptflag) (fexcept_t * flagp, int excepts)
{
  if (flagp)
    {
      *flagp = fetestexcept (excepts);
      return 0;
    }
  else
    return 1;
}

/* END OF FILE */
