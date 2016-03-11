#pragma once
#include <string>
#include <vector>
#include <sstream>
#include "../../dx.h"
#include "../../Utils/string.h"
#include <map>

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
			Utils::String _element;
			std::vector<std::vector<Utils::String>> _values;

			bool __dim( const uint& );
			bool __dim( const uint&, const uint& );
		public:
			StyleElement() = default;

			Utils::String& Name( ) { return _element; }
			Utils::String  Value( const uint& idx, const uint& val_idx_arr );
			bool setValue( const uint& val_idx, const uint& val_idx_arr, const Utils::String& value );
			std::vector<std::vector<Utils::String>>& Array( ) { return _values; };
		};

		class Stylesheet : public Object
		{
		public:
			typedef std::vector<StyleElement> List;
			bool changed_since = true;
			std::map<uint, Color> _map;
		public:
			Stylesheet( const List& types, const Utils::String& );
			Stylesheet() = default;
			

			// E.g the Red of "Style_foreground"
			uint get_value( const Utils::String& element, const uint& val_idx, const uint& val_idx_arr )
			{
				auto values = get_value_str( element, val_idx, val_idx_arr );
				if ( values.empty( ) )
					return uint( );
				if ( values.contains( "0x" ) )
				{
					uint t;
					std::stringstream ss( values.c_str( ) );
					ss >> std::hex >> t;
					return t;
				}
				uint t;
				std::stringstream ss( values.c_str( ) );
				ss >> t;
				return t;
			}

			Color get_argb( const Utils::String& element, const uint& val_idx )
			{
				auto hash = element.hash( ) + ( val_idx * element.length( ) );
				Color argb = Colors::White;

				if ( changed_since )
				{
					argb = D3DCOLOR_ARGB( get_value( element, val_idx, A), get_value( element, val_idx, R ), get_value( element, val_idx, G ), get_value( element, val_idx, B ) );
					_map[hash] = argb;
				}
				return _map[hash];
			}


			Utils::String get_value_str( const Utils::String& element, const uint& val_idx, const uint& val_idx_arr );
			bool set_value( const Utils::String& element, const uint& val_idx, const uint& val_idx_arr, const Utils::String& value );
			Utils::String& getName( ) { return _name; }

		private:
			Utils::String _name;
			List _types;
			friend class Object;
		};



	}
}