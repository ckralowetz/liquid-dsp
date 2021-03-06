/*
 * Copyright (c) 2007, 2008, 2009, 2010, 2011, 2012, 2013 Joseph Gaeddert
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

#include <assert.h>
#include "autotest/autotest.h"
#include "liquid.h"

// Helper function to keep code base small
void firpfbch2_crcf_runtest(unsigned int _M,
                            unsigned int _m,
                            float        _As)
{
    float tol = 1e-3f;
    unsigned int i;

    // derived values
    unsigned int num_symbols = 8*_m;    // number of symbols
    unsigned int num_samples = _M * num_symbols;

    // allocate arrays
    float complex x[num_samples];
    float complex y[num_samples];

    // generate pseudo-random sequence
    unsigned int s = 1;         // seed
    unsigned int p = 524287;    // large prime number
    unsigned int g =   1031;    // another large prime number
    for (i=0; i<num_samples; i++) {
        s = (s * p) % g;
        x[i] = (float)s / (float)g - 0.5f;
        //x[i] = (i==0) ? 1.0f : 0.0f;  // impulse response
    }

    // create filterbank objects from prototype
    firpfbch2_crcf qa = firpfbch2_crcf_create_kaiser(LIQUID_ANALYZER,    _M, _m, _As);
    firpfbch2_crcf qs = firpfbch2_crcf_create_kaiser(LIQUID_SYNTHESIZER, _M, _m, _As);

    // run channelizer
    float complex Y[_M];
    for (i=0; i<num_samples; i+=_M/2) {
        // run analysis filterbank
        firpfbch2_crcf_execute(qa, &x[i], Y);

        // run synthesis filterbank
        firpfbch2_crcf_execute(qs, Y, &y[i]);
    }

    // destroy fiterbank objects
    firpfbch2_crcf_destroy(qa); // analysis fitlerbank
    firpfbch2_crcf_destroy(qs); // synthesis filterbank

    // validate output
    unsigned int delay = 2*_M*_m - _M/2 + 1;
    float rmse = 0.0f;
    for (i=0; i<num_samples; i++) {
        //printf("%3u : %12.8f + %12.8fj\n", i, crealf(y[i]), cimagf(y[i]));
        if (i < delay) {
            CONTEND_DELTA( crealf(y[i]), 0.0f, tol );
            CONTEND_DELTA( cimagf(y[i]), 0.0f, tol );
        } else {
            CONTEND_DELTA( crealf(y[i]), crealf(x[i-delay]), tol );
            CONTEND_DELTA( cimagf(y[i]), cimagf(x[i-delay]), tol );
        }

        // compute rmse
        float complex err = y[i] - (i < delay ? 0.0f : x[i-delay]);
        rmse += crealf(err * conjf(err));
    }

    rmse = sqrtf(rmse / (float)num_samples);
    if (liquid_autotest_verbose)
        printf("firpfbch2:  M=%3u, m=%2u, As=%8.2f dB, rmse=%12.4e\n", _M, _m, _As, rmse);
}

// analysis
void autotest_firpfbch2_crcf_n8()    { firpfbch2_crcf_runtest(   8, 5, 60.0f); }
void autotest_firpfbch2_crcf_n16()   { firpfbch2_crcf_runtest(  16, 5, 60.0f); }
void autotest_firpfbch2_crcf_n32()   { firpfbch2_crcf_runtest(  32, 5, 60.0f); }
void autotest_firpfbch2_crcf_n64()   { firpfbch2_crcf_runtest(  64, 5, 60.0f); }

