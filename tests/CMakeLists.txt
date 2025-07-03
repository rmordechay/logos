enable_testing()

add_executable(lgs_tests
    main.cpp
    analysis/sema/SemaTest.cpp
)

target_precompile_headers(lgs_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../include/pch.h)

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    target_link_libraries(lgs_tests PRIVATE
        lib
        ${CMAKE_CURRENT_SOURCE_DIR}/../external/lib/linux/libgtest.a
        ${CMAKE_CURRENT_SOURCE_DIR}/../external/lib/linux/libgmock.a
        ${CMAKE_CURRENT_SOURCE_DIR}/../external/lib/linux/libgtest_main.a
    )
elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    target_link_libraries(lgs_tests PRIVATE
        lib
        ${CMAKE_CURRENT_SOURCE_DIR}/../external/lib/macos/libgtest.a
        ${CMAKE_CURRENT_SOURCE_DIR}/../external/lib/macos/libgmock.a
        ${CMAKE_CURRENT_SOURCE_DIR}/../external/lib/macos/libgtest_main.a
    )
endif()
