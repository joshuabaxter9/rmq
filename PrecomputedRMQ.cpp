#include "PrecomputedRMQ.h"

PrecomputedRMQ::PrecomputedRMQ(const RMQEntry* elems, std::size_t numElems) {


	table = new size_t*[numElems];

	for(size_t i = 0; i < numElems; ++i){
		table[i] = new size_t[numElems];
	}


	for(size_t i = 0; i < numElems; i++)
		table[i][i] = i;

	for(size_t i = 0; i < numElems; ++i){
		for(size_t j = i + 1; j < numElems; ++j){
			if(elems[j] < elems[table[i][j - 1]])
				table[i][j] = j;

			else
				table[i][j] = table[i][j - 1];
		}
	}
}

PrecomputedRMQ::~PrecomputedRMQ() {
	for(size_t i = 0; i < count; ++i)
		delete[] table[i];

	delete[] table;

}

//void PrecomputedRMQ::precompute(const RMQEntry* elems, size_t numElems){}

std::size_t PrecomputedRMQ::rmq(std::size_t low, std::size_t high) const {

	return table[low][high - 1];
}
