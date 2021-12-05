#include "binary.h"
#include <string>

void binary::print(bits_t b, int size, bool spacedOut) {
	int sizeOfB{ 8 };

	for (int i{ sizeOfB - 1 - (sizeOfB - size) }; i >= 0; --i) {
		std::cout << (bool)(b & (1 << i));

		if (spacedOut)
			std::cout << ' ';
	}
}

bits_t binary::getFromCmd() {
	std::string str{};
	std::cin >> str;

	bits_t result{};
	int counter{};

	for (auto iterator{ str.rbegin() }; iterator != str.rend(); ++iterator) {
		result |= ((*iterator == '1') << counter);
		counter++;
	}

	return result;
}