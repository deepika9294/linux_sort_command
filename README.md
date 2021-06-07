
[![LinkedIn][linkedin-shield]][linkedin-url]

<!-- PROJECT LOGO -->
<br />
<p align="center">
  <a href="https://https://github.com/deepika9294/linux_sort_command">
    <img src="sort1.jpeg" alt="Logo" width="80" height="80">
  </a>

  <h3 align="center">Linux Sort Command</h3>
</p>


<!-- TABLE OF CONTENTS -->
<details open="open">
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
    </li>
    <li>
      <a href="#getting-started">Getting Started</a>
    </li>
    <li><a href="#usage">Usage</a></li>
    <li><a href="#contributing">Contributing</a></li>
    <li><a href="#author">Author</a></li>
	  
  </ol>
</details>



<!-- ABOUT THE PROJECT -->
## About The Project


**Sort** command in linux is used to sort a file or inputs, arranging the records in a particular order. By default, the sort command sorts assuming the contents are ASCII. It can also be used to sort records numerically with the help of options provided. Sorts the content line by line. Sorting is done based on one or more sort keys extracted from each line of input and by default, the entire input is taken as sort key. It can also sort files of big size (i.e more than size of RAM). 

**External sorting** is supported and is implemented with the help of heaps. External sorting is required when the data being sorted do not fit into the main memory of a computing device (usually RAM) and instead they must reside in the slower external memory, usually a hard disk drive.


  [![forthebadge](https://forthebadge.com/images/badges/made-with-c.svg)](https://forthebadge.com)



<!-- GETTING STARTED -->
## Getting Started

1. Clone the repository
2. Navigate to the src directory and run the make file by typing make in terminal.


<!-- USAGE EXAMPLES -->
## Usage

*./sort [OPTION] [FILE]* 

If no file is mention then, user is supposed to give inputs: </br> Usage: *./sort [OPTION] (user inputs)* 
		
For merging two files: </br> Usage:  *./sort [OPTION] [FILE1] [FILE2]*

For [FILE], enter the path of the file w.r.t to **src** directory.

### [OPTIONS] supported: 

	 -b, --ignore leading blanks		Ignore leading blanks
	 -i, --ignore-nonprinting		Consider only printable characters
	 -n, --numeric sort			Compare according to string numeric value
	 -f, --ignore case			Fold lower case to upper case
	 -r, --reverse				Reverse the result of comparisions
	 -b, --dictionary-order			Consider only blanks and alphanumeric characters

### Other Options:
	 -t, --field-separator=SEP		use SEP instead of non-blank to blank transi-tion
		 For example, if you want to consider comma separator file, and sort column 2, so use -t,2
	 -k, --key=KEYDEF			Sort via a key. KEYDEF gives location
	 -m, --merge				Merge already sorted files; Do not sort.
	 -u, --unique				Remove duplicates from result
	 -h, --help				Print this usage and exit

	 -nr or -rn --reverse numeric sort	sort numerically in a reverse order
	 -nk --numeric key=KEYDEF		Sort nemerically via a key. KEYDEF gives location
	 

To understand more about it, test.txt file can help guide. 


<!-- CONTRIBUTING -->
## Contributing

Contributions make the open source community such an amazing place to be learn, inspire, and create. Any contribution is **greatly appreciated**.

1. Fork the Project
2. Create your Feature Branch (`git checkout -b feature/AmazingFeature`)
3. Commit your Changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the Branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request


<!-- CONTRIBUTOR -->
## Author
[Deepika Goyal](https://github.com/deepika9294)


<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->
[linkedin-shield]: https://img.shields.io/badge/-LinkedIn-black.svg?style=for-the-badge&logo=linkedin&colorB=555
[linkedin-url]: https://linkedin.com/in/deepika9294



