#include <cstdio>
#include <initializer_list>
#include <iostream>

class Matrix {
public:
  Matrix();

  Matrix(const size_t, const size_t);

  Matrix(const std::initializer_list<const std::initializer_list<double>> &);

  Matrix(Matrix &&);

  Matrix(const Matrix &);

  Matrix &operator=(Matrix &&);

  double operator()(size_t, size_t) const;

  Matrix operator-() const;

  std::string toString() const;

  friend std::ostream &operator<<(std::ostream &, const Matrix &);

  ~Matrix();

protected:
  size_t N = 0;
  size_t M = 0;
  double *data = nullptr;
};

class MatrixWithLabel : public Matrix {
public:
  using Matrix::Matrix;

  MatrixWithLabel(const std::string &, const size_t, const size_t);
  MatrixWithLabel(
      const std::string &,
      const std::initializer_list<const std::initializer_list<double>>);
  MatrixWithLabel(const MatrixWithLabel &);
  MatrixWithLabel(MatrixWithLabel &&) = default;
  MatrixWithLabel &operator=(MatrixWithLabel &&);

  std::string getLabel();
  void setLabel(const std::string &);

private:
  std::string label = "Placeholder label";
};