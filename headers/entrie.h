#ifndef ENTRIE_H
#define ENTRIE_H

#include <vector>
#include <string>
// #include <iostream> //delete

namespace manager_interface
{
    enum EntrieType {
        CheckFlag,  NumberFlag, Info, Menu, Command
    };

    class Entrie
    {
    private:
        std::vector<Entrie *> subentries;
        std::string name;
        std::string description;
        std::string command;
        bool sudo_required;

    public:
        Entrie(){};
        Entrie(std::string &name, bool sudo_required = 0) : name(std::move(name)), sudo_required(sudo_required) {}
        Entrie(std::vector<Entrie *> &subentries, std::string &name, bool sudo_required = 0) : 
            subentries(std::move(subentries)), name(std::move(name)), sudo_required(sudo_required) {}

        void set_subentries(std::vector<Entrie *> &_subentries) { subentries = std::move(_subentries); }
        void set_name(std::string &_name) { name = std::move(_name); }
        void set_desc(std::string &_desc) { description = std::move(_desc); }
        void set_command(std::string &_command) { command = std::move(_command); }
        void set_sudo_req(bool req) { sudo_required = req; }

        const std::vector<Entrie *> &get_subentries() const { return subentries; }
        bool get_sudo_req() const { return sudo_required; }
        const std::string &get_name() const { return name; }
        const std::string &get_desc() const { return description; }
        const std::string &get_command() const { return command; }
        virtual EntrieType get_type() const { return EntrieType::Menu; }

        // void print(std::ostream& c);

        virtual ~Entrie();
    };
}

#endif