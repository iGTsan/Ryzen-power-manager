#include <iostream>
#include <string>
#include "core.h"
#include "smth.h"

int main() {
	manager_core::Core core(manager_core::parse("to_parse"));
	manager_ui::ConsoleInterface interface(core);
	std::string value;
	size_t choose;
	while (interface.get_status() != manager_core::InterfaceStates::Off) {
		choose = 1;
		switch (interface.get_status()) {
		case manager_core::InterfaceStates::Show:
			interface.show(std::cout);
			std::cin >> choose;
			break;
		case manager_core::InterfaceStates::FlagInput:
			interface.check_input(std::cout, std::cin);
			break;
		case manager_core::InterfaceStates::ValueInput:
			interface.check_input(std::cout, std::cin);
			interface.value_input(std::cout, std::cin);
			break;
		case manager_core::InterfaceStates::Load:
			std::cout << "Profile name: ";
			std::cin >> value;
			interface.load_profile(value);
			break;
		case manager_core::InterfaceStates::Save:
			try {
				interface.save_profile();
			} catch (manager_core::NoProfileName& err) {
				std::cout << "Profile name: ";
				std::cin >> value;
				interface.set_profile_name(value);
				interface.save_profile();
			}
			break;
		default:
			break;
		}
		interface.choose(choose);
	}
}