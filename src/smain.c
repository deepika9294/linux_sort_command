#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"sort.h"

int main(int argc, char *argv[]) {
	
	char *str;
	int i, choice_count;
	int keyflag = 0;
	int no_line;
	int n_files;
	keyfield kf;
	init_key(&kf);
	
	if(argc < 2) {
		printf("Enter correct Arguements\n");
		return 0;
	}
	
	if(argv[1][0] == '-')  {
		char choice;
		choice = argv[1][1];  
		
		switch(choice) {
			case 'k' : 
				kf.keys = 1;
				kf.keyno = (int)argv[1][2] - 48;
				if((strlen(argv[1]) == 5) && (argv[1][3] == '.')) {
					kf.key_advance = argv[1][4] - 48;
					
				}
				
				else if(strlen(argv[1]) == 2){
					printf("sort: invalid number at field start: invalid count\n");
					return 0;
				
				}
				
				break;
			case 'n' : 
				kf.numeric = 1;
				if(argv[1][2] == 'r') {
					kf.reverse = 1;
				}
				if(argv[1][2] == 'k') {
					kf.keys = 1;
					kf.keyno = (int)argv[1][3] - 48;
					if((strlen(argv[1]) == 6) && (argv[1][4] == '.')) {
						kf.key_advance = argv[1][5] - 48;
						
					}
					
					else if(strlen(argv[1]) == 3){
						printf("sort: invalid number at field start: invalid count\n");
						return 0;
					}
				}
				break;
			case 'b' : 
				kf.ignoreblanks = 1;
				break;
			case 'd' : 
				kf.dict = 1;
				break;
			case 'i' : 
				kf.i_nonprint = 1;
				break;
			case 'r' : 
				kf.reverse = 1;
				if(argv[1][2] == 'n') {
					kf.numeric = 1;
				}
				break;
			case 'm' : 
				kf.merge = 1;
				break;
			case 't' : 
				kf.t_sepa = 1;
				if(strlen(argv[1]) == 4) {
					kf.t_value = argv[1][2];
					kf.keyno = argv[1][3] - 48;
				}
				
				else {
					printf("Enter correct choice, by refering the help section.\n");
					return 0;
				}
				break;
			case 'u' : 
				kf.unique = 1;
				break;
			case 'f' :
				kf.ignorecase = 1;
				break;
			case '-' :
				if(argv[1][2] == 'h'){
					help();
					return 0;
				}
				else {
					printf("No Choice entered.\n");
					return 0;
				}
				break;
			default : printf("Enter some correct keys, for any querey check help section by using '-h' command\n");
			
		}
			
		
	}
	else {
		printf("Entered wrong choice.\nRefer help section\nUse --h command\n");
		return 0;
	}
	
	if(argc == 2) {
		//read from user and write in file, if no file is mentioned
		
		char temp_str[1000];
		
		FILE *fi;
		str = (char *)malloc(sizeof(char) * 50);
		strcpy(str, "input.txt");
		
		fi = fopen(str, "w+");
		if(fi == NULL) {
			printf("Error in opening file in the starting");
			return 0;
		}
		
		while(scanf("%[^\n]%*c", temp_str) != -1) {
			fprintf(fi, "%s", temp_str);
			fprintf(fi, "%c",'\n');
		}
		fclose(fi);
	}
	else
		str = argv[2];
	
	
	if (kf.numeric == 1 || kf.keys == 1 || kf.ignoreblanks == 1 || kf.dict == 1 || kf.i_nonprint == 1 || kf.reverse == 1 ||kf.ignorecase == 1) {
		//getting total lines
		no_line = lines_count(str);
		//calculating total runs
		n_files = runs(str, no_line);
		//slpiting the file, sorting it and merging it
		split_file(str, n_files, kf, no_line);
		//initialising heap
		heapInit(&h);
		//merging the files
		mergefiles(str, n_files, kf, &h);
	}
	
	
	else if (kf.unique == 1) {
		//getting total lines
		no_line = lines_count(str);
		//calculating total runs
		n_files = runs(str, no_line);
		//slpiting the file, sorting it and merging it
		split_file(str, n_files, kf, no_line);
		//initialising heap
		heapInit(&h);
		//merging the files
		mergefiles(str, n_files, kf, &h);
		
		FILE *f;
		f = fopen("output.txt", "r+");
		if(f == NULL) {
			printf("File not opened");
			return 0;
		}
		print_unique_file(f);
		
	}
	
	else if(kf.t_sepa == 1) {
		//getting total lines
		no_line = lines_count(str);
		//calculating total runs
		n_files = runs(str, no_line);
		//slpiting the file, sorting it and merging it
		split_file(str, n_files, kf, no_line);
		//initialising heap
		heapInit(&h);
		//merging the files
		mergefiles(str, n_files, kf, &h);
	
	}
	
	else if (kf.merge == 1 ) {
		if(argc < 4) {
			printf("Enter correct arguements, otherwise check help section.");
			return 0;
		}
		
		str = argv[2];
		heapInit(&h);
		//merging the files
		merge_two_files(str, argv[3], n_files, kf, &h);
	}
	return 0;
}
