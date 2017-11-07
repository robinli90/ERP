//using System;
//using System.Collections.Generic;
//using System.Linq;
//using System.Text;
//using System.Text.RegularExpressions;
//using DocumentFormat.OpenXml;
//using DocumentFormat.OpenXml.Packaging;
//using DocumentFormat.OpenXml.Spreadsheet;

//namespace ExcoUtility
//{
//    public class ExcoExcel
//    {
//        // spreadsheet document 
//        // By default, AutoSave = true, Editable = true, and Type = xlsx
//        private SpreadsheetDocument document;
//        // excel file path
//        private string filePath = string.Empty;
//        // spreadsheet workbook part
//        private WorkbookPart workbookPart;
//        // spreadsheet worksheet part
//        private WorksheetPart worksheetPart;
//        // spreadsheet sheets in the workbook
//        private Sheets sheets;
//        // current sheet id
//        private UInt32Value sheetID = 1;

//        #region Public Member Functions

//        // constructor
//        public ExcoExcel(string filePath)
//        {
//            this.filePath = filePath;
//            // construct document
//            document = SpreadsheetDocument.Create(filePath, SpreadsheetDocumentType.Workbook);
//            // Add a WorkbookPart to the document.
//            workbookPart = document.AddWorkbookPart();
//            workbookPart.Workbook = new Workbook();
//            // Add a WorksheetPart to the WorkbookPart.
//            worksheetPart = workbookPart.AddNewPart<WorksheetPart>();
//            worksheetPart.Worksheet = new Worksheet(new SheetData());
//            // Add Sheets to the Workbook.
//            sheets = document.WorkbookPart.Workbook.AppendChild<Sheets>(new Sheets());
//        }

//        // add a sheet
//        public void AddSheet(string name)
//        {
//            // Append a new worksheet and associate it with workbook.
//            Sheet sheet = new Sheet() { Id = document.WorkbookPart.GetIdOfPart(worksheetPart), SheetId = sheetID++, Name = name };
//            sheets.Append(sheet);
//        }

//        // save to excel file
//        public void SaveToFile()
//        {
//            workbookPart.Workbook.Save();
//        }

//        // Given a document name, a sheet name, the name of the
//        // first cell in the contiguous range, the name of the last
//        // cell in the contiguous range, and the name of the results
//        // cell, calculates the sum of the cells in the contiguous
//        // range and inserts the result into the results cell.
//        // Note: All cells in contiguous range must contain numbers.
//        public void CalculateSumOfCellRange(Sheet sheet, string firstCellName, string lastCellName, string resultCell)
//        {
//            // Get the row number and column name for the first and last cells in the range.
//            uint firstRowNum = GetRowIndex(firstCellName);
//            uint lastRowNum = GetRowIndex(lastCellName);
//            string firstColumn = GetColumnName(firstCellName);
//            string lastColumn = GetColumnName(lastCellName);

//            double sum = 0;

//            // Iterate through the cells within the range and add their values to the sum.
//            foreach (Row row in sheet.Descendants<Row>().Where(r => r.RowIndex.Value >= firstRowNum && r.RowIndex.Value <= lastRowNum))
//            {
//                foreach (Cell cell in row)
//                {
//                    string columnName = GetColumnName(cell.CellReference.Value);
//                    if (CompareColumn(columnName, firstColumn) >= 0 && CompareColumn(columnName, lastColumn) <= 0)
//                    {
//                        sum += double.Parse(cell.CellValue.Text);
//                    }
//                }
//            }

//            // Get the SharedStringTablePart and add the result to it.
//            // If the SharedStringPart does not exist, create a new one.
//            SharedStringTablePart shareStringPart;
//            if (document.WorkbookPart.GetPartsOfType<SharedStringTablePart>().Count() > 0)
//            {
//                shareStringPart = document.WorkbookPart.GetPartsOfType<SharedStringTablePart>().First();
//            }
//            else
//            {
//                shareStringPart = document.WorkbookPart.AddNewPart<SharedStringTablePart>();
//            }

//            // Insert the result into the SharedStringTablePart.
//            int index = InsertSharedStringItem("Result:" + sum, shareStringPart);

//            Cell result = InsertCellInWorksheet(GetColumnName(resultCell), GetRowIndex(resultCell), worksheetPart);

//            // Set the value of the cell.
//            result.CellValue = new CellValue(index.ToString());
//            result.DataType = new EnumValue<CellValues>(CellValues.SharedString);

//            worksheetPart.Worksheet.Save();
//        }

//        // Write a text into a given cell
//        public void WriteText(string sheetName, uint row, uint column, string text)
//        {
//            // Get the SharedStringTablePart. If it does not exist, create a new one.
//            SharedStringTablePart shareStringPart;
//            if (workbookPart.GetPartsOfType<SharedStringTablePart>().Count() > 0)
//            {
//                shareStringPart = workbookPart.GetPartsOfType<SharedStringTablePart>().First();
//            }
//            else
//            {
//                shareStringPart = workbookPart.AddNewPart<SharedStringTablePart>();
//            }

//            // Insert the text into the SharedStringTablePart.
//            int index = InsertSharedStringItem(text, shareStringPart);

//            // Insert a new worksheet.
//            SetWorksheetPartByName(sheetName);

//            // Insert cell A1 into the new worksheet.
//            Cell cell = InsertCellInWorksheet(ConvertColumnIndexIntoName(column), row, worksheetPart);

//            // Set the value of cell A1.
//            cell.CellValue = new CellValue(index.ToString());
//            cell.DataType = new EnumValue<CellValues>(CellValues.SharedString);

//            // Save the new worksheet.
//            worksheetPart.Worksheet.Save();
//        }

//        #endregion

//        #region Private Member Functions

//        // convert column index into column name
//        private string ConvertColumnIndexIntoName(uint column)
//        {
//            string output = string.Empty;
//            uint a = column / 26;
//            uint b = column % 26;
//            if (a > 0)
//            {
//                output = Convert.ToChar(Convert.ToInt32('A') + a).ToString();
//            }
//            output += Convert.ToChar(Convert.ToInt32('A') + b - 1).ToString();
//            return output;
//        }

//        // Given a cell name, parses specified cell to get row index.
//        private uint GetRowIndex(string cellName)
//        {
//            // Create a regular expression to match the row index
//            // portion the cell name.
//            Regex regex = new Regex(@"\d+");
//            Match match = regex.Match(cellName);

//            return uint.Parse(match.Value);
//        }

//        // Given text and a SharedStringTablePart, creates a
//        // SharedStringItem with the specified text and inserts it
//        // into the SharedStringTablePart. If the item already exists,
//        // returns its index.
//        private int InsertSharedStringItem(string text, SharedStringTablePart shareStringPart)
//        {
//            // If the part does not contain a SharedStringTable, create it.
//            if (shareStringPart.SharedStringTable == null)
//            {
//                shareStringPart.SharedStringTable = new SharedStringTable();
//            }


//            int i = 0;
//            foreach (SharedStringItem item in shareStringPart.SharedStringTable.Elements<SharedStringItem>())
//            {
//                if (item.InnerText == text)
//                {
//                    // The text already exists in the part. Return its index.
//                    return i;
//                }

//                i++;
//            }

//            // The text does not exist in the part. Create the SharedStringItem.
//            shareStringPart.SharedStringTable.AppendChild(new SharedStringItem(new DocumentFormat.OpenXml.Spreadsheet.Text(text)));
//            shareStringPart.SharedStringTable.Save();

//            return i;
//        }

//        // Given a cell name, parses the specified cell to get
//        // column name.
//        private string GetColumnName(string cellName)
//        {
//            // Create a regular expression to match the column name portion of the cell name.
//            Regex regex = new Regex("[A-Za-z]+");
//            Match match = regex.Match(cellName);

//            return match.Value;
//        }

//        // Given two columns, compares the columns.
//        private int CompareColumn(string column1, string column2)
//        {
//            if (column1.Length > column2.Length)
//            {
//                return 1;
//            }
//            else if (column1.Length < column2.Length)
//            {
//                return -1;
//            }
//            else
//            {
//                return string.Compare(column1, column2, true);
//            }
//        }

//        // set worksheet part by providing a sheet name
//        private void SetWorksheetPartByName(string sheetName)
//        {
//            IEnumerable<Sheet> sheets = document.WorkbookPart.Workbook.GetFirstChild<Sheets>().Elements<Sheet>().Where(s => s.Name == sheetName);

//            if (sheets.Count() == 0)
//            {
//                // The specified worksheet does not exist.
//                throw new Exception(sheetName + " doesn't exist!");
//            }

//            string relationshipId = sheets.First().Id.Value;
//            worksheetPart = (WorksheetPart)document.WorkbookPart.GetPartById(relationshipId);
//        }

//        // Given a column name, a row index, and a WorksheetPart,
//        // inserts a cell into the worksheet. 
//        // If the cell already exists, returns it. 
//        private static Cell InsertCellInWorksheet(string columnName, uint rowIndex, WorksheetPart worksheetPart)
//        {
//            Worksheet worksheet = worksheetPart.Worksheet;
//            SheetData sheetData = worksheet.GetFirstChild<SheetData>();
//            string cellReference = columnName + rowIndex;

//            // If the worksheet does not contain a row with the specified row index, insert one.
//            Row row;
//            if (sheetData.Elements<Row>().Where(r => r.RowIndex == rowIndex).Count() != 0)
//            {
//                row = sheetData.Elements<Row>().Where(r => r.RowIndex == rowIndex).First();
//            }
//            else
//            {
//                row = new Row() { RowIndex = rowIndex };
//                sheetData.Append(row);
//            }

//            // If there is not a cell with the specified column name, insert one.  
//            if (row.Elements<Cell>().Where(c => c.CellReference.Value == columnName + rowIndex).Count() > 0)
//            {
//                return row.Elements<Cell>().Where(c => c.CellReference.Value == cellReference).First();
//            }
//            else
//            {
//                // Cells must be in sequential order according to CellReference. Determine where to insert the new cell.
//                Cell refCell = null;
//                foreach (Cell cell in row.Elements<Cell>())
//                {
//                    if (string.Compare(cell.CellReference.Value, cellReference, true) > 0)
//                    {
//                        refCell = cell;
//                        break;
//                    }
//                }

//                Cell newCell = new Cell() { CellReference = cellReference };
//                row.InsertBefore(newCell, refCell);

//                worksheet.Save();
//                return newCell;
//            }
//        }

//        #endregion
//    }
//}
