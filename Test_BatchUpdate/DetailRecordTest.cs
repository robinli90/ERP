//using System;
//using System.Collections.Generic;
//using System.Linq;
//using System.Text;
//using BatchUpdate;
//using Microsoft.VisualStudio.TestTools.UnitTesting;

//namespace Test_BatchUpdate
//{
//    [TestClass]
//    public class DetailRecordTest
//    {
//        [TestMethod]
//        public void TestConstructor()
//        {
//            DetailRecord record = new DetailRecord();
//            Assert.AreEqual("DTL", record.title.value);
//            Assert.AreEqual("R", record.mode.value);
//            Assert.AreEqual(new string(' ', 2), record.department.value);
//            Assert.AreEqual(new string(' ', 5), record.resource.value);
//            Assert.AreEqual(new string(' ', 20), record.part.value);
//            Assert.AreEqual(new string('0', 3), record.seq.value);
//            Assert.AreEqual(new string(' ', 10), record.indCode.value);
//            Assert.AreEqual(new string('0', 4), record.totalMachTime.value);
//            Assert.AreEqual(new string(' ', 10), record.workOrder.value);
//            Assert.AreEqual(new string(' ', 1), record.numMen.value);
//            Assert.AreEqual(new string(' ', 1), record.numMach.value);
//            Assert.AreEqual(new string(' ', 1), record.reversing.value);
//            Assert.AreEqual(new string(' ', 1), record.use2Digits.value);
//            Assert.AreEqual(new string(' ', 2), record.numMen2Digits.value);
//            Assert.AreEqual(new string(' ', 2), record.numMach2Digits.value);
//        }

//        [TestMethod]
//        public void TestBuildString()
//        {
//            DetailRecord record = new DetailRecord();
//            record.numMach2Digits.SetString("22");
//            record.numMen2Digits.SetString("aa");
//            record.use2Digits.SetString("Y");
//            record.reversing.SetString("9");
//            record.numMach.SetString("2");
//            record.numMen.SetString("p");
//            record.workOrder.SetString("0010425689");
//            record.totalMachTime.SetString("1234");
//            record.indCode.SetString("abcdefghij");
//            record.seq.SetString("ooo");
//            record.part.SetString("HD 15 X 2 Backer aaa");
//            record.resource.SetString("saw22");
//            record.department.SetString("qq");
//            Assert.AreEqual("DTLRqqsaw22HD 15 X 2 Backer aaaoooabcdefghij12340010425689p29Yaa22", record.BuildString());
//        }
//    }
//}
