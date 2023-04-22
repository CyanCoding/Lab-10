#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct TrieNode {
    int count;
    struct TrieNode *children[26];
};

struct Trie {
    struct TrieNode *root;
};

void insert(struct Trie **ppTrie, char *word) {
    struct TrieNode *node = (*ppTrie)->root;
    int i = 0;
    while (word[i] != '\0') {
        int idx = word[i] - 'a';
        if (node->children[idx] == NULL) {
            node->children[idx] = (struct TrieNode *)malloc(sizeof(struct TrieNode));
            memset(node->children[idx], 0, sizeof(struct TrieNode));
        }
        node = node->children[idx];
        i++;
    }
    node->count++;
}

int numberOfOccurrences(struct Trie *pTrie, char *word) {
    struct TrieNode *node = pTrie->root;
    int i = 0;
    while (word[i] != '\0' && node != NULL) {
        int idx = word[i] - 'a';
        node = node->children[idx];
        i++;
    }
    if (node != NULL && node->count > 0) {
        return node->count;
    } else {
        return 0;
    }
}

void deallocateTrieNode(struct TrieNode *node) {
    if (node == NULL) {
        return;
    }
  
    // Rescursively delete nodes
    for (int i = 0; i < 26; i++) {
        deallocateTrieNode(node->children[i]);
    }
    free(node);
}

struct Trie *deallocateTrie(struct Trie *pTrie) {
    deallocateTrieNode(pTrie->root);
    free(pTrie);
    return NULL;
}

int main(void) {
    struct Trie *trie = (struct Trie *)malloc(sizeof(struct Trie));
    memset(trie, 0, sizeof(struct Trie));

    // read the number of words in the dictionary
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        char word[101];
        scanf("%s", word);
        insert(&trie, word);
    }

    char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
    for (int i = 0; i < 5; i++) {
        printf("\t%s : %d\n", pWords[i], numberOfOccurrences(trie, pWords[i]));
    }

    trie = deallocateTrie(trie);
    if (trie != NULL) {
        printf("There is an error in this program\n");
    }

    return 0;
}
