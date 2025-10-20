# Install script for directory: /opt/cppcheck/cppcheck-main/cli

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "0")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/objdump")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "applications" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}/usr/local/bin/cppcheck" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/bin/cppcheck")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}/usr/local/bin/cppcheck"
         RPATH "")
  endif()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/bin/cppcheck")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "/usr/local/bin" TYPE EXECUTABLE FILES "/opt/cppcheck/cppcheck-main/build/bin/cppcheck")
  if(EXISTS "$ENV{DESTDIR}/usr/local/bin/cppcheck" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/bin/cppcheck")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/usr/local/bin/cppcheck")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "applications" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/bin/cppcheck-htmlreport")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "/usr/local/bin" TYPE PROGRAM FILES "/opt/cppcheck/cppcheck-main/htmlreport/cppcheck-htmlreport")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "headers" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/share/Cppcheck/addons/__init__.py;/usr/local/share/Cppcheck/addons/cppcheck.py;/usr/local/share/Cppcheck/addons/cppcheckdata.py;/usr/local/share/Cppcheck/addons/findcasts.py;/usr/local/share/Cppcheck/addons/misc.py;/usr/local/share/Cppcheck/addons/misra.py;/usr/local/share/Cppcheck/addons/misra_9.py;/usr/local/share/Cppcheck/addons/naming.py;/usr/local/share/Cppcheck/addons/namingng.py;/usr/local/share/Cppcheck/addons/runaddon.py;/usr/local/share/Cppcheck/addons/threadsafety.py;/usr/local/share/Cppcheck/addons/y2038.py")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "/usr/local/share/Cppcheck/addons" TYPE FILE FILES
    "/opt/cppcheck/cppcheck-main/addons/__init__.py"
    "/opt/cppcheck/cppcheck-main/addons/cppcheck.py"
    "/opt/cppcheck/cppcheck-main/addons/cppcheckdata.py"
    "/opt/cppcheck/cppcheck-main/addons/findcasts.py"
    "/opt/cppcheck/cppcheck-main/addons/misc.py"
    "/opt/cppcheck/cppcheck-main/addons/misra.py"
    "/opt/cppcheck/cppcheck-main/addons/misra_9.py"
    "/opt/cppcheck/cppcheck-main/addons/naming.py"
    "/opt/cppcheck/cppcheck-main/addons/namingng.py"
    "/opt/cppcheck/cppcheck-main/addons/runaddon.py"
    "/opt/cppcheck/cppcheck-main/addons/threadsafety.py"
    "/opt/cppcheck/cppcheck-main/addons/y2038.py"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "headers" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/share/Cppcheck/addons/ROS_naming.json;/usr/local/share/Cppcheck/addons/namingng.config.json;/usr/local/share/Cppcheck/addons/namingng.json")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "/usr/local/share/Cppcheck/addons" TYPE FILE FILES
    "/opt/cppcheck/cppcheck-main/addons/ROS_naming.json"
    "/opt/cppcheck/cppcheck-main/addons/namingng.config.json"
    "/opt/cppcheck/cppcheck-main/addons/namingng.json"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "headers" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/share/Cppcheck/cfg/avr.cfg;/usr/local/share/Cppcheck/cfg/bento4.cfg;/usr/local/share/Cppcheck/cfg/boost.cfg;/usr/local/share/Cppcheck/cfg/bsd.cfg;/usr/local/share/Cppcheck/cfg/cairo.cfg;/usr/local/share/Cppcheck/cfg/cppcheck-lib.cfg;/usr/local/share/Cppcheck/cfg/cppunit.cfg;/usr/local/share/Cppcheck/cfg/dpdk.cfg;/usr/local/share/Cppcheck/cfg/embedded_sql.cfg;/usr/local/share/Cppcheck/cfg/emscripten.cfg;/usr/local/share/Cppcheck/cfg/ginac.cfg;/usr/local/share/Cppcheck/cfg/gnu.cfg;/usr/local/share/Cppcheck/cfg/googletest.cfg;/usr/local/share/Cppcheck/cfg/gtk.cfg;/usr/local/share/Cppcheck/cfg/icu.cfg;/usr/local/share/Cppcheck/cfg/kde.cfg;/usr/local/share/Cppcheck/cfg/libcerror.cfg;/usr/local/share/Cppcheck/cfg/libcurl.cfg;/usr/local/share/Cppcheck/cfg/libsigc++.cfg;/usr/local/share/Cppcheck/cfg/lua.cfg;/usr/local/share/Cppcheck/cfg/mfc.cfg;/usr/local/share/Cppcheck/cfg/microsoft_atl.cfg;/usr/local/share/Cppcheck/cfg/microsoft_sal.cfg;/usr/local/share/Cppcheck/cfg/microsoft_unittest.cfg;/usr/local/share/Cppcheck/cfg/motif.cfg;/usr/local/share/Cppcheck/cfg/nspr.cfg;/usr/local/share/Cppcheck/cfg/ntl.cfg;/usr/local/share/Cppcheck/cfg/opencv2.cfg;/usr/local/share/Cppcheck/cfg/opengl.cfg;/usr/local/share/Cppcheck/cfg/openmp.cfg;/usr/local/share/Cppcheck/cfg/openssl.cfg;/usr/local/share/Cppcheck/cfg/pcre.cfg;/usr/local/share/Cppcheck/cfg/posix.cfg;/usr/local/share/Cppcheck/cfg/protobuf.cfg;/usr/local/share/Cppcheck/cfg/python.cfg;/usr/local/share/Cppcheck/cfg/qt.cfg;/usr/local/share/Cppcheck/cfg/ruby.cfg;/usr/local/share/Cppcheck/cfg/sdl.cfg;/usr/local/share/Cppcheck/cfg/selinux.cfg;/usr/local/share/Cppcheck/cfg/sfml.cfg;/usr/local/share/Cppcheck/cfg/sqlite3.cfg;/usr/local/share/Cppcheck/cfg/std.cfg;/usr/local/share/Cppcheck/cfg/tinyxml2.cfg;/usr/local/share/Cppcheck/cfg/vcl.cfg;/usr/local/share/Cppcheck/cfg/windows.cfg;/usr/local/share/Cppcheck/cfg/wxsqlite3.cfg;/usr/local/share/Cppcheck/cfg/wxsvg.cfg;/usr/local/share/Cppcheck/cfg/wxwidgets.cfg;/usr/local/share/Cppcheck/cfg/zephyr.cfg;/usr/local/share/Cppcheck/cfg/zlib.cfg")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "/usr/local/share/Cppcheck/cfg" TYPE FILE FILES
    "/opt/cppcheck/cppcheck-main/cfg/avr.cfg"
    "/opt/cppcheck/cppcheck-main/cfg/bento4.cfg"
    "/opt/cppcheck/cppcheck-main/cfg/boost.cfg"
    "/opt/cppcheck/cppcheck-main/cfg/bsd.cfg"
    "/opt/cppcheck/cppcheck-main/cfg/cairo.cfg"
    "/opt/cppcheck/cppcheck-main/cfg/cppcheck-lib.cfg"
    "/opt/cppcheck/cppcheck-main/cfg/cppunit.cfg"
    "/opt/cppcheck/cppcheck-main/cfg/dpdk.cfg"
    "/opt/cppcheck/cppcheck-main/cfg/embedded_sql.cfg"
    "/opt/cppcheck/cppcheck-main/cfg/emscripten.cfg"
    "/opt/cppcheck/cppcheck-main/cfg/ginac.cfg"
    "/opt/cppcheck/cppcheck-main/cfg/gnu.cfg"
    "/opt/cppcheck/cppcheck-main/cfg/googletest.cfg"
    "/opt/cppcheck/cppcheck-main/cfg/gtk.cfg"
    "/opt/cppcheck/cppcheck-main/cfg/icu.cfg"
    "/opt/cppcheck/cppcheck-main/cfg/kde.cfg"
    "/opt/cppcheck/cppcheck-main/cfg/libcerror.cfg"
    "/opt/cppcheck/cppcheck-main/cfg/libcurl.cfg"
    "/opt/cppcheck/cppcheck-main/cfg/libsigc++.cfg"
    "/opt/cppcheck/cppcheck-main/cfg/lua.cfg"
    "/opt/cppcheck/cppcheck-main/cfg/mfc.cfg"
    "/opt/cppcheck/cppcheck-main/cfg/microsoft_atl.cfg"
    "/opt/cppcheck/cppcheck-main/cfg/microsoft_sal.cfg"
    "/opt/cppcheck/cppcheck-main/cfg/microsoft_unittest.cfg"
    "/opt/cppcheck/cppcheck-main/cfg/motif.cfg"
    "/opt/cppcheck/cppcheck-main/cfg/nspr.cfg"
    "/opt/cppcheck/cppcheck-main/cfg/ntl.cfg"
    "/opt/cppcheck/cppcheck-main/cfg/opencv2.cfg"
    "/opt/cppcheck/cppcheck-main/cfg/opengl.cfg"
    "/opt/cppcheck/cppcheck-main/cfg/openmp.cfg"
    "/opt/cppcheck/cppcheck-main/cfg/openssl.cfg"
    "/opt/cppcheck/cppcheck-main/cfg/pcre.cfg"
    "/opt/cppcheck/cppcheck-main/cfg/posix.cfg"
    "/opt/cppcheck/cppcheck-main/cfg/protobuf.cfg"
    "/opt/cppcheck/cppcheck-main/cfg/python.cfg"
    "/opt/cppcheck/cppcheck-main/cfg/qt.cfg"
    "/opt/cppcheck/cppcheck-main/cfg/ruby.cfg"
    "/opt/cppcheck/cppcheck-main/cfg/sdl.cfg"
    "/opt/cppcheck/cppcheck-main/cfg/selinux.cfg"
    "/opt/cppcheck/cppcheck-main/cfg/sfml.cfg"
    "/opt/cppcheck/cppcheck-main/cfg/sqlite3.cfg"
    "/opt/cppcheck/cppcheck-main/cfg/std.cfg"
    "/opt/cppcheck/cppcheck-main/cfg/tinyxml2.cfg"
    "/opt/cppcheck/cppcheck-main/cfg/vcl.cfg"
    "/opt/cppcheck/cppcheck-main/cfg/windows.cfg"
    "/opt/cppcheck/cppcheck-main/cfg/wxsqlite3.cfg"
    "/opt/cppcheck/cppcheck-main/cfg/wxsvg.cfg"
    "/opt/cppcheck/cppcheck-main/cfg/wxwidgets.cfg"
    "/opt/cppcheck/cppcheck-main/cfg/zephyr.cfg"
    "/opt/cppcheck/cppcheck-main/cfg/zlib.cfg"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "headers" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/share/Cppcheck/platforms/aix_ppc64.xml;/usr/local/share/Cppcheck/platforms/arm32-wchar_t2.xml;/usr/local/share/Cppcheck/platforms/arm32-wchar_t4.xml;/usr/local/share/Cppcheck/platforms/arm64-wchar_t2.xml;/usr/local/share/Cppcheck/platforms/arm64-wchar_t4.xml;/usr/local/share/Cppcheck/platforms/avr8.xml;/usr/local/share/Cppcheck/platforms/cray_sv1.xml;/usr/local/share/Cppcheck/platforms/elbrus-e1cp.xml;/usr/local/share/Cppcheck/platforms/mips32.xml;/usr/local/share/Cppcheck/platforms/msp430_eabi_large_datamodel.xml;/usr/local/share/Cppcheck/platforms/pic16.xml;/usr/local/share/Cppcheck/platforms/pic8-enhanced.xml;/usr/local/share/Cppcheck/platforms/pic8.xml")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "/usr/local/share/Cppcheck/platforms" TYPE FILE FILES
    "/opt/cppcheck/cppcheck-main/platforms/aix_ppc64.xml"
    "/opt/cppcheck/cppcheck-main/platforms/arm32-wchar_t2.xml"
    "/opt/cppcheck/cppcheck-main/platforms/arm32-wchar_t4.xml"
    "/opt/cppcheck/cppcheck-main/platforms/arm64-wchar_t2.xml"
    "/opt/cppcheck/cppcheck-main/platforms/arm64-wchar_t4.xml"
    "/opt/cppcheck/cppcheck-main/platforms/avr8.xml"
    "/opt/cppcheck/cppcheck-main/platforms/cray_sv1.xml"
    "/opt/cppcheck/cppcheck-main/platforms/elbrus-e1cp.xml"
    "/opt/cppcheck/cppcheck-main/platforms/mips32.xml"
    "/opt/cppcheck/cppcheck-main/platforms/msp430_eabi_large_datamodel.xml"
    "/opt/cppcheck/cppcheck-main/platforms/pic16.xml"
    "/opt/cppcheck/cppcheck-main/platforms/pic8-enhanced.xml"
    "/opt/cppcheck/cppcheck-main/platforms/pic8.xml"
    )
endif()

