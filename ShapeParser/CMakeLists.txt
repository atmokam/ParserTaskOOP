cmake_minimum_required(VERSION 3.15)

project( 
    PowerPointProject
    VERSION 1.0
    DESCRIPTION "PowerPoint Project"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)

add_compile_options(-I.)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_executable(PowerPointProject
    CLI/Controller.cpp 
    CLI/Validator.cpp  
    Data/Slide.cpp 
    Program.cpp 
    CLI/Parser.cpp 
    Data/Item.cpp 
    Data/Document.cpp 
    Serialization/Converter.cpp 
    CLI/Command.cpp 
    Serialization/SaveLoad.cpp 
    Director/Actions.cpp 
    Director/UndoRedo.cpp 
    Director/Director.cpp 
    Director/Renderer.cpp )