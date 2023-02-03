#include <iostream>
#include "entrie.h"
#include "core.h"

int main() {
	std::cout << "Hi" << std::endl;
	manager_interface::Entry entr;
	auto vec = entr.get_subentries();
	auto menu = manager_core::parse("to_parse");
	delete menu;
	// menu->print(std::cout);
}
