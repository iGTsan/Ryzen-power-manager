#include "entrie.h"

manager_interface::Entry::~Entry() {
    for (auto subentrie: subentries)
        delete subentrie;
}

// void manager_interface::Entrie::print(std::ostream &c) {
//     c << "Name: " << name << std::endl;
//     c << "Command: " << command << std::endl;
//     c << "Desc: " << description << std::endl;
//     for (auto e: subentries)
//         e->print(c);
// }