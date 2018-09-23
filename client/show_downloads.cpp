/********************************************************************************/
/*             Name: Priyendu Mori                                              */
/*          Roll no: 2018201103                                                 */
/********************************************************************************/

#include "header.h"
#include "clientglobal.h"

/*
    displays downloads done by user
    S means downloaded
    D means downloading
*/
void show_down()
{
    for (auto i : downloads)
    {
        char status;
        if (i.second == 2)
            status = 'S';
        if (i.second == 1)
            status = 'D';
        cout << status << " " << i.first << endl;
    }
}