#include <stdio.h>
#include <ncurses.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

static int hayError=0;
static int printError = 1;
static int lastError=0;
static FILE * fderror;

void ERR_printError(int print,char * file)
{
   printError = print;
   fderror=stdout;
   if (print && file != NULL){
    fderror=fopen(file,"a+");
    if (fderror==NULL) fderror=stdout;
  }
}

void ERR_fatalError(int error, char * formato,...)
{
   va_list       params;

   if (printError)
   {
     if (formato == NULL)
     { 
      formato = "ERROR = NULL";
      fprintf(fderror,"ERROR %d-NULL \n",error);
     } 
     else
     {
       fprintf(fderror,"ERROR %d - ",error);
       va_start(params, formato);
       vfprintf(fderror,formato, params);
       va_end(params);
     }
   }
  endwin();
  exit(error);
}

void ERR_Error(int error, char * formato,...)
{
   va_list       params;

    if (printError)
    {
     if (formato == NULL)
     { 
      formato = "ERROR = NULL";
      fprintf(fderror,"ERROR %d-NULL \n",error);
     } 
     else
     {
       fprintf(fderror,"ERROR %d - ",error);
       va_start(params, formato);
       vfprintf(fderror,formato, params);
       va_end(params);
     }
    }  
    hayError=1;
    lastError = error;
}

int ERR_isError()
{
  return hayError;
}

int ERR_lastError()
{
 int error;
   error=lastError;
   lastError=0;
  return error;
}
