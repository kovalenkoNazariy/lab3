#ifndef BINARY_H
#define BINARY_H

#include <iostream>

using bits_t = unsigned char;

namespace binary {
	void print(bits_t b, int size=8, bool spacedOut = false);
	bits_t getFromCmd();
}

#endif