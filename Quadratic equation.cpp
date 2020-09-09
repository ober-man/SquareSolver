/**This program find solutions
 *of the quadratic equation
 */

#include <stdio.h>
#include <math.h>
#include <assert.h>

const int INF = -100;     /// if equation has infinite number of roots
const int ERR = -1;       /// error in function
const double EPS = 1e-15; /// very small numeral
const int MAXTRIES = 100; /// max number of attempts of enter
const int MAXCOEFF = 3; /// max number of coefficients

int SolveSquare(double a, double b, double c, double *x1, double  *x2);
int SolveLinear(double b, double c, double *x);
int Compare(double param, double num);
void Fill(double array[], int len, double number);
void Input(const char text[], double data[], size_t size);


int main()
{
    printf("# Square equation solver\n");
    printf("# (c)Oberman Igor, 28.08.2019\n\n");

    double coeff[MAXCOEFF] = {};
    Fill(coeff, MAXCOEFF, NAN);

    /**Entry coefficients of equation**/
    Input("Enter coefficients", coeff, MAXCOEFF);

    double a = coeff[0], b = coeff[1], c = coeff[2];

    /**The solutions**/
    double x1 = NAN, x2 = NAN;

    /**Number of solutions**/
    int num = SolveSquare(a, b, c, &x1, &x2);
    switch (num)
    {
    case 0:
        printf("Equation hasn't got solutions");
        break;
    case 1:
        printf("Equation has 1 solutions: %lg", x1);
        break;
    case 2:
        printf("Equation has 2 solutions: %lg and %lg", x1, x2);
        break;
    case INF:
        printf("Any numeral is solution of this equation");
        break;
    default:
        printf("Error: %d solutions", num);
        break;
    }
    return 0;
}

//----------------------------------------------------
//! Function "SolveSquare" find solutions
//! of the quadratic equation
//! like ax^2 + bx + c = 0
//!
//!@param [in] a a-coefficient
//!@param [in] b b-coefficient
//!@param [in] c c-coefficient
//!@param [out] x1 First solution
//!@param [out] x2 Second solution
//!
//!@return Number of solutions
//!
//!@note If equation has infinite number of solutions,
//!      the function will return INF = -100
//!@note If there is an error,
//!      the function will return ERR = -1
//----------------------------------------------------
int SolveSquare(double a, double b, double c, double *x1, double *x2)
{
    /**Checking correctness of entry**/
    assert(isfinite(a));
    assert(isfinite(b));
    assert(isfinite(c));
    assert(x1 != NULL);
    assert(x2 != NULL);
    assert(x1 != x2);

    if (Compare(a, 0) == 0)
    {
        return SolveLinear(b, c, x1);
    }
    /**a != 0, any b, c**/
    else if (Compare(b, 0) == 0)
            if (Compare(c, 0) == 0)
            {
                *x1 = 0;
                return 1;
            }
            else /**c != 0**/
            {
                if (Compare(-c/a, 0) == 1)
                {
                    *x1 = sqrt(-c / a);
                    return 1;
                }
                else return 0;
            }
    /**a!= 0, b != 0, any c**/
    else if (Compare(c, 0) == 0)
    {
        *x1 = 0;
        int num = SolveLinear(a, b, x2);
        if(num == INF)
            return INF;
        else
            return num + 1;
    }

    /**Discriminant**/
    double d = b * b - 4 * a * c;
    if (Compare(d, 0) == 1) /**Discriminant > 0**/
    {
        double root = sqrt(d);

        /**Two solutions:**/
        *x1 = (-b + root) / 2 / a;
        *x2 = (-b - root) / 2 / a;
        return 2;
    }
    else if (Compare(d, 0) == 0) /**Discriminant = 0**/
    {
        /**One solution:**/
        *x1 = -b / 2 / a;
        return 1;
    }
    else
        return 0; /**No solutions, discriminant < 0**/

    return ERR; /**Error**/
}

//----------------------------------------
//! Function "SolveLinear" find solutions
//! of the linear equation
//! like ax + b = 0
//!
//!@param [in] a a-coefficient
//!@param [in] b b-coefficient
//!@param [out] x Solution
//!
//!@return Number of solutions
//!
//!@note If there is an error,
//!      the function will return ERR = -1
//----------------------------------------
int SolveLinear(double a, double b, double *x)
{
    /**Checking correctness of entry**/
    assert(isfinite(a));
    assert(isfinite(b));
    assert(x != NULL);

    if (Compare(a, 0) == 0)
        if (Compare(b, 0) == 0)
            return INF;
        else /**a = 0, b != 0**/
            return 0; /**No solution**/
    else if(b == 0)/**a != 0, b = 0**/
    {
        *x = 0;
        return 1;
    }
    else /**a != 0, b = 0**/
    {
        /**One solution**/
        *x = -b / a;
        return 1;
    }
    return ERR;
}

//---------------------------------------------------------
//! Function "Compare" compares parameter with some numeral
//!
//!@param [in] param Parameter comparing with numeral
//!@param [in] num Numeral
//!
//!@return 0, if param = numeral
//!        1, if param > numeral
//!       -1, if param < numeral
//---------------------------------------------------------
int Compare(double param, double num)
{
    /**Checking correctness of entry**/
    assert(isfinite(param));
    assert(isfinite(num));
    if(param >= num + EPS)
        return 1;
    if(param < num - EPS)
        return -1;
    else
        return 0;
}

//-----------------------------------------------------
//! Function "Fill" get equal numbers in array
//!
//!@param [in] array Array we are working with
//!@param [in] len Number of elements in array
//!@param [in] number Number what will contain in array
//!
//!@note For the best using recommends number = NAN
//-----------------------------------------------------
void Fill(double array[], int len, double number)
{
    /**Checking correctness of entry**/
    assert(isfinite(len));
    assert(array != NULL);

    for(int i = 0; i < len; ++i)
    {
        array[i] = number;
    }
    return;
}

//-------------------------------------------------------------------
//! Function "Input" enter coefficients of equation you want to solve
//!
//!@param [in] text[] Phrase to user
//!@param [in] data[] Array we are working with
//!@param [in] size Number of elements in array
//!
//!@note You have only MAXTRIES attempts to enter coefficients
//-------------------------------------------------------------------
void Input(const char text[], double data[], size_t size)
{
    /**Checking correctness of entry**/
    assert(isfinite(size));
    assert(text != NULL);
    assert(data != NULL);

    int i = 0, j = 0;
    printf("%s\n", text);
    while(true)
    {
        /**The coefficients:**/
        for(j = 0; j < size; ++j)
        {
            if (scanf("%lg", &data[j]) == 1)
                continue;
            else
            {
                printf("Wrong entry\n");
                printf("Try again\n");
                break;
            }
        }
        fflush(stdin);//clear buffer
        if(j == size)///All coefficients were entered correctly
            break;
    }
    if (i == MAXTRIES)
        printf("Your entry is wrong and attempts to enter have been over\n");
    return;
}
