using MySql.Data.MySqlClient;
using MySqlX.XDevAPI.Common;
using Org.BouncyCastle.Asn1.X509;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace JbmfgPartsDB
{
    internal class PartsDAO
    {
        //check port when moving to JBMFG computer
        string connectionString = "datasource=localhost;port=3306;username=root;password=root;database=jbmfg_parts;";

        public List<Part> getAllParts()
        {
            List<Part> returnTheseParts = new List<Part>();

            MySqlConnection connection = new MySqlConnection(connectionString);
            connection.Open();

            MySqlCommand command = new MySqlCommand("SELECT * FROM PARTS", connection);

            using(MySqlDataReader reader = command.ExecuteReader())
            {
                while (reader.Read())
                {
                    Part p = new Part 
                    { 
                        PartID = reader.GetString(0),
                        PDF = reader.GetString(1)
                    };
                    returnTheseParts.Add(p);
                }
            }
            connection.Close();

            return returnTheseParts;
        }

        public List<Part> searchPartNumbers(String searchTerm)
        {
            List<Part> returnTheseParts = new List<Part>();

            MySqlConnection connection = new MySqlConnection(connectionString);
            connection.Open();

            String searchThis = searchTerm + "%";

            MySqlCommand command = new MySqlCommand();

            command.CommandText = "SELECT * FROM PARTS WHERE PARTNUMBER LIKE @search";
            command.Parameters.AddWithValue("@search", searchThis);
            command.Connection = connection;


            using (MySqlDataReader reader = command.ExecuteReader())
            {
                while (reader.Read())
                {
                    Part p = new Part
                    {
                        PartID = reader.GetString(0),
                        PDF = reader.GetString(1)
                    };
                    returnTheseParts.Add(p);
                }
            }
            connection.Close();

            return returnTheseParts;
        }

        internal int addOnePart(Part part)
        {

            MySqlConnection connection = new MySqlConnection(connectionString);
            connection.Open();

            MySqlCommand command = new MySqlCommand("INSERT INTO `parts`(`PartNumber`, `PDF`) VALUES (@part, @pdf)", connection);
            command.Parameters.AddWithValue("@part", part.PartID);
            command.Parameters.AddWithValue("@pdf", part.PDF);
            int newRows = command.ExecuteNonQuery();

            connection.Close();

            return newRows;
        }

        public List<Order> getQuotes(String partNumber)
        {
            List<Order> returnTheseOrders = new List<Order>();

            MySqlConnection connection = new MySqlConnection(connectionString);
            connection.Open();

            MySqlCommand command = new MySqlCommand();

            command.CommandText = "SELECT parts_PartNumber as 'Part #', `Customer`, `Date`, `Quantity`, `UnitPrice`, orderID as 'Unit Price' FROM `quotesandinvoices` WHERE QuoteOrOrder = 0 AND parts_PartNumber = @partid";
            command.Parameters.AddWithValue("@partid", partNumber);
            command.Connection = connection;


            using (MySqlDataReader reader = command.ExecuteReader())
            {
                while (reader.Read())
                {
                    Order p = new Order()
                    {
                        PartID = reader.GetString(0),
                        Customer = reader.GetString(1),
                        Date = reader.GetDateTime(2),
                        Quantity = reader.GetInt32(3),
                        Price = reader.GetDouble(4),
                        ID = reader.GetInt32(5)
                    };
                    returnTheseOrders.Add(p);
                }
            }
            connection.Close();

            return returnTheseOrders;
        }
        public List<Order> getOrders(String partNumber)
        {
            List<Order> returnTheseOrders = new List<Order>();

            MySqlConnection connection = new MySqlConnection(connectionString);
            connection.Open();

            MySqlCommand command = new MySqlCommand();

            command.CommandText = "SELECT parts_PartNumber, `Customer`, `Date`, `Quantity`, `UnitPrice`, orderID FROM `quotesandinvoices` WHERE QuoteOrOrder = 1 AND parts_PartNumber = @partid";
            command.Parameters.AddWithValue("@partid", partNumber);
            command.Connection = connection;


            using (MySqlDataReader reader = command.ExecuteReader())
            {
                while (reader.Read())
                {
                    Order p = new Order()
                    {
                        PartID = reader.GetString(0),
                        Customer = reader.GetString(1),
                        Date = reader.GetDateTime(2),
                        Quantity = reader.GetInt32(3),
                        Price = reader.GetDouble(4),
                        ID = reader.GetInt32(5)
                    };
                    returnTheseOrders.Add(p);
                }
            }
            connection.Close();

            return returnTheseOrders;
        }
        public List<Order> getAllQuotes()
        {
            List<Order> returnTheseParts = new List<Order>();

            MySqlConnection connection = new MySqlConnection(connectionString);
            connection.Open();

            MySqlCommand command = new MySqlCommand("SELECT parts_PartNumber as 'Part #', `Customer`, `Date`, `Quantity`, `UnitPrice`, orderID as 'Unit Price' FROM `quotesandinvoices` WHERE QuoteOrOrder = 0 ORDER BY Date DESC", connection);

            using (MySqlDataReader reader = command.ExecuteReader())
            {
                while (reader.Read())
                {
                    Order p = new Order()
                    {
                        PartID = reader.GetString(0),
                        Customer = reader.GetString(1),
                        Date = reader.GetDateTime(2),
                        Quantity = reader.GetInt32(3),
                        Price = reader.GetDouble(4),
                        ID = reader.GetInt32(5)
                    };
                    returnTheseParts.Add(p);
                }
            }
            connection.Close();

            return returnTheseParts;
        }
        public List<Order> getAllOrders()
        {
            List<Order> returnTheseParts = new List<Order>();

            MySqlConnection connection = new MySqlConnection(connectionString);
            connection.Open();

            MySqlCommand command = new MySqlCommand("SELECT parts_PartNumber as 'Part #', `Customer`, `Date`, `Quantity`, `UnitPrice`, orderID as 'Unit Price' FROM `quotesandinvoices` WHERE QuoteOrOrder = 1 ORDER BY Date DESC", connection);

            using (MySqlDataReader reader = command.ExecuteReader())
            {
                while (reader.Read())
                {
                    Order p = new Order()
                    {
                        PartID = reader.GetString(0),
                        Customer = reader.GetString(1),
                        Date = reader.GetDateTime(2),
                        Quantity = reader.GetInt32(3),
                        Price = reader.GetDouble(4),
                        ID = reader.GetInt32(5)
                    };
                    returnTheseParts.Add(p);
                }
            }
            connection.Close();

            return returnTheseParts;
        }

        internal int verifyPartNumber(string part)
        {
            MySqlConnection connection = new MySqlConnection(connectionString);
            connection.Open();

            MySqlCommand command = new MySqlCommand();
            command.CommandText = "SELECT COUNT(*) FROM PARTS WHERE PARTNUMBER=@search";
            String searchTerm = part;
            command.Parameters.AddWithValue("@search", searchTerm);
            command.Connection = connection;

            int returnCheck = (int)(long)command.ExecuteScalar();

            connection.Close();

            return returnCheck;
        }

        internal int addOneOrder(Order order, int qoro)
        { 
            MySqlConnection connection = new MySqlConnection(connectionString);
            connection.Open();

            MySqlCommand command = new MySqlCommand("INSERT INTO `quotesandinvoices`(`Date`, Quantity, `UnitPrice`, `Customer`, `QuoteOrOrder`, `parts_PartNumber`) VALUES (@date, @quantity, @price, @customer, @qoro, @partNumber)", connection);
            DateTime temp = order.Date;
            String formDate = temp.ToString("yyyy-MM-dd");
            command.Parameters.AddWithValue("@date", formDate);
            command.Parameters.AddWithValue("@quantity", order.Quantity);
            command.Parameters.AddWithValue("@price", order.Price);
            command.Parameters.AddWithValue("@customer", order.Customer);
            command.Parameters.AddWithValue("@qoro", qoro);
            command.Parameters.AddWithValue("@partNumber", order.PartID);
            int newRows = command.ExecuteNonQuery();
            

            connection.Close();

            return newRows;
        }

        internal int verifyOrderNumber(string part)
        {
            MySqlConnection connection = new MySqlConnection(connectionString);
            connection.Open();

            MySqlCommand command = new MySqlCommand();
            command.CommandText = "SELECT COUNT(*) FROM QUOTESANDINVOICES WHERE orderID=@search";
            String searchTerm = part;
            command.Parameters.AddWithValue("@search", searchTerm);
            command.Connection = connection;

            int returnCheck = (int)(long)command.ExecuteScalar();

            connection.Close();

            return returnCheck;
        }

        internal void deleteOrder(string part)
        {
            MySqlConnection connection = new MySqlConnection(connectionString);
            connection.Open();

            MySqlCommand command = new MySqlCommand("DELETE FROM QUOTESANDINVOICES WHERE orderID=@quoteNumber", connection);
            String searchTerm = part;
            command.Parameters.AddWithValue("@quoteNumber", searchTerm);
            int newRows = command.ExecuteNonQuery();


            connection.Close();
        }

        internal void editPDFLocation(string part, string newLocation)
        {
            MySqlConnection connection = new MySqlConnection(connectionString);
            connection.Open();

            MySqlCommand command = new MySqlCommand("UPDATE `parts` SET `PDF`=@newLoc WHERE PartNumber=@partNumber", connection);
            String searchTerm = part;
            String searchTermPdf = newLocation;
            command.Parameters.AddWithValue("@partNumber", searchTerm);
            command.Parameters.AddWithValue("@newLoc", searchTermPdf);
            command.ExecuteNonQuery();


            connection.Close();
        }
    }
}
