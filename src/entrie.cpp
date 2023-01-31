#include "entrie.h"

const std::vector<manager_interface::Entrie *> &manager_interface::Entrie::get_subentries() const {
    return subentries;
}

manager_interface::Entrie::Entrie() {

}
