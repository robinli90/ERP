using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace BatchUpdate
{
    public enum FieldType
    {
        NULL,
        Text,
        Numeric
    }

    public class Field
    {
#if DEBUG
        // field length
        public int length = 0;
        // field type
        // if text, output blank as space
        // if numeric, output blank as 0
        public FieldType type = FieldType.NULL;
        // field string value
        public string value = string.Empty;
        // blank char
        public char blankChar = ' ';
#else
        private int length = 0;
        private FieldType type = FieldType.NULL;
        private string value = string.Empty;
        private char blankChar = ' ';
#endif


        // default constructor
        public Field(int length, FieldType type)
        {
            this.length = length;
            this.type = type;
            // set blank char value
            switch (type)
            {
                case FieldType.Numeric:
                    blankChar = '0';
                    break;
                case FieldType.Text:
                    blankChar = ' ';
                    break;
                default:
                    throw new Exception("Invalid field type");
            }
            // set default value string
            value = new string(blankChar, length);
        }

        // set value
        public void SetString(string value)
        {
            if (value.Length > length)
            {
                throw new Exception("Value too long: " + value);
            }
            this.value = value.PadRight(length, blankChar);
        }

        // field string constructor
        public string GetString()
        {
            return value;
        }
    }
}
