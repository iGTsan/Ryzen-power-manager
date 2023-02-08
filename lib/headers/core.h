#ifndef CORE_H
#define CORE_H

#include <string>
#include <vector>
#include <exception>
#include "entry.h"
#include <iostream>

namespace MI = manager_interface;

namespace manager_core {
    class Core {
    private:
        std::string sudo_password;
        std::string profile_name;
        MI::Entry *menu;
        bool valid = true;

        bool check_password(const std::string& password);

    public:
        Core() {};
        Core(MI::Entry *menu) : menu(menu) {};
        Core(Core& other);
        Core(Core&& other);

        void set_password(const std::string& password);
        void set_profilename(const std::string& name) { profile_name = name; }

        void save_profile();
        void load_profile(const std::string& name);

        MI::Entry *get_menu() {return menu;}
        void choose(size_t n);
        bool is_valid() const {return valid;}

        ~Core() {delete menu;}
    };

    class WrongSudoPassword : std::exception {};
    class FileError : std::exception {};
    class NoProfileName : std::exception {};

    MI::Entry *parse(const std::string& filename);
}

#endif