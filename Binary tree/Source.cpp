#include <iostream>
#include <string>
#include <locale>
using namespace std;

class TreeNode 
{
public:
    string word;
    string translation;
    int count;
    TreeNode* left;
    TreeNode* right;

    TreeNode(const string& w, const string& t, int c = 0): word(w), translation(t), count(c), left(nullptr), right(nullptr) {}
};

class BinaryTreeDictionary 
{
private:
    TreeNode* root;

    TreeNode* addNode(TreeNode* node, const string& word, const string& translation, int count = 0) 
    {
        if (!node) return new TreeNode(word, translation, count);

        if (word < node->word) 
        {
            node->left = addNode(node->left, word, translation, count);
        }

        else if (word > node->word) 
        {
            node->right = addNode(node->right, word, translation, count);
        }

        else 
        {
            node->translation = translation;
        }

        return node;
    }

    TreeNode* findNode(TreeNode* node, const string& word)
    {
        if (!node || node->word == word) return node;

        if (word < node->word) 
        {
            return findNode(node->left, word);
        }

        else 
        {
            return findNode(node->right, word);
        }
    }

    TreeNode* deleteNode(TreeNode* node, const string& word) 
    {
        if (!node) return nullptr;

        if (word < node->word)
        {
            node->left = deleteNode(node->left, word);
        }

        else if (word > node->word) 
        {
            node->right = deleteNode(node->right, word);
        }
        else 
        {
            if (!node->left)
            {
                TreeNode* temp = node->right;
                delete node;
                return temp;
            }

            else if (!node->right)
            {
                TreeNode* temp = node->left;
                delete node;
                return temp;
            }

            TreeNode* minNode = findMin(node->right);
            node->word = minNode->word;
            node->translation = minNode->translation;
            node->count = minNode->count;
            node->right = deleteNode(node->right, minNode->word);
        }

        return node;
    }

    TreeNode* findMin(TreeNode* node) 
    {
        while (node && node->left)
        {
            node = node->left;
        }

        return node;
    }

    void findMostLeastPopular(TreeNode* node, TreeNode*& mostPopular, TreeNode*& leastPopular) 
    {
        if (!node) return;

        if (!mostPopular || node->count > mostPopular->count) 
        {
            mostPopular = node;
        }

        if (!leastPopular || node->count < leastPopular->count) 
        {
            leastPopular = node;
        }

        findMostLeastPopular(node->left, mostPopular, leastPopular);
        findMostLeastPopular(node->right, mostPopular, leastPopular);
    }

    void deleteTree(TreeNode* node) 
    {
        if (!node) return;
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }

public:
    BinaryTreeDictionary() : root(nullptr) {}

    ~BinaryTreeDictionary() 
    {
        deleteTree(root);
    }

    void addWord(const string& word, const string& translation, int count = 0)
    {
        root = addNode(root, word, translation, count);
    }

    void displayWord(const string& word)
    {
        TreeNode* node = findNode(root, word);
        if (node) 
        {
            node->count++;
            cout << "Word: " << node->word << ", Translation: " << node->translation << ", Count: " << node->count << endl;
        }

        else
        {
            cout << "Word not found." << endl;
        }
    }

    void updateTranslation(const string& word, const string& newTranslation) 
    {
        TreeNode* node = findNode(root, word);
        if (node)
        {
            node->translation = newTranslation;
            cout << "Translation updated." << endl;
        }
        else 
        {
            cout << "Word not found." << endl;
        }
    }

    void deleteWord(const string& word) 
    {
        root = deleteNode(root, word);
    }

    void displayMostPopularWord()
    {
        TreeNode* mostPopular = nullptr;
        TreeNode* leastPopular = nullptr;
        findMostLeastPopular(root, mostPopular, leastPopular);

        if (mostPopular)
        {
            cout << "Most popular word: " << mostPopular->word << ", Translation: " << mostPopular->translation
                << ", Count: " << mostPopular->count << endl;
        }

        else 
        {
            cout << "Dictionary is empty." << endl;
        }
    }

    void displayLeastPopularWord() 
    {
        TreeNode* mostPopular = nullptr;
        TreeNode* leastPopular = nullptr;
        findMostLeastPopular(root, mostPopular, leastPopular);

        if (leastPopular) 
        {
            cout << "Least popular word: " << leastPopular->word << ", Translation: " << leastPopular->translation
                << ", Count: " << leastPopular->count << endl;
        }
        else
        {
            cout << "Dictionary is empty." << endl;
        }
    }
};

int main() 
{
    setlocale(LC_ALL,"Russian");
    BinaryTreeDictionary dictionary;

    dictionary.addWord("hello", "привет", 2);
    dictionary.addWord("world", "мир", 3);
    dictionary.addWord("tree", "дерево", 1);

    dictionary.displayWord("hello");
    dictionary.displayWord("world");

    dictionary.updateTranslation("world", "вселенная");

    dictionary.deleteWord("tree");

    dictionary.displayMostPopularWord();
    dictionary.displayLeastPopularWord();

    return 0;
}