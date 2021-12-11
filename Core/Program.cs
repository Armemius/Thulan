using System;

namespace Thulan
{
    public class Program
    {
        public static void Main(string[] args)
        {
            try
            {
                Translator.Program.main();
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.ToString());
            }
        }
    }
}