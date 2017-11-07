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

	This was originally taken from somebody else online
*****************************************************************************/

// govsupp.h - Government support functions header file

/* 
Social Insurance Number Authentication

Copyright Arkhein _

The Social Insurance Number (SIN) was created in 1964 to serve as a client 
account number in the administration of the Canada Pension Plan (CPP) and 
Canada's varied employment insurance programs.  In 1967, Revenue Canada, 
now called Canada Customs and Revenue Agency (CCRA) Canada Revenue Agency 
(CRA), co-opted the SIN and started using it for tax reporting purposes.  
Since then, things have gotten way out of control.  

The SIN is arguably your most valuable identification number and should be 
closely guarded.  A person possessing your SIN can easily apply for a 
credit card or open a bank account, rent vehicles, equipment, or 
accommodation -- all in your name and you will be held responsible by 
authorities.  Never use your SIN number as identification except where 
required by law.  

The only legislated uses of the SIN are: Canada Customs and Revenue 
Agency, your employer for Income Tax reporting, banks (with some 
exceptions), Social Assistance programs, and a few other government and/or 
tax related agencies.  When in doubt make them prove that you are legally 
obligated to provide your SIN.  Unless an organization can demonstrate 
that your SIN is required by law, or that no alternative identifier would 
suffice to complete the transaction, you cannot be denied a product or 
service on the grounds of your refusal to provide your SIN.  Banks don't 
even require your SIN anymore when you open an account.  Since interest 
rates are so low and service charges are so high, they are finally 
acknowledging that it more than cancels out any interest you could ever 
hope to get.  You may find some banks that try to insist that you provide 
your SIN.  Be persistent and/or shop around.  

Widespread use of the SIN as identification has put many peoples personal 
information and privacy at risk.  Computer technology makes it possible to 
use the SIN to find and match your information from one database to 
another; thereby facilitating the creation of a detailed profile about 
you.  Of course, if you are using credit/debit cards you are already 
seriously fucked in that regard.  

Algorithm _

Social Insurance Numbers are validated via a simple checksum process.

Let's use this fictitious SIN to demonstrate:

    046 454 286  <  Try substituting your SIN

    046 454 286  \  Multiply each top number
    121 212 121  /  by the number below it..
    -----------
    086 858 276  <  and get this.
             ^
             Notice here that 8*2=16, add 1 and
             6 together and get 7. If you get a
             2 digit # add the digits together.

Add all of these digits together.

0+8+6+8+5+8+2+7+6=50
                  /\
                If the SIN is valid this # will
                be evenly divisible by 10. This
                is a 'valid' SIN.

Application _

Here is a JavaScript app which demonstrates the algorithm.

Stick SIN in here
9 digits, no spaces
v 
  Valid?  
   

I also wrote a simple SIN validator for the PalmPilot. Requires cbasPad. 

Analysis _

The first digit of a SIN indicates province of registration. 

1 = NB, NF, NS, PE
2 = QC
3 = Not Used? QC?
4 = ON
5 = ON       6 = AB, MB, SK, NT, NU?
7 = BC, YU
8 = Not Used
9 = Immigrants & other temp SIN's
0 = Not Used  


Furthermore, it seems the second and third digits can be related to the 
birth-date of the SIN holder, or probably more accurately, the date period 
in which the SIN was registered.  For this analysis I've had to rely on 
date of birth since most people don't know when they registered for their 
SIN.  (Though the average age of registration seems to be around 17.) 
(Note: In the case of SIN's starting with 9 I am tracking date of 
registration.) We can clearly see a pattern in the tables below.  SIN's 
appear to be assigned incrementally by region.  More data is still 
required to complete this analysis and furnish comprehensive tables.  

At the present time I have kept the prairie provinces seperated from one 
another and done the same for the maritimes.  Though it is definitely 
looking like they are treated as groups and I will merge their respective 
sets of data once I have collected enough to prove this conclusively.  

(AB)       Alberta
------------------
609     1948-06-26
616     1948-11-06
620     1951-10-07
622     1953-08-16
623     1955-08-08
624     1957-08
624     1957-11
625     1955-09-26
631     1966-05-31
637     1967
637     1968-10-08
638     1967-11-09
639     1972-08-13
639     1973-08-19
640     1968-01-29
640     1971-08-17
641     1968-12-26
642     1972-09-24
642     1974-06-27
644     1975-01-06
644     1977-12-01
645     1974-12-15
645     1976-09-16
645     1977-02-17
647     1978-08-17
648     1982-04-07
649     1983-01-08
650     1980-01
650     1981-11-11
650     1983-01-14
650     1983-12-20
651     1981-10-29
651     1982-10-10
652     1982-04-24
653     1984-11-14
654     1984-01-26
654     1985-04-21
657     1986-03-27
659     1987-08-28


(BC)
  British Columbia
------------------
700     1935-08-11
703     1937-01-05
704     1941-08-31
705     1947-10-24
706     1947-09-26
707     1937-08-30
706     1964-66
710     1953
710     1968
711     1951-05-25
712     1954
716     1959-08-28
717     1958-08-20
720     1963-07-07
723     1966-07-28
725     1970
726     1972-12
726     1973-10-12
726     1973-11-19
726     1974-07-27
727     1974-12-01
727     1974-12-11
727     1974-12-31
727     1975-03-18
728     1976-03-28
728     1978-02-15
729     1977-01-09
729     1977-05-12
729     1978-07-27
730     1978-08-31
731     1979
732     1980-03-05
733     1982-04-18
733     1982-05-12
734     1980-06-29
734     1982-10-02
734     1983-03-13
736     1983-11-01
736     1984-07-05
737     1984-09-20
739     1985-07-17
739     1986
740     1986-07-06
742     1988


(MB)      Manitoba
------------------
600     1941
604     1943
608     1946-09-10
610     1938-12-13
614     1950-02
615     1943-01-06
621     1953-05-23
622     1954-02-22
623     1953-01-31
623     1953-07
623     1955-01-22
624     1957-11-22
625     1957-05-20
628     1960-12-26
634     1957-07-14
635     1960-06-07
635     1964-02-01
636     1965-01-13
637     1966-02-09
640     1968-12
640     1979-12-18
641     1971-10-25
642	1974-09-04
643     1974-06-13
644     1977-10-29
645     1978-10-01
646     1982-03-07
648     1978-03-15
648	1978-04-03
648     1978-09-28
649     1984-10-17
650	1979-05-14
650     1979-07-29
652     1980-12-09
653     1985-09-19


(NB) New Brunswick
------------------
101     1938-11
106     1938
115     1960-09-06
120     1965-12-14
121     1965-09-14
122     1970-03-14
123	1968-03-18
123     1973-12-17
125     1978-03-31
126     1977-08-19
127     1981-12-17
129     1983-11-22
129     1984-07-23

       (NF)  Newfoundland
------------------
112     1954
114     1960-07-23
126     1977-07-12
129     1987-04-21


(NS)   Nova Scotia
------------------
113     1965
119     1964-11-15
120     1964-08-11
122     1966-05-05
123     1971
124     1975-10-31
125     1978
127     1981-12-04
130     1985-05-12


(NT)           NWT
------------------
643     1975-05-16
643     1975-08-30


(NU)       Nunavut
------------------


(ON)       Ontario
------------------
404     1941-07
406     1936-06-15
409     1943-07-30
423     1946-01-24
425     1946-06
426     1946-07-08
428     1932-08-13
430     1940-03-14
431     1949-05-10
437     1950-05-10
443     1953-09
446     1954
448     1955-04-01
448	1955-09-18
452     1956-07
455     1968-08-12
457     1958-05-21
464     1959-04-10
464     1960
465     1961-03-25
466     1959-01-27
467     1961-02-07
469     1958
471     1960-11-14
472     1970-12-15
475     1960-06-28
479     1973-07
480     1965
482	1965-03-28
482     1967-04-14
484     1967-12-10
486     1970-02-20
486     1970-10-14
487     1969-03-19
487     1972-02-29
488     1971-07-21
489     1970-09-15
490     1962-10-03
490     1970-09-04
490     1971-01-23
490     1972-01-03
493     1972-10-12
495     1974-06-13
495     1975-09-04
495     1975-10-05
496     1972-06-30
496     1972-09-03
496     1975-10-29
498     1974-11-21
498     1975-04-30
499     1976-09-20
500     1975-10
500     1976-08-05
502     1978-01-10
506     1978-09-18
503     1977-05-13
503     1978-11-22
503     1979-09-20
505     1979-05
505     1979-10-01
505     1979-10-08
505     1980-07-23
505     1980-10-23
506     1980-09-01
511     1980-08-20
512     1982-03-07
513     1980-09-11
514     1981-07-12
514     1983-04-11
515     1981-05-15
516     1980-08-09
516     1981-08-05
516     1982-09-30
516     1983-09-15
516     1983-10-08
517     1983-01-21
518     1983-05-06
519     1981-10-16
520     1984-02-10
521     1984-11-29
522     1981-11-19
522     1985-12-05
523     1982-03-17
525     1982-11-28
525     1983-07-17
525     1985-05-09
527     1983-02-24
528     1984-08-06
529     1985-02-13
529     1985-09-06
530     1984-07-24
532     1985-02-01
536     1985-08
540     1987-07-08
544     1988-01-07

       (PE)           PEI
------------------
121     1983-05-26


(QC)        Quebec
------------------
211     1942-06-06
212     1937-12-08
227     1949-09-20
232     1951-10-12
233     1951-08-05
240     1955-08-10
246     1961-04-28
252     1963-10
258     1963-11-25
259	1963
270     1973-05-29
271     1975-10-18
272     1974-06-02
273     1977-01-18
274     1978-08-11
276     1980-05
279     1980-05-31
279     1980-09-25
280     1981-10-30
281     1982-02-17
284     1981-10-19
285     1984-05-25
286     1983-06-04
289     1984-10-30
291     1985-07-04
291     1986-07-27


(SK)  Saskatchewan
------------------
602     1944
606     1946-02
632     1963
632     1969-10-11
639     1968-11-25
640     1969-12-04
640     1971-11
641     1973
643     1973
647     1981-08-23
647     1983-11-24
650     1980-10-21
651     1982-11-24
654     1983-12-02
656     1983-02-06
658     1987-11-17


(YU)         Yukon
------------------


(9XX)   Temp SIN's
------------------
919     2005-08

 
I would like to thank everyone who has contributed data in an effort to 
further this project.  It has certainly helped answer some questions.  
Everyone I have spoken to, even government employees at the provincial and 
federal levels, has told me that there is absolutely no correlation 
between the SIN and birth-date or date of registration.  I think it is 
very clear now that there is a direct correlation and that a person's age 
can be fairly accurately estimated based on their SIN.  

A lot of data is still needed to finish the above tables, so if you havn't 
submitted the first 3 digits of your SIN along with province of 
registration and date of birth, please e-mail it to me.  Thanks.  

Abuse _

There are almost 4 million more active SINs than there are people in 
Canada.  Opportunities for SIN abuse are numerous and include fraudulently 
obtaining government benefits, insurance, and credit cards.  These are 
also some of the reasons why you shouldn't divulge your SIN to anyone but 
your employer and the tax-man.  

Methods for aquiring SINs include:

Assumimg the name of someone deceased who has not been recorded as dead in 
the SIN registry.  According to the SIN registry, over 300,000 dead 
Canadians are still alive.  Assuming a living persons identity.  Using a 
false birth certificate to obtain one.  Temporary SINs issued to foreign 
students and other non-permanent residents.  To make matters worse (or 
better, depending on your angle), SIN fraud investigations carried out by 
the federal Human Resources Development Canada (HRDC: the same people 
responsible for the ridiculously inaccurate SIN registry) are weak or 
non-existant.  The maximum penalty for SIN fraud is a $1,000 fine and one 
year in prison.  Though fines of a couple hundred dollars with no prison 
time are the norm for the few who are actually caught and prosecuted.  

Also _

The SIN algorithm is commonly known as the LUHN algorithm or the mod-10 
algorithm.  It also happens to be used to validate Credit Card numbers 
among other things.  

The SIN algorithm can be arranged to generate as well as validate.  

When fabricating a SIN it is probably best to start with the first three 
digits of someones SIN in the particular province who is in your age group 
then build it from that.  

The Seven Deadly Sins are Pride, Envy, Gluttony, Lust, Anger, Greed, and Sloth. 

The Canadian government uses the same authentication algorithm on many, if 
not all, of its "unique" numbers.  It is used for employer account 
numbers, trust numbers, Income Tax Filer identification (your H&R Block 
e-file rep), and the first nine digits of the Business Number (BN).  When 
there are letters in the identification number the following table is used 
to convert the letters to numbers: 

A    B    C    D    E    F    G    H    I
J    K    L    M    N    O    P    Q    R
     S    T    U    V    W    X    Y    Z
-----------------------------------------
1    2    3    4    5    6    7    8    9

*/ 


//! Return true if SIN is valid Canadian Social Insurance Number
/*!
    \param sin array of the 9 digitis in the social insurance number
    \return 0=bad SIN, 1=SIN could be valid

    The input sin number must be a 9 digit Canadian SIN in the form "123456789" for example. If
    there are any leading zeros then these must also be included in the number since the 
    string is not right justified on entry. The actual integer values are to be passed in the 
    array and not the ASCII equivalent character value. Thus for the digit 9 you need to 
    pass the value 0x09 and not 0x39
 */
int ValidCanadianSIN(int sin[]) ;


//! Return true if SIN is valid Canadian Social Insurance Number
/*!
    \param sin ASCI 9 digit SIN number
    \return 0=bad SIN, 1=SIN could be valid

    The input sin number must be a 9 digit Canadian SIN in the form "123456789" for example. If
    there are any leading zeros then these must also be included in the number since the 
    string is not right justified on entry. 
 */
int ValidCanadianSIN(char *sin) ;



