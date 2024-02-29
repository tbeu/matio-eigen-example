#include <iostream>

// Matrix library
// https://eigen.tuxfamily.org/dox/GettingStarted.html
#include <Eigen/Dense>
using Eigen::MatrixXd;

// MATio library
// https://github.com/tesch1/eigen-matio
#include <MATio>
namespace Matio = matio;

namespace MatioEigenExample
{
  double read_first(const char* file_name, const char* var_name)
  {
    MatrixXd data;
    Matio::read_mat(file_name, var_name, data);
    return data(0);
  }
}  // namespace MatioEigenExample
