/*
 * Copyright (c) 2019 Tobias Briones.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include "SecantTest.h"

void Result::set(double root, double froot, int i, bool wasFound)
{
    this->root = root;
    this->froot = froot;
    this->iterations = i;
    this->wasFound = wasFound;
}

void testPolynomial(Polynomial& p, double a, double b, Result expected)
{
    bool rootFound;
    int i;
    double root = SecantMethodApp::compute(p, a, b, ERROR, THRESHOLD, rootFound, i);
    double froot = p.eval(root);
    bool passed = true;

    printf("Testing polynomial...\n");

    // If a root was found but there is actually no root for this call of the algorithm or
    // if there is a root but a root was not found by the algorithm
    // then the test is already failed
    if (rootFound != expected.wasFound)
    {
        printf("Different outcome, root found is %s but %s was expected\n", rootFound ? "true" : "false", expected.wasFound ? "true" : "false");
        passed = false;
    }

    // If a root was successfully found then test the results
    if (rootFound)
    {
        bool passedRoot = root == expected.root;
        bool passedFRoot = root == expected.froot;
        bool passedIterations = root == expected.iterations;
        passed &= passedRoot && passedFRoot && passedIterations;

        // If it didn't pass the previous tests, show the information
        if (!passed)
        {
            if (!passedRoot)
            {
                printf("Roots didn't pass, found: x = %f, expected x = %f\n", root, expected.root);
            }
            if (!passedFRoot)
            {
                printf("Images didn't pass, found P(x) = %f, expected P(x) = %f\n", froot, expected.froot);
            }
            if (!passedIterations)
            {
                printf("Number of iterations didn't pass, it had %d iterations, expected %d iterations\n", i, expected.iterations);
            }
        }
    }

    printf("Computation error was: %f, threshold: %d\n", ERROR, THRESHOLD);
    if (passed)
    {
        if (rootFound)
        {
            printf("Root at x = %f with P(x) = %f and %d iterations\n", root, froot, i);
        }
        else
        {
            printf("A root wasn't found. Finished with x = %f with P(x) = %f and %d iterations\n", root, froot, i);
        }
        printf("Test for P(x) = %s PASSED!\n", p.toString().c_str());
    }
    else
    {
        printf("Test for P(x) = %s FAILED\n", p.toString().c_str());
    }
    printf("\n");
    printf("\n");
}

void testForConstantPolynomials()
{
    double a;
    double b;
    Result expected;
    Polynomial p1(0);
    Polynomial p2(0);
    Polynomial p3(0);
    Polynomial p4(0);
    Polynomial p5(0);

    // P(x) = -20
    p1.setCoefficient(0, -20);
    expected.set(0, 0, 0, false);
    testPolynomial(p1, -1, 1, expected);
    
    // P(x) = -1
    p2.setCoefficient(0, -1);
    expected.set(0, 0, 0, false);
    testPolynomial(p2, -1, 1, expected);

    // P(x) = 0
    p3.setCoefficient(0, 0);
    expected.set(0, 0, 0, true);
    testPolynomial(p3, -1, 1, expected);

    // P(x) = 1
    p4.setCoefficient(0, 1);
    expected.set(0, 0, 0, false);
    testPolynomial(p4, -1, 1, expected);

    // P(x) = 20
    p5.setCoefficient(0, 20);
    expected.set(0, 0, 0, false);
    testPolynomial(p5, -1, 1, expected);
}

void testForGradeOnePolynomial()
{

}

void testForConstantMonomialZero()
{

}

void testForMixedPolynomial()
{

}

void testForPolynomialsWithDecimals()
{

}

void testForBigPolynomials()
{

}

void testForHugePolynomials()
{

}

void testForNonRootPolynomials()
{

}

void testForFarInitialValues()
{

}

void runAllTests()
{
    testForConstantPolynomials();
    testForGradeOnePolynomial();
    testForConstantMonomialZero();
    testForMixedPolynomial();
    testForPolynomialsWithDecimals();
    testForBigPolynomials();
    testForHugePolynomials();
    testForNonRootPolynomials();
    testForFarInitialValues();
}
