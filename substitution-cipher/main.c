#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

char alphabets[26];

void build_lowercase_alphabets();

bool check_key_validity(char *key);

void process_ciphertext(char *plaintext, char *key);

int main(int argc, char *argv[])
{
    // Check if only one command-line argument is passed
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    // Create an array of alphabets in lowercase
    build_lowercase_alphabets();

    // Check key's validity
    char *key = argv[1];

    if (!check_key_validity(key))
    {
        printf("Key must contain 26 alphabetical characters.\n");
        return 1;
    }

    // Prompt user for plaintext
    char *plaintext = NULL;

    printf("plaintext: ");
    // The %ms specifier allocates memory and returns a pointer to that memory --
    // scanf() allocates a buffer of sufficient size, and assigns the address of
    // this buffer to the corresponding pointer argument, which should be a pointer to a char * variable.
    scanf("%m[^\n]", &plaintext);

    if (plaintext == NULL)
    {
        printf("No plaintext was provided.\n");
        return 1;
    }

    // Create and print ciphertext
    process_ciphertext(plaintext, key);

    free(plaintext);

    return 0;
}

void build_lowercase_alphabets()
{
    for (int i = 0, letter = 'a'; letter <= 'z'; i++, letter++)
    {
        alphabets[i] = letter;
    }
}

bool check_key_validity(char *key)
{
    int counter = 0;
    char current_char = tolower(key[counter]);

    while (isalpha(current_char) && counter <= 26)
    {
        // Check for duplicate alphabets and keep track by
        // uppercasing alphabets that have been already looked at.
        int idx = current_char - 'a';

        if (alphabets[idx] != current_char) break;

        alphabets[idx] = toupper(current_char);
        counter++;
        current_char = tolower(key[counter]);
    }

    return counter == 26;
}

void process_ciphertext(char *plaintext, char *key)
{
    int plaintext_len = strlen(plaintext);
    char ciphertext[plaintext_len];

    for (int i = 0; i < plaintext_len; i++)
    {
        char current = plaintext[i];

        if (isalpha(current))
        {
            char char_in_key = key[tolower(current) - 'a'];

            char corresponding_letter_in_key = isupper(current)
                ? toupper(char_in_key)
                : tolower(char_in_key);

            ciphertext[i] = corresponding_letter_in_key;
        }
        else
        {
            ciphertext[i] = current;
        }
    }

    ciphertext[plaintext_len] = '\0';

    printf("ciphertext: %s\n", ciphertext);
}
