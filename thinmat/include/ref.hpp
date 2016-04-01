#ifndef THINMAT_ALLOCATOR_HPP_HPP
#define THINMAT_ALLOCATOR_HPP_HPP

#include <memory>

namespace trisnap {
namespace thinmat {

template<typename DataType, typename IndexType, template<typename DT, typename IT> class Allocator>
class ElementReference {
 public:
  typedef Allocator<DataType, IndexType> allocator_t;
  typedef std::shared_ptr<allocator_t> allocator_ptr_t;
  ElementReference(const IndexType row, const IndexType col, allocator_ptr_t allocator_ptr) :
      _col(col), _row(row), allocator(allocator_ptr) { }

  inline const DataType &operator=(const DataType &value) {
    allocator->set(_row, _col, value);
    return value;
  }

  inline const DataType &operator=(const DataType &&value) {
    allocator->set(_row, _col, value);
    return value;
  }

  inline operator DataType() const {
    return allocator->get(_row, _col);
  }

 private:
  IndexType _col, _row;
  allocator_ptr_t allocator;
};

}
}

#endif //THINMAT_ALLOCATOR_HPP_HPP
