/* ======================================================== */
/*   definitions.h		        						    */
/* ======================================================== */
#ifndef DEFENITIONS_H
#define DEFENITIONS_H

//---------------------------------------------------------------------------
//----------------------------- Includes ------------------------------------
//---------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//---------------------------------------------------------------------------
//----------------------------- General Defines -----------------------------
//---------------------------------------------------------------------------
#define PRIVATE
#define PUBLIC
#define NONE 0
#define MAX_LEN  255
#define BITCOIN_DB_FILENAME  "bitcoin_db.txt"

//---------------------------------------------------------------------------
//----------------------------- General Typedefs ----------------------------
//---------------------------------------------------------------------------
typedef enum { FALSE=0, TRUE=1 } EBoolType;
typedef enum { SUCCESS = 0, FAILURE = 1, PARSED = 2 } EExecutionStatus;
typedef void* pVoid;

//---------------------------------------------------------------------------
//----------------------------- Debugging -----------------------------------
//---------------------------------------------------------------------------

#define DEB 1
#define DEBUG if (DEB) printf("%s Line: %d\n", __func__, __LINE__);

#endif // DEFENITIONS_H

//Compiled Sources Used during Run-Time:
//======================================
//How to Create SO files:
//gcc -shared -fPIC utils.c -o libutils.so

//How to Use SO files:
//====================
//gcc main.c -L'<Dir Where the .SO file is found>' -lutils -o main.out
//l<filename> == libfilename.so
//'pwd' == current working Directory 

//for example:
//============
//gcc main.c -L'pwd' -lutils -o main.out

//For the Dynamic-linker to know where to search for the .SO file:
//================================================================
//export LD_LIBRARY_PART='pwd'