#include "task.h"
#include "binary.h"

#include <string>
#include <vector>

void task::printTruthTable(bits_t b) {
	std::cout << "x y z F\n";

	for (bits_t i{ 0 }; i < 8; ++i) {
		binary::print(i, 3, true);
		std::cout << (bool)(b & (1 << 7 - i)) << '\n';
	}
}

bits_t task::getDvoista(bits_t b) {
	bits_t result{};

	int size{ 8 };

	for (int i{ 0 }; i < size - 1; ++i) {
		result |= static_cast<bool>(b & (1 << i)) << (7 - i);
	}

	return ~result;
}

void task::printDDNF(bits_t b) {
	std::string out{};

	out += "DDNF: \n";

	for (bits_t i{ 0 }; i < 8; ++i) {
		if ( static_cast<bool>( (b & (1 << 7 - i)) ) ) {
			/*out += '(';
			* out += std::to_string(static_cast<int>(i) + 1);
			* out += ") ";
			*/
			for (bits_t j{ 0 }; j < 3; ++j) {
				out += static_cast<unsigned char>(120 + j);
				if ( !(i & (1 << (2 - j))) ) {
					out += '\'';
				}
			}

			out += " v \n";
		}
	}

	out = out.substr(0, out.length() - 4);
	out += '\n';

	std::cout << out;
}

void task::printDKNF(bits_t b) {
	std::string out{};
	out += "DKNF: \n";

	for (bits_t i{ 0 }; i < 8; ++i) {
		if (!static_cast<bool>((b & (1 << 7 - i)))) {
			/*out += '(';
			* out += std::to_string(static_cast<int>(i) + 1);
			* out += ") ";
			*/

			for (bits_t j{ 0 }; j < 3; ++j) {
				out += static_cast<unsigned char>(120 + j);
				if ((i & (1 << (2 - j)))) {
					out += '\'';
				}
				else {
					out += ' ';
				}

				if (j != 2)
					out += " v ";
			}

			out += " ^ \n";
		}
	}

	out = out.substr(0, out.length() - 4);
	out += '\n';
	
	std::cout << out;
}

std::string task::getJigalkinsPolynom(bits_t b, std::string *ptr) {
	static std::vector<std::string> map{
		"1", "z", "y", "yz", "x", "xz", "xy", "xyz"
	};

	std::string out{};
	out += "Jigalkin's polynom: \n";

	bool triangle[8][8]{};

	for (int i{ 0 }; i < 8; ++i) {
		triangle[0][i] = static_cast<bool>(b & (1 << (7 - i)));
	}

	for (int i{ 1 }; i < 8; ++i) {
		for (int j{ 0 }; j < 8 - i; ++j) {
			triangle[i][j] = triangle[i - 1][j] ^ triangle[i - 1][j + 1];
		}
	}

	for (int i{ 0 }; i < 8; ++i) {
		if (triangle[i][0]) {
			out += map[i];
			out += " + ";
		}
	}

	out = out.substr(0, out.length() - 3);
	if(ptr)
		*ptr = out.substr(21, out.length() - 1);
	return out + '\n';
}

bool task::isMonotonous(bits_t b) {
	for (int i{ 7 }; i < 0; ++i) {
		int first{ static_cast<bool>(b & (1 << i)) };
		int second{ static_cast<bool>(b & (1 << (i + 1))) };

		if(first <= second)
			return false;
	}

	return true;
}

std::vector<std::string> split(std::string &strToDestroy, const std::string &delimiter) {
	std::vector<std::string> res{};
	res.resize(8);

	size_t pos = 0;
	std::string token;
	int counter{};
	while ((pos = strToDestroy.find(delimiter)) != std::string::npos) {
		res[pos] = strToDestroy.substr(0, pos);
		strToDestroy.erase(0, pos + delimiter.length());
		
		++counter;
	}
	
	return res;
}

bool task::isLinear(bits_t b) {
	std::string jigalkins{};
	task::getJigalkinsPolynom(b, &jigalkins);

	std::vector<std::string> vec{ split(jigalkins, " + ") };

	for (std::string str : vec) {
		if (str.length() > 1)
			return false;
	}

	return true;
}