cmake_minimum_required(VERSION 3.16)

project(spreadsheet VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6 REQUIRED COMPONENTS Quick)

qt_standard_project_setup()

qt_add_executable(appspreadsheet
    main.cpp
)

qt_add_qml_module(appspreadsheet
    URI spreadsheet
    VERSION 1.0
    QML_FILES Main.qml
    SOURCES spreadsheet.h spreadsheet.cpp editablespreadsheet.h editablespreadsheet.cpp
)

set_target_properties(appspreadsheet PROPERTIES
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appspreadsheet PRIVATE Qt6::Quick)

include(GNUInstallDirs)
install(TARGETS appspreadsheet
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
