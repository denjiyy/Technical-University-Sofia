using System;

class Program
{
    private static int Recursive(int x)
    {
        if (x == 0) return 0;
        if (x % 2 == 0) return 1 + Recursive(x / 2);
        else return 1 + Recursive(x * 3 + 1);
    }

    private static int Iterative(int x)
    {
        int count = 0;

        if (x == 1) return 0;

        while (x != 1)
        {
            if (x % 2 == 0)
                x /= x;
            else
                x = x * 3 + 1;
            count++;
        }

        return count;
    }

    static void Main(string[] args)
    {
        Console.Write("Enter a number: ");
        int n = int.Parse(Console.ReadLine()!);

        Console.WriteLine($"Recursive: {Recursive(n)}");
        Console.WriteLine($"Iterative: {Iterative(n)}");

        Console.ReadLine();
    }
}