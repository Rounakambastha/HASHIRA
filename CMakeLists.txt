cmake_minimum_required(VERSION 3.15)
project(ShamirSecretSharing)

find_package(nlohmann_json CONFIG REQUIRED)

add_executable(solution solution.cpp)
target_link_libraries(solution PRIVATE nlohmann_json::nlohmann_json)
set_property(TARGET solution PROPERTY CXX_STANDARD 17)
