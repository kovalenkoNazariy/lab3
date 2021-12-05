#ifndef TASK_H
#define TASK_H

#include <iostream>
#include "binary.h"

namespace task {
	void printTruthTable(bits_t b);
	bits_t getDvoista(bits_t b);
	void printDDNF(bits_t b);
	void printDKNF(bits_t b);
	std::string getJigalkinsPolynom(bits_t b, std::string *ptr = nullptr);
	bool isMonotonous(bits_t b);
	bool isLinear(bits_t b);
}

#endif