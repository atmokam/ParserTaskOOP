cmake_minimum_required(VERSION 3.15)

project( 
    PowerPointProject
    VERSION 1.0
    DESCRIPTION "PowerPoint Project"
    LANGUAGES CXX
)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets)
find_package(Qt6 COMPONENTS Gui REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

add_compile_options(-I. )

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_executable(PowerPointProject
CLI/Controller.cpp 
CLI/Validator.cpp  
Data/Slide.cpp 
CLI/Parser.cpp 
Data/Document.cpp 
Serialization/Converter.cpp 
CLI/Command.cpp 
Serialization/SaveLoad.cpp 
Serialization/Serializer.cpp
Serialization/Deserializer.cpp
Director/Actions.cpp  
Director/Director.cpp 
Application/Application.cpp
Data/Item/ItemBase.cpp
Renderer/Shape/ShapeBase.cpp
CLI/CommandHistory.cpp
CLI/CommandFactory.cpp
Data/Item/ItemAttributes.cpp
Renderer/Shape/ShapeLibrary.cpp
Renderer/Formatting/DimentionConverter.cpp
Renderer/Formatting/FormatLibrary.cpp
Serialization/JsonConverter.cpp
Data/IDGenerator.cpp
Renderer/VisualConversion/QtConverter.cpp
Renderer/VisualConversion/TextFontAdjuster.cpp
Renderer/VisualRenderingVisitor.cpp
Renderer/ConsoleRenderingVisitor.cpp
Renderer/Shape/ShapeTextVisitor.cpp
Renderer/Shape/InnerMarginConstant.cpp
Renderer/Shape/InscribedRectangleCalculator.cpp
Data/Item/ItemBuilder.cpp
UI/Controller.cpp
UI/CommandPane.cpp
UI/MainWindow.cpp
Program.cpp 
 )

target_link_libraries(PowerPointProject PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets)