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
    public class PieceTest
    {
        [TestMethod]
        public void TestConstructor()
        {
            Piece piece = new Piece("0425252", "HD 8 X 6", 'M', 265656);
            Assert.AreEqual("0425252", piece.wo);
            Assert.AreEqual("HD 8 X 6", piece.part);
            Assert.AreEqual('M', piece.type);
            Assert.AreEqual(265656, piece.so);
        }


    }
}