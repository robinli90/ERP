using System;
using System.Text;
using System.Collections.Generic;
using System.Linq;
using BatchUpdate;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace Test_BatchUpdate
{
    [TestClass]
    public class FieldTest
    {
        //[TestMethod]
        //public void TestConstructor()
        //{
        //    // numeric field
        //    Field field1 = new Field(4, FieldType.Numeric);
        //    Assert.AreEqual(4, field1.length);
        //    Assert.AreEqual('0', field1.blankChar);
        //    Assert.AreEqual(FieldType.Numeric, field1.type);
        //    Assert.AreEqual("0000", field1.value);
        //    // text field
        //    Field field2 = new Field(3, FieldType.Text);
        //    Assert.AreEqual(3, field2.length);
        //    Assert.AreEqual(' ', field2.blankChar);
        //    Assert.AreEqual(FieldType.Text, field2.type);
        //    Assert.AreEqual("   ", field2.value);
        //    // numeric field
        //    try
        //    {
        //        Field field3 = new Field(4, FieldType.NULL);
        //    }
        //    catch (Exception e)
        //    {
        //        Assert.AreEqual("Invalid field type", e.Message);
        //    }
        //}

        //[TestMethod]
        //public void TestGetString()
        //{
        //    Field field = new Field(4, FieldType.Numeric);
        //    field.SetString("aaa");
        //    Assert.AreEqual("aaa0", field.GetString());
        //}


        //[TestMethod]
        //public void TestSetString()
        //{
        //    // numeric field
        //    Field field1 = new Field(4, FieldType.Numeric);
        //    field1.SetString("aaa");
        //    Assert.AreEqual("aaa0", field1.value);
        //    field1.SetString("aaab");
        //    Assert.AreEqual("aaab", field1.value);
        //    try
        //    {
        //        field1.SetString("213414");
        //    }
        //    catch (Exception e)
        //    {
        //        Assert.AreEqual("Value too long: 213414", e.Message);
        //    }
        //    // text field
        //    Field field2 = new Field(5, FieldType.Text);
        //    field2.SetString("aaa");
        //    Assert.AreEqual("aaa  ", field2.value);
        //    field2.SetString("aaab3");
        //    Assert.AreEqual("aaab3", field2.value);
        //    try
        //    {
        //        field2.SetString("213414");
        //    }
        //    catch (Exception e)
        //    {
        //        Assert.AreEqual("Value too long: 213414", e.Message);
        //    }
        //}
    }
}
