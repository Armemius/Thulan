using System;

namespace Thulan
{
    public class Program
    {
        public static void Main(string[] args)
        {
            try
            {
                var tokens = Translator.Lexic.parseFile(@"C:\My Files\Sus\Thulan\Translator\Source.txt");
                Auxiliary.Syntactic.check(tokens);
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.ToString());
            }
        }
    }
}