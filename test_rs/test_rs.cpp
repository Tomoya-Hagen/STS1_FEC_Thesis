#include <stdio.h>
#include <cstring>
#include <random>

#include "fec.h"

int main() {
    data_t data[223] = {0};
    data_t parity[32] = {0};
    int pad = 0;
    int i;

    std::random_device rd;                          // Seed
    std::mt19937 gen(rd());                         // Mersenne Twister RNG
    std::uniform_int_distribution<> dist(1, 254);   // Range

    for (i = 0; i < 223; i++) {
        int randomNumber = dist(gen);
        data[i] = --randomNumber;
    }

    unsigned char block[NN] = {0};
    encode_rs_ccsds(data, parity, block, pad);

    printf("Parity Symbols: ");
    for (i = 0; i < NROOTS; i++) {
        printf("%u ", parity[i]);
    }
    printf("\n");
    printf("Encoded: ");
    for (i = 0; i < NN; i++) {
        printf("%u ", block[i]);
    }
    printf("\n");

    int x = 10;
    // printf("\nErrors: \n");
    for (i = 0; i < 16; i += 4) {
        block[x + i]  ^= 0x11;
        block[x + i + 1] ^= 0xF1;
        block[x + i + 2] ^= 0xBF;
        block[x + i + 3] ^= 0xB1;
        // printf("%d: %d ", x + i, block[x + i]);
    }

    printf("Corrupted: \n");
    for (i = 0; i < NN; i++) {
        printf("%d ", block[i]);
    }
    printf("\n\n");

    data_t decoded[NN - NROOTS] = {0};
    int* erasures = NULL;

    int roots = decode_rs_ccsds(block, decoded, erasures, 0, pad);
    printf("\nroots: %d\n", roots);

    printf("Decoded: ");
    for (i = 0; i < sizeof(decoded); i++) {
        printf("%u ", decoded[i]);
    }

}