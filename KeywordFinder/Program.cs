using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ExcoUtility;
using System.Data.Odbc;
using System.IO;

namespace KeywordFinder
{
    class Program
    {
        private static List<string> tableList = new List<string>();

        private static void FillTableList()
        {
            tableList.Add("ADRS");
            tableList.Add("ALTMDA");
            tableList.Add("ALTMDM");
            tableList.Add("ALTMDR");
            tableList.Add("ALTMH");
            tableList.Add("ALTMOP");
            tableList.Add("APBT");
            tableList.Add("APPL");
            tableList.Add("APVB");
            tableList.Add("APVD");
            tableList.Add("APVH");
            tableList.Add("APVHT");
            tableList.Add("ARCHQ");
            tableList.Add("ARCSHA");
            tableList.Add("ARCSHB");
            tableList.Add("ARCSHC");
            tableList.Add("ARCSHG");
            tableList.Add("ARMASA");
            tableList.Add("ARMASB");
            tableList.Add("ARMASC");
            tableList.Add("ARNSFA");
            tableList.Add("AROHT");
            tableList.Add("AROP");
            tableList.Add("AROPA");
            tableList.Add("AROPE");
            tableList.Add("AROPT");
            tableList.Add("ARTRN");
            tableList.Add("AVGCSTX");
            tableList.Add("AVTX");
            tableList.Add("BCDM");
            tableList.Add("BLRV");
            tableList.Add("BM311WF");
            tableList.Add("BOLA");
            tableList.Add("BOLD");
            tableList.Add("BOLF");
            tableList.Add("BOLH");
            tableList.Add("B13H");
            tableList.Add("B13HX");
            tableList.Add("CBCR");
            tableList.Add("CCLT");
            tableList.Add("CCRD");
            tableList.Add("CCRF");
            tableList.Add("CCRH");
            tableList.Add("CCRI");
            tableList.Add("CCRIE");
            tableList.Add("CCRP");
            tableList.Add("CCRS");
            tableList.Add("CHQR");
            tableList.Add("CIFDFT");
            tableList.Add("CIFGRP");
            tableList.Add("CIFM");
            tableList.Add("CJOBDM");
            tableList.Add("CJOBDR");
            tableList.Add("CJOBH");
            tableList.Add("CJOBOP");
            tableList.Add("CNTC");
            tableList.Add("CNTE");
            tableList.Add("CNTT");
            tableList.Add("CODE");
            tableList.Add("CONT");
            tableList.Add("CORG");
            tableList.Add("CRAI");
            tableList.Add("CREX");
            tableList.Add("CRSV");
            tableList.Add("CRZT");
            tableList.Add("CSPT");
            tableList.Add("CSTB");
            tableList.Add("CSTP");
            tableList.Add("CSTPE");
            tableList.Add("CURPRO");
            tableList.Add("CUST");
            tableList.Add("CUSTMAIL");
            tableList.Add("DEPTS");
            tableList.Add("DOSLABEL");
            tableList.Add("DPSF");
            tableList.Add("DSDISC");
            tableList.Add("DSGRAS");
            tableList.Add("EBNK");
            tableList.Add("EFMT");
            tableList.Add("EFTBD");
            tableList.Add("EFTBH");
            tableList.Add("FGADJ");
            tableList.Add("FGRP");
            tableList.Add("FGWIP");
            tableList.Add("FIRM");
            tableList.Add("FOCL");
            tableList.Add("FOCM");
            tableList.Add("FOMF");
            tableList.Add("FOMH");
            tableList.Add("FOMO");
            tableList.Add("FOOD");
            tableList.Add("FOOH");
            tableList.Add("FRT");
            tableList.Add("GLCCOM");
            tableList.Add("GLCDEP");
            tableList.Add("GLCM");
            tableList.Add("GLCPD");
            tableList.Add("GLCPH");
            tableList.Add("GLCS");
            tableList.Add("GLDATE");
            tableList.Add("GLDATREF");
            tableList.Add("GLDEL");
            tableList.Add("GLFPA");
            tableList.Add("GLIE");
            tableList.Add("GLMC");
            tableList.Add("GLMT");
            tableList.Add("GLSBAP");
            tableList.Add("GLSBAR");
            tableList.Add("GLSBIV");
            tableList.Add("GLSDIS");
            tableList.Add("GTLYN");
            tableList.Add("GTRAN");
            tableList.Add("HISPRO");
            tableList.Add("HJOBDM");
            tableList.Add("HJOBDR");
            tableList.Add("HJOBH");
            tableList.Add("HJOBOP");
            tableList.Add("HLYSHP");
            tableList.Add("HOLIDY");
            tableList.Add("HSTR");
            tableList.Add("ICPL");
            tableList.Add("ICRZ");
            tableList.Add("ICSTM");
            tableList.Add("ICSTP");
            tableList.Add("ICSTT");
            tableList.Add("ICSTTID");
            tableList.Add("ICSTTW");
            tableList.Add("IMAS");
            tableList.Add("INDLBR");
            tableList.Add("INGL");
            tableList.Add("INQRT");
            tableList.Add("INVA");
            tableList.Add("IPRCA");
            tableList.Add("IPRCB");
            tableList.Add("IPRCC");
            tableList.Add("IPRCCT");
            tableList.Add("IPRCCTN");
            tableList.Add("IPRCCTO");
            tableList.Add("IREA");
            tableList.Add("JCSTA");
            tableList.Add("JCSTB");
            tableList.Add("JCSTM");
            tableList.Add("JCSTT");
            tableList.Add("JOBLOG");
            tableList.Add("JRNA");
            tableList.Add("JRNB");
            tableList.Add("JRNC");
            tableList.Add("KYRTR");
            tableList.Add("LBDT");
            tableList.Add("LBFD");
            tableList.Add("LBFG");
            tableList.Add("LBFM");
            tableList.Add("LBFMX");
            tableList.Add("LBFP");
            tableList.Add("LBFV");
            tableList.Add("LBMS");
            tableList.Add("LBPT");
            tableList.Add("LBWP");
            tableList.Add("LOTM");
            tableList.Add("MAJG");
            tableList.Add("MAST");
            tableList.Add("METHDA");
            tableList.Add("METHDM");
            tableList.Add("METHDR");
            tableList.Add("METHH");
            tableList.Add("METHOP");
            tableList.Add("MMGP");
            tableList.Add("MMSL");
            tableList.Add("MNUL");
            tableList.Add("MNUM");
            tableList.Add("MNUN");
            tableList.Add("MPS1");
            tableList.Add("MRPNET");
            tableList.Add("MSTCON");
            tableList.Add("MSVD");
            tableList.Add("MTDMH");
            tableList.Add("NAME");
            tableList.Add("NEGACCW");
            tableList.Add("OCMD");
            tableList.Add("OCMF");
            tableList.Add("OCMH");
            tableList.Add("OCMI");
            tableList.Add("OCMIE");
            tableList.Add("OCMP");
            tableList.Add("OCMS");
            tableList.Add("OCODE");
            tableList.Add("OCRD");
            tableList.Add("OCRF");
            tableList.Add("OCRH");
            tableList.Add("OCRHE");
            tableList.Add("OCRI");
            tableList.Add("OCRIE");
            tableList.Add("OCRO");
            tableList.Add("OCRP");
            tableList.Add("OCRRL");
            tableList.Add("OCRS");
            tableList.Add("OCRV");
            tableList.Add("OECP");
            tableList.Add("OID");
            tableList.Add("OIDPD");
            tableList.Add("OIH");
            tableList.Add("OIS");
            tableList.Add("OIT");
            tableList.Add("OIX");
            tableList.Add("OPCODE");
            tableList.Add("OPEN");
            tableList.Add("OPENT");
            tableList.Add("PCODE");
            tableList.Add("PDMTS");
            tableList.Add("PHLC");
            tableList.Add("PHPF");
            tableList.Add("PHYIB");
            tableList.Add("PHYS");
            tableList.Add("PHYSDP");
            tableList.Add("PHYSLP");
            tableList.Add("PJCL");
            tableList.Add("PJRL");
            tableList.Add("PJRM");
            tableList.Add("PJTP");
            tableList.Add("PLAN");
            tableList.Add("PLCK");
            tableList.Add("PLKS");
            tableList.Add("PLNT");
            tableList.Add("PLNTE");
            tableList.Add("POBUYR");
            tableList.Add("POD");
            tableList.Add("POH");
            tableList.Add("POI");
            tableList.Add("POMVAR");
            tableList.Add("PONM");
            tableList.Add("POPT");
            tableList.Add("POPTVN");
            tableList.Add("POPTVP");
            tableList.Add("POQD");
            tableList.Add("PORCAP");
            tableList.Add("PORCAPA");
            tableList.Add("PORCAPT");
            tableList.Add("PORCH");
            tableList.Add("PORCHD");
            tableList.Add("PORCHN");
            tableList.Add("PORD");
            tableList.Add("POREQR");
            tableList.Add("PORH");
            tableList.Add("PORI");
            tableList.Add("PORQD");
            tableList.Add("PORQI");
            tableList.Add("PORV");
            tableList.Add("POVD");
            tableList.Add("POVP");
            tableList.Add("PRHIST");
            tableList.Add("PRTFD");
            tableList.Add("PRTFH");
            tableList.Add("PRTRAN");
            tableList.Add("PSSC");
            tableList.Add("PSSCD");
            tableList.Add("PSSCDT");
            tableList.Add("PUNIT");
            tableList.Add("QCRD");
            tableList.Add("QCRF");
            tableList.Add("QCRH");
            tableList.Add("QCRI");
            tableList.Add("QCRIE");
            tableList.Add("QCRP");
            tableList.Add("QCRS");
            tableList.Add("RACT");
            tableList.Add("RCTF");
            tableList.Add("RDEV");
            tableList.Add("RESRE");
            tableList.Add("RESRP");
            tableList.Add("RFGADJ");
            tableList.Add("RFGBB");
            tableList.Add("RPRH");
            tableList.Add("RPRM");
            tableList.Add("RPRN");
            tableList.Add("RPRP");
            tableList.Add("RPRQ");
            tableList.Add("RPRQE");
            tableList.Add("RPRR");
            tableList.Add("SCGC");
            tableList.Add("SCRAP");
            tableList.Add("SERC");
            tableList.Add("SERH");
            tableList.Add("SERI");
            tableList.Add("SERM");
            tableList.Add("SERS");
            tableList.Add("SFRF");
            tableList.Add("SHCR");
            tableList.Add("SHCREX");
            tableList.Add("SLMB");
            tableList.Add("SOPC");
            tableList.Add("SPRM");
            tableList.Add("SPRSN");
            tableList.Add("SRTE");
            tableList.Add("SSCH");
            tableList.Add("SSCL");
            tableList.Add("STKA");
            tableList.Add("STKAS");
            tableList.Add("STKB");
            tableList.Add("STKC");
            tableList.Add("STKLVL");
            tableList.Add("STKMM");
            tableList.Add("STKMP");
            tableList.Add("STKR");
            tableList.Add("STKRX");
            tableList.Add("STKT");
            tableList.Add("STKTCST");
            tableList.Add("STKTE");
            tableList.Add("STKX");
            tableList.Add("STXTD");
            tableList.Add("STXTH");
            tableList.Add("SUPS");
            tableList.Add("TAZA");
            tableList.Add("TAZB");
            tableList.Add("TAZM");
            tableList.Add("TAZP");
            tableList.Add("TREA");
            tableList.Add("TRRB");
            tableList.Add("TXGP");
            tableList.Add("TXGPD");
            tableList.Add("TXRT");
            tableList.Add("TXRTD");
            tableList.Add("TXTP");
            tableList.Add("UCHQ");
            tableList.Add("USRC");
            tableList.Add("USRD");
            tableList.Add("USRDE");
            tableList.Add("VCHR");
            tableList.Add("VEND");
            tableList.Add("VENDDS");
            tableList.Add("VNDP");
            tableList.Add("VOID");
            tableList.Add("VRTF");
            tableList.Add("VRTL");
            tableList.Add("WIPB");
            tableList.Add("WIPT");
        }

        static private void Find(string keyword)
        {
            Console.WriteLine("start searching " + keyword);
            // output
            List<string> foundTableList = new List<string>();
            // search
            ExcoODBC odbcConnection = ExcoODBC.Instance;
            odbcConnection.Open(Database.PRODTEST);
            foreach (string table in tableList)
            {
                // get all fields in a table
                //Console.WriteLine("start processing " + table);
                string query = "select * from cmsdat." + table + " fetch first 1 rows only";
                OdbcDataReader reader = odbcConnection.RunQuery(query);
                List<string> fieldList = new List<string>();
                if (reader.Read())
                {
                    for (int i = 0; i < reader.FieldCount; i++)
                    {
                        try
                        {
                            if ("System.String" == reader[i].GetType().ToString() || "System.Decimal" == reader[i].GetType().ToString() || "System.Int32" == reader[i].GetType().ToString() || "System.UInt32" == reader[i].GetType().ToString() || "System.UInt64" == reader[i].GetType().ToString() || "System.Int64" == reader[i].GetType().ToString() || "System.UInt16" == reader[i].GetType().ToString() || "System.Int16" == reader[i].GetType().ToString())
                            {
                                fieldList.Add(reader.GetName(i));
                            }
                            else
                            {
                                string aa = reader[i].GetType().ToString();
                                if ("System.DateTime" != reader[i].GetType().ToString() && "System.TimeSpan" != reader[i].GetType().ToString())
                                {
                                    aa.ToString();
                                }
                            }
                        }
                        catch
                        {
                            continue;
                        }
                    }
                }
                reader.Close();
                //Console.WriteLine(fieldList.Count.ToString() + " fields found");
                // search for keyword
                foreach (string field in fieldList)
                {
                    //Console.WriteLine(table + ", " + field);
                    query = "select * from cmsdat." + table + " where " + field + " like '" + keyword + "%' fetch first 1 rows only";
                    reader = odbcConnection.RunQuery(query);
                    if (reader.Read())
                    {
                        if (reader.HasRows)
                        {
                            foundTableList.Add(table + ", " + field);
                            //Console.WriteLine("found" + Environment.NewLine + Environment.NewLine);
                        }
                    }
                    reader.Close();
                }
                //Console.WriteLine("done");
            }
            // write to file
            File.Delete(keyword + " result.txt");
            StreamWriter sw = new StreamWriter(keyword + "result.txt");
            foreach (string foundTable in foundTableList)
            {
                sw.WriteLine(foundTable);
            }
            sw.Flush();
            sw.Close();
        }

        static void Main(string[] args)
        {
            FillTableList();
            Find("278520");
            Console.WriteLine("done");
            Find("0468025");
            Console.WriteLine("done");
            Find("278521");
            Console.WriteLine("done");
            Find("0468026");
            Console.WriteLine("done");
        }
    }
}
