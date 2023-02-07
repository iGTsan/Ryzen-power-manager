#ifndef ENTRIE_H
#define ENTRIE_H

#include <vector>
#include <string>
// #include <iostream> //delete

namespace manager_interface
{
    enum EntrieType
    {
        CheckFlag,
        ValueFlag,
        Info,
        Menu,
        Command
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
        Entry(Entry *parent) : Entry("", parent) {}
        Entry(const std::string &name, Entry *parent) : parent(parent), name(name) {}
        

        void set_subentries(std::vector<Entry *> &_subentries) { subentries = std::move(_subentries); }
        void set_name(const std::string &_name) { name = _name; }
        void set_desc(const std::string &_desc) { description = _desc; }
        void set_command(const std::string &_command) { command = _command; }
        void set_sudo_req(bool req) { sudo_required = req; }

        const std::vector<Entry *> &get_subentries() const { return subentries; }
        bool get_sudo_req() const { return sudo_required; }
        const std::string &get_name() const { return name; }
        const std::string &get_desc() const { return description; }
        const std::string &get_command() const { return command; }
        virtual EntrieType get_type() const { return EntrieType::Menu; }

        virtual std::string gen_command() const;

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
        virtual EntrieType get_type() const override { return EntrieType::CheckFlag; }

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
        EntrieType get_type() const override { return EntrieType::ValueFlag; }

        std::string gen_command() const override;

        ~ValueEntry(){};
    };
}

#endif