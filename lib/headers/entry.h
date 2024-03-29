#ifndef ENTRIE_H
#define ENTRIE_H

#include <vector>
#include <string>
#include "consts.h"
// #include <iostream> //delete

namespace MCS = manager_consts;

namespace manager_interface
{
    enum EntryType
    {
        CheckFlag,
        ValueFlag,
        Info,
        Menu,
        Command,
        Save,
        Load,
        ChangeName
    };

    class Entry
    {
    private:
        std::vector<Entry *> subentries;
        Entry *parent;
        std::string name;
        std::string description;
        std::string command;
        bool sudo_required = 0;
        bool changed = 0;

    protected:
        void change();

    public:
        Entry() : Entry(NULL){};
        Entry(Entry *parent) : Entry(MCS::default_entry_name, parent) {}
        Entry(const std::string &name, Entry *parent) : parent(parent), name(name) {}
        

        void set_subentries(std::vector<Entry *> &_subentries) { subentries = std::move(_subentries); }
        void set_name(const std::string &_name) { name = _name; }
        void set_desc(const std::string &_desc) { description = _desc; }
        void set_command(const std::string &_command) { command = _command; }
        void set_sudo_req(bool req);
        void set_parent(Entry *_parent) { parent = _parent; }

        const std::vector<Entry *> &get_subentries() const { return subentries; }
        bool get_sudo_req() const { return sudo_required; }
        virtual const std::string &get_name() const { return name; }
        const std::string &get_desc() const { return description; }
        const std::string &get_command() const { return command; }
        virtual std::string get_info() const;
        virtual EntryType get_type() const { return EntryType::Menu; }
        Entry* get_parent() const {return parent;}


        virtual std::string gen_command() const;
        Entry* get_subentry(size_t n);

        // void print(std::ostream& c);

        virtual ~Entry();
    };

    class FlagEntry : public Entry
    {
    protected:
        bool enabled = 0;

    public:
        FlagEntry() : Entry() {};
        FlagEntry(Entry *parent) : Entry(parent) {}

        void set_enabled(bool _enabled);

        bool get_enabled() const { return enabled; }
        virtual EntryType get_type() const override { return EntryType::CheckFlag; }
        const std::string &get_name() const override { return get_command(); }
        std::string get_info() const override;

        virtual std::string gen_command() const override;

        ~FlagEntry(){};
    };

    class ValueEntry : public FlagEntry
    {
    private:
        std::string value;

    public:
        ValueEntry() : FlagEntry() {};
        ValueEntry(Entry *parent) : FlagEntry(parent) {}

        void set_value(const std::string &_value);

        const std::string &get_value() const { return value; }
        EntryType get_type() const override { return EntryType::ValueFlag; }

        std::string gen_command() const override;

        ~ValueEntry(){};
    };

    class SaveProfile : public Entry 
    {
    public:
        SaveProfile() : Entry() {};
        SaveProfile(Entry *parent) : Entry(MCS::save_profile, parent) {};

        EntryType get_type() const override { return EntryType::Save; }
    };

    class LoadProfile : public Entry 
    {
    public:
        LoadProfile() : Entry() {};
        LoadProfile(Entry *parent) : Entry(MCS::load_profile, parent) {};

        EntryType get_type() const override { return EntryType::Load; }
    };

    class ChangeProfileName : public Entry 
    {
    public:
        ChangeProfileName() : Entry() {};
        ChangeProfileName(Entry *parent) : Entry(MCS::change_profile_name, parent) {};

        EntryType get_type() const override { return EntryType::ChangeName; }
    };

    class MenuEntry : public Entry 
    {
    public:
        MenuEntry() : Entry(MCS::menu_name, NULL) {};

        EntryType get_type() const override { return EntryType::Menu; }
        std::string gen_command() const override;
    };

    class WrongOption : std::exception {};
    class WrongEntry : std::exception {};
    class WrongEntryType : std::exception {};
}

#endif