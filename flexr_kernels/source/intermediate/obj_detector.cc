/* flexr_kernels/source/intermediate/example_kernel.cc */
#ifdef __FLEXR_KERNEL_OBJ_DETECTOR__

#include <flexr_kernels/include/intermediate/example_kernel.h>

namespace flexr
{
  namespace kernels
  {
    ObjDetector::ObjDetector(std::string id, int width, int height): FleXRKernel(id)
    {
      setName("ObjDetector");
      portManager.registerInPortTag("in_frame", components::PortDependency::BLOCKING, utils::deserializeRawFrame);
      //TODO: Check what the utils in the portmanager is for
      //TODO: Add utils for the output json
      //TODO: Change the output port (int for test for now)
      portManager.registerOutPortTag("out_info", utils::sendLocalBasicCopy<int>);
    }

    raft::kstatus ObjDetector::run()
    {
      ObjDetecorInFrame *inFrame  = portManager.getInput<ObjDetecorInFrame>("in_frame");
      types::Message<int> *outputC = portManager.getOutputPlaceholder<types::Message<int>>("out_info");

      if(inFrame->data.useAsCVMat().empty() == false){
        //1 means flipping around y-axis, 
        //0 means x-axis
        //-1 means both
        cv::flip(inFrame->data.useAsCVMat()., mirroredImage, 1);
      }

      if(inputB != nullptr) outputC->data = inputA->data + inputB->data;
      else outputC->data = inputA->data + defaultValue;

      portManager.sendOutput("output_c", outputC);
      portManager.freeInput("input_a", inputA);
      portManager.freeInput("input_b", inputB);

      return raft::proceed;
    }
  }
}

#endif