/*
 * Copyright (c) 2012 Joseph Gaeddert
 * Copyright (c) 2012 Virginia Polytechnic Institute & State University
 *
 * This file is part of liquid.
 *
 * liquid is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * liquid is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with liquid.  If not, see <http://www.gnu.org/licenses/>.
 */

//
// Fixed-point math API: 16-bit q16 type
//

#include "liquidfpm.internal.h"

#define Q(name)     LIQUIDFPM_CONCAT(q16,name)
#define CQ(name)    LIQUIDFPM_CONCAT(cq16,name)

// source files
#include "qtype_div.port.c"
#include "qtype_inv_newton.c"
#include "qtype_mul.port.c"
#include "qtype_log2_frac.c"
#include "qtype_log2_shiftadd.c"
#include "qtype_atan_cordic.c"
#include "qtype_sincos_cordic.c"
#include "qtype_sincos_tab.c"
#include "qtype_sqrt.c"

// complex
#include "cqtype_arithmetic.c"
#include "cqtype_conversion.c"
