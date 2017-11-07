using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Data.Odbc;

namespace InvoiceGenerator
{
    public enum Database
    {
        NULL,
        CMSDAT,
        PRODTEST,
        DECADE_MARKHAM,
        DECADE_MICHIGAN,
        DECADE_TEXAS,
        DECADE_COLOMBIA,
        TIGER_MARKHAM
    }

    /// <summary>
    /// ExcoODBC intends to manage all database connections via ODBC.
    /// Using singleton pattern.
    /// </summary>

    public class ExcoODBC
    {
        internal OdbcConnection connection;
        internal OdbcCommand command;
        internal string connectionString;
        internal Database database;
        internal static ExcoODBC instance;
        internal string dbName;
        internal string user = string.Empty;
        internal string password = string.Empty;

        public string DbName
        {
            get
            {
                return dbName;
            }
        }

        public string ConnectionString
        {
            get
            {
                return connectionString;
            }
        }

        public static ExcoODBC Instance
        {
            get
            {
                if (null == instance)
                {
                    instance = new ExcoODBC();
                }
                return instance;
            }
        }

        internal ExcoODBC() { }

        // be able to open and swith database connections
        public void Open(Database database)
        {
            // open db when designating with another arguments
            if (this.database != database)
            {
                this.database = database;
                switch (database)
                {
                    case Database.CMSDAT:
                        user = "JXU";//user = "ZWANG";
                        password = "qwpo555";//password = "ZWANG";
                        connectionString = "Driver={iSeries Access ODBC Driver};Name=cms1;System=10.0.0.35;Uid=" + user + ";Pwd=" + password + ";";
                        dbName = "cmsdat";
                        break;
                    case Database.PRODTEST:
                        user = "JXU";//user = "ZWANG";
                        password = "qwpo555";//password = "ZWANG";
                        connectionString = "Driver={iSeries Access ODBC Driver};Name=cms1;System=10.0.0.35;Uid=" + user + ";Pwd=" + password + ";";
                        dbName = "prodtest";
                        break;
                    case Database.DECADE_MARKHAM:
                        user = "jamie";
                        password = "jamie";
                        connectionString = "Driver={SQL Server};Server=10.0.0.6;Uid=" + user + ";Pwd=" + password + ";";
                        dbName = "dbo";
                        break;
                    case Database.DECADE_MICHIGAN:
                        user = "jamie";
                        password = "jamie";
                        connectionString = "Driver={SQL Server};Server=192.168.1.7;Uid=" + user + ";Pwd=" + password + ";";
                        dbName = "dbo";
                        break;
                    case Database.DECADE_TEXAS:
                        user = "jamie";
                        password = "jamie";
                        connectionString = "Driver={SQL Server};Server=192.168.12.7;Uid=" + user + ";Pwd=" + password + ";";
                        dbName = "dbo";
                        break;
                    case Database.DECADE_COLOMBIA:
                        user = "jamie";
                        password = "jamie";
                        connectionString = "Driver={SQL Server};Server=192.168.101.7;Uid=" + user + ";Pwd=" + password + ";";
                        dbName = "dbo";
                        break;
                    case Database.TIGER_MARKHAM:
                        user = "jamie";
                        password = "jamie";
                        connectionString = "Driver={SQL Server};Server=10.0.0.6;Uid=" + user + ";Pwd=" + password + ";";
                        dbName = "tiger";
                        break;
                    default:
                        throw new Exception("Unhandled database!");
                }

                if (null == connection)
                {
                    connection = new OdbcConnection(connectionString);
                }
                else
                {
                    connection.Close();
                    connection.ConnectionString = connectionString;
                }
                //connection.ConnectionTimeout = int.MaxValue;
                connection.Open();
                if (null == command)
                {
                    command = new OdbcCommand();
                }
                command.Connection = connection;
                command.CommandTimeout = 0;
            }
        }

        public OdbcDataReader RunQuery(string query)
        {
            try
            {
                // adjust database for testing
                if (Database.PRODTEST == database)
                {
                    query = query.Replace("cmsdat", "prodtest");
                }
                command = new OdbcCommand();
                command.Connection = connection;
                command.CommandTimeout = 0;
                command.CommandText = query;
                return command.ExecuteReader();
            }
            catch (Exception exception)
            {
                throw exception;
            }
        }

        public int RunQueryWithoutReader(string query)
        {
            try
            {
                // adjust database for testing
                if (Database.PRODTEST == database)
                {
                    query = query.Replace("cmsdat", "prodtest");
                }
                command = new OdbcCommand();
                command.Connection = connection;
                command.CommandTimeout = 0;
                command.CommandText = query;
                return command.ExecuteNonQuery();
            }
            catch (Exception exception)
            {
                throw exception;
            }
        }
    }
}
