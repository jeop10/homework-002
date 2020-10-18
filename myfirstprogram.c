#include <stdio.h>
#include <regex.h>

void endApp(char *message)
{
    printf("%s \n", message);
    printf("Exit program");
}

int readFile(char *filename, char *needle)
{
    FILE *file;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    int lineNumber = 1;
    int needleFound = 0;
    regex_t reg;
    int compiledRegex = 0;

    file = fopen(filename, "r");

    if (file == NULL)
    {
        endApp("The file does not exists on the folder");
        return 1;
    }

    compiledRegex = regcomp(&reg, needle, REG_ICASE | REG_EXTENDED);

    if (compiledRegex != 0)
    {
        endApp("Regex not valid");
    }

    while ((read = getline(&line, &len, file)) != -1)
    {
        //this is using a pattern
        if (regexec(&reg, line, 0, NULL, 0) == 0)
        {
            printf("[Line: %d]: %s", lineNumber, line);
            needleFound = 1;
        }

        lineNumber++;
    }

    if (needleFound < 1)
    {
        endApp("Word not found on file.");
    }
}

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        endApp("Filename and word to search are obligatory parameters");
    }
    if (argc == 3)
    {
        return readFile(argv[1], argv[2]);
    }
}