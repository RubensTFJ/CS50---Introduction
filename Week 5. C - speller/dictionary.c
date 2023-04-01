// Implements a dictionary's functionality
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>

#include "dictionary.h"

bool insertword(char *word);

// Represents a node in a hash table
typedef struct node
{
	char word[LENGTH + 1];
	struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

int word_counter = 0;

// Hash table
node *table[N];

char *removecaps(const char *string);

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
	node *chain;
	char *low_word;
	int check;

	low_word = removecaps(word);

	chain = table[low_word[0] - 97]->next;
	while (chain != NULL)
	{
		check = strcmp(chain->word, low_word);
		if (check == 0)
		{
			free(low_word);
			return true;
		}
		chain = chain->next;
	}
	free(low_word);
	return false;
}

char *removecaps(const char *string)
{
	int i = 0;
	char *restring;

	restring = malloc(strlen(string) + 1);

	while (string[i] != '\0')
	{
		if (64 < string[i] && string[i] < 91)
			restring[i] = string[i] + 32;
		else
			restring[i] = string[i];
		i++;
	}
	restring[i] = '\0';
	return (restring);
}

// Hashes word to a number
unsigned int hash(const char *word)
{
	// TODO: Improve this hash function
	return toupper(word[0]) - 'A';
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
	char word[46];
	int i;

	for (int j = 0; j < 26; j++)
	{
		table[j] = malloc(sizeof(node));
		if (!table[j])
			return false;
	}
	for (int j = 0; j < 26; j++)
		table[j]->next = NULL;

	FILE *fp = fopen(dictionary, "r");

	while (fread(&word[0], sizeof(char), 1, fp))
	{
		for (i = 0; word[i] != '\n'; i++)
				fread(&word[i + 1], sizeof(char), 1, fp);

		word[i] = '\0';
		if (!insertword(word))
			return false;
		word_counter++;
	}
	fclose(fp);
	return true;
}

bool insertword(char *word)
{
	node *find = table[word[0] - 97];
	int i;

	while (find->next != NULL)
		find = find->next;

	find->next = malloc(sizeof(node));
	if (!find->next)
		return false;

	for (i = 0; word[i] != '\0'; i++)
		find->next->word[i] = word[i];
	find->next->word[i] = '\0';
	find->next->next = NULL;
	return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
	return (word_counter);
}

void freechain(node *chain);
// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
	for (int i = 0; i < 26; i++)
	{
		freechain(table[i]);
	}
	return true;
}

void freechain(node *chain)
{
	if (chain->next != NULL)
	{
		freechain(chain->next);
	}
	free(chain);
}
