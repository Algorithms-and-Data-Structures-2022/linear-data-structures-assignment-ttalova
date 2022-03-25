#include "assignment/linked_list.hpp"

namespace assignment {

  LinkedList::~LinkedList() {

    // эквивалентно очистке списка
    LinkedList::Clear();
  }

  void LinkedList::Add(int value) {
      Node* node = new Node(value);
      if (front_ == nullptr) {
          front_ = node;
          back_ = node;
      }
      else {
          back_->next = node;
          back_ = node;
      }
      size_ ++;
  }

  bool LinkedList::Insert(int index, int value) {
if (index >= 0 and index <= size_) {
    Node* node = new Node(value);
    if (front_ == nullptr) {
        front_ = node;
        back_ = node;
    }
    else {
        if (index == 0) {
            node -> next = front_;
            front_ = node;
        } else if (index == size_) {
            back_ -> next = node;
            back_ = node;
        } else {
            Node* prev_node = FindNode(index-1);
            node->next = prev_node->next;
            prev_node->next = node;
        }
    }
    size_++;
    return true;
}
    return false;
  }

  bool LinkedList::Set(int index, int new_value) {
      if (index >= 0 and index < size_) {
          Node* node = FindNode(index);
          node->value = new_value;
          return true;
      }
    return false;
  }

  std::optional<int> LinkedList::Remove(int index) {
    if (index >= 0 and index <= size_ and front_ != nullptr) {
        if (index == 0) {
            Node* a = front_;
            Node* curr = front_->next;
            front_= curr;
            size_--;
            return a->value;
        }
        else {
            int i = 0;
            for (Node* curr = front_; curr != nullptr;) {
                if (i == index - 1) {
                    int b = curr->next->value;
                    curr -> next = curr -> next -> next;
                    size_--;
                    return b;
                }
                i++;
                curr = curr->next;
            }
        }
    }
    return std::nullopt;
  }

  void LinkedList::Clear() {
    for (Node* curr = front_; curr != nullptr; ) {
        Node* node_to_remove = curr;
        curr = curr -> next;
        delete node_to_remove;
    }
    front_ = nullptr;
    back_ = nullptr;
    size_ = 0;
  }

  std::optional<int> LinkedList::Get(int index) const {
      if (index >= 0 and index < size_) {
          Node* node = FindNode(index);
          return node->value;
      }
    return std::nullopt;
  }

  std::optional<int> LinkedList::IndexOf(int value) const {
      int i = 0;
      for (Node* curr = front_; curr != nullptr;){
          if ( curr->value == value){
              return i;
          }
          i++;
          curr = curr->next;
    }
        return std::nullopt;
  }

  bool LinkedList::Contains(int value) const {
      for (Node* curr = front_; curr != nullptr;){
          if ( curr->value == value){
              return true;
          }
          curr = curr->next;
      }
    return false;
  }

  bool LinkedList::IsEmpty() const {
    return front_ == nullptr;
  }

  int LinkedList::size() const {
    return size_;
  }

  std::optional<int> LinkedList::front() const {
    if (front_ != nullptr) {
        return front_ -> value;
    }
    return std::nullopt;
  }

  std::optional<int> LinkedList::back() const {
      if (back_ != nullptr) {
          return back_ -> value;
      }
    return std::nullopt;
  }

  Node* LinkedList::FindNode(int index) const {
      if (index >= 0 and index < size_) {
          int i = 0;
          for (Node* curr = front_; curr != nullptr;){
              if ( i == index){
                  return curr;
              }
              i++;
              curr = curr->next;
          }
          }
          return nullptr;
  }

  // ДЛЯ ТЕСТИРОВАНИЯ
  LinkedList::LinkedList(const std::vector<int>& values) {

    if (values.empty()) {
      return;
    }

    auto* curr_node = new Node(values.front());
    front_ = curr_node;

    for (int index = 1; index < values.size() - 1; ++index) {
      curr_node->next = new Node(values[index]);
      curr_node = curr_node->next;
    }

    if (values.size() == 1) {
      back_ = front_;
    } else {
      curr_node->next = new Node(values.back());
      back_ = curr_node->next;
    }

    size_ = static_cast<int>(values.size());
  }

  std::vector<int> LinkedList::toVector() const {

    if (front_ == nullptr || size_ == 0) {
      return {};
    }

    std::vector<int> array;
    array.reserve(size_);

    for (auto* node = front_; node != nullptr; node = node->next) {
      array.push_back(node->value);
    }

    return array;
  }

}  // namespace assignment