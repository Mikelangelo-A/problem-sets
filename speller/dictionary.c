// Implements a dictionary's functionality

#include <stdbool.h>
#include <strings.h>
#include <stdio.h>
#include <stdint.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

unsigned int count = 0;

// Number of buckets in hash table
const unsigned int N = 256;

// Hash table
node *table[N];

// unsigned int count_letters(const char* word);

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    int n = strlen(word);
    char* inputw = malloc((sizeof(char) * n) + 1);
    for(int i = 0; i < n + 1; i++)
    {
        if(word[i] == '\0')
        {
            inputw[i] = '\0';
        }
        else
        {
        inputw[i] = tolower(word[i]);
        //printf("inputw[i] is %c\n", inputw[i]);
        }
            
    }
    int key = hash(inputw) % N;
    node *ptr = table[key];
    while(ptr != NULL)
    {
        int result = strcasecmp(ptr->word, word);
        if(result == 0)
        {
            free(inputw);
            return true;
        }
        else
        {
            ptr = ptr->next;
        }
    }
    free(inputw);
    return false;
}


//Hash taken from source : https://stackoverflow.com/questions/32795453/use-of-murmurhash-in-c
// Hashes word to a number
unsigned int hash(const char *word)
{
    // uint32_t length = 0;
    // for(int i = 0; word[i] != '\0'; i++)
    // {
    //     //printf("word[i] is %c\n", word[i]);
    //     //printf("%c\n",word[i]);
    //     length++;
    // }
    int length = strlen(word);
    // unsigned int length = count_letters(word);
    unsigned int len = length;
    uint32_t seed = 7;
    static const uint32_t c1 = 0xcc9e2d51;
    static const uint32_t c2 = 0x1b873593;
    static const uint32_t r1 = 15;
    static const uint32_t r2 = 13;
    static const uint32_t m = 5;
    static const uint32_t n = 0xe6546b64;

    uint32_t hash = seed;

    const int nblocks = len / 4;
    const uint32_t *blocks = (const uint32_t *) word;
    int i;
    for (i = 0; i < nblocks; i++) {
        uint32_t k = blocks[i];
        k *= c1;
        k = (k << r1) | (k >> (32 - r1));
        k *= c2;

        hash ^= k;
        hash = ((hash << r2) | (hash >> (32 - r2))) * m + n;
    }

    const uint8_t *tail = (const uint8_t *) (word + nblocks * 4);
    uint32_t k1 = 0;

    switch (len & 3) {
    case 3:
        k1 ^= tail[2] << 16;
    case 2:
        k1 ^= tail[1] << 8;
    case 1:
        k1 ^= tail[0];

        k1 *= c1;
        k1 = (k1 << r1) | (k1 >> (32 - r1));
        k1 *= c2;
        hash ^= k1;
    }

    hash ^= len;
    hash ^= (hash >> 16);
    hash *= 0x85ebca6b;
    hash ^= (hash >> 13);
    hash *= 0xc2b2ae35;
    hash ^= (hash >> 16);

    return hash;
}


// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    //initialize_table(table);
    FILE *dict = fopen(dictionary , "r");
    if(dict == NULL)
    {
        return false;
    }
    bool end = false;
    while(!end)
    {
        char input[LENGTH + 1];
        int c = fscanf(dict, "%s", input);
        if(c == EOF)
        {
            end = true;
            continue;
        }
        else
        {
            node *element = malloc(sizeof(node));
            if(element == NULL)
            {
                return false;
            }
            count++;
            strcpy(element->word , input);
            unsigned int key = ((hash(input)) % N);
            printf("%i\n", key);
            // int n =
            // if()

            element->next = table[key];
            table[key] = element;
            //printf("%p\n", table[key]->next);

            // if(table[key]->next != NULL)
            // {
            //     element->next = table[key]->next;
            //     table[key]->next = element;
            // }
            // if(table[key]->next == NULL)
            // {
            //     element->next = NULL;
            //     table[key]->next = element;
            // }
        }
    }
    if(end == true)
    {
        fclose(dict);
        return true;
    }
    fclose(dict);
    return false;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    if(count > 0)
    {
    return count;
    }
    else
    {
        return 0;
    }
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    bool done = false;
    for(int i = 0; i < N; i++)
    {
        while(table[i] != NULL)
        {
            node *tmp = table[i]->next;
            free(table[i]);
            table[i] = tmp;
        }
        if(i == 255)
        {
            done = true;
        }
    }
    if(done == true)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// unsigned int count_letters(const char* word)
// {

//     int lcount = 0;
//     for(int i = 0; i < N ; i++)
//     {
//         if(word[i + 1] == '\0')
//         {
//             lcount++;
//             break;
//         }
//         lcount++;
//     }
//     return lcount;
// }
