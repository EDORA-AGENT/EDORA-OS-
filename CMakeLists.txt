cmake_minimum_required(VERSION 3.16)

project(EDORA_OS VERSION 2.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(EDORA-OS
    main.cpp
    login/login.cpp
    kernel/kernel.cpp
    shell/shell.cpp
    filesystem/filesystem.cpp
    drivers/driver.cpp
    commands/basic.cpp
    commands/file.cpp
    commands/system.cpp
    commands/security.cpp
    apps/notepad.cpp
    apps/binary.cpp
    apps/edo.cpp
    apps/game.cpp
    apps/calculator.cpp
    apps/todo.cpp
    apps/system_monitor.cpp
    apps/debug.cpp
    network/ping.cpp
)

target_include_directories(EDORA-OS PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)