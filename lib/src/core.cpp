#include "core.h"
#include <exception>
#include <fstream>
#include <cstdlib>
#include <iostream>

void manager_core::Core::set_password(const std::string &password) {
     if (check_password(password))
          sudo_password = password;
     else
          throw manager_core::WrongSudoPassword();
}

bool manager_core::Core::check_password(const std::string &password) {
     if (password.size())
          return 1;
     return 0;
}

void manager_core::Core::set_enabled(bool enabled)
{
     if (get_menu()->get_type() != manager_interface::EntrieType::CheckFlag &&
        get_menu()->get_type() != manager_interface::EntrieType::ValueFlag)
        throw WrongEntryType();
    (static_cast<manager_interface::FlagEntry *> (get_menu()))->set_enabled(enabled);
}

void manager_core::Core::set_value(const std::string &value)
{
    if (get_menu()->get_type() != manager_interface::EntrieType::ValueFlag)
        throw WrongEntryType();
    (static_cast<manager_interface::ValueEntry *> (get_menu()))->set_value(value);
}

bool manager_core::Core::get_enabled()
{
    if (get_menu()->get_type() != manager_interface::EntrieType::CheckFlag &&
        get_menu()->get_type() != manager_interface::EntrieType::ValueFlag)
        throw WrongEntryType();
    return (static_cast<manager_interface::FlagEntry *> (get_menu()))->get_enabled();
}

MI::Entry *make_subentrie(const std::string& line, MI::Entry *parent) {
     auto param_start = line.find('-');
     if (param_start == std::string::npos || (param_start != 0 && line[param_start - 1] != ' ')) 
          return NULL;
     // std::cout << line << std::endl;
     MI::ValueEntry *subentrie = NULL;
     std::string end_symbs = " =.,\n\t[";
     auto param_end = line.find_first_of(end_symbs, param_start);
     if (param_end == std::string::npos) {
          std::cout << line << std::endl;
     }
     else {
          subentrie = new MI::ValueEntry(parent);
          std::string command = line.substr(param_start, param_end - param_start);
          std::string desc = line.substr(param_end);
          subentrie->set_command(command);
          subentrie->set_desc(desc);
     }
     return subentrie;
}

MI::Entry *make_command_entrie(const std::string& command, MI::Entry *parent) {
     if (command.empty())
          return NULL;
     std::string filename = "command_out";
     MI::Entry *entrie = new MI::Entry(parent);
     std::system((command + " --help > " + filename).c_str());
     std::ifstream file(filename);
     std::string command_out;
     std::vector<MI::Entry *> subentries;
     do {
          // file >> command_out;
          std::getline(file, command_out, '\n');
          auto subentrie = make_subentrie(command_out, entrie);
          if (subentrie)
               subentries.push_back(subentrie);
     } while (!file.eof());
     entrie->set_command(command);
     entrie->set_name(command);
     entrie->set_subentries(subentries);
     return entrie;
}

MI::Entry *make_commands_entrie(const std::string &filename, MI::Entry *parent) {
     std::ifstream file("../resources/" + filename);
     if (!file.is_open())
          throw manager_core::FileError();
     std::string command;
     MI::Entry *command_menu = new MI::Entry(parent);
     std::vector<MI::Entry *> subentries;
     do {
          file >> command;
          auto subentrie = make_command_entrie(command, command_menu);
          if (subentrie)
               subentries.push_back(subentrie);
     } while (!file.eof());
     command_menu->set_subentries(subentries);
     command_menu->set_name("Commands");
     return command_menu;
}

manager_interface::Entry *manager_core::parse(const std::string &filename) {
     MI::Entry *menu = new MI::Entry;
     std::vector<MI::Entry *> subentries;
     subentries.push_back(make_commands_entrie(filename, menu));
     subentries.push_back(new MI::LoadProfile(menu));
     subentries.push_back(new MI::SaveProfile(menu));
     menu->set_subentries(subentries);
     return menu;
}

void manager_core::Core::save_profile() {
     if (profile_name.empty())
          throw NoProfileName();
     std::ofstream file("../profiles/" + profile_name);
     if (!file.is_open())
          throw FileError();
     for (auto subentry: main_menu->get_subentries()[0]->get_subentries()) {
          file << subentry->gen_command() << std::endl;
     }
     file.close();

}

void manager_core::Core::load_profile(const std::string &name)
{
     profile_name = name;
}

void manager_core::Core::choose(size_t n) {
     auto new_menu = menu->get_subentry(n - 1);
     if (!new_menu)
          status = Off;
     else {
          menu = new_menu;
        switch (menu->get_type()) {
        case manager_interface::EntrieType::Command:
            status = Show;
            break;
        case manager_interface::EntrieType::Info:
            status = Show;
            break;
        case manager_interface::EntrieType::Menu:
            status = Show;
            break;
        case manager_interface::EntrieType::CheckFlag:
            status = FlagInput;
            break;
        case manager_interface::EntrieType::ValueFlag:
            status = ValueInput;
            break;
        case manager_interface::EntrieType::Load:
            status = Load;
            break;
        case manager_interface::EntrieType::Save:
            status = Save;
            break;
        default:
            throw WrongMenuType();
        }
     }
}

manager_core::Core::Core(manager_core::Core &other) :
     sudo_password(other.sudo_password), 
     profile_name(other.profile_name), 
     menu(other.menu), main_menu(other.menu) {}

manager_core::Core::Core(manager_core::Core &&other) :
     sudo_password(std::move(other.sudo_password)),
     profile_name(std::move(other.profile_name)),
     menu(other.menu), main_menu(other.menu) 
     {other.menu = NULL, other.main_menu = NULL;}