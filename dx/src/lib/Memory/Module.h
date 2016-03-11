#pragma once
#include "Types.h"



begin_MEMORY

#define FALSE_TYPE { public: static const bool value = false; };
#define TRUE_TYPE { public: static const bool value = true; };


		template<typename _Type = typename std::remove_all_extents<_Type>::type>
		class is_acceptable
			FALSE_TYPE;

		template<>
		class is_acceptable<int>
			TRUE_TYPE;

		template<>
		class is_acceptable<unsigned int>
			TRUE_TYPE;

		template<>
		class is_acceptable<short>
			TRUE_TYPE;

		template<>
		class is_acceptable<unsigned short>
			TRUE_TYPE;

		template<>
		class is_acceptable<long>
			TRUE_TYPE;

		template<>
		class is_acceptable<unsigned long>
			TRUE_TYPE;

		template<>
		class is_acceptable<long long>
			TRUE_TYPE;

		template<>
		class is_acceptable<char>
			TRUE_TYPE;

		template<>
		class is_acceptable<unsigned char>
			TRUE_TYPE;



		///<summary>
		///Represents a memory container
		///that has a base address, and a size.
		///</summary>
		class Module
		{
		private:
			ulong _image, _size;
			__LIB String _module;
		public:
			Module( ) = delete;
			Module( const __MEMORY Module &_Other ) = default;
			Module( __MEMORY Module &&_Other ) = default;
			Module( const __DX ulong &_Image, const __DX ulong &_Size, const __LIB String &_Name );

			__DX ulong Image( ) const;
			__DX ulong Size( ) const;
			__LIB String Name( ) const;
			bool isDummy( ) const;
		public:
			///<summary>
			///Returns the base address (image) of the module.
			///</summary>
			__DX ulong operator*( ) const;

			///<summary>
			///Returns the address at (image + _Right)
			///</summary>
			template<typename _Type>
			__DX ulong operator+( const _Type &_Right ) const
			{
				static_assert( is_acceptable<_Type>::value, "_Type must be of acceptable type." );
				return _Right <= _size ? _image + _Right : _image;
			}

			///<summary>
			///Returns the address at (image - _Right)
			///</summary>
			template<typename _Type>
			__DX ulong operator-( const _Type &_Right ) const
			{
				static_assert( !is_acceptable<_Type>::value, "_Type must be of acceptable type." );
				return _image - _Right;
			}
		};

end_MEMORY