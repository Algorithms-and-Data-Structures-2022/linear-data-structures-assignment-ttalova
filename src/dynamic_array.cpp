#include "assignment/dynamic_array.hpp"

#include <algorithm>  // copy, fill
#include <stdexcept>  // invalid_argument (НЕЛЬЗЯ ИСПОЛЬЗОВАТЬ)

namespace assignment {

  DynamicArray::DynamicArray(int capacity) {

    // выбрасываем ошибку, если указана неположительная емкость массива
    if (capacity <= 0) {
      throw std::invalid_argument("capacity is not positive");
    }

    capacity_ = capacity;
    data_ = new int[capacity_];

    std::fill(&data_[0], &data_[capacity_], 0);


  }

  DynamicArray::~DynamicArray() {
    size_ = 0;
    capacity_ = 0;

    delete[] data_;
    data_ = nullptr;
  }

  void DynamicArray::Add(int value) {

    if (size_ == capacity_) {
        Resize(capacity_ + kCapacityGrowthCoefficient);
    }
      data_[size_] = value;
    size_ ++;
  }

  bool DynamicArray::Insert(int index, int value) {
  if (index >= 0 and index <= size_) {
      if (size_ == capacity_) {
          Resize(capacity_ + kCapacityGrowthCoefficient);
      }
      int a;
      for (int i = index; i < size_; i++) {
            a = data_[i];
          data_[i] = value;
          value = a;
      }
    data_[size_] = value;
      size_++;
    return true;
  }
      return false;
  }

  bool DynamicArray::Set(int index, int new_value) {
    if (index >= 0 and index <size_) {
        data_[index] = new_value;
        return true;
    }
    return false;
  }

  std::optional<int> DynamicArray::Remove(int index) {
      if (index >= 0 and index < size_) {
          int a = data_[index];
          for (int i = index; i < size_; i++) {
              data_[i] = data_[i+1];
          }
          size_ -= 1;
          return a;
      }
    return std::nullopt;
  }

  void DynamicArray::Clear() {
      std::fill(&data_[0], &data_[capacity_], 0);
      size_ = 0;
  }

  std::optional<int> DynamicArray::Get(int index) const {
    if (index >= 0 and index < size_ ) {
        return data_[index];
    }
    return std::nullopt;
  }

  std::optional<int> DynamicArray::IndexOf(int value) const {
    for (int i = 0; i < size_; i ++) {
        if (data_[i] == value) {
            return i;
        }

    }
    return std::nullopt;
  }

  bool DynamicArray::Contains(int value) const {
      for (int i = 0; i < size_; i++) {
          if (data_[i] == value) {
              return true;
          }
      }
    return false;
  }

  bool DynamicArray::IsEmpty() const {
    return size_ == 0;
  }

  int DynamicArray::size() const {
    return size_;
  }

  int DynamicArray::capacity() const {
    return capacity_;
  }

  bool DynamicArray::Resize(int new_capacity) {
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
  DynamicArray::DynamicArray(const std::vector<int>& values, int capacity) {

    size_ = static_cast<int>(values.size());
    capacity_ = capacity;

    data_ = new int[capacity]{};

    std::copy(values.data(), values.data() + size_, data_);
  }

  std::vector<int> DynamicArray::toVector(std::optional<int> size) const {

    if (capacity_ == 0 || data_ == nullptr) {
      return {};
    }

    if (size.has_value()) {
      return {data_, data_ + size.value()};
    }

    return {data_, data_ + capacity_};
  }

}  // namespace assignment