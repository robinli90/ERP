using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Data.Odbc;
using System.IO;

namespace copy_solarsoft_to_mysql
{

    string table = "<h2>Welcome to the HTML editor!</h2> <p>Just type the HTML and it will be shown below.</p><p>Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed elementum neque id magna. Mauris sollicitudin nisi sit amet sem. Etiam sit amet lectus a velit interdum facilisis. Vestibulum ante ipsum primis in faucibus orci <strong>luctus et ultrices posuere</strong> cubilia Curae; In tincidunt eleifend neque. Maecenas interdum, neque in fringilla pellentesque, lacus massa eleifend elit, nec scelerisque nulla orci a nunc. Quisque sollicitudin. Sed pulvinar lacus id lacus. Vestibulum imperdiet tellus eget risus. Quisque libero nisl, feugiat<strong>\"+UserName+\"</strong><br />\"+Salary+\" $ are credited to your account for March payout\"+\"<br > you can find breakup below <table><tr><td>BLAH BLAH BLAH</td></tr></table> eu, euismod at, elementum eget, tellus. <a href=\"http://www.clesto.com\">Clesto.com</a></p> <img src=\"http://www.google.se/images/google_80wht.gif\" alt=\"Google logo\"><h2>Heading in h2, som more sample text</h2><p>Phasellus sem odio, varius quis, cursus at, ullamcorper eget, turpis. Maecenas a mi. Mauris dignissim lectus malesuada odio. Duis elit arcu, lobortis ut, porta ac, venenatis ornare, odio. Pellentesque scelerisque. Ut elementum laoreet massa. Suspendisse hendrerit odio eget turpis. Cras tellus dui, malesuada id, adipiscing ut, laoreet sed, magna. Phasellus scelerisque aliquet ligula. Quisque vitae elit sit amet enim suscipit interdum. Curabitur laoreet, mauris sit amet aliquet interdum, pede sapien malesuada metus, in tincidunt turpis justo id arcu. Donec gravida odio ac lectus. Nam rutrum ante in nisi laoreet aliquet. Sed at ante.</p><h3>Heading in h3, som more sample text</h3><p>Nulla facilisi. Nullam cursus scelerisque erat. Praesent convallis rhoncus dui. In hac habitasse platea dictumst. Nullam pellentesque. Mauris ac orci. Donec dictum. Etiam purus tortor, elementum a, posuere nec, pulvinar id, ipsum. Pellentesque habitant morbi tristique senectus et netus et malesuada fames ac turpis egestas. Quisque vel justo. Nullam posuere purus sed arcu.</p><ul><li>Nulla facilisi.</li><li>Pellentesque habitant morbi</li><li>Quisque vel justo.</li><li>Nullam posuere purus sed arcu.</li></ul>";

    class Program
    {
        static void CopySolarsoft()
        {
            // input
            string[] tables = File.ReadAllLines("list.txt");
            // search
            string mysqlConnStr = "Driver={MySQL ODBC 5.2a Driver};Server=.;Database=solarsoft;User=root;pwd=;option=3;";
            string solarsoftConnStr = "Driver={iSeries Access ODBC Driver};Name=cms1;System=10.0.0.35;Uid=JXU;Pwd=qwpo555;";//Uid=ZWANG;Pwd=ZWANG;";
            OdbcConnection mysqlConn = new OdbcConnection(mysqlConnStr);
            OdbcConnection solarsoftConn = new OdbcConnection(solarsoftConnStr);
            mysqlConn.Open();
            solarsoftConn.Open();
            foreach (string table in tables)
            {
                string solarsoftQuery = "select * from cmsdat.";
                solarsoftQuery += table;
                OdbcCommand solarsoftCom = new OdbcCommand(solarsoftQuery, solarsoftConn);
                OdbcDataReader solarsoftReader = solarsoftCom.ExecuteReader();
                // create tables in mysql
                string mysqlQuery = "create table " + table + " (";
                OdbcCommand mysqlCom = new OdbcCommand(mysqlQuery, mysqlConn);
                for (int i = 1; i < solarsoftReader.FieldCount; i++)
                {
                    mysqlQuery += table + i.ToString() + " TEXT, ";
                }
                mysqlQuery += table + solarsoftReader.FieldCount.ToString() + " TEXT)";
                mysqlCom.CommandText = mysqlQuery;
                mysqlCom.ExecuteNonQuery();
                while (solarsoftReader.Read())
                {
                    mysqlQuery = "insert into " + table + " values ('";
                    for (int i = 0; i < solarsoftReader.FieldCount - 1; i++)
                    {
                        if (solarsoftReader.HasRows)
                        {
                            string value = solarsoftReader[i].ToString();
                            value = value.Replace("\\", " ");
                            value = value.Trim();
                            value = value.Replace("'", "''");
                            value = value.Replace("´", "''");
                            mysqlQuery += value + "', '";
                        }
                    }
                    string lastValue = solarsoftReader[solarsoftReader.FieldCount - 1].ToString();
                    lastValue = lastValue.Replace("\\", " ");
                    lastValue = lastValue.Trim();
                    lastValue = lastValue.Replace("'", "''");
                    lastValue = lastValue.Replace("´", "''");
                    mysqlQuery += lastValue + "')";
                    mysqlCom.CommandText = mysqlQuery;
                    mysqlCom.ExecuteNonQuery();
                }
            }
            mysqlConn.Close();
            solarsoftConn.Close();
        }

        static void CopyDecade()
        {
            // search
            string mysqlConnStr = "Driver={MySQL ODBC 5.2a Driver};Server=.;Database=solarsoft;User=root;pwd=;option=3;";
            string decadeConnStr = "Driver={SQL Server Native Client 10.0};Server=10.0.0.6;Uid=jamie;Pwd=jamie;";
            OdbcConnection mysqlConn = new OdbcConnection(mysqlConnStr);
            OdbcConnection decadeConn = new OdbcConnection(decadeConnStr);
            mysqlConn.Open();
            decadeConn.Open();
            string decadeQuery = "select * from dbo.d_task where tasktime>'2012-01-01 00:00:00.000'";
            OdbcCommand decadeCom = new OdbcCommand(decadeQuery, decadeConn);
            OdbcDataReader decadeReader = decadeCom.ExecuteReader();
            // create tables in mysql
            string mysqlQuery = "create table decade.d_task (id int, ordernumber int, employeenumber int, task varchar(2), part varchar(1), subpart varchar(1), station varchar(5), tasktime varchar(32), flags int, runtime varchar(32))";
            OdbcCommand mysqlCom = new OdbcCommand(mysqlQuery, mysqlConn);
            mysqlCom.ExecuteNonQuery();
            while (decadeReader.Read())
            {
                mysqlQuery = "insert into decade.d_task values ('";
                for (int i = 0; i < decadeReader.FieldCount - 1; i++)
                {
                    if (decadeReader.HasRows)
                    {
                        string value = decadeReader[i].ToString();
                        value = value.Trim();
                        mysqlQuery += value + "', '";
                    }
                }
                string lastValue = decadeReader[decadeReader.FieldCount - 1].ToString();
                lastValue = lastValue.Trim();
                mysqlQuery += lastValue + "')";
                mysqlCom.CommandText = mysqlQuery;
                mysqlCom.ExecuteNonQuery();
            }
            mysqlConn.Close();
            decadeConn.Close();
        }

        static void Main(string[] args)
        {
            //CopySolarsoft();
            CopyDecade();
        }
    }
}
