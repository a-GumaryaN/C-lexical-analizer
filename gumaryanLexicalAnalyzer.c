#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// comment

FILE *inputFile = NULL;

FILE *outFile = NULL;

char *program, ch, buffer[100] = " ";

long length;

int i; // iterator integer for count for loops in program

int bufferPointer; // buffer pointer

bool inlineCommentMode = false,
     multilineCommentMode = false,
     stringMode = false;

bool isSingleCharOperator(char ch);

bool isMultiCharOperator(char *str);

bool isKeyword(char *str);

bool isNumber(char *str);

void resetBuffer();

bool isDelimeter(char ch);

void checkBufferAndPrint(char *buff);

bool isStringOperator(char ch);

bool isEmpty(char *str);

void main(int argn, char *argv[])
{
    inputFile = fopen(argv[1], "r");

    if (inputFile == NULL)
    {
        printf("file not exist");
        return;
    }

    fseek(inputFile, 0, SEEK_END);

    length = ftell(inputFile);

    fseek(inputFile, 0, SEEK_SET);

    program = malloc(length);

    if (program)
        fread(program, 1, length, inputFile);

    if (!program)
    {
        printf("error in read file");
        return;
    }

    outFile = fopen(argv[2], "w");

    if (outFile == NULL)
    {
        printf("out put file not exist");
        return;
    }

    fprintf(outFile, "<out>");

    while (i < length)
    {
        ch = *(program + i);
        i++;

        char operator[2] = "";
        operator[0] = ch;
        operator[1] = *(program + i);

        // check if ch is a comment operator

        if (strcmp(operator, "/*") == 0)
        {
            // if receive to  activate or deactivate multilineCommentMode
            multilineCommentMode = true;
            i++;
            continue;
        }
        if (strcmp(operator, "*/") == 0)
        {
            // if receive to  activate or deactivate multilineCommentMode
            multilineCommentMode = false;
            i++;
            continue;
        }
        if (strcmp(operator, "//") == 0)
        {
            // if receive to  activate or deactivate multilineCommentMode
            inlineCommentMode = true;
            i++;
            continue;
        }
        if (ch == '\n' && inlineCommentMode == true)
        {
            // if receive to \n deactivate inlineCommentMode
            inlineCommentMode = false;
            continue;
        }



        // ignore other lines if we are in comments
        if (inlineCommentMode || multilineCommentMode)
        {
            continue;
        }



        // check if ch is string operator
        if (isStringOperator(ch))
        {
            if (isEmpty(buffer))
            {
                printf("<string>%s</string>\n", buffer);

                fprintf(outFile, "<string>%s</string>\n", buffer);

                resetBuffer();

                stringMode = false;
            }
            else
            {
                stringMode = true;
            }
            continue;
        }



        // check if string mode is active
        if (stringMode)
        {
            buffer[bufferPointer] = ch;
            bufferPointer++;
            continue;
        }



        // check ch is an single character  operator
        if (isMultiCharOperator(operator))
        {

            // check characters befor ch to see those content
            if (strlen(buffer) != 0)
            {

                checkBufferAndPrint(buffer);

                resetBuffer();
            }

            printf("<operator>%s</operator>\n", operator);

            fprintf(outFile, "<operator>%s</operator>\n", operator);

            i++;

            continue;
        }

        

        // check ch is an single character operator
        if (isSingleCharOperator(ch))
        {
            printf("<operator>%c</operator>\n", ch);

            fprintf(outFile, "<operator>%c</operator>\n", ch);

            // check characters befor ch to see those content
            if (strlen(buffer) != 0)
            {
                checkBufferAndPrint(buffer);
                resetBuffer();
            }

            continue;
        }



        // check if ch is delimeter
        if (isDelimeter(ch))
        {
            if (strlen(buffer) != 0)
            {
                checkBufferAndPrint(buffer);
                resetBuffer();
            }

            continue;
        }


        buffer[bufferPointer] = ch;
        bufferPointer++;

    }

    fprintf(outFile, "</out>");

    fclose(inputFile);

    fclose(outFile);
}

bool isSingleCharOperator(char ch)
{
    char operators[9] = "*/+-%>=<!";
    int i;
    bool flag = false;
    for (i = 0; operators[i]; i++)
    {
        if (operators[i] == ch)
        {
            flag = true;
            break;
        }
    }
    return flag;
}

bool isMultiCharOperator(char *str)
{
    bool flag = false;

    if (!strcmp("<=", str))
    {
        flag = true;
    }

    if (!strcmp("==", str))
    {
        flag = true;
    }

    if (!strcmp(">=", str))
    {
        flag = true;
    }

    if (!strcmp("!=", str))
    {
        flag = true;
    }

    if (!strcmp("*=", str))
    {
        flag = true;
    }

    if (!strcmp("/=", str))
    {
        flag = true;
    }

    if (!strcmp("+=", str))
    {
        flag = true;
    }

    if (!strcmp("-=", str))
    {
        flag = true;
    }

    if (!strcmp("||", str))
    {
        flag = true;
    }

    return flag;
}

bool isKeyword(char *str)
{
    char keywords[34][10] = {"auto", "break", "case", "char", "const", "continue", "default",
                             "do", "double", "else", "enum", "extern", "float", "for", "goto",
                             "if", "int", "long", "register", "return", "short", "signed",
                             "sizeof", "static", "struct", "switch", "typedef", "union",
                             "unsigned", "void", "volatile", "while", "#include", "#define"};
    int i;
    bool flag = false;
    for (i = 0; i < 32; ++i)
    {
        if (strcmp(str, keywords[i]) == 0)
        {
            flag = true;
            break;
        }
    }
    return flag;
}

bool isNumber(char *str)
{
    int i;
    bool flag = true;

    for (i = 0; *(str + i); i++)
    {
        if (*(str + i) < 48 || *(str + i) > 57)
        {
            flag = false;
            break;
        }
    }

    return flag;
}

void resetBuffer()
{
    for (int buffPointer = 0; buffer[buffPointer]; buffPointer++)
        buffer[buffPointer] = '\0';
    bufferPointer = 0;
}

bool isDelimeter(char ch)
{
    const char delimiters[] = {';', '\n', ' ', '{', '}', '<', '>', '(', ')', ':', '\t', ',', '[', ']', '(', ')'};

    int i;
    bool flag = false;

    for (i = 0; delimiters[i]; i++)
    {
        if (delimiters[i] == ch)
        {
            flag = true;
            break;
        }
    }

    return flag;
}

void checkBufferAndPrint(char *buff)
{
    if (isKeyword(buff))
    {
        printf("<keyword>%s</keyword>\n", buff);
        fprintf(outFile, "<keyword>%s</keyword>\n", buffer);
    }
    else if (isNumber(buff))
    {
        printf("<number>%s</number>\n", buff);
        fprintf(outFile, "<number>%s</number>\n", buffer);
    }
    else
    {
        printf("<identifire>%s</identifire>\n", buff);
        fprintf(outFile, "<identifire>%s</identifire>\n", buffer);
    }
}

bool isStringOperator(char ch)
{
    if (ch + 0 == 34 || ch + 0 == 39)
        return true;
    return false;
}

bool isEmpty(char *str)
{
    if (strlen(str) != 0)
        return true;
    return false;
}