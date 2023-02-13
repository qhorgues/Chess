cmake_minimum_required (VERSION 3.20)

project (Chess LANGUAGES C VERSION 1.0)

include(CTest)
enable_testing()

include(${CMAKE_SOURCE_DIR}/cmake/option.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/CompilerWarnings.cmake)

if (MINGW)
    set (CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static")

    # if (${CMAKE_BUILD_TYPE} MATCHES "Debug" OR ${CMAKE_BUILD_TYPE} MATCHES "RelWithDebInfo")
    #     set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -mwindows")
    # endif()
endif (MINGW)

set_choice (CMAKE_BUILD_TYPE "Debug;Release;MinSizeRel;RelWithDebInfo" "Debug" "Choose type of build")

set (SRCS
	src/main.c
	src/Board/Board.c
	src/listMove/listMove.c
	src/log/log.c
)

set (HEADERS
	src/log/log.h
	src/Board/Board.h
	src/listMove/listMove.h
	include/except.h
	include/version.h
)

include_directories(${CMAKE_SOURCE_DIR}/include)

set (CMAKE_C_STANDARD 17)
set (CMAKE_C_STANDARD_REQUIRED ON)

add_executable (${PROJECT_NAME} ${SRCS} ${HEADERS})
set_target_warnings(${PROJECT_NAME})

include(GNUInstallDirs)

if (WIN32)
	install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION .)
else ()
	install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin/)
endif ()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PACKAGE_NAME ${PROJECT_NAME})
set(CPACK_PACKAGE_VENDOR "Quentin Horgues")



set (CPACK_NSIS_MUI_ICON "${CMAKE_CURRENT_SOURCE_DIR}/Icones\\Knight.ico")
set (CPACK_NSIS_MUI_UNIICON "${CMAKE_CURRENT_SOURCE_DIR}/Icones\\Uninstall.ico")

set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
set (CPACK_PACKAGE_INSTALL_DIRECTORY "${PROJECT_NAME}-${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}")

set (CPACK_NSIS_PACKAGE_NAME "${PROJECT_NAME}-${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}")
set (CPACK_NSIS_INSTALL_NAME "${PROJECT_NAME}-Install")
set (CPACK_NSIS_UNINSTALL_NAME "${PROJECT_NAME}-Uninstall")
set (CPACK_NSIS_DISPLAY_NAME "${PROJECT_NAME}-${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}")

if (WIN32)
	set (CPACK_NSIS_MUI_ICON "${CMAKE_CURRENT_SOURCE_DIR}/Icones\\Knight.ico")
	set (CPACK_NSIS_MUI_UNIICON "${CMAKE_CURRENT_SOURCE_DIR}/Icones\\Uninstall.ico")
	set (CPACK_PACKAGE_ICON "${CMAKE_CURRENT_SOURCE_DIR}/Icones\\Knight.ico")
else ()
	set (CPACK_NSIS_MUI_ICON "${CMAKE_CURRENT_SOURCE_DIR}/Icones/Knight.ico")
	set (CPACK_NSIS_MUI_UNIICON "${CMAKE_CURRENT_SOURCE_DIR}/Icones/Uninstall.ico")
	set (CPACK_PACKAGE_ICON "${CMAKE_CURRENT_SOURCE_DIR}/Icones/Knight.ico")
endif ()

set (CPACK_RESOURCE_FILE_LICENSE
     "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")

set (CPACK_CREATE_DESKTOP_LINKS ${PROJECT_NAME})
set (CPACK_PACKAGE_EXECUTABLES "${PROJECT_NAME}-${PROJECT_VERSION}" "Chess" )

set (CPACK_DEBIAN_PACKAGE_MAINTAINER "Quentin Horgues")
set (CPACK_PACKAGE_CONTACT "quentin.horgues@outlook.fr")
set (CPACK_DEBIAN_PACKAGE_DEPENDS "libc6")

include(CPack)