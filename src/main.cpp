#include <gtest/gtest.h>
#include <unordered_map.h>
#include <string>

int main()
{
	ssuds::UnorderedMap<std::string, int> UM(10);
	UM["Bob"] = 7;		// We get back from the [] operator a pair with the value uninitialized.  WE (main
	//    program) are setting the value to 7
	UM["Sue"] = 3;		// Same, but setting the value to 3.
	UM["Bob"] = 8;		// Changing, not adding.  We're getting back the CURRENT key-value pair, WE (main program
	//UM.size();
	//    are changing the value from 7 to 8).
	/*std::cout << UM["Bob"] << "\n";			// 8
	std::cout << UM["Sue"] << "\n";			// 3
	std::cout << UM["I'm not here"] << "\n";// ???

	std::cout << UM;*/

	ssuds::UnorderedMap<std::string, int>::unorderMapIterator it = UM.begin();
	while (it != UM.end())
	{
		std::pair<std::string, int> p = *it;
		std::cout << p.first << "\t" << p.second << std::endl;
		++it;
	}
	/*for (std::string test_str : {"Bob", "Sue", "Joe", "Xavier"})
	{
		ssuds::UnorderedMap<std::string, int>::unorderMapIterator iter = test_map.find(test_str);
		if (iter == test_map.end())
			std::cout << "test_map does NOT contain " << test_str << std::endl;
		else
			std::cout << "test_map DOES contain " << test_str << std::endl;
	}*/
}




/*int main()
{
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}*/