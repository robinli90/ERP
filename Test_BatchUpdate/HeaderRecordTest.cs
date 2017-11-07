//using System;
//using System.Collections.Generic;
//using System.Linq;
//using System.Text;
//using BatchUpdate;
//using Microsoft.VisualStudio.TestTools.UnitTesting;

//namespace Test_BatchUpdate
//{
//    [TestClass]
//    public class HeaderRecordTest
//    {
//        [TestMethod]
//        public void TestConstructor()
//        {
//            HeaderRecord record = new HeaderRecord();
//            Assert.AreEqual("HDR", record.title.value);
//            Assert.AreEqual(new string('0', 6), record.date.value);
//            Assert.AreEqual("1", record.shift.value);
//            Assert.AreEqual(new string('0', 4), record.fiscalPeriod.value);
//            Assert.AreEqual(new string(' ', 1), record.shiftGroup.value);
//            Assert.AreEqual(new string(' ', 3), record.fgStockLoc.value);
//            Assert.AreEqual("001", record.plant.value);
//        }

//        [TestMethod]
//        public void TestBuildString()
//        {
//            HeaderRecord record = new HeaderRecord();
//            record.plant.SetString("222");
//            record.fgStockLoc.SetString("aaa");
//            record.shiftGroup.SetString("5");
//            record.fiscalPeriod.SetString("1309");
//            record.date.SetString("061813");
//            Assert.AreEqual("HDR061813113095aaa222", record.BuildString());
//        }
//    }
//}
