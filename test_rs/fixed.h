#pragma once

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

// extern data_t CCSDS_alpha_to[];
// extern data_t CCSDS_index_of[];
// extern data_t CCSDS_poly[];

#define MM 8
#define NN 255
#define NROOTS 32
#define FCR 112
#define PRIM 11
#define IPRIM 116
#define PAD pad