# Mendax-Binder
![Mendax-Binder](https://s14.postimg.org/ynx423o9d/mendax_logo.png)


A useful and efficient file binder.  I created this for educational purposes after researching some file binding techniques on some old forum posts.
Not only can it bind two exes (Windows only), but this program also obfuscates ths two exes.  Its output file is usually fully undetectable among 68.7% of the antivirus software used on VirusTotal.

## How it Works
This program always binds itself to the two other files.  This way, when the binded application runs, the program first checks if the application is correctly binded.  If it is, it runs the two applications.

## Usage
So far, only CLI is supported.  Here are the options:
 * -1: First input file
 * -2: Second input file
 * -o: Name for the output file
 * -h: Displays this help message
 * -v: Displays version number
 * -s: Silent mode
 
 Users can either choose to download the executable from the releases section, clone the repo, or compile mendax.c with MinGW's gcc.
 When compiling the GUI, make sure to have already compiled mendax.c and link mendax_binder.c with all the .o files.
 By running or downloading this program, you agree to the terms of the disclaimer below.

## Disclaimer
Remember that this program is only for EDUCATIONAL PURPOSES.  Do not use this for malicious purposes.  This program must not be used on any system or network that you do not have permission to. I am not responsible if you ruin your own computer or get in serious trouble for creating malware.
 
 ## Authors
* **Will Liu** - *Creator* - [BitsByWill](https://github.com/BitsByWill)

## What's Next
* Better obfuscation
* Bind more than two files
* Patch up any issues (Let me know of any issues please!)

## Note
Please note that this program still has problems and must be improved.  I am currently trying to figure out an issue that causes the binded file to not work in certain cases (it works 100% on XP and Vista, but sometimes break on 7, 8, and 10).

## License
This project is licensed under the GNU GPLv3 - see the [LICENSE](LICENSE) file for details
