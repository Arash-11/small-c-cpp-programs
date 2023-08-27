```c
#include <stdio.h>

#define COUNT 3

int main(void) {
    char a[] = "a";
    char b[] = "big";
    char c[] = "cake";

    char *words[COUNT] = { a, b, c };

    char **word_ptr = words;

    printf("sizeof(words): %lu bytes\n\n", sizeof(words));

    for (int i = 0; i < COUNT; ++i) {
        printf("%p\n", word_ptr);
        printf("%p\n", *word_ptr);
        printf("%s\n", *word_ptr);
        printf("%c\n\n", **word_ptr);

        word_ptr++;
    }
}
```

In C, strings are arrays of characters, and an array name in C is essentially a constant pointer to
the first element of the array. So when we say `char a[] = "a";`, `a` is essentially a pointer to the
first character in the string, which in this case is the only character 'a'.

So when you initialize `char *words[COUNT] = { a, b, c };`, each element in the array `words` is a pointer
to the first character of a string. `words` itself is an array of pointers, and it can also be seen as a
pointer to its first element, which is a pointer to a character. That's why `char **word_ptr = words;` works,
`word_ptr` is a pointer to a pointer to a char, and it initially points to the first element of `words`.

When you dereference `word_ptr` once (i.e., `*word_ptr`), you get the value it points to, which is a
`char *` (a pointer to a char). Because C strings are arrays of characters terminated by a null character (`\0`),
this `char *` actually points to a full string, even though it's technically only pointing to the first
character of that string. The rest of the string is reached by continuously incrementing the pointer to get
to the next characters, until the null character is found which signifies the end of the string.

So, `*word_ptr` gives you the string that `word_ptr` points to, and `**word_ptr` dereferences the pointer twice,
effectively getting the character that `word_ptr` points to.

```
> gcc -o pointer_demo pointer_demo.c && ./pointer_demo

sizeof(words): 24 bytes

0x16af572d0
0x16af572ca
a
a

0x16af572d8
0x16af572c4
big
b

0x16af572e0
0x16af572bc
cake
c
```
