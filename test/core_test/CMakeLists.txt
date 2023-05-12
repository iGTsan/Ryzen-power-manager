set(LIBRARIES gtest gmock pthread ${LIBRARY})

set(MYLIBRARY ../../lib/)

include_directories(${MYLIBRARY}/headers/)
include(GoogleTest)

SET(TARGET core_test)
SET(TARGET_SRC test.cpp)

# Исполняемый файл теста - это обычная исполняемая цель сборки
add_executable(${TARGET} ${TARGET_SRC})
target_link_libraries(${TARGET} ${LIBRARIES})

# Регистрируем исполняемый файл в CMake как набор тестов.
#  можно назначить тесту особое имя, но проще использовать имя исполняемого файла теста.
gtest_discover_tests(${TARGET})