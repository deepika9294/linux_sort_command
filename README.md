*****************************************************************************
Name : Deepika Goyal
Project : Linux Sort-Command (with external sorting)
---------DSA MINI PROJECT-------------------
******************************************************************************

In this command we can run many options to sort a particular file, methods are given below:


Usage: ./sort [OPTION] [FILE] 
If no file is mention then, user is supposed to give inputs:
		Usage: ./sort [OPTION] (Start giving inputs) 
If merging two files then: ./sort [OPTION] [FILE1] [FILE2]

     OPTIONS:
--------------------
	 -b, --ignore leading blanks		Ignore leading blanks
	 -i, --ignore-nonprinting		Consider only printable characters
	 -n, --numeric sort			Compare according to string numeric value
	 -f, --ignore case			Fold lower case to upper case
	 -r, --reverse				Reverse the result of comparisions
	 -b, --dictionary-order			Consider only blanks and alphanumeric characters

  Other OPTIONS: 
------------------
	 -t, --field-separator=SEP		use SEP instead of non-blank to blank transi-tion
		 For example, if you want to consider comma separator file, and sort column 2, so use -t,2
	 -k, --key=KEYDEF			Sort via a key. KEYDEF gives location
	 -m, --merge				Merge already sorted files; Do not sort.
	 -u, --unique				Remove duplicates from result
	 -h, --help				Print this usage and exit

	 -nr or -rn --reverse numeric sort	sort numerically in a reverse order
	 -nk --numeric key=KEYDEF		Sort nemerically via a key. KEYDEF gives location
	 
	 
The sort command sorts any user input or files. It can sort files of any size.In this project, big file is divided on the basis of number of lines into many runs i.e files. Then these files are individually get sorted with the help of merge sort algorithm. After that, merging of these sorted files is done with the help of min heap or max heap, depending on the order of sorting.

