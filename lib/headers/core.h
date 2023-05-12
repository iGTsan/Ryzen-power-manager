#ifndef CORE_H
#define CORE_H

#include <string>
#include <vector>
#include <exception>
#include "entry.h"
#include <iostream>

namespace MI = manager_interface;

namespace manager_core {

    enum CoreStates 
    {
        Show, 
        ValueInput, 
        FlagInput, 
        Off,
        Save,
        Load,
        ChangeName
    };

    class Core {
    private:
        CoreStates status;
        std::string sudo_password;
        std::string profile_name;
        MI::Entry *menu;
        MI::Entry *main_menu;

        bool check_password(const std::string& password);

    protected:
        void set_enabled(bool enabled);
        void set_value(const std::string& value);
        bool get_enabled();
        void enable_command(const std::string& command);
        void enable_flags(const std::string& flags);

    public:
        Core(MI::Entry *menu) : status(Show), menu(menu), main_menu(menu) {};
        Core(Core&& other);

        Core& operator = (Core&& other);

        void set_password(const std::string& password);
        void set_profile_name(const std::string& name) { profile_name = name; }

        void save_profile();
        void load_profile(const std::string& name);

        MI::Entry *get_menu() {return menu;}
        CoreStates get_status() const {return status;}

        void choose(size_t n);

        ~Core() {delete menu;}
    };

    class WrongSudoPassword : std::exception {};
    class FileError : std::exception {};
    class NoProfileName : std::exception {};
    class WrongMenuType : std::exception {};
    class CantOpenFile : FileError {};
    class WrongFlagName : FileError {};

    MI::Entry *parse(const std::string& filename);
}

#endif