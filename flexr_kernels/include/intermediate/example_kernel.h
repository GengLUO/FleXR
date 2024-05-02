/* flexr_kernels/include/intermediate/example_kernel.h */
# pragma once
#ifdef __FLEXR_KERNEL_EXAMPLE_KERNEL__

#include <flexr_core/include/core.h>

namespace flexr
{
  namespace kernels
  {
    class ExampleKernel: public FleXRKernel
    {
      private:
        int defaultValue;
      public:
        ExampleKernel(std::string id, int defaultValue);
        raft::kstatus run() override;
    }
  }
}

#endif