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
     if (get_menu()->get_type() != manager_interface::EntryType::CheckFlag &&
        get_menu()->get_type() != manager_interface::EntryType::ValueFlag)
        throw MI::WrongEntryType();
    (static_cast<manager_interface::FlagEntry *> (get_menu()))->set_enabled(enabled);
}

void manager_core::Core::set_value(const std::string &value)
{
    if (get_menu()->get_type() != manager_interface::EntryType::ValueFlag)
        throw MI::WrongEntryType();
    (static_cast<manager_interface::ValueEntry *> (get_menu()))->set_value(value);
}

bool manager_core::Core::get_enabled()
{
    if (get_menu()->get_type() != manager_interface::EntryType::CheckFlag &&
        get_menu()->get_type() != manager_interface::EntryType::ValueFlag)
        throw MI::WrongEntryType();
    return (static_cast<manager_interface::FlagEntry *> (get_menu()))->get_enabled();
}

MI::Entry *make_subentrie(const std::string& line, MI::Entry *parent) {
     auto param_start = line.find('-');
     if (param_start == std::string::npos || (param_start != 0 && line[param_start - 1] != ' ')) 
          return NULL;
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
     std::ifstream file(MCS::resources_path + filename);
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
     MI::Entry *menu = new MI::MenuEntry;
     std::vector<MI::Entry *> subentries;
     subentries.push_back(make_commands_entrie(filename, menu));
     subentries.push_back(new MI::LoadProfile(menu));
     subentries.push_back(new MI::SaveProfile(menu));
     subentries.push_back(new MI::ChangeProfileName(menu));
     menu->set_subentries(subentries);
     return menu;
}

void manager_core::Core::save_profile() {
     if (profile_name.empty())
          throw NoProfileName();
     std::ofstream file(manager_consts::profiles_path + profile_name);
     if (!file.is_open())
          throw CantOpenFile();
     file << main_menu->gen_command();
     file.close();

}

void string_trim(std::string &str) {
     const std::string delimeters = " \t\n";
     auto left = str.find_first_not_of(delimeters);
     auto right = str.find_first_of(delimeters, left);
     if (right == std::string::npos)
          right = str.size();
     str = str.substr(left, right - left);
}

void manager_core::Core::enable_flags(const std::string &flags) {
     auto flag_all_start = flags.find_first_not_of(" -");
     auto flag_curr_end = flags.find(" -", flag_all_start);
     while (flag_all_start != std::string::npos) {
          auto value_start = flags.find(' ', flag_all_start);
          if (value_start == std::string::npos)
               value_start = flags.size();
          std::string flag_name = flags.substr(flag_all_start - 1, value_start - flag_all_start + 1);
          string_trim(flag_name);
          if (flag_curr_end == std::string::npos)
               flag_curr_end = flags.size();
          std::string value = flags.substr(value_start, flag_curr_end - value_start);
          string_trim(value);
          for (auto subentry: menu->get_subentries())
               if (subentry->get_name() == flag_name) {
                    if (subentry->get_type() == manager_interface::EntryType::CheckFlag) {
                         dynamic_cast<manager_interface::FlagEntry *>(subentry)->set_enabled(1);
                    } else if (subentry->get_type() == manager_interface::EntryType::ValueFlag) {
                         dynamic_cast<manager_interface::ValueEntry *>(subentry)->set_value(value);
                    }
               }
          flag_all_start = flags.find_first_not_of(" -", flag_curr_end);
          flag_curr_end = flags.find(" -", flag_all_start);
     }
}

void manager_core::Core::enable_command(const std::string &command) {
     auto name_end = command.find(' ');
     if (name_end == std::string::npos)
          return;
     auto name = command.substr(0, name_end);
     auto flags_start = command.find('-', name_end);
     auto flags = command.substr(flags_start);
     menu = main_menu->get_subentries()[0];
     for (auto subentry: menu->get_subentries())
          if (subentry->get_name() == name) {
               menu = subentry;
               enable_flags(flags);
               return;
          }
     throw MI::WrongEntry();
}

void manager_core::Core::load_profile(const std::string &name) {
     std::ifstream file(MCS::profiles_path + name);
     if (!file.is_open())
          throw FileError();
     std::string command;
      do {
          std::getline(file, command, '\n');
          enable_command(command);
     } while (!file.eof());
     profile_name = name;
     menu = main_menu;
}

void manager_core::Core::choose(size_t n) {
     auto new_menu = menu->get_subentry(n - 1);
     if (!new_menu)
          status = Off;
     else {
          menu = new_menu;
          switch (menu->get_type()) {
          case manager_interface::EntryType::Command:
               status = Show;
               break;
          case manager_interface::EntryType::Info:
               status = Show;
               break;
          case manager_interface::EntryType::Menu:
               status = Show;
               break;
          case manager_interface::EntryType::CheckFlag:
               status = FlagInput;
               break;
          case manager_interface::EntryType::ValueFlag:
               status = ValueInput;
               break;
          case manager_interface::EntryType::Load:
               status = Load;
               break;
          case manager_interface::EntryType::Save:
               status = Save;
               break;
          case manager_interface::EntryType::ChangeName:
               status = ChangeName;
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