/**
 * Tests for Matrix.cpp
 *
 * AUTHOR: Moriah David
 * 
 * Date: 2022-04
 */

#include <sstream>
#include "doctest.h"
#include "Matrix.hpp"
using namespace zich;
using namespace std;

// #include <string>


// GOOD INPUT
//~~~~~~~~~~~~

TEST_CASE("good input(+, +=, unary+, -, -=, unary-)"){

    vector<double> identity = {1, 0, 0, 0, 1, 0, 0, 0, 1};
    Matrix m1{identity, 3, 3};

    vector<double> v2 = {0, 1, 1, 1, 0, 1, 1, 1, 0};
    Matrix m2{v2, 3, 3};

    vector<double> v3 = {1, 1, 1, 1, 1, 1, 1, 1, 1};
    Matrix m3{v3, 3, 3}; //for+

    vector<double> v4 = {1, -1, -1, -1, 1, -1, -1, -1, 1};
    Matrix m4{v4, 3, 3}; //for- (1-2)

    vector<double> v5 = {-1, 0, 0, 0, -1, 0, 0, 0, -1};
    Matrix m5{v5, 3, 3};

    //+
    CHECK(((m1 + m2) == m3) == true);

    //+=
    m1 += m2;
    CHECK((m1 == m3) == true);
    m1 = Matrix{identity, 3, 3};  // constructor taking a vector and a matrix size

    //plus unary
    CHECK((+m1 == m1) == true);

    //-
    CHECK(((m1 - m2) == m4) == true);

    //minus unary
    CHECK((-m1 == m5) == true);

    //-=
    m1 -= m2;
    CHECK((m1 == m4) == true);

}

TEST_CASE("good input(> >=, <, <=, ==, !=)"){

    vector<double> identity = {1, 0, 0, 0, 1, 0, 0, 0, 1};
    Matrix m1{identity, 3, 3};

    vector<double> v2 = {0, 1, 0, 0, 1, 0, 0, 0, 1};
    Matrix m2{v2, 3, 3};
    
    vector<double> v4 = {1, 0, 0, 0, 1, 0, 0, 0, 1};
    Matrix m4{v4, 3, 3};

    vector<double> v5 = {0, 1, 2, 3, 4, 5, 6, 7, 8};
    Matrix m5{v5, 3, 3};
    

    // >
    CHECK((m5 > m1) == true);

    // >=
    CHECK((m1 >= m5) == false);
    CHECK((m1 >= m2) == true);

    //<
    CHECK((m1 < m5) == true);

    //<=
    CHECK((m5 <= m1) == false);
    CHECK((m1 <= m2) == true);

    //==
    CHECK((m1 == m4) == true);

    //!=
    CHECK((m1 != m5) == true);
    CHECK((m1 != m4) == false);
}

TEST_CASE("good input(x++, ++x, x--, --x)"){

    vector<double> identity = {1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0};
    Matrix m1{identity, 4, 3};

    vector<double> v2 = {2, 1, 1, 1, 2, 1, 1, 1, 2, 1, 1, 1};
    Matrix m2{v2, 4, 3};

    vector<double> v3 = {0, -1, -1, -1, 0, -1, -1, -1, 0, -1, -1, -1};
    Matrix m3{v3, 4, 3};

    vector<double> v4 = {1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0};
    Matrix m4{v4, 4, 3};

    //++
    //postfix
    CHECK((m1++ == m4) == true);
    CHECK((m1 == m2) == true);

    m1 = Matrix(identity, 4, 3);

    //prefix
    CHECK((++m1 == m2) == true);
    CHECK((m1 == m2) == true);

    m1 = Matrix(identity, 4, 3);

    //--
    //postfix
    CHECK((m1-- == m4) == true);
    CHECK((m1 == m3) == true);

    m1 = Matrix{identity, 4, 3};

    //prefix
    CHECK((++m1 == m2) == true);
    CHECK((m1 == m2) == true);
}

TEST_CASE("good input(*, *= mat&mat and mat&num)"){

    vector<double> identity = {1, 0, 0, 0, 1, 0, 0, 0, 1};
    Matrix m1{identity, 3, 3};

    vector<double> v2 = {2, 4, 1, 0, 1, 3, 4, 6, 1};
    Matrix m2{v2, 3, 3};

    vector<double> v3 = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};
    Matrix m3{v3, 3, 5};

    vector<double> v4 = {30, 37, 44, 51, 58, 35, 39, 43, 47, 51, 40, 51, 62, 73, 84};
    Matrix m4{v4, 3, 5}; //m2*m3

    vector<double> v5 = {0, 1, 2, 3, 4, 5, 6, 7, 8};
    Matrix m5{v5, 3, 3};

    vector<double> v6 = {18, 25, 32, 21, 25, 29, 24, 35, 46};
    Matrix m6{v6, 3, 3}; // m2*m5

    vector<double> v7 = {10, 20, 5, 0, 5, 15, 20, 30, 5};
    Matrix m7{v7, 3, 3}; // 5*m2

    //* mat*num
    CHECK(((m2 * 5) == m7) == true);

    //* num*mat
    CHECK(((5 * m2) == m7) == true);


    //*  mat*mat
    CHECK(((m1 * m5) == m5) == true);
    CHECK(((m5 * m1) == m5) == true);
    CHECK(((m2 * m5) == m6) == true);
    CHECK(((m2 * m3) == m4) == true);// diff mat sizes

    //*= mat*num
    m2 *= 5;
    CHECK((m2 == m7) == true);

    //*= mat*mat
    m1 *= m5;
    CHECK((m1 == m5) == true);

    m2 = Matrix{v2, 3, 3};
    m2 *= m5;
    CHECK((m2 == m6) == true);

    m2 = Matrix{v2, 3, 3};
    m2 *= m3;
    CHECK((m2 == m4) == true);// diff mat sizes

}

TEST_CASE("good input(cin and cout)"){

    vector<double> v1 = {0, 1, 2, 3, 4, 5, 6, 7, 8};
    Matrix m1{v1, 3, 3};
    vector<double> v2 = {0, 1, 2, 3, 4, 5, 6, 7};
    Matrix m2{v2, 2, 4};
    vector<double> v3 = {1, 0, 0, 0, 1, 0, 0, 0, 1};
    Matrix m3{v3, 3, 3};

    //cin
    // stringstream ss("[0 1 2], [3 4 5], [6 7 8]\n");
    // ss >> m3;
    // CHECK((m1 == m3) == true);

    //cout
    stringstream ss1;
    ss1 << m1;
    CHECK(ss1.str() == "[0 1 2]\n[3 4 5]\n[6 7 8]\n");

    stringstream ss2;
    ss2 << m2;
    CHECK(ss2.str() == "[0 1 2 3]\n[4 5 6 7]\n");
}



// BAD INPUT
//~~~~~~~~~~

TEST_CASE("bad input(+, +=, unary+, -, -=, unary-)"){

    vector<double> identity = {1, 0, 0, 0, 1, 0, 0, 0, 1};
    Matrix m1{identity, 3, 3};

    vector<double> v2 = {0, 1, 1, 1, 0, 1, 1, 1, 0};
    Matrix m2{v2, 3, 3};

    vector<double> v3 = {1, 1, 1, 1, 1, 1, 1, 1, 1};
    Matrix m3{v3, 3, 3}; //for+

    vector<double> v4 = {1, -1, -1, -1, 1, -1, -1, -1, 1};
    Matrix m4{v4, 3, 3}; //for- (1-2)

    vector<double> v5 = {0, 1, 2, 3, 4, 5, 6, 7, 8};
    Matrix m5{v5, 3, 3};

    vector<double> v6 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};
    Matrix m6{v6, 5, 2};

    //+
    CHECK_THROWS(m1 + m6);

    //+=
    CHECK_THROWS(m1 += m6);

    //plus unary


    //-
    CHECK_THROWS(m1 - m6);

    //-=
    CHECK_THROWS(m1 -= m6);

    //minus unary
}

TEST_CASE("bad input(> >=, <, <=, ==, !=)"){
    
    vector<double> identity = {1, 0, 0, 0, 1, 0, 0, 0, 1};
    Matrix m1{identity, 3, 3};

    vector<double> v3 = {1, 1, 1, 1, 1, 1, 1, 1, 1};
    Matrix m3{v3, 3, 3}; //for+

    vector<double> v6 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};
    Matrix m6{v6, 5, 2};

    // >
    CHECK_THROWS(if(m1 > m6){}); //diff size of mat

    // >=
    CHECK_THROWS(if(m1 >= m6){});

    //<
    CHECK_THROWS(if(m1 < m6){});

    //<=
    CHECK_THROWS(if(m1 <= m6));

    //==
    CHECK_THROWS(if(m1 == m6));

    //!=
    CHECK_THROWS(if(m1 != m6));
}

TEST_CASE("bad input(*, *= mat&mat and mat&num)"){

    vector<double> v5 = {0, 1, 2, 3, 4, 5, 6, 7, 8};
    Matrix m5{v5, 3, 3};

    vector<double> v6 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};
    Matrix m6{v6, 5, 2};

    //*  mat*mat
    CHECK_THROWS(m5 * m6);

    //*=
    CHECK_THROWS(m5 *= m6);
}

TEST_CASE("bad input(create)"){

    vector<double> v1 = {0, 1, 2, 3, 4, 5, 6, 7, 8};
    
    CHECK_THROWS(Matrix m1(v1, 2, 3));
}

TEST_CASE("bad input(cin and cout)"){
    //cin
    //cout
}
