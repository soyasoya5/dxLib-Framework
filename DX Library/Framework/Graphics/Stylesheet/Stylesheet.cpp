#include "Stylesheet.h"

namespace Graphics {
	namespace Style {

		bool StyleElement::__dim(const uint &idx)
		{
			if (idx <= _values.size() && idx >= 0)
				return true;
			return false;
		}

		bool StyleElement::__dim(const uint &pos, const uint &pos2)
		{
			return __dim( pos ) && ( pos2 <= _values[pos].size( ) && pos2 >= 0 );
		}

		std::string StyleElement::Value(const uint & val_idx, const uint & val_idx_arr)
		{
			if ( !__dim( val_idx, val_idx_arr ) )
				return "";
			return _values[val_idx][val_idx_arr];
		}

		bool StyleElement::setValue(const uint & val_idx, const uint & val_idx_arr, const std::string & value)
		{
			if ( !__dim( val_idx, val_idx_arr ) )
				return false;
			_values[val_idx][val_idx_arr] = value;
			return true;
		}


		Stylesheet::Stylesheet(const List & types, const Utils::String& name)
		{
			_types = types;
			_name = name;
		}

	
		std::string Stylesheet::get_value_str(const std::string & element, const uint & val_idx, const uint & val_idx_arr)
		{
			for ( auto&x : _types )
			{
				if ( x.Name( ) == element)
					return x.Value( val_idx, val_idx_arr );
			}
			return "";
		}

		bool Stylesheet::set_value(const std::string & element, const uint & val_idx, const uint & val_idx_arr, const std::string& value)
		{
			for ( auto&x : _types )
			{
				if ( x.Name( ) == element )
				{
					x.setValue( val_idx, val_idx_arr, value );
					return true;
				}
			}
			return false;
		}

	}
}
