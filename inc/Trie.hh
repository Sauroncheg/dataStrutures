// A memory optimized CPP implementation of trie 
// using unordered_map 
#include <iostream> 
#include <unordered_map> 
#include <array>
#include <optional>

using namespace std;

struct SmallLetters {
	static const int itemCount = 26;

	static int hash(const char x) {
		return x - 'a';
	}
};

template <class Logic, class Item>
class Trie {
	// isEndOfWord is true if the node 
	// represents end of a word 
	std::optional<Item> isEndOfWord{};

	Logic logic;

	/* nodes store a map to child node */
	std::array<Trie*, Logic::itemCount> map{};

	/*function to make a new trie*/
	Trie* getNewTrieNode() {
		Trie* node = new Trie;
		return node;
	}
public:
	/*function to insert in trie*/
	void insert(const string& str, Item item) {
		Trie* temp = this;
		for (unsigned i = 0; i < str.length(); i++) {
			char x = str[i];

			/* make a new node if there is no path */
			if (!temp->map[logic.hash(x)])
				temp->map[logic.hash(x)] = getNewTrieNode();

			temp = temp->map[logic.hash(x)];
		}

		temp->isEndOfWord.emplace(item);
	}

	/*function to search in trie*/
	std::optional<Item> search(const string& str) {
		Trie* temp = this;
		for (unsigned i = 0; i < str.length(); i++) {

			/* go to next node*/
			temp = temp->map[logic.hash(str[i])];

			if (temp == nullptr)
				return {};
		}
		return temp->isEndOfWord;
	}
};