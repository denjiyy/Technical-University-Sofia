using System;

public class SequenceCalculator
{
    public static int FindNthElementIterative(int n)
    {
        if (n <= 0)
        {
            throw new ArgumentException("n must be a positive integer.");
        }
        if (n == 1)
        {
            return 2;
        }
        if (n == 2)
        {
            return 4;
        }
        if (n == 3)
        {
            return 6;
        }

        int a1 = 2;
        int a2 = 4;
        int a3 = 6;
        int ai = 0;

        for (int i = 4; i <= n; i++)
        {
            ai = 3 * a1 + 4 * a2 - 7 * a3;
            a1 = a2;
            a2 = a3;
            a3 = ai;
        }

        return ai;
    }

    public static int FindNthElementRecursive(int n)
    {
        if (n <= 0)
        {
            throw new ArgumentException("n must be a positive integer.");
        }
        if (n == 1)
        {
            return 2;
        }
        if (n == 2)
        {
            return 4;
        }
        if (n == 3)
        {
            return 6;
        }

        return 3 * FindNthElementRecursive(n - 3) + 4 * FindNthElementRecursive(n - 2)
            - 7 * FindNthElementRecursive(n - 1);
    }

    public static void Main()
    {
        int n = int.Parse(Console.ReadLine()!);
        int nthElementIterative = FindNthElementIterative(n);
        int nthElementRecursive = FindNthElementRecursive(n);
        Console.WriteLine($"The {n}-th element of the sequence A is: {nthElementIterative} (Iterative)");
        Console.WriteLine($"The {n}-th element of the sequence A is: {nthElementRecursive} (Recursive)");
    }
}