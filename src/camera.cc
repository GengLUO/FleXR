#include <include/camera.h>
#include <include/cv_types.h>

namespace mxre
{
  namespace pipeline
  {
    namespace input_srcs
    {
      Camera::Camera(int dev_idx) : intrinsic(3, 3, CV_64FC1), distCoeffs(4, 1, CV_64FC1, {0, 0, 0, 0}), raft::kernel()
      {
        cam.open(dev_idx, cv::CAP_ANY);
        cam.set(cv::CAP_PROP_FRAME_WIDTH, WIDTH);
        cam.set(cv::CAP_PROP_FRAME_HEIGHT, HEIGHT);
        if (!cam.isOpened())
          std::cerr << "ERROR: unable to open camera" << std::endl;

        frame_idx = 0;

        // set default camera intrinsic
        this->intrinsic.at<double>(0, 0) = WIDTH; this->intrinsic.at<double>(0, 1) = 0; this->intrinsic.at<double>(0, 2) = WIDTH/2;
        this->intrinsic.at<double>(1, 0) = 0; this->intrinsic.at<double>(1, 1) = WIDTH; this->intrinsic.at<double>(1, 2) = HEIGHT/2;
        this->intrinsic.at<double>(2, 0) = 0; this->intrinsic.at<double>(2, 1) = 0; this->intrinsic.at<double>(2, 2) = 1;

        output.addPort<cv::Mat>("out_frame");
      }

      Camera::~Camera()
      {
        if (cam.isOpened())
          cam.release();
      }

      raft::kstatus Camera::run()
      {
        while (frame_idx++ < TOTAL_FRAMES)
        {
          auto frame = output["out_frame"].template allocate_s<cv::Mat>();

          cam >> *frame;
          if ((*frame).empty())
          {
            std::cerr << "ERROR: blank frame grabbed" << std::endl;
            break;
          }
          output["out_frame"].send(); // zero copy

          return raft::proceed;
        }

        return raft::stop;
      }
    } // namespace input_srcs
  }   // namespace pipeline
} // namespace mxre

