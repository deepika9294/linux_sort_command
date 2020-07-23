#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include"sort.h"
/*
*initialising the options, like if no key is entered by default key '1' will be considered
*/
void init_key(keyfield *kf) {
	kf->reverse = 0;
	kf->keys = 0;
	kf->keyno = 1;
	kf->key_advance  = 0; 
	kf->unique = 0;
	kf->numeric = 0;
	kf->ignoreblanks = 0;
	kf->ignorecase = 0;
	kf->merge = 0;
	kf->i_nonprint = 0;
	kf->t_sepa = 0;
	kf->t_value = ' ';
	kf->dict = 0;
}
/*
*This file simply returns the number of lines in the file
*/
int lines_count(char *file1) {
	char c;
	int count = 0;
	int i = 0;

	FILE *fp;
	fp = fopen(file1, "r+");

	if(fp == NULL) {
		printf("Error in openong file");
		return 0;
	}

	while(fscanf(fp,"%c", &c) != EOF) { 
		if(c == '\n')
			count++;

		i++;
	}
	fclose(fp);
	return count;

}
/*
*Here each line of a file is read and stored into an array, character by character
*and allocation of variables are done to use it while merge sorting
*/
void readline(FILE *fp, int no_line) {
	int j = 0;
	int i;
	
	l = (Line *)malloc(sizeof(Line) * (no_line)); 
	b = (char **)malloc(sizeof(char *) * (no_line));
	for(i = 0; i < no_line; i++) {
		b[i] = (char *)malloc(sizeof(char) * 1000);
	}
	d = (char **)malloc(sizeof(char *) * (no_line));
	for(i = 0; i < no_line; i++) {
		d[i] = (char *)malloc(sizeof(char) * 1000);
	}
	for(i = 0; i < no_line; i++) {

		l[i].data = (char *)malloc(sizeof(char) * 1000);
		fscanf(fp, "%c", &l[i].data[j]);
		while(l[i].data[j] != '\n') {
			j++;
			fscanf(fp, "%c", &l[i].data[j]);

		}
		l[i].data[j] = '\0';
		j = 0;
	}
	return;
}

void print(int no_line) {
	for(int i = 0; i < no_line; i++) {
		printf("%s\n", l[i].data);

	}
}

void print_file(int no_line, FILE *f1) {
	for(int i = 0; i < no_line; i++) {
		fprintf(f1, "%s\n", l[i].data);

	}	
}

void print_reverse(int no_line, FILE *f1) {
	for(int i = no_line - 1; i >= 0; i--) {
		fprintf(f1, "%s\n", l[i].data);

	}

}
void print_word(int no_line) {

	for(int i = 0; i < no_line; i++) {
		printf("%s\n", l[i].word);

	}
}

/*
*this function stores the data i.e lines according to the key i.e. column
*here the temporary version of line gets copied to l[i].word according to the spaces, comma, etc
*/

void store(int no_lines, keyfield kf) {
	//have to store data in l[i].word;
	int j = 0 , k = 0, flag = 0;
	int col = 1, len;
	char str[1000];
	int i = 0;

	if(kf.keyno == 1 && kf.t_sepa == 0){
		for(i = 0; i < no_lines; i++) {
			len = strlen(l[i].data);
			while(j < len ) {
				if(l[i].data[j] == ' ') {
					str[k] = l[i].data[j];
					k++;
					j++;

				}
				if(l[i].data[j] != ' ')
					break;
			}
			while(j < len) {
				str[k] = l[i].data[j];
				k++;
				j++;
				if(l[i].data[j] == '\n') {
					break;
				}
			}
			str[k] = '\0';
			j = 0;
			k = 0;
			l[i].word = (char *)malloc(sizeof(char) * 1000);  //allocating memory for word
			strcpy(l[i].word, str);
			strcpy(str, "");
		}
	}

	// for keys greater than 1
	else if(kf.t_sepa == 0) {
		
		for(i = 0; i < no_lines; i++) {
			len = strlen(l[i].data);
			if(l[i].data[0] == ' ')
			{
				col = 0;
			}
			while(j < len - 1) {
				if(l[i].data[j] == ' ' && l[i].data[j+1] != ' ' && flag == 0) {
					col++;
					
				}
				if(col == kf.keyno) {
						flag = 1;
						break;
				}
				else
					j++;
			}
			if(col < kf.keyno) {
				printf("Enter correct KEY \n");
				exit(0);
			}
			j++;
			while(l[i].data[j] != '\0' && flag == 1 ) {
				str[k] =  l[i].data[j];
				k++;
				j++;
			}
			if(flag == 1)
			{
				str[k] = '\0';
				j = 0;
				k = 0;
				col = 1;
				flag = 0;
				l[i].word = (char *)malloc(sizeof(char) * 1000);
				strcpy(l[i].word, str);
				strcpy(str, "");
			}
		}
	}
	//If separator function is used
	else if(kf.t_sepa == 1){
		for(i = 0; i < no_lines; i++) {
			len = strlen(l[i].data);
			
			while(j < len - 1) {
				if(l[i].data[j] == kf.t_value && flag == 0) {
					col++;
					
				}
				if(col == kf.keyno) {
						flag = 1;
						break;
				}
				else
					j++;
			}
			if(col < kf.keyno) {
				printf("Enter correct KEY ");
				exit(0);
			}
			while(l[i].data[j] != '\0' && flag == 1 ) {
				str[k] =  l[i].data[j];
				k++;
				j++;
			}
			if(flag == 1)
			{
				str[k] = '\0';
				j = 0;
				k = 0;
				col = 1;
				flag = 0;
				l[i].word = (char *)malloc(sizeof(char) * 1000);
				strcpy(l[i].word, str);
				strcpy(str, ""); //making a string empty
			}
		}
	}
	
	i = 0;
	j = 0;
	k = 0;
	/*
	*If key enterd is with some extra specifications
	*/
	if(kf.key_advance != 0) {
		
		for(i = 0; i < no_lines; i++) {
			j = kf.key_advance - 1;
			if(j > strlen(l[i].word)) {
				break;
			}
			while(j < strlen(l[i].word)) {
				str[k] = l[i].word[j];
				k++;
				j++;
			
			}
			
			str[k] = '\0';
			j = 0;
			k = 0;
			strcpy(l[i].word, str);
			strcpy(str, ""); 
			}
	}
	
	
}

//-----------------------------------------------------------------------------------------------------------------
void merge_sort(int low, int high, keyfield kf){
	
	int m;
	if(low < high) {
		m = (low + high) / 2;
		merge_sort(low, m, kf);
		merge_sort(m + 1, high, kf);
		merge_array(low, m, high, kf);
	}
	else { 
		return;
	}   
}
void merge_array(int low, int m, int high, keyfield kf){ 

	int i = low, j = m + 1, k = 0;
	while(i <= m && j <= high) {
		if(mycmp(l[i].word, l[j].word, kf) == 0) {
			strcpy(b[k],l[j].word);
			strcpy(d[k], l[j].data);
			k++;
		    	j++;
		}
		else {
			strcpy(b[k],l[i].word);
			strcpy(d[k], l[i].data);
			k++; 
			i++;
		}
	}
	
	// add elements in first array 
	while(i <= m) {
		strcpy(b[k],l[i].word);
		strcpy(d[k], l[i].data);
		k++;
		i++;
	}

	// add elements in second array
	while(j <= high) {
		strcpy(b[k],l[j].word);
		strcpy(d[k], l[j].data);
		k++; j++;
	}
	
	// copy array to original
	for(i = low; i <= high; i++) {
		strcpy(l[i].word,b[i-low]);
		strcpy(l[i].data, d[i - low]);
	}
	return;
} 
//---------------------------------------------------------------------------------------------------------------------

/*
*This function is like the body of the program
*here all the options are handled
*and according the files get sorted
*/

int mycmp(char *str1, char *str2, keyfield kf) {
	// numbers come front, lowercase, uppercase
	//numbers from 48-57
	//big alpha from 65 to 90
	//small alpha from 97 to 122
	// non printable from 0 to 31 , 127, 
	// use as strcmp only for numbers 
	int str1_case, str2_case;
	float num1, num2;
	keyfield kf1 = kf;
	char a[1000], a1[1000];
	int i = 0, j = 0;
	if(kf.numeric) {
		num1 = atof(str1);
		num2 = atof(str2);
		if(num1 <= num2) {
			return 1;
		}
		else
			return 0;
	}
	else if(kf.keys == 1 || kf.merge == 1 || kf.reverse == 1 || kf.unique == 1 || kf.t_sepa == 1) {
		if(strcmp(str1, str2) <= 0)
			return 1;
		else
			return 0;
	}
	
	else if(kf.dict) {
		j = 0;
		i = 0;
		while(str1[i] != '\0') {
			if((str1[i] >= 65 && str1[i] <= 90) || (str1[i] >= 97 && str1[i] <= 122) || (str1[i] >= 48 && str1[i] <= 57) || str1[i] == 32) {
				a[j] = str1[i];
				i++;
				j++;
			
			}
			else 
				i++;
				
		}
		a[j] = '\0';
		j = 0;
		i = 0;
		
		while(str2[i] != '\0') {
			if((str2[i] >= 65 && str2[i] <= 90) || (str2[i] >= 97 && str2[i] <= 122) || (str2[i] >= 48 && str2[i] <= 57) || str2[i] == 32) {
				a1[j] = str2[i];
				i++;
				j++;
			
			}
			else 
				i++;
				
		}
		a1[j] = '\0';
	
		if(strcmp(a, a1) <= 0)
			return 1;
		else
			return 0;
	}
	
	else if(kf.ignoreblanks) {
		while(str1[i] == ' ') {
			i++;
		}
		while(str1[i] != ' ' && str1[i] != '\0') {
			a[j] = str1[i];
			i++;
			j++;
		}
		i = 0;
		j = 0;
		while(str2[i] == ' ') {
			i++;
		}
		while(str2[i] != ' ' && str2[i] != '\0') {
			a1[j] = str2[i];
			i++;
			j++;
		}
		if(strcmp(a, a1) <= 0)
			return 1;
		else
			return 0;
		
		
	}
	else if(kf.i_nonprint) {
		j = 0;
		i = 0;
		while(str1[i] != '\0') {
			if((str1[i] >= 0 && str1[i] <= 31) || str1[i] == 127) {
				
				i++;
			}
			else {
				a[j] = str1[i];
				i++;
				j++;
			
			}
				
		}
		a[j] = '\0';
		j = 0;
		i = 0;
		
		while(str2[i] != '\0') {
			if((str2[i] >= 0 && str2[i] <= 31) || str2[i] == 127) {
				
				i++;
			}
			else {
				a1[j] = str2[i];
				i++;
				j++;
			}
			
				
		}
		a1[j] = '\0';
	
		if(strcmp(a, a1) <= 0)
			return 1;
		else
			return 0;
	}
	
	else if(kf.ignorecase) {
	
		while(str1[i] != '\0') {
			if(str1[i] >= 'a' && str1[i] <= 'z' && i == 0){
				a[j] = str1[i] - 32;
				j++;
				i++;
			}
			else {
				a[j] = str1[i];
				j++;
				i++;
			}
		}
		a[j] = '\0';
		i = 0;
		j = 0;
		while(str2[i] != '\0') {
			if(str2[i] >= 'a' && str2[i] <= 'z' && i == 0){
				a1[j] = str2[i] - 32;
				j++;
				i++;
			}
			else {
				a1[j] = str2[i];
				j++;
				i++;
			}
		}
		a1[j] = '\0';
		if(strcmp(a, a1) <= 0)
			return 1;
		else
			return 0;
	}
}

/*
*This function gets called when user chooses unique option
*removes the duplicates and write the output in "output_unique.txt"
*/
void print_unique_file(FILE *f) {
	char s1[1000], s2[1000];
	int i = 0, j = 0;
	FILE *fu;
	fu = fopen("output_unique.txt", "w+");
	if(fu == NULL){
		printf("file not opened");
		return;
	}
	fscanf(f, "%c", &s1[i]);
	while(!feof(f) && s1[i] != '\n') {
		i++;
		fscanf(f, "%c", &s1[i]);
	}
	s1[i] = '\0';
	
	while(!feof(f)){
		i = 0;
		fscanf(f, "%c", &s2[i]);
		while(!feof(f) && s2[i] != '\n') {
			i++;
			fscanf(f, "%c", &s2[i]);
		}
		s2[i] = '\0';
		if(!feof(f)){
			if(strcmp(s1, s2) != 0){
				fprintf(fu, "%s", s1);
				fprintf(fu, "%c", '\n');
				printf("%s\n", s1);
				strcpy(s1,s2);
				strcpy(s2,"");
			}
			else {
				
				strcpy(s1,s2);
				strcpy(s2,"");
			}
		}
	}
	printf("%s\n", s1);
	fprintf(fu, "%s", s1);
	fprintf(fu, "%c", '\n');
	fclose(fu);
	fclose(f);
}


//External sorting functions start
int runs(char *filename, int no_line) {
	 //based on lines;
	int run;
	int mod_of_run;
	mod_of_run = no_line % run_size;
	run = no_line / run_size;
	if(mod_of_run == 0) {
		return run;
	}
	return run + 1;
}
//**********************************************************************************************************************
/*
*Main function:
*here, spliting of files is done on the basis of lines,
*then individual splited files are sorted by merge sort function
*and output is written on another files
*input split files are removed 
*/

void split_file(char *filename, int run, keyfield kf, int no_line) {
	FILE **f;  // input split files
	FILE **f1; //output split merged files
	FILE *fp;  // input file pointer
	char **filen1; // names of input split files
	char **filen2;
	int i;
	int run_size_last = no_line % run_size;
	
	if(run_size_last == 0)
		run_size_last = run_size;
	
	f = (FILE **)malloc(sizeof(FILE *) * run);
	
	f1 = (FILE **)malloc(sizeof(FILE *) * run);
	
	filen1 = (char **)malloc(sizeof(char *) * run);
	filen2 = (char **)malloc(sizeof(char *) * run);
	
	//naming of input split files
	for(i = 0; i < run; i++) {
		filen1[i] = (char *)malloc(sizeof(char) * 20);
		sprintf(filen1[i], "%d", i + 1); 
  
	}
	//naming of output split files
	for(i = 0; i < run; i++) {
		filen2[i] = (char *)malloc(sizeof(char) * 20);
		sprintf(filen2[i], "%f", (i + .1)); 
  	}
	// opening the main input file
	fp = fopen(filename, "r+");
	if(fp == NULL) {
		printf("Error in opening file");
		return;
	}
	
	// reading and writing
	for(i = 0; i < run - 1; i++) {
		f[i] = (FILE *)malloc(sizeof(FILE));
		f[i] = fopen(filen1[i], "w+");
		if(f[i] == NULL) {
			printf("Error in opening file");
			return;
		}
		read_write(fp, f[i], run_size);
		fclose(f[i]);
	}
	
	f[i] = (FILE *)malloc(sizeof(FILE));
	f[i] = fopen(filen1[i], "w+");
	if(f[i] == NULL) {
		printf("Error in opening file");
		return;
	}
	read_write(fp, f[i], run_size_last);
	fclose(f[i]);
	fclose(fp);
	
	for(i = 0; i < run - 1; i++) {
		f1[i] = (FILE *)malloc(sizeof(FILE));
		f1[i] = fopen(filen2[i], "w+");
		if(f1[i] == NULL) {
			printf("Error in opening file");
			return;
		}
		f[i] = fopen(filen1[i], "r+");
		if(f[i] == NULL) {
			printf("Error in opening file");
			return;
		}
		readline(f[i], run_size);
		store(run_size, kf);
		
		merge_sort(0, run_size - 1, kf);
		
		if(kf.reverse == 1){
			print_reverse(run_size, f1[i]);
		}
		else{
			print_file(run_size, f1[i]);
		}
		//added extra part
		for(int j = 0; j < run_size ; j++) {
			free(b[j]);
			free(d[j]);
			free(l[j].data);
			free(l[j].word);
			
		}
		free(l);
		free(b);
		free(d);
		
		fclose(f1[i]);
		fclose(f[i]);
		
		
	}
	//for last file
	f1[i] = (FILE *)malloc(sizeof(FILE));
	f1[i] = fopen(filen2[i], "w+");
	if(f1[i] == NULL) {
		printf("Error in opening file");
		return;
	}
	f[i] = fopen(filen1[i], "r+");
	if(f[i] == NULL) {
		printf("Error in opening file");
		return;
	}
	readline(f[i], run_size_last);
	store(run_size_last, kf);
	merge_sort(0, run_size_last - 1, kf);
	if(kf.reverse == 1){
		print_reverse(run_size_last, f1[i]);
	}
	else{
		print_file(run_size_last, f1[i]);
	}
	
	
	free(l);
	free(b);
	free(d);
	fclose(f1[i]);
	fclose(f[i]);
		
	//removing input files	
	for(i = 0; i < run; i++ ){
		if (remove(filen1[i]) != 0) 
      			printf("Unable to delete the file"); 
   		
	}
	
       //freeing filenames
	for(i = 0; i < run; i++) {
		free(filen1[i]);
		free(filen2[i]);
		
	}
	free(filen1);
	free(filen2);	
		
}

//******************************************************************************************************************************

/*
*Here it reads from the main file and writes in input split files
*/

void read_write(FILE *fp, FILE *f, int no_line) {
	char c;
	int i;
	
	for(int i = 0; i < no_line; i++) {
		fscanf(fp, "%c", &c);
		while(c != '\n') {
			//j++;
			fprintf(f,"%c",c);
			fscanf(fp, "%c", &c);
		}
		fprintf(f,"%c",c);
	}
	return;	
}

//************************************************************************************************************************//
//--------------------------------HEAP------------------------------------------------------------------------------------//
//***********************************************************************************************************************//

//heap initialisation
void heapInit(heap *h){
	int i;
	h->n = 0;
	h->store = (char **)malloc(sizeof(char *) * run_size);          
	for(i = 0; i < run_size; i++) {
		h->store[i] = (char *)malloc(sizeof(char) * 1000);
	}
	
	h->main_store = (char **)malloc(sizeof(char *) * run_size);          
	for(i = 0; i < run_size; i++) {
		h->main_store[i] = (char *)malloc(sizeof(char) * 1000);
	}
	
	
	h->file_no = (int *)malloc(sizeof(int ) * run_size);
}

//swaping strings
void swap(char **store, int x, int y) {
	char temp[1000];
	strcpy(temp, store[x]);
	strcpy(store[x], store[y]);
	strcpy(store[y], temp);	
}
//swaping filenumber
void swapf(int *a, int x, int y) {
	int temp;
	temp = a[x];
	a[x] = a[y];
	a[y] = temp;
	
}

void heapInsert(heap *h, char *str, keyfield kf, int num, char *str_main){
	int c, p;
	c = h->n;
	strcpy(h->store[c], str);
	strcpy(h->main_store[c], str_main);
	h->file_no[c] = num;
	p = (c - 1) / 2;
	while(c) {
		if(mycmp(h->store[c], h->store[p], kf) == 1) {
			swap(h->store, c, p);
			swap(h->main_store, c, p);
			swapf(h->file_no, c, p);
			c = p;
			p = (c - 1) / 2;
		}
		else
			break;
	}
	h->n++;
}
#define MIN(a, b) (mycmp((a),(b),kf) ? (a) : (b))
int findsmallest(char **p, int a, int b, int c, keyfield kf) {
	char x[1000];
	char y[1000];
	strcpy(x, MIN(p[a], p[b]));
	strcpy(y, MIN(x, p[c]));
	if(strcmp(y, p[a]) == 0)
		return a;
	if(strcmp(y, p[b]) == 0)
		return b;
	if(strcmp(y, p[c]) == 0)
		return c;
	return -1;
}
blah heapRemove(heap *h, keyfield kf){
	int p, c1, c2, smallest;
	blah temp;
	char s[1000];
	char *t_s;
	strcpy(s, h->main_store[0]);
	temp.filenumber = h->file_no[0];
	strcpy(h->store[0], h->store[h->n - 1]);
	strcpy(h->main_store[0], h->main_store[h->n -1]);
	h->file_no[0] = h->file_no[h->n - 1];
	(h->n)--;
	p = 0;
	c1 = 2 * p + 1;
	c2 = 2 * p + 2;
	while(c1 < h->n) {
		smallest = findsmallest(h->store, p, c1, c2,kf);
		if(smallest == p)
			break;
		swap(h->store, p, smallest);
		swap(h->main_store, p, smallest);
		swapf(h->file_no , p, smallest);
		p = smallest;
		c1 = 2 * p + 1;
		c2 = 2 * p + 2;
	}
	temp.s = (char *)malloc(sizeof(strlen(s) + 1));
	temp.s = s;
	return temp;
}


int heapEmpty(heap *h){
	return h->n == 0;
}
int heapFull(heap *h){
	return h->n == run_size;
}

void M_heapInsert(heap *h, char *str, keyfield kf, int num, char *str_main){
	int c, p;
	c = h->n;
	strcpy(h->store[c], str);
	strcpy(h->main_store[c], str_main);
	h->file_no[c] = num;
	p = (c - 1) / 2;
	while(c) {
		//if(h->store[c] < h->store[p]) {
		if(mycmp(h->store[c], h->store[p], kf) == 0) {
			swap(h->store, c, p);
			swap(h->main_store, c, p);
			swapf(h->file_no, c, p);
			c = p;
			p = (c - 1) / 2;
		}
		else
			break;
	}
	h->n++;
}
#define MAX(a, b) (mycmp((a),(b),kf) ? (b) : (a))
int findlargest(char **p, int a, int b, int c, keyfield kf) {
	char x[1000];
	char y[1000];
	strcpy(x, MAX(p[a], p[b]));
	strcpy(y, MAX(x, p[c]));
	if(strcmp(y, p[a]) == 0)
		return a;
	if(strcmp(y, p[b]) == 0)
		return b;
	if(strcmp(y, p[c]) == 0)
		return c;
	return -1;
}
/*
*Here this return a structure which contains a string and an integer(filenumber))
*/

blah M_heapRemove(heap *h, keyfield kf){
	int p, c1, c2, largest;
	blah temp;
	char s[1000];
	char *t_s;
	strcpy(s, h->main_store[0]);
	temp.filenumber = h->file_no[0];
	strcpy(h->store[0], h->store[h->n - 1]);
	strcpy(h->main_store[0], h->main_store[h->n -1]);
	h->file_no[0] = h->file_no[h->n - 1];
	(h->n)--;
	p = 0;
	c1 = 2 * p + 1;
	c2 = 2 * p + 2;
	while(c1 < h->n) {
		largest = findlargest(h->store, p, c1, c2,kf);
		if(largest == p)
			break;
		swap(h->store, p, largest);
		swap(h->main_store, p, largest);
		swapf(h->file_no , p, largest);
		p = largest;
		c1 = 2 * p + 1;
		c2 = 2 * p + 2;
	}
	temp.s = (char *)malloc(sizeof(strlen(s) + 1));
	temp.s = s;
	return temp;
}

//**************************************************************************************************************************
//*****************************************************************************************************************************


/*
*Here the input sorted files are opened and data is read line by line
*then remove the minimum element
*and insert the element from the file where it is removed
*/

void mergefiles(char *filename, int run, keyfield kf, heap *h){
	FILE **f;  // input split sorted files
	FILE *fp;  // output file pointer
	char **filen1; // names of input split files
	int i, count = 0;
	int j = 0;
	char ch;
	int file_n;
	char temp_str[1000];
	blah rec;
	
	f = (FILE **)malloc(sizeof(FILE *) * run);  //creating input sorted files pointer
	
	filen1 = (char **)malloc(sizeof(char *) * run); //creating their names
	
	//naming of input split files
	for(i = 0; i < run; i++) {
		filen1[i] = (char *)malloc(sizeof(char) * 20);
		sprintf(filen1[i], "%f", i + .1); 
  
	}
	
	// opening the main input file
	fp = fopen("output.txt", "w+");
	if(fp == NULL) {
		printf("Error in opening file");
		return;
	}
	
	//open a input sorted files.
	for(i = 0; i < run; i++) {
		f[i] = (FILE *)malloc(sizeof(FILE));
		f[i] = fopen(filen1[i], "r+");
		if(f[i] == NULL) {
			printf("Error in opening file");
			return;
		}
	}
	// read first lines from the file
	for(i = 0; i < run; i++) {
			l = (Line *)malloc(sizeof(Line));
			l[0].data = (char *)malloc(sizeof(char)*1000);
			
			j = 0;
			fscanf(f[i], "%c", &l[0].data[j]);
			while(l[0].data[j] != '\n'){
				
				j++;
				fscanf(f[i], "%c", &l[0].data[j]);
			}
			l[0].data[j] = '\0';
			store(1, kf);
			if(kf.reverse == 1)
				M_heapInsert(h, l[0].word, kf, i, l[0].data);
			else
				heapInsert(h, l[0].word, kf, i, l[0].data);
			
			free(l);
			
	}
	//removing the minimum element
	//and now n-way merging starts
	while(count < run){
		//Removing an element
		if(!heapEmpty(h)){
			if(kf.reverse == 1)
				rec = M_heapRemove(h, kf);
			else
				rec = heapRemove(h, kf);	
			
			strcpy(temp_str, rec.s);
			fprintf(fp, "%s", temp_str);
			fprintf(fp, "%c", '\n');
			if(kf.unique == 0)
				printf("%s\n", temp_str);
			
		}
		else
			return;
			
		if (!(feof(f[rec.filenumber]))) {
		
			l = (Line *)malloc(sizeof(Line));
			l[0].data = (char *)malloc(sizeof(char)*1000);
			j = 0;
			
			fscanf(f[rec.filenumber], "%c", &l[0].data[j]);
			if(!(feof(f[rec.filenumber]))) {
				while(l[0].data[j] != '\n'){
					j++;
					fscanf(f[rec.filenumber], "%c", &l[0].data[j]);
				}
				l[0].data[j] = '\0';
				store(1, kf);
				if(kf.reverse == 1)
					M_heapInsert(h, l[0].word, kf, rec.filenumber, l[0].data);
				else
					heapInsert(h, l[0].word, kf, rec.filenumber, l[0].data);
				free(l[0].word);
				free(l[0].data);
				free(l);
			
			}
			else {
				count++;
			}
		}
	}
	fclose(fp);
	//removing the files
	for(i = 0; i < run; i++ ){
		if (remove(filen1[i]) != 0) 
      			printf("Unable to delete the file"); 
   		
	}
}
/*
*This function is used when merge option is to be dealt
*here two files names are passed as an arguement,
*By using heap, did the, merging
*/
void merge_two_files(char *file1, char *file2, int run, keyfield kf, heap *h){
	FILE *f[2];  // input split sorted files
	FILE *fp;  // output file pointer
	int i, count = 0;
	int j = 0;
	char ch;
	int file_n;
	char temp_str[1000];
	blah rec;
	
	// opening the main input file
	fp = fopen("output.txt", "w+");
	if(fp == NULL) {
		printf("Error in opening file");
		return;
	}
	f[0] = fopen(file1, "r+");
	if(f[0] == NULL) {
		printf("Error in opening file");
		return;
	}
	f[1] = fopen(file2, "r+");
	if(f[1] == NULL) {
		printf("Error in opening file");
		return;
	}
	
	for(i = 0; i < 2; i++) {
			l = (Line *)malloc(sizeof(Line));
			l[0].data = (char *)malloc(sizeof(char)*1000);
			j = 0;
			fscanf(f[i], "%c", &l[0].data[j]);
			while(l[0].data[j] != '\n'){
				
				j++;
				fscanf(f[i], "%c", &l[0].data[j]);
			}
			l[0].data[j] = '\0';
			store(1, kf);
			heapInsert(h, l[0].word, kf, i, l[0].data);
			
			free(l);
			
	}
	
	while(count < 2){
		//Removing an element
		if(!heapEmpty(h)){
			rec = heapRemove(h, kf);
			strcpy(temp_str, rec.s);
			
			fprintf(fp, "%s", temp_str);
			printf("%s\n", temp_str);
			fprintf(fp, "%c", '\n');
		}
		else
			return;
			
		if (!(feof(f[rec.filenumber]))) {
			l = (Line *)malloc(sizeof(Line));
			l[0].data = (char *)malloc(sizeof(char) * 1000);
			j = 0;
			
			fscanf(f[rec.filenumber], "%c", &l[0].data[j]);
			if(!(feof(f[rec.filenumber]))) {
				while(l[0].data[j] != '\n'){
					j++;
					fscanf(f[rec.filenumber], "%c", &l[0].data[j]);
				}
				l[0].data[j] = '\0';
				store(1, kf);
				heapInsert(h, l[0].word, kf, rec.filenumber, l[0].data);
				free(l);
			
			}
			else {
				count++;
			}
		}
	}
}
//help section which tells about different features.
void help() {
	printf("Usage: ./sort [OPTION] [FILE] \n");
	printf("If no file is mention then, user is supposed to give inputs:\n");
	printf("\t\tUsage: ./sort [OPTION] (Start giving inputs) \n");
	printf("If merging two files then: ./sort [OPTION] [FILE1] [FILE2]\n\n");
	printf("  Ordering Options:\n");
	printf("--------------------\n");
	printf("\t -b, --ignore leading blanks\tIgnore leading blanks\n");
	printf("\t -i, --ignore-nonprinting\tConsider only printable characters\n");
	printf("\t -n, --numeric sort\t\tCompare according to string numeric value\n");
	printf("\t -f, --ignore case\t\tFold lower case to upper case\n");
	printf("\t -r, --reverse\t\t\tReverse the result of comparisions\n");
	printf("\t -b, --dictionary-order\t\tConsider only blanks and alphanumeric characters\n\n");
	
	printf("  Other Options: \n");
	printf("------------------\n");
	printf("\t -t, --field-separator=SEP\t\tuse SEP instead of non-blank to blank transi-tion\n");
        printf("\t\t For example, if you want to consider comma separator file, and sort column 2, so use -t,2\n");      
	printf("\t -k, --key=KEYDEF\t\tSort via a key. KEYDEF gives location\n");
	printf("\t -m, --merge\t\t\tMerge already sorted files; Do not sort.\n");
	printf("\t -u, --unique\t\t\tRemove duplicates from result\n");	
	printf("\t -h, --help\t\t\tPrint this usage and exit\n");

	return;
}

