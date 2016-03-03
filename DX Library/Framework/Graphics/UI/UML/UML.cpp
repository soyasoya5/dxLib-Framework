#include "UML.h"
#include "../../Renderer/Renderer.h"
#include "../Button.h"
#include "../Label.h"
#include "../Scrollbar.h"
#include "../TabControl.h"
#include "../Checkbox.h"
#include "../Textbox.h"
#include "../Window.h"
#include "../Canvas.h"
#include "../../Stylesheet/Style.h"
#include "../../../Utils/Logger.h"



namespace Graphics {
	namespace UI {
		namespace UML {


			Document::Document(Utils::String filename, Utils::String Docname)
				: _fileName( filename ), _docName( Docname ), _tokenizer( FileIO::ReadFile( filename.c_str( ) ) )
			{
			}

			Utils::String & Document::getFileName()
			{
				return _fileName;
			}

			Utils::String & Document::getDocName()
			{
				return _docName;
			}

			FileIO::Tokenizer & Document::getTokenizer()
			{
				return _tokenizer;
			}

			Executer::Executer()
			{
				_logger = new Utils::Logger();
			}

			Executer::~Executer()
			{
				delete _logger;
			}

			void Executer::addDocument(Document *doc)
			{
				Script *script = new Script( );
				ParseScript( doc, *script );
				_scripts.push_back( script );
			}

			void Executer::re_parse()
			{
				for ( auto&x : _scripts )
				{
					x->Release( );
					auto oldDoc = x->_doc;
					x->_doc = new Document( oldDoc->getFileName( ), oldDoc->getDocName( ) );
					delete oldDoc;
					ParseScript( x->_doc, *x );
				}
			}

			void Executer::ParseScript(Document* doc, Script& script)
			{
				using namespace FileIO;
				script._doc = doc;
				script._macros.clear( );
				script._calls.clear( );
				auto tokenizer = doc->getTokenizer();
				tokenizer.Tokenize();

				int error = 0;
				for (auto it = tokenizer.begin(); it < tokenizer.end(); ++it)
				{
					if (SyntaxHelper::isComment(it))
						SyntaxHelper::eatComment(it);

					if (*it == Tokenizer::eToken_identifier && *it != "macro")
					{
						auto name = it->string.c_str();
						auto expr = SyntaxHelper::ParseExpression(++it, error);
						if (error == -1)
						{
							OnErrorOccured().Invoke(this, doc, it->line_count, "Failed to parse call expression.");
							continue;
						}

						Script::FunctionCall call;
						call._function = name;
						call._params = expr;
						script._calls.push_back(call);
						continue;
					}

					
					// Macro
					if (*it == "macro")
					{
						if (*(++it) != "(")
						{
							OnErrorOccured().Invoke(this, doc, it->line_count, "Macro missing parenthesis.");
							continue;
						}

						if (*(++it) != Tokenizer::eToken_string)
						{
							OnErrorOccured().Invoke(this, doc, it->line_count, "Macro not containing component");
							continue;
						}

						Script::Macro macro;
						macro.name_comp = it->string.c_str();
						macro.name_comp = macro.name_comp.substr(macro.name_comp.find_wild("\"", "\""));
						++it;
						if (*(++it) != "->")
						{
							OnErrorOccured().Invoke(this, doc, it->line_count, "Macro missing event access operator");
							continue;
						}

						macro.name = (++it)->string.c_str();
						++it; // eat '->'
						macro.params = SyntaxHelper::count_params("(", ")", it);
						auto params = SyntaxHelper::ParseParenthesis(it, error);
						if (error == -1)
						{
							OnErrorOccured().Invoke(this, doc, it->line_count, "Failed to parse macro event parameters");
							continue;
						}

						for (auto x : params)
							macro.param_names.push_back(x[0].get_value(0));
						++it; // eat ')'
						while (*it == "\n")
							++it; // eat endls
								  // Parse body..
						
						// PARSE Macro body
						while (*it != "}" && *it != Tokenizer::eToken_eof)
						{
							if ( SyntaxHelper::isComment( it ) )
								SyntaxHelper::eatComment( it );

							if (*it == Tokenizer::eToken_identifier && *it != "macro")
							{
								auto name = it->string.c_str();
								auto expr = SyntaxHelper::ParseExpression(++it, error);
								if (error == -1)
								{
									OnErrorOccured().Invoke(this, doc, it->line_count, "Failed to parse expression.");
									continue;
								}

								Script::FunctionCall call;
								call._function = name;
								call._params = expr;
								macro.body.push_back(call);
							}

							if ( *it == "var" )
							{
								// A Variable.
								
								

							}

							++it;
						}
						script._macros.push_back(macro);
					}
				}

				if ( !_render )
					OnErrorOccured().Invoke( this, doc, 0, "No renderer attached." );
				

				for ( auto&call : script._calls )
				{
					auto name = call._function;
					auto param = call._params;
					auto res = call_native_macro( &script, name, param );
					if ( res != "success" ) {
						_logger->Log( "UML " + res, Utils::Error );
						OnErrorOccured().Invoke( this, doc, 0, "Failed to invoke native macro: " + res );
					}
				}

			}

			Utils::Logger * Executer::getLogger()
			{
				return _logger;
			}
		

			void Executer::Paint(Renderer::D9Renderer *r)
			{
				for ( auto&script : _scripts )
				{
					for ( auto&x : script->_comps )
						x->Paint( r );
				}
			}

			void Executer::Tick()
			{
				for ( auto&script : _scripts )
				{
					for ( auto&x : script->_comps )
						x->Tick( );
				}
			}

			bool Executer::OnMouseMove(Vector2 mouse)
			{
				for ( auto&script : _scripts )
				{
					for ( auto&x : script->_comps )
						x->OnMouseMove( mouse );
				}
				return false;
			}

			bool Executer::OnLeftMouseDown(Vector2 mouse)
			{
				for ( auto&script : _scripts )
				{
					for ( auto&x : script->_comps )
						x->OnLeftMouseDown( mouse );
				}
				return false;
			}

			bool Executer::OnLeftMouseUp(Vector2 mouse)
			{
				for ( auto&script : _scripts )
				{
					for ( auto&x : script->_comps )
						x->OnLeftMouseUp( mouse );
				}
				return false;
			}

			bool Executer::OnRightMouseDown(Vector2 mouse)
			{
				for ( auto&script : _scripts )
				{
					for ( auto&x : script->_comps )
						x->OnRightMouseDown( mouse );
				}
				return false;
			}

			bool Executer::OnRightMouseUp(Vector2 mouse)
			{
				for ( auto&script : _scripts )
				{
					for ( auto&x : script->_comps )
						x->OnRightMouseUp( mouse );
				}
				return false;
			}

			bool Executer::OnLeftMouseDoubleClick(Vector2 mouse)
			{
				for ( auto&script : _scripts )
				{
					for ( auto&x : script->_comps )
						x->OnLeftMouseDoubleClick( mouse );
				}
				return false;
			}

			bool Executer::OnRightMouseDoubleClick(Vector2 mouse)
			{
				for ( auto&script : _scripts )
				{
					for ( auto&x : script->_comps )
						x->OnRightMouseDoubleClick( mouse );
				}
				return false;
			}

			bool Executer::OnKeyDown(uint c)
			{
				for ( auto&script : _scripts )
				{
					for ( auto&x : script->_comps )
						x->OnKeyDown( c );
				}
				return false;
			}

			bool Executer::OnKeyUp(uint c)
			{
				for ( auto&script : _scripts )
				{
					for ( auto&x : script->_comps )
						x->OnKeyUp( c );
				}
				return false;
			}

			bool Executer::OnKeyDownChar(char c)
			{ 
				for ( auto&script : _scripts )
				{
					for ( auto&x : script->_comps )
						x->OnKeyDownChar( c );
				}
				return false;
			}

			void Parameter::set_value(const uint & idx, const Utils::String &val)
			{
				_values[idx] = val;
			}

			Utils::String Parameter::get_value(const uint & idx) const
			{
				return _values[idx];
			}

			Utils::String Executer::call_native_macro(Script* script, Utils::String name, std::vector<std::vector<Parameter>> params)
			{
				if ( !_render )
					return "(Native) Renderer is not attached.";
				
				if ( name == "PrepareFont" )
				{
					if ( params.size( ) < 4)
						return "(Native) To few parameters for macro: " + name;
					auto windows = params[0][0].get_value( 0 );
					auto font = params[1][0].get_value( 0 );
					auto sz = params[2][0].get_value<uint>( 0 );
					auto wh = params[3][0].get_value<uint>( 0 );
					_render->PrepareFont( windows.substr( windows.find_wild( "\"", "\"" ) ) , font.substr(font.find_wild("\"", "\"")), sz, wh );
					return "success";
				}

				// ==============================================================================================================================
				// =                                                   addWindow                                                                =
				// ==============================================================================================================================
				if ( name == "addWindow" )
				{
					if ( !script )
						return "Script cannot be null when calling 'addButton'";
					if ( params.size( ) < 7 )
						return "To few parameters for macro: " + name;
					auto name = params[0][0].get_value( 0 );
					auto text = params[1][0].get_value( 0 );
					auto font = params[2][0].get_value( 0 );
					auto style = params[3][0].get_value( 0 );
					auto pos = ParamToVec( params[4] );
					auto size = ParamToVec( params[5] );
					auto allign = ParamToAllignment( params[6] );
					auto window = new UI::Window( );
					window->setName( name.substr( name.find_wild( "\"", "\"" ) ) );
					window->setText( text.substr( text.find_wild( "\"", "\"" ) ) );
					window->setFont( font.substr( font.find_wild( "\"", "\"" ) ) );
					window->setStylesheet( *script->getStyle( style.substr( style.find_wild( "\"", "\"" ) ) ) );
					window->setAbsolutePosition( pos );
					window->setSize( size );
					window->setAllignment( allign );
					window->OnComponentClicked() += [script, this](UI::Component* comp, Vector2 vec)
					{
						auto res = this->call_script_macro( script, comp->getName( ), "OnComponentClicked", { { Parameter( { comp->getName( ) } ) } } );
						if ( res != "success" ) {
							_logger->Log( "UML " + res, Utils::Error );
							return false;
						}
						return true;
					};

					script->_comps.push_back( window );
					return "success";
				}


				// ==============================================================================================================================
				// =                                                   addButton                                                                =
				// ==============================================================================================================================
				if ( name == "addButton" )
				{
					if ( !script )
						return "Script cannot be null when calling 'addButton'";
					auto psize = params.size( );
					if ( psize == 7 )
					{
						auto name = params[0][0].get_value( 0 );
						auto text = params[1][0].get_value( 0 );
						auto font = params[2][0].get_value( 0 );
						auto style = params[3][0].get_value( 0 );
						auto padding = ParamToVec( params[4] );
						auto size = ParamToVec( params[5] );
						auto allign = ParamToAllignment( params[6] );
						auto button = new UI::Button( );
						script->_comps.push_back( button );
						button->setName( name.substr( name.find_wild("\"", "\"") ) );
						button->setText( text.substr( text.find_wild("\"", "\"") ) );
						button->setFont( font.substr( font.find_wild("\"", "\"") ) );
						button->setStylesheet( *script->getStyle( style.substr( style.find_wild( "\"", "\"" ) ) ) );
						button->setPadding( padding );
						button->setSize( size );
						button->setAllignment( allign );
						button->OnComponentClicked() += [script, this](UI::Component* comp, Vector2 vec)
						{
							auto res = this->call_script_macro( script, comp->getName( ), "OnComponentClicked", { { Parameter( { comp->getName( ) } ) } } );
							if ( res != "success" ) {
								_logger->Log( "UML " + res, Utils::Error );
								return false;
							}
							return true;
						};
						return "success";
					}
					else if ( psize == 8 )
					{
						auto name = params[0][0].get_value( 0 );
						auto text = params[1][0].get_value( 0 );
						auto font = params[2][0].get_value( 0 );
						auto style = params[3][0].get_value( 0 );
						auto padding = ParamToVec( params[4] );
						auto size = ParamToVec( params[5] );
						auto allign = ParamToAllignment( params[6] );
						auto parent = params[7][0].get_value( 0 );
						auto parent_ptr = script->getComponent( parent.substr( parent.find_wild( "\"", "\"" ) ) );
						if ( !parent_ptr )
							return "Parent: " + parent + " does not exist.";
						auto button = new UI::Button( );
						button->setName( name.substr( name.find_wild("\"", "\"") ) );
						button->setText( text.substr( text.find_wild("\"", "\"") ) );
						button->setFont( font.substr( font.find_wild("\"", "\"") ) );
						button->setStylesheet( *script->getStyle( style.substr( style.find_wild( "\"", "\"" ) ) ) );
						button->setPadding( padding );
						button->setSize( size );
						button->setAllignment( allign );
						button->OnComponentClicked() += [script, this](UI::Component* comp, Vector2 vec)
						{
							auto res = this->call_script_macro( script, comp->getName( ), "OnComponentClicked", { { Parameter( { comp->getName( ) } ) } } );
							if ( res != "success" ) {
								_logger->Log( "UML " + res, Utils::Error );
								return false;
							}
							return true;
						};
						parent_ptr->addChild( button );
						return "success";
					}
					return "(Native) To few/many parameters for function: " + name;
				} 
				

				// ==============================================================================================================================
				// =                                                   addCheckbox                                                              =
				// ==============================================================================================================================
				if ( name == "addCheckbox" )
				{
					if ( !script )
						return "Script cannot be null when calling 'addCheckbox'";
					auto psize = params.size( );
					if ( psize == 7 )
					{
						auto name = params[0][0].get_value( 0 );
						auto text = params[1][0].get_value( 0 );
						auto font = params[2][0].get_value( 0 );
						auto style = params[3][0].get_value( 0 );
						auto state = ParamToBool( params[4] );
						auto padding = ParamToVec( params[5] );
						auto size = ParamToVec( params[6] );
						auto cbx = new UI::Checkbox( );
						cbx->setName( name.substr( name.find_wild("\"", "\"") ) );
						cbx->setText( text.substr( text.find_wild("\"", "\"") ) );
						cbx->setFont( font.substr( font.find_wild("\"", "\"") ) );
						cbx->setStylesheet( *script->getStyle( style.substr( style.find_wild( "\"", "\"" ) ) ) );
						cbx->setPadding( padding );
						cbx->setSize( size);
						cbx->setState( state );
						cbx->OnComponentClicked() += [script, this](UI::Component* comp, Vector2 vec)
						{
							auto res = this->call_script_macro( script, comp->getName( ), "OnComponentClicked", { { Parameter( { comp->getName( ) } ) } } );
							if ( res != "success" ) {
								_logger->Log( "UML " + res, Utils::Error );
								return false;
							}
							return true;
						};
						script->_comps.push_back( cbx );
						_logger->Log( "UML Created Checkbox " + cbx->getName( ), Utils::Debug );
						return "success";
					}
					else if ( psize == 8 )
					{
						auto name = params[0][0].get_value( 0 );
						auto text = params[1][0].get_value( 0 );
						auto font = params[2][0].get_value( 0 );
						auto style = params[3][0].get_value( 0 );
						auto state = ParamToBool( params[4] );
						auto padding = ParamToVec( params[5] );
						auto size = ParamToVec( params[6] );
						auto parent = params[7][0].get_value( 0 );
						auto parent_ptr = script->getComponent( parent.substr( parent.find_wild( "\"", "\"" ) ) );
						if ( !parent_ptr )
							return "Parent: " + parent + " does not exist.";
						auto cbx = new UI::Checkbox( );
						cbx->setName( name.substr( name.find_wild("\"", "\"") ) );
						cbx->setText( text.substr( text.find_wild("\"", "\"") ) );
						cbx->setFont( font.substr( font.find_wild("\"", "\"") ) );
						cbx->setStylesheet( *script->getStyle( style.substr( style.find_wild( "\"", "\"" ) ) ) );
						cbx->setPadding( padding );
						cbx->setSize( size);
						cbx->setState( state );
						cbx->OnComponentClicked() += [script, this](UI::Component* comp, Vector2 vec)
						{
							auto res = this->call_script_macro( script, comp->getName( ), "OnComponentClicked", { { Parameter( { comp->getName( ) } ) } } );
							if ( res != "success" ) {
								_logger->Log( "UML " + res, Utils::Error );
								return false;
							}
							return true;
						};
						parent_ptr->addChild( cbx );
						_logger->Log( "UML Created Checkbox " + cbx->getName( ) + " with parent " + parent_ptr->getName( ), Utils::Debug );
						return "success";
					}
					return "(Native) To few/many parameters for macro: " + name;
				}
				

				// ==============================================================================================================================
				// =                                                                                                                            =
				// =                                                                                                                            =
				// =                                                      Setters                                                               =
				// =                                                                                                                            =
				// =                                                                                                                            =
				// ==============================================================================================================================



				// ==============================================================================================================================
				// =                                                   setPadding                                                               =
				// ==============================================================================================================================
				if ( name == "setPadding" )
				{
					// Macro:
					// setPadding( name, padding )
					// setPadding( "Button", { 25, 25 } )
					if ( params.size( ) != 2 )
						return "To few/many parameters for macro: " + name;
					if ( !script )
						return "'script' cannot be null when calling " + name;

					auto name = params[0][0].get_value( 0 );
					auto pad = ParamToVec( params[1] );
					auto comp = script->getComponent( name.substr( name.find_wild( "\"", "\"" ) ) );
					if ( !comp )
						return "Component " + name + " doesn't exist.";
					comp->setPadding( pad );
					//_logger->Log( "UML " + comp->getName( ) + "'s padding set to {" +  
					//if ( _file.is_open( ) )
					//	_file << "[UML] " << comp->getName() << "'s padding set to { " << pad.x << ", " << pad.y << " }.\n";
					std::stringstream ss;
					ss << "UML " << comp->getName() << "'s padding set to {" << pad.x << ", " << pad.y << "}.";
					_logger->Log( ss.str( ), Utils::Debug );
					return "success";
				}

				// ==============================================================================================================================
				// =                                                     setSize                                                                =
				// ==============================================================================================================================
				if ( name == "setSize" )
				{
					// Macro:
					// setSize( name, size )
					// setSize( "Button", { 25, 25 } )
					if ( params.size( ) != 2 )
						return "To few/many parameters for macro: " + name;
					if ( !script )
						return "'script' cannot be null when calling " + name;

					auto name = params[0][0].get_value( 0 );
					auto size = ParamToVec( params[1] );
					auto comp = script->getComponent( name.substr( name.find_wild( "\"", "\"" ) ) );
					if ( !comp )
						return "Component " + name + " doesn't exist.";
					comp->setSize( size );
					std::stringstream ss;
					ss << "UML " << comp->getName() << "'s size set to { " << size.x << ", " << size.y << " }.\n";
					_logger->Log( ss.str( ), Utils::Debug );
					return "success";
				}

				// ==============================================================================================================================
				// =                                                     setName                                                                =
				// ==============================================================================================================================
				if ( name == "setName" )
				{
					// Macro:
					// setName( name, newname ) 
					// setName( "Button", "Checkbox" )
					if ( params.size( ) != 2 )
						return "To few/many parameters for macro: " + name;
					if ( !script )
						return "'script' cannot be null when calling " + name;
					
					auto name = params[0][0].get_value( 0 );
					auto newname= params[1][0].get_value( 0 );
					auto comp = script->getComponent( name.substr( name.find_wild( "\"", "\"" ) ) );
					if ( !comp )
						return "Component " + name + " doesn't exist.";
					comp->setName( newname );
					std::stringstream ss;
					ss << "UML " << name.substr(name.find_wild("\"", "\"")) << "'s name set to: " << comp->getName() << ".\n";
					_logger->Log( ss.str( ), Utils::Debug );
					return "success";
				}

				// ==============================================================================================================================
				// =                                                     setText                                                                =
				// ==============================================================================================================================
				if ( name == "setText" )
				{
					// Macro:
					// setName( name, newname ) 
					// setName( "Button", "Checkbox" )
					if ( params.size( ) != 2 )
						return "To few/many parameters for macro: " + name;
					if ( !script )
						return "'script' cannot be null when calling " + name;
					
					auto name = params[0][0].get_value( 0 );
					auto newname= params[1][0].get_value( 0 );
					auto comp = script->getComponent( name.substr( name.find_wild( "\"", "\"" ) ) );
					if ( !comp )
						return "Component " + name + " doesn't exist.";
					comp->setText( newname );
					std::stringstream ss;
					ss << "UML " << comp->getName( ) << "'s text set to: " << comp->getText( ) << ".\n";
					_logger->Log( ss.str( ), Utils::Debug );
					return "success";
				}
 
				return "(Native) Macro not found: " + name;
			}

			Utils::String Executer::call_script_macro(Script* script, Utils::String component, Utils::String event, std::vector<std::vector<Parameter>> params)
			{
				if ( !script )
					return "Script cannot be null when calling a script macro.";

				auto comp = script->getComponent( component );
				if ( !comp )
					return "Component: " + component + " not found.";

				// Loop through all event macro in the script context
				bool failed = false;
				for ( auto&macro : script->_macros )
				{
					// If the current event name & component name is correct
					if ( macro.name_comp == comp->getName( ) && macro.name == event )
					{
						// Loop through all calls in the body
						for ( auto&call : macro.body )
						{
							// Set any paramters given to the event by the event handler
							for ( int i = 0; i < call._params.size( ); ++i )
							{
								auto &param = call._params[i];
								
								
								
								auto correct = getParameter( params, "\"" + param[0].get_value( 0 ) + "\"" );
								if ( correct.get_value( 0 ) != "" )
									param[0].set_value( 0, correct.get_value( 0 ) );
							}

							// Call the native macro function.
							auto res = call_native_macro( script, call._function, call._params );
							if ( res != "success" ) {
								_logger->Log( "UML " + res, Utils::Error );
							}
						}
					}
				}
				return "success";
			}

			Parameter Graphics::UI::UML::Executer::getParameter(const std::vector<std::vector<Parameter>>&params, const Utils::String& string)
			{
				for ( auto& x : params )
					if ( x[0].get_value( 0 ) == string )
						return x[0];
				return Parameter( {}, { "" } );
			}

			Allignment Executer::ParamToAllignment(const std::vector<Parameter>& param)
			{
				auto str = param[0].get_value( 0 );
				if ( str == "Left" )
					return Left;
				else if ( str == "Middle" )
					return Middle;
				else if ( str == "Right" )
					return Right;
				return Allignment( param[0].get_value<uint>( 0 ) );
			}

			bool Executer::ParamToBool(const std::vector<Parameter>& param)
			{
				auto str = param[0].get_value( 0 ).lower( );
				if ( str == "false")
					return false;
				else if ( str == "true" )
					return true;
				return param[0].get_value<bool>( 0 );
			}

			Vector2 Executer::ParamToVec( const std::vector<Parameter>& param)
			{
				return Vector2( param[0].get_value<float>( 0 ), param[1].get_value<float>( 0 ) );
			}

			Event<bool, Executer*, Document*, uint, Utils::String>& Executer::OnErrorOccured()
			{
				return _OnErrorOccured;
			}

			std::vector<std::vector<Parameter>> SyntaxHelper::ParseParenthesis(iterator &iter, error &err)
			{
				using namespace FileIO;
				err = -1;
				if ( *(iter) != "(" )
					return {};
				++iter;

				std::vector<std::vector<Parameter>> ret;
				while( *iter != ")" && *iter != Tokenizer::eToken_eof )
				{
					if ( *iter == "," )
					{
						if ( *(iter-1) == "(" || *(iter-1) == "," )
							return {};
						++iter;
						continue;
					}

					if ( isValidExpr( iter ) )
					{
						auto expr = ParseExpression( iter, err );
						if ( err == -1 )
							return {};
						ret.push_back( expr[0] );
					} 
					else
						return {};
					++iter;
				}
				err = 0;
				return ret;
			}

			std::vector<Parameter> SyntaxHelper::ParseBrackets(iterator &iter, error &err)
			{
				using namespace FileIO;
				err = -1;
				if ( *(iter) != "{" )
					return {};
				++iter;
				
				std::vector<Parameter> ret;
				while( *iter != "}" && *iter != Tokenizer::eToken_eof )
				{ 
					if ( *iter == "," )
					{
						if ( *(iter-1) != Tokenizer::eToken_string && *(iter-1) != Tokenizer::eToken_numerical
							&& *(iter-1) != Tokenizer::eToken_identifier )
							return {};
						++iter;
						continue;
					}
					
					if ( *iter == Tokenizer::eToken_string || *iter == Tokenizer::eToken_identifier || *iter == Tokenizer::eToken_numerical )
					{
						std::vector<Tokenizer::Token> _toks{ *iter };
						std::vector<Utils::String> _vals{ iter->string.c_str( ) };
						Parameter expr{ _toks, _vals };
						ret.push_back( expr );
					} 
					else
						return{};
					++iter;
				}
				err = 0;
				return ret;
			}

			std::vector<std::vector<Parameter>> SyntaxHelper::ParseExpression(iterator &iter, error &err)
			{
				using namespace FileIO;
				if ( *iter == "(" )
					return ParseParenthesis( iter, err );
				else if ( *iter == "{" )
					return { ParseBrackets( iter, err ) };
				else if ( *iter == Tokenizer::eToken_string || *iter == Tokenizer::eToken_identifier || *iter == Tokenizer::eToken_numerical )
				{
					std::vector<Tokenizer::Token> _toks{ *iter };
					std::vector<Utils::String> _vals{ iter->string.c_str( ) };
					Parameter expr{ _toks, _vals };
					err = 0;
					return { { expr } };
				}
				return {};
			}

			bool SyntaxHelper::isValidExpr(iterator iter)
			{
				using namespace FileIO;
				return *iter == Tokenizer::eToken_string || *iter == Tokenizer::eToken_identifier || *iter == Tokenizer::eToken_numerical || *iter == "{";
			}

			uint SyntaxHelper::count_params(const Utils::String& start, const Utils::String& end, iterator iter)
			{
				if ( *iter != start.c_str( ) )
					return 0;
				++iter;
				uint count = 0;
				while( *iter != FileIO::Tokenizer::eToken_eof && *iter != end.c_str( ) )
				{
					if ( *iter == "," )
					{
						if ( *(iter - 1) == start.c_str( ) || *(iter - 1) == "(" )
							return 0;
						++iter;
						continue;
					}
					++count;
					++iter;
				}
				return count;
			}

			bool SyntaxHelper::isComment(iterator iter)
			{
				return *iter == "//";
			}

			bool SyntaxHelper::eatComment(iterator &iter)
			{
				while( *iter != "eof" && *iter != "\n" )
					++iter;
				return true;
			}


			Style::Stylesheet * Executer::Script::getStyle(const Utils::String &name)
			{
				for ( auto& x : _styles )
					if ( x->getName( ) == name)
						return x;
				auto style = Style::CreateStyleSheet( name.c_str( ) );
				_styles.push_back( style );
				return style;
			}

			Component * Executer::Script::getComponent(const Utils::String &name)
			{
				for (auto comp : _comps)
				{
					if ( comp->getName( ) == name )
						return comp;

					auto child = comp->get_child_of_name( name );
					if ( child )
						return child;
				}

				return nullptr;
			}

			Executer::Script::Macro * Executer::Script::EventMacro(const Utils::String & comp, const Utils::String & event)
			{
				for ( auto& x : _macros )
					if ( x.name_comp == comp && x.name == event )
						return &x;
				return nullptr;
			}

			void Executer::Script::SymbolTable::addSymbol( const Symbol &sym )
			{
				_symbols.push_back( sym );
			}

			void Graphics::UI::UML::Executer::Script::SymbolTable::addSymbol(const Utils::String &name, const Utils::String &value)
			{
				addSymbol( { name, value } );
			}

			void Graphics::UI::UML::Executer::Script::SymbolTable::removeSymbol(const Utils::String &s)
			{
				for ( auto it = _symbols.begin( ); it < _symbols.end( ); ++it ) 
				{
					if ( it->name == s )
					{
						_symbols.erase( it );
						break;
					}
				}
			}

			bool Graphics::UI::UML::Executer::Script::SymbolTable::exists(const Symbol &other)
			{
				return exists( other.name );
			}

			bool Graphics::UI::UML::Executer::Script::SymbolTable::exists(const Utils::String &name)
			{
				for ( auto it = _symbols.begin( ); it < _symbols.end( ); ++it ) 
					if ( it->name == name )
						return true;
				return false;
			}

			void Executer::Script::Release()
			{
				for (auto&x : _comps)
				{
					x->Release( );
					delete x;
				}
				_comps.clear( );
			}


		}
	}
}