#pragma once

#ifdef __FLEXR_KERNEL_OBJ_DETECTOR__

#include <opencv2/opencv.hpp>

#include "flexr_core/include/core.h"

namespace flexr
{
  namespace kernels
  {

    using namespace flexr::types;
    using ObjDetecorInFrame = Message<Frame>;
    //TODO:Determine the real type to use for output info. 
    //TODO:Add Json definitions somewhere.

    //TODO: Remove the 'int' (only for test now) 
    using ObjDetecorOutJson = Message<int>;
    //TODO: Remove out frame (only for test for now)
    using ObjDetectorOutFrame = Message<Frame>; 


    /**
     * @brief Kernel to detect the objects and output the preficted results
     *
     * Port Tag             | Type
     * ---------------------| ----------------------------
     * in_frame             | @ref flexr::types::Message<@ref flexr::types::Frame>
     * out_json             | @ref flexr::types::Message<@ref flexr::types::Json>
    */
    class ObjDetector : public FleXRKernel
    {
      private:
        cv::Mat mirroredImage;

      public:
      /**
       * @brief Initialize kernel with Opencv contexts and frame info
       * @param id
       *  Kernel ID
       * @param width
       *  Frame width
       * @param height
       *  Frame height
       */
        ObjDetector(std::string id, int width = 1920, int height = 1080);

        raft::kstatus run() override;
    };

  }   // namespace pipeline
} // namespace flexr

#endif

