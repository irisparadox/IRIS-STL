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
struct hash {
    size_t operator()(const std::string& _Mykey) const {
        return XXH64(_Mykey);
    }

    template <typename _Ty>
    size_t operator()(const _Ty& _Mykey) const {
        return murmur3_32(_Mykey);
    }

private:
    
    uint64 lsbhash(const uint64& _Mykey) const {
        return (_Mykey ^ (_Mykey >> 27)) * 0x9e3779b97f4a7c15;
    }

    inline uint64 rotl64(uint64 x, int r) const {
        return (x << r) | (x >> (64 - r));
    }

    uint64 XXH64(const std::string& input, uint64 seed = 1) const {
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
                if (remainingLength < 8 * (i + 1)) break;

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

    static inline uint32 murmur_32_scramble(uint32 k) {
        k *= 0xcc9e2d51;
        k = (k << 15) | (k >> 17);
        k *= 0x1b873593;
        return k;
    }

    template <typename _Ty>
    uint32 murmur3_32(const _Ty& _Mykey, uint32 _Seed = 1) const {

        const uint8* data = reinterpret_cast<const uint8*>(&_Mykey);
        size_t len = sizeof(_Ty);

        uint32 h = _Seed;
        uint32 k;
        
        for (size_t i = len >> 2; i; --i) {
            memcpy(&k, data, sizeof(uint32));
            data += sizeof(uint32);
            h ^= murmur_32_scramble(k);
            h  = (h << 13) | (h >> 19);
            h  = h * 5 + 0xe6546b64;
        }

        k = 0;
        for (size_t i = len & 3; i; --i) {
            k <<= 8;
            k |= data[i - 1];
        }

        h ^= murmur_32_scramble(k);
        h ^= len;
        h ^= h >> 16;
        h *= 0x85ebca6b;
        h ^= h >> 13;
        h *= 0xc2b2ae35;
        h ^= h >> 16;

        return h;
    }
};
_IRIS_END_
#endif // _IRIS_HASH_
