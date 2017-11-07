using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace BatchUpdate
{
    // detail record, length 66
    public class DetailRecord
    {
        // title, default DTL
        // index 0, length 3
        public Field title = new Field(3, FieldType.Text);
        // mode S(Setup)/R(Run)/D(Downtime), default R
        // index 3, length 1
        public Field mode = new Field(1, FieldType.Text);
        // department
        // index 4, length 2
        public Field department = new Field(2, FieldType.Text);
        // resource
        // index 6, length 5
        public Field resource = new Field(5, FieldType.Text);
        // part# (family or actual part#)
        // index 11, length 20
        public Field part = new Field(20, FieldType.Text);
        // sequence#
        // index 31, length 3
        public Field seq = new Field(3, FieldType.Numeric);
        // indirect code (mandatory if mode is D), default empty
        // index 34, length 10
        public Field indCode = new Field(10, FieldType.Text);
        // total machine time (HHMM)
        // index 44, length 4
        public Field totalMachTime = new Field(4, FieldType.Numeric);
        // work order#
        // index 48, length 10
        public Field workOrder = new Field(10, FieldType.Text);
        // number of men, optional
        // index 58, length 1
        public Field numMen = new Field(1, FieldType.Text);
        // number of machines, optional
        // index 59, length 1
        public Field numMach = new Field(1, FieldType.Text);
        // reversing (Y or blank), optional
        // index 60, length 1
        public Field reversing = new Field(1, FieldType.Text);
        // use 2 digits for # of men/mach (Y or blank), optional
        // index 61, length 1
        public Field use2Digits = new Field(1, FieldType.Text);
        // number of men (2 digits), optional
        // index 62, length 2
        public Field numMen2Digits = new Field(2, FieldType.Text);
        // number of machines (2 digits), optional
        // index 64, length 2
        public Field numMach2Digits = new Field(2, FieldType.Text);

        // constructor
        public DetailRecord()
        {
            title.SetString("DTL");
            mode.SetString("R");
        }

        // construct header string and return
        public string BuildString()
        {
            string output = string.Empty;
            string value = string.Empty;
            // add title
            value = title.GetString();
            if (0 != value.CompareTo("DTL"))
            {
                throw new Exception("DTL record title invalid: " + value);
            }
            output += value;
            // add mode
            value = mode.GetString();
            if (0 != value.CompareTo("R"))
            {
                throw new Exception("DTL record mode invalid: " + value);
            }
            output += value;
            // add department
            value = department.GetString();
            if (0 == value.CompareTo(new string(' ', 2)))
            {
                throw new Exception("DTL record department invalid: " + value);
            }
            output += value;
            // add resource
            value = resource.GetString();
            if (0 == value.CompareTo(new string(' ', 5)))
            {
                throw new Exception("DTL record resource invalid: " + value);
            }
            output += value;
            // add part
            value = part.GetString();
            if (0 == value.CompareTo(new string(' ', 20)))
            {
                throw new Exception("DTL record part invalid: " + value);
            }
            output += value;
            // add sequence
            value = seq.GetString();
            if (0 == value.CompareTo(new string('0', 3)))
            {
                throw new Exception("DTL record sequence invalid: " + value);
            }
            output += value;
            // add indirect code
            output += indCode.GetString();
            // add total machine time
            output += totalMachTime.GetString();
            // add work order
            value = workOrder.GetString();
            if (0 == value.CompareTo(new string(' ', 10)))
            {
                throw new Exception("DTL record work order invalid: " + value);
            }
            output += value;
            // add number of men
            output += numMen.GetString();
            // add number of machines
            output += numMach.GetString();
            // add reversing
            output += reversing.GetString();
            // add use 2 digits for # of men/mach
            output += use2Digits.GetString();
            // add number of men (2 digits)
            output += numMen2Digits.GetString();
            // add number of machine (2 digits)
            output += numMach2Digits.GetString();
            // check string length
            if (66 != output.Length)
            {
                throw new Exception("Build DTL record error: " + output);
            }
            return output;
        }
    }
}
