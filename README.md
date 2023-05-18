lexical analyzer for C language programs

this program analyze any C program file lexically an then return one file in xml format.
to use , after clone file's , compile cLexicalAnalyzer.c with any c compiler you want ,
and then execute out put file with two argument:
-first argument is c file that you want to analyze
-second argument is output file with .xml suffix

algorithm of this program:
in this program we implement a general lexicall analyzer algorithm that can analyze many programming languages
and it looks like this(the left for the main algorithm and the right for buffer detector algorithm):
![flowchart](https://github.com/a-GumaryaN/C-lexical-analizer/assets/76553715/eb0030c9-2002-45c2-845e-3a2ba3e9de5a)
to use this algorithm we should customize algorithm (keywords,comment operators,operators and other features) to base programing language that we want to analyz that.
