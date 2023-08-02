/*
 * Template JAVA User Interface
 * =============================
 *
 * Database Management Systems
 * Department of Computer Science &amp; Engineering
 * University of California - Riverside
 *
 * Target DBMS: 'Postgres'
 *
 */


import java.sql.DriverManager;
import java.sql.Connection;
import java.sql.Statement;
import java.sql.ResultSet;
import java.sql.ResultSetMetaData;
import java.sql.SQLException;
import java.io.File;
import java.io.FileReader;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.List;
import java.util.ArrayList;
import java.lang.Math;

/**
 * This class defines a simple embedded SQL utility class that is designed to
 * work with PostgreSQL JDBC drivers.
 *
 */
public class Retail {
	//public static int usID = 0;
   // reference to physical database connection.
   private Connection _connection = null;

   // handling the keyboard inputs through a BufferedReader
   // This variable can be global for convenience.
   static BufferedReader in = new BufferedReader(
                                new InputStreamReader(System.in));

   /**
    * Creates a new instance of Retail shop
    *
    * @param hostname the MySQL or PostgreSQL server hostname
    * @param database the name of the database
    * @param username the user name used to login to the database
    * @param password the user login password
    * @throws java.sql.SQLException when failed to make a connection.
    */
	static int usID=0;
   public Retail(String dbname, String dbport, String user, String passwd) throws SQLException {
      System.out.print("Connecting to database...");
      try{
         // constructs the connection URL
         String url = "jdbc:postgresql://localhost:" + dbport + "/" + dbname;
         System.out.println ("Connection URL: " + url + "\n");

         // obtain a physical connection
         this._connection = DriverManager.getConnection(url, user, passwd);
         System.out.println("Done");
      }catch (Exception e){
         System.err.println("Error - Unable to Connect to Database: " + e.getMessage() );
         System.out.println("Make sure you started postgres on this machine");
         System.exit(-1);
      }//end catch
   }//end Retail

   // Method to calculate euclidean distance between two latitude, longitude pairs. 
   public double calculateDistance (double lat1, double long1, double lat2, double long2){
      double t1 = (lat1 - lat2) * (lat1 - lat2);
      double t2 = (long1 - long2) * (long1 - long2);
      return Math.sqrt(t1 + t2); 
   }
   /**
    * Method to execute an update SQL statement.  Update SQL instructions
    * includes CREATE, INSERT, UPDATE, DELETE, and DROP.
    *
    * @param sql the input SQL string
    * @throws java.sql.SQLException when update failed
    */
   public void executeUpdate (String sql) throws SQLException {
      // creates a statement object
      Statement stmt = this._connection.createStatement ();

      // issues the update instruction
      stmt.executeUpdate (sql);

      // close the instruction
      stmt.close ();
   }//end executeUpdate

   /**
    * Method to execute an input query SQL instruction (i.e. SELECT).  This
    * method issues the query to the DBMS and outputs the results to
    * standard out.
    *
    * @param query the input query string
    * @return the number of rows returned
    * @throws java.sql.SQLException when failed to execute the query
    */
   public int executeQueryAndPrintResult (String query) throws SQLException {
      // creates a statement object
      Statement stmt = this._connection.createStatement ();

      // issues the query instruction
      ResultSet rs = stmt.executeQuery (query);

      /*
       ** obtains the metadata object for the returned result set.  The metadata
       ** contains row and column info.
       */
      ResultSetMetaData rsmd = rs.getMetaData ();
      int numCol = rsmd.getColumnCount ();
      int rowCount = 0;

      // iterates through the result set and output them to standard out.
      boolean outputHeader = true;
      while (rs.next()){
		 if(outputHeader){
			for(int i = 1; i <= numCol; i++){
			System.out.print(rsmd.getColumnName(i) + "\t");
			}
			System.out.println();
			outputHeader = false;
		 }
         for (int i=1; i<=numCol; ++i)
            System.out.print (rs.getString (i) + "\t");
         System.out.println ();
         ++rowCount;
      }//end while
      stmt.close ();
      return rowCount;
   }//end executeQuery

   /**
    * Method to execute an input query SQL instruction (i.e. SELECT).  This
    * method issues the query to the DBMS and returns the results as
    * a list of records. Each record in turn is a list of attribute values
    *
    * @param query the input query string
    * @return the query result as a list of records
    * @throws java.sql.SQLException when failed to execute the query
    */
   public List<List<String>> executeQueryAndReturnResult (String query) throws SQLException {
      // creates a statement object
      Statement stmt = this._connection.createStatement ();

      // issues the query instruction
      ResultSet rs = stmt.executeQuery (query);

      /*
       ** obtains the metadata object for the returned result set.  The metadata
       ** contains row and column info.
       */
      ResultSetMetaData rsmd = rs.getMetaData ();
      int numCol = rsmd.getColumnCount ();
      int rowCount = 0;

      // iterates through the result set and saves the data returned by the query.
      boolean outputHeader = false;
      List<List<String>> result  = new ArrayList<List<String>>();
      while (rs.next()){
        List<String> record = new ArrayList<String>();
		for (int i=1; i<=numCol; ++i)
			record.add(rs.getString (i));
        result.add(record);
      }//end while
      stmt.close ();
      return result;
   }//end executeQueryAndReturnResult

   /**
    * Method to execute an input query SQL instruction (i.e. SELECT).  This
    * method issues the query to the DBMS and returns the number of results
    *
    * @param query the input query string
    * @return the number of rows returned
    * @throws java.sql.SQLException when failed to execute the query
    */
   public int executeQuery (String query) throws SQLException {
       // creates a statement object
       Statement stmt = this._connection.createStatement ();

       // issues the query instruction
       ResultSet rs = stmt.executeQuery (query);

       int rowCount = 0;

       // iterates through the result set and count nuber of results.
       while (rs.next()){
          rowCount++;
       }//end while
       stmt.close ();
       return rowCount;
   }

   /**
    * Method to fetch the last value from sequence. This
    * method issues the query to the DBMS and returns the current
    * value of sequence used for autogenerated keys
    *
    * @param sequence name of the DB sequence
    * @return current value of a sequence
    * @throws java.sql.SQLException when failed to execute the query
    */
   public int getCurrSeqVal(String sequence) throws SQLException {
	Statement stmt = this._connection.createStatement ();

	ResultSet rs = stmt.executeQuery (String.format("Select currval('%s')", sequence));
	if (rs.next())
		return rs.getInt(1);
	return -1;
   }

   /**
    * Method to close the physical connection if it is open.
    */
   public void cleanup(){
      try{
         if (this._connection != null){
            this._connection.close ();
         }//end if
      }catch (SQLException e){
         // ignored.
      }//end try
   }//end cleanup

   /**
    * The main execution method
    *
    * @param args the command line arguments this inclues the <mysql|pgsql> <login file>
    */
   public static void main (String[] args) {
      if (args.length != 3) {
         System.err.println (
            "Usage: " +
            "java [-classpath <classpath>] " +
            Retail.class.getName () +
            " <dbname> <port> <user>");
         return;
      }//end if

      Greeting();
      Retail esql = null;
      try{
         // use postgres JDBC driver.
         Class.forName ("org.postgresql.Driver").newInstance ();
         // instantiate the Retail object and creates a physical
         // connection.
         String dbname = args[0];
         String dbport = args[1];
         String user = args[2];
         esql = new Retail (dbname, dbport, user, "");

         boolean keepon = true;
         while(keepon) {
            // These are sample SQL statements
            System.out.println("MAIN MENU");
            System.out.println("---------");
            System.out.println("1. Create user");
            System.out.println("2. Log in");
            System.out.println("9. < EXIT");
            String authorisedUser = null;
            switch (readChoice()){
               case 1: CreateUser(esql); break;
               case 2: authorisedUser = LogIn(esql); break;
               case 9: keepon = false; break;
               default : System.out.println("Unrecognized choice!"); break;
            }//end switch
            if (authorisedUser != null) {
              boolean usermenu = true;
              while(usermenu) {
                System.out.println("MAIN MENU");
                System.out.println("---------");
                System.out.println("1. View Stores within 30 miles");
                System.out.println("2. View Product List");
                System.out.println("3. Place a Order");
                System.out.println("4. View 5 recent orders");

                //the following functionalities basically used by managers
                System.out.println("5. Update Product/Users");
                //System.out.println("6. View 5 recent Product Updates Info");
                System.out.println("6. View 5 Popular Items");
                System.out.println("7. View 5 Popular Customers");
                System.out.println("8. Place Product Supply Request to Warehouse");
                System.out.println("9. View All Orders");

                System.out.println(".........................");
                System.out.println("20. Log out");
                switch (readChoice()){
                   case 1: viewStores(esql); break;
                   case 2: viewProducts(esql); break;
                   case 3: placeOrder(esql); break;
                   case 4: viewRecentOrders(esql); break;
                   case 5: updateProduct(esql); break;
                   //case 6: viewRecentUpdates(esql); break;
                   case 6: viewPopularProducts(esql); break;
                   case 7: viewPopularCustomers(esql); break;
                   case 8: placeProductSupplyRequests(esql); break;
                   case 9: viewAllOrders(esql); break;
                   case 20: usermenu = false; break;
                   default : System.out.println("Unrecognized choice!"); break;
                }
              }
            }
         }//end while
      }catch(Exception e) {
         System.err.println (e.getMessage ());
      }finally{
         // make sure to cleanup the created table and close the connection.
         try{
            if(esql != null) {
               System.out.print("Disconnecting from database...");
               esql.cleanup ();
               System.out.println("Done\n\nBye !");
            }//end if
         }catch (Exception e) {
            // ignored.
         }//end try
      }//end try
   }//end main

   public static void Greeting(){
      System.out.println(
         "\n\n*******************************************************\n" +
         "              User Interface      	               \n" +
         "*******************************************************\n");
   }//end Greeting

   /*
    * Reads the users choice given from the keyboard
    * @int
    **/
   public static int readChoice() {
      int input;
      // returns only if a correct value is given.
      do {
         System.out.print("Please make your choice: ");
         try { // read the integer, parse it and break.
            input = Integer.parseInt(in.readLine());
            break;
         }catch (Exception e) {
            System.out.println("Your input is invalid!");
            continue;
         }//end try
      }while (true);
      return input;
   }//end readChoice

   /*
    * Creates a new user
    **/
   public static void CreateUser(Retail esql){
      try{
         System.out.print("\tEnter name: ");
         String name = in.readLine();
         System.out.print("\tEnter password: ");
         String password = in.readLine();
         System.out.print("\tEnter latitude: ");   
         String latitude = in.readLine();       //enter lat value between [0.0, 100.0]
         System.out.print("\tEnter longitude: ");  //enter long value between [0.0, 100.0]
         String longitude = in.readLine();
         
         String type="Customer";

			String query = String.format("INSERT INTO USERS (name, password, latitude, longitude, type) VALUES ('%s','%s', %s, %s,'%s')", name, password, latitude, longitude, type);

         esql.executeUpdate(query);
         System.out.println ("User successfully created!");
      }catch(Exception e){
         System.err.println (e.getMessage ());
      }
   }//end CreateUser


   /*
    * Check log in credentials for an existing user
    * @return User login or null is the user does not exist
    **/
   public static String LogIn(Retail esql){
      try{
         System.out.print("\tEnter name: ");
         String name = in.readLine();
         System.out.print("\tEnter password: ");
         String password = in.readLine();

         String query = String.format("SELECT * FROM USERS WHERE name = '%s' AND password = '%s'", name, password);
         int userNum = esql.executeQuery(query);
	String query2 = String.format("SELECT userID FROM USERS WHERE name = '%s' AND password = '%s'", name, password);
	Retail.usID = Integer.parseInt(esql.executeQueryAndReturnResult(query2).get(0).get(0));
	//esql.executeQueryAndPrintResult(query2);
	 if (userNum > 0){
		//System.out.print(usID);
		return name;
         }else{
		return null;
	}
      }catch(Exception e){
         System.err.println (e.getMessage ());
         return null;
      }
   }//end

// Rest of the functions definition go in here

   public static void viewStores(Retail esql) {
	try{
		System.out.println("\tFinding stores within 30 miles");
		String query = String.format("SELECT * FROM STORE");
		int storeNum = esql.executeQuery(query);
		String tempID = String.valueOf(Retail.usID);
		String query1 = String.format("SELECT latitude FROM USERS WHERE userID = '%s'", tempID);
		String query2 = String.format("SELECT longitude FROM USERS WHERE userID = '%s'", tempID);
		double tempLat = Double.valueOf(esql.executeQueryAndReturnResult(query1).get(0).get(0));
		double tempLong = Double.valueOf(esql.executeQueryAndReturnResult(query2).get(0).get(0));
		//System.out.print("\t" + tempLat + " " + tempLong);
		for(int i = 1; i <= storeNum; i++){
			String query3 = String.format("SELECT latitude FROM STORE WHERE storeID = '%s'", i);
			String query4 = String.format("SELECT longitude FROM STORE WHERE storeID = '%s'", i);
			double storeLat = Double.valueOf(esql.executeQueryAndReturnResult(query3).get(0).get(0));
			double storeLong = Double.valueOf(esql.executeQueryAndReturnResult(query4).get(0).get(0));
			//System.out.println(storeLat + " " + storeLong + " " + tempLat + " " + tempLong);
			double distance = (esql.calculateDistance(tempLat, tempLong, storeLat, storeLong));
			//System.out.println(distance);
			if(distance < 30){
				String query5 = String.format("SELECT storeID, name FROM STORE WHERE storeID = '%s'", i);
				esql.executeQueryAndPrintResult(query5);
				//System.out.println(i);
			}
		}	
	}catch(Exception e){
		System.err.println(e.getMessage());
	}
}
   public static void viewProducts(Retail esql) {
   try{
	System.out.println("Store Names and IDs");
	String query1 = String.format("SELECT name, storeID FROM STORE");
	esql.executeQueryAndPrintResult(query1);
	System.out.println("\tEnter Store ID: ");
	String storeID = in.readLine();
	String query = String.format("SELECT * FROM PRODUCT WHERE storeID = '%s'", storeID);
	if(esql.executeQuery(query) == 0){
		System.out.println("Not a valid store ID");
		return;
	}
	esql.executeQueryAndPrintResult(query);
   }catch(Exception e){
	System.err.println (e.getMessage());
   }
}
   public static void placeOrder(Retail esql) {
   try{
	System.out.println("Place an Order");
	System.out.println("Stores in your area");
	viewStores(esql);
	System.out.println("Enter Store Number");
	String storeID = in.readLine();
	String query3 = String.format("SELECT * FROM STORE WHERE storeID = '%s'", storeID);
	int temp = esql.executeQuery(query3);
	if(temp == 0){
		System.out.println("Invalid Store Number");
		return;
	}
	System.out.println("Available Products");
	String query = String.format("SELECT * FROM PRODUCT WHERE storeID = '%s'", storeID);
	esql.executeQueryAndPrintResult(query);
	System.out.println("Enter Product Name");
	String prodName = in.readLine();
	String query4 = String.format("SELECT * FROM PRODUCT WHERE productName = '%s'", prodName);
	temp = esql.executeQuery(query4);
	if(temp == 0){
		System.out.println("Invalid Product Name");
		return;
	}
	System.out.println("Enter Number of Units");
	String unitNum = in.readLine();
	String query6 = String.format("SELECT * FROM PRODUCT WHERE productName = '%s' AND numberOfUnits >= '%s' AND storeID = '%s'", prodName, unitNum, storeID);
	temp = esql.executeQuery(query6);
	if(temp == 0){
		System.out.println("Not enough in inventory");
		return;
	}
	String query1 = String.format("SELECT * FROM ORDERS");
	String orderCount = String.valueOf(esql.executeQuery(query1)+1);
	//System.out.println(orderCount);
	String userIden = String.valueOf(Retail.usID);
	String query5 = String.format("INSERT INTO ORDERS (orderNumber, customerID, storeID, productName, unitsOrdered, orderTime) VALUES ('%s', '%s', '%s', '%s', '%s', NOW())", orderCount, userIden, storeID, prodName, unitNum);
   	esql.executeUpdate(query5);
	String query8 = String.format("SELECT numberOfUnits FROM PRODUCT WHERE storeID = '%s' AND productName = '%s'", storeID, prodName);
	String temp1 = esql.executeQueryAndReturnResult(query8).get(0).get(0);
	String temp2 = String.valueOf(Integer.valueOf(temp1) - Integer.valueOf(unitNum));
	//System.out.println(temp1);
	//System.out.println(unitNum);
	String query7 = String.format("UPDATE PRODUCT SET numberOfUnits = '%s' WHERE storeID = '%s' AND productName = '%s'", temp2, storeID, prodName);
	esql.executeUpdate(query7);
	System.out.println("Order Placed!");
   }catch(Exception e){
	System.err.println(e.getMessage());
   }
}
   public static void viewRecentOrders(Retail esql) {
   try{
	System.out.println("\tGetting your last 5 orders");
	String temp2 = String.valueOf(Retail.usID);
	String query = String.format("SELECT orders.storeID, store.name, orders.productName, orders.unitsOrdered, orders.orderTime FROM orders, store WHERE orders.customerID = '%s' AND orders.storeID = store.storeID Order By orderNumber DESC LIMIT 5", temp2);
	esql.executeQueryAndPrintResult(query);
   }catch(Exception e){
	System.err.println (e.getMessage());
   }
}
public static void updateProduct(Retail esql) {
   try{
	String temp = String.valueOf(Retail.usID);
	String query = String.format("SELECT type FROM USERS WHERE userID = '%s'",temp);
	String type = esql.executeQueryAndReturnResult(query).get(0).get(0);
	if(type.charAt(0) == 'c'){
		System.out.println("You do not have access to this feature");
		return;
	}
	if(type.charAt(0) == 'a'){
		System.out.println("To edit users press e, press any other key to edit products or view updates");
		String input = in.readLine();
		if(input.charAt(0) != 'e'){
	while(true){
      System.out.println("Store List:");
			String query1 = String.format("SELECT storeID, name FROM STORE");
      esql.executeQueryAndPrintResult(query1);
      System.out.println("Enter storeID to edit the products/view recent updates or any other character to exit");
      String storeID = in.readLine();
      String query3 = String.format("SELECT * FROM STORE WHERE storeID = '%s'", storeID);
      int t = esql.executeQuery(query3);
      if(t == 0){
        System.out.println("StoreID does not exist");
        return;
      }
      System.out.println("1 to view recent updates\n2 to edit products");
      String input2 = in.readLine();
      if(input2.charAt(0)=='1'){
        String query99 = String.format("SELECT * FROM productUpdates WHERE storeID = '%s' Order By updateNumber DESC LIMIT 5", storeID);
        esql.executeQueryAndPrintResult(query99);
      }else if(input2.charAt(0)=='2'){
      String query2 = String.format("SELECT * FROM PRODUCT WHERE storeID = '%s'", storeID);
      esql.executeQueryAndPrintResult(query2);
      System.out.println("Enter Product Name:");
      String tempProd = in.readLine();
      String query4 = String.format("SELECT * FROM PRODUCT WHERE storeID = '%s' AND productName = '%s'", storeID, tempProd);
      t = esql.executeQuery(query4);
      if(t == 0){
        System.out.println("Product does not exist");
        return;
      }
      
        System.out.println("Choose field to update \n1. numberOfUnits, \n2. pricePerUnit \n Any other key: Exit");
        String field = in.readLine();
        if(field.charAt(0)=='1'){
          System.out.println("Enter new number of units:");
          String newNum = in.readLine();
          System.out.println("Updating number of units");
          String query5 = String.format("UPDATE PRODUCT SET numberOfUnits = '%s' WHERE storeID = '%s' AND productName = '%s'", newNum, storeID, tempProd);
          esql.executeUpdate(query5);
          String query7 = String.format("SELECT * FROM productUpdates");
          int size = esql.executeQuery(query7)+1;
          String query6 = String.format("INSERT INTO productUpdates VALUES ('%s', '%s', '%s', '%s', NOW())", size, Retail.usID, storeID, tempProd);
          esql.executeUpdate(query6);
	}else if(field.charAt(0)=='2'){
          System.out.println("Enter new price:");
          String newPrice = in.readLine();
          System.out.println("Updating product price");
	       System.out.println(newPrice + storeID + tempProd);
          String query5 = String.format("UPDATE PRODUCT SET pricePerUnit = '%s' WHERE storeID = '%s' AND productName = '%s'", newPrice, storeID, tempProd);
          esql.executeUpdate(query5);
          String query7 = String.format("SELECT * FROM productUpdates");
          int size = esql.executeQuery(query7)+1;
          String query6 = String.format("INSERT INTO productUpdates VALUES ('%s', '%s', '%s', '%s', NOW())", size, Retail.usID, storeID, tempProd);
          esql.executeUpdate(query6);
        }else{
          System.out.println("Exiting");
          return;
        }
      }else{
        System.out.println("Not a valid input");
      }
    }
		}else{
			while(input != "t"){
			System.out.println("Enter userID to edit or press t to exit");
			String choice = in.readLine();
			if(choice == "t"){
				return;
			}
			String query2 = String.format("SELECT * FROM USERS WHERE userID = '%s'", choice);
			int check = esql.executeQuery(query2);
			if(check == 0){
				System.out.println("Not a valid user");
			}else{
				System.out.println("Select a field to edit");
				System.out.println("1. exit\n2. name\n3. password\n4. latitude\n5. longitude\n6. type\n7. view account info");
				String field = in.readLine();
				if(field.charAt(0) == '1'){
					return;
				}else if(field.charAt(0) == '2'){
					System.out.println("Enter new name");
					String newName = in.readLine();
					String query5 = String.format("UPDATE USERS SET name = '%s' WHERE userID = '%s'", newName, choice);
					esql.executeUpdate(query5);
					System.out.println("Name updated");
				}else if(field.charAt(0) == '3'){
					System.out.println("Enter new password");
					String newPass = in.readLine();
					String query6 = String.format("UPDATE USERS SET password = '%s' WHERE userID = '%s'", newPass, choice);
					esql.executeUpdate(query6);
					System.out.println("Password updated");
				}else if(field.charAt(0) == '4'){
					System.out.println("Enter new latitude");
					String newLat = in.readLine();
					String query7 = String.format("UPDATE USERS SET latitude = '%s' WHERE userID = '%s'", newLat, choice);
					esql.executeUpdate(query7);
					System.out.println("Latitude Updated");
				}else if(field.charAt(0) == '5'){
					System.out.println("Enter new longitude");
					String newLong = in.readLine();
					String query8 = String.format("UPDATE USERS SET longitude = '%s' WHERE userID = '%s'", newLong, choice);
					esql.executeUpdate(query8);
					System.out.println("Longitude updated");
				}else if(field.charAt(0) == '6'){
					System.out.println("Enter new type (admin, manager, customer)");
					String newType = in.readLine();
					if(newType.charAt(0) == 'a' || newType.charAt(0) == 'm' || newType.charAt(0) == 'c'){
						String query9 = String.format("UPDATE USERS SET type = '%s' WHERE userID = '%s'", newType, choice);
						esql.executeUpdate(query9);
					}else{
						System.out.println("Not a type");
					}
				}else if(field.charAt(0) == '7'){
					String query10 = String.format("SELECT * FROM USERS WHERE userID = '%s'", choice);
					esql.executeQueryAndPrintResult(query10);
				}else{
					return;
				}
			}
		}
		} 
	 }
	if(type.charAt(0) == 'm'){
	while(true){
	System.out.println("Store List:");
      String query1 = String.format("SELECT storeID, name FROM STORE WHERE managerID = '%s'", Retail.usID);
      esql.executeQueryAndPrintResult(query1);
      System.out.println("Enter storeID to edit the products or any other key to exit");
      String storeID = in.readLine();
      String query3 = String.format("SELECT * FROM STORE WHERE storeID = '%s' AND managerID = '%s'", storeID, Retail.usID);
      int t = esql.executeQuery(query3);
      if(t == 0){
        System.out.println("You are not a manager for selected store");
        return;
      }
      System.out.println("1 to view recent updates\n2 to edit products");
      String input2 = in.readLine();
      if(input2.charAt(0)=='1'){
        String query99 = String.format("SELECT * FROM productUpdates WHERE storeID = '%s' Order By updateNumber DESC LIMIT 5", storeID);
        esql.executeQueryAndPrintResult(query99);
      }else if(input2.charAt(0)=='2'){
      String query2 = String.format("SELECT * FROM PRODUCT WHERE storeID = '%s'", storeID);
      esql.executeQueryAndPrintResult(query2);
      System.out.println("Enter Product Name:");
      String tempProd = in.readLine();
      String query4 = String.format("SELECT * FROM PRODUCT WHERE storeID = '%s' AND productName = '%s'", storeID, tempProd);
      t = esql.executeQuery(query4);
      if(t == 0){
        System.out.println("Product does not exist");
        return;
      }
        System.out.println("Choose field to update \n1. numberOfUnits, \n2. pricePerUnit \n Any other key: Exit");
        String field = in.readLine();
        if(field.charAt(0)=='1'){
          System.out.println("Enter new number of units:");
          String newNum = in.readLine();
          System.out.println("Updating number of units");
          String query5 = String.format("UPDATE PRODUCT SET numberOfUnits = '%s' WHERE storeID = '%s' AND productName = '%s'", newNum, storeID, tempProd);
          esql.executeUpdate(query5);
          String query7 = String.format("SELECT * FROM productUpdates");
          int size = esql.executeQuery(query7)+1;
          String query6 = String.format("INSERT INTO productUpdates VALUES ('%s', '%s', '%s', '%s', NOW())", size, Retail.usID, storeID, tempProd);
          esql.executeUpdate(query6);
	}else if(field.charAt(0)=='2'){
          System.out.println("Enter new price:");
          String newPrice = in.readLine();
          System.out.println("Updating product price");
          String query5 = String.format("UPDATE PRODUCT SET pricePerUnit = '%s' WHERE storeID = '%s' AND productName = '%s'", newPrice, storeID, tempProd);
          esql.executeUpdate(query5);
          String query7 = String.format("SELECT * FROM productUpdates");
          int size = esql.executeQuery(query7)+1;
          String query6 = String.format("INSERT INTO productUpdates VALUES ('%s', '%s', '%s', '%s', NOW())", size, Retail.usID, storeID, tempProd);
          esql.executeUpdate(query6);
	}else{
          System.out.println("Exiting");
          return;
        }
      }
      }
	   }
   }catch(Exception e){
	System.err.println(e.getMessage());
   }
}
//   public static void viewRecentUpdates(Retail esql) {}
   public static void viewPopularProducts(Retail esql) {
    try{String temp = String.valueOf(Retail.usID);
    String query = String.format("SELECT type FROM USERS WHERE userID = '%s'",temp);
    String type = esql.executeQueryAndReturnResult(query).get(0).get(0);
    if(type.charAt(0) == 'c'){
      System.out.println("You do not have access to this feature");
      return;
    }else if(type.charAt(0) == 'm'){
      System.out.println("Store List:");
      String query1 = String.format("SELECT storeID, name FROM STORE WHERE managerID = '%s'", Retail.usID);
      esql.executeQueryAndPrintResult(query1);
      System.out.println("Enter storeID to view it's top 5 products or input any other key to exit");
      String storeID = in.readLine();
      String query3 = String.format("SELECT * FROM STORE WHERE storeID = '%s' AND managerID = '%s'", storeID, Retail.usID);
      int t = esql.executeQuery(query3);
      if(t == 0){
      System.out.println("You are not a manager for the selected store");
      return;
    }
      String query4 = String.format("SELECT productName, SUM(unitsOrdered) AS units_Ordered FROM Orders O WHERE O.storeID IN (SELECT P.storeID FROM Product P WHERE storeID = '%s') GROUP BY productName ORDER BY units_Ordered DESC LIMIT 5", storeID);
      esql.executeQueryAndPrintResult(query4);
    }else{
      System.out.println("Store List:");
      String query1 = String.format("SELECT storeID, name FROM STORE");
      esql.executeQueryAndPrintResult(query1);
      System.out.println("Enter storeID to view it's top 5 products or press any other key to exit");
      String storeID = in.readLine();
      String query3 = String.format("SELECT * FROM STORE WHERE storeID = '%s'", storeID);
      int t = esql.executeQuery(query3);
    if(t == 0){
      System.out.println("Selected store does not exist");
      return;
    }
      String query4 = String.format("SELECT productName, SUM(unitsOrdered) AS units_Ordered FROM Orders O WHERE O.storeID IN (SELECT P.storeID FROM Product P WHERE storeID = '%s') GROUP BY productName ORDER BY units_Ordered DESC LIMIT 5", storeID);
      esql.executeQueryAndPrintResult(query4);
    }
}catch(Exception e){
System.err.println(e.getMessage());
}
   }
   public static void viewPopularCustomers(Retail esql) {
try{
    String temp = String.valueOf(Retail.usID);
    String query = String.format("SELECT type FROM USERS WHERE userID = '%s'",temp);
    String type = esql.executeQueryAndReturnResult(query).get(0).get(0);
    if(type.charAt(0) == 'c'){
      System.out.println("You do not have access to this feature");
      return;
    }else if(type.charAt(0) == 'm'){
      System.out.println("Store List:");
      String query1 = String.format("SELECT storeID, name FROM STORE WHERE managerID = '%s'", Retail.usID);
      esql.executeQueryAndPrintResult(query1);
      System.out.println("Enter storeID to view it's top 5 customers or input any other key to exit");
      String storeID = in.readLine();
      String query3 = String.format("SELECT * FROM STORE WHERE storeID = '%s' AND managerID = '%s'", storeID, Retail.usID);
      int t = esql.executeQuery(query3);
    if(t == 0){
      System.out.println("You are not a manager for the selected store");
      return;
    }
      String query4 = String.format("SELECT COUNT(DISTINCT orderNumber) AS numberOfOrders, customerID FROM Orders O GROUP BY customerID ORDER BY numberOfOrders DESC LIMIT 5");
      esql.executeQueryAndPrintResult(query4);
    }else{
      System.out.println("Store List:");
      String query1 = String.format("SELECT storeID, name FROM STORE");
      esql.executeQueryAndPrintResult(query1);
      System.out.println("Enter storeID to view it's top 5 customers or press any other key to exit");
      String storeID = in.readLine();
      String query3 = String.format("SELECT * FROM STORE WHERE storeID = '%s'", storeID);
      int t = esql.executeQuery(query3);
    	if(t == 0){
      System.out.println("Selected store does not exist");
      return;
    }
    String query4 = String.format("SELECT COUNT(DISTINCT orderNumber) AS numberOfOrders, customerID FROM Orders O GROUP BY customerID ORDER BY numberOfOrders DESC LIMIT 5");
    esql.executeQueryAndPrintResult(query4);
    }
}catch(Exception e){
System.err.println(e);
}
   }
   public static void placeProductSupplyRequests(Retail esql) {try{
	String temp = String.valueOf(Retail.usID);
	String quer = String.format("SELECT type FROM USERS WHERE userID = '%s'", temp);
	String type = esql.executeQueryAndReturnResult(quer).get(0).get(0);
	if(type.charAt(0) == 'c'){
		System.out.println("You do not have access to this feature");
		return;
	}
        System.out.print("\tEnter Store ID: ");
        String storeID = in.readLine();
        System.out.print("\tPlease enter desired product: ");
        String productName = in.readLine();
        System.out.print("\tPlease enter requested amount: ");
        String unitsRequested = in.readLine();
        System.out.print("\tPlease enter Warehouse ID: ");
        String warehouseID = in.readLine();
        String query = String.format("UPDATE Product SET numberOfUnits=Product.numberOfUnits + '%s' WHERE storeID = '%s' AND productName = '%s'", unitsRequested, storeID, productName);
        String query9 = String.format("SELECT requestNumber FROM productSupplyRequests");
        int size = esql.executeQuery(query9)+1;
        String query10 = String.format("INSERT INTO productSupplyRequests VALUES('%s','%s','%s','%s','%s','%s')",size,Retail.usID,warehouseID,storeID,productName,unitsRequested);
        esql.executeUpdate(query10);
        esql.executeUpdate(query);
        }catch(Exception e){
        System.err.println (e.getMessage());
        }
}
   public static void viewAllOrders(Retail esql) {
try{
    String temp = String.valueOf(Retail.usID);
    String query = String.format("SELECT type FROM USERS WHERE userID = '%s'",temp);
    String type = esql.executeQueryAndReturnResult(query).get(0).get(0);
    if(type.charAt(0) == 'c'){
      System.out.println("You do not have access to this feature");
      return;
    }else if(type.charAt(0) == 'm'){
      System.out.println("Store List:");
      String query1 = String.format("SELECT storeID, name FROM STORE WHERE managerID = '%s'", Retail.usID);
      esql.executeQueryAndPrintResult(query1);
      System.out.println("Enter storeID view all order or any other key to exit");
      String storeID = in.readLine();
      String query3 = String.format("SELECT * FROM STORE WHERE storeID = '%s' AND managerID = '%s'", storeID, Retail.usID);
      int t = esql.executeQuery(query3);
      if(t == 0){
        System.out.println("You are not a manager for selected store");
        return;
      }
      String query4 = String.format("SELECT * FROM ORDERS WHERE storeID = '%s'", storeID);
      esql.executeQueryAndPrintResult(query4);
    }else{
      System.out.println("Store List:");
      String query1 = String.format("SELECT storeID, name FROM STORE");
      esql.executeQueryAndPrintResult(query1);
      System.out.println("Enter storeID view all order or any other key to exit");
      String storeID = in.readLine();
      String query3 = String.format("SELECT * FROM STORE WHERE storeID = '%s'", storeID);
      int t = esql.executeQuery(query3);
      if(t == 0){
        System.out.println("Selected store does not exist");
        return;
      }
      String query4 = String.format("SELECT * FROM ORDERS WHERE storeID = '%s'", storeID);
      esql.executeQueryAndPrintResult(query4);
    }
}catch(Exception e){
System.err.println(e.getMessage());
}
   }

}//end Retail

