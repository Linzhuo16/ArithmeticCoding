#include <stdexcept>
#include "FrequencyTable.hpp"
#include <iostream>
using std::uint32_t;


FrequencyTable::~FrequencyTable() {}


FlatFrequencyTable::FlatFrequencyTable(uint32_t numSyms) {
	if (numSyms < 1)
		throw std::domain_error("Number of symbols must be positive");
	if (numSyms > UINT32_MAX - 1)
		throw std::length_error("Too many symbols");

	uint32_t size = numSyms;
	numSymbols = numSyms;

	frequencies.reserve(numSymbols + 1);
	for (uint32_t i = 0; i < size + 1; i++)
		frequencies.push_back(1);
	
	// BITVec init
	BITVec.reserve(numSymbols + 1);
	
	for (uint32_t i = 0; i <= size; i++)
		BITVec.push_back(0);

	for (uint32_t i = 1; i < size; i++)
		update(i, 1);

	total = getHigh(size - 1);
}


uint32_t FlatFrequencyTable::getSymbolLimit() const {
	return numSymbols+1;
}


uint32_t FlatFrequencyTable::get(uint32_t symbol) const  {
	checkSymbol(symbol);

	return 1;
}


uint32_t FlatFrequencyTable::getTotal() const  {
	return total;
}


uint32_t FlatFrequencyTable::getLow(uint32_t symbol) const  {
	checkSymbol(symbol);
	return prefixSum(symbol);
}


uint32_t FlatFrequencyTable::getHigh(uint32_t symbol) const  {
	checkSymbol(symbol);
	return prefixSum(symbol+1);
}


void FlatFrequencyTable::set(uint32_t, uint32_t)  {
	throw std::logic_error("Unsupported operation");
}


void FlatFrequencyTable::increment(uint32_t symbol) {
	if (frequencies.at(symbol) == UINT32_MAX)
		throw std::overflow_error("Arithmetic overflow");
	frequencies.at(symbol)++;
	checkedAdd(total, 1);
	update(symbol, 1);
}


void FlatFrequencyTable::checkSymbol(uint32_t symbol) const {
	if (symbol >= numSymbols){
		//std::cout << "file" << __FILE__<<"line="<<__LINE__<<std::endl;
		throw std::domain_error("Symbol out of range");
	}
}


uint32_t FlatFrequencyTable::checkedAdd(uint32_t x, uint32_t y) {
	if (x > UINT32_MAX - y)
		throw std::overflow_error("Arithmetic overflow");
	return x + y;
}


uint32_t FlatFrequencyTable::prefixSum(uint32_t symbol) const {
	checkSymbol(symbol);
	uint32_t sum = 0;
	while(symbol > 0) {
		sum = checkedAdd(sum, BITVec.at(symbol));
		symbol = symbol - (symbol & -symbol);
	}
	return sum;
}

void FlatFrequencyTable::update(uint32_t symbol, uint32_t delta) {
	checkSymbol(symbol);
	while(symbol < numSymbols) {
		BITVec.at(symbol) += delta;
		symbol = symbol + (symbol & -symbol);
	}
}






SimpleFrequencyTable::SimpleFrequencyTable(const std::vector<uint32_t> &freqs) {
	if (freqs.size() > UINT32_MAX - 1)
		throw std::length_error("Too many symbols");
	uint32_t size = static_cast<uint32_t>(freqs.size());
	if (size < 1)
		throw std::invalid_argument("At least 1 symbol needed");
	
	frequencies = freqs;
	cumulative.reserve(size + 1);
	initCumulative(false);
	total = getHigh(size - 1);
}


SimpleFrequencyTable::SimpleFrequencyTable(const FrequencyTable &freqs) {
	uint32_t size = freqs.getSymbolLimit();
	if (size < 1)
		throw std::invalid_argument("At least 1 symbol needed");
	if (size > UINT32_MAX - 1)
		throw std::length_error("Too many symbols");
	
	frequencies.reserve(size + 1);
	for (uint32_t i = 0; i < size; i++)
		frequencies.push_back(freqs.get(i));
	
	cumulative.reserve(size + 1);
	initCumulative(false);
	total = getHigh(size - 1);
}


uint32_t SimpleFrequencyTable::getSymbolLimit() const {
	return static_cast<uint32_t>(frequencies.size());
}


uint32_t SimpleFrequencyTable::get(uint32_t symbol) const {
	return frequencies.at(symbol);
}


void SimpleFrequencyTable::set(uint32_t symbol, uint32_t freq) {
	if (total < frequencies.at(symbol))
		throw std::logic_error("Assertion error");
	uint32_t temp = total - frequencies.at(symbol);
	total = checkedAdd(temp, freq);
	frequencies.at(symbol) = freq;
	cumulative.clear();
}


void SimpleFrequencyTable::increment(uint32_t symbol) {
	if (frequencies.at(symbol) == UINT32_MAX)
		throw std::overflow_error("Arithmetic overflow");
	total = checkedAdd(total, 1);
	frequencies.at(symbol)++;
	cumulative.clear();
}


uint32_t SimpleFrequencyTable::getTotal() const {
	return total;
}


uint32_t SimpleFrequencyTable::getLow(uint32_t symbol) const {
	initCumulative();
	return cumulative.at(symbol);
}


uint32_t SimpleFrequencyTable::getHigh(uint32_t symbol) const {
	initCumulative();
	return cumulative.at(symbol + 1);
}


void SimpleFrequencyTable::initCumulative(bool checkTotal) const {
	if (!cumulative.empty())
		return;
	uint32_t sum = 0;
	cumulative.push_back(sum);
	for (uint32_t freq : frequencies) {
		// This arithmetic should not throw an exception, because invariants are being maintained
		// elsewhere in the data structure. This implementation is just a defensive measure.
		sum = checkedAdd(freq, sum);
		cumulative.push_back(sum);
	}
	if (checkTotal && sum != total)
		throw std::logic_error("Assertion error");
}


uint32_t SimpleFrequencyTable::checkedAdd(uint32_t x, uint32_t y) {
	if (x > UINT32_MAX - y)
		throw std::overflow_error("Arithmetic overflow");
	return x + y;
}
