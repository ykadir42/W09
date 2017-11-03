#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>

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
	int total = 0;
	while(entry = readdir(dir)){
		if(entry->d_type == DT_REG){
			printf("%s is %d bytes.\n", entry->d_name, entry->d_reclen);
			total += entry->d_reclen;
		}
	}
	printf("total size:%dB\n", total);
	if (closedir(dir) < 0){
		printf("errno: %d\n", errno);
		printf("error: %s\n", strerror(errno));
		exit(1);
	}






	return 0;
}
