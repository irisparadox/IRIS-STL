#ifndef _IRIS_HASH_
#define _IRIS_HASH_

#include <cxx_config.h>
#include <common_types.h>

// XXHASH CONSTANTS
#define XXH64_PRIME1 0x9E3779B185EBCA87ULL
#define XXH64_PRIME2 0xC2B2AE3D27D4EB4FULL
#define XXH64_PRIME3 0x165667B19E3779F9ULL
#define XXH64_PRIME4 0x85EBCA6B7CEC4A64ULL
#define XXH64_PRIME5 0x27D4EB2F165667C5ULL

_IRIS_BEGIN_
inline uint64 rotl64(uint64 x, int r) {
    return (x << r) | (x >> (64 - r));
}

template <typename _Ty>
uint64 XXH64(const _Ty& input, uint64 seed = 0) {
    const uint8* data = reinterpret_cast<const uint8*>(&input);
    size_t length = sizeof(input);

    uint64 h64 = seed + XXH64_PRIME5;

    size_t remainingLength = length;

    while (remainingLength >= 32) {
        uint64 v1 = seed + XXH64_PRIME1 + XXH64_PRIME2;
        uint64 v2 = seed + XXH64_PRIME2;
        uint64 v3 = seed + 0;
        uint64 v4 = seed - XXH64_PRIME1;

        for (int i = 0; i < 4; ++i) {
            uint64 k1 = *(uint64*)(data + i * 8);
            uint64 k2 = *(uint64*)(data + i * 8 + 8);
            uint64 k3 = *(uint64*)(data + i * 8 + 16);
            uint64 k4 = *(uint64*)(data + i * 8 + 24);

            v1 += k1 * XXH64_PRIME2;
            v1 = rotl64(v1, 31);
            v1 *= XXH64_PRIME1;

            v2 += k2 * XXH64_PRIME2;
            v2 = rotl64(v2, 31);
            v2 *= XXH64_PRIME1;

            v3 += k3 * XXH64_PRIME2;
            v3 = rotl64(v3, 31);
            v3 *= XXH64_PRIME1;

            v4 += k4 * XXH64_PRIME2;
            v4 = rotl64(v4, 31);
            v4 *= XXH64_PRIME1;

            data += 32;
            remainingLength -= 32;
        }

        v1 = rotl64(v1, 27) * XXH64_PRIME1 + v2;
        v2 = rotl64(v2, 31) * XXH64_PRIME2 + v3;
        v3 = rotl64(v3, 31) * XXH64_PRIME3 + v4;

        h64 ^= v1 ^ v2 ^ v3;
    }

    uint64 k1 = 0;
    if (remainingLength >= 8) {
        k1 = *(uint64*)data;
        data += 8;
        remainingLength -= 8;
    }

    uint64 k2 = 0;
    if (remainingLength >= 4) {
        k2 = *(uint32*)data;
        data += 4;
        remainingLength -= 4;
    }

    uint64 k3 = 0;
    if (remainingLength >= 2) {
        k3 = *(uint16*)data;
        data += 2;
        remainingLength -= 2;
    }

    uint64 k4 = 0;
    if (remainingLength > 0) {
        k4 = *data;
    }

    h64 ^= k1 * XXH64_PRIME1;
    h64 = rotl64(h64, 31);
    h64 *= XXH64_PRIME2;

    h64 ^= k2 * XXH64_PRIME2;
    h64 = rotl64(h64, 31);
    h64 *= XXH64_PRIME3;

    h64 ^= k3 * XXH64_PRIME3;
    h64 = rotl64(h64, 31);
    h64 *= XXH64_PRIME4;

    h64 ^= k4 * XXH64_PRIME4;
    h64 = rotl64(h64, 31);
    h64 *= XXH64_PRIME5;

    h64 ^= h64 >> 33;
    h64 *= XXH64_PRIME2;
    h64 ^= h64 >> 29;
    h64 *= XXH64_PRIME3;
    h64 ^= h64 >> 32;

    return h64;
}
_IRIS_END_
#endif // _IRIS_HASH_
