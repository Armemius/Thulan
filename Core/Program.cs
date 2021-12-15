using System;

namespace Thulan
{
    public class Program
    {
        public static void Main(string[] args)
        {
            try
            {
                Translator.Program.parseFile(@"C:\My Files\Sus\Thulan\Translator\Source.txt");
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.ToString());
            }
        }
    }
}