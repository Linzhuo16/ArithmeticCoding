#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <limits>
#include "ArithmeticCoder.hpp"
#include "BitIoStream.hpp"
#include "FrequencyTable.hpp"

using std::uint32_t;


int main(int argc, char *argv[]) {
	// Handle command line arguments
	if (argc != 3) {
		std::cerr << "Usage: " << argv[0] << " InputFile OutputFile" << std::endl;
		return EXIT_FAILURE;
	}
	const char *inputFile  = argv[1];
	const char *outputFile = argv[2];
	
	// Perform file decompression
	std::ifstream in(inputFile, std::ios::binary);
	std::ofstream out(outputFile, std::ios::binary);
	BitInputStream bin(in);
	try {
		
		FlatFrequencyTable freqs(257);
		ArithmeticDecoder dec(32, bin);
		while (true) {
			// Decode and write one byte
			uint32_t symbol = dec.read(freqs);
			if (symbol == 256)  // EOF symbol
				break;
			int b = static_cast<int>(symbol);
			if (std::numeric_limits<char>::is_signed)
				b -= (b >> 7) << 8;
			out.put(static_cast<char>(b));
			freqs.increment(symbol);
		}
		return EXIT_SUCCESS;
		
	} catch (const char *msg) {
		std::cerr << msg << std::endl;
		return EXIT_FAILURE;
	}
}
