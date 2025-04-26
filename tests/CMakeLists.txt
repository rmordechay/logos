enable_testing()

add_executable(lgs_tests
    main.cpp
)

target_include_directories(lgs_tests PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../external/include
    ${CMAKE_CURRENT_SOURCE_DIR}
)

if(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    target_link_libraries(lgs_tests PRIVATE
        lib
        ${CMAKE_CURRENT_SOURCE_DIR}/../external/lib/macos/libgtest.a
        ${CMAKE_CURRENT_SOURCE_DIR}/../external/lib/macos/libgmock.a
        ${CMAKE_CURRENT_SOURCE_DIR}/../external/lib/macos/libgtest_main.a
        ${CMAKE_CURRENT_SOURCE_DIR}/../external/lib/macos/libLLVM.dylib
        ${CMAKE_CURRENT_SOURCE_DIR}/../external/lib/macos/liblldCommon.dylib
        ${CMAKE_CURRENT_SOURCE_DIR}/../external/lib/macos/liblldMachO.dylib
        ${CMAKE_CURRENT_SOURCE_DIR}/../external/lib/macos/libantlr4-runtime.a
    )
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    target_link_libraries(lgs_tests PRIVATE
        lib
        ${CMAKE_CURRENT_SOURCE_DIR}/../external/lib/linux/libgtest.a
        ${CMAKE_CURRENT_SOURCE_DIR}/../external/lib/linux/libgtest_main.a
        ${CMAKE_CURRENT_SOURCE_DIR}/../external/lib/linux/libantlr4-runtime.so
        ${CMAKE_CURRENT_SOURCE_DIR}/../external/lib/linux/libLLVM.so
    )
endif()
