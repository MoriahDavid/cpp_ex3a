#include <vector>
#include <iostream>

using namespace std;

namespace zich{

    class Matrix {

        private:
            int rows;
            int cols;
            vector<double> values;

        public:
            Matrix(vector<double> values, int rows, int cols);

        double sum();

        //+
        Matrix operator+(const Matrix& other);

        //+=
        Matrix& operator+=(const Matrix& other);

        //plus unary
        friend Matrix operator+(Matrix &other);


        //-
        Matrix operator-(const Matrix& other);

        //-=
        Matrix& operator-=(const Matrix& other);

        //minus unary
        friend Matrix operator-(Matrix &other);


        // >
        bool operator>(Matrix& other);

        // >=
        bool operator>=(Matrix& other);

        //<
        bool operator<(Matrix& other);

        //<=
        bool operator<=(Matrix& other);

        //==
        bool operator==(Matrix& other);

        //!=
        bool operator!=(Matrix& other);


        //++
        Matrix& operator++(); //prefix
        Matrix operator++(int num); //postfix

        //--
        Matrix& operator--(); //prefix
        Matrix operator--(int num); //postfix


        //* mat*num
        Matrix operator*(double num);
        //* num*mat
        friend Matrix operator*(const double num, Matrix& mat);
        //*=
        Matrix& operator*=(double num);

        //*  mat*mat
        Matrix operator*(const Matrix& other);
        //*=
        Matrix& operator*=(const Matrix& other);


        //cout
        friend std::ostream& operator<< (std::ostream& output, const Matrix& mat);

        //cin
        friend std::istream& operator>> (std::istream& input , Matrix& mat);

    };
}