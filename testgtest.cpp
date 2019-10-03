#include <iostream>
#include "Trie.hh"
#include "CollapsedTrie.hh"
#include "gtest/gtest.h"

// just slova
//std::vector<std::string> vec1 = {
//	"condemnation","gutter","enzyme","cocktail","respondent","tracker","exchange","contingent",
//	"intermission","darling","interrogator","landing","chart","stockpile","commander","program",
//	"fillet","dud","mink","snowstorm","sandwich","sole","cleanser","tubing","pineapple","discrimination",
//	"traffic","tic","bulimia","presence","place","setup","streetlight","drift","championship","atbat",
//	"wrench","asterisk","profiling","meatball","aviator","storm","doubling","pastime","mysticism","crowd",
//	"pc","whiff","throwback","version","vacancy","mustard","daughter","diving","conspiracy","upside","designer",
//	"doctor","transfusion","restitution","stool","angler","preface","quality","bowler","afternoon","sweat","end",
//	"trek","lilac","emphasis","jockey","brain","fence","looter","binoculars","nutrient","juniper","merchant",
//	"federalism","stretcher","ethics","periodical","knot","repellent","critter","model","biosolids","section",
//	"colonizer","newsman","quiver","liquidity","urgency","hormone","graveyard","filipino","applause","forest","dietitian"
//};

#define suf "1m"

#include <fstream>
#include <string>

class TestEnvironment : public ::testing::Environment {
public:
	// Assume there's only going to be a single instance of this class, so we can just
	// hold the timestamp as a const static local variable and expose it through a
	// static member function
	static void init_vec() {
		std::fstream file;
		file.open(std::string("asd") + suf + ".txt", std::fstream::in);
		if (!file.is_open())
			throw(new std::exception);
		std::string in;
		while (std::getline(file, in)) {
			if (!in.empty())
				vec.push_back(in);
		}
	}

	static std::vector<std::string> vec;

	// Initialise the timestamp.
	virtual void SetUp() {
		init_vec();
	}
};

std::vector<std::string> TestEnvironment::vec;

TEST(sample_test_case, sample_test) {
	auto* root = new CollapsedTrie<int, SmallLetters>;
	std::optional<int> it;
	root->insert("geeks", 1);
	root->insert("for", 1);
	it = root->search("geeks");
	EXPECT_EQ(it, 1);
	it = root->search("gee");
	EXPECT_EQ(it, std::nullopt);
	
	root->insert("for", 2);
	it = root->search("for");
	EXPECT_EQ(it, 2);

	it = root->search("greeks");
	EXPECT_EQ(it, std::nullopt);

	root->insert("gee", 1);
	it = root->search("gee");
	EXPECT_EQ(it, 1);
	it = root->search("geeks");
	EXPECT_EQ(it, 1);

	root->insert("geekss", 2);
	it = root->search("geeks");
	EXPECT_EQ(it, 1);
}

TEST(sample_test_case, data) {
	auto* root = new CollapsedTrie<int, SmallLetters>;
	for (int j = 0; j < 1; j++) {
		int i = 0;
		for (const auto& str : TestEnvironment::vec) {
			i++;
			root->insert(str, i);
		}
	}

	for (int j = 0; j < 1; j++) {
		int i = 0;
		for (const auto& str : TestEnvironment::vec) {
			i++;

			EXPECT_EQ(i, root->search(str));
		}
	}
}

TEST(sample_test_case, data1) {
	std::map<std::string, int> root;

	for (int j = 0; j < 1; j++) {
		int i = 0;
		for (const auto& str : TestEnvironment::vec) {
			i++;
			root[str] = i;
		}
	}
	
	for (int j = 0; j < 1; j++) {
		int i = 0;
		for (const auto& str : TestEnvironment::vec) {
			i++;

			EXPECT_EQ(i, root.find(str)->second);
		}
	}
}

int main(int argc, char* argv[]) {
	::testing::InitGoogleTest(&argc, argv);
	// gtest takes ownership of the TestEnvironment ptr - we don't delete it.
	::testing::AddGlobalTestEnvironment(new TestEnvironment);
	return RUN_ALL_TESTS();
}