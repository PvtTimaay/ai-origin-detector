cmake_minimum_required(VERSION 3.20)

project(ai-origin-detector
    VERSION 0.1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ---------------------------------------------------------------------------
# vcpkg integration
# Set VCPKG_ROOT or pass -DCMAKE_TOOLCHAIN_FILE=<vcpkg>/scripts/buildsystems/vcpkg.cmake
# ---------------------------------------------------------------------------
if(DEFINED ENV{VCPKG_ROOT} AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(CMAKE_TOOLCHAIN_FILE
        "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake"
        CACHE STRING "vcpkg toolchain file"
    )
endif()

# ---------------------------------------------------------------------------
# Dependencies (managed via vcpkg.json manifest)
# ---------------------------------------------------------------------------
find_package(nlohmann_json CONFIG REQUIRED)
find_package(spdlog        CONFIG REQUIRED)

# ---------------------------------------------------------------------------
# Library target – reusable detection logic
# ---------------------------------------------------------------------------
add_library(detector_lib STATIC
    src/detector.cpp
)

target_include_directories(detector_lib
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_link_libraries(detector_lib
    PUBLIC
        nlohmann_json::nlohmann_json
        spdlog::spdlog
)

# ---------------------------------------------------------------------------
# Executable target
# ---------------------------------------------------------------------------
add_executable(ai-origin-detector
    src/main.cpp
)

target_link_libraries(ai-origin-detector
    PRIVATE
        detector_lib
)

# ---------------------------------------------------------------------------
# Installation rules
# ---------------------------------------------------------------------------
install(TARGETS ai-origin-detector
    RUNTIME DESTINATION bin
)

install(TARGETS detector_lib
    ARCHIVE DESTINATION lib
)

install(DIRECTORY include/
    DESTINATION include
)
