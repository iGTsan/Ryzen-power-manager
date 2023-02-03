#ifndef ENTRIE_H
#define ENTRIE_H

#include <vector>
#include <string>
// #include <iostream> //delete

namespace manager_interface
{
    enum EntrieType {
        CheckFlag,  ValueFlag, Info, Menu, Command
    };

    class Entry
    {
    private:
        std::vector<Entry *> subentries;
        std::string name;
        std::string description;
        std::string command;
        bool sudo_required;

    public:
        Entry() : sudo_required(0) {};
        Entry(std::string &name, bool sudo_required = 0) : name(std::move(name)), sudo_required(sudo_required) {}
        Entry(std::vector<Entry *> &subentries, std::string &name, bool sudo_required = 0) : 
            subentries(std::move(subentries)), name(std::move(name)), sudo_required(sudo_required) {}

        void set_subentries(std::vector<Entry *> &_subentries) { subentries = std::move(_subentries); }
        void set_name(std::string &_name) { name = std::move(_name); }
        void set_desc(std::string &_desc) { description = std::move(_desc); }
        void set_command(std::string &_command) { command = std::move(_command); }
        void set_sudo_req(bool req) { sudo_required = req; }

        const std::vector<Entry *> &get_subentries() const { return subentries; }
        bool get_sudo_req() const { return sudo_required; }
        const std::string &get_name() const { return name; }
        const std::string &get_desc() const { return description; }
        const std::string &get_command() const { return command; }
        virtual EntrieType get_type() const { return EntrieType::Menu; }

        // void print(std::ostream& c);

        virtual ~Entry();
    };

    class FlagEntry : public Entry
    {
    private:
        bool active;
    public:
        FlagEntry() : Entry(), active(0) {};

        void set_active(bool _active) {active = _active;}

        bool get_active() const {return active;}
        virtual EntrieType get_type() const override {return EntrieType::CheckFlag;}

        ~FlagEntry() {};
    };    

    class ValueEntry : public FlagEntry
    {
    private:
        int value;
    public:
        ValueEntry() : FlagEntry(), value(0) {};

        void set_value(int _value) {value = _value;}

        bool get_active() const {return value;}
        EntrieType get_type() const override {return EntrieType::ValueFlag;}

        ~ValueEntry() {};
    };    
}

#endif