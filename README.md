# xecho for Windows

xecho is a simple command line tool that prints the arguments it receives to stderr and then exits successfully.
I originally wrote it to help me debug problems with the often arcane command line tokenization that happens
inside .bat files running under Windows's cmd.exe. It has also been useful troubleshooting commandlike tokenization
quirks in WSL, MSYS2, Git Bash, PowerShell, and Cygwin.   
    
It has two usage forms:

### <br>  
### `xecho <commandline>`
Prints the raw command-line as reported by [GetCommandLine()](https://learn.microsoft.com/en-us/windows/win32/api/processenv/nf-processenv-getcommandlinew). The printf format used in this case is:  
```cpp
"xecho [%s]\n"
```
Where `%s` is the string from `GetCommandLineW` (or `GetCommandLineA`, depending on how the executable was compiled).  


### <br>
### `xecho -c <commandline>`
Prints the arguments as tokenized by the C runtime and passed to main(argc, char** argv).
The printf format of each argv string is:
```cpp
"xecho argv[%d]=[%s]\n"
```
Where `%d` is the zero-based index `i` into argv and `%s` is the value of `argv[i]`.

