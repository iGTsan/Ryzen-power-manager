#include "smth.h"

void manager_ui::ConsoleInterface::show_entries(std::ostream &c)
{
    int num = 0;
    for (auto subentry: core.get_menu()->get_subentries())
        c << ++num << ". " << subentry->get_info() << std::endl;
    c << ++num << ". Exit" << std::endl;
}

void manager_ui::ConsoleInterface::choose(size_t n)
{
    core.choose(n);
}