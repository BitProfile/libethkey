find_package(Boost COMPONENTS system REQUIRED)

#add_definitions(-D__DEBUG__)

include_directories(${CMAKE_BINARY_DIR}/include)


file(GLOB SOURCES 
    "src/*.cpp"
    "src/external/*.cpp"
    "src/detail/*.cpp"
    "src/serialization/*.cpp"
    "src/serialization/detail/*.cpp"
    "src/encoding/*.cpp"
    "src/encoding/detail/*.cpp"
)



file(GLOB HEADERS RELATIVE ${CMAKE_SOURCE_DIR}/src
    "src/*.hpp"
    "src/*.ipp"
    "src/external/*.h"
    "src/detail/*.hpp"
    "src/detail/*.ipp"
    "src/serialization/*.hpp"
    "src/serialization/*.ipp"
    "src/serialization/detail/*.hpp"
    "src/serialization/detail/*.ipp"
    "src/encoding/*.hpp"
    "src/encoding/*.ipp"
    "src/encoding/detail/*.hpp"
    "src/encoding/detail/*.ipp"
)


add_library(bitcrypto-dummy STATIC ${CMAKE_SOURCE_DIR}/src/main.cpp)



add_library(bitcrypto-core STATIC ${SOURCES})
add_dependencies(bitcrypto-core libsecp256k1 bitcrypto-dummy)


#add_custom_command(
#    TARGET bitcrypto-core
#    PRE_BUILD
#    COMMAND ${CMAKE_COMMAND} ARGS -E make_directory ${CMAKE_BINARY_DIR}/include/bitcrypto/external
#)

foreach(HEADER ${HEADERS})
    add_custom_command(
        TARGET bitcrypto-dummy
        PRE_BUILD
        COMMAND ${CMAKE_COMMAND}
        ARGS -E copy ${CMAKE_SOURCE_DIR}/src/${HEADER} ${CMAKE_BINARY_DIR}/include/bitcrypto/${HEADER}
)
endforeach(HEADER )


