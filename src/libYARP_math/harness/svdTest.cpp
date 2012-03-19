// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

/*
* Author: Lorenzo Natale
* Copyright (C) 2010 The Robotcub consortium.
* CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
*/


/**
 * \infile Tests for SVD.
 */

#include <yarp/os/impl/UnitTest.h>

#include <yarp/math/Math.h>
#include <yarp/sig/Vector.h>
#include <yarp/math/SVD.h>
#include <yarp/math/Rand.h>
#include <math.h>
#include <string>

using namespace yarp::os::impl;
using namespace yarp::sig;
using namespace yarp::math;
using namespace std;

const double TOL = 1e-8;

class SVDTest : public UnitTest {
public:
    virtual String getName() { return "SVDTest"; }

    // Assert that 2 matrices are equal
    void assertEqual(const Matrix &A, const Matrix &B, string testName, bool verbose=false)
    {
        if(A.cols() != B.cols() || A.rows()!=B.rows()){
            if(verbose) printf("A != B: %s != %s\n", A.toString(3).c_str(), B.toString(3).c_str());
            checkTrue(false, testName.c_str());
        }
        for(int r=0; r<A.rows(); r++){
            for(int c=0; c<A.cols(); c++){
                if(fabs(A(r,c)-B(r,c))>TOL){
                    if(verbose) printf("A != B: %s != %s\n", A.toString(3).c_str(), B.toString(3).c_str());
                    checkTrue(false, testName.c_str());
                }
            }
        }
        checkTrue(true, testName.c_str());
    }

    void svd()
    {
        report(0,"checking SVD of skinny matrix");

        int m=6, n=5, nTest=1;
        Matrix U(m,n), V(n,n);
        Vector s(n);
        Matrix S(n,n);

        for(int i=0;i<nTest;i++){
            Matrix M = Rand::matrix(m,n)*100;
            SVD(M, U, s, V);
            S.diagonal(s);
            Matrix T = U*S*V.transposed();
            assertEqual(T, M, "SVD decomposition of skinny matrix");
        }
    }

    void svdFat()
    {
        report(0,"checking SVD of fat matrix");

        int m=5, n=6, nTest=1;
        Matrix U(m,m), V(n,m);
        Vector s(m);
        Matrix S(m,m);

        for(int i=0;i<nTest;i++){
            Matrix M = Rand::matrix(m,n)*100;
            SVD(M, U, s, V);
            S.diagonal(s);
            Matrix T = U*S*V.transposed();
            assertEqual(T, M, "SVD decomposition of fat matrix");
        }
    }

    void pInv()
    {
        report(0, "checking pInv of skinny/square matrix");

        int m=6, n=5, nTest=1;
        Matrix M, Minv;
        for(int i=0; i<nTest; i++)
        {
            do{
                M = Rand::matrix(m,m);  // create a random nonsingular square matrix
            }while(fabs(det(M))<TOL);
            Minv = pinv(M, TOL);
            assertEqual(M*Minv, eye(m), "pinv of square nonsingular matrix");
        }

        Matrix U(m,n), V(n,n);
        Vector s(n);
        for(int i=0; i<nTest; i++)
        {
            do
            {
                M = Rand::matrix(m,n)*100;  // skinny full rank matrix
                SVD(M, U, s, V);
            }while(s[n-1] < TOL);
            Minv = pinv(M, TOL);
            assertEqual(Minv*M, eye(n), "pinv of full-rank skinny matrix");
        }
    }

    void pInvFat()
    {
        report(0, "checking pInv of fat matrix");
        int m=4, n=5, nTest=1;
        Matrix M, Minv;
        Matrix U(m,m), V(m,n);
        Vector s(m);
        for(int i=0; i<nTest; i++)
        {
            do
            {
                M = Rand::matrix(m,n)*100;  // skinny full rank matrix
                SVD(M, U, s, V);
            }while(s[m-1] < TOL);
            Minv = pinv(M, TOL);
            assertEqual(M*Minv, eye(m), "pinv of full-rank fat matrix");
        }
    }

    virtual void runTests() 
    {
        svd();
        svdFat();
        pInv();
        pInvFat();
    }
};

static SVDTest theSVDTest;

UnitTest& getSVDTest() {
    return theSVDTest;
}

