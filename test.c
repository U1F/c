#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <time.h>

// reverse string function:
const int BIRTHYEAR = 1981;
void tests(void);
void tests(void)
{
    printf("This is a test.\n");
    printf("Hello, world!\n\nHi!\n");
    const int number = 42;
    printf("The number is %d.\n", number);
    const size_t sizeofnumber = sizeof(number);
    printf("The size of the number is %zu.\n", sizeofnumber);
    const float pi = 3.14159265359;
    printf("Pi is %f.\n", pi);
    printf("Pi is %.2f.\n", pi);
    printf("Pi is %.5f.\n", pi);
    const size_t sizeoffloat = sizeof(pi);
    printf("The size of the float is %zu.\n", sizeoffloat);

    const double pid = 3.141592653589793238462643383279502884197169399375105820974944592307816406286;
    printf("Pi is %f.\n", pid);
    printf("Pi is %.2f.\n", pid);
    const size_t sizedouble = sizeof(pid);
    printf("The size of the double is %zu.\n", sizedouble);

    const char letter = 'A';
    printf("The letter is %c.\n", letter);
    const size_t sizechar = sizeof(letter);
    printf("The size of the letter is %zu.\n", sizechar);

    const bool isProgrammingFun = true;
    printf("Is programming fun? %d\n", isProgrammingFun);
    const size_t sizebool = sizeof(isProgrammingFun);
    printf("The size of the bool is %zu.\n", sizebool);

    const int shorthandTest = (isProgrammingFun) ? 69 : 420;
    printf("The shorthand test is %d.\n", shorthandTest);

    char greetings[] = "Hello World!";
    printf("The greeting is %s.\n", greetings);
    const size_t sizegreetings = sizeof(greetings);
    printf("The size of the greetings is %zu.\n", sizegreetings);

    char myName[] = {'U', 'l', 'f', '\0'};
    printf("My name is %s.\n", myName);
    const size_t sizemyName = sizeof(myName);
    printf("The size of my name is %zu.\n", sizemyName);

    const int lengthName = strlen(myName);
    printf("The length of my name is %d.\n", lengthName);

    const char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    printf("Alphabet length: %zu \n", strlen(alphabet)); // 26
    printf("Alhpabet size: %lu\n", sizeof(alphabet));    // 27

    char str1[20] = "Hello ";
    const char str2[] = "World!";

    strcat(str1, str2);
    printf("%s", str1);

    char str3[20];

    strcpy(str3, str1);
    printf("%s", str3);
    // compare strings:
    const char str4[] = "Hello";
    const char str5[] = "Hello";
    const char str6[] = "Hello World";

    printf("str4 == str5: %d\n", strcmp(str4, str5)); // 0
    printf("str4 == str6: %d\n", strcmp(str4, str6)); // some negative number
    printf("str6 == str4: %d\n", strcmp(str6, str4)); // some positive number

    // get user input:
    const int MAX = 20;
    int ch;
    char name[MAX]; // That number must be specified at compile time. It cannot be a variable.
    printf("Enter your name: ");
    scanf("%19s", name);
    printf("Your name is %s.\n", name);
    // the input works, but it's not perfect at all.
    while ((ch = getchar()) != '\n' && ch != EOF)
        ; // Clearing the buffer
    //
    // Let's try fgets
    char name2[MAX];
    printf("Enter your name: ");
    fgets(name2, MAX, stdin);
    printf("Your name is %s.\n", name2);
    // fgets is better, but it's still not perfect.
}

char *reverse(char *word);

char *reverse(char *word)
{
    int length = 0;
    while (word[length] != '\0')
    {
        length++;
    }

    int start = 0;
    int end = length - 1;
    char temp;

    while (start < end)
    {
        temp = word[start];
        word[start] = word[end];
        word[end] = temp;
        start++;
        end--;
    }

    return word;
}

int main(int argc, char *argv[])
{
    // test string:

    if (argc < 2)
    {
        printf("No arguments passed.\n");
    }

    if (argc == 2)
    {
        printf("One argument passed.\n");
        printf("Argument: %s\n", argv[1]);
        printf("Reversed: %s\n", reverse(argv[1]));
    }
    // tests();

    FILE *fptr;
    fptr = fopen("filename.txt", "a");
    fprintf(fptr, "\nSome text");

    fclose(fptr);
    char myString[200];
    fptr = fopen("filename.txt", "r");
    if (fptr == NULL)
    {
        printf("Error opening file!");
        exit(1);
    }
    while (fgets(myString, 100, fptr))
    {
        printf("%s", myString);
    }
    fclose(fptr);

    struct person
    {
        char name[50];
        int age;
        float weight;
    };

    struct person examplePerson;
    examplePerson.age = 42;
    examplePerson.weight = 69.420;
    strcpy(examplePerson.name, "Ulf"); // assignment is not possible, so we need to use strcpy

    printf("Name: %s\n", examplePerson.name);
    printf("Age: %d\n", examplePerson.age);
    printf("Weight: %f\n", examplePerson.weight);

    enum Company
    {
        GOOGLE = 1, // 0 is default
        FACEBOOK,
        XEROX,
        YAHOO,
        EBAY,
        MICROSOFT
    };

    enum Company xerox = XEROX;

    printf("The value of xerox is: %d\n", xerox);

    switch (xerox)
    {
    case GOOGLE:
        printf("Google\n");
        break;
    case FACEBOOK:

        printf("Facebook\n");
        break;
    case XEROX:
        printf("Xerox\n");
        break;
    case YAHOO:
        printf("Yahoo\n");
        break;
    case EBAY:
        printf("Ebay\n");
        break;
    case MICROSOFT: 
        printf("Microsoft\n");
        break;
    default:

        printf("No company found\n");
        break;
    }

    // time
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    printf("Today is %d-%d-%d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
    
    return 0;
}