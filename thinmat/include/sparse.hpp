#ifndef THINMAT_SPARSE_HPP
#define THINMAT_SPARSE_HPP

#include <memory>
#include <stdexcept>
#include <typeinfo>
#include <type_traits>
#include "crs.hpp"
#include "ref.hpp"

namespace trisnap {
namespace thinmat {

template<typename DataType, typename IndexType, template<typename DT, typename IT> typename Allocator>
class BasicSparseMatrix {
 public:
  static_assert(std::is_integral<IndexType>::value, "IndexType isn't an integral primitive");
  typedef Allocator<DataType, IndexType> allocator_t;
  typedef std::shared_ptr<allocator_t> allocator_ptr_t;
  typedef ElementReference<DataType, IndexType, Allocator> ref_t;

  BasicSparseMatrix(const IndexType row, const IndexType col) : _col(col), _row(row) {
    static_assert(std::is_nothrow_default_constructible<DataType>::value,
                  "DataType isn't nothrow default constructible. You must specify a zero value.");
    allocator.reset(new allocator_t(col, row, DataType()));
  }

  BasicSparseMatrix(const IndexType row, const IndexType col, const DataType &zero) :
      _col(col), _row(row), allocator(new allocator_t(col, row, zero)) { }

  BasicSparseMatrix(const IndexType row, const IndexType col, const DataType &&zero) :
      _col(col), _row(row), allocator(new allocator_t(col, row, zero)) { }

  inline const DataType at(const IndexType row, const IndexType col) const {
    bound_check(row, col);
    return allocator->get(row, col);
  }

  inline ref_t ref(const IndexType row, const IndexType col) {
    bound_check(row, col);
    return ref_t(row, col, allocator);
  }

  inline const DataType &insert(const IndexType row, const IndexType col, const DataType &value) {
    bound_check(row, col);
    return allocator->set(row, col, value);
  }

  inline const IndexType col() const {
    return _col;
  }

  inline const IndexType row() const {
    return _row;
  }

  inline const IndexType size() const {
    return _row * _col;
  }

  inline const size_t count() const {
    return allocator->count();
  }

 private:
  IndexType _col, _row;
  allocator_ptr_t allocator;

  inline void bound_check(const IndexType row, const IndexType col) const {
    if (not (1 <= row and row <= _row and 1 <= col and col <= _col)) {
      throw std::out_of_range("access(" + std::to_string(row) + "," + std::to_string(col) + ")");
    }
  }
};

typedef BasicSparseMatrix<float, int32_t, CRSAllocator> SparseMatrix;

}
}

#endif //THINMAT_SPARSE_HPP
