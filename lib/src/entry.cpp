#include "entry.h"

manager_interface::Entry::~Entry() {
    for (auto subentry: subentries)
        delete subentry;
}

void manager_interface::Entry::set_sudo_req(bool req)
{
    if (req == 1)
        for (auto subentry: subentries)
            subentry->set_sudo_req(req);
    sudo_required = req;
}

std::string manager_interface::Entry::get_info() const
{
    std::string res = get_name();
    return res;
}

std::string manager_interface::Entry::gen_command() const
{
    std::string res;
    if (changed) {
        res = command;
        for (auto subentry: subentries)
            res += subentry->gen_command();
    }
    return res;
}

manager_interface::Entry *manager_interface::Entry::get_subentry(size_t n)
{
    if (n == subentries.size())
        return parent;
    if (n < 0 || n > subentries.size())
        throw WrongOption();
    return subentries[n];
}

std::string manager_interface::FlagEntry::get_info() const
{
    std::string res = get_name() + get_desc();
    return res;
}

std::string manager_interface::FlagEntry::gen_command() const
{
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

std::string manager_interface::MenuEntry::gen_command() const
{
    std::string res;
    for (auto subentry: get_subentries()[0]->get_subentries())
        res += subentry->gen_command() + '\n';
    return res;
}
