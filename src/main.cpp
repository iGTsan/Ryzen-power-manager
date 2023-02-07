#include <iostream>
#include "core.h"

int main() {
	std::cout << "Hi" << std::endl;
	manager_interface::Entry entr;
	auto vec = entr.get_subentries();
	auto menu = manager_core::parse("to_parse");
	manager_core::Core core(menu);
	core.set_profilename("1");
	core.save_profile();

	// menu->print(std::cout);
}
