/* atan2f4 -
   Copyright (C) 2006, 2007 Sony Computer Entertainment Inc.
   All rights reserved.

   Redistribution and use in source and binary forms,
   with or without modification, are permitted provided that the
   following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the Sony Computer Entertainment Inc nor the names
      of its contributors may be used to endorse or promote products derived
      from this software without specific prior written permission.

   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
   ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
   LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
   INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
   CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
   ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
   POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef ___SIMD_MATH_ATAN2F4_H___
#define ___SIMD_MATH_ATAN2F4_H___

#include <simdmath.h>
#include <altivec.h>

#include <simdmath/_atanf4.h>

//
// Inverse tangent function of two variables
//
static inline vector float
_atan2f4 (vector float y, vector float x)
{
  vector float res = _atanf4(divf4(y,x));

  // Use the arguments to determine the quadrant of the result:
  // if (x < 0)
  //   if (y < 0)
  //      res = -PI + res
  //   else
  //      res = PI + res
  //
  vector unsigned int yNeg = (vector unsigned int)vec_cmpgt(__vec_splatsf4(0.0f), y);
  vector unsigned int xNeg = (vector unsigned int)vec_cmpgt(__vec_splatsf4(0.0f) ,x);

  vector float bias =
    vec_sel(__vec_splatsf4(3.14159265358979323846f),
          __vec_splatsf4(-3.14159265358979323846f), yNeg);

  vector float newRes = vec_add(bias, res);

  res = vec_sel(res,newRes,xNeg);

  return res;
}

#endif
