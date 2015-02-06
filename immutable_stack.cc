template <typename T>
class immutable_stack {
public:
  immutable_stack()
      : next(nullptr), val(0) {}

  immutable_stack(const immutable_stack<T> &t)
      : next(t.next), val(t.val) {}

  const immutable_stack<T> push(const T &v) const {
    return immutable_stack(v, this);
  }

  // Require: empty() != true
  const immutable_stack<T> pop() const {
    return *next;
  }

  // Require: empty() != true
  T peek() const {
    assert(next != nullptr);
    return val;
  }

  bool empty() const {
    return next == nullptr;
  }

private:
  immutable_stack(const T &v, const immutable_stack *const n)
      : val(v), next(n) {}
  const T val;
  const immutable_stack *const next;
};