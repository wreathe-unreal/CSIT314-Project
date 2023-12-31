cmake_minimum_required(VERSION 3.5)

project(QtCafeWorkforceManager VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Sql) 
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Sql)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(QtCafeWorkforceManager
        MANUAL_FINALIZATION
        main.cpp
        AuthWindow.cpp
        AuthWindow.h
        AuthWindow.ui
        Controller.cpp Controller.h
        Bid.cpp Bid.h Slot.cpp Slot.h
        CafeResources.qrc
        Enums.h
        Enums.cpp
        QApplicationGlobal.h
        QApplicationGlobal.cpp


        User.h
        User.cpp



        SysAdminWindow.h SysAdminWindow.cpp SysAdminWindow.ui
        CafeOwnerWindow.h CafeOwnerWindow.cpp CafeOwnerWindow.ui
        CafeManagerWindow.h CafeManagerWindow.cpp CafeManagerWindow.ui
        CafeStaffWindow.h CafeStaffWindow.cpp CafeStaffWindow.ui





        Response.h
        PopUp.cpp PopUp.h PopUp.ui
        UnitTests.cpp UnitTests.h
        Entity.h


    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET QtCafeWorkforceManager APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(QtCafeWorkforceManager SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PARENT_SOURCE_DIR}/android")
    else()
        add_executable(QtCafeWorkforceManager
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(QtCafeWorkforceManager PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Sql)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.QtCafeWorkforceManager)
endif()
set_target_properties(QtCafeWorkforceManager PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS QtCafeWorkforceManager
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(QtCafeWorkforceManager)
endif()
