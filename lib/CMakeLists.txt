file(GLOB SOURCES src/*.cpp)
file(GLOB HEADERS /headers/*.h)

add_library(${LIBRARY} STATIC ${SOURCES} ${HEADERS})


