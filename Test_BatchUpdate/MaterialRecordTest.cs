//using System;
//using System.Collections.Generic;
//using System.Linq;
//using System.Text;
//using BatchUpdate;
//using Microsoft.VisualStudio.TestTools.UnitTesting;

//namespace Test_BatchUpdate
//{
//    [TestClass]
//    public class MaterialRecordTest
//    {
//        [TestMethod]
//        public void TestConstructor()
//        {
//            MaterialRecord record = new MaterialRecord();
//            Assert.AreEqual("MAT", record.title.value);
//            Assert.AreEqual(new string(' ', 20), record.part.value);
//            Assert.AreEqual(new string(' ', 3), record.stoRoom.value);
//            Assert.AreEqual(new string(' ', 1), record.required.value);
//            Assert.AreEqual(new string(' ', 1), record.backFlush.value);
//            Assert.AreEqual(new string('0', 15), record.quantity.value);
//            Assert.AreEqual(new string(' ', 3), record.units.value);
//            Assert.AreEqual(new string(' ', 6), record.traDate.value);
//            Assert.AreEqual(new string(' ', 3), record.seqNum.value);
//            Assert.AreEqual(new string(' ', 15), record.lotNum.value);
//            Assert.AreEqual(new string(' ', 11), record.serNum.value);
//            Assert.AreEqual(new string(' ', 1), record.matScr.value);
//        }

//        [TestMethod]
//        public void TestBuildString()
//        {
//            MaterialRecord record = new MaterialRecord();
//            record.part.SetString("H-13 12 DIA         ");
//            record.stoRoom.SetString("STL");
//            record.required.SetString("R");
//            record.backFlush.SetString("Y");
//            record.quantity.SetString("000000000169480");
//            record.units.SetString("IN");
//            record.matScr.SetString("N");
//            Assert.AreEqual("MATH-13 12 DIA         STLRY000000000169480IN                                    N", record.BuildString());
//        }
//    }
//}