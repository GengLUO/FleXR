macro(add_ffmpeg_module target)
  pkg_search_module("${target}1" ${target})
  list(APPEND FFMPEG_INCLUDE_DIRS "${${target}1_INCLUDE_DIRS}")
  list(APPEND FFMPEG_CXX_FLAGS "${${target}1_CFLAGS}")
  list(APPEND FFMPEG_CXX_FLAGS "${${target}1_CFLAGS_OTHER}")
  list(APPEND FFMPEG_LDFLAGS "${${target}1_LDFLAGS}")
endmacro()

macro(use_ffmpeg)
  SET(FFMPEG_INCLUDE_DIRS "")
  SET(FFMPEG_CXX_FLAGS "")
  SET(FFMPEG_LDFLAGS "")

  SET(FFMPEG_MODULES libavcodec libavformat libavutil libswresample libswscale)
  foreach(FFMPEG_MODULE ${FFMPEG_MODULES})
    add_ffmpeg_module(${FFMPEG_MODULE})
  endforeach(FFMPEG_MODULE)

  #pkg_search_module(AVFILTER REQUIRED libavfilter)
  #if(AVFILTER_FOUND)
  #  list(APPEND FFMPEG_INCLUDE_DIRS ${AVFILTER_INCLUDE_DIRS})
  #  list(APPEND FFMPEG_CXX_FLAGS ${AVFILTER_CFLGAS_OTHER})
  #  list(APPEND FFMPEG_LDFLAGS ${AVFILTER_LDFLAGS})
  #endif(AVFILTER_FOUND)

  #pkg_search_module(AVFORMAT REQUIRED libavformat)
  #if(AVFORMAT_FOUND)
  #  list(APPEND FFMPEG_INCLUDE_DIRS ${AVFORMAT_INCLUDE_DIRS})
  #  list(APPEND FFMPEG_CXX_FLAGS ${AVFORMAT_CFLGAS_OTHER})
  #  list(APPEND FFMPEG_LDFLAGS ${AVFORMAT_LDFLAGS})
  #endif(AVFORMAT_FOUND)


  #pkg_search_module(AVUTIL REQUIRED libavutil)
  #if(AVUTIL_FOUND)
  #  list(APPEND FFMPEG_INCLUDE_DIRS ${AVUTIL_INCLUDE_DIRS})
  #  list(APPEND FFMPEG_CXX_FLAGS ${AVUTIL_CFLGAS_OTHER})
  #  list(APPEND FFMPEG_LDFLAGS ${AVUTIL_LDFLAGS})
  #endif(AVUTIL_FOUND)

  #pkg_search_module(SWRESAMPLE REQUIRED libswresample)
  #if(SWRESAMPLE_FOUND)
  #  list(APPEND FFMPEG_INCLUDE_DIRS ${SWRESAMPLE_INCLUDE_DIRS})
  #  list(APPEND FFMPEG_CXX_FLAGS ${SWRESAMPLE_CFLGAS_OTHER})
  #  list(APPEND FFMPEG_LDFLAGS ${SWRESAMPLE_LDFLAGS})
  #endif(SWRESAMPLE_FOUND)


  #pkg_search_module(SWSCALE REQUIRED libswscale)
  #if(SWSCALE_FOUND)
  #  list(APPEND FFMPEG_INCLUDE_DIRS ${SWSCALE_INCLUDE_DIRS})
  #  list(APPEND FFMPEG_CXX_FLAGS ${SWSCALE_CFLGAS_OTHER})
  #  list(APPEND FFMPEG_LDFLAGS ${SWSCALE_LDFLAGS})
  #endif(SWSCALE_FOUND)

  if(${USE_FFMPEG_NVCODEC})
    # NVIDIA Performance Primitives (NPP) dependencies
    pkg_search_module(NPPIG nppig nppig-10.1 nppig-10.2 nppig-10.0 nppig-9.2 nppig-9.1 nppig-9.0 nppig-8.0)
    if(NPPIG_FOUND)
      include_directories(${NPPIG_INCLUDE_DIRS})
      list(APPEND MXRE_LINKER_FLAGS ${NPPIG_LDFLAGS})
    else(NPPIG_FOUND)
      message(FATAL_ERROR "NPPIG not found")
    endif(NPPIG_FOUND)

    pkg_search_module(NPPICC nppicc nppicc-10.1 nppicc-10.2 nppicc-10.0 nppicc-9.2 nppicc-9.1 nppicc-9.0 nppicc-8.0)
    if(NPPICC_FOUND)
      include_directories(${NPPICC_INCLUDE_DIRS})
      list(APPEND MXRE_LINKER_FLAGS ${NPPICC_LDFLAGS})
    else(NPPICC_FOUND)
      message(FATAL_ERROR "NPPICC not found")
    endif(NPPICC_FOUND)

    pkg_search_module(NPPC nppc nppc-10.1 nppc-10.2 nppc-10.0 nppc-9.2 nppc-9.1 nppc-9.0 nppc-8.0)
    if(NPPC_FOUND)
      include_directories(${NPPC_INCLUDE_DIRS})
      list(APPEND MXRE_LINKER_FLAGS ${NPPC_LDFLAGS})
    else(NPPC_FOUND)
      message(FATAL_ERROR "NPPC not found")
    endif(NPPC_FOUND)
  endif(${USE_FFMPEG_NVCODEC})

  message(STATUS "[FFMpeg Details]")
  message("\t FFMPEG_INCLUDE_DIRS: ${FFMPEG_INCLUDE_DIRS}")
  message("\t FFMPEG_LDFLAGS: ${FFMPEG_LDFLAGS}")

  include_directories(${FFMPEG_INCLUDE_DIRS})
  list(APPEND MXRE_CXX_FLAGS ${FFMPEG_CXX_FLAGS})
  list(APPEND MXRE_LINKER_FLAGS ${FFMPEG_LDFLAGS})
endmacro()

use_ffmpeg()