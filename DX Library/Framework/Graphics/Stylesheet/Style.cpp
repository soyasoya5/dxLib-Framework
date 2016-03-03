#include "Style.h"
#include "Stylesheet.h"
#include "../../FileIO/Config.h"

namespace Graphics {
	namespace Style {

		Stylesheet CreateDefaultStyle( std::string file )
		{
			std::ofstream _file(file, std::ios::app);
			if ( _file.is_open( ) ) {
				_file.close( );
				return *CreateStyleSheet( file );
			}


			_file << R"(background = [ { 255, 75, 75, 75 } ]

					 ui_button = [ { 255, 23, 23, 23 }, { 255, 45, 45, 45 }, { 255, 255, 255, 255 } ]
					 ui_button_focus = [ { 255, 23, 23, 23 }, { 255, 55, 55, 55 }, { 255, 255, 255, 255 } ]
					 ui_button_hover = [ { 255, 23, 23, 23 }, { 255, 65, 65, 65 }, { 255, 255, 255, 255 } ]

					 ui_checkbox = [ { 255, 23, 23, 23 }, { 255, 45, 45, 45 }, { 255, 255, 255, 255 }, { 255, 35, 35, 35 } ]
					 ui_checkbox_focus = [ { 255, 23, 23, 23 }, { 255, 55, 55, 55 }, { 255, 255, 255, 255 }, { 255, 35, 35, 35 } ]
					 ui_checkbox_hover = [ { 255, 23, 23, 23 }, { 255, 65, 65, 65 }, { 255, 255, 255, 255 }, { 255, 35, 35, 35 } ]
					 
					 ui_textbox = [ { 255, 23, 23, 23 }, { 255, 35, 35, 35 }, { 255, 255, 255, 255 }, { 255, 150, 150, 150 } ]
					 
					 ui_label =  [ { 255, 255, 255, 255 } ]
					 
					 ui_scrollbar = [ { 255, 23, 23, 23 }, { 255, 35, 35, 35 }, { 0, 0, 0, 0 }, { 255, 0, 157, 222 } ]
					 ui_scrollbar_hover = [ { 255, 0, 157, 240 } ]
					 
					 ui_window = [ { 255, 24, 24, 24 }, { 255, 35, 35, 35 }, { 255, 255, 255, 255 } ]
					 
					 ui_tabcontrol = [ { 255, 35, 35, 35 }, { 0, 0, 0, 0 }, { 255, 255, 255, 255 }, { 255, 0, 157, 222 } ]
					 
					 ui_listbox = [ { 255, 23, 23, 23 }, { 255, 45, 45, 45 }, { 0 }, { 255, 0, 157, 222 } ])";
			_file.close( );
			return *CreateStyleSheet( file );
		}

		const Stylesheet DEFAULT_STYLE = CreateDefaultStyle( "Style_gray.ini" );

		Stylesheet *CreateStyleSheet(const std::string& file)
		{
			Stylesheet::List list;
			FileIO::Config config{ file };
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
