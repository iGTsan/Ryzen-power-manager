#ifndef ENTRIE_H
#define ENTRIE_H

#include <vector>
#include <string>

namespace manager_interface {
    class Entrie {
    private:
        std::vector<Entrie *> subentries;
        std::string name;
        // bool sudo_required;
    public:
        Entrie();
        const std::vector<Entrie *>& get_subentries() const;
    };
}

#endif