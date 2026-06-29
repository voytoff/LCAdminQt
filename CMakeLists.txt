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

set(APP_ICON_RESOURCE_WINDOWS "appicon.rc")

qt_add_executable(LCAdmin
    ${ADMIN_PROJECT_RESOURCES}
    ${APP_ICON_RESOURCE_WINDOWS}
    main.cpp types.h
    enums.h enums.cpp
    istatewidget.h treeitemtype.h
    mainwindow.h mainwindow.cpp
    settings.h settings.cpp
    treeview.h treeview.cpp
    optionmodel.h optionmodel.cpp
    treeitem.h treeitem.cpp
    tabview.h tabview.cpp
    docbase.h docbase.cpp
    dictionmodel.h dictionmodel.cpp
    leftview.h leftview.cpp
    modeltreebase.h modeltreebase.cpp
    tableview.h tableview.cpp
    db/modeltablemodule.h db/modeltablemodule.cpp
    db/modeltablebase.cpp db/modeltablebase.h
    db/modeltablecrate.h db/modeltablecrate.cpp
    db/modeltableexperiment.h db/modeltableexperiment.cpp
    db/modeltablecalibration.h db/modeltablecalibration.cpp
    db/modeltablecalibration.h db/modeltablecalibration.cpp
    ctl/fixedlistdelegate.h ctl/fixedlistdelegate.cpp
    ctl/enumlistdelegate.h ctl/enumlistdelegate.cpp
    ctl/spinboxdelegate.h ctl/spinboxdelegate.cpp
    db/modeltablesensor.h db/modeltablesensor.cpp
    db/modeltablesensortype.h db/modeltablesensortype.cpp
    db/modeltablemeasureunit.h db/modeltablemeasureunit.cpp
    ctl/checkboxdelegate.h ctl/checkboxdelegate.cpp
    ctl/dateeditdelegate.h ctl/dateeditdelegate.cpp
    ctl/datetimeeditdelegate.h
    ctl/datetimeeditdelegate.cpp
    ctl/sqlcombobox.h ctl/sqlcombobox.cpp
    ctl/styledelegatebase.h ctl/styledelegatebase.cpp
    vw/customviewbase.h vw/customviewbase.cpp
    vw/sensorview.h vw/sensorview.cpp
    vw/tableviewcache.h vw/tableviewcache.cpp
    dlg/settingsdlg.h dlg/settingsdlg.cpp dlg/settingsdlg.ui
    dlg/calibrationdlg.h dlg/calibrationdlg.cpp dlg/calibrationdlg.ui
    vw/modelviewcache.h vw/modelviewcache.cpp
)

target_sources(LCAdmin PRIVATE
    tableview.h tableview.cpp
)

set(SCHEMEHELPEREDIR "../SchemeHelperQt")
include_directories(${SCHEMEHELPEREDIR})
if (NOT TARGET SchemeHelper)
    add_subdirectory(${SCHEMEHELPEREDIR} SchemeHelper)
endif()

set(DBEXTENSIONDIR "../DBExtensionQt/lib")
include_directories(${DBEXTENSIONDIR})
if (NOT TARGET DBExtension)
    add_subdirectory(${DBEXTENSIONDIR} DBExtension)
endif()

set(LCARDDIR "../LCardQt/lib")
include_directories(${LCARDDIR})
if (NOT TARGET LCard)
    add_subdirectory(${LCARDDIR} LCard)
endif()

set(GLOBALLIBDIR "../GlobalLibQt")
include_directories(${GLOBALLIBDIR})
if (NOT TARGET GlobalLib)
    add_subdirectory(${GLOBALLIBDIR} GlobalLib)
endif()


include_directories(db ctl vw dlg)

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
    LCard
    GlobalLib
)

include(GNUInstallDirs)
install(TARGETS LCAdmin
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
