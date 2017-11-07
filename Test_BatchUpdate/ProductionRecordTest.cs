//using System;
//using System.Collections.Generic;
//using System.Linq;
//using System.Text;
//using BatchUpdate;
//using Microsoft.VisualStudio.TestTools.UnitTesting;

//namespace Test_BatchUpdate
//{
//    [TestClass]
//    public class ProductionRecordTest
//    {
//        [TestMethod]
//        public void TestConstructor()
//        {
//            ProductionRecord record = new ProductionRecord();
//            Assert.AreEqual("PRT", record.title.value);
//            Assert.AreEqual(new string(' ', 20), record.part.value);
//            Assert.AreEqual(new string('0', 10), record.quaGood.value);
//            Assert.AreEqual(new string('0', 20), record.quaSca.value);
//            Assert.AreEqual(new string(' ', 3), record.units.value);
//            Assert.AreEqual(new string(' ', 2), record.scaReason.value);
//            Assert.AreEqual(new string(' ', 2), record.empDep.value);
//            Assert.AreEqual(new string(' ', 5), record.empNum.value);
//            Assert.AreEqual(new string(' ', 2), record.chargeDep.value);
//            Assert.AreEqual(new string(' ', 5), record.chargeRes.value);
//            Assert.AreEqual(new string(' ', 1), record.reversing.value);
//            Assert.AreEqual(new string(' ', 15), record.lotNum.value);
//            Assert.AreEqual(new string(' ', 1), record.stampLot.value);
//            Assert.AreEqual(new string(' ', 1), record.createSer.value);
//            Assert.AreEqual(new string(' ', 10), record.outputLib.value);
//            Assert.AreEqual(new string(' ', 10), record.outputNam.value);
//            Assert.AreEqual(new string(' ', 20), record.userFie1.value);
//            Assert.AreEqual(new string(' ', 20), record.userFie2.value);
//            Assert.AreEqual(new string(' ', 20), record.userFie3.value);
//            Assert.AreEqual(new string(' ', 11), record.voidSer.value);
//            Assert.AreEqual(new string(' ', 30), record.prodSerNum.value);
//            Assert.AreEqual(new string(' ', 1), record.noBackFlush.value);
//            Assert.AreEqual(new string(' ', 40), record.scanID.value);
//        }

//        [TestMethod]
//        public void TestBuildString()
//        {
//            ProductionRecord record = new ProductionRecord();
//            record.part.SetString("HD 12 X 5.890 MANDRE");
//            record.quaGood.SetString("0000000001");
//            record.quaSca.SetString("0");
//            record.units.SetString("EA");
//            record.empDep.SetString("SW");
//            record.empNum.SetString("99999");
//            record.noBackFlush.SetString("Y");
//            Assert.AreEqual("PRTHD 12 X 5.890 MANDRE000000000100000000000000000000EA   SW99999                                                                                                                                                  Y                                        ", record.BuildString());
//        }
//    }
//}
