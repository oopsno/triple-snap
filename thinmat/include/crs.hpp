#ifndef THINMAT_CRS_HPP
#define THINMAT_CRS_HPP

#include <iostream>
#include <algorithm>
#include <vector>

namespace trisnap {
namespace thinmat {

template<typename DataType, typename IndexType>
class CRSAllocator {
 public:
  CRSAllocator(IndexType row, IndexType col, const DataType &zero) :
      _row(row), _col(col), zero(), data(), col_index(), row_index(row + 1) { }

  const DataType &get(const IndexType row, const IndexType col) const {
    const IndexType begin = row_index[row], end = row_index[row + 2];
    const auto cbegin = col_index.cbegin();
    auto iter = std::find(cbegin + begin, cbegin + end, col);
    if (iter == col_index.cend()) {
      return zero;
    } else {
      return data[*iter];
    }
  }

  void set(const DataType &value, const IndexType row, const IndexType col) {
    const IndexType begin = row_index[row], end = row_index[row + 1];
    const auto cbegin = col_index.cbegin();
    auto iter = std::find(cbegin + begin, cbegin + end, col);
  }

  const size_t count() const {
    return data.size();
  }

 private:
  const DataType zero;
  IndexType _col, _row;
  std::vector<DataType> data;
  std::vector<IndexType> col_index;
  std::vector<IndexType> row_index;
};

}
}

#endif
