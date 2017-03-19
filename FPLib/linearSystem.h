// Linear System Declaration
#ifndef _FIRE_PHOENIX_LINEAR_SYSTEM_H_
#define _FIRE_PHOENIX_LINEAR_SYSTEM_H_

#include "dependence.h"


namespace FIREPHOENIX
{
    // 离散时间传递函数
    template<typename Scalar> class DiscreteTransFun
    {
    private:
        typedef Eigen::Matrix<Scalar, 1, Eigen::Dynamic> RowVector; // 行向量类型
        RowVector m_numerator; // 分子多项式， z^(-1) 的多项式，升幂排列
        RowVector m_denominator; //  分母多项式， z^(-1) 的多项式，升幂排列 ，首项为 1
        RowVector m_inputHistory; // 输入历史序列 uk, uk_1, ... , uk_m
        RowVector m_outputHistory; //  输出历史序列 yk, yk_1, ... , yk_n
    public:
        // 将系统初始化为增益为 1 的纯比例环节
        DiscreteTransFun()
        {
            InitSysPara( RowVector::Ones(1,1),  RowVector::Ones(1,1) );
        }

        // 将系统初始化为分子为 numerator、分母为 denominator, 输入、输出历史序列为零的离散时间传递函数
        DiscreteTransFun( const RowVector & numerator, const RowVector & denominator )
        {
            InitSysPara( numerator, denominator );
        }

        // 将系统初始化为分子为 numerator、分母为 denominator, 输入、输出历史序列为零的离散时间传递函数
        void InitSysPara( const RowVector & numerator, const RowVector & denominator )
        {
            if( 0 == numerator.size() || 0 == denominator.size() )
            {

            }
            m_numerator = numerator;
            m_denominator = denominator;
            Scalar a = m_denominator(0);
            m_numerator /= a;
            m_denominator /= a;
            SetState( RowVector::Zero( m_numerator.rows(), m_numerator.cols() ),
                     RowVector::Zero( m_denominator.rows(), m_denominator.cols() ) );
        }

        // 将历史输入、输出序列分别设置为：inputHistory、outputHistory
        void SetState( const RowVector & inputHistory, const RowVector & outputHistory )
        {
            if( inputHistory.size() != m_numerator.size() || outputHistory.size() != m_denominator.size() )
            {

            }
            m_inputHistory = inputHistory;
            m_outputHistory = outputHistory;
        }

        void GetSysPara( RowVector & numerator, RowVector & denominator ) const
        {
            numerator = m_numerator;
            denominator = m_denominator;
        }
        void GetState( RowVector & inputHistory, RowVector & outputHistory ) const
        {
            inputHistory = m_inputHistory;
            outputHistory = m_outputHistory;
        }

        // 以当前输入 input,向前步进一步，更新系统状态，并返回系统输出值
        Scalar StepForward( Scalar input )
        {
            int i;
            for( i = m_inputHistory.size() - 1; i > 0; --i )
            {
                m_inputHistory( i ) = m_inputHistory( i - 1 );
            }
            m_inputHistory(0) = input;
            for( i = m_outputHistory.size() - 1; i > 0; --i )
            {
                m_outputHistory( i ) = m_outputHistory( i - 1 );
            }
            m_outputHistory(0) = m_numerator.dot( m_inputHistory );
            for( i = 1; i < m_denominator.size(); ++i )
            {
                m_outputHistory(0) -= m_denominator(i) * m_outputHistory(i);
            }
            return m_outputHistory(0);
        }
    };
}


#endif // _FIRE_PHOENIX_LINEAR_SYSTEM_H_
