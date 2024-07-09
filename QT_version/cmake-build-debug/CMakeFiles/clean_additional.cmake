# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\PK_subway_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\PK_subway_autogen.dir\\ParseCache.txt"
  "PK_subway_autogen"
  )
endif()
