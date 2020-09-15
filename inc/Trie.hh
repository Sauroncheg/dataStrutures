// A memory optimized CPP implementation of trie 
#pragma once
#include <iostream> 
#include <array>
#include <optional>
#include <vector>

//using std::vector;
using namespace std;

template <class ValueType, class Logic>
class Trie {
	vector<string> a;
	// value is true if the node 
	// represents end of a word 
	std::optional<ValueType> value{};
	//TODO: when finish iterator work
	//Trie* parent = nullptr;

	/* nodes store a map to child node */
	std::array<std::unique_ptr<Trie>, Logic::itemCount> map{};
public:

	//TODO: when finish iterator work
	//class Iterator : public std::iterator<std::bidirectional_iterator_tag, ValueType> {
	//public:
	//	std::string _key;
	//	const std::string& key() {
	//		return _key;
	//	}

	//	std::optional<ValueType>& value() {
	//		return _value->value;
	//	}

	//	Trie* _value;

	//	bool operator==(const Iterator& cmp) const {
	//		return this->_key == cmp._key;
	//	}

	//	//Iterator operator++(int) {

	//	//}

	//	Iterator& operator++() {
	//		Trie* temp = this;
	//		while (!temp->value.has_value()) {
	//			int i = 0;
	//			for (int j = 0; j <  ) {
	//				if (item) {
	//					return_val._key.push_back(Logic::rHash(i));
	//					temp = temp->map[i].get();
	//					break;
	//				}
	//				++i;
	//			}
	//			if (i >= Logic::itemCount)
	//				return _end;
	//		}
	//		return_val._value = temp;
	//		return *this;
	//	}

	//	std::pair<const std::string&, std::optional<ValueType>&> operator*() {
	//		return { _key, _value->value };
	//	}

	//	bool operator!=(const Iterator& cmp) const {
	//		return !(*this == cmp);
	//	}
	//};
	//Iterator _end{};

	//Iterator begin() {
	//	Iterator return_val;
	//	Trie* temp = this;
	//	while (!temp->value.has_value()) {
	//		int i = 0;
	//		for (auto& item : temp->map) {
	//			if (item) {
	//				return_val._key.push_back(Logic::rHash(i));
	//				temp = item.get();
	//				break;
	//			}
	//			++i;
	//		}
	//	}
	//	return_val._value = temp;
	//	return return_val;
	//}

	//Iterator end() {
	//	return _end;
	//}

	vector<string> return_value;
	void get_items(Trie* node = nullptr, const string& prefix = "") {
		if (!node)
			node = this;
		if (node->value)
			return_value.push_back(prefix);

		int  i = 0;
		for (const auto& x : node->map) {
			if (x) {
				get_items(x.get(), prefix + (char)('a' + i));
			}
			i++;
		}
	}


	std::vector<string> starts_with(const string& prefix) {
		Trie* temp = this;
		for (const auto& x : prefix) {
			/* go to next node*/
			temp = temp->map[Logic::hash(x)].get();

			if (temp == nullptr)
				return {};
		}
		get_items(temp, prefix);
		return return_value;
	}

	/*function to insert in trie*/
	void insert(const string& key, ValueType value) {
		Trie* temp = this;
		for (const auto& x : key) {
			/* make a new node if there is no path */
			auto& item = temp->map[Logic::hash(x)];
			if (item == nullptr)
				item.reset(new Trie);
			//item->parent = temp;
			temp = item.get();
		}

		temp->value.emplace(value);
	}

	/*function to search in trie*/
	std::optional<ValueType> search(const string& key) {
		Trie* temp = this;
		for (auto x : key) {
			/* go to next node*/
			temp = temp->map[Logic::hash(x)].get();

			if (temp == nullptr)
				return std::nullopt;
		}
		return temp->value;
	}
};