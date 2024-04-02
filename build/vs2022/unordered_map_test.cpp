#include <gtest/gtest.h>
#include <unordered_map.h>
#include <sstream>
#include <ostream>

#define DO_UNORDERED_MAP_TESTS 1
#if DO_UNORDERED_MAP_TESTS


TEST(UnorderedTest, basic_construction)
{
	ssuds::UnorderedMap<std::string, int> map(10);

	map["Bob"] = 7;
	map["Sue"] = 1;
	map["Jose"] = 4;

	map["Bob"] = 9;

	EXPECT_EQ(map.size(), 3);
	EXPECT_EQ(map.capacity(), 10);

	EXPECT_TRUE(map.remove("Bob"));
	EXPECT_EQ(map.size(), 2);


	EXPECT_NO_THROW(map.find("Sue"));
}

TEST(UnorderedTest, Iterator)
{
	ssuds::UnorderedMap<std::string, int> map(10);

	map["Bob"] = 7;
	map["Sue"] = 1;
	map["Jose"] = 4;

	ssuds::UnorderedMap<std::string, int>::unorderMapIterator it = map.begin();
	while (it != map.end())
	{
		std::pair<std::string, int> p = *it;
		std::cout << p.first << "\t" << p.second << std::endl;
		++it;
	}
}

TEST(UnorderedTest, ostream)
{
	ssuds::UnorderedMap<std::string, int> map(10);

	map["Bob"] = 7;
	map["Sue"] = 1;
	map["Jose"] = 4;

	std::cout << map;
}

#endif