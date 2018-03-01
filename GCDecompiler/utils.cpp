
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "types.h"
#if defined(_WIN32) || defined(WIN32)
#include <windows.h>
#else
#include <unistd.h>
#include <sys/stat.h>
#endif

uint btoi(char *bytes, uint len) {
	uint out = 0;
	for (uint i = 0; i < len; i++) {
		out += bytes[i] << (8 * (len - i - 1));
	}
	return out;
}

const char* itob(uint num, uint length = 4) {
	char *output = new char[length]();
	for (uint i = 0; i < length; i++) {
		output[i] = num >> (8 * (length - i - 1));
	}
	return output;
}

std::string ctoh(char num) {
	std::stringstream out;
	if (num < 16) {
		out << "0";
	}
	out << std::hex << std::uppercase << (int)num;
	return out.str();
}

std::string itoh(uint num) {
	std::stringstream out;
	out << "0x";
	out << std::hex << std::uppercase << num;
	return out.str();
}

std::string itoh(int num) {
	std::stringstream out;
	if (num < 0) {
		out << "-";
		num = -num;
	}
	out << "0x";
	out << std::hex << std::uppercase << num;
	return out.str();
}

bool ends_with(std::string val, std::string ending) {
	if (ending.size() > val.size()) return false;
	return !val.compare(val.length() - ending.length(), ending.length(), ending);
}

uint next_int(std::fstream *file, uint length) {
	char *input = new char[length]();
	file->read(input, length);
	uint out = btoi(input, length);
	delete[] input;
	return out;
}

void write_int(std::fstream *file, uint num, uint length) {
	const char *to_write;
	to_write = itob(num, length);
	file->write(to_write, length);
	delete[] to_write;
}

