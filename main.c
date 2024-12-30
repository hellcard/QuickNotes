#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void usage(char *progname){
	printf("[GUIDE] When running the executable, enter the file name first and then the note \n");
	printf("\t[EXAMPLE] %s \"<filename>\" \"<your note>\" \n",progname);

	printf("[GUIDE] Or, if you want everything saved in a notes file, you can immediately write your note \n");
	printf("\t[EXAMPLE] %s \"<your note>\" \n",progname);

	printf("[GUIDE] If you want to read the file, you can enter the following command: \n");
	printf("\t[EXAMPLE] %s \"<file name>\" \n",progname);

	printf("[GUIDE] If you want to delete the file with notes - enter the following command: \n");
	printf("\t[EXAMPLE] %s \"<file name>\" \n",progname);
	exit(0);
}

void *checkerr_malloc(unsigned int);

void add_note(char* notename,char* note){
	FILE *f = fopen(notename,"a"); // open file in append mode

	if(f == NULL){
		perror("[ERROR] error opening file");
		exit(-1);
	}

	fwrite(note,sizeof(note[0]),strlen(note),f);
	fclose(f);

	printf("[INFO] note successfully saved in file %s\n",notename);
}

void read_notes(char *notename){
	FILE *f = fopen(notename,"r"); // open file in read mode

	if(f == NULL){
		perror("[ERROR] error reading file");
		exit(-1);
	}

	char* line;

	line = checkerr_malloc(100);

	printf("Your notes:\n\n");
	while(fgets(line,100,f)) printf("%s",line);
	printf("\n");

	fclose(f);
	free(line);

	printf("[INFO] notes successfully readed in file %s\n",notename);
}

int main(int argc, char *argv[]){
	int choice;
	char *buffer, *filename;

	buffer = checkerr_malloc(100);
	filename = checkerr_malloc(20);

	if(argc<2) usage(argv[0]);
	else if(argc==2){
		printf("Enter your choice:\n1. new note\n2. read notes from file\n3. remove file with notes\n");
		printf("Choice: "); scanf("%d",&choice);
		if(choice == 1){
			strcpy(filename,"notes.txt");
			strcpy(buffer,argv[1]);
			strcat(buffer,"\n---\n");
			add_note(filename,buffer);
		}
		else if(choice == 2){
			strcpy(filename,argv[1]);
			read_notes(filename);
		}
		else if(choice == 3){
			strcpy(filename,argv[1]);
			if(remove(filename) == 0) printf("[INFO] the %s file was successfully deleted\n",filename);
			else perror("[ERROR] error when deleting file");
		}
		else{
			perror("[ERROR] there is no such choice");
			exit(-1);
		}
	}
	else if(argc == 3){
		strcpy(filename,argv[1]);
		strcpy(buffer,argv[2]);
		strcat(buffer,"\n---\n");
		add_note(filename,buffer);
	}
	else usage(argv[0]);
	free(buffer); free(filename);
	return 0;
}

void *checkerr_malloc(unsigned int size){
	void *ptr;
	ptr  = malloc(size);
	if(ptr == NULL){
		perror("[ERROR] memory allocation error (checkerr_malloc)\n");
		exit(-1);
	}
	return ptr;
}
