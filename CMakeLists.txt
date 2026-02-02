cmake_minimum_required(VERSION 3.16)

project(helloworld_Qt VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick)
find_package(Qt6 REQUIRED COMPONENTS Sql)

qt_add_executable(apphelloworld_Qt
    main.cpp
)

qt_add_qml_module(apphelloworld_Qt
    URI helloworld_Qt
    VERSION 1.0
    QML_FILES
        Main.qml
        RESOURCES
        RESOURCES resource/images/README.txt
        RESOURCES resource/images/backspace.svg
        SOURCES Calculator.cpp
        SOURCES Calculator.h
        SOURCES database.cpp
        SOURCES database.h
        QML_FILES
        QML_FILES
        QML_FILES UI_components/CalcButton.qml
        QML_FILES UI_components/HistoryPanel.qml
        QML_FILES UI_components/Display.qml
        RESOURCES README.md
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(apphelloworld_Qt PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.apphelloworld_Qt
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(apphelloworld_Qt
    PRIVATE Qt6::Quick
    PRIVATE Qt6::Sql
)

include(GNUInstallDirs)
install(TARGETS apphelloworld_Qt
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
