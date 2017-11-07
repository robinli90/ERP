using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace BatchUpdate
{
    // MAT record type, length 82
    public class MaterialRecord
    {
        // title, default MAT
        // index 0, length 3
        public Field title = new Field(3, FieldType.Text);
        // material part#
        // index 3, length 20
        public Field part = new Field(20, FieldType.Text);
        // stock room (same plant as DTL resc)
        // index 23, length 3
        public Field stoRoom = new Field(3, FieldType.Text);
        // R=required, B=by-product
        // index 26, length 1
        public Field required = new Field(1, FieldType.Text);
        // backflush (Y=Yes, N=No)
        // index 27, length 1
        public Field backFlush = new Field(1, FieldType.Text);
        // quantity
        // index 28, length 15
        public Field quantity = new Field(15, FieldType.Numeric);
        // units
        // index 43, length 3
        public Field units = new Field(3, FieldType.Text);
        // transaction date (MMDDYY), optinal
        // index 46, length 6
        public Field traDate = new Field(6, FieldType.Text);
        // sequence#, optional
        // index 52, length 3
        public Field seqNum = new Field(3, FieldType.Text);
        // lot#, optional
        // index 55, length 15
        public Field lotNum = new Field(15, FieldType.Text);
        // serial#, optional
        // index 70, length 11
        public Field serNum = new Field(11, FieldType.Text);
        // materail for scrap product (Y/N)
        // index 81, length 1
        public Field matScr = new Field(1, FieldType.Text);

        // constructor
        public MaterialRecord()
        {
            title.SetString("MAT");
        }

        // construct header string and return
        public string BuildString()
        {
            string output = string.Empty;
            string value = string.Empty;
            // add title
            value = title.GetString();
            if (0 != value.CompareTo("MAT"))
            {
                throw new Exception("MAT record title invalid: " + value);
            }
            output += value;
            // add material part#
            value = part.GetString();
            if (0 == value.CompareTo(new string(' ', 20)))
            {
                throw new Exception("MAT record part# invalid: " + value);
            }
            output += value;
            // add stock room
            value = stoRoom.GetString();
            if (0 == value.CompareTo(new string('0', 3)))
            {
                throw new Exception("MAT record stock room invalid: " + value);
            }
            output += value;
            // add required or by-product
            value = required.GetString();
            if (0 == value.CompareTo(new string(' ', 1)))
            {
                throw new Exception("MAT record required ro by-product invalid: " + value);
            }
            output += value;
            // add backflush
            value = backFlush.GetString();
            if (0 == value.CompareTo(new string(' ', 1)))
            {
                throw new Exception("MAT record backflush invalid: " + value);
            }
            output += value;
            // add quantity
            value = quantity.GetString();
            if (0 == value.CompareTo(new string('0', 15)))
            {
                throw new Exception("MAT record quantity invalid: " + value);
            }
            output += value;
            // add units
            value = units.GetString();
            if (0 == value.CompareTo(new string(' ', 3)))
            {
                throw new Exception("MAT record units invalid: " + value);
            }
            output += value;
            // add transaction date
            output += traDate.GetString();
            // add sequence#
            output += seqNum.GetString();
            // add lot#
            output += lotNum.GetString();
            // add serial#
            output += serNum.GetString();
            // add material for scarp product (Y/N)
            value = matScr.GetString();
            if (0 == value.CompareTo(new string(' ', 1)))
            {
                throw new Exception("MAT record material for scarp product invalid: " + value);
            }
            output += value;
            // check string length
            if (82 != output.Length)
            {
                throw new Exception("Build MAT record error: " + output);
            }
            return output;
        }
    }
}
