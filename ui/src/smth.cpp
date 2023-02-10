#include "smth.h"

void manager_ui::ConsoleInterface::show(std::ostream &ostream) 
{
    int num = 0;
    for (auto subentry: get_menu()->get_subentries())
        ostream << ++num << ". " << subentry->get_info() << std::endl;
    ostream << ++num << ". Exit" << std::endl;
    
}

void manager_ui::ConsoleInterface::check_input(std::ostream &ostream, std::istream &istream)
{
    std::string value;
    ostream << "Enable? (y/n): ";
    istream  >> value;
    if (value == "y") 
        set_enabled(1);
    else
        set_enabled(0);
}

void manager_ui::ConsoleInterface::value_input(std::ostream &ostream, std::istream &istream)
{
    if (!get_enabled())
        return;
    std::string value;
    ostream << "Value: ";
    istream >> value;
    set_value(value);
}