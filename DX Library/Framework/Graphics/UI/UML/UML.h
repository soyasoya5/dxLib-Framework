#pragma once
/*----------------------------------------------------------------------
						UI Modeling Language
------------------------------------------------------------------------*/
#include "../Component.h"
#include "../../../FileIO/Config.h"

namespace Utils { class Logger; }

namespace Graphics {
	namespace UI {
		class Canvas;
		namespace UML {

			
			class Document
			{
			private:
				Utils::String _fileName, _docName;

				FileIO::Tokenizer _tokenizer;
			public:
				Document( Utils::String filename, Utils::String Docname );

				Utils::String& getFileName( );
				Utils::String& getDocName( );
				FileIO::Tokenizer& getTokenizer( );
			};


			class Parameter
			{
			private:
				std::vector<FileIO::Tokenizer::Token> _tokens;
				std::vector<Utils::String> _values;
			public:
				Parameter( const std::vector<FileIO::Tokenizer::Token>& tokens, const std::vector<Utils::String>& values )
					: _tokens( tokens ), _values( values ) {}

				Parameter( const std::vector<Utils::String>& values )
					: _values(values) { }

				std::vector<FileIO::Tokenizer::Token>& Tokens( ) { return _tokens; }
				std::vector<Utils::String>& Values( ) { return _values; }

				void set_value( const uint& idx, const Utils::String& );
				Utils::String get_value( const uint& idx ) const;

				template<typename T>
				T get_value( const uint& idx ) const
				{
					auto str = get_value( idx );
					T t;
					std::stringstream ss( str.c_str( ) );
					ss >> t;
					return t;
				}

			};

			class SyntaxHelper
			{
			public:
				typedef std::vector<FileIO::Tokenizer::Token>::iterator iterator;
				typedef int error;

				// RULES:
				//
				// '(' ARGUMENTS ')'
				// Where 'ARGUMENTS' is a set of expression(s).
				//
				static std::vector<std::vector<Parameter>> ParseParenthesis( iterator&, error& );

				// RULES:
				//
				// '{' ARGUMENTS '}'
				// Where 'ARGUMENTS' is a set of expression(s).
				static std::vector<Parameter> ParseBrackets( iterator&, error& );

				// Expression:
				// e.g an expression is:
				// '(' expression ')' '{' expression, expression '}'
				// When calling 'ParseExpression' iterator must
				// start on either of these:
				// eToken_identifier, eToken_numerical
				static std::vector<std::vector<Parameter>> ParseExpression( iterator&, error& );
				static bool isValidExpr( iterator );
				static uint count_params( const Utils::String&, const Utils::String&, iterator );

				// UML only has one line comments. (//)
				static bool isComment( iterator );
				static bool eatComment( iterator& );
			};


			class Executer
			{
			public:
				class Script
				{
				public:
					friend class Executer;
					struct FunctionCall
					{
						std::vector<std::vector<Parameter>> _params;
						Utils::String _function;
					};

					class SymbolTable
					{
					public:
						struct Symbol;

					private:
						std::vector<Symbol> _symbols;

					public:

						struct Symbol
						{
							Utils::String name;
							Utils::String value;
						};

						void addSymbol( const Symbol& );
						void addSymbol( const Utils::String&, const Utils::String& );
						void removeSymbol( const Utils::String& );
						bool exists( const Symbol& other );
						bool exists( const Utils::String& );
					};

					class Macro
					{
					public:
						uint params;
						std::vector<Utils::String> param_names;
						Utils::String name, name_comp;
						std::vector<FunctionCall> body;
						SymbolTable table;
					};

					
					
					Document* _doc;
					std::vector<FunctionCall> _calls;
					std::vector<Macro> _macros;
					std::vector<Component*> _comps;
					std::vector<Style::Stylesheet*> _styles;

					Style::Stylesheet* getStyle( const Utils::String& );
					Component* getComponent( const Utils::String& );
					Executer::Script::Macro* EventMacro( const Utils::String& comp, const Utils::String& event );

					void Release();
				};

			private:
				std::vector<Script*> _scripts;
				Event<bool, Executer*, Document*, uint, Utils::String> _OnErrorOccured;
				Renderer::D9Renderer* _render;
				Utils::Logger* _logger;

			public:
				Executer( );
				~Executer( );

				void addDocument( Document* );
				void setRender( Renderer::D9Renderer* r) { _render = r; }
				void re_parse( );
				void ParseScript( Document*, Script& );
				Utils::Logger* getLogger( );

				void Paint( Renderer::D9Renderer* );
				void Tick( );
				bool OnMouseMove( Vector2 );
				bool OnLeftMouseDown( Vector2 );
				bool OnLeftMouseUp( Vector2 );
				bool OnRightMouseDown( Vector2 );
				bool OnRightMouseUp( Vector2 );
				bool OnLeftMouseDoubleClick( Vector2 );
				bool OnRightMouseDoubleClick( Vector2 );
				bool OnKeyDown( uint );
				bool OnKeyUp( uint );
				bool OnKeyDownChar( char );

			public: // Executer
				Utils::String call_native_macro( Script* script, Utils::String name, std::vector<std::vector<Parameter>> params );
				Utils::String call_script_macro( Script* script, Utils::String component, Utils::String event, std::vector<std::vector<Parameter>> params );
				Parameter getParameter( const std::vector<std::vector<Parameter>>&, const Utils::String& );
				Vector2 ParamToVec( const std::vector<Parameter>& param );
				Allignment ParamToAllignment( const std::vector<Parameter>& param );
				bool ParamToBool( const std::vector<Parameter>& param );

			public:

				Event<bool, Executer*, Document*, uint, Utils::String>& OnErrorOccured( );
			};


		}
	}
}
