#include <iostream>
#include "entrie.h"

int main() {
	std::cout << "Hi" << std::endl;
	manager_interface::Entrie entr;
	auto vec = entr.get_subentries();
	
}
