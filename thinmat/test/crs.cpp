#include <gtest/gtest.h>

#if (!defined(THINMAT_CRS_UNITTEST))
#define THINMAT_CRS_UNITTEST
#endif

#include "crs.hpp"

using namespace trisnap::thinmat;

TEST(CRS, custom_zero_value) {
  CRSAllocator<int32_t, int32_t> allocator_ii(32, 32, -1);
  EXPECT_EQ(-1, allocator_ii.get(3, 4));
  EXPECT_EQ(-1, allocator_ii.get(17, 29));

  CRSAllocator<std::string, int32_t> allocator_si(32, 32, "empty");
  EXPECT_EQ("empty", allocator_si.get(5, 21));
  EXPECT_EQ("empty", allocator_si.get(6, 30));
}

TEST(CRS, set_value) {
  CRSAllocator<int32_t, int32_t> allocator_ii(32, 32, 0);
  allocator_ii.set(5, 8, 42);
  EXPECT_EQ(42, allocator_ii.get(5, 8));
}