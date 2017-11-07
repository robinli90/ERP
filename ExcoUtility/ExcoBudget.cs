using System;
using System.Collections.Generic;
using System.Linq;
using System.IO;
using System.Text;
using System.Data.Odbc;

namespace ExcoUtility
{
    public class ExcoBudget
    {
        // can only have one instance
        // load budgets when created initially
        private static ExcoBudget instance;

        public static ExcoBudget Instance
        {
            get
            {
                if (null == instance)
                {
                    instance = new ExcoBudget();
                }
                return instance;
            }
        }

        private ExcoBudget()
        {
        }

        public double GetMonthlyBudget(ExcoCustomer customer, int plant, ExcoCalendar calendar)
        {
            double value = 0.0;
            try
            {
                if (1 == plant)
                {
                    ExcoODBC database = ExcoODBC.Instance;
                    database.Open(Database.DECADE_MARKHAM);
                    string query = "select Period" + calendar.GetFiscalMonth().ToString("D2") + " from tiger.dbo.Markham_Budget where Year=20" + calendar.GetFiscalYear().ToString("D2") + " and CustomerID='" + customer.BillToID + "'";
                    OdbcDataReader reader = database.RunQuery(query);
                    if (reader.Read())
                    {
                        value = Convert.ToDouble(reader[0]);
                        reader.Close();
                    }
                    else
                    {
                        reader.Close();
                        query = "select Period" + calendar.GetFiscalMonth().ToString("D2") + "from tiger.dbo.Markham_Budget where Year=20" + calendar.GetFiscalYear().ToString("D2") + " and CustomerID='" + customer.ShipToID + "'";
                        reader = database.RunQuery(query);
                        if (reader.Read())
                        {
                            value = Convert.ToDouble(reader[0]);
                            reader.Close();
                        }
                        else
                        {
                            reader.Close();
                            query = "select Period" + calendar.GetFiscalMonth().ToString("D2") + "from tiger.dbo.Markham_Budget where Year=20" + calendar.GetFiscalYear().ToString("D2") + " and CustomerID='" + customer.SillyID + "'";
                            reader = database.RunQuery(query);
                            if (reader.Read())
                            {
                                value = Convert.ToDouble(reader[0]);
                            }
                            reader.Close();
                        }
                    }
                }
                else if (3 == plant)
                {
                    ExcoODBC database = ExcoODBC.Instance;
                    database.Open(Database.DECADE_MARKHAM);
                    string query = "select Period" + calendar.GetFiscalMonth().ToString("D2") + " from tiger.dbo.Michigan_Budget where Year=20" + calendar.GetFiscalYear().ToString("D2") + " and CustomerID='" + customer.BillToID + "'";
                    OdbcDataReader reader = database.RunQuery(query);
                    if (reader.Read())
                    {
                        value = Convert.ToDouble(reader[0]);
                        reader.Close();
                    }
                    else
                    {
                        reader.Close();
                        query = "select Period" + calendar.GetFiscalMonth().ToString("D2") + "from tiger.dbo.Michigan_Budget where Year=20" + calendar.GetFiscalYear().ToString("D2") + " and CustomerID='" + customer.ShipToID + "'";
                        reader = database.RunQuery(query);
                        if (reader.Read())
                        {
                            value = Convert.ToDouble(reader[0]);
                            reader.Close();
                        }
                        else
                        {
                            reader.Close();
                            query = "select Period" + calendar.GetFiscalMonth().ToString("D2") + "from tiger.dbo.Michigan_Budget where Year=20" + calendar.GetFiscalYear().ToString("D2") + " and CustomerID='" + customer.SillyID + "'";
                            reader = database.RunQuery(query);
                            if (reader.Read())
                            {
                                value = Convert.ToDouble(reader[0]);
                            }
                            reader.Close();
                        }
                    }
                }
                else if (5 == plant)
                {
                    ExcoODBC database = ExcoODBC.Instance;
                    database.Open(Database.DECADE_MARKHAM);
                    string query = "select Period" + calendar.GetFiscalMonth().ToString("D2") + " from tiger.dbo.Texas_Budget where Year=20" + calendar.GetFiscalYear().ToString("D2") + " and CustomerID='" + customer.BillToID + "'";
                    OdbcDataReader reader = database.RunQuery(query);
                    if (reader.Read())
                    {
                        value = Convert.ToDouble(reader[0]);
                        reader.Close();
                    }
                    else
                    {
                        reader.Close();
                        query = "select Period" + calendar.GetFiscalMonth().ToString("D2") + "from tiger.dbo.Texas_Budget where Year=20" + calendar.GetFiscalYear().ToString("D2") + " and CustomerID='" + customer.ShipToID + "'";
                        reader = database.RunQuery(query);
                        if (reader.Read())
                        {
                            value = Convert.ToDouble(reader[0]);
                            reader.Close();
                        }
                        else
                        {
                            reader.Close();
                            query = "select Period" + calendar.GetFiscalMonth().ToString("D2") + "from tiger.dbo.Texas_Budget where Year=20" + calendar.GetFiscalYear().ToString("D2") + " and CustomerID='" + customer.SillyID + "'";
                            reader = database.RunQuery(query);
                            if (reader.Read())
                            {
                                value = Convert.ToDouble(reader[0]);
                            }
                            reader.Close();
                        }
                    }
                }
                else if (4 == plant)
                {
                    int year;
                    int period;
                    if (calendar.GetFiscalMonth() >= 10)
                    {
                        year = calendar.GetFiscalYear() + 1;
                        period = calendar.GetFiscalMonth() - 9;
                    }
                    else
                    {
                        year = calendar.GetFiscalYear();
                        period = calendar.GetFiscalMonth() + 3;
                    }
                    ExcoODBC database = ExcoODBC.Instance;
                    database.Open(Database.DECADE_MARKHAM);
                    string query = "select Period" + period.ToString("D2") + " from tiger.dbo.Colombia_Budget where Year=20" + year.ToString("D2") + " and CustomerID='" + customer.BillToID + "'";
                    OdbcDataReader reader = database.RunQuery(query);
                    if (reader.Read())
                    {
                        value = Convert.ToDouble(reader[0]);
                        reader.Close();
                    }
                    else
                    {
                        reader.Close();
                        query = "select Period" + period.ToString("D2") + "from tiger.dbo.Colombia_Budget where Year=20" + year.ToString("D2") + " and CustomerID='" + customer.ShipToID + "'";
                        reader = database.RunQuery(query);
                        if (reader.Read())
                        {
                            value = Convert.ToDouble(reader[0]);
                            reader.Close();
                        }
                        else
                        {
                            reader.Close();
                            query = "select Period" + period.ToString("D2") + "from tiger.dbo.Colombia_Budget where Year=20" + year.ToString("D2") + " and CustomerID='" + customer.SillyID + "'";
                            reader = database.RunQuery(query);
                            if (reader.Read())
                            {
                                value = Convert.ToDouble(reader[0]);
                            }
                            reader.Close();
                        }
                    }
                }
            }
            catch
            {
                return 0.0;
            }
            return value;
        }
    }
}
