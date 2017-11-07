/***************************************************************************
    Copyright (C) 1981-2009 Cadamation Systems Inc., Ontario, Canada 
            All Rights Reserved Worldwide

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
    SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
    FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
    ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
    DEALINGS IN THE SOFTWARE.
*****************************************************************************/

// cs_fileblk.h - File access in blocks. Useful when reading from binary
//  data files where the size of the required data block is unknown except
//  by looking at the data. 


#ifndef __CS_FILEBLK_H__
#define __CS_FILEBLK_H__

#ifdef WIN32
#pragma warning( disable : 4996 )
#endif 


//! Class used to read data when the size of the data blocks
//! within the file is unknown.
/*! 
  This allows the data to be read up front based on a certain minimum
  designated block size (or lookahead value). Thus the buffer is 
  pre-loaded with enough data to allow the main function to operate
  freely on the binary data without worrying about whether or not
  it has to read more memory from the disk. This only works if the 
  data blocks required are less than some minimum. If you need
  to see the entire file then there's no point using this class.

  Notes:

  No testing is done to make sure that buffer memory has been allocated
  for reading the data blocks. This is for efficiency purposes. 

  To use this class proceed as follows:
    <ul>
        <li> Instantiate the class data, and sepcify a minimum data size if required
        <li> Open the file to be read with OpenFile()
        <li> Loop through file until done processing
        <ul> 
            <li> Extract the data you require from the buffer and process it
            <li> Call Skip(n) where n is the number of bytes extracted and exit 
                when skip returns 0. Skip() returns the total buffer length 
                remaining. Skip also calls LoadBuffer(). 
        </ul>
        <li> Close the file
        <li> Call class destructor if dynamically allocated
    </ul>

  The default minimum read threshold is 16k (0x4000), thus data will 
  be read in chunks of 
 */
class CS_FileBlock 
{
public:
    enum {
        MINREADTHRESHOLD    = 0x4000,    
    } ;

    int minreadthreshold ;
    int buffersize ; 
    unsigned char *buf ; 
    int buflen, bufidx ; 
    unsigned long filepos ; // current offset into the file at start of buffer

    unsigned long fileLength ; 

    int bEOF ; // set true once all data from file is read
    FILE *fp ; // the file being read

    /*!
        Initializes the read buffer to MINREADTHRESHOLD * 4, 
        and sets all the internal counters to 0
     */
    CS_FileBlock() 
    {
        minreadthreshold = MINREADTHRESHOLD ; 
        buffersize = minreadthreshold * 4 ;
        buf =  new unsigned char[buffersize] ; 
        buflen = 0 ; 
        bufidx = 0 ; 
        filepos = 0 ; 
        fp = 0 ; 
        bEOF = 0 ; 
    } 

    //! CS_FileBlock constructor
    /*!
        \param minthresh  the amount of unread data in the buffer that triggers a read

        Initializes the read buffer to minthresh * 4, and sets all the internal counters
        to zero. When reading the file with the LoadBuffer() member function, 
        nothing is read unless the amount of data left unread in the buffer is 
        less than the minthresh value specified. Thus you want to set minthresh to 
        something larger than the largest data packet size that you expect to 
        receive during processing. 
     */
    CS_FileBlock(int minthresh) 
    {
        minreadthreshold = minthresh ; 
        buffersize = minreadthreshold * 4 ;
        buf =  new unsigned char[buffersize] ; 
        buflen = 0 ; 
        bufidx = 0 ; 
        filepos = 0 ; 
        fp = 0 ; 
        bEOF = 0 ; 
    } 


    ~CS_FileBlock() 
    {
        if (buf)
            delete[] buf ; 
        if (fp)
            fclose(fp) ; 
    } 

    //! Open the file and do initial read to load buffer 
    /*!
        \param filename Full pathname of file to be read
        \param mode fopen() style file mode string default = "rt"
        \return The file pointer. NULL if file couldn't be opened.

        Opens the file filename and reads the initial data block to 
        completely fill the allocated data buffer. The file is opened
        using the mode "rt" unless a value is passed in with the 
        mode variable ("rb" would be the only real logical other
        possibility here). 
     */
    FILE *OpenFile(char *filename, char *mode=0)
    {
        if (mode == 0)
            mode = "rt" ; 
        fp = fopen(filename, mode) ;
        if (!fp)
            return 0 ; 
        fseek(fp, 0, SEEK_END) ; 
        fileLength = ftell(fp) ; 
        fseek(fp, 0, SEEK_SET) ; 
        LoadBuffer() ; 
        return fp ; 
    }

    //! returns true if the buffer is empty, otherwise returns false.
    int Empty()
    {
        if (buflen)
            return 0 ; 
        return 1 ; 
    }

    //! Read enough data to fill the allocated data buffer. Returns
    //! number of bytes in buffer (not the number of bytes just read).
    int LoadBuffer() ; // returns the amount data in the buffer (buflen)

    //! Returns pointer to the next byte to be read from the buffer
    unsigned char *CurPos()
    {
        return &buf[bufidx] ; 
    } 

    //! returns the number of bytes from the CurPos [bufidx] to the end 
    //! of the buffer
    unsigned int BufSize()
    {
        return buflen - bufidx ; 
    }

    //! Returns reference to the next byte to be read from the buffer
    /*!
        \param n return character offset number of bytes from the current file index 

        When skip is called, the internal bufidx counter is incremented which
        is used as the base offset into the internal buffer. Thus to read 
        one byte at a time you would do the following

        \verbatim
        do {
            processNextChar(fl[0]) ; 
        } while (file.Skip(1)) ;
        \endverbatim
     */
    unsigned char &operator[](unsigned int n)
    {
        return buf[bufidx + n] ;
    }

    //! Advance the buffer pointer ahead by n bytes, then calls LoadBuffer.
    //! Returns the number of data bytes left in the buffer after the LoadBuffer call.
    int Skip(int n) ; // returns remaining buffer length
} ;


#endif


