
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <string.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <fcntl.h>
#define SIZE 10485760
struct filesharing_struct {
	char flag;
	int size;
	char filecontent[SIZE];
};
int main(){
//create a new shared memory object that will be used as a storage to share the content of a single file. The name of the shared object should be “{yourLinuxID}_filesharing” ({yourLinuxID}	
int shm_fd;
const char *name = "mrhill9_filesharing";
shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
//Configure the size of the shared memory object. The size should be 10MB.
ftruncate(shm_fd, SIZE);
//Memory map the shared memory object

struct filesharing_struct *ptr;
ptr = (struct filesharing_struct *) mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);
//ask the user to type in the name of the file that will be shared (e.g., “/bin/ls”)
printf("Type in the name of the file that will be shared.");
/*The content of the specified file is read from the file system and then copied to the appropriate
location in the shared memory. The flag and size fields in the shared memory are updated accordingly*/
char filename[20];
scanf("%s",filename);
printf("file %s selected \n", filename);
FILE *fp;
fp = fopen(filename,"r");
if (fp == NULL){ printf("file does not exist");
return 2;}
fseek(fp,0, SEEK_END);
int fpSize = ftell(fp);
rewind(fp);
ptr->flag = 1;
ptr->size = sizeof(char) * fpSize;
fread(ptr->filecontent,ptr->size, 1, fp);
fclose(fp);
return 0;
}