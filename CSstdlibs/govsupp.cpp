/***************************************************************************
    Portions Copyright (C) 1981-2009 Cadamation Systems Inc., Ontario, Canada 
            All Rights Reserved Worldwide

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
    SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
    FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
    ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
    DEALINGS IN THE SOFTWARE.
*****************************************************************************/

// govsupp.cpp Government Support functions


int ValidCanadianSIN(int sin[9])
{
    int i, n, w[9] ; 
    static int pattern[9] = {1,2,1,2,1,2,1,2,1} ; 

    for (i=0; i < 9; i++)
    {
        n = sin[i] * pattern[i] ; 
        if (n > 9) 
            n = (n % 10) + 1 ;
        w[i] = n ; 
    }

    n = 0 ; 
    for (i=0; i < 9; i++)
        n += w[i] ; 

    return ((n % 10) == 0) ? 1 : 0 ; 
}

int ValidCanadianSIN(char *sin)
{
    // The sin string is the SIN# as ASCII digits

    int i ; 
    int nsin[9] ; 

    for (i = 0; i < 9; i++)
        nsin[i] = sin[i] - '0' ; 
    
    return ValidCanadianSIN(nsin) ; 
}


