/* This function wraps around the fixed 8-bit encoder, performing the
 * basis transformations necessary to meet the CCSDS standard
 *
 * Copyright 2002, Phil Karn, KA9Q
 * fixed bug Aug 2007
 * May be used under the terms of the GNU Lesser General Public License (LGPL)
 */
 #include "fec.h"

 void encode_rs_ccsds(data_t* data, data_t* parity, data_t* block)
 {
     int i;
     data_t cdata[NN - NROOTS];

     /* Convert data from dual basis to conventional */
     for (i = 0; i < NN - NROOTS; i++) {
         cdata[i] = Tal1tab[data[i]];
     }

     encode_rs_8(cdata, parity);

     /* Convert parity from conventional to dual basis */
     for (i = 0; i < NROOTS; i++) {
         parity[i] = Taltab[parity[i]];
     }

     for (i = 0; i < NN; i++) {
        if (i < NN - NROOTS) {
            block[i] = data[i];
        } else {
            block[i] = parity[i - (NN - NROOTS)];
        }
     }
 }