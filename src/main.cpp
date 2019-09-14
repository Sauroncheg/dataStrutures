#include "Trie.hh"

void print(Trie<SmallLetters, int>* root, const std::string& name) {
	auto it = root->search(name);
	try {
		std::cout << it.value() << '\n';
	}
	catch (const std::bad_optional_access& e) {
		std::cout << e.what() << "\n";
	}
}

int main() {
	auto* root = new Trie<SmallLetters, int>;
	root->insert("geeks", 1);
	root->insert("for", 1);
	print(root, "geeks");

	root->insert("for", 2);
	print(root, "for");

	print(root, "greeks");
	
	root->insert("gee", 1);
	print(root, "gee");
	print(root, "geeks");
	return 0;
}