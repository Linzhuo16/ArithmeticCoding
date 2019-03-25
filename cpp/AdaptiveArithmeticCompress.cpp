#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <stdexcept>
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
	
	// Perform file compression
	std::ifstream in(inputFile, std::ios::binary);
	std::ofstream out(outputFile, std::ios::binary);
	BitOutputStream bout(out);
	try {
		
		FlatFrequencyTable freqs(257);
		ArithmeticEncoder enc(32, bout);
		while (true) {
			// Read and encode one byte
			int symbol = in.get();
			if (symbol == EOF)
				break;
			if (symbol < 0 || symbol > 255)
				throw std::logic_error("Assertion error");
			enc.write(freqs, static_cast<uint32_t>(symbol));
			freqs.increment(static_cast<uint32_t>(symbol));
		}
		
		enc.write(freqs, 256);  // EOF
		enc.finish();  // Flush remaining code bits
		bout.finish();
		return EXIT_SUCCESS;
		
	} catch (const char *msg) {
		std::cerr << msg << std::endl;
		return EXIT_FAILURE;
	}
}
