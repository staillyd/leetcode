#include <iostream>
#include <memory>
#include <mutex>

template <class T>

class SharedPtr {
 public:
  SharedPtr(T* ptr = nullptr) : _ptr(ptr), _p_count(new int(1)), _p_mutex(new std::mutex) {}
  ~SharedPtr() { Release(); }

  SharedPtr(const SharedPtr<T>& sp) : _p_count(sp._p_count), _ptr(sp._ptr), _p_mutex(sp._p_mutex) { AddCount(); }
  SharedPtr<T>& operator=(const SharedPtr<T>& sp) {
    if (_ptr != sp._ptr) {
      Release();
      _ptr = sp._ptr;
      _p_count = sp._p_count;
      _p_mutex = sp._p_mutex;
      AddCount();
    }
    return *this;
  }
  int use_count() { return *_p_count; }
  T* operator*() { return *_ptr; }
  T* operator->() { return _ptr; }

 private:
  void Release() {
    bool delete_flag = false;
    _p_mutex->lock();
    if (--(*_p_count) == 0) {
      delete _ptr;
      delete _p_count;
      delete_flag = true;
    }
    _p_mutex->unlock();
    if (delete_flag) {
      delete _p_mutex;
    }
  }
  void AddCount() {
    _p_mutex->lock();
    ++(*_p_count);
    _p_mutex->unlock();
  }

 private:
  int* _p_count;
  T* _ptr;
  std::mutex* _p_mutex;
};

struct ListNode {
  int _data;
  // std::shared_ptr<ListNode> _prev;
  // std::shared_ptr<ListNode> _next;
  SharedPtr<ListNode> _prev;
  SharedPtr<ListNode> _next;
  ~ListNode() { std::cout << "~ListNode()" << std::endl; }
};

int main() {
  // std::shared_ptr<ListNode> node1(new ListNode);
  // std::shared_ptr<ListNode> node2(new ListNode);
  SharedPtr<ListNode> node1(new ListNode);
  SharedPtr<ListNode> node2(new ListNode);
  std::cout << node1.use_count() << std::endl;
  std::cout << node2.use_count() << std::endl;
  node1->_next = node2;
  node2->_prev = node1;
  std::cout << node1.use_count() << std::endl;
  std::cout << node2.use_count() << std::endl;
  return 0;
}