if(WIN32 OR MSVC)
    set(SECP256K1_USE_CMAKE 1)
    include(CheckTypeSize) 
    check_type_size("__int128" SIZEOF_INT128 BUILTIN_TYPES_ONLY)
    if(SIZEOF_INT128)
        add_definitions(-D__HAS_INT128__=1)
    endif()
endif()

include(cmake/modules/MakeIncludesLink.cmake)
include(cmake/cryptopp.cmake)
include(cmake/secp256k1.cmake)
include(cmake/libscrypt.cmake)
include(cmake/core.cmake)


add_dependencies(ethcrypto-core secp256k1)
add_dependencies(ethcrypto-core scrypt)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_CURRENT_BINARY_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_BINARY_DIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG "${CMAKE_CURRENT_BINARY_DIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_BINARY_DIR}")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${CMAKE_CURRENT_BINARY_DIR}")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_BINARY_DIR}")
add_library(ethcrypto STATIC ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp) 

target_include_directories(ethcrypto-core PUBLIC ${LIBSCRYPT_INCLUDE_DIRS})
target_include_directories(ethcrypto-core PUBLIC ${SECP256K1_INCLUDE_DIRS})

add_dependencies(ethcrypto secp256k1)
add_dependencies(ethcrypto cryptopp)
add_dependencies(ethcrypto ethcrypto-core)




if (WIN32 AND NOT MINGW)
    set_property (TARGET ethcrypto APPEND PROPERTY STATIC_LIBRARY_FLAGS "\"${CMAKE_CURRENT_BINARY_DIR}\\lib.obj\\secp256k1.lib\" \"${CMAKE_CURRENT_BINARY_DIR}\\lib.obj\\scrypt.lib\" \"${CMAKE_CURRENT_BINARY_DIR}\\lib.obj\\ethcrypto-core.lib\"")
elseif (${CMAKE_GENERATOR} STREQUAL "Xcode")
    set_property (TARGET ethcrypto APPEND PROPERTY STATIC_LIBRARY_FLAGS "${CMAKE_CURRENT_BINARY_DIR}/lib.obj/secp256k1.a ${CMAKE_CURRENT_BINARY_DIR}/lib.obj/libscrypt.a ${CMAKE_CURRENT_BINARY_DIR}/lib.obj/ethcrypto-core.a")
else()
    set(LIB_OBJ_DIR ${CMAKE_CURRENT_BINARY_DIR}/lib.obj/obj)
    make_directory (${LIB_OBJ_DIR})

    ADD_CUSTOM_COMMAND(TARGET ethcrypto
          POST_BUILD
          COMMAND echo "packing libethcrypto.a"
          COMMAND ${CMAKE_AR} x ${CMAKE_CURRENT_BINARY_DIR}/lib.obj/libcryptopp.a WORKING_DIRECTORY ${LIB_OBJ_DIR}
          COMMAND ${CMAKE_AR} x ${CMAKE_CURRENT_BINARY_DIR}/lib.obj/libsecp256k1.a WORKING_DIRECTORY ${LIB_OBJ_DIR}
          COMMAND ${CMAKE_AR} x ${CMAKE_CURRENT_BINARY_DIR}/lib.obj/libscrypt.a WORKING_DIRECTORY ${LIB_OBJ_DIR}
          COMMAND ${CMAKE_AR} x ${CMAKE_CURRENT_BINARY_DIR}/lib.obj/libethcrypto-core.a WORKING_DIRECTORY ${LIB_OBJ_DIR}
          COMMAND ${CMAKE_AR} rcs ${CMAKE_CURRENT_BINARY_DIR}/libethcrypto.a ${LIB_OBJ_DIR}/*.o
          COMMAND rm -fr ${LIB_OBJ_DIR}
    )
endif ()




#if(NOT SKIP_LIBRARY_INSTALL)
#    install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/include DESTINATION include OPTIONAL)
#    install (TARGETS ethcrypto ARCHIVE DESTINATION lib LIBRARY DESTINATION lib RUNTIME DESTINATION bin OPTIONAL)
#endif()

MakeIncludesLink()


set(ETHCRYPTO_INCLUDE_DIR "${CMAKE_CURRENT_BINARY_DIR}/include" FORCE)
set(ETHCRYPTO_INCLUDE_DIRS ${ETHCRYPTO_INCLUDE_DIR} ${LIBSCRYPT_INCLUDE_DIRS} ${SECP256K1_INCLUDE_DIRS} ${CRYPTOPP_INCLUDE_DIRS} ${ETHCRYPTO_CONFIG_INCLUDE_DIR}  CACHE STRING "" FORCE)
set(ETHCRYPTO_LIBRARY "ethcrypto" CACHE STRING "" FORCE)
set(ETHCRYPTO_LIBRARIES ${ETHCRYPTO_LIBRARY}  CACHE STRING "" FORCE)

