#include <iostream>
#include "core.h"
#include "smth.h"

int main() {
	manager_core::Core core(manager_core::parse("to_parse"));
	manager_ui::ConsoleInterface interface(core);
	size_t choose;
	while (interface.is_valid()) {
		interface.show_entries(std::cout);
		std::cin >> choose;
		interface.choose(choose);
	}
}