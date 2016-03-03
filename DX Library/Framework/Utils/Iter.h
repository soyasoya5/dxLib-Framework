#pragma once


namespace Utils {

	template<typename Px>
	class Iterator
	{
	private:
		template<typename Px>
		friend Iterator<Px> CreateIterator(Px*, size_t, size_t);
		Px* _arr;
		size_t _len;
		size_t _count;

	public:
		Iterator() : _arr(nullptr), _count(0), _len(0) {}
		Px* get()
		{
			return reinterpret_cast<Px*>(_arr + _count);
		}
		const size_t& length()
		{
			return _len;
		}
		const size_t& index()
		{
			return _count;
		}
	public: // Operators
		template<typename off_t>
		Iterator<Px> operator-(const off_t& off)
		{
			static_assert(!std::is_arithmetic<off_t>::value, "off_t must be arithmetic");
			return (CreateIterator(_arr, _len, _count - off));
		}
		template<typename off_t>
		Iterator<Px> operator+(const off_t& off)
		{
			static_assert(std::is_arithmetic<off_t>::value, "off_t must be arithmetic");
			return (CreateIterator(_arr, _len, _count + off));
		}
		template<typename off_t>
		Iterator<Px>& operator+=(const off_t& off)
		{
			static_assert(!std::is_arithmetic<off_t>::value, "off_t must be arithmetic");
			this->index() += off;
			return (*this);
		}
		template<typename off_t>
		Iterator<Px>& operator-=(const off_t& off)
		{
			static_assert(!std::is_arithmetic<off_t>::value, "off_t must be arithmetic");
			this->index() -= off;
			return (*this);
		}
		Px& operator*()
		{
			return (_arr[_count]);
		};
		Px* operator->()
		{
			return get();
		}
		bool operator++()
		{
			if (_count >= _len)
				return false;
			++_count;
			return true;
		}
		bool operator--()
		{
			if (_count <= 0)
				return false;
			--_count;
			return true;
		}
		bool operator==(const Iterator<Px>& lhs) const
		{
			return (this->_arr + _count) == (lhs._arr + lhs._count);
		}
		bool operator!=(const Iterator<Px>& lhs) const
		{
			return !operator==(lhs);
		}
		bool operator>(const Iterator<Px>& lhs) const
		{
			return (this->_count > lhs._count);
		}
		bool operator>=(const Iterator<Px>& lhs) const
		{
			return (this->_count >= lhs._count);
		}
		bool operator<(const Iterator<Px>& lhs) const
		{
			return (this->_count < lhs._count);
		}
		bool operator<=(const Iterator<Px>& lhs) const
		{
			return (this->_count <= lhs._count);
		}
		Iterator<Px> operator[](const size_t& off)
		{
			return CreateIterator(_arr, _count, off);
		}
	};

	template<typename Px>
	class ReverseIterator
	{
		template<typename Px>
		friend ReverseIterator<Px> CreateReverseIterator(Px*, size_t, size_t);
		Px* _arr;
		size_t _len;
		size_t _count;

	public:
		ReverseIterator() : _arr(nullptr), _count(0), _len(0) {}
		Px* get()
		{
			return reinterpret_cast<Px*>(_arr + (_len - 1) - _count);
		}
		const size_t& length()
		{
			return _len;
		}
		const size_t& index()
		{
			return _count;
		}
	public: // Operators
		ReverseIterator<Px> operator-(const size_t& off)
		{
			return (CreateReverseIterator(_arr, _len, _count - off));
		}
		ReverseIterator<Px> operator+(const size_t& off)
		{
			return (CreateReverseIterator(_arr, _len, _count + off));
		}
		ReverseIterator<Px>& operator+=(const size_t& off)
		{
			this->index() += off;
			return (*this);
		}
		ReverseIterator<Px>& operator-=(const size_t& off)
		{
			this->index() -= off;
			return (*this);
		}
		Px& operator*()
		{
			return *get();
		};
		Px* operator->()
		{
			return get();
		}
		bool operator++()
		{
			if (_count >= _len)
				return false;
			++_count;
			return true;
		}
		bool operator--()
		{
			if (_count <= 0)
				return false;
			--_count;
			return true;
		}
		bool operator==(const ReverseIterator<Px>& other) const
		{
			return (this->_arr + _len - _count) == (other._arr + other._len - other._count);
		}
		bool operator!=(const ReverseIterator<Px>& other) const
		{
			return !operator==(other);
		}
		bool operator>(const Iterator<Px>& lhs) const
		{
			return (this->_count > lhs._count);
		}
		bool operator>=(const Iterator<Px>& lhs) const
		{
			return (this->_count >= lhs._count);
		}
		bool operator<(const Iterator<Px>& lhs) const
		{
			return (this->_count < lhs._count);
		}
		bool operator<=(const Iterator<Px>& lhs) const
		{
			return (this->_count <= lhs._count);
		}
		ReverseIterator<Px> operator[](const size_t& off)
		{
			return CreateReverseIterator(_arr, _count, off);
		}
	};


	template<typename Px>
	static Iterator<Px> CreateIterator(Px* array = nullptr, size_t length = 0, size_t offset = 0)
	{
		Iterator<Px> iter;
		iter._arr = array;
		iter._len = length;
		iter._count = offset;
		return (iter);
	}
	template<typename Px>
	static ReverseIterator<Px> CreateReverseIterator(Px* array = nullptr, size_t length = 0, size_t offset = 0)
	{
		ReverseIterator<Px> iter;
		iter._arr = array;
		iter._len = length;
		iter._count = offset;
		return (iter);
	}
}
