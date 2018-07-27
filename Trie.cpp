/**
 This is free and unencumbered software released into the public domain.
 

 See the included UNLICENSE file, or http://unlicense.org/
 */

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

class TrieNode
{
  private:
    /* Variables */
    char data = '\0';
    std::size_t count = 1;
    bool isEndOfWord = false;
    std::vector<TrieNode> children;

  public:
    /* Constructors */
    TrieNode() {}
    TrieNode(char _data) : data(_data) {}

    /* Functions */
    void add(std::string input);
    char getData() const { return data; }
    std::size_t findPrefix(std::string input);
    std::string search(std::string input);
};

/** 
 * @brief  Trie -- Add word to Trie
 * @note   Children would be sorted each time a word is added
 * @param  input: String need to be added to Trie
 * @retval None
 */

void TrieNode::add(std::string input)
{
    TrieNode *node = this;

    for (const char &ch : input)
    {
        bool foundInChild = false;
        for (auto &child : node->children)
            if (child.data == ch)
            {
                ++child.count;
                node = &child;
                foundInChild = true;
                break;
            }

        if (!foundInChild)
        {
            node->children.push_back(TrieNode(ch));
            TrieNode *next_node = &(*node->children.rbegin());
            std::sort(
                node->children.begin(),
                node->children.end(),
                [](const TrieNode &trie1, const TrieNode &trie2) {
                    return trie1.data < trie2.data;
                });
            node = next_node;
        }
    }

    node->isEndOfWord = true;
}

/** 
 * @brief  Trie -- Find number of words with given prefix 
 * @note   
 * @param  input: prefix string
 * @retval Number of words match the prefix
 */

std::size_t TrieNode::findPrefix(std::string input)
{
    TrieNode *node = this;

    if (this->children.empty())
        return 0;

    for (const auto &ch : input)
    {
        bool not_found = true;
        for (auto &child : node->children)
            if (child.data == ch)
            {
                not_found = false;
                node = &child;
                break;
            }
        if (not_found)
            return 0;
    }

    return node->count;
}

/** 
 * @brief  Trie -- Search for words in Trie
 * @note   The return string would be chosen alphabetically
 * @param  input: Search string
 * @retval Search result
 */

std::string TrieNode::search(std::string input)
{
    TrieNode *node = this;
    std::string str;

    if (this->children.empty())
        return str;
    for (const auto &ch : input)
    {
        bool not_found = true;
        for (auto &child : node->children)
            if (child.data == ch)
            {
                not_found = false;
                str += ch;
                node = &child;
                break;
            }
        if (not_found)
            break;
    }

    while (!node->isEndOfWord)
    {
        node = &(*node->children.begin());
        str += node->data;
    }
    return str;
}

int main()
{
    TrieNode trie;
    int dictQuery;
    std::cin >> dictQuery;
    for (int i = 0; i < dictQuery; ++i)
    {
        std::string word;
        std::cin >> word;
        trie.add(word);
    }

    int actions;
    std::cin >> actions;
    for (int i = 0; i < actions; ++i)
    {
        int num;
        std::string str;
        std::cin >> num >> str;

        if (num == 1)
            /* Find Prefix */
            std::cout << trie.findPrefix(str) << '\n';
        if (num == 2)
            /* Search */
            std::cout << trie.search(str) << '\n';
    }

    return 0;
}
