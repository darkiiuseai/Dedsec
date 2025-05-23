cmake_minimum_required(VERSION 3.10)
project(dedsec-tool)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Sources
set(SOURCES
    src/main.cpp
    src/console_color.cpp
    src/animation.cpp
    src/system_utils.cpp
    src/network_tools.cpp
    src/security_tools.cpp
    src/dev_tools.cpp
    src/utils.cpp
    src/dedsec_tool.cpp
)

# Executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE src)

# Compiler-specific options
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4 /utf-8)
    target_compile_definitions(${PROJECT_NAME} PRIVATE _CRT_SECURE_NO_WARNINGS)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic)
endif()

# Platform-specific libraries
if(WIN32)
    target_link_libraries(${PROJECT_NAME} ws2_32 iphlpapi psapi winmm)
else()
    target_link_libraries(${PROJECT_NAME} pthread)
endif()

# Set output directory
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# Install target
install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION bin
)
