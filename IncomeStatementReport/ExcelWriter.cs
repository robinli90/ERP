using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Excel = Microsoft.Office.Interop.Excel;
using ExcoUtility;
using IncomeStatementReport.Categories;

namespace IncomeStatementReport
{
    public class ExcelWriter
    {
        private bool Implement_Changes = true;

        // excel objects
        private Excel.Application excel = new Excel.Application();
        private object misValue = System.Reflection.Missing.Value;
        private Excel.Workbook workBook;
        // work sheets
        private Excel.Worksheet colCADSheet;
        private Excel.Worksheet colPESOSheet;
        private Excel.Worksheet texCADSheet;
        private Excel.Worksheet texUSDSheet;
        private Excel.Worksheet micCADSheet;
        private Excel.Worksheet micUSDSheet;
        private Excel.Worksheet marCADSheet;
        private Excel.Worksheet consolidateSheet;
        // period
        private int fiscalYear;
        private int fiscalMonth;
        // data source
        private Process process;
        // total rows for each categories
        private int totalSSRow = 0;
        private int totalPTRow = 0;
        private int totalCSRow = 0;
        private int totalDLRow = 0;
        private int totalFORow = 0;
        private int totalDSRow = 0;
        private int totalGARow = 0;
        private int totalOERow = 0;
        // rows for consolidation
        private int provisionRow = 0;
        private int factorySATravelRow = 0;
        private int officeSATravelRow = 0;
        private int grandTotalRow = 0;
        private int directLabourShop = 0;
        private int directLabourHeat = 0;
        private int directLabourCAM = 0;
        private int factoryCAD = 0;
        private int factoryIndirectLabour = 0;
        private int factorySupervisor = 0;
        private int factoryEmployeeBenefits = 0;
        private int factoryGroupInsurance = 0;
        private int factoryWorkersCompensation = 0;
        private int factoryVacationPay = 0;
        private int factoryStatHoliday = 0;
        private int officeSalaries = 0;
        private int salesSalaries = 0;
        private int salesEmployeeBenefits = 0;
        private int salesGroupInsurance = 0;
        private int salesWorkersCompensation = 0;
        private int salesVacationPay = 0;
        private int salesStatHoliday = 0;
        private int officeEmployeeBenefits = 0;
        private int officeGroupInsurance = 0;
        private int officePayrollTaxes = 0;
        private int officeWorkersCompensation = 0;
        private int officeVacationPay = 0;
        private int officeStatHoliday = 0;
        private int factoryRent = 0;
        private int officeRent = 0;
        private int factoryDepreBuilding = 0;
        private int factoryDepreBuildingImprov = 0;
        private int factoryReqMainBuilding = 0;
        private int factoryPropertyTax = 0;
        private int factoryDepreMachine = 0;
        private int factoryDepreFurniture = 0;
        private int factoryDepreSoftware = 0;
        private int factoryToolAmort = 0;
        private int officeDepreFurniture = 0;
        private int officeSoftwareAmort = 0;
        private int salesDepreAuto = 0;
        private int factoryToolExpense = 0;
        private int factoryCADCAMSupplies = 0;
        private int factoryShopSupplies = 0;
        private int factoryHeatTreatSupplies = 0;
        private int factoryShippingSupplies = 0;
        private int officeSupplies = 0;
        private int factoryTravel = 0;
        private int factoryMeals = 0;
        private int factoryAirFare = 0;
        private int salesGolf = 0;
        private int salesMeals = 0;
        private int salesTravel = 0;
        private int salesAirFare = 0;
        private int officeMeals = 0;
        private int officeTravel = 0;
        private int officeAirFare = 0;
        private bool isForBonnie = false;
        private int switchpositivenegative = -1;


        private double GET_BUDGET_EXCHANGE_RATE(int fiscal_year, string plant)
        {
            if (plant.Contains("4"))
            {
                switch (fiscal_year)
                {
                    case 10:
                        return 1750;
                    case 11:
                        return 1750;
                    case 12:
                        return 1750;
                    case 13:
                        return 1750;
                    case 14:
                        return 1750;
                    case 15:
                        return 1750;
                    case 16:
                        return 1900;
                    case 17:
                        return 2400;
                    default:
                        return 1900;
                }
            }
            else if (plant == "3" || plant == "5")
            {
                switch (fiscal_year)
                {
                    case 10:
                        return 0.900900900900900900900900;
                    case 11:
                        return 1.11;
                    case 12:
                        return 1.11;
                    case 13:
                        return 1.11;
                    case 14:
                        return 1.11;
                    case 15:
                        return 1.111;
                    case 16:
                        return 1.111;
                    case 17:
                        return 1.25;
                    default:
                        return 1.1111;
                }
            }
            else
            {
                return 1;
            }
        }


        // constructor
        public ExcelWriter(Process process)
        {
            this.process = process;
            this.fiscalMonth = process.fiscalMonth;
            this.fiscalYear = process.fiscalYear;


            // create work book            
            workBook = excel.Workbooks.Add(misValue);

            // create work sheets

            if (true)
            {
                colCADSheet = workBook.Worksheets.Add();
                colCADSheet.Name = "Colombia at " + fiscalMonth + "-" + fiscalYear + " (CAD)";
                colPESOSheet = workBook.Worksheets.Add();
                colPESOSheet.Name = "Colombia at " + fiscalMonth + "-" + fiscalYear + " (PESO)";
                //texCADSheet = workBook.Worksheets.Add();
           } 
            else
            {
                colCADSheet = workBook.Worksheets[3];
                colCADSheet.Name = "Colombia at ?" + fiscalMonth + "-" + fiscalYear + " (CAD)";
                colPESOSheet = workBook.Worksheets[2];
                colPESOSheet.Name = "Colombia at " + fiscalMonth + "-" + fiscalYear + " (PESO)";

                //colCADSheet = workBook.Worksheets.Add();
                //colCADSheet.Name = "Colombia at " + fiscalMonth + "-" + fiscalYear + " (CAD)";
                //colPESOSheet = workBook.Worksheets.Add();
                //colPESOSheet.Name = "Colombia at " + fiscalMonth + "-" + fiscalYear + " (PESO)";
                //texCADSheet = workBook.Worksheets.Add();
            }
            texCADSheet = workBook.Worksheets.Add();
            texCADSheet.Name = "Texas at " + fiscalMonth + "-" + fiscalYear + " (CAD)";
            texUSDSheet = workBook.Worksheets.Add();
            texUSDSheet.Name = "Texas at " + fiscalMonth + "-" + fiscalYear + " (USD)";
            micCADSheet = workBook.Worksheets.Add();
            micCADSheet.Name = "Michigan at " + fiscalMonth + "-" + fiscalYear + " (CAD)";
            micUSDSheet = workBook.Worksheets.Add();
            micUSDSheet.Name = "Michigan at " + fiscalMonth + "-" + fiscalYear + " (USD)";
            marCADSheet = workBook.Worksheets.Add();
            marCADSheet.Name = "Markham at " + fiscalMonth + "-" + fiscalYear + " (CAD)";
            consolidateSheet = workBook.Worksheets.Add();
            consolidateSheet.Name = "Consolidate " + fiscalMonth + "-" + fiscalYear + " (CAD)";
        }

        // output to an external excel file
        public void OutputToFile(string filePath)
        {
            workBook.SaveAs(filePath, Excel.XlFileFormat.xlOpenXMLWorkbook);
            excel.Quit();
            
        }

        // fill sheets
        public void FillSheets()
        {
            FillMarkhamCADWorkSheet();
            FillMichiganCADWorkSheet();
            FillMichiganUSDWorkSheet();
            FillTexasCADWorkSheet();
            FillTexasUSDWorkSheet();
            FillColombiaCADWorkSheet();
            FillColombiaPESOWorkSheet();
            
            // new process for consolidated
            this.process = new Process(process.fiscalYear, process.fiscalMonth, true);
            FillConsolidateCADWorkSheet();
        }

        // write sheet header
        private int WriteSheetHeader(string title, Excel.Worksheet sheet)
        {
            int row = 1;
            sheet.Cells[row, 1] = title;
            sheet.Cells.get_Range("A1").Font.Bold = true;
            sheet.Cells.get_Range("A1").Font.Size = 20;
            sheet.Cells.get_Range("A1").Font.ColorIndex = 3;
            sheet.Cells.get_Range("A1", "H1").Merge();
            return row;
        }

        // write exchange rate row
        private int WriteExchangeRateRow(int row, int plantID, string currency, Excel.Worksheet sheet)
        {
            if (plantID == 4)
            {
                plantID = 1;
            }
            sheet.Cells[row, 1] = "Exchange Rate:";
            // this period
            ExcoCalendar calendar = new ExcoCalendar(fiscalYear, fiscalMonth, true, plantID);
            sheet.Cells[row, 2] = ExcoExRate.GetToCADRate(calendar.GetNextCalendarMonth(), currency);
            //sheet.Cells[row, 6] = ExcoExRate.GetToCADRate(calendar.GetNextCalendarMonth(), currency);
            sheet.Cells[row, 6] = (plantID == 4 ? 1/(GET_BUDGET_EXCHANGE_RATE(fiscalYear, plantID.ToString())) : GET_BUDGET_EXCHANGE_RATE(fiscalYear, plantID.ToString()));
            // last period
            if (fiscalMonth > 1)
            {
                calendar = new ExcoCalendar(fiscalYear, fiscalMonth - 1, true, plantID);
            }
            else
            {
                calendar = new ExcoCalendar(fiscalYear - 1, 12, true, plantID);
            }
            sheet.Cells[row, 4] = ExcoExRate.GetToCADRate(calendar.GetNextCalendarMonth(), currency);
            // this period last year
            calendar = new ExcoCalendar(fiscalYear - 1, fiscalMonth, true, plantID);
            sheet.Cells[row, 12] = ExcoExRate.GetToCADRate(calendar.GetNextCalendarMonth(), currency);
            return row;
        }

        // adjust style for a sheet
        private void AdjustSheetStyle(Excel.Worksheet sheet, int row)
        {
            sheet.Cells.Columns.AutoFit();
            sheet.Cells.HorizontalAlignment = Excel.XlHAlign.xlHAlignCenter;
            sheet.Cells.get_Range("A2", "A" + row.ToString()).HorizontalAlignment = Excel.XlHAlign.xlHAlignLeft;
            sheet.Cells.get_Range("B2", "M" + row.ToString()).HorizontalAlignment = Excel.XlHAlign.xlHAlignRight;
        }

        // write header
        private int WriteHeader(Excel.Worksheet sheet, int row)
        {
            sheet.Cells[row, 1] = "Name";
            sheet.Cells[row, 2] = "Period " + fiscalMonth + " Actual";
            sheet.Cells[row, 4] = "Last Period Actual";
            sheet.Cells[row, 6] = "Period " + fiscalMonth + " Budget";
            sheet.Cells[row, 8] = "Y-T-D Actual";
            sheet.Cells[row, 10] = "Y-T-D Budget";
            sheet.Cells[row, 12] = "Last Year Period " + fiscalMonth + " Actual"; ;
            Excel.Range range = sheet.Cells.get_Range("A" + row.ToString(), "M" + row.ToString());
            range.Font.Bold = true;
            range.Font.Size = 14;
            range.Cells.Borders[Excel.XlBordersIndex.xlEdgeBottom].LineStyle = Excel.XlLineStyle.xlContinuous;
            return row;
        }

        int ProductionSalesRow = 0;
        int SteelSurchargeRow = 0;
        int OtherSalesRow = 0;
        int ProductionSalesRowTotal = 0;
        int SteelSurchargeRowTotal = 0;
        int OtherSalesRowTotal = 0;

        // write a group list
        private int WriteGroupList(Excel.Worksheet sheet, int row, int plantID, string currency, Category category, bool Native_Currency=false)
        {
            List<Group> groupList = category.groupList;

            bool hasProductionSales = false;
            bool hasSteelSurcharge = false;
            bool hasOtherSales = false;
            bool hasTotalSales = false;

            if (category.name == "" && plantID == 4) Console.Write("");

            bool _Native_Currency = Native_Currency;
            // write amount
            foreach (Group group in groupList)
            {
                if (!hasProductionSales && category.name == "SALES" && Implement_Changes)
                {
                    sheet.Cells[row, 1] = "PRODUCTION SALES";
                    //sheet.Cells.get_Range("A" + row.ToString()).Interior.ColorIndex = 40;
                    ProductionSalesRow = row;
                    row++;
                    hasProductionSales = true;
                }
                // title
                sheet.Cells[row, 1] = group.name;
                if (group.name.Contains("STEEL SURCHARGE"))
                    sheet.Rows[row].Hidden = true;
                Plant plant;
                if (plantID != 4)
                {
                    if (plantID == 1)
                    {
                        plant = group.plant01;
                    }
                    else if (plantID == 3)
                    {
                        plant = group.plant03;
                    }
                    else if (plantID == 5)
                    {
                        plant = group.plant05;
                    }
                    else
                    {
                        throw new Exception("Invalid plant " + plantID);
                    }

                    ExcoCalendar calendar = new ExcoCalendar(fiscalYear, fiscalMonth, true, plantID);
                    //sheet.Cells[row, 2] = ExcoExRate.GetToCADRate(calendar.GetNextCalendarMonth(), currency);
                    //sheet.Cells[row, 6] = ExcoExRate.GetToCADRate(calendar.GetNextCalendarMonth(), currency);


                    // actual this period
                    sheet.Cells[row, 2] = (plant.actualThisYearList[fiscalMonth].GetAmount(currency) * switchpositivenegative).ToString("C2");
                    // actual last period
                    if (fiscalMonth > 1)
                    {
                        sheet.Cells[row, 4] = (plant.actualThisYearList[fiscalMonth - 1].GetAmount(currency) * switchpositivenegative).ToString("C2");
                    }
                    else
                    {
                        sheet.Cells[row, 4] = (plant.actualLastYearList[12].GetAmount(currency) * switchpositivenegative).ToString("C2");
                    }
                    // budget this period
                    if (_Native_Currency)
                        sheet.Cells[row, 6] = (plant.budgetThisYearList[fiscalMonth].GetAmount(currency) * switchpositivenegative).ToString("C2");
                    else
                        sheet.Cells[row, 6] = (((plant.budgetThisYearList[fiscalMonth].GetAmount(currency) * switchpositivenegative) / ExcoExRate.GetToCADRate(calendar.GetNextCalendarMonth(), "US")) * GET_BUDGET_EXCHANGE_RATE(fiscalYear, plantID.ToString())).ToString("C2");
                    //string gg = (plant.budgetThisYearList[fiscalMonth].GetAmount(currency) * switchpositivenegative).ToString();
                    //string l = ExcoExRate.GetToCADRate(calendar.GetNextCalendarMonth(), "US").ToString();
                    //string k = GET_BUDGET_EXCHANGE_RATE(fiscalYear, plantID.ToString()).ToString();
                    //string p = gg + l + k;
                    
                    // year to date actual
                    double ytdActual = 0.0;
                    double ytdBudget = 0.0;
                    for (int i = 1; i <= fiscalMonth; i++)
                    {
                        ytdActual += plant.actualThisYearList[i].GetAmount(currency);
                        if (true)
                        //if (false) ;
                        ytdBudget += plant.budgetThisYearList[i].GetAmount(currency);
                        else
                            ytdBudget += (((plant.budgetThisYearList[i].GetAmount(currency) * switchpositivenegative) / ExcoExRate.GetToCADRate(calendar.GetNextCalendarMonth(), "US")) * GET_BUDGET_EXCHANGE_RATE(fiscalYear, plantID.ToString())) * switchpositivenegative;
                    }
                    sheet.Cells[row, 8] = (ytdActual*switchpositivenegative).ToString("C2");
                    sheet.Cells[row, 10] = (ytdBudget*switchpositivenegative).ToString("C2");
                    // last year this period actual
                    sheet.Cells[row, 12] = (plant.actualLastYearList[fiscalMonth].GetAmount(currency)*switchpositivenegative).ToString("C2");
                }
                else
                {
                    ExcoMoney thisPeriod;
                    ExcoMoney lastPeriod;
                    ExcoMoney thisPeriodLastYear;
                    ExcoCalendar calendar = new ExcoCalendar(group.plant04.calendar.GetCalendarYear(), group.plant04.calendar.GetCalendarMonth(), true, 1);
                    if (fiscalMonth > 2)
                    {
                        double a = group.plant04.actualThisYearList[fiscalMonth].GetAmount("CP") + 0;
                        double b = group.plant41.actualThisYearList[fiscalMonth].GetAmount("CP") + 0;
                        double c = group.plant48.actualThisYearList[fiscalMonth].GetAmount("CP") + 0;
                        double d = group.plant49.actualThisYearList[fiscalMonth].GetAmount("CP") + 0;
                        double e = group.plant04.actualThisYearList[fiscalMonth - 1].GetAmount("CP") + 0;
                        double f = group.plant41.actualThisYearList[fiscalMonth - 1].GetAmount("CP") + 0; //reporting error
                        double i = group.plant48.actualThisYearList[fiscalMonth - 1].GetAmount("CP") + 0;
                        double h = group.plant49.actualThisYearList[fiscalMonth - 1].GetAmount("CP") + 0;
                        thisPeriod = new ExcoMoney(calendar.GetNextCalendarMonth(), 
                            (
                                group.plant04.actualThisYearList[fiscalMonth] +
                                group.plant41.actualThisYearList[fiscalMonth] +
                                group.plant48.actualThisYearList[fiscalMonth] +
                                group.plant49.actualThisYearList[fiscalMonth]
                            ).amountCP - 
                            (
                                group.plant04.actualThisYearList[fiscalMonth - 1] +
                                group.plant41.actualThisYearList[fiscalMonth - 1] +
                                group.plant48.actualThisYearList[fiscalMonth - 1] +
                                group.plant49.actualThisYearList[fiscalMonth - 1]
                            ).amountCP, 
                            "CP");
                        lastPeriod = new ExcoMoney(calendar.GetLastCalendarMonth(), 
                            (
                                group.plant04.actualThisYearList[fiscalMonth - 1] +
                                group.plant41.actualThisYearList[fiscalMonth - 1] +
                                group.plant48.actualThisYearList[fiscalMonth - 1] +
                                group.plant49.actualThisYearList[fiscalMonth - 1]
                            ).amountCP - 
                            (
                                group.plant04.actualThisYearList[fiscalMonth - 2] +
                                group.plant41.actualThisYearList[fiscalMonth - 2] +
                                group.plant48.actualThisYearList[fiscalMonth - 2] +
                                group.plant49.actualThisYearList[fiscalMonth - 2])
                            .amountCP,
                            "CP");
                        thisPeriodLastYear = new ExcoMoney(calendar.GetCalendarMonthLastYear(), 
                            (
                                group.plant04.actualLastYearList[fiscalMonth] +
                                group.plant41.actualLastYearList[fiscalMonth] + 
                                group.plant48.actualLastYearList[fiscalMonth] + 
                                group.plant49.actualLastYearList[fiscalMonth]
                            ).amountCP - 
                            (
                                group.plant04.actualLastYearList[fiscalMonth - 1] +
                                group.plant41.actualLastYearList[fiscalMonth - 1] + 
                                group.plant48.actualLastYearList[fiscalMonth - 1] + 
                                group.plant49.actualLastYearList[fiscalMonth - 1]
                            ).amountCP, 
                            "CP");
                    }
                    else if (fiscalMonth == 2)
                    {
                        thisPeriod = new ExcoMoney(calendar.GetNextCalendarMonth(), (group.plant04.actualThisYearList[fiscalMonth] + group.plant41.actualThisYearList[fiscalMonth] + group.plant48.actualThisYearList[fiscalMonth] + group.plant49.actualThisYearList[fiscalMonth]).amountCP - (group.plant04.actualThisYearList[fiscalMonth - 1] + group.plant41.actualThisYearList[fiscalMonth - 1] + group.plant48.actualThisYearList[fiscalMonth - 1] + group.plant49.actualThisYearList[fiscalMonth - 1]).amountCP, "CP");
                        lastPeriod = group.plant04.actualThisYearList[fiscalMonth - 1] + group.plant41.actualThisYearList[fiscalMonth - 1] + group.plant48.actualThisYearList[fiscalMonth - 1] + group.plant49.actualThisYearList[fiscalMonth - 1];
                        thisPeriodLastYear = new ExcoMoney(calendar.GetCalendarMonthLastYear(), (group.plant04.actualLastYearList[fiscalMonth] + group.plant41.actualLastYearList[fiscalMonth] + group.plant48.actualLastYearList[fiscalMonth] + group.plant49.actualLastYearList[fiscalMonth]).amountCP - (group.plant04.actualLastYearList[fiscalMonth - 1] + group.plant41.actualLastYearList[fiscalMonth - 1] + group.plant48.actualLastYearList[fiscalMonth - 1] + group.plant49.actualLastYearList[fiscalMonth - 1]).amountCP, "CP");
                    }
                    else // period 1

                    {
                        //lastPeriod = new ExcoMoney(calendar.GetNextCalendarMonth(), 0, "CP");
                        //thisPeriod = new ExcoMoney(calendar.GetNextCalendarMonth(), 0, "CP");
                        //thisPeriodLastYear = new ExcoMoney(calendar.GetNextCalendarMonth(), 0, "CP");

                        // last period is 0 returning error
                        //lastPeriod = new ExcoMoney(calendar.GetLastCalendarMonth(), (group.plant04.actualLastYearList[12] + group.plant41.actualLastYearList[12] + group.plant48.actualLastYearList[12] + group.plant49.actualLastYearList[12]).amountCP - (group.plant04.actualLastYearList[11] + group.plant41.actualLastYearList[11] + group.plant48.actualLastYearList[11] + group.plant49.actualLastYearList[11]).amountCP, "CP"); thisPeriod = group.plant04.actualThisYearList[fiscalMonth] + group.plant41.actualThisYearList[fiscalMonth] + group.plant48.actualThisYearList[fiscalMonth] + group.plant49.actualThisYearList[fiscalMonth];
                        //thisPeriod = group.plant04.actualThisYearList[fiscalMonth] + group.plant41.actualThisYearList[fiscalMonth] + group.plant48.actualThisYearList[fiscalMonth] + group.plant49.actualThisYearList[fiscalMonth] - (group.plant04.actualLastYearList[12] + group.plant41.actualLastYearList[12] + group.plant48.actualLastYearList[12] + group.plant49.actualLastYearList[12]);
                        //thisPeriodLastYear = group.plant04.actualLastYearList[fiscalMonth] + group.plant41.actualLastYearList[fiscalMonth] + group.plant48.actualLastYearList[fiscalMonth] + group.plant49.actualLastYearList[fiscalMonth];
                    
                        // tIGER original
                        thisPeriod = group.plant04.actualThisYearList[fiscalMonth] + group.plant41.actualThisYearList[fiscalMonth] + group.plant48.actualThisYearList[fiscalMonth] + group.plant49.actualThisYearList[fiscalMonth];
                        //thisPeriod = group.plant04.actualThisYearList[fiscalMonth] + group.plant41.actualThisYearList[fiscalMonth] + group.plant48.actualThisYearList[fiscalMonth] + group.plant49.actualThisYearList[fiscalMonth] - (group.plant04.actualLastYearList[12] + group.plant41.actualLastYearList[12] + group.plant48.actualLastYearList[12] + group.plant49.actualLastYearList[12]); //robin add
                        //thisPeriod = (group.plant04.actualLastYearList[12] + group.plant41.actualLastYearList[12] + group.plant48.actualLastYearList[12] + group.plant49.actualLastYearList[12]); //robin add
                        lastPeriod = new ExcoMoney(calendar.GetLastCalendarMonth(), (group.plant04.actualLastYearList[12] + group.plant41.actualLastYearList[12] + group.plant48.actualLastYearList[12] + group.plant49.actualLastYearList[12]).amountCP - (group.plant04.actualLastYearList[11] + group.plant41.actualLastYearList[11] + group.plant48.actualLastYearList[11] + group.plant49.actualLastYearList[11]).amountCP, "CP");
                        thisPeriodLastYear = group.plant04.actualLastYearList[fiscalMonth] + group.plant41.actualLastYearList[fiscalMonth] + group.plant48.actualLastYearList[fiscalMonth] + group.plant49.actualLastYearList[fiscalMonth];
                    }
                    // actual this period
                    string g = (thisPeriod.GetAmount(currency) * switchpositivenegative).ToString("C2");
                    sheet.Cells[row, 2] = g;
                    // actual last period
                    g = (lastPeriod.GetAmount(currency) * switchpositivenegative).ToString("C2");
                    sheet.Cells[row, 4] = g;
                    // budget this period
                    if (_Native_Currency)
                        sheet.Cells[row, 6] = ((group.plant04.budgetThisYearList[fiscalMonth].GetAmount(currency) + group.plant41.budgetThisYearList[fiscalMonth].GetAmount(currency) + group.plant48.budgetThisYearList[fiscalMonth].GetAmount(currency) + group.plant49.budgetThisYearList[fiscalMonth].GetAmount(currency))*switchpositivenegative).ToString("C2");
                    else
                        sheet.Cells[row, 6] = ((((group.plant04.budgetThisYearList[fiscalMonth].GetAmount(currency) + group.plant41.budgetThisYearList[fiscalMonth].GetAmount(currency) + group.plant48.budgetThisYearList[fiscalMonth].GetAmount(currency) + group.plant49.budgetThisYearList[fiscalMonth].GetAmount(currency))*switchpositivenegative) / ExcoExRate.GetToCADRate(calendar.GetNextCalendarMonth(), "CP")) / GET_BUDGET_EXCHANGE_RATE(fiscalYear, plantID.ToString())).ToString("C2");
                    //string gg = ((group.plant04.budgetThisYearList[fiscalMonth].GetAmount(currency) + group.plant41.budgetThisYearList[fiscalMonth].GetAmount(currency) + group.plant48.budgetThisYearList[fiscalMonth].GetAmount(currency) + group.plant49.budgetThisYearList[fiscalMonth].GetAmount(currency)) * switchpositivenegative).ToString();
                    //string l = ExcoExRate.GetToCADRate(calendar.GetNextCalendarMonth(), "CP").ToString();
                    //string k = GET_BUDGET_EXCHANGE_RATE(fiscalYear, plantID.ToString()).ToString();
                    //string dd = ((Convert.ToDouble(gg) / Convert.ToDouble(l)) / Convert.ToDouble(k)).ToString();
                    //Console.WriteLine(gg + l + k + dd);

                    // year to date actual
                    double ytdBudget = 0.0;
                    double ytdActual = 0.0;
                    for (int i = 1; i <= fiscalMonth; i++)
                    {

                        double a = 0;
                        double b = 0;
                        double c = 0;
                        double d = 0;
                        double a1 = 0;
                        double b1 = 0;
                        double c1 = 0;
                        double d1 = 0;
                        if (i - 1 <= 0)
                        {
                            //ACTUAL
                            a = group.plant04.actualThisYearList[i].amountCP * ExcoExRate.PESOtoCAD(calendar, fiscalYear, i);
                            b = group.plant41.actualThisYearList[i].amountCP * ExcoExRate.PESOtoCAD(calendar, fiscalYear, i);
                            c = group.plant48.actualThisYearList[i].amountCP * ExcoExRate.PESOtoCAD(calendar, fiscalYear, i);
                            d = group.plant49.actualThisYearList[i].amountCP * ExcoExRate.PESOtoCAD(calendar, fiscalYear, i);
                            //BUDGET
                            a1 = group.plant04.budgetThisYearList[i].amountCP; //* ExcoExRate.PESOtoCAD(calendar, fiscalYear, i);
                            b1 = group.plant41.budgetThisYearList[i].amountCP; //* ExcoExRate.PESOtoCAD(calendar, fiscalYear, i);
                            c1 = group.plant48.budgetThisYearList[i].amountCP; //* ExcoExRate.PESOtoCAD(calendar, fiscalYear, i);
                            d1 = group.plant49.budgetThisYearList[i].amountCP; //* ExcoExRate.PESOtoCAD(calendar, fiscalYear, i);
                        }
                        else
                        {
                            //ACTUAL
                            a = (group.plant04.actualThisYearList[i].amountCP - group.plant04.actualThisYearList[i - 1].amountCP) * ExcoExRate.PESOtoCAD(calendar, fiscalYear, i);
                            b = (group.plant41.actualThisYearList[i].amountCP - group.plant41.actualThisYearList[i - 1].amountCP) * ExcoExRate.PESOtoCAD(calendar, fiscalYear, i);
                            c = (group.plant48.actualThisYearList[i].amountCP - group.plant48.actualThisYearList[i - 1].amountCP) * ExcoExRate.PESOtoCAD(calendar, fiscalYear, i);
                            d = (group.plant49.actualThisYearList[i].amountCP - group.plant49.actualThisYearList[i - 1].amountCP) * ExcoExRate.PESOtoCAD(calendar, fiscalYear, i);
                            //BUDGET
                            a1 = (group.plant04.budgetThisYearList[i].amountCP);// - group.plant04.budgetThisYearList[i - 1].amountCP); //* ExcoExRate.PESOtoCAD(calendar, fiscalYear, i);
                            b1 = (group.plant41.budgetThisYearList[i].amountCP);// - group.plant41.budgetThisYearList[i - 1].amountCP); //* ExcoExRate.PESOtoCAD(calendar, fiscalYear, i);
                            c1 = (group.plant48.budgetThisYearList[i].amountCP);// - group.plant48.budgetThisYearList[i - 1].amountCP); //* ExcoExRate.PESOtoCAD(calendar, fiscalYear, i);
                            d1 = (group.plant49.budgetThisYearList[i].amountCP);// - group.plant49.budgetThisYearList[i - 1].amountCP); //* ExcoExRate.PESOtoCAD(calendar, fiscalYear, i);
                        }
                        double temp = a1 + b1 + c1 + d1;

                        // Determine which sheet
                        ytdActual = Native_Currency == false ? ytdActual + a + b + c + d :
                            ytdActual + ((a + b + c + d) / ExcoExRate.PESOtoCAD(calendar, fiscalYear, i));

                        //ytdBudget = ytdBudget + (a1 + b1 + c1 + d1) / GET_BUDGET_EXCHANGE_RATE(fiscalYear, "4");
                        // Determine which sheet
                        ytdBudget = Native_Currency == false ? ytdBudget + (a1 + b1 + c1 + d1) / GET_BUDGET_EXCHANGE_RATE(fiscalYear, "4") :
                            ytdBudget + (a1 + b1 + c1 + d1);

                        /*
                        if (_Native_Currency)
                            ytdBudget += group.plant04.budgetThisYearList[i].GetAmount(currency) + group.plant41.budgetThisYearList[i].GetAmount(currency) + group.plant48.budgetThisYearList[i].GetAmount(currency) + group.plant49.budgetThisYearList[i].GetAmount(currency);
                        else
                            ytdBudget += ((((group.plant04.budgetThisYearList[i].GetAmount(currency) + group.plant41.budgetThisYearList[i].GetAmount(currency) + group.plant48.budgetThisYearList[i].GetAmount(currency) + group.plant49.budgetThisYearList[i].GetAmount(currency)) * switchpositivenegative) / ExcoExRate.GetToCADRate(calendar.GetNextCalendarMonth(), "CP")) / GET_BUDGET_EXCHANGE_RATE(fiscalYear, plantID.ToString())) * switchpositivenegative;
                         * */
                    }
                    //double aa = group.plant04.actualThisYearList[fiscalMonth].GetAmount(currency);
                    //double bb = group.plant41.actualThisYearList[fiscalMonth].GetAmount(currency);
                    //double cc = group.plant48.actualThisYearList[fiscalMonth].GetAmount(currency);
                    //double dd = group.plant49.actualThisYearList[fiscalMonth].GetAmount(currency);
                    //double tempd = aa + bb + cc + dd;
                    //ytdActual = aa + bb + cc + dd + tempd - tempd;
                    //sheet.Cells[row, 8] = ((group.plant04.actualThisYearList[fiscalMonth] + group.plant41.actualThisYearList[fiscalMonth] + group.plant48.actualThisYearList[fiscalMonth] + group.plant49.actualThisYearList[fiscalMonth]).GetAmount(currency)*switchpositivenegative).ToString("C2");
                    sheet.Cells[row, 8] = (ytdActual * switchpositivenegative).ToString("C2");
                    sheet.Cells[row, 10] =  (ytdBudget*switchpositivenegative).ToString("C2");
                    // last year this period actual
                    sheet.Cells[row, 12] = (thisPeriodLastYear.GetAmount(currency)*switchpositivenegative).ToString("C2");
                }
                row++;
                int surcharge_total_row = 0;
                if (!hasSteelSurcharge && group.name.Contains("INTERDIVISION SALES") && category.name == "SALES" && Implement_Changes)
                {
                    StyleOfSubSummary(sheet, row);
                    sheet.Cells[row, 1] = "TOTAL PRODUCTION SALES";
                    ProductionSalesRowTotal = row;
                    for (int i = 2; i <= 13; i++)
                    {
                        string colCode = Convert.ToChar((Convert.ToInt32('A') + i - 1)).ToString();
                        sheet.Cells[row, i].Formula = "=SUM(" + colCode + (ProductionSalesRow + 1).ToString() + ":" + colCode + (row - 1).ToString() + ")";
                    }
                    StyleOfSummary(sheet, row);
                    row++;
                    row++;
                    sheet.Rows[row].Hidden = true;
                    sheet.Cells[row, 1] = "STEEL SURCHARGE";
                    //sheet.Cells.get_Range("A" + row.ToString()).Interior.ColorIndex = 40;
                    SteelSurchargeRow = row;
                    row++;
                    hasSteelSurcharge = true;
                }
                else if (!hasOtherSales && group.name.Contains("INTERDIVISION SALES STEEL SURCHARGE") && category.name == "SALES" && Implement_Changes)
                {
                    StyleOfSubSummary(sheet, row);
                    sheet.Cells[row, 1] = "TOTAL STEEL SURCHARGE";
                    surcharge_total_row = row;
                    sheet.Rows[row].Hidden = true;
                    for (int i = 2; i <= 13; i++)
                    {
                        string colCode = Convert.ToChar((Convert.ToInt32('A') + i - 1)).ToString();
                        sheet.Cells[row, i].Formula = "=SUM(" + colCode + (SteelSurchargeRow+ 1).ToString() + ":" + colCode + (row - 1).ToString() + ")";
                    }

                    StyleOfSummary(sheet, row);
                    SteelSurchargeRowTotal = row;
                    row++;
                    sheet.Rows[row].Hidden = true;
                    row++;
                    sheet.Cells[row, 1] = "OTHER SALES";
                    //sheet.Cells.get_Range("A" + row.ToString()).Interior.ColorIndex = 40;
                    OtherSalesRow = row;
                    row++;
                    hasOtherSales = true;

                    sheet.Cells[row, 1] = "STEEL SURCHARGE";
                    for (int i = 2; i <= 13; i++)
                    {
                        string colCode = Convert.ToChar((Convert.ToInt32('A') + i - 1)).ToString();
                        sheet.Cells[row, i].Formula = "=" + colCode + (surcharge_total_row).ToString();
                    }
                    row++;
                }
                else if (!hasTotalSales && group.name.Contains("SCRAP SALES") && category.name == "SALES" && Implement_Changes)
                {
                    StyleOfSubSummary(sheet, row);
                    sheet.Cells[row, 1] = "TOTAL OTHER SALES";
                    for (int i = 2; i <= 13; i++)
                    {
                        string colCode = Convert.ToChar((Convert.ToInt32('A') + i - 1)).ToString();
                        sheet.Cells[row, i].Formula = "=SUM(" + colCode + (OtherSalesRow + 1).ToString() + ":" + colCode + (row - 1).ToString() + ")";
                    }
                    StyleOfSummary(sheet, row);
                    OtherSalesRowTotal = row;
                    row++;
                    hasTotalSales = true;
                    //row++;
                }
            }
            return row;// -1;
        }

        // style of summary
        private void StyleOfSummary(Excel.Worksheet sheet, int row)
        {
            sheet.Cells.get_Range("A" + row.ToString(), "M" + row.ToString()).Font.Bold = true;
            sheet.Cells.get_Range("A" + row.ToString(), "M" + row.ToString()).Cells.Borders[Excel.XlBordersIndex.xlEdgeTop].LineStyle = Excel.XlLineStyle.xlContinuous;
        }

        // style of sub summary
        private void StyleOfSubSummary(Excel.Worksheet sheet, int row)
        {
            sheet.Cells.get_Range("A" + row.ToString(), "M" + row.ToString()).Cells.Borders[Excel.XlBordersIndex.xlEdgeTop].LineStyle = Excel.XlLineStyle.xlContinuous;
        }

        // write a group list summary
        private int WriteGroupListSummary(Excel.Worksheet sheet, int startRow, int row)
        {
            sheet.Cells[row, 1] = "TOTAL :";
            if (ProductionSalesRowTotal > 0 && SteelSurchargeRowTotal > 0 && OtherSalesRowTotal > 0)
            {

                // write percentage
                for (int i = 1; i <= 6; i++)
                {
                    string colCode = Convert.ToChar((Convert.ToInt32('A') + i * 2)).ToString();
                    string prevColCode = Convert.ToChar((Convert.ToInt32('A') + (i * 2 - 1))).ToString();
                    for (int j = startRow; j < row; j++)
                    {
                        sheet.Cells[j, i * 2 + 1].NumberFormat = "0.00%";
                        //sheet.Cells[j, i * 2 + 1].Formula = "=" + prevColCode + j.ToString() + "/" + prevColCode + totalSSRow.ToString();
                        sheet.Cells[j, i * 2 + 1].Formula = "=IF(" + prevColCode + j.ToString() + "<>\"\"," + prevColCode + j.ToString() + "/" + prevColCode + totalSSRow.ToString() + ", \"\")";
                    }
                }

                for (int i = 1; i <= 6; i++)
                {
                    string colCode = Convert.ToChar((Convert.ToInt32('A') + i * 2 - 1)).ToString();
                    sheet.Cells[row, i * 2].Formula = "=" + colCode + ProductionSalesRowTotal.ToString() + "+" + colCode + OtherSalesRowTotal.ToString(); // "+" + colCode + SteelSurchargeRowTotal.ToString() + 
                }
                for (int i = 1; i <= 6; i++)
                {
                    string colCode = Convert.ToChar((Convert.ToInt32('A') + i * 2)).ToString();
                    sheet.Cells[row, i * 2 + 1].Formula = "=" + colCode + ProductionSalesRowTotal.ToString() + "+" + colCode + OtherSalesRowTotal.ToString(); // "+" + colCode + SteelSurchargeRowTotal.ToString() + 
                }

                ProductionSalesRowTotal = 0;
                SteelSurchargeRowTotal = 0;
                OtherSalesRowTotal = 0;
                StyleOfSummary(sheet, row);
            }
            else
            {
                for (int i = 1; i <= 6; i++)
                {
                    string colCode = Convert.ToChar((Convert.ToInt32('A') + i * 2 - 1)).ToString();
                    sheet.Cells[row, i * 2].Formula = "=sum(" + colCode + startRow.ToString() + ":" + colCode + (row - 1).ToString() + ")";
                }
                // write percentage
                for (int i = 1; i <= 6; i++)
                {
                    string colCode = Convert.ToChar((Convert.ToInt32('A') + i * 2)).ToString();
                    string prevColCode = Convert.ToChar((Convert.ToInt32('A') + (i * 2 - 1))).ToString();
                    for (int j = startRow; j < row; j++)
                    {
                        sheet.Cells[j, i * 2 + 1].NumberFormat = "0.00%";
                        //sheet.Cells[j, i * 2 + 1].Formula = "=" + prevColCode + j.ToString() + "/" + prevColCode + totalSSRow.ToString();
                        sheet.Cells[j, i * 2 + 1].Formula = "=IF(" + prevColCode + j.ToString() + "<>\"\"," + prevColCode + j.ToString() + "/" + prevColCode + totalSSRow.ToString() + ", \"\")";
                    }
                }
                for (int i = 1; i <= 6; i++)
                {
                    string colCode = Convert.ToChar((Convert.ToInt32('A') + i * 2)).ToString();
                    sheet.Cells[row, i * 2 + 1].Formula = "=sum(" + colCode + startRow.ToString() + ":" + colCode + (row - 1).ToString() + ")";
                }
                // adjust style
            }
            StyleOfSummary(sheet, row);
            return row;
        }


        // write category
        private int WriteCategory(Excel.Worksheet sheet, int row, int plantID, string currency, Category category, bool Native_Currency=false)
        {

            if (!(category.name == ""))
            {
                sheet.Cells[row, 1] = category.name;
                sheet.Cells.get_Range("A" + row.ToString()).Interior.ColorIndex = 27;
                row++;
            }
            // write amount
            int startRow = row;
            row = WriteGroupList(sheet, row, plantID, currency, category, Native_Currency);
            // write summary
            row++;
            switch (category.name)
            {
                case "SALES":
                    totalSSRow = row;
                    break;
                case "COST OF STEELS":
                    totalCSRow = row;
                    break;
                case "DELIVERY AND SELLING":
                    totalDSRow = row;
                    break;
                case "FACTORY OVERHEAD":
                    totalFORow = row;
                    break;
                case "GENERAL AND ADMINISTRATION":
                    totalGARow = row;
                    break;
                case "OTHER EXPENSE AND INCOME":
                    totalOERow = row;
                    break;
                case "DIRECT LABOUR":
                    totalDLRow = row;
                    break;
                case "":
                    totalPTRow = row;
                    break;
                default:
                    throw new Exception("Unknown category " + category.name);
            }
            if (!(category.name == ""))
                row = WriteGroupListSummary(sheet, startRow, row);
            else
            {
                Console.Write("");
            }
            return row + 1;
        }

        // fill the data of a plant into a work sheet
        private void FillMarkhamCADWorkSheet()
        {
            int row = 1;
            // title
            row = WriteSheetHeader("Markham Income Statement at " + fiscalMonth.ToString("D2") + "-" + fiscalYear.ToString("D2") + " (CAD)", marCADSheet);
            // header
            row++;
            row = WriteHeader(marCADSheet, row);
            // write sales
            row++;
            row = WriteCategory(marCADSheet, row, 1, "CA", process.ss, true);
            // write cost of steels
            row++;
            row = WriteCategory(marCADSheet, row, 1, "CA", process.cs, true);
            // write direct labour
            row++;
            row = WriteCategory(marCADSheet, row, 1, "CA", process.dl, true);
            // write factory overhead
            row++;
            row = WriteCategory(marCADSheet, row, 1, "CA", process.fo, true);
            // write total cost of goods
            row++;
            marCADSheet.Cells[row, 1] = "TOTAL COST OF GOODS:";
            for (int i = 2; i <= 13; i++)
            {
                string colCode = Convert.ToChar((Convert.ToInt32('A') + i - 1)).ToString();
                marCADSheet.Cells[row, i].Formula = "=" + colCode + totalCSRow.ToString() + "+" + colCode + totalDLRow.ToString() + "+" + colCode + totalFORow.ToString();
            }
            StyleOfSummary(marCADSheet, row);
            row++;
            // write gross margin
            row++;
            marCADSheet.Cells[row, 1] = "GROSS MARGIN:";
            for (int i = 2; i <= 13; i++)
            {
                string colCode = Convert.ToChar((Convert.ToInt32('A') + i - 1)).ToString();
                marCADSheet.Cells[row, i].Formula = "=" + colCode + totalSSRow.ToString() + "+" + colCode + totalCSRow.ToString() + "+" + colCode + totalDLRow.ToString() + "+" + colCode + totalFORow.ToString();
            }
            StyleOfSummary(marCADSheet, row);
            row++;
            // write delivery and selling
            row++;
            row = WriteCategory(marCADSheet, row, 1, "CA", process.ds, true);
            // write general and administration
            row++;
            row = WriteCategory(marCADSheet, row, 1, "CA", process.ga, true);
            // write other expense and income
            row++;
            row = WriteCategory(marCADSheet, row, 1, "CA", process.oe, true);
            // write total expenses
            row++;
            marCADSheet.Cells[row, 1] = "TOTAL EXPENSES:";
            for (int i = 2; i <= 13; i++)
            {
                string colCode = Convert.ToChar((Convert.ToInt32('A') + i - 1)).ToString();
                marCADSheet.Cells[row, i].Formula = "=" + colCode + totalDSRow.ToString() + "+" + colCode + totalGARow.ToString() + "+" + colCode + totalOERow.ToString();
            }
            StyleOfSummary(marCADSheet, row);
            row++;

            // write provisional tax
            row++;
            row++;
            row++;
            for (int j = 2; j <= 7; j++)
            {
                string colCode = Convert.ToChar((Convert.ToInt32('A') + (j - 1) * 2 - 1)).ToString();
                marCADSheet.Cells[row, j * 2 - 1].NumberFormat = "0.00%";
                marCADSheet.Cells[row, j * 2 - 1].Formula = "=" + colCode + row.ToString() + "/" + colCode + totalSSRow.ToString();
            }
            row = WriteCategory(marCADSheet, row, 1, "CA", process.pt, true);
            row--;

            // adjust style
            AdjustSheetStyle(marCADSheet, row);
            // write gross margin

            marCADSheet.Cells[row, 1] = "TOTAL NET INCOME:";
            for (int i = 2; i <= 13; i++)
            {
                string colCode = Convert.ToChar((Convert.ToInt32('A') + i - 1)).ToString();
                marCADSheet.Cells[row, i].Formula = "=" + colCode + (row - 4).ToString() + "+" + colCode + (row - 2).ToString();
                //marCADSheet.Cells[row, i].Formula = "=" + colCode + totalSSRow.ToString() + "+" + colCode + totalDSRow.ToString() + "+" + colCode + totalGARow.ToString() + "+" + colCode + totalOERow.ToString() + "+" + colCode + totalCSRow.ToString() + "+" + colCode + totalDLRow.ToString() + "+" + colCode + totalFORow.ToString();
                
                for (int j = 2; j <= 7; j++)
                {
                    colCode = Convert.ToChar((Convert.ToInt32('A') + (j-1) * 2 - 1)).ToString();
                    marCADSheet.Cells[row, j * 2 - 1].NumberFormat = "0.00%";
                    marCADSheet.Cells[row, j * 2 - 1].Formula = "=" + colCode + row.ToString() + "/" + colCode + totalSSRow.ToString();
                }
            }
            StyleOfSummary(marCADSheet, row);
            // adjust style
            AdjustSheetStyle(marCADSheet, row);


            // write before income tax
            row-=4;
            marCADSheet.Cells[row, 1] = "NET INCOME  BEFORE PROVISIONAL TAX";
            for (int i = 2; i <= 13; i++)
            {
                string colCode = Convert.ToChar((Convert.ToInt32('A') + i - 1)).ToString(); 
                marCADSheet.Cells[row, i].Formula = "=" + colCode + totalSSRow.ToString() + "+" + colCode + totalDSRow.ToString() + "+" + colCode + totalGARow.ToString() + "+" + colCode + totalOERow.ToString() + "+" + colCode + totalCSRow.ToString() + "+" + colCode + totalDLRow.ToString() + "+" + colCode + totalFORow.ToString();
            
                //marCADSheet.Cells[row, i].Formula = "=" + colCode + (row + 4).ToString() + "-" + colCode + (row + 2).ToString();
            }
            StyleOfSummary(marCADSheet, row);
            // adjust style
            AdjustSheetStyle(marCADSheet, row);


            AdjustSheetStyle(marCADSheet, row+4);
        }

        private void FillMichiganCADWorkSheet()
        {
            int row = 1;
            // title
            row = WriteSheetHeader("Michigan Income Statement at " + fiscalMonth.ToString("D2") + "-" + fiscalYear.ToString("D2") + " (CAD)", micCADSheet);
            // exchange rate
            row++;
            row = WriteExchangeRateRow(row, 3, "US", micCADSheet);
            // header
            row++;
            row = WriteHeader(micCADSheet, row);
            // write sales
            row++;
            row = WriteCategory(micCADSheet, row, 3, "CA", process.ss);
            // write cost of steels
            row++;
            row = WriteCategory(micCADSheet, row, 3, "CA", process.cs);
            // write direct labour
            row++;
            row = WriteCategory(micCADSheet, row, 3, "CA", process.dl);
            // write factory overhead
            row++;
            row = WriteCategory(micCADSheet, row, 3, "CA", process.fo);
            // write total cost of goods
            row++;
            micCADSheet.Cells[row, 1] = "TOTAL COST OF GOODS:";
            for (int i = 2; i <= 13; i++)
            {
                string colCode = Convert.ToChar((Convert.ToInt32('A') + i - 1)).ToString();
                micCADSheet.Cells[row, i].Formula = "=" + colCode + totalCSRow.ToString() + "+" + colCode + totalDLRow.ToString() + "+" + colCode + totalFORow.ToString();
            }
            StyleOfSummary(micCADSheet, row);
            row++;
            // write gross margin
            row++;
            micCADSheet.Cells[row, 1] = "GROSS MARGIN:";
            for (int i = 2; i <= 13; i++)
            {
                string colCode = Convert.ToChar((Convert.ToInt32('A') + i - 1)).ToString();
                micCADSheet.Cells[row, i].Formula = "=" + colCode + totalSSRow.ToString() + "+" + colCode + totalCSRow.ToString() + "+" + colCode + totalDLRow.ToString() + "+" + colCode + totalFORow.ToString();
            }
            StyleOfSummary(micCADSheet, row);
            row++;
            // write delivery and selling
            row++;
            row = WriteCategory(micCADSheet, row, 3, "CA", process.ds);
            // write general and administration
            row++;
            row = WriteCategory(micCADSheet, row, 3, "CA", process.ga);
            // write other expense and income
            row++;
            row = WriteCategory(micCADSheet, row, 3, "CA", process.oe);
            // write total expenses
            row++;
            micCADSheet.Cells[row, 1] = "TOTAL EXPENSES:";
            for (int i = 2; i <= 13; i++)
            {
                string colCode = Convert.ToChar((Convert.ToInt32('A') + i - 1)).ToString();
                micCADSheet.Cells[row, i].Formula = "=" + colCode + totalDSRow.ToString() + "+" + colCode + totalGARow.ToString() + "+" + colCode + totalOERow.ToString();
            }
            StyleOfSummary(micCADSheet, row);
            row++;

            // write provisional tax
            row+=3;
            for (int j = 2; j <= 7; j++)
            {
                string colCode = Convert.ToChar((Convert.ToInt32('A') + (j - 1) * 2 - 1)).ToString();
                micCADSheet.Cells[row, j * 2 - 1].NumberFormat = "0.00%";
                micCADSheet.Cells[row, j * 2 - 1].Formula = "=" + colCode + row.ToString() + "/" + colCode + totalSSRow.ToString();
            }
            row = WriteCategory(micCADSheet, row, 3, "CA", process.pt, true);
            row--;

            // adjust style
            AdjustSheetStyle(micCADSheet, row);
            // write gross margin

            micCADSheet.Cells[row, 1] = "TOTAL NET INCOME:";
            for (int i = 2; i <= 13; i++)
            {
                string colCode = Convert.ToChar((Convert.ToInt32('A') + i - 1)).ToString();
                micCADSheet.Cells[row, i].Formula = "=" + colCode + (row - 4).ToString() + "+" + colCode + (row - 2).ToString();
                //micCADSheet.Cells[row, i].Formula = "=" + colCode + totalSSRow.ToString() + "+" + colCode + totalDSRow.ToString() + "+" + colCode + totalGARow.ToString() + "+" + colCode + totalOERow.ToString() + "+" + colCode + totalCSRow.ToString() + "+" + colCode + totalDLRow.ToString() + "+" + colCode + totalFORow.ToString();

                for (int j = 2; j <= 7; j++)
                {
                    colCode = Convert.ToChar((Convert.ToInt32('A') + (j - 1) * 2 - 1)).ToString();
                    micCADSheet.Cells[row, j * 2 - 1].NumberFormat = "0.00%";
                    micCADSheet.Cells[row, j * 2 - 1].Formula = "=" + colCode + row.ToString() + "/" + colCode + totalSSRow.ToString();
                }
            }
            StyleOfSummary(micCADSheet, row);
            // adjust style
            AdjustSheetStyle(micCADSheet, row);


            // write before income tax
            row -= 4;
            micCADSheet.Cells[row, 1] = "NET INCOME BEFORE PROVISIONAL TAX";
            for (int i = 2; i <= 13; i++)
            {
                string colCode = Convert.ToChar((Convert.ToInt32('A') + i - 1)).ToString();
                micCADSheet.Cells[row, i].Formula = "=" + colCode + totalSSRow.ToString() + "+" + colCode + totalDSRow.ToString() + "+" + colCode + totalGARow.ToString() + "+" + colCode + totalOERow.ToString() + "+" + colCode + totalCSRow.ToString() + "+" + colCode + totalDLRow.ToString() + "+" + colCode + totalFORow.ToString();

                //micCADSheet.Cells[row, i].Formula = "=" + colCode + (row + 4).ToString() + "-" + colCode + (row + 2).ToString();
            }
            StyleOfSummary(micCADSheet, row);
            // adjust style
            AdjustSheetStyle(micCADSheet, row);
            AdjustSheetStyle(micCADSheet, row + 4);
            /*
            // write gross margin
            row++;
            micCADSheet.Cells[row, 1] = "TOTAL NET INCOME:";
            for (int i = 2; i <= 13; i++)
            {
                string colCode = Convert.ToChar((Convert.ToInt32('A') + i - 1)).ToString();
                micCADSheet.Cells[row, i].Formula = "=" + colCode + totalSSRow.ToString() + "+" + colCode + totalDSRow.ToString() + "+" + colCode + totalGARow.ToString() + "+" + colCode + totalOERow.ToString() + "+" + colCode + totalCSRow.ToString() + "+" + colCode + totalDLRow.ToString() + "+" + colCode + totalFORow.ToString();
            }
            StyleOfSummary(micCADSheet, row);
            // adjust style
            AdjustSheetStyle(micCADSheet, row);
            */
        }

        private void FillMichiganUSDWorkSheet()
        {
            int row = 1;
            // title
            row = WriteSheetHeader("Michigan Income Statement at " + fiscalMonth.ToString("D2") + "-" + fiscalYear.ToString("D2") + " (USD)", micUSDSheet);
            // header
            row++;
            row = WriteHeader(micUSDSheet, row);
            // write sales
            row++;
            row = WriteCategory(micUSDSheet, row, 3, "US", process.ss, true);
            // write cost of steels
            row++;
            row = WriteCategory(micUSDSheet, row, 3, "US", process.cs, true);
            // write direct labour
            row++;
            row = WriteCategory(micUSDSheet, row, 3, "US", process.dl, true);
            // write factory overhead
            row++;
            row = WriteCategory(micUSDSheet, row, 3, "US", process.fo, true);
            // write total cost of goods
            row++;
            micUSDSheet.Cells[row, 1] = "TOTAL COST OF GOODS:";
            for (int i = 2; i <= 13; i++)
            {
                string colCode = Convert.ToChar((Convert.ToInt32('A') + i - 1)).ToString();
                micUSDSheet.Cells[row, i].Formula = "=" + colCode + totalCSRow.ToString() + "+" + colCode + totalDLRow.ToString() + "+" + colCode + totalFORow.ToString();
            }
            StyleOfSummary(micUSDSheet, row);
            row++;
            // write gross margin
            row++;
            micUSDSheet.Cells[row, 1] = "GROSS MARGIN:";
            for (int i = 2; i <= 13; i++)
            {
                string colCode = Convert.ToChar((Convert.ToInt32('A') + i - 1)).ToString();
                micUSDSheet.Cells[row, i].Formula = "=" + colCode + totalSSRow.ToString() + "+" + colCode + totalCSRow.ToString() + "+" + colCode + totalDLRow.ToString() + "+" + colCode + totalFORow.ToString();
            }
            StyleOfSummary(micUSDSheet, row);
            row++;
            // write delivery and selling
            row++;
            row = WriteCategory(micUSDSheet, row, 3, "US", process.ds, true);
            // write general and administration
            row++;
            row = WriteCategory(micUSDSheet, row, 3, "US", process.ga, true);
            // write other expense and income
            row++;
            row = WriteCategory(micUSDSheet, row, 3, "US", process.oe, true);
            // write total expenses
            row++;
            micUSDSheet.Cells[row, 1] = "TOTAL EXPENSES:";
            for (int i = 2; i <= 13; i++)
            {
                string colCode = Convert.ToChar((Convert.ToInt32('A') + i - 1)).ToString();
                micUSDSheet.Cells[row, i].Formula = "=" + colCode + totalDSRow.ToString() + "+" + colCode + totalGARow.ToString() + "+" + colCode + totalOERow.ToString();
            }
            StyleOfSummary(micUSDSheet, row);
            row++;
            // write provisional tax
            row += 3;
            for (int j = 2; j <= 7; j++)
            {
                string colCode = Convert.ToChar((Convert.ToInt32('A') + (j - 1) * 2 - 1)).ToString();
                micUSDSheet.Cells[row, j * 2 - 1].NumberFormat = "0.00%";
                micUSDSheet.Cells[row, j * 2 - 1].Formula = "=" + colCode + row.ToString() + "/" + colCode + totalSSRow.ToString();
            }
            row = WriteCategory(micUSDSheet, row, 3, "US", process.pt, true);
            row--;

            // adjust style
            AdjustSheetStyle(micUSDSheet, row);
            // write gross margin

            micUSDSheet.Cells[row, 1] = "TOTAL NET INCOME:";
            for (int i = 2; i <= 13; i++)
            {
                string colCode = Convert.ToChar((Convert.ToInt32('A') + i - 1)).ToString();
                micUSDSheet.Cells[row, i].Formula = "=" + colCode + (row - 4).ToString() + "+" + colCode + (row - 2).ToString();
                //micUSDSheet.Cells[row, i].Formula = "=" + colCode + totalSSRow.ToString() + "+" + colCode + totalDSRow.ToString() + "+" + colCode + totalGARow.ToString() + "+" + colCode + totalOERow.ToString() + "+" + colCode + totalCSRow.ToString() + "+" + colCode + totalDLRow.ToString() + "+" + colCode + totalFORow.ToString();

                for (int j = 2; j <= 7; j++)
                {
                    colCode = Convert.ToChar((Convert.ToInt32('A') + (j - 1) * 2 - 1)).ToString();
                    micUSDSheet.Cells[row, j * 2 - 1].NumberFormat = "0.00%";
                    micUSDSheet.Cells[row, j * 2 - 1].Formula = "=" + colCode + row.ToString() + "/" + colCode + totalSSRow.ToString();
                }
            }
            StyleOfSummary(micUSDSheet, row);
            // adjust style
            AdjustSheetStyle(micUSDSheet, row);


            // write before income tax
            row -= 4;
            micUSDSheet.Cells[row, 1] = "NET INCOME  BEFORE PROVISIONAL TAX";
            for (int i = 2; i <= 13; i++)
            {
                string colCode = Convert.ToChar((Convert.ToInt32('A') + i - 1)).ToString();
                micUSDSheet.Cells[row, i].Formula = "=" + colCode + totalSSRow.ToString() + "+" + colCode + totalDSRow.ToString() + "+" + colCode + totalGARow.ToString() + "+" + colCode + totalOERow.ToString() + "+" + colCode + totalCSRow.ToString() + "+" + colCode + totalDLRow.ToString() + "+" + colCode + totalFORow.ToString();

                //micUSDSheet.Cells[row, i].Formula = "=" + colCode + (row + 4).ToString() + "-" + colCode + (row + 2).ToString();
            }
            StyleOfSummary(micUSDSheet, row);
            // adjust style
            AdjustSheetStyle(micUSDSheet, row);
            AdjustSheetStyle(micUSDSheet, row + 4);
        }

        private void FillTexasCADWorkSheet()
        {
            int row = 1;
            // title
            row = WriteSheetHeader("Texas Income Statement at " + fiscalMonth.ToString("D2") + "-" + fiscalYear.ToString("D2") + " (CAD)", texCADSheet);
            // exchange rate
            row++;
            row = WriteExchangeRateRow(row, 5, "US", texCADSheet);
            // header
            row++;
            row = WriteHeader(texCADSheet, row);
            // write sales
            row++;
            row = WriteCategory(texCADSheet, row, 5, "CA", process.ss);
            // write cost of steels
            row++;
            row = WriteCategory(texCADSheet, row, 5, "CA", process.cs);
            // write direct labour
            row++;
            row = WriteCategory(texCADSheet, row, 5, "CA", process.dl);
            // write factory overhead
            row++;
            row = WriteCategory(texCADSheet, row, 5, "CA", process.fo);
            // write total cost of goods
            row++;
            texCADSheet.Cells[row, 1] = "TOTAL COST OF GOODS:";
            for (int i = 2; i <= 13; i++)
            {
                string colCode = Convert.ToChar((Convert.ToInt32('A') + i - 1)).ToString();
                texCADSheet.Cells[row, i].Formula = "=" + colCode + totalCSRow.ToString() + "+" + colCode + totalDLRow.ToString() + "+" + colCode + totalFORow.ToString();
            }
            StyleOfSummary(texCADSheet, row);
            row++;
            // write gross margin
            row++;
            texCADSheet.Cells[row, 1] = "GROSS MARGIN:";
            for (int i = 2; i <= 13; i++)
            {
                string colCode = Convert.ToChar((Convert.ToInt32('A') + i - 1)).ToString();
                texCADSheet.Cells[row, i].Formula = "=" + colCode + totalSSRow.ToString() + "+" + colCode + totalCSRow.ToString() + "+" + colCode + totalDLRow.ToString() + "+" + colCode + totalFORow.ToString();
            }
            StyleOfSummary(texCADSheet, row);
            row++;
            // write delivery and selling
            row++;
            row = WriteCategory(texCADSheet, row, 5, "CA", process.ds);
            // write general and administration
            row++;
            row = WriteCategory(texCADSheet, row, 5, "CA", process.ga);
            // write other expense and income
            row++;
            row = WriteCategory(texCADSheet, row, 5, "CA", process.oe);
            // write total expenses
            row++;
            texCADSheet.Cells[row, 1] = "TOTAL EXPENSES:";
            for (int i = 2; i <= 13; i++)
            {
                string colCode = Convert.ToChar((Convert.ToInt32('A') + i - 1)).ToString();
                texCADSheet.Cells[row, i].Formula = "=" + colCode + totalDSRow.ToString() + "+" + colCode + totalGARow.ToString() + "+" + colCode + totalOERow.ToString();
            }
            StyleOfSummary(texCADSheet, row);
            row++;
            // write provisional tax
            row += 3;
            for (int j = 2; j <= 7; j++)
            {
                string colCode = Convert.ToChar((Convert.ToInt32('A') + (j - 1) * 2 - 1)).ToString();
                texCADSheet.Cells[row, j * 2 - 1].NumberFormat = "0.00%";
                texCADSheet.Cells[row, j * 2 - 1].Formula = "=" + colCode + row.ToString() + "/" + colCode + totalSSRow.ToString();
            }
            row = WriteCategory(texCADSheet, row, 5, "CA", process.pt, true);
            row--;

            // adjust style
            AdjustSheetStyle(texCADSheet, row);
            // write gross margin

            texCADSheet.Cells[row, 1] = "TOTAL NET INCOME:";
            for (int i = 2; i <= 13; i++)
            {
                string colCode = Convert.ToChar((Convert.ToInt32('A') + i - 1)).ToString();
                texCADSheet.Cells[row, i].Formula = "=" + colCode + (row - 4).ToString() + "+" + colCode + (row - 2).ToString();
                //texCADSheet.Cells[row, i].Formula = "=" + colCode + totalSSRow.ToString() + "+" + colCode + totalDSRow.ToString() + "+" + colCode + totalGARow.ToString() + "+" + colCode + totalOERow.ToString() + "+" + colCode + totalCSRow.ToString() + "+" + colCode + totalDLRow.ToString() + "+" + colCode + totalFORow.ToString();

                for (int j = 2; j <= 7; j++)
                {
                    colCode = Convert.ToChar((Convert.ToInt32('A') + (j - 1) * 2 - 1)).ToString();
                    texCADSheet.Cells[row, j * 2 - 1].NumberFormat = "0.00%";
                    texCADSheet.Cells[row, j * 2 - 1].Formula = "=" + colCode + row.ToString() + "/" + colCode + totalSSRow.ToString();
                }
            }
            StyleOfSummary(texCADSheet, row);
            // adjust style
            AdjustSheetStyle(texCADSheet, row);


            // write before income tax
            row -= 4;
            texCADSheet.Cells[row, 1] = "NET INCOME  BEFORE PROVISIONAL TAX";
            for (int i = 2; i <= 13; i++)
            {
                string colCode = Convert.ToChar((Convert.ToInt32('A') + i - 1)).ToString();
                texCADSheet.Cells[row, i].Formula = "=" + colCode + totalSSRow.ToString() + "+" + colCode + totalDSRow.ToString() + "+" + colCode + totalGARow.ToString() + "+" + colCode + totalOERow.ToString() + "+" + colCode + totalCSRow.ToString() + "+" + colCode + totalDLRow.ToString() + "+" + colCode + totalFORow.ToString();

                //texCADSheet.Cells[row, i].Formula = "=" + colCode + (row + 4).ToString() + "-" + colCode + (row + 2).ToString();
            }
            StyleOfSummary(texCADSheet, row);
            // adjust style
            AdjustSheetStyle(texCADSheet, row);
            AdjustSheetStyle(texCADSheet, row + 4);
        }

        private void FillTexasUSDWorkSheet()
        {
            int row = 1;
            // title
            row = WriteSheetHeader("Texas Income Statement at " + fiscalMonth.ToString("D2") + "-" + fiscalYear.ToString("D2") + " (USD)", texUSDSheet);
            // header
            row++;
            row = WriteHeader(texUSDSheet, row);
            // write sales
            row++;
            row = WriteCategory(texUSDSheet, row, 5, "US", process.ss, true);
            // write cost of steels
            row++;
            row = WriteCategory(texUSDSheet, row, 5, "US", process.cs, true);
            // write direct labour
            row++;
            row = WriteCategory(texUSDSheet, row, 5, "US", process.dl, true);
            // write factory overhead
            row++;
            row = WriteCategory(texUSDSheet, row, 5, "US", process.fo, true);
            // write total cost of goods
            row++;
            texUSDSheet.Cells[row, 1] = "TOTAL COST OF GOODS:";
            for (int i = 2; i <= 13; i++)
            {
                string colCode = Convert.ToChar((Convert.ToInt32('A') + i - 1)).ToString();
                texUSDSheet.Cells[row, i].Formula = "=" + colCode + totalCSRow.ToString() + "+" + colCode + totalDLRow.ToString() + "+" + colCode + totalFORow.ToString();
            }
            StyleOfSummary(texUSDSheet, row);
            row++;
            // write gross margin
            row++;
            texUSDSheet.Cells[row, 1] = "GROSS MARGIN:";
            for (int i = 2; i <= 13; i++)
            {
                string colCode = Convert.ToChar((Convert.ToInt32('A') + i - 1)).ToString();
                texUSDSheet.Cells[row, i].Formula = "=" + colCode + totalSSRow.ToString() + "+" + colCode + totalCSRow.ToString() + "+" + colCode + totalDLRow.ToString() + "+" + colCode + totalFORow.ToString();
            }
            StyleOfSummary(texUSDSheet, row);
            row++;
            // write delivery and selling
            row++;
            row = WriteCategory(texUSDSheet, row, 5, "US", process.ds, true);
            // write general and administration
            row++;
            row = WriteCategory(texUSDSheet, row, 5, "US", process.ga, true);
            // write other expense and income
            row++;
            row = WriteCategory(texUSDSheet, row, 5, "US", process.oe, true);
            // write total expenses
            row++;
            texUSDSheet.Cells[row, 1] = "TOTAL EXPENSES:";
            for (int i = 2; i <= 13; i++)
            {
                string colCode = Convert.ToChar((Convert.ToInt32('A') + i - 1)).ToString();
                texUSDSheet.Cells[row, i].Formula = "=" + colCode + totalDSRow.ToString() + "+" + colCode + totalGARow.ToString() + "+" + colCode + totalOERow.ToString();
            }
            StyleOfSummary(texUSDSheet, row);
            row++;
            // write provisional tax
            row += 3;
            for (int j = 2; j <= 7; j++)
            {
                string colCode = Convert.ToChar((Convert.ToInt32('A') + (j - 1) * 2 - 1)).ToString();
                texUSDSheet.Cells[row, j * 2 - 1].NumberFormat = "0.00%";
                texUSDSheet.Cells[row, j * 2 - 1].Formula = "=" + colCode + row.ToString() + "/" + colCode + totalSSRow.ToString();
            }
            row = WriteCategory(texUSDSheet, row, 5, "US", process.pt, true);
            row--;

            // adjust style
            AdjustSheetStyle(texUSDSheet, row);
            // write gross margin

            texUSDSheet.Cells[row, 1] = "TOTAL NET INCOME:";
            for (int i = 2; i <= 13; i++)
            {
                string colCode = Convert.ToChar((Convert.ToInt32('A') + i - 1)).ToString();
                texUSDSheet.Cells[row, i].Formula = "=" + colCode + (row - 4).ToString() + "+" + colCode + (row - 2).ToString();
                //texUSDSheet.Cells[row, i].Formula = "=" + colCode + totalSSRow.ToString() + "+" + colCode + totalDSRow.ToString() + "+" + colCode + totalGARow.ToString() + "+" + colCode + totalOERow.ToString() + "+" + colCode + totalCSRow.ToString() + "+" + colCode + totalDLRow.ToString() + "+" + colCode + totalFORow.ToString();

                for (int j = 2; j <= 7; j++)
                {
                    colCode = Convert.ToChar((Convert.ToInt32('A') + (j - 1) * 2 - 1)).ToString();
                    texUSDSheet.Cells[row, j * 2 - 1].NumberFormat = "0.00%";
                    texUSDSheet.Cells[row, j * 2 - 1].Formula = "=" + colCode + row.ToString() + "/" + colCode + totalSSRow.ToString();
                }
            }
            StyleOfSummary(texUSDSheet, row);
            // adjust style
            AdjustSheetStyle(texUSDSheet, row);


            // write before income tax
            row -= 4;
            texUSDSheet.Cells[row, 1] = "NET INCOME  BEFORE PROVISIONAL TAX";
            for (int i = 2; i <= 13; i++)
            {
                string colCode = Convert.ToChar((Convert.ToInt32('A') + i - 1)).ToString();
                texUSDSheet.Cells[row, i].Formula = "=" + colCode + totalSSRow.ToString() + "+" + colCode + totalDSRow.ToString() + "+" + colCode + totalGARow.ToString() + "+" + colCode + totalOERow.ToString() + "+" + colCode + totalCSRow.ToString() + "+" + colCode + totalDLRow.ToString() + "+" + colCode + totalFORow.ToString();

                //texUSDSheet.Cells[row, i].Formula = "=" + colCode + (row + 4).ToString() + "-" + colCode + (row + 2).ToString();
            }
            StyleOfSummary(texUSDSheet, row);
            // adjust style
            AdjustSheetStyle(texUSDSheet, row);
            AdjustSheetStyle(texUSDSheet, row + 4);
        }

        private void FillColombiaCADWorkSheet()
        {
            int row = 1;
            // title
            row = WriteSheetHeader("Colombia Income Statement at " + fiscalMonth.ToString("D2") + "-" + fiscalYear.ToString("D2") + " (CAD)", colCADSheet);
            // exchange rate
            row++;
            row = WriteExchangeRateRow(row, 4, "CP", colCADSheet);
            // header
            row++;
            row = WriteHeader(colCADSheet, row);
            // write sales
            row++;
            row = WriteCategory(colCADSheet, row, 4, "CA", process.ss);
            // write cost of steels
            row++;
            row = WriteCategory(colCADSheet, row, 4, "CA", process.cs);
            // write direct labour
            row++;
            row = WriteCategory(colCADSheet, row, 4, "CA", process.dl);
            // write factory overhead
            row++;
            row = WriteCategory(colCADSheet, row, 4, "CA", process.fo);
            // write total cost of goods
            row++;
            colCADSheet.Cells[row, 1] = "TOTAL COST OF GOODS:";
            for (int i = 2; i <= 13; i++)
            {
                string colCode = Convert.ToChar((Convert.ToInt32('A') + i - 1)).ToString();
                colCADSheet.Cells[row, i].Formula = "=" + colCode + totalCSRow.ToString() + "+" + colCode + totalDLRow.ToString() + "+" + colCode + totalFORow.ToString();
            }
            StyleOfSummary(colCADSheet, row);
            row++;
            // write gross margin
            row++;
            colCADSheet.Cells[row, 1] = "GROSS MARGIN:";
            for (int i = 2; i <= 13; i++)
            {
                string colCode = Convert.ToChar((Convert.ToInt32('A') + i - 1)).ToString();
                colCADSheet.Cells[row, i].Formula = "=" + colCode + totalSSRow.ToString() + "+" + colCode + totalCSRow.ToString() + "+" + colCode + totalDLRow.ToString() + "+" + colCode + totalFORow.ToString();
            }
            StyleOfSummary(colCADSheet, row);
            row++;
            // write delivery and selling
            row++;
            row = WriteCategory(colCADSheet, row, 4, "CA", process.ds);
            // write general and administration
            row++;
            row = WriteCategory(colCADSheet, row, 4, "CA", process.ga);
            // write other expense and income
            row++;
            row = WriteCategory(colCADSheet, row, 4, "CA", process.oe);
            // write total expenses
            row++;
            colCADSheet.Cells[row, 1] = "TOTAL EXPENSES:";
            for (int i = 2; i <= 13; i++)
            {
                string colCode = Convert.ToChar((Convert.ToInt32('A') + i - 1)).ToString();
                colCADSheet.Cells[row, i].Formula = "=" + colCode + totalDSRow.ToString() + "+" + colCode + totalGARow.ToString() + "+" + colCode + totalOERow.ToString();
            }
            StyleOfSummary(colCADSheet, row);
            row++;
            // write provisional tax
            row += 3;
            for (int j = 2; j <= 7; j++)
            {
                string colCode = Convert.ToChar((Convert.ToInt32('A') + (j - 1) * 2 - 1)).ToString();
                colCADSheet.Cells[row, j * 2 - 1].NumberFormat = "0.00%";
                colCADSheet.Cells[row, j * 2 - 1].Formula = "=" + colCode + row.ToString() + "/" + colCode + totalSSRow.ToString();
            }
            row = WriteCategory(colCADSheet, row, 4, "CA", process.pt);
            row--;

            // adjust style
            AdjustSheetStyle(colCADSheet, row);
            // write gross margin

            colCADSheet.Cells[row, 1] = "TOTAL NET INCOME:";
            for (int i = 2; i <= 13; i++)
            {
                string colCode = Convert.ToChar((Convert.ToInt32('A') + i - 1)).ToString();
                colCADSheet.Cells[row, i].Formula = "=" + colCode + (row - 4).ToString() + "+" + colCode + (row - 2).ToString();
                //colCADSheet.Cells[row, i].Formula = "=" + colCode + totalSSRow.ToString() + "+" + colCode + totalDSRow.ToString() + "+" + colCode + totalGARow.ToString() + "+" + colCode + totalOERow.ToString() + "+" + colCode + totalCSRow.ToString() + "+" + colCode + totalDLRow.ToString() + "+" + colCode + totalFORow.ToString();

                for (int j = 2; j <= 7; j++)
                {
                    colCode = Convert.ToChar((Convert.ToInt32('A') + (j - 1) * 2 - 1)).ToString();
                    colCADSheet.Cells[row, j * 2 - 1].NumberFormat = "0.00%";
                    colCADSheet.Cells[row, j * 2 - 1].Formula = "=" + colCode + row.ToString() + "/" + colCode + totalSSRow.ToString();
                }
            }
            StyleOfSummary(colCADSheet, row);
            // adjust style
            AdjustSheetStyle(colCADSheet, row);


            // write before income tax
            row -= 4;
            colCADSheet.Cells[row, 1] = "NET INCOME  BEFORE PROVISIONAL TAX";
            for (int i = 2; i <= 13; i++)
            {
                string colCode = Convert.ToChar((Convert.ToInt32('A') + i - 1)).ToString();
                colCADSheet.Cells[row, i].Formula = "=" + colCode + totalSSRow.ToString() + "+" + colCode + totalDSRow.ToString() + "+" + colCode + totalGARow.ToString() + "+" + colCode + totalOERow.ToString() + "+" + colCode + totalCSRow.ToString() + "+" + colCode + totalDLRow.ToString() + "+" + colCode + totalFORow.ToString();

                //colCADSheet.Cells[row, i].Formula = "=" + colCode + (row + 4).ToString() + "-" + colCode + (row + 2).ToString();
            }
            StyleOfSummary(colCADSheet, row);
            // adjust style
            AdjustSheetStyle(colCADSheet, row);
            AdjustSheetStyle(colCADSheet, row + 4);
        }

        private void FillColombiaPESOWorkSheet()
        {
            int row = 1;
            // title
            row = WriteSheetHeader("Colombia Income Statement at " + fiscalMonth.ToString("D2") + "-" + fiscalYear.ToString("D2") + " (PESO)", colPESOSheet);
            // header
            row++;
            row = WriteHeader(colPESOSheet, row);
            // write sales
            row++;
            row = WriteCategory(colPESOSheet, row, 4, "CP", process.ss, true);
            // write cost of steels
            row++;
            row = WriteCategory(colPESOSheet, row, 4, "CP", process.cs, true);
            // write direct labour
            row++;
            row = WriteCategory(colPESOSheet, row, 4, "CP", process.dl, true);
            // write factory overhead
            row++;
            row = WriteCategory(colPESOSheet, row, 4, "CP", process.fo, true);
            // write total cost of goods
            row++;
            colPESOSheet.Cells[row, 1] = "TOTAL COST OF GOODS:";
            for (int i = 2; i <= 13; i++)
            {
                string colCode = Convert.ToChar((Convert.ToInt32('A') + i - 1)).ToString();
                colPESOSheet.Cells[row, i].Formula = "=" + colCode + totalCSRow.ToString() + "+" + colCode + totalDLRow.ToString() + "+" + colCode + totalFORow.ToString();
            }
            StyleOfSummary(colPESOSheet, row);
            row++;
            // write gross margin
            row++;
            colPESOSheet.Cells[row, 1] = "GROSS MARGIN:";
            for (int i = 2; i <= 13; i++)
            {
                string colCode = Convert.ToChar((Convert.ToInt32('A') + i - 1)).ToString();
                colPESOSheet.Cells[row, i].Formula = "=" + colCode + totalSSRow.ToString() + "+" + colCode + totalCSRow.ToString() + "+" + colCode + totalDLRow.ToString() + "+" + colCode + totalFORow.ToString();
            }
            StyleOfSummary(colPESOSheet, row);
            row++;
            // write delivery and selling
            row++;
            row = WriteCategory(colPESOSheet, row, 4, "CP", process.ds, true);
            // write general and administration
            row++;
            row = WriteCategory(colPESOSheet, row, 4, "CP", process.ga, true);
            // write other expense and income
            row++;
            row = WriteCategory(colPESOSheet, row, 4, "CP", process.oe, true);
            // write total expenses
            row++;
            colPESOSheet.Cells[row, 1] = "TOTAL EXPENSES:";
            for (int i = 2; i <= 13; i++)
            {
                string colCode = Convert.ToChar((Convert.ToInt32('A') + i - 1)).ToString();
                colPESOSheet.Cells[row, i].Formula = "=" + colCode + totalDSRow.ToString() + "+" + colCode + totalGARow.ToString() + "+" + colCode + totalOERow.ToString();
            }
            StyleOfSummary(colPESOSheet, row);
            row++;
            // write provisional tax
            row += 3;
            for (int j = 2; j <= 7; j++)
            {
                string colCode = Convert.ToChar((Convert.ToInt32('A') + (j - 1) * 2 - 1)).ToString();
                colPESOSheet.Cells[row, j * 2 - 1].NumberFormat = "0.00%";
                colPESOSheet.Cells[row, j * 2 - 1].Formula = "=" + colCode + row.ToString() + "/" + colCode + totalSSRow.ToString();
            }
            row = WriteCategory(colPESOSheet, row, 4, "CP", process.pt, true);
            row--;

            // adjust style
            AdjustSheetStyle(colPESOSheet, row);
            // write gross margin

            colPESOSheet.Cells[row, 1] = "TOTAL NET INCOME:";
            for (int i = 2; i <= 13; i++)
            {
                string colCode = Convert.ToChar((Convert.ToInt32('A') + i - 1)).ToString();
                colPESOSheet.Cells[row, i].Formula = "=" + colCode + (row - 4).ToString() + "+" + colCode + (row - 2).ToString();
                //colPESOSheet.Cells[row, i].Formula = "=" + colCode + totalSSRow.ToString() + "+" + colCode + totalDSRow.ToString() + "+" + colCode + totalGARow.ToString() + "+" + colCode + totalOERow.ToString() + "+" + colCode + totalCSRow.ToString() + "+" + colCode + totalDLRow.ToString() + "+" + colCode + totalFORow.ToString();

                for (int j = 2; j <= 7; j++)
                {
                    colCode = Convert.ToChar((Convert.ToInt32('A') + (j - 1) * 2 - 1)).ToString();
                    colPESOSheet.Cells[row, j * 2 - 1].NumberFormat = "0.00%";
                    colPESOSheet.Cells[row, j * 2 - 1].Formula = "=" + colCode + row.ToString() + "/" + colCode + totalSSRow.ToString();
                }
            }
            StyleOfSummary(colPESOSheet, row);
            // adjust style
            AdjustSheetStyle(colPESOSheet, row);


            // write before income tax
            row -= 4;
            colPESOSheet.Cells[row, 1] = "NET INCOME  BEFORE PROVISIONAL TAX";
            for (int i = 2; i <= 13; i++)
            {
                string colCode = Convert.ToChar((Convert.ToInt32('A') + i - 1)).ToString();
                colPESOSheet.Cells[row, i].Formula = "=" + colCode + totalSSRow.ToString() + "+" + colCode + totalDSRow.ToString() + "+" + colCode + totalGARow.ToString() + "+" + colCode + totalOERow.ToString() + "+" + colCode + totalCSRow.ToString() + "+" + colCode + totalDLRow.ToString() + "+" + colCode + totalFORow.ToString();

                //colPESOSheet.Cells[row, i].Formula = "=" + colCode + (row + 4).ToString() + "-" + colCode + (row + 2).ToString();
            }
            StyleOfSummary(colPESOSheet, row);
            // adjust style
            AdjustSheetStyle(colPESOSheet, row);
            AdjustSheetStyle(colPESOSheet, row + 4);
        }

        // write consolidate category
        private int WriteConsolidateCategory(Category category, int row)
        {
            bool hasProductionSales = false;
            bool hasSteelSurcharge = false;
            bool hasOtherSales = false;
            bool hasTotalSales = false;

            consolidateSheet.Cells[row, 1] = category.name;
            consolidateSheet.Cells.get_Range("A" + row.ToString()).Interior.ColorIndex = 27;
            row++;
            
            int startRow = row;
            foreach (Group group in category.groupList)
            {

                switch (group.name)
                {
                    case "PROVISION FOR INCOME TAX":
                        provisionRow = row;
                        break;
                    case "FACTORY SOUTH AMERICA TRAVEL":
                        factorySATravelRow = row;
                        break;
                    case "OFFICE SOUTH AMERICA TRAVEL":
                        officeSATravelRow = row;
                        break;
                    case "DIRECT LABOUR SHOP":
                        directLabourShop = row;
                        break;
                    case "DIRECT LABOUR HEAT TREAT":
                        directLabourHeat = row;
                        break;
                    case "CAM SALARIES":
                        directLabourCAM = row;
                        break;
                    case "CAD SALARIES":
                        factoryCAD = row;
                        break;
                    case "INDIRECT LABOUR ISO IT PURCHASER":
                        factoryIndirectLabour = row;
                        break;
                    case "SUPERVISORY SALARIES":
                        factorySupervisor = row;
                        break;
                    case "FACTORY EMPLOYEE BENEFITS":
                        factoryEmployeeBenefits = row;
                        break;
                    case "FACTORY GROUP INSURANCE":
                        factoryGroupInsurance = row;
                        break;
                    case "STATUTORY HOLIDAY":
                        factoryStatHoliday = row;
                        break;
                    case "VACATION PAY EXPENSE":
                        factoryVacationPay = row;
                        break;
                    case "WORKERS COMPENSATION":
                        factoryWorkersCompensation = row;
                        break;
                    case "SALARIES":
                        officeSalaries = row;
                        break;
                    case "SALES SALARIES":
                        salesSalaries = row;
                        break;
                    case "EMPLOYEE BENEFITS SALES":
                        salesEmployeeBenefits = row;
                        break;
                    case "GROUP INSURANCE SALES":
                        salesGroupInsurance = row;
                        break;
                    case "STATUTORY HOLIDAY SALES":
                        salesStatHoliday = row;
                        break;
                    case "VACATION PAY SALES":
                        salesVacationPay = row;
                        break;
                    case "WORKERS COMPENSATION SALES":
                        salesWorkersCompensation = row;
                        break;
                    case "OFFICE EMPLOYEE BENEFITS":
                        officeEmployeeBenefits = row;
                        break;
                    case "OFFICE GROUP INSURANCE":
                        officeGroupInsurance = row;
                        break;
                    case "PAYROLL TAXES":
                        officePayrollTaxes = row;
                        break;
                    case "OFFICE STATUTORY HOLIDAY":
                        officeStatHoliday = row;
                        break;
                    case "OFFICE VACATION PAY":
                        officeVacationPay = row;
                        break;
                    case "OFFICE WORKER'S COMPENSATION":
                        officeWorkersCompensation = row;
                        break;
                    case "OFFICE RENT":
                        officeRent = row;
                        break;
                    case "FACTORY RENT":
                        factoryRent = row;
                        break;
                    case "DEPRECIATION BUILDING":
                        factoryDepreBuilding = row;
                        break;
                    case "DEPRECIATION BUILDING IMPROVEMENT":
                        factoryDepreBuildingImprov = row;
                        break;
                    case "MAINTENANCE AND REPAIR BUILDING":
                        factoryReqMainBuilding = row;
                        break;
                    case "REALTY TAX":
                        factoryPropertyTax = row;
                        break;
                    case "DEPRECIATION MACHINE AND EQUIPMENT":
                        factoryDepreMachine = row;
                        break;
                    case "DEPRECIATION FURNITURE AND FIXTURE":
                        factoryDepreFurniture = row;
                        break;
                    case "DEPRECIATION SOFTWARE":
                        factoryDepreSoftware = row;
                        break;
                    case "OFFICE DEPRECIATION EXPENSE":
                        officeDepreFurniture = row;
                        break;
                    case "SOFTWARE AMORTIZATION":
                        officeSoftwareAmort = row;
                        break;
                    case "TOOL AMORTIZATION":
                        factoryToolAmort = row;
                        break;
                    case "DEPRECIATION AUTOMOBILE":
                        salesDepreAuto = row;
                        break;
                    case "TOOLS EXPENSE":
                        factoryToolExpense = row;
                        break;
                    case "SHIPPING SUPPLIES":
                        factoryShippingSupplies = row;
                        break;
                    case "SHOP SUPPLIES EXPENSE":
                        factoryShopSupplies = row;
                        break;
                    case "SHOP SUPPLIES HEAT TREAT":
                        factoryHeatTreatSupplies = row;
                        break;
                    case "CAD and CAM SUPPLIES":
                        factoryCADCAMSupplies = row;
                        break;
                    case "OFFICE SUPPLIES":
                        officeSupplies = row;
                        break;
                    case "SHOP TRAVEL":
                        factoryTravel = row;
                        break;
                    case "SHOP MEALS AND ENTERTAINMENT":
                        factoryMeals = row;
                        break;
                    case "SHOP AIR FARE":
                        factoryAirFare = row;
                        break;
                    case "NON DEDUCTIBLE EXPENSE GOLF":
                        salesGolf = row;
                        break;
                    case "SELLING AND TRAVEL MEALS AND ENTERTAINMENT":
                        salesMeals = row;
                        break;
                    case "SELLING AND TRAVEL EXPENSES":
                        salesTravel = row;
                        break;
                    case "AIR FARE":
                        salesAirFare = row;
                        break;
                    case "MEAL AND ENTERTAINMENT":
                        officeMeals = row;
                        break;
                    case "TRAVEL EXPENSES":
                        officeTravel = row;
                        break;
                    case "OFFICE AIR FARE":
                        officeAirFare = row;
                        break;
                }

                if (group.name.Contains("STEEL SURCHARGE"))
                    consolidateSheet.Rows[row].Hidden = true;

                if (!hasProductionSales && category.name == "SALES" && Implement_Changes)
                {
                    consolidateSheet.Cells[row, 1] = "PRODUCTION SALES";
                    //consolidateSheet.Cells.get_Range("A" + row.ToString()).Interior.ColorIndex = 40;
                    ProductionSalesRow = row;
                    row++;
                    hasProductionSales = true;
                }
                consolidateSheet.Cells[row, 1] = group.name;
                consolidateSheet.Cells[row, 2] = (group.plant01.actualThisYearList[fiscalMonth].GetAmount("CA")*switchpositivenegative).ToString("C2");
                consolidateSheet.Cells[row, 4] = (group.plant03.actualThisYearList[fiscalMonth].GetAmount("CA")*switchpositivenegative).ToString("C2");
                consolidateSheet.Cells[row, 6] = (group.plant05.actualThisYearList[fiscalMonth].GetAmount("CA")*switchpositivenegative).ToString("C2");
                if (fiscalMonth == 1)
                {
                    consolidateSheet.Cells[row, 8] = ((group.plant04.actualThisYearList[fiscalMonth].GetAmount("CA") + group.plant41.actualThisYearList[fiscalMonth].GetAmount("CA") + group.plant48.actualThisYearList[fiscalMonth].GetAmount("CA") + group.plant49.actualThisYearList[fiscalMonth].GetAmount("CA"))*switchpositivenegative).ToString("C2");
                }
                else
                {
                    ExcoCalendar calendar = new ExcoCalendar(group.plant04.calendar.GetCalendarYear(), group.plant04.calendar.GetCalendarMonth(), true, 1);
                    consolidateSheet.Cells[row, 8] = ((new ExcoMoney(calendar.GetNextCalendarMonth(), (group.plant04.actualThisYearList[fiscalMonth] + group.plant41.actualThisYearList[fiscalMonth] + group.plant48.actualThisYearList[fiscalMonth] + group.plant49.actualThisYearList[fiscalMonth]).amountCP - (group.plant04.actualThisYearList[fiscalMonth - 1] + group.plant41.actualThisYearList[fiscalMonth - 1] + group.plant48.actualThisYearList[fiscalMonth - 1] + group.plant49.actualThisYearList[fiscalMonth - 1]).amountCP, "CP")).GetAmount("CA") * switchpositivenegative).ToString("C2");
                }
                consolidateSheet.Cells[row, 10].Formula = "=B" + row.ToString() + "+D" + row.ToString() + "+F" + row.ToString() + "+H" + row.ToString();
                row++;

                int surcharge_total_row = 0;

                if (!hasSteelSurcharge && group.name.Contains("INTERDIVISION SALES") && category.name == "SALES" && Implement_Changes)
                {
                    StyleOfSubSummary(consolidateSheet, row);
                    consolidateSheet.Cells[row, 1] = "TOTAL PRODUCTION SALES";
                    ProductionSalesRowTotal = row;
                    for (int i = 2; i <= 11; i++)
                    {
                        string colCode = Convert.ToChar((Convert.ToInt32('A') + i - 1)).ToString();
                        consolidateSheet.Cells[row, i].Formula = "=SUM(" + colCode + (ProductionSalesRow + 1).ToString() + ":" + colCode + (row - 1).ToString() + ")";
                    }
                    StyleOfSummary(consolidateSheet, row);
                    row++;
                    row++;
                    consolidateSheet.Cells[row, 1] = "STEEL SURCHARGE";
                    //consolidateSheet.Cells.get_Range("A" + row.ToString()).Interior.ColorIndex = 40;
                    SteelSurchargeRow = row;
                    consolidateSheet.Rows[row].Hidden = true;
                    row++;
                    hasSteelSurcharge = true;
                }
                else if (!hasOtherSales && group.name.Contains("INTERDIVISION SALES STEEL SURCHARGE") && category.name == "SALES" && Implement_Changes)
                {
                    StyleOfSubSummary(consolidateSheet, row);
                    consolidateSheet.Cells[row, 1] = "TOTAL STEEL SURCHARGE";
                    surcharge_total_row = row;
                    for (int i = 2; i <= 11; i++)
                    {
                        string colCode = Convert.ToChar((Convert.ToInt32('A') + i - 1)).ToString();
                        consolidateSheet.Cells[row, i].Formula = "=SUM(" + colCode + (SteelSurchargeRow + 1).ToString() + ":" + colCode + (row - 1).ToString() + ")";
                    }
                    StyleOfSummary(consolidateSheet, row);
                    SteelSurchargeRowTotal = row;
                    consolidateSheet.Rows[row].Hidden = true;
                    row++;
                    consolidateSheet.Rows[row].Hidden = true;
                    row++;
                    consolidateSheet.Cells[row, 1] = "OTHER SALES";
                    //consolidateSheet.Cells.get_Range("A" + row.ToString()).Interior.ColorIndex = 40;
                    OtherSalesRow = row;
                    row++;
                    hasOtherSales = true;

                    consolidateSheet.Cells[row, 1] = "STEEL SURCHARGE";
                    for (int i = 2; i <= 11; i++)
                    {
                        string colCode = Convert.ToChar((Convert.ToInt32('A') + i - 1)).ToString();
                        consolidateSheet.Cells[row, i].Formula = "=" + colCode + (surcharge_total_row).ToString();
                    }
                    row++;
                }
                else if (!hasTotalSales && group.name.Contains("SCRAP SALES") && category.name == "SALES" && Implement_Changes)
                {
                    StyleOfSubSummary(consolidateSheet, row);
                    consolidateSheet.Cells[row, 1] = "TOTAL OTHER SALES";
                    for (int i = 2; i <= 11; i++)
                    {
                        string colCode = Convert.ToChar((Convert.ToInt32('A') + i - 1)).ToString();
                        consolidateSheet.Cells[row, i].Formula = "=SUM(" + colCode + (OtherSalesRow + 1).ToString() + ":" + colCode + (row - 1).ToString() + ")";
                    }
                    StyleOfSummary(consolidateSheet, row);
                    OtherSalesRowTotal = row;
                    row++;
                    hasTotalSales = true;
                    row++;
                }
            }
            switch (category.name)
            {
                case "SALES":
                    totalSSRow = row;
                    break;
                case "COST OF STEELS":
                    totalCSRow = row;
                    break;
                case "DELIVERY AND SELLING":
                    totalDSRow = row;
                    break;
                case "FACTORY OVERHEAD":
                    totalFORow = row;
                    break;
                case "GENERAL AND ADMINISTRATION":
                    totalGARow = row;
                    break;
                case "OTHER EXPENSE AND INCOME":
                    totalOERow = row;
                    break;
                case "DIRECT LABOUR":
                    totalDLRow = row;
                    break;
                case "":
                    totalPTRow = row;
                    break;
                default:
                    throw new Exception("Unknown category " + category.name);
            }
            consolidateSheet.Cells[row, 1] = "TOTAL :";

            if (ProductionSalesRowTotal > 0 && SteelSurchargeRowTotal > 0 && OtherSalesRowTotal > 0)
            {

                // write percentage
                for (int i = 1; i <= 5; i++)
                {
                    string colCode = Convert.ToChar((Convert.ToInt32('A') + i * 2)).ToString();
                    string prevColCode = Convert.ToChar((Convert.ToInt32('A') + (i * 2 - 1))).ToString();
                    for (int j = startRow; j < row; j++)
                    {
                        consolidateSheet.Cells[j, i * 2 + 1].NumberFormat = "0.00%";
                        //sheet.Cells[j, i * 2 + 1].Formula = "=" + prevColCode + j.ToString() + "/" + prevColCode + totalSSRow.ToString();
                        consolidateSheet.Cells[j, i * 2 + 1].Formula = "=IF(" + prevColCode + j.ToString() + "<>\"\"," + prevColCode + j.ToString() + "/" + prevColCode + totalSSRow.ToString() + ", \"\")";
                    }
                }

                for (int i = 1; i <= 5; i++)
                {
                    string colCode = Convert.ToChar((Convert.ToInt32('A') + i * 2 - 1)).ToString();
                    consolidateSheet.Cells[row, i * 2].Formula = "=" + colCode + ProductionSalesRowTotal.ToString() + "+" + colCode + OtherSalesRowTotal.ToString();// "+" + colCode + SteelSurchargeRowTotal.ToString() + 
                }
                for (int i = 1; i <= 5; i++)
                {
                    string colCode = Convert.ToChar((Convert.ToInt32('A') + i * 2)).ToString();
                    consolidateSheet.Cells[row, i * 2 + 1].Formula = "=" + colCode + ProductionSalesRowTotal.ToString() + "+" + colCode + OtherSalesRowTotal.ToString(); // "+" + colCode + SteelSurchargeRowTotal.ToString() + 
                }

                ProductionSalesRowTotal = 0;
                SteelSurchargeRowTotal = 0;
                OtherSalesRowTotal = 0;
                StyleOfSummary(consolidateSheet, row);
            }
            else
            {
                for (int i = 1; i <= 5; i++)
                {
                    string colCode = Convert.ToChar((Convert.ToInt32('A') + i * 2 - 1)).ToString();
                    consolidateSheet.Cells[row, i * 2].Formula = "=sum(" + colCode + startRow.ToString() + ":" + colCode + (row - 1).ToString() + ")";
                }
                // percentages
                for (int i = 1; i <= 5; i++)
                {
                    string colCode = Convert.ToChar((Convert.ToInt32('A') + i * 2)).ToString();
                    string prevColCode = Convert.ToChar((Convert.ToInt32('A') + (i * 2 - 1))).ToString();
                    for (int j = startRow; j < row; j++)
                    {
                        consolidateSheet.Cells[j, i * 2 + 1].NumberFormat = "0.00%";
                        //consolidateSheet.Cells[j, i * 2 + 1].Formula = "=" + prevColCode + j.ToString() + "/" + prevColCode + totalSSRow.ToString();
                        consolidateSheet.Cells[j, i * 2 + 1].Formula = "=IF(" + prevColCode + j.ToString() + "<>\"\"," + prevColCode + j.ToString() + "/" + prevColCode + totalSSRow.ToString() + ", \"\")";

                    }
                }
                for (int i = 1; i <= 5; i++)
                {
                    string colCode = Convert.ToChar((Convert.ToInt32('A') + i * 2)).ToString();
                    consolidateSheet.Cells[row, i * 2 + 1].Formula = "=sum(" + colCode + startRow.ToString() + ":" + colCode + (row - 1).ToString() + ")";
                }
                StyleOfSummary(consolidateSheet, row);
            }
            return row + 1;
        }

        private void FillConsolidateCADWorkSheet()
        {
            int row = 1;
            // title
            row = WriteSheetHeader("Consolidated Income Statement at " + fiscalMonth.ToString("D2") + "-" + fiscalYear.ToString("D2") + " (CAD)", consolidateSheet);
            // exchange rate
            row++;
            consolidateSheet.Cells[row, 1] = "Exchange Rate:";
            consolidateSheet.Cells[row, 2] = 1.0;
            ExcoCalendar calendar = new ExcoCalendar(fiscalYear, fiscalMonth, true, 1);
            consolidateSheet.Cells[row, 4] = ExcoExRate.GetToCADRate(calendar.GetNextCalendarMonth(), "US");
            consolidateSheet.Cells[row, 6] = ExcoExRate.GetToCADRate(calendar.GetNextCalendarMonth(), "US");
            consolidateSheet.Cells[row, 8] = ExcoExRate.GetToCADRate(calendar.GetNextCalendarMonth(), "CP");
            // header
            row++;
            consolidateSheet.Cells[row, 1] = "Name";
            consolidateSheet.Cells[row, 2] = "Markham";
            consolidateSheet.Cells[row, 4] = "Michigan";
            consolidateSheet.Cells[row, 6] = "Texas";
            consolidateSheet.Cells[row, 8] = "Colombia";
            consolidateSheet.Cells[row, 10] = "Total";
            Excel.Range range = consolidateSheet.Cells.get_Range("A" + row.ToString(), "K" + row.ToString());
            range.Font.Bold = true;
            range.Font.Size = 14;
            range.Cells.Borders[Excel.XlBordersIndex.xlEdgeBottom].LineStyle = Excel.XlLineStyle.xlContinuous;
            // write sales
            row++;
            row = WriteConsolidateCategory(process.ss, row);
            // write cost of steels
            row++;
            row = WriteConsolidateCategory(process.cs, row);
            // write direct labour
            row++;
            row = WriteConsolidateCategory(process.dl, row);
            // write factory overhead
            row++;
            row = WriteConsolidateCategory(process.fo, row);
            // write total cost of goods
            row++;
            consolidateSheet.Cells[row, 1] = "TOTAL COST OF GOODS:";
            for (int i = 2; i <= 11; i++)
            {
                string colCode = Convert.ToChar((Convert.ToInt32('A') + i - 1)).ToString();
                consolidateSheet.Cells[row, i].Formula = "=" + colCode + totalCSRow.ToString() + "+" + colCode + totalDLRow.ToString() + "+" + colCode + totalFORow.ToString();
            }
            StyleOfSummary(consolidateSheet, row);
            row++;
            // write gross margin
            row++;
            consolidateSheet.Cells[row, 1] = "GROSS MARGIN:";
            for (int i = 2; i <= 11; i++)
            {
                string colCode = Convert.ToChar((Convert.ToInt32('A') + i - 1)).ToString();
                consolidateSheet.Cells[row, i].Formula = "=" + colCode + totalSSRow.ToString() + "+" + colCode + totalCSRow.ToString() + "+" + colCode + totalDLRow.ToString() + "+" + colCode + totalFORow.ToString();
            }
            StyleOfSummary(consolidateSheet, row);
            row++;
            // write delivery and selling
            row++;
            row = WriteConsolidateCategory(process.ds, row);
            // write general and administration
            row++;
            row = WriteConsolidateCategory(process.ga, row);
            // write other expense and income
            row++;
            row = WriteConsolidateCategory(process.oe, row);
            // write total expenses
            row++;
            consolidateSheet.Cells[row, 1] = "TOTAL EXPENSES:";
            for (int i = 2; i <= 11; i++)
            {
                string colCode = Convert.ToChar((Convert.ToInt32('A') + i - 1)).ToString();
                consolidateSheet.Cells[row, i].Formula = "=" + colCode + totalDSRow.ToString() + "+" + colCode + totalGARow.ToString() + "+" + colCode + totalOERow.ToString();
            }
            StyleOfSummary(consolidateSheet, row);
            row++;
            // write gross margin
            row++;
            consolidateSheet.Cells[row, 1] = "TOTAL NET INCOME:";
            for (int i = 2; i <= 11; i++)
            {
                string colCode = Convert.ToChar((Convert.ToInt32('A') + i - 1)).ToString();
                consolidateSheet.Cells[row, i].Formula = "=" + colCode + totalSSRow.ToString() + "+" + colCode + totalDSRow.ToString() + "+" + colCode + totalGARow.ToString() + "+" + colCode + totalOERow.ToString() + "+" + colCode + totalCSRow.ToString() + "+" + colCode + totalDLRow.ToString() + "+" + colCode + totalFORow.ToString();

            }
            StyleOfSummary(consolidateSheet, row);
            grandTotalRow = row;
            row++;
            // write adjustments
            row++;
            consolidateSheet.Cells[row, 1] = "ADJUSTMENTS:";
            consolidateSheet.Cells.get_Range("A" + row.ToString()).Font.Bold = true;
            row++;
            consolidateSheet.Cells[row, 1] = "ADD: INCOME TAX PROVISION";
            for (int i = 2; i <= 6; i++)
            {
                string colCode = Convert.ToChar((Convert.ToInt32('A') + i * 2 - 3)).ToString();
                consolidateSheet.Cells[row, i * 2 - 2].Formula = "=" + colCode + provisionRow.ToString();
                consolidateSheet.Cells[row, i * 2 - 1].NumberFormat = "0.00%";
                consolidateSheet.Cells[row, i * 2 - 1].Formula = "=" + colCode + row.ToString() + "/" + colCode + totalSSRow.ToString();
            }
            row++;
            consolidateSheet.Cells[row, 1] = "RECLASS: SOUTH AMERICA TRAVEL";
            for (int i = 2; i <= 6; i++)
            {
                string colCode = Convert.ToChar((Convert.ToInt32('A') + i * 2 - 3)).ToString();
                //consolidateSheet.Cells[row, i * 2 - 2].Formula = "=" + colCode + factorySATravelRow.ToString() + "+" + colCode + officeSATravelRow.ToString();
                consolidateSheet.Cells[row, i * 2 - 2].Formula = "=" + colCode + officeSATravelRow.ToString();
                consolidateSheet.Cells[row, i * 2 - 1].NumberFormat = "0.00%";
                consolidateSheet.Cells[row, i * 2 - 1].Formula = "=" + colCode + row.ToString() + "/" + colCode + totalSSRow.ToString();
            }
            row++;
            consolidateSheet.Cells[row, 1] = "TOTAL ADJUSTMENTS:";
            for (int i = 2; i <= 11; i++)
            {
                string colCode = Convert.ToChar((Convert.ToInt32('A') + i - 1)).ToString();
                consolidateSheet.Cells[row, i].Formula = "=" + colCode + (row - 2).ToString() + "+" + colCode + (row - 1).ToString();
            }
            consolidateSheet.Cells.get_Range("A" + row.ToString(), "K" + row.ToString()).Font.Bold = true;
            row += 2;
            consolidateSheet.Cells[row, 1] = "ADJUSTED NET INCOME BEFORE INC. TAX:";
            for (int i = 2; i <= 11; i++)
            {
                string colCode = Convert.ToChar((Convert.ToInt32('A') + i - 1)).ToString();
                consolidateSheet.Cells[row, i].Formula = "=" + colCode + grandTotalRow.ToString() + "-" + colCode + (row - 2).ToString();
            }
            consolidateSheet.Cells.get_Range("A" + row.ToString(), "K" + row.ToString()).Font.Bold = true;
            row++;
            // supplemental
            row += 3;
            consolidateSheet.Cells[row, 1] = "SUPPLEMENTAL INFO:";
            consolidateSheet.Cells.get_Range("A" + row.ToString(), "K" + row.ToString()).Font.ColorIndex = 8;
            consolidateSheet.Cells.get_Range("A" + row.ToString(), "K" + row.ToString()).Font.Bold = true;
            row++;
            // shop labor
            row++;
            consolidateSheet.Cells[row, 1] = "SHOP LABOR";
            row++;
            consolidateSheet.Cells[row, 1] = "WAGES";
            for (int i = 2; i <= 6; i++)
            {
                string colCode = Convert.ToChar((Convert.ToInt32('A') + i * 2 - 3)).ToString();
                consolidateSheet.Cells[row, i * 2 - 2].Formula = "=" + colCode + directLabourCAM.ToString() + "+" + colCode + directLabourHeat.ToString() + "+" + colCode + directLabourShop.ToString() + "+" + colCode + factorySupervisor.ToString() + "+" + colCode + factoryIndirectLabour.ToString() + "+" + colCode + factoryCAD.ToString();
                consolidateSheet.Cells[row, i * 2 - 1].NumberFormat = "0.00%";
                consolidateSheet.Cells[row, i * 2 - 1].Formula = "=" + colCode + row.ToString() + "/" + colCode + totalSSRow.ToString();
            }
            row++;
            consolidateSheet.Cells[row, 1] = "BENEFITS (% IS TO WAGES)";
            for (int i = 2; i <= 6; i++)
            {
                string colCode = Convert.ToChar((Convert.ToInt32('A') + i * 2 - 3)).ToString();
                consolidateSheet.Cells[row, i * 2 - 2].Formula = "=" + colCode + factoryWorkersCompensation.ToString() + "+" + colCode + factoryVacationPay.ToString() + "+" + colCode + factoryStatHoliday.ToString() + "+" + colCode + factoryGroupInsurance.ToString() + "+" + colCode + factoryEmployeeBenefits.ToString();
                consolidateSheet.Cells[row, i * 2 - 1].NumberFormat = "0.00%";
                consolidateSheet.Cells[row, i * 2 - 1].Formula = "=" + colCode + row.ToString() + "/" + colCode + (row - 1).ToString();
            }
            row++;
            consolidateSheet.Cells[row, 1] = "TOTAL SHOP LABOR COST:";
            for (int i = 2; i <= 6; i++)
            {
                string colCode = Convert.ToChar((Convert.ToInt32('A') + i * 2 - 3)).ToString();
                consolidateSheet.Cells[row, i * 2 - 2].Formula = "=" + colCode + (row - 2).ToString() + "+" + colCode + (row - 1).ToString();
                consolidateSheet.Cells[row, i * 2 - 1].NumberFormat = "0.00%";
                consolidateSheet.Cells[row, i * 2 - 1].Formula = "=" + colCode + row.ToString() + "/" + colCode + totalSSRow.ToString();
            }
            row++;
            // s, g & a labor
            row++;
            consolidateSheet.Cells[row, 1] = "S,G & A LABOR";
            row++;
            consolidateSheet.Cells[row, 1] = "WAGES";
            for (int i = 2; i <= 6; i++)
            {
                string colCode = Convert.ToChar((Convert.ToInt32('A') + i * 2 - 3)).ToString();
                consolidateSheet.Cells[row, i * 2 - 2].Formula = "=" + colCode + officeSalaries.ToString() + "+" + colCode + salesSalaries.ToString();
                consolidateSheet.Cells[row, i * 2 - 1].NumberFormat = "0.00%";
                consolidateSheet.Cells[row, i * 2 - 1].Formula = "=" + colCode + row.ToString() + "/" + colCode + totalSSRow.ToString();
            }
            row++;
            consolidateSheet.Cells[row, 1] = "BENEFITS (% IS TO WAGES)";
            for (int i = 2; i <= 6; i++)
            {
                string colCode = Convert.ToChar((Convert.ToInt32('A') + i * 2 - 3)).ToString();
                consolidateSheet.Cells[row, i * 2 - 2].Formula = "=" + colCode + salesWorkersCompensation.ToString() + "+" + colCode + salesVacationPay.ToString() + "+" + colCode + salesStatHoliday.ToString() + "+" + colCode + salesGroupInsurance.ToString() + "+" + colCode + salesEmployeeBenefits.ToString() + "+" + colCode + officeWorkersCompensation.ToString() + "+" + colCode + officeVacationPay.ToString() + "+" + colCode + officeStatHoliday.ToString() + "+" + colCode + officeGroupInsurance.ToString() + "+" + colCode + officeEmployeeBenefits.ToString();// +"+" + colCode + officePayrollTaxes.ToString();
                consolidateSheet.Cells[row, i * 2 - 1].NumberFormat = "0.00%";
                consolidateSheet.Cells[row, i * 2 - 1].Formula = "=" + colCode + row.ToString() + "/" + colCode + (row - 1).ToString();
            }
            row++;
            consolidateSheet.Cells[row, 1] = "TOTAL S,G&A LABOR COST:";
            for (int i = 2; i <= 6; i++)
            {
                string colCode = Convert.ToChar((Convert.ToInt32('A') + i * 2 - 3)).ToString();
                consolidateSheet.Cells[row, i * 2 - 2].Formula = "=" + colCode + (row - 2).ToString() + "+" + colCode + (row - 1).ToString();
                consolidateSheet.Cells[row, i * 2 - 1].NumberFormat = "0.00%";
                consolidateSheet.Cells[row, i * 2 - 1].Formula = "=" + colCode + row.ToString() + "/" + colCode + totalSSRow.ToString();
            }
            row++;
            // total labor cost
            row++;
            consolidateSheet.Cells[row, 1] = "TOTAL WAGES";
            for (int i = 2; i <= 6; i++)
            {
                string colCode = Convert.ToChar((Convert.ToInt32('A') + i * 2 - 3)).ToString();
                consolidateSheet.Cells[row, i * 2 - 2].Formula = "=" + colCode + (row - 9).ToString() + "+" + colCode + (row - 4).ToString();
                consolidateSheet.Cells[row, i * 2 - 1].NumberFormat = "0.00%";
                consolidateSheet.Cells[row, i * 2 - 1].Formula = "=" + colCode + row.ToString() + "/" + colCode + totalSSRow.ToString();
            }
            row++;
            consolidateSheet.Cells[row, 1] = "TOTOAL BENEFITS (% IS TO WAGES)";
            for (int i = 2; i <= 6; i++)
            {
                string colCode = Convert.ToChar((Convert.ToInt32('A') + i * 2 - 3)).ToString();
                consolidateSheet.Cells[row, i * 2 - 2].Formula = "=" + colCode + (row - 9).ToString() + "+" + colCode + (row - 4).ToString();
                consolidateSheet.Cells[row, i * 2 - 1].NumberFormat = "0.00%";
                consolidateSheet.Cells[row, i * 2 - 1].Formula = "=" + colCode + row.ToString() + "/" + colCode + (row - 1).ToString();
            }
            row++;
            consolidateSheet.Cells[row, 1] = "TOTAL LABOR COST:";
            for (int i = 2; i <= 6; i++)
            {
                string colCode = Convert.ToChar((Convert.ToInt32('A') + i * 2 - 3)).ToString();
                consolidateSheet.Cells[row, i * 2 - 2].Formula = "=" + colCode + (row - 2).ToString() + "+" + colCode + (row - 1).ToString();
                consolidateSheet.Cells[row, i * 2 - 1].NumberFormat = "0.00%";
                consolidateSheet.Cells[row, i * 2 - 1].Formula = "=" + colCode + row.ToString() + "/" + colCode + totalSSRow.ToString();
            }
            consolidateSheet.Cells.get_Range("A" + row.ToString(), "K" + row.ToString()).Font.Bold = true;
            row++;
            // facility cost
            row++;
            consolidateSheet.Cells[row, 1] = "FACILITY COSTS";
            row++;
            consolidateSheet.Cells[row, 1] = "RENT";
            for (int i = 2; i <= 6; i++)
            {
                string colCode = Convert.ToChar((Convert.ToInt32('A') + i * 2 - 3)).ToString();
                consolidateSheet.Cells[row, i * 2 - 2].Formula = "=" + colCode + factoryRent.ToString() + "+" + colCode + officeRent.ToString();
                consolidateSheet.Cells[row, i * 2 - 1].NumberFormat = "0.00%";
                consolidateSheet.Cells[row, i * 2 - 1].Formula = "=" + colCode + row.ToString() + "/" + colCode + totalSSRow.ToString();
            }
            row++;
            consolidateSheet.Cells[row, 1] = "DEPRECIATION";
            for (int i = 2; i <= 6; i++)
            {
                string colCode = Convert.ToChar((Convert.ToInt32('A') + i * 2 - 3)).ToString();
                consolidateSheet.Cells[row, i * 2 - 2].Formula = "=" + colCode + factoryDepreBuilding.ToString() + "+" + colCode + factoryDepreBuildingImprov.ToString();
                consolidateSheet.Cells[row, i * 2 - 1].NumberFormat = "0.00%";
                consolidateSheet.Cells[row, i * 2 - 1].Formula = "=" + colCode + row.ToString() + "/" + colCode + totalSSRow.ToString();
            }
            row++;
            consolidateSheet.Cells[row, 1] = "REPAIR & MAINTENANCE";
            for (int i = 2; i <= 6; i++)
            {
                string colCode = Convert.ToChar((Convert.ToInt32('A') + i * 2 - 3)).ToString();
                consolidateSheet.Cells[row, i * 2 - 2].Formula = "=" + colCode + factoryReqMainBuilding.ToString();
                consolidateSheet.Cells[row, i * 2 - 1].NumberFormat = "0.00%";
                consolidateSheet.Cells[row, i * 2 - 1].Formula = "=" + colCode + row.ToString() + "/" + colCode + totalSSRow.ToString();
            }
            row++;
            consolidateSheet.Cells[row, 1] = "PROPERTY TAX";
            for (int i = 2; i <= 6; i++)
            {
                string colCode = Convert.ToChar((Convert.ToInt32('A') + i * 2 - 3)).ToString();
                consolidateSheet.Cells[row, i * 2 - 2].Formula = "=" + colCode + factoryPropertyTax.ToString();
                consolidateSheet.Cells[row, i * 2 - 1].NumberFormat = "0.00%";
                consolidateSheet.Cells[row, i * 2 - 1].Formula = "=" + colCode + row.ToString() + "/" + colCode + totalSSRow.ToString();
            }
            row++;
            consolidateSheet.Cells[row, 1] = "TOTAL FACILITY COST:";
            for (int i = 2; i <= 6; i++)
            {
                string colCode = Convert.ToChar((Convert.ToInt32('A') + i * 2 - 3)).ToString();
                consolidateSheet.Cells[row, i * 2 - 2].Formula = "=" + colCode + (row - 2).ToString() + "+" + colCode + (row - 1).ToString() + "+" + colCode + (row - 3).ToString() + "+" + colCode + (row - 4).ToString();
                consolidateSheet.Cells[row, i * 2 - 1].NumberFormat = "0.00%";
                consolidateSheet.Cells[row, i * 2 - 1].Formula = "=" + colCode + row.ToString() + "/" + colCode + totalSSRow.ToString();
            }
            consolidateSheet.Cells.get_Range("A" + row.ToString(), "K" + row.ToString()).Font.Bold = true;
            row++;
            // depreciation
            row++;
            consolidateSheet.Cells[row, 1] = "DEPRECIATION";
            row++;
            consolidateSheet.Cells[row, 1] = "BUILDING";
            for (int i = 2; i <= 6; i++)
            {
                string colCode = Convert.ToChar((Convert.ToInt32('A') + i * 2 - 3)).ToString();
                consolidateSheet.Cells[row, i * 2 - 2].Formula = "=" + colCode + factoryDepreBuilding.ToString();
                consolidateSheet.Cells[row, i * 2 - 1].NumberFormat = "0.00%";
                consolidateSheet.Cells[row, i * 2 - 1].Formula = "=" + colCode + row.ToString() + "/" + colCode + totalSSRow.ToString();
            }
            row++;
            consolidateSheet.Cells[row, 1] = "BUILDING IMPROVEMENT";
            for (int i = 2; i <= 6; i++)
            {
                string colCode = Convert.ToChar((Convert.ToInt32('A') + i * 2 - 3)).ToString();
                consolidateSheet.Cells[row, i * 2 - 2].Formula = "=" + colCode + factoryDepreBuildingImprov.ToString();
                consolidateSheet.Cells[row, i * 2 - 1].NumberFormat = "0.00%";
                consolidateSheet.Cells[row, i * 2 - 1].Formula = "=" + colCode + row.ToString() + "/" + colCode + totalSSRow.ToString();
            }
            row++;
            consolidateSheet.Cells[row, 1] = "TOTAL BUILDING:";
            for (int i = 2; i <= 6; i++)
            {
                string colCode = Convert.ToChar((Convert.ToInt32('A') + i * 2 - 3)).ToString();
                consolidateSheet.Cells[row, i * 2 - 2].Formula = "=" + colCode + (row - 2).ToString() + "+" + colCode + (row - 1).ToString();
                consolidateSheet.Cells[row, i * 2 - 1].NumberFormat = "0.00%";
                consolidateSheet.Cells[row, i * 2 - 1].Formula = "=" + colCode + row.ToString() + "/" + colCode + totalSSRow.ToString();
            }
            row++;
            // non building depreciation
            row++;
            consolidateSheet.Cells[row, 1] = "MACHINERY & EQUIPMENT";
            for (int i = 2; i <= 6; i++)
            {
                string colCode = Convert.ToChar((Convert.ToInt32('A') + i * 2 - 3)).ToString();
                consolidateSheet.Cells[row, i * 2 - 2].Formula = "=" + colCode + factoryDepreMachine.ToString();
                consolidateSheet.Cells[row, i * 2 - 1].NumberFormat = "0.00%";
                consolidateSheet.Cells[row, i * 2 - 1].Formula = "=" + colCode + row.ToString() + "/" + colCode + totalSSRow.ToString();
            }
            row++;
            consolidateSheet.Cells[row, 1] = "FURNITURE & FIXTURES, COMPUTERS/SOFTWARE";
            for (int i = 2; i <= 6; i++)
            {
                string colCode = Convert.ToChar((Convert.ToInt32('A') + i * 2 - 3)).ToString();
                consolidateSheet.Cells[row, i * 2 - 2].Formula = "=" + colCode + officeDepreFurniture.ToString() + "+" + colCode + officeSoftwareAmort.ToString();
                consolidateSheet.Cells[row, i * 2 - 1].NumberFormat = "0.00%";
                consolidateSheet.Cells[row, i * 2 - 1].Formula = "=" + colCode + row.ToString() + "/" + colCode + totalSSRow.ToString();
            }
            row++;
            consolidateSheet.Cells[row, 1] = "VEHICLES";
            for (int i = 2; i <= 6; i++)
            {
                string colCode = Convert.ToChar((Convert.ToInt32('A') + i * 2 - 3)).ToString();
                consolidateSheet.Cells[row, i * 2 - 2].Formula = "=" + colCode + salesDepreAuto.ToString();
                consolidateSheet.Cells[row, i * 2 - 1].NumberFormat = "0.00%";
                consolidateSheet.Cells[row, i * 2 - 1].Formula = "=" + colCode + row.ToString() + "/" + colCode + totalSSRow.ToString();
            } row++;
            consolidateSheet.Cells[row, 1] = "TOOLING";
            for (int i = 2; i <= 6; i++)
            {
                string colCode = Convert.ToChar((Convert.ToInt32('A') + i * 2 - 3)).ToString();
                consolidateSheet.Cells[row, i * 2 - 2].Formula = "=" + colCode + factoryToolAmort.ToString();
                consolidateSheet.Cells[row, i * 2 - 1].NumberFormat = "0.00%";
                consolidateSheet.Cells[row, i * 2 - 1].Formula = "=" + colCode + row.ToString() + "/" + colCode + totalSSRow.ToString();
            } row++;
            consolidateSheet.Cells[row, 1] = "TOTAL NON-BUILDING DEPRECIATION:";
            for (int i = 2; i <= 6; i++)
            {
                string colCode = Convert.ToChar((Convert.ToInt32('A') + i * 2 - 3)).ToString();
                consolidateSheet.Cells[row, i * 2 - 2].Formula = "=" + colCode + (row - 2).ToString() + "+" + colCode + (row - 1).ToString() + "+" + colCode + (row - 3).ToString() + "+" + colCode + (row - 4).ToString();
                consolidateSheet.Cells[row, i * 2 - 1].NumberFormat = "0.00%";
                consolidateSheet.Cells[row, i * 2 - 1].Formula = "=" + colCode + row.ToString() + "/" + colCode + totalSSRow.ToString();
            }
            row += 2;
            consolidateSheet.Cells[row, 1] = "TOTAL DEPRECIATION:";
            for (int i = 2; i <= 6; i++)
            {
                string colCode = Convert.ToChar((Convert.ToInt32('A') + i * 2 - 3)).ToString();
                consolidateSheet.Cells[row, i * 2 - 2].Formula = "=" + colCode + (row - 2).ToString() + "+" + colCode + (row - 8).ToString();
                consolidateSheet.Cells[row, i * 2 - 1].NumberFormat = "0.00%";
                consolidateSheet.Cells[row, i * 2 - 1].Formula = "=" + colCode + row.ToString() + "/" + colCode + totalSSRow.ToString();
            }
            consolidateSheet.Cells.get_Range("A" + row.ToString(), "K" + row.ToString()).Font.Bold = true;
            row++;
            // tooling expense
            row++;
            consolidateSheet.Cells[row, 1] = "TOOLING EXPENSE";
            row++;
            consolidateSheet.Cells[row, 1] = "TOOLING EXPENSE";
            for (int i = 2; i <= 6; i++)
            {
                string colCode = Convert.ToChar((Convert.ToInt32('A') + i * 2 - 3)).ToString();
                consolidateSheet.Cells[row, i * 2 - 2].Formula = "=" + colCode + factoryToolExpense.ToString();
                consolidateSheet.Cells[row, i * 2 - 1].NumberFormat = "0.00%";
                consolidateSheet.Cells[row, i * 2 - 1].Formula = "=" + colCode + row.ToString() + "/" + colCode + totalSSRow.ToString();
            }
            row++;
            consolidateSheet.Cells[row, 1] = "TOOLING AMORTIZATION";
            for (int i = 2; i <= 6; i++)
            {
                string colCode = Convert.ToChar((Convert.ToInt32('A') + i * 2 - 3)).ToString();
                consolidateSheet.Cells[row, i * 2 - 2].Formula = "=" + colCode + factoryToolAmort.ToString();
                consolidateSheet.Cells[row, i * 2 - 1].NumberFormat = "0.00%";
                consolidateSheet.Cells[row, i * 2 - 1].Formula = "=" + colCode + row.ToString() + "/" + colCode + totalSSRow.ToString();
            }
            row++;
            consolidateSheet.Cells[row, 1] = "TOTAL TOOLING EXPENSE:";
            for (int i = 2; i <= 6; i++)
            {
                string colCode = Convert.ToChar((Convert.ToInt32('A') + i * 2 - 3)).ToString();
                consolidateSheet.Cells[row, i * 2 - 2].Formula = "=" + colCode + (row - 2).ToString() + "+" + colCode + (row - 1).ToString();
                consolidateSheet.Cells[row, i * 2 - 1].NumberFormat = "0.00%";
                consolidateSheet.Cells[row, i * 2 - 1].Formula = "=" + colCode + row.ToString() + "/" + colCode + totalSSRow.ToString();
            }
            consolidateSheet.Cells.get_Range("A" + row.ToString(), "K" + row.ToString()).Font.Bold = true;
            row++;
            // supplies
            row++;
            consolidateSheet.Cells[row, 1] = "SUPPLIES";
            row++;
            consolidateSheet.Cells[row, 1] = "CAD/CAM SUPPLIES";
            for (int i = 2; i <= 6; i++)
            {
                string colCode = Convert.ToChar((Convert.ToInt32('A') + i * 2 - 3)).ToString();
                consolidateSheet.Cells[row, i * 2 - 2].Formula = "=" + colCode + factoryCADCAMSupplies.ToString();
                consolidateSheet.Cells[row, i * 2 - 1].NumberFormat = "0.00%";
                consolidateSheet.Cells[row, i * 2 - 1].Formula = "=" + colCode + row.ToString() + "/" + colCode + totalSSRow.ToString();
            }
            row++;
            consolidateSheet.Cells[row, 1] = "SHOP SUPPLIES";
            for (int i = 2; i <= 6; i++)
            {
                string colCode = Convert.ToChar((Convert.ToInt32('A') + i * 2 - 3)).ToString();
                consolidateSheet.Cells[row, i * 2 - 2].Formula = "=" + colCode + factoryShopSupplies.ToString();
                consolidateSheet.Cells[row, i * 2 - 1].NumberFormat = "0.00%";
                consolidateSheet.Cells[row, i * 2 - 1].Formula = "=" + colCode + row.ToString() + "/" + colCode + totalSSRow.ToString();
            }
            row++;
            consolidateSheet.Cells[row, 1] = "HEAT TREAT SUPPLIES";
            for (int i = 2; i <= 6; i++)
            {
                string colCode = Convert.ToChar((Convert.ToInt32('A') + i * 2 - 3)).ToString();
                consolidateSheet.Cells[row, i * 2 - 2].Formula = "=" + colCode + factoryHeatTreatSupplies.ToString();
                consolidateSheet.Cells[row, i * 2 - 1].NumberFormat = "0.00%";
                consolidateSheet.Cells[row, i * 2 - 1].Formula = "=" + colCode + row.ToString() + "/" + colCode + totalSSRow.ToString();
            }
            row++;
            consolidateSheet.Cells[row, 1] = "OFFICE SUPPLIES";
            for (int i = 2; i <= 6; i++)
            {
                string colCode = Convert.ToChar((Convert.ToInt32('A') + i * 2 - 3)).ToString();
                consolidateSheet.Cells[row, i * 2 - 2].Formula = "=" + colCode + officeSupplies.ToString();
                consolidateSheet.Cells[row, i * 2 - 1].NumberFormat = "0.00%";
                consolidateSheet.Cells[row, i * 2 - 1].Formula = "=" + colCode + row.ToString() + "/" + colCode + totalSSRow.ToString();
            }
            row++; consolidateSheet.Cells[row, 1] = "TOTAL SUPPLIES:";
            for (int i = 2; i <= 6; i++)
            {
                string colCode = Convert.ToChar((Convert.ToInt32('A') + i * 2 - 3)).ToString();
                consolidateSheet.Cells[row, i * 2 - 2].Formula = "=" + colCode + (row - 2).ToString() + "+" + colCode + (row - 1).ToString() + "+" + colCode + (row - 3).ToString() + "+" + colCode + (row - 4).ToString() + "+" + colCode + (row - 5).ToString();
                consolidateSheet.Cells[row, i * 2 - 1].NumberFormat = "0.00%";
                consolidateSheet.Cells[row, i * 2 - 1].Formula = "=" + colCode + row.ToString() + "/" + colCode + totalSSRow.ToString();
            }
            consolidateSheet.Cells.get_Range("A" + row.ToString(), "K" + row.ToString()).Font.Bold = true;
            row++;
            // travel, meal & entertainment
            row++;
            consolidateSheet.Cells[row, 1] = "TRAVEL, MEALS & ENTERTAINMENT";
            row++;
            /*
            consolidateSheet.Cells[row, 1] = "TRAVEL - SHOP";
            for (int i = 2; i <= 6; i++)
            {
                string colCode = Convert.ToChar((Convert.ToInt32('A') + i * 2 - 3)).ToString();
                consolidateSheet.Cells[row, i * 2 - 2].Formula = "=" + colCode + factoryTravel.ToString();
                consolidateSheet.Cells[row, i * 2 - 1].NumberFormat = "0.00%";
                consolidateSheet.Cells[row, i * 2 - 1].Formula = "=" + colCode + row.ToString() + "/" + colCode + totalSSRow.ToString();
            }
            row++;
            consolidateSheet.Cells[row, 1] = "MEALS & ENTERTAINMENT - SHOP";
            for (int i = 2; i <= 6; i++)
            {
                string colCode = Convert.ToChar((Convert.ToInt32('A') + i * 2 - 3)).ToString();
                consolidateSheet.Cells[row, i * 2 - 2].Formula = "=" + colCode + factoryMeals.ToString();
                consolidateSheet.Cells[row, i * 2 - 1].NumberFormat = "0.00%";
                consolidateSheet.Cells[row, i * 2 - 1].Formula = "=" + colCode + row.ToString() + "/" + colCode + totalSSRow.ToString();
            }
            row++;
            consolidateSheet.Cells[row, 1] = "AIRFARE - SHOP";
            for (int i = 2; i <= 6; i++)
            {
                string colCode = Convert.ToChar((Convert.ToInt32('A') + i * 2 - 3)).ToString();
                consolidateSheet.Cells[row, i * 2 - 2].Formula = "=" + colCode + factoryAirFare.ToString();
                consolidateSheet.Cells[row, i * 2 - 1].NumberFormat = "0.00%";
                consolidateSheet.Cells[row, i * 2 - 1].Formula = "=" + colCode + row.ToString() + "/" + colCode + totalSSRow.ToString();
            }
            row++;
            consolidateSheet.Cells[row, 1] = "SOUTH AMERICA TRAVEL - SHOP";
            for (int i = 2; i <= 6; i++)
            {
                string colCode = Convert.ToChar((Convert.ToInt32('A') + i * 2 - 3)).ToString();
                
                consolidateSheet.Cells[row, i * 2 - 2].Formula = "=" + colCode + factorySATravelRow.ToString();
                consolidateSheet.Cells[row, i * 2 - 1].Formula = "=" + colCode + row.ToString() + "/" + colCode + totalSSRow.ToString();
                
                consolidateSheet.Cells[row, i * 2 - 1].NumberFormat = "0.00%";
            }
            */
            row++;
            consolidateSheet.Cells[row, 1] = "NON DEDUCTIBLE EXP GOLF";
            for (int i = 2; i <= 6; i++)
            {
                string colCode = Convert.ToChar((Convert.ToInt32('A') + i * 2 - 3)).ToString();
                consolidateSheet.Cells[row, i * 2 - 2].Formula = "=" + colCode + salesGolf.ToString();
                consolidateSheet.Cells[row, i * 2 - 1].NumberFormat = "0.00%";
                consolidateSheet.Cells[row, i * 2 - 1].Formula = "=" + colCode + row.ToString() + "/" + colCode + totalSSRow.ToString();
            }
            row++;
            consolidateSheet.Cells[row, 1] = "SELLING & TRAVEL MEALS & ENTERTAINMENT";
            for (int i = 2; i <= 6; i++)
            {
                string colCode = Convert.ToChar((Convert.ToInt32('A') + i * 2 - 3)).ToString();
                consolidateSheet.Cells[row, i * 2 - 2].Formula = "=" + colCode + salesMeals.ToString();
                consolidateSheet.Cells[row, i * 2 - 1].NumberFormat = "0.00%";
                consolidateSheet.Cells[row, i * 2 - 1].Formula = "=" + colCode + row.ToString() + "/" + colCode + totalSSRow.ToString();
            }
            row++;
            consolidateSheet.Cells[row, 1] = "SELLING & TRAVEL EXPENSES";
            for (int i = 2; i <= 6; i++)
            {
                string colCode = Convert.ToChar((Convert.ToInt32('A') + i * 2 - 3)).ToString();
                consolidateSheet.Cells[row, i * 2 - 2].Formula = "=" + colCode + salesTravel.ToString();
                consolidateSheet.Cells[row, i * 2 - 1].NumberFormat = "0.00%";
                consolidateSheet.Cells[row, i * 2 - 1].Formula = "=" + colCode + row.ToString() + "/" + colCode + totalSSRow.ToString();
            }
            row++;
            consolidateSheet.Cells[row, 1] = "SELLING & TRAVEL AIR FARE";
            for (int i = 2; i <= 6; i++)
            {
                string colCode = Convert.ToChar((Convert.ToInt32('A') + i * 2 - 3)).ToString();
                consolidateSheet.Cells[row, i * 2 - 2].Formula = "=" + colCode + salesAirFare.ToString();
                consolidateSheet.Cells[row, i * 2 - 1].NumberFormat = "0.00%";
                consolidateSheet.Cells[row, i * 2 - 1].Formula = "=" + colCode + row.ToString() + "/" + colCode + totalSSRow.ToString();
            }
            row++;
            /*
            consolidateSheet.Cells[row, 1] = "OFFICE MEALS & ENTERTAINMENT";
            for (int i = 2; i <= 6; i++)
            {
                string colCode = Convert.ToChar((Convert.ToInt32('A') + i * 2 - 3)).ToString();
                consolidateSheet.Cells[row, i * 2 - 2].Formula = "=" + colCode + officeMeals.ToString();
                consolidateSheet.Cells[row, i * 2 - 1].NumberFormat = "0.00%";
                consolidateSheet.Cells[row, i * 2 - 1].Formula = "=" + colCode + row.ToString() + "/" + colCode + totalSSRow.ToString();
            }
            row++;
            consolidateSheet.Cells[row, 1] = "OFFICE TRAVEL EXPENSES";
            for (int i = 2; i <= 6; i++)
            {
                string colCode = Convert.ToChar((Convert.ToInt32('A') + i * 2 - 3)).ToString();
                consolidateSheet.Cells[row, i * 2 - 2].Formula = "=" + colCode + officeTravel.ToString();
                consolidateSheet.Cells[row, i * 2 - 1].NumberFormat = "0.00%";
                consolidateSheet.Cells[row, i * 2 - 1].Formula = "=" + colCode + row.ToString() + "/" + colCode + totalSSRow.ToString();
            }
            row++;
            consolidateSheet.Cells[row, 1] = "OFFICE AIR FARE";
            for (int i = 2; i <= 6; i++)
            {
                string colCode = Convert.ToChar((Convert.ToInt32('A') + i * 2 - 3)).ToString();
                consolidateSheet.Cells[row, i * 2 - 2].Formula = "=" + colCode + officeAirFare.ToString();
                consolidateSheet.Cells[row, i * 2 - 1].NumberFormat = "0.00%";
                consolidateSheet.Cells[row, i * 2 - 1].Formula = "=" + colCode + row.ToString() + "/" + colCode + totalSSRow.ToString();
            }
            row++;
            */
            consolidateSheet.Cells[row, 1] = "OFFICE SOUTH AMERICA TRAVEL";
            for (int i = 2; i <= 6; i++)
            {
                string colCode = Convert.ToChar((Convert.ToInt32('A') + i * 2 - 3)).ToString();
                consolidateSheet.Cells[row, i * 2 - 2].Formula = "=" + colCode + officeSATravelRow.ToString();
                consolidateSheet.Cells[row, i * 2 - 1].NumberFormat = "0.00%";
                consolidateSheet.Cells[row, i * 2 - 1].Formula = "=" + colCode + row.ToString() + "/" + colCode + totalSSRow.ToString();
            }
            row += 2;
            consolidateSheet.Cells[row, 1] = "RECLASS SOUTH AMERICA TRAVEL";
            for (int i = 2; i <= 6; i++)
            {
                string colCode = Convert.ToChar((Convert.ToInt32('A') + i * 2 - 3)).ToString();
                consolidateSheet.Cells[row, i * 2 - 2].Formula = "=" + colCode + (row - 7).ToString() + "-" + colCode + (row - 2).ToString();
                consolidateSheet.Cells[row, i * 2 - 1].NumberFormat = "0.00%";
                consolidateSheet.Cells[row, i * 2 - 1].Formula = "=" + colCode + row.ToString() + "/" + colCode + totalSSRow.ToString();
            }
            row += 2;
                 consolidateSheet.Cells[row, 1] = "TOTAL TRAVEL, MEALS & ENTERTAINMENT:";
            for (int i = 2; i <= 6; i++)
            {
                string colCode = Convert.ToChar((Convert.ToInt32('A') + i * 2 - 3)).ToString();
                consolidateSheet.Cells[row, i * 2 - 2].Formula = "=sum(" + colCode + (row - 9).ToString() + ":" + colCode + (row - 1).ToString() + ")";
                consolidateSheet.Cells[row, i * 2 - 1].NumberFormat = "0.00%";
                consolidateSheet.Cells[row, i * 2 - 1].Formula = "=" + colCode + row.ToString() + "/" + colCode + totalSSRow.ToString();
            }
            consolidateSheet.Cells.get_Range("A" + row.ToString(), "K" + row.ToString()).Font.Bold = true;
            row++;
            // adjust style
            AdjustSheetStyle(consolidateSheet, row);
        }
    }
}
