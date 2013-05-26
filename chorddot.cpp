/**
* chorddot - Chord DHT Diagram Generation
* @author William Claydon
* @email will@heisamachine.com
* @copyright Beerware
*/
#include <vector>
#include <iostream>
#include <math.h>
#include <algorithm>

class Chord {
size_t size_;
unsigned int finger_table_size_;
std::vector<size_t> available_nodes_;

public:
Chord(size_t size) : size_(size), finger_table_size_(getFingerTableSize(size)) {
}

void addNode(size_t node) {
	available_nodes_.push_back(node);
}

void setAvailableNodes(std::vector<size_t> available_nodes) {
	available_nodes_ = available_nodes;
	std::sort(available_nodes_.begin(),available_nodes_.end());
}

unsigned int getFingerTableSize(const size_t n) const {
	return ceil(log2(n));
}

int findsuc(size_t node) {
	std::vector<size_t>::iterator it;

	do {
  		it = find (available_nodes_.begin(), available_nodes_.end(), node);
		++node;
		if(node > size_) node = node % size_;

	} while(it == available_nodes_.end());
	return *it;

}

const unsigned int fast2totheN(const unsigned int n) {
	if(n == 0)
		return 1;
	else
		return (2 << (n-1));
}

std::vector<size_t> calculateFingerTable(int node) {
	std::vector<size_t> table;
	table.resize(finger_table_size_);
	for(size_t i = 0; i < finger_table_size_; i++) {
		table[i] = findsuc(node+fast2totheN(i));
	}

	return table;
}

void dotStream(std::ostream& os) {

	os << "graph G {" << std::endl << "graph [rankdir = \"LR\"]" << std::endl;

	for(std::vector<size_t>::iterator iter = available_nodes_.begin(); iter != available_nodes_.end(); iter++) {
		os << *iter << " [color = red]" << std::endl;
		os << "pv" << *iter << " [shape = \"record\" label=\"";
		std::vector<size_t> table = calculateFingerTable(*iter);
		for(std::vector<size_t>::iterator titer = table.begin(); titer != table.end(); titer++) {
			os << *titer;
			if(titer != table.end()-1)
				os << "|";
		}
		os << "\"]" << std::endl;
		os << "pv" << *iter << " --" << *iter << std::endl;
	}

	for (size_t i = 0; i < size_; i++) {
		os << i << " -- ";
	}

	os << "0" << std::endl;

	os << "}" << std::endl;

}
};

int main(int argc, char* argv[]) {
	if(argc == 1) {
		std::cerr << argv[0] << " [size of chord] [first available peer as number]..." << std::endl;
		return -1;
	}

	Chord chord(atoi(argv[1]));
	for(int i = 2; i < argc; i++)
		chord.addNode(atoi(argv[i]));

	chord.dotStream(std::cout);

	return 0;
}

