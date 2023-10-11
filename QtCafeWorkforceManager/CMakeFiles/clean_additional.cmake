# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\QtCafeWorkforceManager_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\QtCafeWorkforceManager_autogen.dir\\ParseCache.txt"
  "QtCafeWorkforceManager_autogen"
  )
endif()
