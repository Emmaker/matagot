/* This file has been put into the public domain by its author.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
   IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
   OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
   ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
   OTHER DEALINGS IN THE SOFTWARE.
*/

/* fesetenv - set current floating-point environment

   AUTHOR: Gregory Pietsch

   DESCRIPTION:

   The functionality described on this reference page is aligned with the 
   ISO C standard. Any conflict between the requirements described here and 
   the ISO C standard is unintentional. This volume of POSIX.1-2008 defers 
   to the ISO C standard. 

   The fesetenv() function shall attempt to establish the floating-point 
   environment represented by the object pointed to by envp. The argument 
   envp shall point to an object set by a call to fegetenv() or 
   feholdexcept(), or equal a floating-point environment macro. The 
   fesetenv() function does not raise floating-point exceptions, but only 
   installs the state of the floating-point status flags represented through 
   its argument.

   RETURN VALUE:

   If the environment was successfully established, fesetenv() shall return 
   zero. Otherwise, it shall return a non-zero value.

   ERRORS:

   No errors are defined.
*/

#include <fenv.h>

int (fesetenv) (const fenv_t * envp)
{
  if (envp)
    {
      _FEcurrent._FErounding = envp->_FErounding;
      _FEcurrent._FEexcepts = envp->_FEexcepts;
      return 0;
    }
  else
    return 1;
}

/* END OF FILE */
