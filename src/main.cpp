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
	UM.size();
	//    are changing the value from 7 to 8).
	std::cout << UM["Bob"] << "\n";			// 8
	std::cout << UM["Sue"] << "\n";			// 3
	std::cout << UM["I'm not here"] << "\n";// ???

	std::cout << UM;
}




/*int main()
{
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}*/