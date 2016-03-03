#pragma once
#include <string>

namespace Graphics {
	namespace Style {
		class Stylesheet;
		extern const Stylesheet DEFAULT_STYLE;
		extern Stylesheet* CreateStyleSheet( const std::string& file );
	}
}



