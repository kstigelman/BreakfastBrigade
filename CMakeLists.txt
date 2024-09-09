cmake_minimum_required(VERSION 3.21)
project(Breakfast LANGUAGES CXX)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

FetchContent_Declare(
  imgui
  GIT_REPOSITORY https://github.com/ocornut/imgui
  GIT_TAG 35b1148efb839381b84de9290d9caf0b66ad7d03
)
FetchContent_MakeAvailable(imgui)

FetchContent_Declare(
  imgui-sfml
  GIT_REPOSITORY https://github.com/SFML/imgui-sfml
  GIT_TAG 82dc2033e51b8323857c3ae1cf1f458b3a933c35
)

set(IMGUI_DIR ${imgui_SOURCE_DIR})
set(IMGUI_SFML_FIND_SFML OFF)
set(IMGUI_SFML_IMGUI_DEMO ON)

FetchContent_MakeAvailable(imgui-sfml)

add_executable(Breakfast src/main.cpp 
)
set(CMAKE_COMPILE_WARNING_AS_ERROR OFF)

target_link_libraries(Breakfast PRIVATE sfml-graphics)
target_link_libraries(Breakfast PRIVATE sfml-audio)
target_link_libraries(Breakfast PRIVATE ImGui-SFML::ImGui-SFML)

target_compile_features(Breakfast PRIVATE cxx_std_17)
if (WIN32 AND BUILD_SHARED_LIBS)
    add_custom_command(TARGET Breakfast POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:Breakfast> $<TARGET_FILE_DIR:Breakfast> COMMAND_EXPAND_LISTS)
endif()

file (COPY ${CMAKE_CURRENT_SOURCE_DIR}/src/resources DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Release/resources)

install(TARGETS Breakfast)

