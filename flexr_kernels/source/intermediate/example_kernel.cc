/* flexr_kernels/source/intermediate/example_kernel.cc */
#ifdef __FLEXR_KERNEL_EXAMPLE_KERNEL__

#include <flexr_kernels/include/intermediate/example_kernel.h>

namespace flexr
{
  namespace kernels
  {
    ExampleKernel::ExampleKernel(std::string id, int defaultValue): FleXRKernel(id), defaultValue(defaultValue)
    {
      setName("ExampleKernel");
      portManager.registerInPortTag("input_a", flexr::PortDependency::BLOCKING);
      portManager.registerInPortTag("input_b", flexr::PortDependency::NONBLOCKING);
      portManager.registerOutPortTag("output_c", utils::sendLocalBasicCopy<int>);
    }

    raft::kstatus ExampleKernel::run()
    {
      types::Message<int> *inputA  = portManager.getInput<types::Message<int>>("input_a");
      types::Message<int> *inputB  = portManager.getInput<types::Message<int>>("input_b");
      types::Message<int> *outputC = portManager.getOutputPlaceholder<types::Message<int>>("output_c");

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