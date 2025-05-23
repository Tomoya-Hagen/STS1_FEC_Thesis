#undef A0
#define A0 (NN) /* Special reserved value encoding zero in index form */

#include <cstring>

#include "ReedSolomon.h"

void encode_rs_8(data_t* data, data_t* parity)
{
    int i, j;
    data_t feedback;

    std::memset(parity, 0, NROOTS * sizeof(data_t));

    for (i = 0; i < NN - NROOTS; i++) {
        feedback = INDEX_OF[data[i] ^ parity[0]];
        if (feedback != A0) { /* feedback term is non-zero */
#ifdef UNNORMALIZED
            /* This line is unnecessary when GENPOLY[NROOTS] is unity, as it must
             * always be for the polynomials constructed by init_rs()
             */
            feedback = MODNN(NN - GENPOLY[NROOTS] + feedback);
#endif
            for (j = 1; j < NROOTS; j++) {
                parity[j] ^= ALPHA_TO[MODNN(feedback + GENPOLY[NROOTS - j])];
            }
        }
        /* Shift */
        std::memmove(&parity[0], &parity[1], sizeof(data_t) * (NROOTS - 1));
        if (feedback != A0)
            parity[NROOTS - 1] = ALPHA_TO[MODNN(feedback + GENPOLY[0])];
        else
            parity[NROOTS - 1] = 0;
    }
}