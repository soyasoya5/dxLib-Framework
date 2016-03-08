#include "Style.h"
#include "Stylesheet.h"
#include "../../FileIO/Config.h"

namespace Graphics {
	namespace Style {

		Stylesheet CreateDefaultStyle( std::string file )
		{
			std::ifstream _read( file );
			if (_read.is_open( ) ) {
				_read.close( );
				auto style = CreateStyleSheet( file );
				auto str = style->get_value_str( "ui_listbox", 0, 0 );
				if ( str != "" )
					return *style;
			}
			
			std::ofstream _file( file, std::ios::app );
			_file << "background = [ { 255, 75, 75, 75 } ]\n" <<
					 "\n" <<
					 "ui_button = [ { 255, 23, 23, 23 }, { 255, 45, 45, 45 }, { 255, 255, 255, 255 }\n" <<
					 "ui_button_focus = [ { 255, 23, 23, 23 }, { 255, 55, 55, 55 }, { 255, 255, 255, 255 } ]\n" <<
					 "ui_button_hover = [ { 255, 23, 23, 23 }, { 255, 65, 65, 65 }, { 255, 255, 255, 255 } ]\n" <<
					 "\n" <<
					 "ui_checkbox = [ { 255, 23, 23, 23 }, { 255, 45, 45, 45 }, { 255, 255, 255, 255 }, { 255, 35, 35, 35 } ]\n" <<
					 "ui_checkbox_focus = [ { 255, 23, 23, 23 }, { 255, 55, 55, 55 }, { 255, 255, 255, 255 }, { 255, 35, 35, 35 } ]\n" <<
					 "ui_checkbox_hover = [ { 255, 23, 23, 23 }, { 255, 65, 65, 65 }, { 255, 255, 255, 255 }, { 255, 35, 35, 35 } ]\n" <<
					 "\n" <<
					 "ui_textbox = [ { 255, 23, 23, 23 }, { 255, 35, 35, 35 }, { 255, 255, 255, 255 }, { 255, 150, 150, 150 } ]\n" <<
					 "\n" <<
					 "ui_label =  [ { 255, 255, 255, 255 } ]\n" <<
					 "\n" <<
					 "ui_scrollbar = [ { 255, 23, 23, 23 }, { 255, 35, 35, 35 }, { 0, 0, 0, 0 }, { 255, 0, 157, 222 } ]\n" <<
					 "ui_scrollbar_hover = [ { 255, 0, 157, 240 } ]\n" <<
					 "\n" <<
					 "ui_window = [ { 255, 24, 24, 24 }, { 255, 35, 35, 35 }, { 255, 255, 255, 255 } ]\n" <<
					 "\n" <<
					 "ui_tabcontrol = [ { 255, 35, 35, 35 }, { 0, 0, 0, 0 }, { 255, 255, 255, 255 }, { 255, 0, 157, 222 } ]\n" <<
					 "\n" <<
					 "ui_listbox = [ { 255, 23, 23, 23 }, { 255, 45, 45, 45 }, { 0 }, { 255, 0, 157, 222 } ]";
			_file.close( );
			return *CreateStyleSheet( file );
		}

		const Stylesheet DEFAULT_STYLE = CreateDefaultStyle( "Style_gray.ini" );

		Stylesheet *CreateStyleSheet(const std::string& file)
		{
			Stylesheet::List list;
			FileIO::Config config{ file.c_str( ) };
			config.Parse( );
			for (auto x : config.getElements( ))
			{
				StyleElement element;
				element.Name( ) = x.Name( );
				
				for (auto& e : x.Array( ))
					element.Array( ).push_back( e );
				list.push_back( element );
			}
			return Object::SafeAlloc<Stylesheet>( list, Utils::String( file.c_str( ), file.length( ) ) );
		}


	}
}
