# -----------------------------------------------
# File that provides "make uninstall" target
#  We use the file 'install_manifest.txt'
# -----------------------------------------------
if(NOT EXISTS "/opt/cppcheck/cppcheck-main/build/install_manifest.txt")
  message(FATAL_ERROR "Cannot find install manifest: \"/opt/cppcheck/cppcheck-main/build/install_manifest.txt\"")
endif(NOT EXISTS "/opt/cppcheck/cppcheck-main/build/install_manifest.txt")

file(READ "/opt/cppcheck/cppcheck-main/build/install_manifest.txt" files)
string(REGEX REPLACE "\n" ";" files "${files}")
foreach(file ${files})
  message(STATUS "Uninstalling \"$ENV{DESTDIR}${file}\"")
	execute_process(COMMAND rm $ENV{DESTDIR}${file})
endforeach(file)


