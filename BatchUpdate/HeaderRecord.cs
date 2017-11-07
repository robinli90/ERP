using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace BatchUpdate
{
    // HDR record type, length 21
    public class HeaderRecord
    {
        // titile, default HDR
        // index 0, length 3
        public Field title = new Field(3, FieldType.Text);
        // reporting date (MMDDYY)
        // index 3, length 6
        public Field date = new Field(6, FieldType.Numeric);
        // shift (1/2/3), default 1
        // index 9, length 1
        public Field shift = new Field(1, FieldType.Text);
        // fiscal period (YYMM)
        // index 10, length 4
        public Field fiscalPeriod = new Field(4, FieldType.Numeric);
        // shift group, optional
        // index 14, length 1
        public Field shiftGroup = new Field(1, FieldType.Text);
        // finished good stock location, optional
        // index 15, length 3
        public Field fgStockLoc = new Field(3, FieldType.Text);
        // reporting plant, default 001
        // index 18, length 3
        public Field plant = new Field(3, FieldType.Text);

        // constructor
        public HeaderRecord()
        {
            title.SetString("HDR");
            shift.SetString("1");
            plant.SetString("001");
        }

        // construct header string and return
        public string BuildString()
        {
            string output = string.Empty;
            string value = string.Empty;
            // add title
            value = title.GetString();
            if (0 != value.CompareTo("HDR"))
            {
                throw new Exception("HDR record title invalid: " + value);
            }
            output += value;
            // add reporting date
            value = date.GetString();
            if (0 == value.CompareTo(new string('0', 6)))
            {
                throw new Exception("HDR record reporting date invalid: " + value);
            }
            output += value;
            // add shift
            value = shift.GetString();
            if (0 != value.CompareTo("1"))
            {
                throw new Exception("HDR record shift invalid: " + value);
            }
            output += value;
            // add fiscal period
            value = fiscalPeriod.GetString();
            if (0 == value.CompareTo(new string('0', 4)))
            {
                throw new Exception("HDR record fiscal period invalid: " + value);
            }
            output += value;
            // add shift group
            output += shiftGroup.GetString();
            // add finished goods stock location
            output += fgStockLoc.GetString();
            // add reporting plant
            output += plant.GetString();
            // check string length
            if (21 != output.Length)
            {
                throw new Exception("Build HDR record error: " + output);
            }
            return output;
        }
    }
}