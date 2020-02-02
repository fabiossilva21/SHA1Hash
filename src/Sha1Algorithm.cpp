#include <Sha1Algorithm.hpp>

#include <iostream>
#include <inttypes.h>
#include <sstream>
#include <iomanip>

namespace Sha1Algorithm {

    std::vector<uint32_t> splitMessageIn16Of32Bits(std::string str, int offset) {
        std::vector<uint32_t> output;

        if ((str.length() * 8) < (offset+1) * 512) {
            return output;
        }

        int beginning = (offset * 64);
        int end = (offset + 1) * 64;

        std::string aux(str.begin() + beginning, str.begin() + end);

        for (int i = 0; i < 64; i += 4) {
            uint8_t firstChar = aux.at(i);
            uint8_t secondChar = aux.at(i + 1);
            uint8_t thirdChar = aux.at(i + 2);
            uint8_t fourthChar = aux.at(i + 3);

            uint32_t aux32 = (firstChar << 24) + (secondChar << 16) + (thirdChar << 8) + (fourthChar);

            output.push_back(aux32);
        }

        return output;
    }

    uint32_t leftRotate(int n, uint32_t d) {
        uint32_t aux = (d >> (32 - n));
        return (d << n) | aux;
    }

    std::string Sha1Hash(const std::vector<uint8_t>& data){
        return Sha1Hash(std::string(data.begin(), data.end()));
    }

    std::string Sha1Hash(const std::string& data){
        // Known constants
        uint32_t h0 = 0x67452301;
        uint32_t h1 = 0xEFCDAB89;
        uint32_t h2 = 0x98BADCFE;
        uint32_t h3 = 0x10325476;
        uint32_t h4 = 0xC3D2E1F0;

        std::string auxiliar(data);

        auxiliar.push_back(0x80); // Append a '1'

        // Pad the message until it is 512 mod 448
        while (((auxiliar.length() * 8) % 512) != 448) {
            auxiliar.push_back(0x00);
        }

        // Get the length of the original message
        uint64_t l = data.length() * 8;

        // Append the length onto it
        for (int i = 56; i >= 0; i -= 8) {
            auxiliar.push_back((l & (0xFFULL << i)) >> i);
        }

        // Divide in 16 chunks of 32 bits (4 bytes)
        int offset = 0;


        std::vector<uint32_t> chunk = splitMessageIn16Of32Bits(auxiliar, offset++);
        while (!chunk.empty()) {
            
            // Extend it to 80 chunks
            for (int i = 16; i < 80; i++) {
                uint32_t wordA = chunk.at(i - 3);
                uint32_t wordB = chunk.at(i - 8);
                uint32_t wordC = chunk.at(i - 14);
                uint32_t wordD = chunk.at(i - 16);

                uint32_t xorA = wordA ^ wordB;
                uint32_t xorB = xorA ^ wordC;
                uint32_t xorC = xorB ^ wordD;

                uint32_t nextChunk = leftRotate(1, xorC);
                
                chunk.push_back(nextChunk);
            }

            uint32_t a = h0;
            uint32_t b = h1;
            uint32_t c = h2;
            uint32_t d = h3;
            uint32_t e = h4;

            for (int i = 0; i < 80; i++) {
                uint32_t f = 0;
                uint32_t k = 0;

                if (i < 20) {
                    f = (b & c) | ((~b) & d);
                    k = 0x5A827999;
                } else if (i < 40) {
                    f = b ^ c ^ d;
                    k = 0x6ED9EBA1;
                } else if (i < 60) {
                    f = (b & c) | (b & d) | (c & d);
                    k = 0x8F1BBCDC;
                } else if (i < 80) {
                    f = b ^ c ^ d;
                    k = 0xCA62C1D6;
                }

                uint32_t tmp = leftRotate(5, a) + f + e + k + chunk.at(i);
                e = d;
                d = c;
                c = leftRotate(30, b);
                b = a;
                a = tmp;
            }

            h0 += a;
            h1 += b;
            h2 += c;
            h3 += d;
            h4 += e;

            chunk = splitMessageIn16Of32Bits(auxiliar, offset++);
        }

        std::stringstream sstream;

        sstream << std::hex << std::setw(8) << std::setfill('0') << h0 
                << std::hex << std::setw(8) << std::setfill('0') << h1 
                << std::hex << std::setw(8) << std::setfill('0') << h2 
                << std::hex << std::setw(8) << std::setfill('0') << h3 
                << std::hex << std::setw(8) << std::setfill('0') << h4;

        return sstream.str();
    }

}