using System;
using System.Text;
using System.Data.Odbc;
using System.Collections.Generic;
using System.Linq;
using System.IO;
using ExcoUtility;
using UploadFF;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace Test_ProcessFFv2
{
    [TestClass]
    public class UploadFFTest
    {
        private TestContext testContextInstance;

        /// <summary>
        ///Gets or sets the test context which provides
        ///information about and functionality for the current test run.
        ///</summary>
        public TestContext TestContext
        {
            get
            {
                return testContextInstance;
            }
            set
            {
                testContextInstance = value;
            }
        }

        internal Process process = new Process();
        // try to delete 790, ok
        internal const string line1 = "0467945   RTE3790001NIN1   NI 000000000000000100000001C100000000010001010000000000000001Y000000000N                                        0000000000000000000000000000000000000000000000";
        // try to create sub parts, ok
        internal const string line2 = "0467946   BOM28000003HD 9 X 1.580 PLATE  00010000EA 000100RYYPRDY0003ZZTMPYY1                                                                                                            \r\nZZTMPYY1  BOM21000001H-13 9 DIA          00015925IN 000100RYYSTLY0001                                                                                                                    \r\n0467946   BOM28000002HD 9 X 1.654 MANDREL00010000EA 000100RYYPRDY0003ZZTMPYY2                                                                                                            \r\nZZTMPYY2  BOM21000001H-13 9 DIA          00016397IN 000100RYYSTLY0001                                                                                                                    \r\n0467946   BOM28000001HD 9 X 2.026 BACKER 00010000EA 000100RYYPRDY0003ZZTMPYY3                                                                                                            \r\nZZTMPYY3  BOM21000001H-13 9 DIA          00020177IN 000100RYYSTLY0001                                                                                                                    ";
        // try to create solid die, need to delete nitride
        internal const string line3 = "0467944   BOM21000001H-13 14 DIA         00014823IN 000100RYYPRDY0001                                                                                                                    ";
        // try to delete 30, but 30 doesn't exist, bad
        internal const string line4 = "0467429   RTE3030001CMEMPL CAM000000000000000100000001C100000000010001010000000000000001Y000000000N                                        0000000000000000000000000000000000000000000000";
        // try to create solid die, ok
        internal const string line5 = "0467429   BOM21000001H-13 14 DIA         00014823IN 000100RYYPRDY0001                                                                                                                    ";
        // try to delete 20, ok
        internal const string line6 = "0467435   RTE3020001CMEMPL CAM000000000000000100000001C100000000010001010000000000000001Y000000000N                                        0000000000000000000000000000000000000000000000";
        // work order doesn't exist, bad
        internal const string line7 = "9999999   RTE3020001CMEMPL CAM000000000000000100000001C100000000010001010000000000000001Y000000000N                                        0000000000000000000000000000000000000000000000";
        // invalid record format, bad
        internal const string line8 = "0320047   RTE3020001CMEMPL ";
        // invalid record: wo exists but so doesn't exist, bad
        internal const string line9 = "0465060   RTE3020001CMEMPL CAM000000000000000100000001C100000000010001010000000000000001Y000000000N                                        0000000000000000000000000000000000000000000000";
        // try to create subparts, but they have been already
        // created, bad
        internal const string line10 = "0433730   BOM28000003HD 9 X 1.580 PLATE  00010000EA 000100RYYPRDY0003ZZTMPYY1                                                                                                            \r\nZZTMPYY1  BOM21000001H-13 9 DIA          00015925IN 000100RYYSTLY0001                                                                                                                    \r\n0433730   BOM28000002HD 9 X 1.654 MANDREL00010000EA 000100RYYPRDY0003ZZTMPYY2                                                                                                            \r\nZZTMPYY2  BOM21000001H-13 9 DIA          00016397IN 000100RYYSTLY0001                                                                                                                    \r\n0433730   BOM28000001HD 9 X 2.026 BACKER 00010000EA 000100RYYPRDY0003ZZTMPYY3                                                                                                            \r\nZZTMPYY3  BOM21000001H-13 9 DIA          00020177IN 000100RYYSTLY0001                                                                                                                    ";
        // try to create subparts without nitride, but they
        // have nitride, ignore nitride deletion record
        internal const string line11 = "0467944   BOM28000003HD 9 X 1.580 PLATE  00010000EA 000100RYYPRDY0003ZZTMPYY1                                                                                                            \r\nZZTMPYY1  RTE3790001NIN1   NI 000000000000000100000001C100000000010001010000000000000001Y000000000N                                        0000000000000000000000000000000000000000000000";
        // try to create subparts with nitride, but they don't
        // have nitride, add nitride deletion record
        internal const string line12 = "0433730   BOM28000003HD 9 X 1.580 PLATE  00010000EA 000100RYYPRDY0003ZZTMPYY1                                                                                                            ";
        // try to delete inexist backer, ignore that record
        internal const string line13 = "0433205   BOM38000001HD 9 X 5.5 BACKER   00010000EA 000100RYYPRDY0001                                                                                                                    \r\n0433205   BOM28000003HD 9 X 2.768 PLATE  00010000EA 000100RYYPRDY0003ZZTMPYY1                                                                                                            \r\nZZTMPYY1  BOM21000001H-13 9 DIA          00027736IN 000100RYYPRDY0001                                                                                                                    ";
        // try to delete backer and plant
        internal const string line14 = "0433730   BOM38000001HD 10 X 3.138 BACKER00010000EA 000100RYYPRDY0001                                                                                                                    \r\n0433730   BOM38000003HD 10 X 3.138 PLATE 00010000EA 000100RYYPRDY0001                                                                                                                    \r\n0433730   BOM28000002HD 10 X 4.494 MANDRE00010000EA 000100RYYPRDY0003ZZTMPYY1                                                                                                            \r\nZZTMPYY1  BOM21000001H-13 10 DIA         00044901IN 000100RYYPRDY0001                                                                                                                    ";
        // try to create subparts, but only plate needs nitride
        internal const string line15 = "0317927   BOM28000003HD 9 X 1.580 PLATE  00010000EA 000100RYYPRDY0003ZZTMPYY1                                                                                                            \r\nZZTMPYY1  BOM21000001H-13 9 DIA          00015925IN 000100RYYSTLY0001                                                                                                                    \r\n0317927   BOM28000002HD 9 X 1.654 MANDREL00010000EA 000100RYYPRDY0003ZZTMPYY2                                                                                                            \r\nZZTMPYY2  BOM21000001H-13 9 DIA          00016397IN 000100RYYSTLY0001                                                                                                                    \r\n0317927   BOM28000001HD 9 X 2.026 BACKER 00010000EA 000100RYYPRDY0003ZZTMPYY3                                                                                                            \r\nZZTMPYY3  BOM21000001H-13 9 DIA          00020177IN 000100RYYSTLY0001                                                                                                                    ";
        // try to create subparts, only mandrel needs nitride
        internal const string line16 = "0317000   BOM28000003HD 9 X 1.580 PLATE  00010000EA 000100RYYPRDY0003ZZTMPYY1                                                                                                            \r\nZZTMPYY1  BOM21000001H-13 9 DIA          00015925IN 000100RYYSTLY0001                                                                                                                    \r\n0317000   BOM28000002HD 9 X 1.654 MANDREL00010000EA 000100RYYPRDY0003ZZTMPYY2                                                                                                            \r\nZZTMPYY2  BOM21000001H-13 9 DIA          00016397IN 000100RYYSTLY0001                                                                                                                    \r\n0317000   BOM28000001HD 9 X 2.026 BACKER 00010000EA 000100RYYPRDY0003ZZTMPYY3                                                                                                            \r\nZZTMPYY3  BOM21000001H-13 9 DIA          00020177IN 000100RYYSTLY0001                                                                                                                    ";
        // try to create subparts, 10" is good
        internal const string line17 = "0436541   BOM28000003HD 10 X 2.380 PLATE 00010000EA 000100RYYPRDY0003ZZTMPYY1                                                                                                            \r\nZZTMPYY1  BOM21000001H-13 10 DIA         00023799IN 000100RYYPRDY0001                                                                                                                    \r\n0436541   BOM28000002HD 10 X 4.179 MANDRE00010000EA 000100RYYPRDY0003ZZTMPYY2                                                                                                            \r\nZZTMPYY2  BOM21000001H-13 10 DIA         00041830IN 000100RYYPRDY0001                                                                                                                    \r\n0436541   BOM28000001HD 10 X 1.969 BACKER00010000EA 000100RYYPRDY0003ZZTMPYY3                                                                                                            \r\nZZTMPYY3  BOM21000001H-13 10 DIA         00019114IN 000100RYYPRDY0001   ";
        // try to create subparts, 10" is bad, convert to 9"
        internal const string line18 = "0229620   BOM28000003HD 10 X 2.380 PLATE 00010000EA 000100RYYPRDY0003ZZTMPYY1                                                                                                            \r\nZZTMPYY1  BOM21000001H-13 10 DIA         00023799IN 000100RYYPRDY0001                                                                                                                    \r\n0229620   BOM28000002HD 10 X 4.179 MANDRE00010000EA 000100RYYPRDY0003ZZTMPYY2                                                                                                            \r\nZZTMPYY2  BOM21000001H-13 10 DIA         00041830IN 000100RYYPRDY0001                                                                                                                    \r\n0229620   BOM28000001HD 10 X 1.969 BACKER00010000EA 000100RYYPRDY0003ZZTMPYY3                                                                                                            \r\nZZTMPYY3  BOM21000001H-13 10 DIA         00019114IN 000100RYYPRDY0001   ";
        // try to create subparts, 9.5" is bad, convert to 10"
        internal const string line19 = "0315708   BOM28000003HD 10 X 2.380 PLATE 00010000EA 000100RYYPRDY0003ZZTMPYY1                                                                                                            \r\nZZTMPYY1  BOM21000001H-13 9.5 DIA        00023799IN 000100RYYPRDY0001                                                                                                                    \r\n0315708   BOM28000002HD 10 X 4.179 MANDRE00010000EA 000100RYYPRDY0003ZZTMPYY2                                                                                                            \r\nZZTMPYY2  BOM21000001H-13 9.5 DIA        00041830IN 000100RYYPRDY0001                                                                                                                    \r\n0315708   BOM28000001HD 10 X 1.969 BACKER00010000EA 000100RYYPRDY0003ZZTMPYY3                                                                                                            \r\nZZTMPYY3  BOM21000001H-13 9.5 DIA        00019114IN 000100RYYPRDY0001   ";
        // try to create subparts, 9.5" is bad, convert to 9"
        internal const string line20 = "0229620   BOM28000003HD 10 X 2.380 PLATE 00010000EA 000100RYYPRDY0003ZZTMPYY1                                                                                                            \r\nZZTMPYY1  BOM21000001H-13 9.5 DIA        00023799IN 000100RYYPRDY0001                                                                                                                    \r\n0229620   BOM28000002HD 10 X 4.179 MANDRE00010000EA 000100RYYPRDY0003ZZTMPYY2                                                                                                            \r\nZZTMPYY2  BOM21000001H-13 9.5 DIA        00041830IN 000100RYYPRDY0001                                                                                                                    \r\n0229620   BOM28000001HD 10 X 1.969 BACKER00010000EA 000100RYYPRDY0003ZZTMPYY3                                                                                                            \r\nZZTMPYY3  BOM21000001H-13 9.5 DIA        00019114IN 000100RYYPRDY0001   ";
        // RTE1 command, ok
        internal const string line21 = "0320028   RTE1010001CDEMPL SHP000000000000001500000015C100000000010001010000000000000001Y000000000N                                        0000000000000000000000000000000000000000000000";
        // RTE1 command, bad
        internal const string line22 = "0320027   RTE1010001CDEMPL SHP000000000000001500000015C100000000010001010000000000000001Y000000000N                                        0000000000000000000000000000000000000000000000";
        // RTE2 command, ok
        internal const string line23 = "0320027   RTE2010001CDEMPL SHP000000000000001500000015C100000000010001010000000000000001Y000000000N                                        0000000000000000000000000000000000000000000000";
        // RTE2 command, bad
        internal const string line24 = "0320028   RTE2010001CDEMPL SHP000000000000001500000015C100000000010001010000000000000001Y000000000N                                        0000000000000000000000000000000000000000000000";


        //Use TestInitialize to run code before running each test
        [TestInitialize()]
        public void MyTestInitialize()
        {
            // initialize process object
            process.targetFolder = "D:\\RTEBOMP1\\";
            process.sourceFolder = "D:\\FF\\";
            process.rerunFolder = "D:\\ReRun\\";
            process.errorFolder = "D:\\FFerrs\\";
            process.archiveFolder = "D:\\ffdone\\";
            process.backupFolder = "D:\\cms\\";
            process.targetFileName = "FF.txt";
            process.targetPath = process.targetFolder + process.targetFileName;
            // process folders
            if (true == Directory.Exists(process.targetFolder))
            {
                Directory.Delete(process.targetFolder, true);
            }
            Directory.CreateDirectory(process.targetFolder);
            if (true == Directory.Exists(process.sourceFolder))
            {
                Directory.Delete(process.sourceFolder, true);
            }
            Directory.CreateDirectory(process.sourceFolder);
            if (true == Directory.Exists(process.rerunFolder))
            {
                Directory.Delete(process.rerunFolder, true);
            }
            Directory.CreateDirectory(process.rerunFolder);
            if (true == Directory.Exists(process.errorFolder))
            {
                Directory.Delete(process.errorFolder, true);
            }
            Directory.CreateDirectory(process.errorFolder);
            if (true == Directory.Exists(process.archiveFolder))
            {
                Directory.Delete(process.archiveFolder, true);
            }
            Directory.CreateDirectory(process.archiveFolder);
            if (true == Directory.Exists(process.backupFolder))
            {
                Directory.Delete(process.backupFolder, true);
            }
            Directory.CreateDirectory(process.backupFolder);
        }

        [TestMethod]
        public void WriteCacheIntoFilesTest()
        {
            // build fileCache contents
            process.fileCache.Clear();
            Assert.AreEqual(0, process.fileCache.Count);
            process.fileCache.Add(line1);
            process.fileCache.Add(line2);
            Assert.AreEqual(2, process.fileCache.Count);
            Assert.IsTrue(Directory.Exists(process.archiveFolder));
            Assert.AreEqual(0, Directory.GetFiles(process.archiveFolder).Length);
            // run test
            process.WriteCacheIntoFiles(process.archiveFolder + DateTime.Now.ToString("yyyyMM") + "\\", Database.PRODTEST);
            // check result
            string[] pathArray = Directory.GetDirectories(process.archiveFolder);
            Assert.AreEqual(1, pathArray.Length);
            Assert.AreEqual(process.archiveFolder + DateTime.Now.ToString("yyyyMM"), pathArray[0]);
            pathArray = Directory.GetFiles(pathArray[0]);
            Assert.AreEqual(2, pathArray.Length);
            Assert.IsTrue(pathArray[0].Contains("278507_0467945"));
            Assert.AreEqual("0467945   RTE3790001NIN1   NI 000000000000000100000001C100000000010001010000000000000001Y000000000N                                        0000000000000000000000000000000000000000000000", File.ReadAllText(pathArray[0]));
            Assert.IsTrue(pathArray[1].Contains("278508_0467946"));
            Assert.AreEqual("0467946   BOM28000003HD 9 X 1.580 PLATE  00010000EA 000100RYYPRDY0003ZZTMPYY1                                                                                                            \r\nZZTMPYY1  BOM21000001H-13 9 DIA          00015925IN 000100RYYSTLY0001                                                                                                                    \r\n0467946   BOM28000002HD 9 X 1.654 MANDREL00010000EA 000100RYYPRDY0003ZZTMPYY2                                                                                                            \r\nZZTMPYY2  BOM21000001H-13 9 DIA          00016397IN 000100RYYSTLY0001                                                                                                                    \r\n0467946   BOM28000001HD 9 X 2.026 BACKER 00010000EA 000100RYYPRDY0003ZZTMPYY3                                                                                                            \r\nZZTMPYY3  BOM21000001H-13 9 DIA          00020177IN 000100RYYSTLY0001                                                                                                                    ", File.ReadAllText(pathArray[1]));
        }

        [TestMethod]
        public void WriteCacheIntoTargetFolderTest()
        {
            // build fileCache contents
            process.fileCache.Clear();
            Assert.AreEqual(0, process.fileCache.Count);
            process.fileCache.Add(line1);
            process.fileCache.Add(line4);
            Assert.AreEqual(2, process.fileCache.Count);
            Assert.IsTrue(Directory.Exists(process.targetFolder));
            Assert.AreEqual(0, Directory.GetFiles(process.targetFolder).Length);
            // run test
            process.WriteCacheIntoTargetFolder();
            // check result
            string[] pathArray = Directory.GetFiles(process.targetFolder);
            Assert.AreEqual(1, pathArray.Length);
            Assert.AreEqual(process.targetPath, pathArray[0]);
            string[] fileLines = File.ReadAllLines(process.targetPath);
            Assert.AreEqual(line1 + Environment.NewLine + line4, File.ReadAllText(process.targetPath));
        }

        [TestMethod]
        public void ReadFileIntoCacheTest()
        {
            // put line1, line2, line4 into a single file
            StreamWriter writer = File.CreateText(process.sourceFolder + "test.txt");
            writer.WriteLine(line1);
            writer.WriteLine(line2);
            writer.WriteLine(line4);
            writer.Close();
            // read into file cache
            process.fileCache.Clear();
            // check result
            Assert.AreEqual(0, process.fileCache.Count);
            process.ReadFileIntoCache(process.sourceFolder + "test.txt");
            Assert.AreEqual(3, process.fileCache.Count);
            Assert.AreEqual(line1, process.fileCache[0]);
            Assert.AreEqual(line2, process.fileCache[1]);
            Assert.AreEqual(line4, process.fileCache[2]);
        }

        [TestMethod]
        public void ReadSourceFilesTest()
        {
            // put line1, line2, line4, line8 into files
            // here line8 should be ignored
            Assert.AreEqual(0, Directory.GetFiles(process.sourceFolder).Length);
            StreamWriter writer = File.CreateText(process.sourceFolder + "test1.txt");
            writer.WriteLine(line1);
            writer.Close();
            writer = File.CreateText(process.sourceFolder + "test2.txt");
            writer.WriteLine(line2);
            writer.Close();
            writer = File.CreateText(process.sourceFolder + "test4.txt");
            writer.WriteLine(line4);
            writer.Close();
            writer = File.CreateText(process.sourceFolder + "test8.txt");
            writer.WriteLine(line8);
            writer.Close();
            Assert.AreEqual(4, Directory.GetFiles(process.sourceFolder).Length);
            // read all source files
            process.fileCache.Clear();
            Assert.AreEqual(0, process.fileCache.Count);
            Assert.AreEqual(0, Directory.GetFiles(process.archiveFolder).Length);
            process.ReadSourceFiles();
            // check result            
            Assert.AreEqual(3, process.fileCache.Count);
            Assert.AreEqual(line1, process.fileCache[0]);
            Assert.AreEqual(line2, process.fileCache[1]);
            Assert.AreEqual(line4, process.fileCache[2]);
            Assert.AreEqual(0, Directory.GetFiles(process.sourceFolder).Length);
            string[] files = Directory.GetFiles(process.backupFolder);
            Assert.AreEqual(4, files.Length);
            Assert.AreEqual("test1.txt", Path.GetFileName(files[0]));
            Assert.AreEqual("test2.txt", Path.GetFileName(files[1]));
            Assert.AreEqual("test4.txt", Path.GetFileName(files[2]));
            Assert.AreEqual("test8.txt", Path.GetFileName(files[3]));
            Assert.AreEqual(line1 + "\r\n", File.ReadAllText(files[0]));
            Assert.AreEqual(line2 + "\r\n", File.ReadAllText(files[1]));
            Assert.AreEqual(line4 + "\r\n", File.ReadAllText(files[2]));
            Assert.AreEqual(line8 + "\r\n", File.ReadAllText(files[3]));
        }

        [TestMethod]
        public void RemoveDuplicatedRecords()
        {
            // case 1 remove duplicated RTE records
            process.fileCache.Clear();
            Assert.AreEqual(0, process.fileCache.Count);
            process.fileCache.Add(line1);
            process.fileCache.Add(line2);
            process.fileCache.Add(line1);
            process.fileCache.Add(line1.Replace("790", "030"));
            Assert.AreEqual(4, process.fileCache.Count);
            process.RemoveDuplicatedRecords();
            Assert.AreEqual(3, process.fileCache.Count);
            Assert.AreEqual(line2, process.fileCache[0]);
            Assert.AreEqual(line1, process.fileCache[1]);
            Assert.AreEqual(line1.Replace("790", "030"), process.fileCache[2]);
            // case 2 remove duplicated BOM records
            process.fileCache.Clear();
            Assert.AreEqual(0, process.fileCache.Count);
            process.fileCache.Add(line2);
            process.fileCache.Add(line1);
            process.fileCache.Add(line2);
            Assert.AreEqual(3, process.fileCache.Count);
            process.RemoveDuplicatedRecords();
            Assert.AreEqual(2, process.fileCache.Count);
            Assert.AreEqual(line1, process.fileCache[0]);
            Assert.AreEqual(line2, process.fileCache[1]);
        }

        [TestMethod]
        public void RemoveInvalidRecordsTest()
        {
            // case 1 wo exists but so doesn't exist
            process.fileCache.Clear();
            Assert.AreEqual(0, process.fileCache.Count);
            process.fileCache.Add(line9);
            process.fileCache.Add(line2);
            process.fileCache.Add(line1);
            Assert.AreEqual(3, process.fileCache.Count);
            process.RemoveInvalidRecords(Database.PRODTEST);
            Assert.AreEqual(2, process.fileCache.Count);
            Assert.AreEqual(line2, process.fileCache[0]);
            Assert.AreEqual(line1, process.fileCache[1]);
            // case 2 remove duplicated BOM records
            process.fileCache.Clear();
            Assert.AreEqual(0, process.fileCache.Count);
            process.fileCache.Add(line7);
            process.fileCache.Add(line1);
            process.fileCache.Add(line2);
            Assert.AreEqual(3, process.fileCache.Count);
            process.RemoveInvalidRecords(Database.PRODTEST);
            Assert.AreEqual(2, process.fileCache.Count);
            Assert.AreEqual(line1, process.fileCache[0]);
            Assert.AreEqual(line2, process.fileCache[1]);
        }

        [TestMethod]
        public void RemoveInvalidRTERecordsTest()
        {
            process.fileCache.Clear();
            Assert.AreEqual(0, process.fileCache.Count);
            process.fileCache.Add(line2);
            process.fileCache.Add(line4);
            process.fileCache.Add(line6);
            process.fileCache.Add(line1);
            process.fileCache.Add(line21);
            process.fileCache.Add(line22);
            process.fileCache.Add(line23);
            process.fileCache.Add(line24);
            Assert.AreEqual(8, process.fileCache.Count);
            process.RemoveInvalidRTERecords(Database.PRODTEST);
            Assert.AreEqual(4, process.fileCache.Count);
            Assert.AreEqual(line2, process.fileCache[0]);
            Assert.AreEqual(line6, process.fileCache[1]);
            Assert.AreEqual(line21, process.fileCache[2]);
            Assert.AreEqual(line22, process.fileCache[3]);
        }

        [TestMethod]
        public void RemoveInvalidBOMDeletionTest()
        {
            process.fileCache.Clear();
            Assert.AreEqual(0, process.fileCache.Count);
            process.fileCache.Add(line2);
            process.fileCache.Add(line1);
            process.fileCache.Add(line13);
            Assert.AreEqual(3, process.fileCache.Count);
            process.RemoveInvalidBOMDeletion(Database.PRODTEST);
            Assert.AreEqual(3, process.fileCache.Count);
            Assert.AreEqual(line2, process.fileCache[0]);
            Assert.AreEqual(line1, process.fileCache[1]);
            Assert.AreEqual(line13.Substring(187, line13.Length - 187), process.fileCache[2]);
        }
        
        [TestMethod]
        public void RemoveProcessedBOMTest()
        {
            process.fileCache.Clear();
            Assert.AreEqual(0, process.fileCache.Count);
            process.fileCache.Add(line2);
            process.fileCache.Add(line1);
            process.fileCache.Add(line10);
            Assert.AreEqual(3, process.fileCache.Count);
            process.RemoveProcessedBOM(Database.PRODTEST);
            Assert.AreEqual(2, process.fileCache.Count);
            Assert.AreEqual(line2, process.fileCache[0]);
            Assert.AreEqual(line1, process.fileCache[1]);
        }

        [TestMethod]
        public void ProcessBOMNitrideTest()
        {
            process.fileCache.Clear();
            Assert.AreEqual(0, process.fileCache.Count);
            process.fileCache.Add(line1);
            process.fileCache.Add(line12);
            process.fileCache.Add(line10);
            process.fileCache.Add(line3);
            process.fileCache.Add(line5);
            process.fileCache.Add(line14);
            process.fileCache.Add(line15);
            Assert.AreEqual(7, process.fileCache.Count);
            process.ProcessBOMNitride(Database.PRODTEST);
            Assert.AreEqual(8, process.fileCache.Count);
            int index = 0;
            Assert.AreEqual(line1, process.fileCache[index++]);
            Assert.AreEqual(line12 + "\r\nZZTMPYY1  RTE3790001NIN1   NI 000000000000000100000001C100000000010001010000000000000001Y000000000N                                        0000000000000000000000000000000000000000000000", process.fileCache[index++]);
            Assert.AreEqual(line10 + "\r\nZZTMPYY1  RTE3790001NIN1   NI 000000000000000100000001C100000000010001010000000000000001Y000000000N                                        0000000000000000000000000000000000000000000000\r\nZZTMPYY2  RTE3790001NIN1   NI 000000000000000100000001C100000000010001010000000000000001Y000000000N                                        0000000000000000000000000000000000000000000000", process.fileCache[index++]);
            Assert.AreEqual(line3, process.fileCache[index++]);
            Assert.AreEqual(line5, process.fileCache[index++]);
            Assert.AreEqual(line14 + "\r\nZZTMPYY1  RTE3790001NIN1   NI 000000000000000100000001C100000000010001010000000000000001Y000000000N                                        0000000000000000000000000000000000000000000000", process.fileCache[index++]);
            Assert.AreEqual(line15 + "\r\nZZTMPYY2  RTE3790001NIN1   NI 000000000000000100000001C100000000010001010000000000000001Y000000000N                                        0000000000000000000000000000000000000000000000", process.fileCache[index++]);
            Assert.AreEqual("0467944   RTE3790001NIN1   NI 000000000000000100000001C100000000010001010000000000000001Y000000000N                                        0000000000000000000000000000000000000000000000", process.fileCache[index++]);
            Assert.AreEqual(8, index);
        }

        [TestMethod]
        public void AdjustBOMSteelDiameterTest()
        {
            // no proper test case right now

            //process.fileCache.Clear();
            //Assert.AreEqual(0, process.fileCache.Count);
            //process.fileCache.Add(line9);
            //process.fileCache.Add(line10);
            //process.fileCache.Add(line17);
            //process.fileCache.Add(line18);
            //process.fileCache.Add(line19);
            //process.fileCache.Add(line20);
            //Assert.AreEqual(6, process.fileCache.Count);
            //process.AdjustBOMSteelDiameter(Database.PRODTEST);
            //Assert.AreEqual(6, process.fileCache.Count);
            //Assert.AreEqual(line9, process.fileCache[0]);
            //Assert.AreEqual(line10, process.fileCache[1]);
            //Assert.AreEqual(line17, process.fileCache[2]);
            //Assert.AreEqual(line18.Replace("H-13 10 DIA", "H-13 9 DIA "), process.fileCache[3]);
            //Assert.AreEqual(line19.Replace("H-13 9.5 DIA", "H-13 10 DIA "), process.fileCache[4]);
            //Assert.AreEqual(line20.Replace("H-13 9.5 DIA", "H-13 9 DIA  "), process.fileCache[5]);
        }

        [TestMethod]
        public void ProcessBOMTagTest()
        {
            process.fileCache.Clear();
            Assert.AreEqual(0, process.fileCache.Count);
            process.fileCache.Add(line2);
            process.fileCache.Add(line1);
            process.fileCache.Add(line11);
            process.fileCache.Add(line12);
            process.fileCache.Add(line10);
            Assert.AreEqual(5, process.fileCache.Count);
            process.ProcessBOMTag();
            Assert.AreEqual(5, process.fileCache.Count);
            string result = line2.Replace("ZZTMPYY1", "TMP01   ");
            result = result.Replace("ZZTMPYY2", "TMP02   ");
            result = result.Replace("ZZTMPYY3", "TMP03   ");
            Assert.AreEqual(result, process.fileCache[0]);
            Assert.AreEqual(line1, process.fileCache[1]);
            result = line11.Replace("ZZTMPYY1", "TMP04   ");
            Assert.AreEqual(result, process.fileCache[2]);
            result = line12.Replace("ZZTMPYY1", "TMP05   ");
            Assert.AreEqual(result, process.fileCache[3]);
            result = line10.Replace("ZZTMPYY1", "TMP06   ");
            result = result.Replace("ZZTMPYY2", "TMP07   ");
            result = result.Replace("ZZTMPYY3", "TMP08   ");
            Assert.AreEqual(result, process.fileCache[4]);
        }
    }
}