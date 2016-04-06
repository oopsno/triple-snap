#ifndef THINMAT_CRS_HPP
#define THINMAT_CRS_HPP

#include <iostream>
#include <algorithm>
#include <utility>
#include <vector>
#include <iterator>

namespace trisnap {
namespace thinmat {

template<typename DataType, typename IndexType>
class CRSAllocator {
 public:
  #if defined(THINMAT_CRS_UNITTEST)
  inline CRSAllocator(IndexType row, IndexType col, const DataType &&zero) :
      CRSAllocator(row, col, zero) { };
  #endif
  CRSAllocator(IndexType row, IndexType col, const DataType &zero) :
      _row(row), _col(col), zero(zero), data(), row_index(row + 1, 0), not_found(row * col) {
  }

  const DataType &get(const IndexType row, const IndexType col) const {
    auto pos = find(row, col);
    if (pos == not_found) {
      return zero;
    } else {
      return data[pos].second;
    }
  }

  void set(const IndexType row, const IndexType col, const DataType &value) {
    IndexType result = find(row, col);
    if (result == not_found) { // 插入
      auto succ_begin = row_index.begin() + row + (_row > 1);
      data.insert(data.begin() + *succ_begin, pair_t(col, value));
      std::transform(succ_begin, row_index.end(), succ_begin, succ);
    } else { // 改写
      data[result].second = value;
    }
  }

  const size_t count() const {
    return data.size();
  }

 private:
  typedef std::pair<IndexType, DataType> pair_t;
  const DataType zero;
  const IndexType not_found;
  IndexType _col, _row;
  std::vector<std::pair<IndexType, DataType>> data;
  std::vector<IndexType> row_index;

  inline IndexType find(const IndexType row, const IndexType col) const {
    const auto range_begin = data.cbegin() + row_index[row];
    const auto range_end = data.cbegin() + row_index[row + 1];
    auto result = std::find_if(range_begin, range_end, [col](auto &p) {
      return p.first == col;
    });
    if (std::distance(result, range_end) == 0) {
      return not_found;
    } else {
      return std::distance(data.cbegin(), result);
    }
  }

  static inline IndexType succ(const IndexType i) {
    return i + 1;
  }
};

}
}

#endif
