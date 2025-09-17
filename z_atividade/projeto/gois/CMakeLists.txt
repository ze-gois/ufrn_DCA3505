cmake_minimum_required(VERSION 3.10)

set(PROJECT_NAME lockdep)

project(${PROJECT_NAME} VERSION 1.0)

set(CMAKE_C_COMPILER /usr/bin/clang)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

set(COMPILE_OPTIONS
    "-Wall"
    "-Werror"
    "-Wextra"
    "-fsanitize=address,undefined"
    "-fno-omit-frame-pointer"
    "-g3")

set(LINK_OPTIONS "-fsanitize=address,undefined")

# Check for libelf availability
find_package(PkgConfig)
if(PKG_CONFIG_FOUND)
    pkg_check_modules(LIBELF libelf)
    pkg_check_modules(RAYLIB REQUIRED raylib)
endif()

# Add ptrace support
set(PTRACE_COMPILE_OPTIONS
    ${COMPILE_OPTIONS}
    "-DUSE_PTRACE")

# Add libelf support if available
if(LIBELF_FOUND)
    set(PTRACE_COMPILE_OPTIONS ${PTRACE_COMPILE_OPTIONS} "-DHAVE_LIBELF")
    message(STATUS "Found libelf: enhanced symbol resolution enabled")
else()
    message(STATUS "libelf not found: using fallback symbol resolution")
endif()

# Graph library sources
file(GLOB GRAPH_SOURCES
    "src/graph/graph.c"
)

# Library interposition sources
file(GLOB VISUALIZATION_SOURCES
    "src/graph/visualizer.c"
)
# Core lockdep library sources
file(GLOB LOCKDEP_SOURCES
    "src/lockdep/lockdep_core.c"
)

# Library interposition sources
file(GLOB INTERPOSE_SOURCES
    "src/interpose/*.c"
    "src/lockdep/*.c"
)

# Ptrace-based sources (excluding test_program.c)
file(GLOB PTRACE_SOURCES
    "src/ptrace/main.c"
    "src/ptrace/ptrace_attach.c"
    "src/ptrace/syscall_intercept.c"
    "src/ptrace/pthread_structures.c"
    "src/ptrace/lock_tracker.c"
    "src/ptrace/backtrace.c"
)

# Test program sources
file(GLOB TEST_SOURCES "src/tests/*.c")

# Include directories
include_directories(src/include)

add_library(graph SHARED ${GRAPH_SOURCES})
target_compile_options(graph PRIVATE ${COMPILE_OPTIONS} "-fvisibility=default")
target_link_options(graph PRIVATE ${LINK_OPTIONS})
target_link_libraries(graph PRIVATE pthread dl)
set_target_properties(graph PROPERTIES
    C_VISIBILITY_PRESET default
    VISIBILITY_INLINES_HIDDEN ON
)

# Build the shared library for graph visualization
# list(APPEND VISUALIZER_LINK_OPTIONS "-Wl,-Bsymbolic")
add_library(graph_visualization SHARED ${VISUALIZATION_SOURCES})
target_compile_options(graph_visualization PRIVATE ${COMPILE_OPTIONS})
# target_link_options(graph_visualization PRIVATE ${VISUALIZER_LINK_OPTIONS})
target_link_options(graph_visualization PRIVATE ${LINK_OPTIONS})
target_link_libraries(graph_visualization PRIVATE graph dl pthread ${RAYLIB_LIBRARIES})

# Build the shared library for LD_PRELOAD
add_library(lockdep_interpose SHARED ${INTERPOSE_SOURCES})
target_compile_options(lockdep_interpose PRIVATE ${COMPILE_OPTIONS})
target_link_options(lockdep_interpose PRIVATE ${LINK_OPTIONS})
target_link_libraries(lockdep_interpose PRIVATE graph dl pthread)

# Build ptrace-based detector
add_executable(ptrace-lockdep ${PTRACE_SOURCES})
target_compile_options(ptrace-lockdep PRIVATE ${PTRACE_COMPILE_OPTIONS})
target_link_options(ptrace-lockdep PRIVATE ${LINK_OPTIONS})
if(LIBELF_FOUND)
    target_include_directories(ptrace-lockdep PRIVATE ${LIBELF_INCLUDE_DIRS})
    target_link_libraries(ptrace-lockdep PRIVATE graph pthread ${LIBELF_LIBRARIES} ${RAYLIB_LIBRARIES})
    target_compile_options(ptrace-lockdep PRIVATE ${LIBELF_CFLAGS_OTHER})
else()
    target_link_libraries(ptrace-lockdep PRIVATE graph pthread ${RAYLIB_LIBRARIES})
endif()

# Build test programs
if(TEST_SOURCES)
    foreach(test_file ${TEST_SOURCES})
        get_filename_component(test_name ${test_file} NAME_WE)
        add_executable(${test_name} ${test_file})
        target_compile_options(${test_name} PRIVATE ${COMPILE_OPTIONS})
        target_link_options(${test_name} PRIVATE ${LINK_OPTIONS} "-rdynamic")
        target_link_libraries(${test_name} PRIVATE pthread)
    endforeach()
endif()


# Create a script to run tests with ptrace-lockdep
configure_file(
    "${CMAKE_SOURCE_DIR}/scripts/run_ptrace_test.sh.in"
    "${CMAKE_BINARY_DIR}/run_ptrace_test.sh"
    @ONLY
)

# Add a custom target to run all tests
add_custom_target(run_tests
    COMMAND ${CMAKE_BINARY_DIR}/run_ptrace_test.sh
    DEPENDS ptrace-lockdep
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Running all deadlock detection tests"
)
