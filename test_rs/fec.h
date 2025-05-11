#pragma once
/* User include file for libfec
 * Copyright 2004, Phil Karn, KA9Q
 * May be used under the terms of the GNU Lesser General Public License (LGPL)
 */
 #include "fixed.h"

 #ifndef _FEC_H_
 #define _FEC_H_

 #define ALPHA_TO CCSDS_alpha_to
 #define INDEX_OF CCSDS_index_of
 #define GENPOLY CCSDS_Poly

 /* General purpose RS codec, 8-bit symbols */
 void encode_rs_char(void* rs, unsigned char* data, unsigned char* parity);
 int decode_rs_char(void* rs, unsigned char* data, int* eras_pos, int no_eras);
 void* init_rs_char(int symsize, int gfpoly, int fcr, int prim, int nroots, int pad);
 void free_rs_char(void* rs);

 /* CCSDS standard (255,223) RS codec with conventional (*not* dual-basis)
  * symbol representation
  */
 void encode_rs_8(unsigned char* data, unsigned char* parity, int pad);
 int decode_rs_8(unsigned char* data, int* eras_pos, int no_eras, int pad);

 /* CCSDS standard (255,223) RS codec with dual-basis symbol representation */
 void encode_rs_ccsds(data_t* data, data_t* parity, data_t* block, int pad);
 int decode_rs_ccsds(data_t* data, data_t* decoded, int* eras_pos, int no_eras, int pad);

 /* Tables to map from conventional->dual (Taltab) and
  * dual->conventional (Tal1tab) bases
  */
//  extern unsigned char Taltab[], Tal1tab[];

extern unsigned char CCSDS_alpha_to[];
extern unsigned char CCSDS_index_of[];
extern unsigned char CCSDS_Poly[];
 #endif /* _FEC_H_ */