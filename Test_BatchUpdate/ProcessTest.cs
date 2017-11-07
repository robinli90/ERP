using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using BatchUpdate;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using ExcoUtility;
using System.Data.Odbc;
using System.IO;

namespace Test_BatchUpdate
{
    [TestClass]
    public class ProcessTest
    {
        [TestMethod]
        public void TestConstructor()
        {
        }

        //[TestMethod]
        //public void TestWriteToBatchFile()
        //{
        //    Process process = new Process();
        //    process.batchFilePath = "D:\\batch.txt";
        //    Assert.AreEqual(0, process.cache.Count);
        //    process.cache.Add("aaa");
        //    process.cache.Add("BBB");
        //    if (File.Exists(process.batchFilePath))
        //    {
        //        File.Delete(process.batchFilePath);
        //    }
        //    Assert.IsFalse(File.Exists(process.batchFilePath));
        //    process.WriteToBatchFile();
        //    Assert.IsTrue(File.Exists(process.batchFilePath));
        //    string[] lines = File.ReadAllLines(process.batchFilePath);
        //    Assert.AreEqual(2, lines.Length);
        //    Assert.AreEqual("aaa", lines[0]);
        //    Assert.AreEqual("BBB", lines[1]);
        //    File.Delete(process.batchFilePath);
        //}
    }
}