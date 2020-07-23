/*
*********************************************************
Linux SORT COMMAND with external sorting.
MIS : 111803117
NAME : Deepika Goyal

*********************************************************
*/


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define run_size 5

typedef struct Line {
	char *data, *word;
}Line;

typedef struct heap {
	char **store;
	char **main_store;
	int n;
	int *file_no;

}heap;
//for returning string and filenumber from heap
typedef struct blah {
	char *s;
	int filenumber;
}blah;

heap h;
char heap_str[256];
Line *l;
char **b;
char **d;

//Structure to hold differnt options entered by user.
typedef struct keyfield {
	int reverse;
	int i_nonprint;
	int keys;
	int keyno;
	int key_advance;
	int dict;
	int t_sepa;
	char t_value;
	int unique;
	int numeric;
	int ignoreblanks;
	int ignorecase;
	int merge;	
}keyfield;
//Genereal functions
void merge_sort(int l, int r, keyfield kf);
void merge_array(int l, int m, int r, keyfield kf);
void readline(FILE *fp, int no_lines);
void init_line(Line *l);
int lines_count(char *filename);
void print(int);
void store(int, keyfield);
void print_word(int no_line);
int mycmp(char *str1, char *str2, keyfield kf);
void init_key(keyfield *kf);
void print_reverse(int no_line, FILE *f1);
void print_unique(int no_line);
void print_unique_file(FILE *f);
//external sorting
void print_file(int no_line, FILE *f1);
int runs(char *filename, int no_line);
void split_file(char *filename, int run, keyfield kf, int);
void read_write(FILE *f, FILE *, int);
//heap
void heapInit(heap *h);
void heapInsert(heap *h, char *, keyfield, int, char *);
blah heapRemove(heap *h, keyfield);
int heapEmpty(heap *h);
int heapFull(heap *h);
void swap(char **store, int x, int y);
void swapf(int *a, int x, int y);
int findsmallest(char **p, int a, int b, int c, keyfield);
void mergefiles(char *filename, int run, keyfield kf, heap *h);
void merge_two_files(char *file1, char *file2, int run, keyfield kf, heap *h);
void M_heapInsert(heap *h, char *str, keyfield kf, int num, char *str_main);
int findlargest(char **p, int a, int b, int c, keyfield kf);
blah M_heapRemove(heap *h, keyfield kf);
//help
void help();
