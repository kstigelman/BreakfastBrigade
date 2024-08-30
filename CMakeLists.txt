cmake_minimum_required(VERSION 3.21)
project(Breakfast LANGUAGES CXX)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

add_executable(Breakfast src/main.cpp 
)
set(CMAKE_COMPILE_WARNING_AS_ERROR OFF)

target_link_libraries(Breakfast PRIVATE sfml-graphics)
target_compile_features(Breakfast PRIVATE cxx_std_17)
if (WIN32 AND BUILD_SHARED_LIBS)
    add_custom_command(TARGET Breakfast POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:Breakfast> $<TARGET_FILE_DIR:Breakfast> COMMAND_EXPAND_LISTS)
endif()

file (COPY ${CMAKE_CURRENT_SOURCE_DIR}/src/resources DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Release/resources)

install(TARGETS Breakfast)

