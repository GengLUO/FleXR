set(FLEXR_CORE_CXX_FLAGS "")
set(FLEXR_CORE_LINKER_FLAGS "")
set(FLEXR_CORE_LINKER_LIBS "")

include(cmake/core/FFmpeg.cmake)
include(cmake/core/nvmpi_portable.cmake)
include(cmake/core/LibZMQ.cmake)
include(cmake/core/OpenCV.cmake)
include(cmake/core/OpenGL.cmake)
include(cmake/core/RaftLib.cmake)
include(cmake/core/Spdlog.cmake)
include(cmake/core/uvgRTP.cmake)
include(cmake/core/yaml-cpp.cmake)
include(cmake/core/rosbag.cmake)
include(cmake/core/catch2.cmake)

macro(core_setup_dependencies)
  core_use_ffmpeg()
  core_use_nvmpi_portable()
  core_use_libzmq()
  core_use_opencv()
  core_use_raftlib()
  core_use_spdlog()
  core_use_rosbag()
  core_use_uvgrtp()
  core_use_yaml_cpp()
  core_use_catch2()
endmacro()

