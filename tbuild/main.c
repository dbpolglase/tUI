#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h> 
#include <tBasic.h>
#include <msg.h>
#include <tparser.h>
#include <tbuild.h>
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>

static void Use(char * program);

int main(int argc, char **argv) {
  int opt;
  unsigned short createInterfaz=0;
  unsigned short createPrototipe=0;
  unsigned short rewrite=0;
  char * fileXml=NULL;
    
    while((opt = getopt(argc, argv, ":iprf:")) != -1) 
    { 
        switch(opt) 
        { 
            case 'i': createInterfaz=1;
		      break;
            case 'p': createPrototipe=1;
		      break;
            case 'r': rewrite=1;
                      break; 
            case 'f': fileXml=optarg;
                break; 
            case ':': 
                printf("option needs a value\n"); 
                break; 
            case '?': 
                Use(argv[0]);
                break; 
        } 
    } 
    if (fileXml == NULL) Use(argv[0]);
    for(; optind < argc; optind++){     
        printf("extra arguments: %s\n", argv[optind]); 
        Use(argv[0]);
    }

   if (PARSER_loadXmlFile(fileXml,0) != 0)
   {
     printf("Failed parser Xml \n");
     exit (1);
   }

  BUILD_do(rewrite,createInterfaz,createPrototipe);

   return 0; 
}

static void Use(char * program)
{
   printf("Use %s -f file.xml [-r] [-i] [-p] \n",program); 
   printf(" -r rewrite interfaz and prototipe\n");
   printf(" -i create interfaz for user functions\n");
   printf(" -p create prototipe for user functions\n");
   exit(1);
}
    
