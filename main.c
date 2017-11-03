#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>

int main(){
	DIR *dir = opendir("./");
	printf("dir: %p\n", dir);
	if(!dir){
		printf("errno: %d\n", errno);
		printf("error: %s\n", strerror(errno));
		exit(1);
	}
	struct dirent *entry;
	while(entry = readdir(dir))
		printf("%s\n", entry->d_name);

	if (closedir(dir) < 0){
		printf("errno: %d\n", errno);
		printf("error: %s\n", strerror(errno));
		exit(1);
	}

	printf("\n");
	dir = opendir("./");
	printf("dir: %p\n", dir);
	if(!dir){
		printf("errno: %d\n", errno);
		printf("error: %s\n", strerror(errno));
		exit(1);
	}
	printf("Directories:\n");
	while(entry = readdir(dir))
		if(entry->d_type==DT_DIR)
			printf("%s\n", entry->d_name);

	if (closedir(dir) < 0){
		printf("errno: %d\n", errno);
		printf("error: %s\n", strerror(errno));
		exit(1);
	}

	printf("\n");
	dir = opendir("./");
	printf("dir: %p\n", dir);
	if(!dir){
		printf("errno: %d\n", errno);
		printf("error: %s\n", strerror(errno));
		exit(1);
	}
	long total = 0;
	struct stat sb;
	off_t size;
	while(entry = readdir(dir)){
		if(entry->d_type == DT_REG){
			stat(entry->d_name, &sb);
			size = sb.st_size;
			printf("%s is %ld bytes.\n", entry->d_name, size);
			total += size;
		}
	}
	if(total >= 1073741824)
		printf("total size:%ldGB\n", total/1073741824);
	else if(total >= 1048576)
		printf("total size:%ldMB\n", total/1048576);
	else if(total >= 1024)
		printf("total size:%ldKB\n", total/1024);
	else
		printf("total size:%ldB\n", total);
	if (closedir(dir) < 0){
		printf("errno: %d\n", errno);
		printf("error: %s\n", strerror(errno));
		exit(1);
	}






	return 0;
}
