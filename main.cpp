#include "des.h"
#include <streambuf>

constexpr char kGenerateKey[] = "-g";
constexpr char kEncrypt[] = "-e";
constexpr char kDecrypt[] = "-d";

int main(int argc, const char * argv[]) {
	Mode mode;
	if(argc == 3 && strcmp(argv[1], kGenerateKey) == 0) {
		mode = Mode::GenerateKey;
		std::fstream output(argv[2], std::ios::out);
		output << DES::keygen();
		output.close();
		std::cout << "Key generated.\n";
		exit(0); // success
	}
	else if(argc == 4 && strcmp(argv[1], kEncrypt) == 0) mode = Mode::Encrypt;
	else if(argc == 4 && strcmp(argv[1], kDecrypt) == 0) mode = Mode::Decrypt;
	else {
		std::cout <<
			"Usage:\n    " <<
			"Generate Key: DES " << kGenerateKey << " [filename]\n    " <<
			"Encrypt: DES " << kEncrypt << " [keyfile] [plaintext file]\n    " <<
			"Decrypt: DES " << kDecrypt << " [keyfile] [ciphertext file]\n";
        exit(-1); // if no input provided, exit with code -1.
	}

	std::ifstream inputFile(argv[3]);
    std::string input((std::istreambuf_iterator<char>(inputFile)), std::istreambuf_iterator<char>());
	inputFile.close();

	std::ifstream keyFile(argv[2]);
	std::string key((std::istreambuf_iterator<char>(keyFile)), std::istreambuf_iterator<char>());
	keyFile.close();

	DES des(input, input.length(), key, mode);

	des.runDES(mode);
	des.output();

	return 0;
}
