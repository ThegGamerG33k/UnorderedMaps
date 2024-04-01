#include <ostream>

namespace ssuds
{
	template <class K, class V>
	class UnorderedMap
	{
	protected:
		// Option2: an array of pair objects and a bool "used" array (better cache
		//     coherency??)
		std::pair<K, V>* mTableData;
		bool* mTableUsed;

		// Both
		unsigned int mSize;
		unsigned int mCapacity;
		std::hash<K> mHashGenerator;
	public:
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

			bool operator== (const unorderMapIterator& other) const
			{
				return this->mData == other.mData && this->mUsed == other.mUsed && this->mPosition == other.mPosition;
			}

			void const operator++()
			{
				++mPosition;
				for (unsigned int i = mPosition; i < mCapacity; i++)
				{
					if (mUsed[mPosition] == false)
						++mPosition;
				}
			}

			std::pair<K,V> const operator*()
			{
				return mData[mPosition];
			}

			bool const operator!= (const unorderMapIterator& other) const
			{
				return this->mData != other.mData || this->mUsed != other.mUsed || this->mPosition != other.mPosition;
			}
		};


	private:
		unsigned long long hashGen(const K& the_key)
		{
			return mHashGenerator(the_key);
		}
	public:
		 
		typename unorderMapIterator begin() 
		{
			return unorderMapIterator(0, this->mTableData, this->mTableUsed, mCapacity); 
		}

		typename unorderMapIterator end()
		{
			return unorderMapIterator(mCapacity, this -> mTableData, this->mTableUsed, mCapacity);
		}

		UnorderedMap(int capacity) : mCapacity(capacity)
		{
			mTableData = new std::pair<K, V>[capacity];
			mTableUsed = new bool[capacity];
			for (int i = 0; i < capacity; i++)
				mTableUsed[i] = false;
		}

		~UnorderedMap()
		{
			delete[]mTableData;
			delete[]mTableUsed;
			mSize = 0;
			mCapacity = 0;
		}
		
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

		/*bool remove(const K& key)
		{
			unsigned long long hash = hashGen(the_key);

			unsigned long long ind = hash % mCapacity;
			if (mSize == 0)
			{
				return false;
			}
			else
			{
				for (int i = ; i < mCapacity; i++)
					if mTableData[i] == ind
					{
						delete(mTableData[i]);
						mSize--;
						return true;
					}
				return false;
			}
		}*/

		friend std::ostream& operator<<(std::ostream& os, const UnorderedMap& M)
		{
			os << "{";

			for (unsigned int i = 0; i < M.capacity(); i++)
			{
				if (M.mTableUsed[i] == true)
				{
					if (i = M.capacity() - 1)
					{
						os << M.mTableData[i].first << ":" << M.mTableData[i].second;
					}
					else
					{
						os << M.mTableData[i].first << ":" << M.mTableData[i].second << ", ";
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

		int size() const
		{
			return mSize;
		}

		unsigned int capacity() const
		{
			return mCapacity;
		}

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
			// Take K, generate the hash code using mHashGenerator.
			// Mod the hash code with the table capacity to get desired spot
			// possibly loop until we either find an "empty" spot or a pair
			// with the_key.  Then...

			// If we found an empty spot, make a new key-value pair
			// with the given key and an UNINITIALIZED value and return a reference to that new value.

			// If we found a non-empty spot, return the value of the existing pair
		}
	};
}
