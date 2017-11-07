using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using BatchUpdate;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using ExcoUtility;
using System.Data.Odbc;

namespace Test_BatchUpdate
{
    [TestClass]
    public class DieTest
    {
        [TestMethod]
        public void TestConstructor()
        {
            Die die = new Die(123456);
            Assert.AreEqual(123456, die.so);
            Assert.AreEqual(0, die.pieceList.Count);
            Assert.AreEqual(-1, die.parentIndex);
            Assert.IsFalse(die.isHollow);
        }

        [TestMethod]
        public void TestDetermineIsHollow()
        {
            Die die = new Die();
            die.pieceList.Add(new Piece());
            die.DetermineIsHollow();
            Assert.IsFalse(die.isHollow);
            die.pieceList.Add(new Piece("0000000", "HD 9 X 4", 'P', 278787));
            die.DetermineIsHollow();
            Assert.IsTrue(die.isHollow);
        }

        [TestMethod]
        public void TestFindParentIfHollow()
        {
            //Die die = new Die();
            //// 1. 7 digit work order
            //// 2. part description contains "HD "
            //// 3. last sequence is 800
            //// 4. has sub parts in cjobh or hjobh
            //die.FindParentIfHollow(Database.CMSDAT);
            //Assert.AreEqual(-1, die.parentIndex);
            //die.isHollow = true;
            //die.pieceList.Add(new Piece("001012345", "HD 22 X 9", 'P', 278787));
            //die.FindParentIfHollow(Database.CMSDAT);
            //Assert.AreEqual(-1, die.parentIndex);
            //die.pieceList.Add(new Piece("0465998", "SD 22 X 9", 'P', 278787));
            //die.FindParentIfHollow(Database.CMSDAT);
            //Assert.AreEqual(-1, die.parentIndex);
            //die.pieceList.Add(new Piece("0465998", "HD 22 X 9", 'G', 278121));
            //die.pieceList[2].GetInfo(Database.PRODTEST);
            //die.FindParentIfHollow();
            //Assert.AreEqual(2, die.parentIndex);
        }
    }
}