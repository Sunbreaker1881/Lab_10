// Evan Suarez

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Trie structure
struct Trie
{
    int isWord;
    struct Trie* next[26];
};

void insert(struct Trie *pTrie, char *word);
int numberOfOccurances(struct Trie *pTrie, char *word);
struct Trie *deallocateTrie(struct Trie *pTrie);
struct Trie *createTrie();
int readDictionary(char *filename, char **pInWords);

// Inserts the word to the trie structure
void insert(struct Trie *pTrie, char *word)
{
    int len = strlen(word);
    if(pTrie == NULL) pTrie = createTrie();

    struct Trie *current = pTrie;

    for(int i = 0; i < len; i++)
    {
        int nidx = word[i] - 'a';
        if(current->next[nidx] == NULL)
            current->next[nidx] = createTrie();
        current = current->next[nidx];
    }
    current->isWord++;
}

// computes the number of occurances of the word
int numberOfOccurances(struct Trie *pTrie, char *word)
{   
    struct Trie* current = pTrie;
    int len = strlen(word);
    for(int i = 0; i < len; i++)
    {
        int idx = word[i]-'a';
        if(current->next[idx]==NULL)
        {
            return 0;
        }
        current = current->next[idx];
    }
    return current->isWord;
}

// deallocate the trie structure
struct Trie *deallocateTrie(struct Trie *pTrie)
{
    for (int i = 0; i < 26; i++)
    {
        if (pTrie->next[i] != NULL)
        {
            free(pTrie->next[i]);
        }
    }
    free(pTrie);
    return NULL;
}

// Initializes a trie structure
struct Trie *createTrie()
{
    struct Trie* tree = (struct Trie*)malloc(sizeof(struct Trie));
    tree->isWord = 0;

    for(int i = 0; i < 26; i++)
    {
        tree->next[i] = NULL;
    }
    return tree;
}


int readDictionary(char *filename, char **pInWords)
{
    int n = 0;
    FILE* fp = fopen(filename, "r");
    if(fp == NULL) 
    {
        return -1;
    }
    fscanf(fp, "%d", &n);

    for(int i = 0; i < n; i++)
    {
        pInWords[i] = (char*)malloc(256*sizeof(char));
        fscanf(fp, "%s", pInWords[i]);
    }
    fclose(fp);
    return n;
}

int main(void)
{
	char *inWords[256];
	int numWords = readDictionary("dictionary.txt", inWords);
	for (int i = 0; i < numWords; ++i)
	{
		printf("%s\n",inWords[i]);
	}
	
	struct Trie *pTrie = createTrie();
	for (int i = 0; i < numWords; i++)
	{
		insert(pTrie, inWords[i]);
	}
	char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
	for (int i = 0; i < 5; i++)
	{
		printf("\t%s : %d\n", pWords[i], numberOfOccurances(pTrie, pWords[i]));
	}
	pTrie = deallocateTrie(pTrie);
	if (pTrie != NULL)
		printf("There is an error in this program\n");
	return 0;
}

