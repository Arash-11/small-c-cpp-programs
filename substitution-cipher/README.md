# Substitution cipher

An implementation of [CS50's substitution problem set](https://cs50.harvard.edu/x/2022/psets/2/substitution/) but without using the `cs50` header library, so we can use some pointers and simple memory management.

## Description
Write a program called `substitution` that enables you to encrypt messages using a substitution cipher. At the time the user executes the program, they should decide, by providing a command-line argument, on what the key should be in the secret message they’ll provide at runtime.

For example, here’s how the program might work if the user provides a key of `VCHPRZGJNTLSKFBDQWAXEUYMOI` and a plaintext of `hello, world`:

```c
$ ./substitution VCHPRZGJNTLSKFBDQWAXEUYMOI
plaintext:  hello, world
ciphertext: jrssb, ybwsp
```

Notice that neither the comma nor the space were substituted by the cipher. Only substitute alphabetical characters! Notice, too, that the case of the original message has been preserved. Lowercase letters remain lowercase, and uppercase letters remain uppercase.

## Specification
- Your program must accept a single command-line argument, the key to use for the substitution. The key itself should be case-insensitive, so whether any character in the key is uppercase or lowercase should not affect the behavior of your program.

- If your program is executed without any command-line arguments or with more than one command-line argument, your program should print an error message of your choice (with printf) and return from main a value of 1 (which tends to signify an error) immediately.

- If the key is invalid (as by not containing 26 characters, containing any character that is not an alphabetic character, or not containing each letter exactly once), your program should print an error message of your choice (with printf) and return from main a value of 1 immediately.

- Your program must preserve case: capitalized letters must remain capitalized letters; lowercase letters must remain lowercase letters.

## Test cases
- substitution.c compiles
- encrypts "A" as "Z" using ZYXWVUTSRQPONMLKJIHGFEDCBA as key
- encrypts "a" as "z" using ZYXWVUTSRQPONMLKJIHGFEDCBA as key
- encrypts "ABC" as "NJQ" using NJQSUYBRXMOPFTHZVAWCGILKED as key
- encrypts "XyZ" as "KeD" using NJQSUYBRXMOPFTHZVAWCGILKED as key
- encrypts "This is CS50" as "Cbah ah KH50" using YUKFRNLBAVMWZTEOGXHCIPJSQD as key
- encrypts "This is CS50" as "Cbah ah KH50" using yukfrnlbavmwzteogxhcipjsqd as key
- encrypts "This is CS50" as "Cbah ah KH50" using YUKFRNLBAVMWZteogxhcipjsqd as key
- encrypts all alphabetic characters using DWUSXNPQKEGCZFJBTLYROHIAVM as key
- does not encrypt non-alphabetical characters using DWUSXNPQKEGCZFJBTLYROHIAVM as key
- handles lack of key
- handles too many arguments
- handles invalid key length
- handles invalid characters in key
- handles duplicate characters in uppercase key
- handles duplicate characters in lowercase key
- handles multiple duplicate characters in key
