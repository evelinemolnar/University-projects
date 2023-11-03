using System;
using System.Configuration;
using System.Data.SqlClient;
using System.Threading;

namespace lab4
{
    class Program
    {
        static string connectionString = "Server = eveline\\sqlexpress;Database=Hotels;Integrated Security = true; TrustServerCertificate=true;";
        static int noRetries = 2;

        static void Main(string[] args)
        {
            Thread t1 = new Thread(new ThreadStart(Transaction1));
            Thread t2 = new Thread(new ThreadStart(Transaction2));

            t1.Start(); t2.Start();
            t1.Join(); t2.Join();

            Console.ReadKey();
        }

        static void Transaction1()
        {
            int noTries = 0;
            while (!Transaction1_Run())
            {
                noTries++;
                if (noTries >= noRetries)
                    break;
            }
            if (noTries == noRetries)
                Console.WriteLine("Transaction 1 abort.");
        }

        static void Transaction2()
        {
            int noTries = 0;
            while (!Transaction2_Run())
            {
                noTries++;
                if (noTries >= noRetries)
                    break;
            }
            if (noTries == noRetries)
                Console.WriteLine("Transaction 2 abort.");
        }

        static bool Transaction1_Run()
        {
            bool success = false;

            Console.WriteLine("Transaction 1 start...");

            using (SqlConnection connection = new SqlConnection(connectionString))
            {
                SqlCommand command = connection.CreateCommand();
                try
                {
                    connection.Open();
                    command.Connection = connection;
                    command.CommandText = "EXECUTE Deadlock_T1_C#";
                    command.ExecuteNonQuery();
                    success = true;
                    Console.WriteLine("Transaction 1 completed!");
                }

                catch (SqlException ex)
                {
                    if (ex.Number == 1205)
                    {
                        Console.WriteLine("Transaction1: exception type: {0}", ex.GetType());
                        Console.WriteLine("Message: {0}", ex.Message);
                    }

                }
                return success;
            }
        }

        static bool Transaction2_Run()
        {
            bool success = false;

            Console.WriteLine("Transaction2 start...");

            using (SqlConnection connection = new SqlConnection(connectionString))
            {
                SqlCommand command = connection.CreateCommand();
                try
                {
                    connection.Open();
                    command.Connection = connection;
                    command.CommandText = "EXECUTE Deadlock_T2_C#";
                    command.ExecuteNonQuery();
                    success = true;
                    Console.WriteLine("Transaction 2 completed!");
                }

                catch (SqlException ex)
                {
                    if (ex.Number == 1205)
                    {
                        Console.WriteLine("Transaction2: exception type: {0}", ex.GetType());
                        Console.WriteLine("Message: {0}", ex.Message);
                    }

                }
                return success;
            }
        }
    }
}