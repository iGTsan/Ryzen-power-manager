#include "core.h"
#include <iostream>

namespace MI = manager_interface;
namespace MC = manager_core;

namespace manager_ui {
    class ConsoleInterface {
    private:
        MC::Core core;
    public:
        ConsoleInterface(MC::Core& core) : core(std::move(core)) {}
        const MC::Core& get_core() const {return core;}
        
        void show_entries(std::ostream& c);
        void choose(size_t n);

        bool is_valid() {return core.is_valid();}

        // ~ConsoleInterface() {std::cout << "ConsoleInterface destructor" << std::endl;}
    };
}