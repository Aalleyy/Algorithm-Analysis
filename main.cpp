#include <iostream>
#include <vector>
#include <chrono> // for timing

using namespace std;

using chrono::duration;
using chrono::duration_cast;
using chrono::high_resolution_clock;
using chrono::microseconds;
using chrono::milliseconds;

int max(int a, int b, int c)
{
    if (a >= b && a >= c)
        return a;
    if (b >= a && b >= c)
        return b;
    if (c >= a && c >= b)
        return c;

    return 0;
}

// Algorithm #01 - Simple
// Tries all possibilities - Brute Force
int maxSubSum1(const vector<int> &a)
{
    int maxSum = 0;

    for (int i = 0; i < a.size(); i++)
        for (int j = i; j < a.size(); j++)
        {
            int thisSum = 0;

            for (int k = i; k <= j; k++)
                thisSum += a[k];

            if (thisSum > maxSum)
                maxSum = thisSum;
        }
    return maxSum;
}

// Algorithm #02 - Improved
int maxSubSum2(const vector<int> &a)
{
    int maxSum = 0;
    for (int i = 0; i < a.size(); i++)
    {
        int thisSum = 0;
        for (int j = i; j < a.size(); j++)
        {
            thisSum += a[j];
            if (thisSum > maxSum)
                maxSum = thisSum;
        }
    }
    return maxSum;
}

// Algorithm #03 - Divide and Conquer
int maxSubSum3(const vector<int> &a, int left, int right)
{
    if (left == right)
        return a[left];
    else
    {
        int mid = (left + right) / 2;
        int maxLeft = maxSubSum3(a, left, mid);
        int maxRight = maxSubSum3(a, mid + 1, right);
        int maxLeftBorder = 0, leftBorder = 0;
        for (int i = mid; i >= left; i--)
        {
            leftBorder += a[i];
            if (leftBorder > maxLeftBorder)
                maxLeftBorder = leftBorder;
        }
        // same for the right
        int maxRightBorder = 0, rightBorder = 0;
        for (int i = mid + 1; i <= right; i++)
        {
            rightBorder += a[i];
            if (rightBorder > maxRightBorder)
                maxRightBorder = rightBorder;
        }
        return max(maxLeft, maxRight, maxLeftBorder + maxRightBorder);
    }
}

int main()
{
    cout << "Subsequence Sum Algorithm Running-Time Analysis\n\n";

    int n[6] = {3000, 3500, 4000, 4500, 5000, 5500};
    for (int attempt = 0; attempt < 3; attempt++)
    {
        cout << "\t\t\tAttempt No:" << attempt + 1 << endl
             << endl;
        for (int test = 0; test < 6; test++)
        {
            vector<int> data(n[test]);

            // Random Number Generator
            srand(time(0));
            for (int i = 0; i <= n[test]; i++)
            {
                data[i] = rand() % 201 - 100; //generating random number between -100 and 100
            }

            cout << "For N = " << n[test] << endl
                 << endl;

            // Running Algorithm #01 - Brute Force

            auto t1 = high_resolution_clock::now();
            maxSubSum1(data);
            auto t2 = high_resolution_clock::now();

            auto ms_int_1 = duration_cast<milliseconds>(t2 - t1);
            duration<double, milli> ms_double_1 = t2 - t1;

            // Running Algorithm #02 - Improved

            t1 = high_resolution_clock::now();
            maxSubSum2(data);
            t2 = high_resolution_clock::now();

            auto ms_int_2 = duration_cast<milliseconds>(t2 - t1);
            duration<double, milli> ms_double_2 = t2 - t1;

            // Running Algorithm #03 - Divide and Conquer

            t1 = high_resolution_clock::now();
            maxSubSum3(data, 0, n[test]);
            t2 = high_resolution_clock::now();

            auto ms_int_3 = duration_cast<milliseconds>(t2 - t1);
            duration<double, milli> ms_double_3 = t2 - t1;

            // Running-Time of Algorithm Result

            cout << "Time taken by Algorithm #01 - Brute Force:\t\t" << ms_int_1.count() << " ms\t" << ms_double_1.count() << " ms\n";
            cout << "Time taken by Algorithm #02 - Improved:\t\t\t" << ms_int_2.count() << " ms\t\t" << ms_double_2.count() << " ms\n";
            cout << "Time taken by Algorithm #03 - Divide and Conquer:\t" << ms_int_3.count() << " ms\t\t" << ms_double_3.count() << " ms\n\n";
        }
    }
}
