#include <iostream>
#include "FPLib/include.h"


using namespace std;
using namespace FIREPHOENIX;
int main()
{
    Eigen::MatrixXd num(1,3);
    Eigen::MatrixXd den(1,3);
    num << 0.1, 0.2,  0.8;
    den << 1.0 , - 1.2 , 0.3;
    DiscreteTransFun<double> dSys(num, den);

    for( int i = 0; i < 50; ++i )
    {
        cout << dSys.StepForward(2.0) << endl;
    }

    return 0;
}
