#include <iostream>
#include "./Eigen3/Dense"
using namespace std;

int main()
{
    Eigen::MatrixXd a(3,3);
    a(0,0) = 1.0;
    a(0,2) = 3.0;
    cout  << a(0,0) << '\t' << a(0,2) << endl;
    return 0;
}
