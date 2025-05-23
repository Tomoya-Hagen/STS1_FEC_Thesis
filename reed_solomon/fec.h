#pragma once
/* User include file for libfec
 * Copyright 2004, Phil Karn, KA9Q
 * May be used under the terms of the GNU Lesser General Public License (LGPL)
 */

 #ifndef _FEC_H_
 #define _FEC_H_

 #define ALPHA_TO CCSDS_alpha_to
 #define INDEX_OF CCSDS_index_of
 #define GENPOLY CCSDS_Poly
 typedef unsigned char data_t;

static inline int mod255(int x)
{
    while (x >= 255) {
        x -= 255;
        x = (x >> 8) + (x & 255);
    }
    return x;
}
#define MODNN(x) mod255(x)

#define MM 8
#define NN 255
#define NROOTS 32
#define FCR 112
#define PRIM 11
#define IPRIM 116
#define PAD pad

 /* CCSDS standard (255,223) RS codec with conventional (*not* dual-basis)
  * symbol representation
  */
 void encode_rs_8(data_t* data, data_t* parity);
 int decode_rs_8(data_t* data, int* eras_pos = nullptr, int no_eras = 0);

 /* CCSDS standard (255,223) RS codec with dual-basis symbol representation */
 void encode_rs_ccsds(data_t* data, data_t* parity);
 int decode_rs_ccsds(data_t* data, int* eras_pos = nullptr, int no_eras = 0);

 /* Tables to map from conventional->dual (Taltab) and
  * dual->conventional (Tal1tab) bases
  */
 extern data_t Taltab[], Tal1tab[];

extern data_t CCSDS_alpha_to[];
extern data_t CCSDS_index_of[];
extern data_t CCSDS_Poly[];
 #endif /* _FEC_H_ */