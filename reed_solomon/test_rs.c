#include <stdio.h>
#include <string.h>

#include "decode_rs.h"
#include "fec.h"

int main() {
    data_t data[223] = {0};
    data_t parity[32] = {0};
    int pad = 0;
    int i;

    for (i = 0; i < 223; i++) {
        data[i] = i;
    }

    data_t output[NN];

    encode_rs_ccsds(data, output);

    printf("Encoded: ");
    for (i = 0; i < NN; i++) {
        printf("%u ", output[i]);
    }


    int x = 10;
    printf("\nErrors: \n");
    for (i = 0; i < 16; i += 4) {
        data[x + i]  ^= 0x0F;
        data[x + i + 1] ^= 0xF0;
        data[x + i + 2] ^= 0xCA;
        data[x + i + 3] ^= 0x15;
        printf("%d: %d ", x + i, data[x + i]);
    }

    data_t decoded[255] = {0};
    memcpy(decoded, data, 223);
    memcpy(decoded + 223, parity, 32);
    int* erasures = NULL;

    int roots = decode_rs_ccsds(decoded, erasures, 0);
    printf("\nroots: %d\n", roots);

    printf("Decoded: ");
    for (i = 0; i < sizeof(decoded); i++) {
        printf("%u ", decoded[i]);
    }


}