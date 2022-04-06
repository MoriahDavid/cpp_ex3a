#include <stdlib.h>
#include <numeric>

#include <iostream>

#include "Matrix.hpp"

namespace zich{

    Matrix::Matrix(vector<double> values, int rows, int cols){
        if(values.size() != rows*cols){
            throw invalid_argument("Wrong input, not valid matrix");
        }
        if(rows < 0 || cols < 0){
            throw invalid_argument("Wrong input, negative rows or cols");
        }
        this->rows = rows;
        this->cols = cols;
        this->values = vector(values);
    }


    double Matrix::sum(){
        return accumulate(this->values.begin(), this->values.end(), 0);
    }

    //+
    Matrix Matrix::operator+(const Matrix& other){
        if(this->rows != other.rows || this->cols != other.cols){
            throw invalid_argument("Matrices size should be identical");
        }
        vector<double> vec((size_t) (this->cols * this->rows));
        for(int i = 0; i < this->cols * this->rows; i++){
            vec.at((size_t) i) = (this->values.at((size_t) i) + other.values.at((size_t) i));
        }
        Matrix m_new(vec, this->rows, this->cols);
        return m_new;
    }

    //+=
    Matrix& Matrix::operator+=(const Matrix& other){
        if(this->rows != other.rows || this->cols != other.cols){
            throw invalid_argument("Matrices size should be identical");
        }
        for(int i = 0; i < this->cols * this->rows; i++){
            this->values.at((size_t) i) += other.values.at((size_t) i);
        }
        return *this;
    }

    //plus unary
    Matrix operator+(Matrix &other){
        return (other * 1);
    }


    //-
    Matrix Matrix::operator-(const Matrix& other){
        if(this->rows != other.rows || this->cols != other.cols){
            throw invalid_argument("Matrices size should be identical");
        }
        vector<double> vec((size_t) (this->cols * this->rows));
        for(int i = 0; i < this->cols * this->rows; i++){
            vec.at((size_t) i) = (this->values.at((size_t) i) - other.values.at((size_t) i));
        }
        Matrix m_new(vec, this->rows, this->cols);
        return m_new;
    }

    //-=
    Matrix& Matrix::operator-=(const Matrix& other){
        if(this->rows != other.rows || this->cols != other.cols){
            throw invalid_argument("Matrices size should be identical");
        }
        for(int i = 0; i < this->cols * this->rows; i++){
            this->values.at((size_t) i) -= other.values.at((size_t) i);
        }
        return *this;
    }

    //minus unary
    Matrix operator-(Matrix &other){
        return (other * -1);
    }

    // >
    bool Matrix::operator>(Matrix& other){
        if(this->rows != other.rows || this->cols != other.cols){
            throw invalid_argument("Matrices size should be identical");
        }
        if((this->sum()) > other.sum()){
            return true;
        }
        return false;
    }

    // >=
    bool Matrix::operator>=(Matrix& other){
        if(this->rows != other.rows || this->cols != other.cols){
            throw invalid_argument("Matrices size should be identical");
        }
        if((this->sum()) >= other.sum()){
            return true;
        }
        return false;
    }

    //<
    bool Matrix::operator<(Matrix& other){
        if(this->rows != other.rows || this->cols != other.cols){
            throw invalid_argument("Matrices size should be identical");
        }
        if((this->sum()) < other.sum()){
            return true;
        }
        return false;
    }

    //<=
    bool Matrix::operator<=(Matrix& other){
        if(this->rows != other.rows || this->cols != other.cols){
            throw invalid_argument("Matrices size should be identical");
        }
        if((this->sum()) <= other.sum()){
            return true;
        }
        return false;
    }

    //==
    bool Matrix::operator==(Matrix& other){
        if(this->rows != other.rows || this->cols != other.cols){
            throw invalid_argument("Matrices size should be identical");
        }
        for(int i = 0; i < this->cols * this->rows; i++){
            if(this->values.at((size_t) i) != other.values.at((size_t) i)){
                return false;
            }
        }
        return true;
    }

    //!=
    bool Matrix::operator!=(Matrix& other){
        if(this->rows != other.rows || this->cols != other.cols){
            throw invalid_argument("Matrices size should be identical");
        }
        for(int i = 0; i < this->cols * this->rows; i++){
            if(this->values.at((size_t) i) != other.values.at((size_t) i)){
                return true;
            }
        }
        return false;
    }

    //++
    //++x
    Matrix& Matrix::operator++(){ //prefix
        for(int i = 0; i < this->cols * this->rows; i++){
            this->values.at((size_t) i) = (this->values.at((size_t) i) + 1);
        }
        return *this;
    }

    //x++ 
    Matrix Matrix::operator++(int num){ //postfix
        Matrix temp = *this * 1;
        for(int i = 0; i < this->cols * this->rows; i++){
            this->values.at((size_t) i) = (this->values.at((size_t) i) + 1);
        }
        return temp;
    }

    //--
    //--x
    Matrix& Matrix::operator--(){ //prefix
        for(int i = 0; i < this->cols * this->rows; i++){
            this->values.at((size_t) i) = (this->values.at((size_t) i) - 1);
        }
        return *this; 
    }

    //x--
    Matrix Matrix::operator--(int num){ //postfix
        Matrix temp = *this * 1;
        for(int i = 0; i < this->cols * this->rows; i++){
            this->values.at((size_t) i) = this->values.at((size_t) i) - 1;
        }
        return temp;
    }


    //* mat*num
    Matrix Matrix::operator*(double num){
        vector<double> vec((size_t) ((this->cols) * (this->rows)));
        for(int i = 0; i < vec.size(); i++){
            if(this->values.at((size_t) i) == 0) continue;

            vec.at((size_t) i) = this->values.at((size_t) i) * num;
        }
        Matrix m_new(vec, this->rows, this->cols);
        return m_new;
    }

    //* num*mat
    Matrix operator*(const double num, Matrix& mat){
        return (mat * num);
    }

    //*=
    Matrix& Matrix::operator*=(double num){
        for(int i = 0; i < this->cols * this->rows; i++){
            if(this->values.at((size_t) i) == 0) continue;

            this->values.at((size_t) i) = (this->values.at((size_t) i) * num);
        }
        return *this;
    }

    //*  mat*mat
    Matrix Matrix::operator*(const Matrix& other){
        if(this->cols != other.rows){
            throw invalid_argument("Cant multiply these matrices");
        }
        vector<double> vec((size_t) (this->rows * other.cols));
        for(int i = 0; i < this->rows; i++){
            for(int j = 0; j < other.cols; j++){
                double s = 0;
                for(int k = 0; k < this->cols; k++){
                    s += this->values.at((size_t) (i * this->cols + k)) * other.values.at((size_t) (j + k*other.cols));
                }
                vec.at((size_t) (i * other.cols + j)) = s;
            }
        }
        Matrix m_new(vec, this->rows, other.cols);
        return m_new;
    }

    //*=
    Matrix& Matrix::operator*=(const Matrix& other){
        if(this->cols != other.rows){
            throw invalid_argument("Cant multiply these matrices");
        }
        vector<double> vec((size_t) (this->rows * other.cols));
        for(int i = 0; i < this->rows; i++){
            for(int j = 0; j < other.cols; j++){
                double s = 0;
                for(int k = 0; k < this->cols; k++){
                    s += this->values.at((size_t)(i * this->cols + k)) * other.values.at((size_t)(j + k*other.cols));
                }
                vec.at((size_t) (i * other.cols + j)) = s;
            }
        }
        this->values = vec;
        this->cols = other.cols;
        return *this; 
    }


    //cout
    std::ostream& operator<< (std::ostream& output, const Matrix& mat){
        for (int i = 0; i < mat.rows; i++){
            output << '[';
            for (int j = 0; j < mat.cols; j++){
                output << mat.values[(size_t)(i * mat.cols + j)];
                
                if (j != mat.cols - 1){
                    output << ' ';
                }
            }
            output << "]\n";
        }
        return output;
    }

    //cin "[1 400 300], [1 8 2]\n"
    std::istream& operator>> (std::istream& input , Matrix& mat){
        // string s;
        // char c;
        // while(c != '\n'){
        //     c = input.get();
        //     s += c;
        // }
        // cout << s;

        return input;
    }
}