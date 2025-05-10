/* User include file for libfec
 * Copyright 2004, Phil Karn, KA9Q
 * May be used under the terms of the GNU Lesser General Public License (LGPL)
 */
 #pragma once

 #include "fixed.h"

 #ifndef _FEC_H_
 #define _FEC_H_

 /* General purpose RS codec, 8-bit symbols */
//  void encode_rs_char(void* rs, data_t* data, data_t* parity);
//  int decode_rs_char(void* rs, data_t* data, int* eras_pos, int no_eras);
//  void* init_rs_char(int symsize, int gfpoly, int fcr, int prim, int nroots, int pad);
//  void free_rs_char(void* rs);

 /* CCSDS standard (255,223) RS codec with conventional (*not* dual-basis)
  * symbol representation
  */
 void encode_rs_8(data_t* data, data_t* parity);
 int decode_rs_8(data_t* data, int* eras_pos, int no_eras);

 /* CCSDS standard (255,223) RS codec with dual-basis symbol representation */
 void encode_rs_ccsds(data_t* data, data_t* output);
 int decode_rs_ccsds(data_t* data, int* eras_pos, int no_eras);

 /* Tables to map from conventional->dual (Taltab) and
  * dual->conventional (Tal1tab) bases
  */
 extern unsigned char Taltab[], Tal1tab[];

 #endif /* _FEC_H_ */