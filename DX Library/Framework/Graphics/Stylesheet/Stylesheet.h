#pragma once
#include <string>
#include <vector>
#include <sstream>
#include "../../dx.h"
#include "../../Utils/string.h"

namespace Graphics {
	namespace Style {

		static const uint Style_foreground = 0;
		static const uint Style_line = 1;
		static const uint Style_text = 2;
		static const uint Style_extra = 3;
		static const uint Style_glow = 3;
		static const uint A = 0;
		static const uint R = 1;
		static const uint G = 2;
		static const uint B = 3;

		class StyleElement
		{
		private:
			std::string _element;
			std::vector<std::vector<std::string>> _values;

			bool __dim( const uint& );
			bool __dim( const uint&, const uint& );
		public:
			StyleElement() = default;

			std::string& Name( ) { return _element; }
			std::string  Value( const uint& idx, const uint& val_idx_arr );
			bool setValue( const uint& val_idx, const uint& val_idx_arr, const std::string& value );
			std::vector<std::vector<std::string>>& Array( ) { return _values; };
		};

		class Stylesheet : public Object
		{
		public:
			typedef std::vector<StyleElement> List;

		public:
			Stylesheet( const List& types, const Utils::String& );
			Stylesheet() = default;
			

			// E.g the Red of "Style_foreground"
			uint get_value( const std::string& element, const uint& val_idx, const uint& val_idx_arr )
			{
				auto values = get_value_str( element, val_idx, val_idx_arr );
				if ( values.empty( ) )
					return uint( );
				if ( values.find( "0x" ) != values.npos )
				{
					uint t;
					std::stringstream ss( values );
					ss >> std::hex >> t;
					return t;
				}
				uint t;
				std::stringstream ss( values );
				ss >> t;
				return t;
			}

			Color get_argb( const std::string& element, const uint& val_idx )
			{
				return D3DCOLOR_ARGB( get_value( element, val_idx, A), get_value(element, val_idx, R), get_value(element, val_idx, G), get_value(element, val_idx, B) );
			}


			std::string get_value_str( const std::string& element, const uint& val_idx, const uint& val_idx_arr );
			bool set_value( const std::string& element, const uint& val_idx, const uint& val_idx_arr, const std::string& value );
			Utils::String& getName( ) { return _name; }

		private:
			Utils::String _name;
			List _types;
			friend class Object;
		};



	}
}