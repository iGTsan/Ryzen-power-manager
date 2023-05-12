#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "core.h"

TEST(CoreConstructor, NULLMenuConstructor) {
    ASSERT_NO_THROW(manager_core::Core core(NULL));
}

TEST(CoreConstructor, SpecifiedMenuConstructor) {
    auto entry = new manager_interface::Entry;

    ASSERT_NO_THROW(manager_core::Core core(entry));
}

TEST(CoreConstructor, MoveConstructor) {
    auto entry = new manager_interface::Entry;
    manager_core::Core old_core(entry);

    ASSERT_NO_THROW(manager_core::Core core(std::move(old_core)));
}