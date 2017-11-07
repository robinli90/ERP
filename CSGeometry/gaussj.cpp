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
// gaussj.cpp - Gauss-Jordan elimination

#include <math.h>

// returns 0 for success or 1 if singular matrix

// This is Gauss-Jordan elimination as taken from Numerical Recipes in 
// Fortran.  

int CS_gaussj(double *a,  // The A[n x n] input matrix
              int n,      // dimension of input matrix a
              double *b,  // right hand side vectors 
              int m)      // number of column vectors to solve for in b
{
    int *indxc, *indxr, *ipiv ; 
    double big, dum, pivinv ; 
    int i, icol, irow, j, k, l, ll ;
    int retval ; 
    
    
    indxc = new int[n] ; 
    indxr = new int[n] ;
    ipiv = new int[n] ; 

    retval = 0 ; 
    
    try{

    for (j=0; j < n; j++)
    {
        ipiv[j]=0 ;
    }

    for (i=0; i < n; i++)
    {
        big=0.0 ;
        for (j=0;j < n; j++)
        {
            if (ipiv[j] != 1) 
            {
                for (k=0; k < n; k++)
                {
                    if (ipiv[k] == 0) 
                    {
                        if (fabs(a[(j * n) + k]) >= big) 
                        {
                            big = fabs(a[(j * n) + k]) ;
                            irow = j ;
                            icol = k ;
                        }
                    }
                    else if (ipiv[k] > 1) 
                    {
                        throw 1 ; // singular matrix in gaussj
                    }
                }
            }
        }
        
        ipiv[icol] = ipiv[icol] + 1 ;
        
        if (irow != icol) 
        {
            for (l=0; l < n; l++)
            {
                dum = a[(irow * n) + l] ;
                a[(irow * n) + l] = a[(icol * n) + l] ;
                a[(icol * n) + l] = dum ;
            }
            for (l=0; l < m; l++)
            {
                dum = b[(irow * m) + l] ;
                b[(irow * m) + l] = b[(icol * m) + l] ;
                b[(icol * m) + l] = dum ;
            }
        }
        indxr[i] = irow ;
        indxc[i] = icol ;
        
        if (fabs(a[(icol * n) + icol]) < 1e-16) throw 1 ; // singular matrix

        pivinv = 1.0 / a[(icol * n) + icol] ;
        
        a[(icol * n) + icol] = 1.0 ;

        for (l=0; l < n; l++)
        {
            a[(icol * n) +l] = a[(icol * n) + l] * pivinv ;
        }
        
        for (l=1; l < m; l++)
        {
            b[(icol * m) + l] = b[(icol * m) +l] * pivinv ;
        }
        
        for (ll=0; ll < n; ll++)
        {
            if (ll != icol) 
            {
                dum = a[(ll * n) +icol] ;
                a[(ll * n) + icol] = 0.0 ;
                
                for (l=0; l < n ;  l++)
                {
                    a[(ll * n) +l] = a[(ll * n) +l] - a[(icol * n) +l] * dum ;
                }
                
                for (l=0; l < m; l++)
                {
                    b[(ll * m) + l] = b[(ll * m) +l] - b[(icol * m) +l] * dum ;
                }                                                 
            }
        }
    }
    for (l = n-1; l >= 0; l--)
    {
        if (indxr[l] != indxc[l]) 
        {
            for (k=0; k < n; k++)
            {
                dum = a[(k * n) + indxr[l]] ;
                a[(k * n) + indxr[l]] = a[(k * n) + indxc[l]] ;
                a[(k * n) + indxc[l]] = dum ;
            }
        }
    }
    
    }
    catch (int sing)
    {
        // singularity error
        retval = sing ; 
    }
    
    delete[] indxc ;
    delete[] indxr ;    
    delete[] ipiv ;

    return retval ; // success
}
//   (C) Copr. 1986-92 Numerical Recipes Software 2-2.
