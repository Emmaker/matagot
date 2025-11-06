/* This file has been put into the public domain by its author.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
   IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
   OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
   ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
   OTHER DEALINGS IN THE SOFTWARE.
*/

/* fesetexceptflag - set floating-point status flags

   AUTHOR: Gregory Pietsch

   DESCRIPTION:

   The functionality described on this reference page is aligned with the 
   ISO C standard. Any conflict between the requirements described here and 
   the ISO C standard is unintentional. This volume of POSIX.1-2008 defers 
   to the ISO C standard.

   The fesetexceptflag() function shall attempt to set the floating-point 
   status flags indicated by the argument excepts to the states stored in the 
   object pointed to by flagp. The value pointed to by flagp shall have been 
   set by a previous call to fegetexceptflag() whose second argument 
   represented at least those floating-point exceptions represented by the 
   argument excepts. This function does not raise floating-point exceptions, 
   but only sets the state of the flags.

   RETURN VALUE:

   If the excepts argument is zero or if all the specified exceptions were 
   successfully set, fesetexceptflag() shall return zero. Otherwise, it shall 
   return a non-zero value.

   ERRORS:

   No errors are defined.
*/

#include <fenv.h>

int (fesetexceptflag) (const fexcept_t * flagp, int excepts)
{
  if (flagp)
    {
      feclearexcept (~*flagp & excepts);
      feraiseexcept (*flagp & excepts);
      return 0;
    }
  else
    return 1;
}

/* END OF FILE */
