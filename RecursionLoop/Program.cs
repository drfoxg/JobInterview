using System;
class Program
{
    //
    // Вывода чисел от a до b с использованием рекурсивного алгоритма
    // Цикл for без ключевого слова for
    //
    static void Main(string[] args)
    {
        Loop(9, 19);

        Console.WriteLine("\n\nPress any key to quit...");
        Console.ReadKey();
    }
    static void Loop(int a, int b)
    {
        Console.Write($"Step {a} ");
        if (a < b) Loop(a + 1, b);
    }
}