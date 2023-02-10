#include "core.h"
#include <iostream>
#include <stdexcept>

namespace MI = manager_interface;
namespace MC = manager_core;

namespace manager_ui {

    class ConsoleInterface : public MC::Core {
    public:
        ConsoleInterface(MC::Core& core) : Core(std::move(core)) {}
        void show(std::ostream& ostream);
        void check_input(std::ostream& ostream, std::istream& istream);
        void value_input(std::ostream& ostream, std::istream& istream);
        // ~ConsoleInterface() {std::cout << "ConsoleInterface destructor" << std::endl;}
    };
}