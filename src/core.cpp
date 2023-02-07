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
          int tmp = std::rand() % 100;
          std::cout << tmp << std::endl;
          if (tmp % 10 == 0)
               subentrie->set_value("value");
          std::string command = line.substr(param_start, param_end - param_start);
          std::string desc = line.substr(param_end);
          subentrie->set_command(command);
          subentrie->set_desc(desc);
     }
     return subentrie;
}

MI::Entry *make_entrie(const std::string& command, MI::Entry *parent) {
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
     entrie->set_subentries(subentries);
     return entrie;
}

manager_interface::Entry *manager_core::parse(const std::string &filename) {
     srand(0);
     std::ifstream file("../resources/" + filename);
     if (!file.is_open())
          throw FileError();
     std::string command;
     MI::Entry *menu = new MI::Entry;
     std::vector<MI::Entry *> subentries;
     do {
          file >> command;
          auto subentrie = make_entrie(command, menu);
          if (subentrie)
               subentries.push_back(subentrie);
     } while (!file.eof());
     // subentries.pop_back();
     menu->set_subentries(subentries);
     menu->set_name("Menu");
     return menu;
}

void manager_core::Core::save_profile() {
     if (profile_name.empty())
          throw NoProfileName();
     std::ofstream file("../profiles/" + profile_name);
     if (!file.is_open())
          throw FileError();
     for (auto subentry: menu->get_subentries()) {
          file << subentry->gen_command() << std::endl;
     }

}
