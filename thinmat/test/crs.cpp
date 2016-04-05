#include <gtest/gtest.h>

#if (!defined(THINMAT_CRS_UNITTEST))
#define THINMAT_CRS_UNITTEST
#endif

#include "crs.hpp"

using namespace trisnap::thinmat;

TEST(CRS, custom_zero_value) {
  CRSAllocator<int32_t, int32_t> allocator_ii(32, 32, -1);
  EXPECT_EQ(allocator_ii.get(3, 4), -1);
  EXPECT_EQ(allocator_ii.get(17, 29), -1);

  CRSAllocator<std::string, int32_t> allocator_si(32, 32, "empty");
  EXPECT_EQ(allocator_si.get(5, 21), "empty");
  EXPECT_EQ(allocator_si.get(6, 30), "empty");
}