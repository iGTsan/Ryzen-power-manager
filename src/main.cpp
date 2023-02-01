#include <iostream>
#include "entrie.h"
#include "core.h"

int main() {
	std::cout << "Hi" << std::endl;
	manager_interface::Entrie entr;
	auto vec = entr.get_subentries();
	auto menu = manager_core::parse("to_parse");
	menu->print(std::cout);
}
