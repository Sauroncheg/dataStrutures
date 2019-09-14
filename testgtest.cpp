#include <iostream>
#include "CollapsedTrie.hh"
#include "gtest/gtest.h"

TEST(sample_test_case, sample_test) {
	auto* root = new CollapsedTrie<SmallLetters, int>;
	std::optional<int> it;
	root->insert("geeks", 1);
	root->insert("for", 1);
	it = root->search("geeks");
	EXPECT_EQ(it, 1);
	
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
}

TEST(sample_test_case, data) {
	auto* root = new CollapsedTrie<SmallLetters, int>;
	std::vector<std::string> vec = {
		"condemnation","gutter","enzyme","cocktail","respondent","tracker","exchange","contingent",
		"intermission","darling","interrogator","landing","chart","stockpile","commander","program",
		"fillet","dud","mink","snowstorm","sandwich","sole","cleanser","tubing","pineapple","discrimination",
		"traffic","tic","bulimia","presence","place","setup","streetlight","drift","championship","atbat",
		"wrench","asterisk","profiling","meatball","aviator","storm","doubling","pastime","mysticism","crowd",
		"pc","whiff","throwback","version","vacancy","mustard","daughter","diving","conspiracy","upside","designer",
		"doctor","transfusion","restitution","stool","angler","preface","quality","bowler","afternoon","sweat","end",
		"trek","lilac","emphasis","jockey","brain","fence","looter","binoculars","nutrient","juniper","merchant",
		"federalism","stretcher","ethics","periodical","knot","repellent","critter","model","biosolids","section",
		"colonizer","newsman","quiver","liquidity","urgency","hormone","graveyard","filipino","applause","forest","dietitian"
	};

	int i = 0;
	for (const auto& str : vec) {
		i++;
		root->insert(str, i);
	}

	i = 0;
	for (const auto& str : vec) {
		i++;

		EXPECT_EQ(i, root->search(str));
	}
}