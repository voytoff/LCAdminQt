cmake_minimum_required(VERSION 3.20)
project(LCAdmin VERSION 0.1 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.2 REQUIRED COMPONENTS
    Quick
    Core
    Widgets
    Gui
    LinguistTools
    Sql
    Svg
    Concurrent
)

qt_standard_project_setup()

set(ADMIN_RESOURCE_FILES res.qrc)
qt6_add_resources(ADMIN_PROJECT_RESOURCES ${ADMIN_RESOURCE_FILES})

qt_add_executable(LCAdmin
    ${ADMIN_PROJECT_RESOURCES}
    main.cpp types.h
    mainwindow.h mainwindow.cpp
    settings.h settings.cpp
    settingsdlg.h settingsdlg.cpp settingsdlg.ui
    treeview.h treeview.cpp
    optionmodel.h optionmodel.cpp
    treeitem.h treeitem.cpp
    tabview.h tabview.cpp
    crateview.h crateview.cpp crateview.ui
    moduleview.h moduleview.cpp moduleview.ui
    docbase.h docbase.cpp
    leftview.h leftview.cpp
    dictionmodel.h dictionmodel.cpp
    modeltreebase.h modeltreebase.cpp
    tableview.h tableview.cpp
    db/modeltablemodule.h db/modeltablemodule.cpp
    db/modeltablebase.cpp db/modeltablebase.h
    db/modeltablecrate.h db/modeltablecrate.cpp
)

set(SCHEMEHELPEREDIR "../SchemeHelperQt")
include_directories(${SCHEMEHELPEREDIR})
add_subdirectory(${SCHEMEHELPEREDIR} SchemeHelper)

set(DBEXTENSIONDIR "../DBExtensionQt")
include_directories(${DBEXTENSIONDIR}/lib)
add_subdirectory(${DBEXTENSIONDIR} DBExtension)

include_directories(db)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(LCAdmin PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.LCAdmin
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(LCAdmin PRIVATE
    Qt6::Quick
    Qt6::Gui
    Qt6::Widgets
    Qt6::Sql
    Qt6::Svg
    SchemeHelper
    DBExtension
)

include(GNUInstallDirs)
install(TARGETS LCAdmin
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
