#include <ostream>

namespace ssuds
{
	template <class K, class V>
	class UnorderedMap
	{
	protected:
		// Option2: an array of pair objects and a bool "used" array
		std::pair<K, V>* mTableData;
		bool* mTableUsed;

		// Both
		unsigned int mSize;
		unsigned int mCapacity;
		std::hash<K> mHashGenerator;
	public:
		//will create an iterator class that will step through and take note of any item that currently has something in it.
		//If the item looked at has a mTableUsed of false, it will be ignored as it is empty
		class unorderMapIterator
		{
		protected:
			const std::pair<K, V>* mData;

			const bool* mUsed;

			const unsigned int mCapacity;

			int mPosition;

			unorderMapIterator(int start_index, std::pair<K, V>* Data, bool* Used, unsigned int cap) : mPosition(start_index), mData(Data), mUsed(Used), mCapacity(cap)
			{
				for (unsigned int i = mPosition; i < mCapacity; i++)
				{
					if (mUsed[mPosition] == false)
						++mPosition;
				}
			}
		public:
			friend class UnorderedMap;

			//will return true if the unorderedlist being looked at is equal to the other passed for comparison if they have the same
			//mTableData, mTableUsed, and same index location
			bool operator== (const unorderMapIterator& other) const
			{
				return this->mData == other.mData && this->mUsed == other.mUsed && this->mPosition == other.mPosition;
			}


			//will step forward to the next item of the unordered map that has a mTableUsed = true
			void const operator++()
			{
				++mPosition;
				for (unsigned int i = mPosition; i < mCapacity; i++)
				{
					if (mUsed[mPosition] == false)
						++mPosition;
				}
			}


			//Returns a std::pair<K,V> pointer to the current item being looked at
			std::pair<K,V> const operator*()
			{
				return mData[mPosition];
			}

			//will return false if the unorderedlist being looked at is not equal to the other passed for comparison if they have the different
			//mTableData, mTableUsed, and different index location
			bool const operator!= (const unorderMapIterator& other) const
			{
				return this->mData != other.mData || this->mUsed != other.mUsed || this->mPosition != other.mPosition;
			}
		};


	private:

		//creates a hash code based on the given key
		unsigned long long hashGen(const K& the_key)
		{
			return mHashGenerator(the_key);
		}
	public:
		 
		//points the iterator to the beginning of the unorderedmap
		typename unorderMapIterator begin() 
		{
			return unorderMapIterator(0, this->mTableData, this->mTableUsed, mCapacity); 
		}

		//points the iterator to the end of the unorderedmap
		typename unorderMapIterator end()
		{
			return unorderMapIterator(mCapacity, this -> mTableData, this->mTableUsed, mCapacity);
		}

		//constructor for the unorderedmap class that takes a int capacity as a parameter
		UnorderedMap(int capacity) : mCapacity(capacity)
		{
			mTableData = new std::pair<K, V>[capacity];
			mTableUsed = new bool[capacity];
			for (int i = 0; i < capacity; i++)
				mTableUsed[i] = false;
		}

		//deconstructor for unorderedMap that deletes all items in the class and then sets the size and capacity to 0
		~UnorderedMap()
		{
			delete[]mTableData;
			delete[]mTableUsed;
			mSize = 0;
			mCapacity = 0;
		}
		

		//first creates a hash using hashGen, given the key passed in for the function. it then finds the index location
		//by taking the modulo of hash and mCapacity. If the Size of the current map is 0, it returns the end() of the iterator
		//if it finds a location in the map that uses the index, it returns an iterator object for the indexed location,
		//otherwise it returns the end() iterator
		typename unorderMapIterator find(const K& key)
		{
			unsigned long long int hash = hashGen(key);

			int ind = hash % mCapacity;

			if (mSize == 0)
			{
				return end();
			}
			else
			{
				if (mTableUsed[ind] != false)
				{
					return unorderMapIterator(ind, mTableData, mTableUsed, mCapacity);
				}
				else
				{
					return end();
				}
			}
		}

		//first creates a hash using hashGen, given the key passed in for the function. it then finds the index location
		//by taking the modulo of hash and mCapacity. If the Size of the current map is 0 or the indexed value has a 
		//mTableUsed of false. If truem it will loop through to check to see if the mTableData's first item at that index is the
		//same as the given key, set the used for that index to false and decrease the size and set found to true. Then copy the 
		//map into a temp, and swap it back into the original in the proper index slots
		bool remove(const K& key)
		{
			unsigned long long hash = hashGen(key);

			unsigned long long ind = hash % mCapacity;

			bool found = false;
			if (mSize == 0 || mTableUsed[ind] == false)
			{
				return false;
			}

			for (unsigned int i = 0; i < mCapacity; i++)
			{
				if (mTableUsed[i] == true && mTableData[i].first == key)
				{
					mTableUsed[i] = false;
					mSize--;
					found = true;
				}
			}

			if (found == true)
			{
				UnorderedMap<K, V> temp(mCapacity);
				for (unsigned int i = 0; i < mCapacity; i++)
				{
					if (mTableUsed[i] == true)
					{
						temp.mTableData[i] = mTableData[i];
						temp.mSize++;
					}
					else
					{
						i++;
					}
				}
				std::swap(mTableData, temp.mTableData);
				std::swap(mTableUsed, temp.mTableUsed);
				mSize = temp.mSize;
			}
			else
			{
				return false;
			}
		}

		//when a ostream is used, sets the output to look like, {K1: V1, K2: V2, ... , Kn: Vn}
		friend std::ostream& operator<<(std::ostream& os, const UnorderedMap& M)
		{
			os << "{";

			for (unsigned int i = 0; i < M.capacity(); i++)
			{
				if (M.mTableUsed[i] == true)
				{
					if (i != M.capacity() - 1)
					{
						os << M.mTableData[i].first << ":" << M.mTableData[i].second << ", ";
					}
					else
					{
						os << M.mTableData[i].first << ":" << M.mTableData[i].second ;
					}
				}
				else
				{
					i++;
				}
			}

			os << "}";
			return os;
		}

		//returns the current size of the UnorderedMap
		int size() const
		{
			return mSize;
		}

		//returns the current capacity of the UnorderedMap
		unsigned int capacity() const
		{
			return mCapacity;
		}

		// Take K, generate the hash code using mHashGenerator.
		// Mod the hash code with the table capacity to get desired spot
		// possibly loop until we either find an "empty" spot or a pair
		// with the_key.  Then...

		// If we found an empty spot, make a new key-value pair
		// with the given key and an UNINITIALIZED value and return a reference to that new value.

		// If we found a non-empty spot, return the value of the existing pair
		V& operator[](const K& the_key)
		{
			unsigned long long hash = hashGen(the_key);

			unsigned long long ind = hash % mCapacity;
			for (unsigned int i = 0; i < mCapacity; i++)
			{
				if (mTableUsed[ind] == true)
				{
					if (mTableData[ind].first == the_key)
					{
						return mTableData[ind].second;
					}
					
					else if (ind < mCapacity)
					{
						ind++;
					}
					else
					{
						ind = 0;
					}
				}
				else if (mTableUsed[ind] == false)
				{
					mTableData[ind].first = the_key;
					mSize++;
					mTableUsed[ind] = true;
					return mTableData[ind].second;
				}
			}
			
		}
	};
}
