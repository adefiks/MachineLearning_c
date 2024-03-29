#include <iostream>
#include <vector>
#include <tuple>
#include <numeric>
#include <cmath>
#include <limits>
#include <algorithm>

using namespace std;

class linearRegresion
{
private:
    vector<double> m_x_values, m_y_values;
    double m_numberOfElements;
    double coefficient_a, coefficient_b;
    double m_previous_error;

    bool isConverged()
    {
        double error = 0;
        double threshold = 0.001;

        for (size_t i = 0; i < m_numberOfElements; i++)
        {
            error += pow(((coefficient_a * m_x_values[i] + coefficient_b) - m_y_values[i]), 2);
        }
        error /= m_numberOfElements;
        cout << "Error: " << error << endl;

        if (abs(error) > m_previous_error - threshold && abs(error) < m_previous_error + threshold)
        {
            m_previous_error = abs(error);
            return true;
        }
        else
        {
            m_previous_error = abs(error);
            return false;
        }
    }

public:
    linearRegresion() {}
    linearRegresion(vector<double> vec_x, vector<double> vec_y) : m_x_values(vec_x), m_y_values(vec_y), m_numberOfElements(vec_y.size()), m_previous_error(numeric_limits<double>::max()) {}
    ~linearRegresion() {}

    void trainAlgorithm(int numberOfIter, double i_coefficient_a, double i_coefficient_b)
    {
        int iterations = 0;
        coefficient_a = i_coefficient_a;
        coefficient_b = i_coefficient_b;

        while (!isConverged() && iterations < numberOfIter)
        {
            double step = 2 / double(iterations + 2);
            double a_grad = 0, b_grad = 0;

            // compute the gradient of error
            for (size_t i = 0; i < m_numberOfElements; i++)
            {
                a_grad += m_x_values[i] * ((coefficient_a * m_x_values[i] + coefficient_b) - m_y_values[i]);
                b_grad += ((coefficient_a * m_x_values[i] + coefficient_b) - m_y_values[i]);
            }
            a_grad = (2 * a_grad) / m_numberOfElements;
            b_grad = (2 * b_grad) / m_numberOfElements;

            // take a step
            coefficient_a -= step * a_grad;
            coefficient_b -= step * b_grad;

            cout << "coeficient a: " << coefficient_a << " b:" << coefficient_b << endl;
            cout << "grad a: " << a_grad << " b: " << b_grad << endl;

            iterations++;
        }
    }

    double regress(double x_)
    {
        double returnValue = coefficient_a * x_ + coefficient_b;
        return returnValue;
    }
};

int main()
{
    cout << "Linear Regression" << endl;

    vector<double> x{1, 2, 3, 4, 5};
    // vector<double> y{1, 2, 3, 4, 5};
    vector<double> y{2.8, 2.9, 7.6, 9, 8.6};
    // vector<double> y{2, 4, 5, 4, 5};

    linearRegresion linearEntity(x, y);

    linearEntity.trainAlgorithm(1000, 3, -10);

    cout << "Regresion: " << linearEntity.regress(3) << endl;

    return 0;
}