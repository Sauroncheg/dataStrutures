// A memory optimized CPP implementation of trie 
#pragma once
#include <iostream> 
#include <unordered_map> 
#include <array>
#include <optional>
#include <algorithm>

using namespace std;

struct SmallLetters {
	static const int itemCount = 26;

	static int hash(const char x) {
		return x - 'a';
	}

//	static char rHash(const int x) {
//		return x + 'a';
//	}
};

template <class ValueType, class Logic>
class CollapsedTrie {
	// value is true if the node 
	// represents end of a word 
	std::optional<ValueType> value{};

	std::string longKey;

	/* nodes store a map to child node */
	std::array<CollapsedTrie*, Logic::itemCount> map{};

	/*function to make a new trie*/
	CollapsedTrie* getNewTrieNode() {
		auto* node = new CollapsedTrie;
		return node;
	}

	void separate(const string_view& _str, ValueType item, CollapsedTrie* curItem, int substrbegin, int substrofset) {
		std::string temp = curItem->longKey;
		curItem->longKey = temp.substr(0, substrofset);
		auto* it = new CollapsedTrie;
		it->longKey = temp.substr(substrofset + 1);
		it->map.swap(curItem->map);
		it->value.swap(curItem->value);
		curItem->map[Logic::hash(temp[substrofset])] = it;
		if (_str.size() > substrbegin + substrofset) {
			auto& i = curItem->map[Logic::hash(_str[substrbegin + substrofset])] = getNewTrieNode();
			i->longKey = _str.substr(substrbegin + substrofset + 1);
			i->value = item;
		} else {
			curItem->value.emplace(item);
		}
	}

public: 
	~CollapsedTrie() {
		for (auto* it : map) {
			if (it)
				delete it;
		}
	}

	/*function to insert in trie*/
	void insert(const string_view& _str, ValueType item) {
		std::string_view str(_str);
		CollapsedTrie* temp = this;
		for (auto i = 0u; i < str.length(); i++) {
			if (!temp->longKey.empty()) {
				// it's starts with longKey for str 
				for (int j = 0; j < temp->longKey.size(); j++) {
					if (i + j == _str.size() || temp->longKey[j] != _str[i + j])
						return separate( _str, item, temp, i, j);
				}
				i += temp->longKey.size();
				if (i == _str.size())
					break;
			}

			/* make a new node if there is no path */
			if (std::all_of(temp->map.begin(), temp->map.end(), [](CollapsedTrie* i) {return !i;})) {
				if (temp->longKey.empty()) {
					temp->longKey = _str.substr(i);
					temp->value.emplace(item);
					return;
				}
			}
			if (!temp->map[Logic::hash(str[i])]) {
				temp->map[Logic::hash(str[i])] = getNewTrieNode();
			}

			temp = temp->map[Logic::hash(str[i])];
		}
		temp->value.emplace(item);
	}

	/*function to search in trie*/
	std::optional<ValueType> search(const string& _str) {
		std::string_view str(_str);
		auto* temp = this;
		for (unsigned i = 0; i < str.length(); i++) {
			if (temp->longKey.empty()) {
				/* go to next node*/
				temp = temp->map[Logic::hash(str[i])];

				if (temp == nullptr)
					return {};
			} else {
				// it's starts with longKey for str 
				for (int j = 0; j < temp->longKey.size(); j++) {
					if (temp->longKey[j] != _str[i + j])
						return {};
				}
				i += temp->longKey.size();
				if (i >= _str.size())
					break;

				temp = temp->map[Logic::hash(str[i])];

				if (temp == nullptr)
					return {};
			}
		}
		return temp->value;
	}
};
