macro(flexr_option var desc val)
  set(${var} ${val})
endmacro()

macro(build_option variable desc value)
  # BUILD_TYPE: Release, Debug
  if(${variable} STREQUAL DEBUG)
    if(${value})
      add_definitions(-D__DEBUG__=1)
    else()
      add_definitions(-D__DEBUG__=0)
    endif()
  endif()
endmacro()

