#include "entry.h"

manager_interface::Entry::~Entry() {
    for (auto subentry: subentries)
        delete subentry;
}

std::string manager_interface::Entry::gen_command() const {
    std::string res;
    if (changed) {
        res = command;
        for (auto subentry: subentries)
            res += subentry->gen_command();
    }
    return res;
}

std::string manager_interface::FlagEntry::gen_command() const {
    std::string res;
    if (enabled)
        res = ' ' + get_command();
    return res;
}

std::string manager_interface::ValueEntry::gen_command() const {
    std::string res;
    if (enabled)
        res = FlagEntry::gen_command() + ' ' + value;
    return res;
}

void manager_interface::Entry::change() {
    changed = 1;
    if (parent)
        parent->change();
}

void manager_interface::ValueEntry::set_value(const std::string &_value) {
    set_enabled(1);
    value = _value;
}

void manager_interface::FlagEntry::set_enabled(bool _enabled) {
    enabled = _enabled;
    change();
}