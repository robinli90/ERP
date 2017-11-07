/***************************************************************************
    Copyright (C) 1986-2011 Cadamation Systems Inc., Ontario, Canada 
            All Rights Reserved Worldwide

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
    SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
    FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
    ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
    DEALINGS IN THE SOFTWARE.
*****************************************************************************/
#include <stdio.h>

#include <list>

using namespace std ; 

typedef list<int> IntList ; 
typedef list<int>::iterator IntListItr ; 

int main(int argc, char **argv)
{
    IntList intlist ;
    IntListItr ili = intlist.begin() ;
    if (ili == intlist.end())
    {
        printf("In uninited list begin == end\n") ; 
    }
    else
    {
        printf("In uninited list begin != end\n") ; 
    }
    return 0 ; 
}
