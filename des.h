#ifndef des_h
#define des_h

#include <iostream>
#include <fstream>
#include <string>
#include <bitset>
#include <vector>
#include <time.h>
#include <stdlib.h>
#include "hex.h"
#include "base64.h"

using uchar = unsigned char;
using cint = const unsigned int;

constexpr auto kBlockSize = 64; // block size used in DES algorithm (in bits)
constexpr auto kKeySize = 56; // key size used in DES algorithm (in bits)
constexpr auto kRoundKeySize = 48; // round key size which are derived from main key
constexpr auto kNumRounds = 16; // total number of rounds in Feistel network
constexpr auto kByteSize = 8; // 1 byte/8 bits

enum class Mode { GenerateKey, Encrypt, Decrypt, Undefined };

struct Keychain {
    std::bitset<kBlockSize> mainKey64; // main key including parity bits
    std::bitset<kKeySize> mainKey56; // main key used in algorithm
    std::bitset<kRoundKeySize> roundKeys[kNumRounds]; // round keys array
};

class DES {
    std::vector<std::bitset<kBlockSize>> in, out;
	Mode mode;
    Keychain keys;
	void resizeTexts(cint &);
    template<std::size_t N> void loadBitset(uchar, std::bitset<N> &);
	template<std::size_t N, std::size_t M> void permute(std::bitset<N> &, std::bitset<M> &, cint &, cint &, cint *);
	void roundKeygen(); // computes round keys from main key
	std::bitset<kBlockSize/2> roundFunction(int, std::bitset<kBlockSize/2>);
public:
    DES(std::string s, int length, std::string key, Mode mode) {
		this->mode = mode;
		cint numBlock = mode == Mode::Encrypt ? length/kByteSize + 1 : length/kByteSize;
		for(int i = 0; i < kByteSize; ++i) loadBitset(key[i], keys.mainKey64);
        resizeTexts(numBlock);
        for(int i = 0; i < length; ++i) loadBitset(s[i], in[i/kByteSize]); // load "pt" vector with input
		if(mode == Mode::Encrypt) {
			for(int i = 0; i < (kByteSize - length%kByteSize); ++i) { // loop to add padding, PKCS5 scheme used.
	            in.back() <<= kByteSize;
	            in.back() |= std::bitset<kBlockSize>(8 - length%kByteSize);
	        }
		}
	}
	static std::string keygen(); // pseudorandom key gen. based on rand(), which is NOT cryptographically secure
	void runDES(Mode & mode); // run the algorithm
	void output();
};
#include "des.tcc"
#endif /* des_h */