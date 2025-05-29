#include "ReedSolomon.hpp"

void RSEncode(unsigned char *data) {
    encode_rs_ccsds(data, data + MessageLength, 0);
}
int RSDecode(unsigned char *data) {
    return decode_rs_ccsds(data, nullptr, 0, 0);
}