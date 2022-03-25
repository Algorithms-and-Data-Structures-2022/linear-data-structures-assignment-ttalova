#include "assignment/array_stack.hpp"

#include <algorithm>  // copy, fill
#include <stdexcept>  // invalid_argument (НЕЛЬЗЯ ИСПОЛЬЗОВАТЬ)

namespace assignment {

  ArrayStack::ArrayStack(int capacity) {

    // выбрасываем ошибку, если указана неположительная емкость стека
    if (capacity <= 0) {
      throw std::invalid_argument("capacity is not positive");
    }

      capacity_ = capacity;
      data_ = new int[capacity_];
      std::fill(&data_[0], &data_[capacity_], 0);
  }

  ArrayStack::~ArrayStack() {
    size_ = 0;
    capacity_ = 0;
    delete[] data_;
    data_ = nullptr;
  }

  void ArrayStack::Push(int value) {
      if (size_ == capacity_) {
          Resize(capacity_ + kCapacityGrowthCoefficient);
      }
      data_[size_] = value;
      size_ ++;
  }

  bool ArrayStack::Pop() {
      if (size_ > 0){
          data_[size_ - 1] = 0;
          size_--;
          return true;
      }
    return false;
  }

  void ArrayStack::Clear() {
      std::fill(&data_[0], &data_[capacity_], 0);
      size_ = 0;
  }

  std::optional<int> ArrayStack::Peek() const {
    if (size_ > 0){
        return data_[size_ - 1];
    }
    return std::nullopt;
  }

  bool ArrayStack::IsEmpty() const {
    // Write your code here ...
    return size_== 0;
  }

  int ArrayStack::size() const {
    // Write your code here ...
    return size_;
  }

  int ArrayStack::capacity() const {
    // Write your code here ...
    return capacity_;
  }

  bool ArrayStack::Resize(int new_capacity) {
      if (new_capacity > 0 and new_capacity > capacity_) {
          capacity_ = new_capacity;
          int *data2_ = new int[capacity_];
          std::fill(&data2_[0], &data2_[capacity_], 0);
          for (int i = 0; i < capacity_; i++) {
              data2_[i] = data_[i];
          }
          delete[] data_;
          data_ = data2_;
          return true;
      }
    return false;
  }

  // ДЛЯ ТЕСТИРОВАНИЯ
  ArrayStack::ArrayStack(const std::vector<int>& values, int capacity) {

    size_ = static_cast<int>(values.size());
    capacity_ = capacity;

    data_ = new int[capacity]{};

    std::copy(values.data(), values.data() + size_, data_);
  }

  std::vector<int> ArrayStack::toVector(std::optional<int> size) const {

    if (capacity_ == 0 || data_ == nullptr) {
      return {};
    }

    if (size.has_value()) {
      return {data_, data_ + size.value()};
    }

    return {data_, data_ + capacity_};
  }

}  // namespace assignment
