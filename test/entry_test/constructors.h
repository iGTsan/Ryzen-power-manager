#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "entry.h"

std::string ENTRY_NAME = "Some name";

TEST(EntryConstructor, EmptyConstructor) {
    ASSERT_NO_THROW(manager_interface::Entry entry);
}

TEST(EntryConstructor, ParentConstructor) {
    manager_interface::Entry parent_entry;
    
    ASSERT_NO_THROW(manager_interface::Entry entry(&parent_entry));
}

TEST(EntryConstructor, ParentAndNameConstructor) {
    manager_interface::Entry parent_entry;

    ASSERT_NO_THROW(manager_interface::Entry entry(ENTRY_NAME, &parent_entry));
}

TEST(EntryConstructor, GetName) {
    manager_interface::Entry empty_entry;
    manager_interface::Entry named_entry(ENTRY_NAME, &empty_entry);

    ASSERT_EQ(empty_entry.get_name(), manager_consts::default_entry_name);
    ASSERT_EQ(named_entry.get_name(), ENTRY_NAME);
}
