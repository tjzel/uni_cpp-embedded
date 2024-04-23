#include <iostream>
using namespace std;

template <size_t> class Vector;

template <typename T, size_t N> class OperationNodeTraits {
public:
  typedef const T NodeType;
};

template <size_t N> class OperationNodeTraits<Vector<N>, N> {
public:
  typedef const Vector<N> &NodeType;
};

template <size_t N, typename Left, typename Right> class AddOperation {
public:
  static int getForIndex(const size_t index, const Left &left,
                         const Right &right) {
    return left[index] + right[index];
  };

  static Vector<N> getWhole(const Left &left, const Right &right) {
    Vector<N> result;
    for (size_t i = 0; i < N; i++) {
      result[i] = getForIndex(i, left, right);
    }
    return result;
  }
};

template <size_t N, typename Left, typename Right> class SubtractOperation {
public:
  static int getForIndex(const size_t index, const Left &left,
                         const Right &right) {
    return left[index] - right[index];
  };

  static Vector<N> getWhole(const Left &left, const Right &right) {
    Vector<N> result;
    for (size_t i = 0; i < N; i++) {
      result[i] = getForIndex(i, left, right);
    }
    return result;
  }
};

template <size_t N, typename Node> class MultiplyOperation {
public:
  static int getForIndex(const size_t index, const Node &node,
                         const int value) {
    return value * node[index];
  };

  static Vector<N> getWhole(const Node &node, const int value) {
    Vector<N> result;
    for (size_t i = 0; i < N; i++) {
      result[i] = getForIndex(i, node, value);
    }
    return result;
  }
};

template <size_t N, typename Left, typename Right, typename Operation>
class OperationNode {
  typedef OperationNodeTraits<Left, N>::NodeType LeftType;
  typedef OperationNodeTraits<Right, N>::NodeType RightType;

  LeftType _left;
  RightType _right; // keep mult in right

public:
  OperationNode(LeftType left, RightType right) : _left(left), _right(right){};

  int operator[](size_t index) const {
    return Operation::getForIndex(index, _left, _right);
  }

  operator Vector<N>() const { return Operation::getWhole(_left, _right); }
};

template <size_t N> class Vector {
  int data[N];

public:
  Vector() { cout << " Default constr" << endl; }
  Vector(std::initializer_list<int> list) {
    cout << " Init list constr" << endl;
    auto it = list.begin();
    for (int i = 0; i < N; i++) {
      data[i] = *it++;
    }
  }
  Vector(const Vector &m) {
    std::copy(m.data, m.data + N, data);
    cout << " Copy constr" << endl;
  }
  int operator[](int index) const { return data[index]; }
  int &operator[](int index) { return data[index]; }

  friend ostream &operator<<(ostream &out, const Vector &m) {
    for (auto x : m.data) {
      cout << x << ", ";
    }
    return out;
  }

  typedef OperationNode<N, Vector<N>, Vector<N>,
                        AddOperation<N, Vector<N>, Vector<N>>>
      AddNode;

  friend AddNode operator+(const Vector<N> &left, const Vector<N> &right) {
    return AddNode(left, right);
  }

  typedef OperationNode<N, Vector<N>, Vector<N>,
                        SubtractOperation<N, Vector<N>, Vector<N>>>
      SubtractNode;
  friend SubtractNode operator-(const Vector<N> &left, const Vector<N> &right) {
    return SubtractNode(left, right);
  }

  typedef OperationNode<N, Vector<N>, int, MultiplyOperation<N, Vector<N>>>
      MultiplyNode;
  friend MultiplyNode operator*(const Vector<N> &left, const int right) {
    return MultiplyNode(left, right);
  }

  friend MultiplyNode operator*(const int left, const Vector<N> &right) {
    return MultiplyNode(right, left);
  }
};

int main() {
  using V = Vector<10>;
  V v{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  V x(v);
  V y{4, 4, 2, 5, 3, 2, 3, 4, 2, 1};

  cout << "Lazy operations :\n";
  // It does not create temporary Vectors
  // It computes resulting vector coordinate by coordinate
  // (evaluating whole expression)
  V z = v + x + 3 * y - 2 * x;
  cout << z << endl;

  // Computes only one coordinate of Vector
  int e = (z + x + y)[2];
  cout << " e = " << e << endl;
  return 0;
}
/**
 Init list constr
 Copy constr
 Init list constr
Lazy operations :
 Default constr
12, 12, 6, 15, 9, 6, 9, 12, 6, 3,
e = 11
 */