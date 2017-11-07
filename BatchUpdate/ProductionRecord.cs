using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace BatchUpdate
{
    // PRT record type, length 252
    public class ProductionRecord
    {
        // title, default PRT
        // index 0, length 3
        public Field title = new Field(3, FieldType.Text);
        // part#
        // index 3, length 20
        public Field part = new Field(20, FieldType.Text);
        // quantity good
        // index 23, length 10
        public Field quaGood = new Field(10, FieldType.Numeric);
        // quantity scrap, optional
        // index 33, length 20
        public Field quaSca = new Field(20, FieldType.Numeric);
        // units
        // index 53, length 3
        public Field units = new Field(3, FieldType.Text);
        // scarp reason, optional
        // index 56, length 2
        public Field scaReason = new Field(2, FieldType.Text);
        // employee department
        // index 58, length 2
        public Field empDep = new Field(2, FieldType.Text);
        // employee #
        // index 60, length 5
        public Field empNum = new Field(5, FieldType.Text);
        // charge department, optional
        // index 65, lengkth 2
        public Field chargeDep = new Field(2, FieldType.Text);
        // charge resource, optional
        // index 67, length 5
        public Field chargeRes = new Field(5, FieldType.Text);
        // reversing (Y), optional
        // index 72, length 1
        public Field reversing = new Field(1, FieldType.Text);
        // lot #, optional
        // index 73, length 15
        public Field lotNum = new Field(15, FieldType.Text);
        // stamp lot# on quantity scarp (Y), optional
        // index 88, length 1
        public Field stampLot = new Field(1, FieldType.Text);
        // create serial (Y-Yes, H-Yes+Hold), optional
        // index 89, length 1
        public Field createSer = new Field(1, FieldType.Text);
        // output queue library, optional
        // index 90, length 10
        public Field outputLib = new Field(10, FieldType.Text);
        // output queue name, optional
        // index 100, length 10
        public Field outputNam = new Field(10, FieldType.Text);
        // user-enter field 1, optional
        // index 110, length 20
        public Field userFie1 = new Field(20, FieldType.Text);
        // user-enter field 2, optional
        // index 130, length 20
        public Field userFie2 = new Field(20, FieldType.Text);
        // user-enter field 3, optional
        // index 150, length 20
        public Field userFie3 = new Field(20, FieldType.Text);
        // voiding serial, optional
        // index 170, length 11
        public Field voidSer = new Field(11, FieldType.Text);
        // product serial number, optional
        // index 181, length 30
        public Field prodSerNum = new Field(30, FieldType.Text);
        // no backflush (Y), optional
        // index 211, length 1
        public Field noBackFlush = new Field(1, FieldType.Text);
        // scan id, optional
        // index 212, length 40
        public Field scanID = new Field(40, FieldType.Text);

        // constructor
        public ProductionRecord()
        {
            title.SetString("PRT");
        }

        // construct header string and return
        public string BuildString()
        {
            string output = string.Empty;
            string value = string.Empty;
            // add title
            value = title.GetString();
            if (0 != value.CompareTo("PRT"))
            {
                throw new Exception("PRT record title invalid: " + value);
            }
            output += value;
            // add part#
            value = part.GetString();
            if (0 == value.CompareTo(new string(' ', 20)))
            {
                throw new Exception("PRT record part# invalid: " + value);
            }
            output += value;
            // add quantity good
            value = quaGood.GetString();
            if (0 == value.CompareTo(new string('0', 10)))
            {
                throw new Exception("PRT record quantity good invalid: " + value);
            }
            output += value;
            // add quantity scarp
            output += quaSca.GetString();
            // add units
            value = units.GetString();
            if (0 == value.CompareTo(new string(' ', 3)))
            {
                throw new Exception("PRT record units invalid: " + value);
            }
            output += value;
            // add scarp reason
            output += scaReason.GetString();
            // add employee department
            value = empDep.GetString();
            if (0 == value.CompareTo(new string(' ', 2)))
            {
                value = "XX";
            }
            output += value;
            // add employee #
            value = empNum.GetString();
            if (0 == value.CompareTo(new string(' ', 5)))
            {
                throw new Exception("PRT record employee# invalid: " + value);
            }
            output += value;
            // add charge department
            output += chargeDep.GetString();
            // add charge resource
            output += chargeRes.GetString();
            // add reversing (Y)
            output += reversing.GetString();
            // add lot#
            output += lotNum.GetString();
            // add stamp lot# on quantity scarp (Y)
            output += stampLot.GetString();
            // add create serial (Y-Yes, H-Yes+Hold)
            output += createSer.GetString();
            // add output queue library
            output += outputLib.GetString();
            // add output queue name
            output += outputNam.GetString();
            // add user-enter field 1
            output += userFie1.GetString();
            // add user-enter field 2
            output += userFie2.GetString();
            // add user-enter field 3
            output += userFie3.GetString();
            // add voiding serial
            output += voidSer.GetString();
            // add product serial number
            output += prodSerNum.GetString();
            // add no backflush (Y)
            output += noBackFlush.GetString();
            // add scan ID
            output += scanID.GetString();
            // check string length
            if (252 != output.Length)
            {
                throw new Exception("Build PRT record error: " + output);
            }
            return output;
        }
    }
}
