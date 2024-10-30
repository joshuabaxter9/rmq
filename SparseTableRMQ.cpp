#include "SparseTableRMQ.h"

SparseTableRMQ::SparseTableRMQ(const RMQEntry* elems, std::size_t numElems){
  /* TODO: Delete this line, the lines after this one, and implement
   * this function.
   */
	v = elems;
	number_of_elements = numElems;
	log_table_size = numElems + 1;

	//log table instantiation
	log_table = new size_t[log_table_size] {0};

	for(size_t i = 2; i < log_table_size; i++)
		log_table[i] = log_table[i/2] + 1;

	//sparse table creation
	sparse_table = new size_t *[log_table[log_table_size - 1] + 1];

	for(size_t row = 0; row < (log_table[log_table_size-1] + 1); row++)
		sparse_table[row] = new size_t[numElems];

	//fill the inital row will all its default indices
	for(size_t i = 0; i < numElems; i++)
		sparse_table[0][i] = i;

	//populate
	for(size_t row = 1; row < (log_table[log_table_size - 1] + 1); row++){
		for(size_t i = 0; i + (1 << row) <= numElems; i++){
			if(elems[sparse_table[row-1][i]] > elems[sparse_table[row-1][i + (1 << (row-1))]]){
				sparse_table[row][i] = sparse_table[row - 1][i + (1 << (row - 1))];
			}
			else{
				sparse_table[row][i] = sparse_table[row - 1][i];
			}
		}
	}
}

SparseTableRMQ::~SparseTableRMQ() {
  /* TODO: Delete this comment and implement this function. */

	for(size_t i = 0; i < log_table[log_table_size - 1] + 1; i++)
		delete[] sparse_table[i];

	delete[] sparse_table;

	delete[] log_table;
}

std::size_t SparseTableRMQ::rmq(std::size_t low, std::size_t high) const {
  /* TODO: Delete this line, the lines after this one, and implement
   * this function.
   */

	size_t log = log_table[high - low];
	if(v[sparse_table[log][low]] < v[sparse_table[log][high - (1 << log)]])
		return sparse_table[log][low];

	else
		return sparse_table[log][high - (1 << log)];

}

//help from marcus
