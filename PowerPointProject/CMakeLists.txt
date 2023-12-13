cmake_minimum_required(VERSION 3.15)

project( 
    PowerPointProject
    VERSION 1.0
    DESCRIPTION "PowerPoint Project"
    LANGUAGES CXX
)

find_package(Qt6 REQUIRED COMPONENTS Core)
find_package(Qt6 COMPONENTS Gui REQUIRED)

set(CMAKE_CXX_STANDARD 17)

add_compile_options(-I.  -g)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_executable(PowerPointProject
CLI/Controller.cpp 
CLI/Validator.cpp  
Data/Slide.cpp 
Program.cpp 
CLI/Parser.cpp 
Data/Document.cpp 
Serialization/Converter.cpp 
CLI/Command.cpp 
Serialization/SaveLoad.cpp 
Director/Actions.cpp  
Director/Director.cpp 
Application/Application.cpp
Data/ItemBase.cpp
Renderer/ShapeBase.cpp
CLI/CommandHistory.cpp
Data/ItemAttributes.cpp
Renderer/Renderer.cpp
Renderer/ShapeLibrary.cpp
Renderer/Formatting/DimentionConverter.cpp
Renderer/Formatting/Format.cpp )

target_link_libraries(PowerPointProject PRIVATE Qt6::Core Qt6::Gui)