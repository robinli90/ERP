// Configuration.cpp
//
//
//

#include "stdafx.h"
#include "InOut.h"
#include "Configuration.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CConfiguration g_Configuration;

// Constructor
//
CConfiguration::CConfiguration()
{
}

// Destructor
//
CConfiguration::~CConfiguration()
{
}

// Clear()
//
void CConfiguration::Clear()
{
    
    m_mapBooleans.clear();
    m_mapIntegers.clear();
    m_mapFloats.clear();
    m_mapStrings.clear();
}

CString NextToken(CString &strLine, const char *szDelims = " \t")
{
    
    CString strResult;
    
    int nIndex = strLine.FindOneOf(szDelims);
    if (nIndex == -1)
    {
        
        strResult = strLine;
        strLine = "";
    }
    else
    {
        
        strResult = strLine.Left(nIndex);
        strLine = strLine.Mid(nIndex + 1);
        strLine.TrimLeft();
    }
    
    return strResult;
}

// Load()
//
void CConfiguration::Load(const char *szFilename)
{
    
    CStdioFile fileInput;
    if (!fileInput.Open(szFilename, CFile::modeRead))
        throw CString("Error opening file.");
    
    CString strLine;
    while (fileInput.ReadString(strLine))
    {
        
        strLine.TrimLeft();
        strLine.TrimRight();
        
        if (strLine.IsEmpty())
            continue;
        if (strLine.GetAt(0) == '#')
            continue;
        
        CString strName = NextToken(strLine);
        if (strLine.IsEmpty())
            throw CString("");
        
        CString strEquals = NextToken(strLine);
        if (strEquals != "=")
            throw CString("");
        
        CString strType = NextToken(strLine, ":");
        if (strType.IsEmpty())
            throw CString("");
        strType.MakeLower();
        
        CString strValue = strLine;
        
        // booleans
        if (strType == "boolean" || strType == "bool" || strType == "b")
        {
            
            strValue.MakeLower();
            if (strValue == "true" || strValue == "t")
                m_mapBooleans.insert(std::make_pair(strName, true));
            else if (strValue == "false" || strValue == "f")
                m_mapBooleans.insert(std::make_pair(strName, false));
            else
                throw CString("Invalid boolean value.");
        }
        
        // integers
        else if (strType == "integer" || strType == "int" || strType == "i")
            m_mapIntegers.insert(std::make_pair(strName, atoi((LPCTSTR) strValue)));
        
        // floats
        else if (strType == "float" || strType == "f")
            m_mapFloats.insert(std::make_pair(strName, (float)(atof((LPCTSTR) strValue))));
        
        // strings
        else if (strType == "string" || strType == "s")
            m_mapStrings.insert(std::make_pair(strName, strValue));
        
        else
            throw CString("Invalid type.");
    }
}

// GetBoolean()
//
bool CConfiguration::GetBoolean(const char *szKey, bool bDefault) const
{
    
    std::map<CString, bool>::const_iterator i = m_mapBooleans.find(CString(szKey));
    if (i == m_mapBooleans.end())
        return bDefault;
    
    return i->second;
}

// GetInteger()
//
int CConfiguration::GetInteger(const char *szKey, int nDefault) const
{
    
    std::map<CString, int>::const_iterator i = m_mapIntegers.find(CString(szKey));
    if (i == m_mapIntegers.end())
        return nDefault;
    
    return i->second;
}

// GetFloat()
//
float CConfiguration::GetFloat(const char *szKey, float fDefault) const
{
    
    std::map<CString, float>::const_iterator i = m_mapFloats.find(CString(szKey));
    if (i == m_mapFloats.end())
        return fDefault;
    
    return i->second;
}

// GetString()
//
CString CConfiguration::GetString(const char *szKey, const char *szDefault) const
{
    
    std::map<CString, CString>::const_iterator i = m_mapStrings.find(CString(szKey));
    if (i == m_mapStrings.end())
        return CString(szDefault);
    
    return i->second;
}
