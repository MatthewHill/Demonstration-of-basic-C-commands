/*o Open the shared memory object using “{yourLinuxID}_filesharing” as the name of the object
o Memory map the shared memory object. The size should 10MB.
o access the shared memory to find out the following information:
 whether the content of a file is available on the shared memory
 size of the file
o If there is a file already in the shared memory, download the file to your local directory (i.e.,
store the store in your local directory). You may choose any name for the file. Otherwise, print
out a message indicating that there is no file on the shared memory.*/
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
int shm_fd;
const char *name = "mrhill9_filesharing";
shm_fd = shm_open(name, O_RDONLY, 0666);
//Configure the size of the shared memory object. The size should be 10MB.
ftruncate(shm_fd, SIZE);
//Memory map the shared memory object
struct filesharing_struct *ptr;
ptr = (struct filesharing_struct *) mmap(0, SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);
FILE *fp;
if(ptr->flag){
	
fp = fopen("downloadedfile","w");
if (fp == NULL){ printf("file does not exist");
return 2;}
printf("file is available on shared memory\n");
printf("File size  is : %d\n",ptr->size);
fwrite(ptr->filecontent, ptr->size,1,fp); 
fclose(fp);
}
else{printf("File does not exist in shared memory");}
shm_unlink(name);
return 0;
}
