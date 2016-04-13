//#define DONT_LINK_GRAPHICS
#include "src\api"
#include <iomanip>
#include <array>

class Word
{
public:
	dx::String word_name;
	dx::String word_all_upper;
	dx::String word_all_lower;
};

class WordGen
{
private:
	std::vector<Word> words_;
	dx::uint index_;
public:
	WordGen( const dx::String &file )
	{
		std::ifstream stream{ file.c_str( ) };
		while( !stream.eof( ) )
		{
			std::string str = "";
			std::getline( stream, str );
			Word word;
			word.word_name = str.c_str( );
			word.word_all_lower = word.word_name.lower( );
			word.word_all_upper = word.word_name.upper( );
			words_.push_back( std::move( word ) );
		}

		std::srand( std::time( 0 ) );
		std::random_shuffle( words_.begin( ), words_.end( ) );
	}

	std::vector<Word*> GetNextSetOfWords( const dx::uint &max_amount )
	{
		std::vector<Word*> result;
		for ( int i = 0; (index_ + max_amount < words_.size( ) ? i < max_amount : index_ < words_.size( )); ++index_, ++i )
			result.push_back( &words_[index_] );
		return result;
	}
};

class Form
{
private:
	dx::RichLabel *label_;
	dx::Textbox *box_;
	WordGen *generator_;
	std::vector<Word*> words_;
	dx::RichLabel::RichText* word_;
	dx::uint index_;
	int cpm_, avgcpm_, ccpm_, avgccpm_;
	int wpm_, avgwpm_;
	dx::Timer *timer_, *timer2_;
	float dt_, dtt_;
	bool _firstchar;

	dx::RichLabel *numbers_;


public:
	Form( dx::Window *window )
	{
		generator_ = new WordGen( "res/words/words.txt" );

		// Label
		label_ = new dx::RichLabel( );
		label_->setLocalPosition( { 15, 45 } );
		setNextWords( );


		// Box
		box_ = new dx::Textbox( );
		box_->setFilter( "qwertyuiopåasdfghjklöäzxcvbnmQWERTYUIOPÅASDFGHJKLÖÄZXCVBNM-_:;,^*#!¤%&/()=? " );
		box_->setPromptText( "Type word" );
		box_->setAllignment( dx::Allignment::Center );
		box_->setLocalRegion( { { 15, window->Height( ) - 40 }, { window->Width( ) - 35, 30 } } );
		box_->OnCharacterAdded( ) += BIND_METHOD_2( &Form::CharacterAdded, this );
		box_->setStyle( dx::StyleManager( dx::Theme::Dark, dx::Style::Blue ) );

		// Numbers
		numbers_ = new dx::RichLabel( );
		numbers_->setLocalPosition( { 15, 220 } );
		numbers_->appendText( "Ave rage characters per minute: ", dx::Colors::FloralWhite ); // 0
		numbers_->appendText( "0\n", dx::Colors::Green ); // 1

		numbers_->appendText( "Average Words per minute: ", dx::Colors::FloralWhite ); // 2
		numbers_->appendText( "0\n", dx::Colors::Green ); // 3

		numbers_->appendText( "Time: ", dx::Colors::FloralWhite );
		numbers_->appendText("0___\n", dx::Colors::Green );

		dx::Application::get( )->OnTick( ) += BIND_METHOD( &Form::Tick, this );
		 
		window->HandleComponent( label_ );
		window->HandleComponent( box_ );
		window->HandleComponent( numbers_ );
		window->OnWindowResize( ) += BIND_METHOD_2( &Form::Resize, this );
		window->OnPaint( ) += BIND_METHOD_2( &Form::PaintUnderline, this ); 
	}

	void Tick( )
	{
		if ( _firstchar )
		{
			if ( !timer2_ )
				timer2_ = new dx::Timer( );

			dtt_ += timer2_->GetDeltaTime( );
			numbers_->textAt( 5 )->container.text = dx::to_string( (int)dtt_ ) + "\n";
		}
	}

	void PaintUnderline( dx::Window *sender, dx::BasePainter *painter ) 
	{
		dx::Line line;
		line.Position( { word_->position.x + 10, word_->position.y + word_->size.y } );
		line.Target( { word_->position.x + word_->size.x, word_->position.y + word_->size.y } );
		line.Pen( dx::Pen( dx::Colors::Wheat, 2 ) );

		painter->PaintLine( line );
	}

	void Resize( dx::Window *sender, dx::WindowResizeArgs &args )
	{
		box_->setLocalRegion( { { 15, sender->Height( ) - 40 }, { sender->Width( ) - 35, 30 } } );
	}

	void CharacterAdded( dx::Component *sender, const char &character )
	{	
		if ( !timer_ )
			timer_ = new dx::Timer( );

		_firstchar = true;

		dt_ += timer_->GetDeltaTime( );
		if ( dt_ >= 60.0 )
		{
			avgccpm_ = ccpm_;
			avgcpm_ = cpm_;
			// 5 or so characters per word
			avgwpm_ = avgcpm_ / 5;
			ccpm_ = cpm_ = 0;

			numbers_->textAt( 1 )->container.text = dx::to_string( avgcpm_ ) + "\n";
			numbers_->textAt( 3 )->container.text = dx::to_string( avgwpm_ ) + "\n";
			numbers_->OnModified( ).Invoke( numbers_ );
			dt_ = 0.0f;
			dtt_ = 0.0f;
		}

		
		auto text = sender->getText( );

		// Remove spaces for good checking
		if ( text.contains( " " ) )
			text.erase( text.find( ' ' ), 1 );

		// Check correctness
		auto res = check_correctness( text ); 

		// is he supposedly done with this word
		if ( character == ' ' )
		{
			text = " " + text;
			res = check_correctness( text );
			if ( !res )
				word_->container.color = dx::Colors::Red;

			stepCharacter( );
			sender->setText( "" );
		}
	}

	void stepCharacter( )
	{
		index_++;
		if ( index_ >= words_.size( ) )
			setNextWords( );
		word_ = label_->textAt( index_ );
	}

	void setNextWords( )
	{
 		label_->clearText( );
		index_ = 0;
		words_ = std::move( generator_->GetNextSetOfWords( 50 ) );
		dx::uint i = 0;
		for ( auto it = words_.begin( ); it < words_.end( ); ++it, ++i )
		{
			if ( i == 10 )
			{
				i = 0;
				auto &word = *it;
				label_->appendText( " " + word->word_name + "\n", dx::Colors::White );
				continue;
			}

			auto &word = *it;
			label_->appendText( " " + word->word_name, dx::Colors::White );
		}

		label_->textAt( 0 )->container.color = dx::Colors::Wheat;
		word_ = label_->textAt( 0 );
		index_ = 0;
	}

	int compare_string( const dx::String &Left, const dx::String &Right, const bool &ignore_whitespace = true )
	{
		auto lIt = Left.c_str( ), lEnd = lIt + Left.length( );
		auto rIt = Right.c_str( ), rEnd = rIt + Right.length( );
	
		int count = 0;
		for ( ;lIt < lEnd && rIt < rEnd; )
		{
			auto lChar = *lIt, rChar = *rIt;
		
			if ( (rChar == ' ' || lChar == ' ') && ignore_whitespace  )
			{
				if ( rChar == ' ' )
				{
					++count;
					++rIt;
				}
				++lIt;
				continue;
			}
		
			if ( rChar != lChar )
				return count;
			++count;
			++rIt, ++lIt;
		}
		
		return count;
	}

	bool check_correctness( const dx::String &text )
	{
		++ccpm_;
		// On the way to being correct:
		// Wheat
		// Wrong:
		// Red
		// Right:
		// Green
		auto res = compare_string( word_->container.text, text );

		// Green all good to go!
		if ( res == word_->container.text.length( ) )
		{
			word_->container.color = dx::Colors::Green;
			++cpm_;
			return true;
		}
		// Well it contains all of the characters from the current
		// typed text, so it gets wheat.
		else if ( res == text.length( ) )
		{
			word_->container.color = dx::Colors::Wheat;
			++cpm_;
			return false;
		}
		// Whoop, error.
		word_->container.color = dx::Colors::Red;
		return false;
	}


};



#pragma warning( disable : 4996 )
int main( )
{
	//FreeConsole( );
	// Create application
	auto appl = dx::Application::Create( );

	// Set tick rate
	appl->setTickRate( 10 );

	// Create window & painter

	//  width: 768     height: 362
	auto window = dx::Window::Create( "ClassName", "UI Test", { { 300, 300 }, { 930, 362 } } );
	auto painter = dx::Painter::Create( window );
	
	// Only paint on Event
	window->SpecializePaint( dx::Window::OnTick_t );

	// Show
	window->Show( );

	// Bring to top
	window->BringToTop( );

	window->LoadIcon( "res/icons/Icon.ico" );
	window->LoadIconSm( "res/icons/Icon.ico" );

	// Handle the closing of our window
	window->OnWindowClosed( ) += []( dx::Window *sender )
	{
		// Exit the application
		dx::Application::get( )->exit( );
	};
	
	// Lets change the current default font, we dont want the font to be Arial
	auto context = painter->defaultFont( )->context( );
	context.Height = 20;
	context.Weight = 75;
	painter->setDefaultFont( dx::Font::Create( "Consolas", context ) );

	// Do background
	auto texture = dx::Texture::Create( "res/icons/Icon.png" );
	window->OnPaint( ) += [&texture]( dx::Window *sender, dx::BasePainter *painter )
	{
		painter->PaintRect( { { 0, 0 }, { sender->Width( ), sender->Height( ) } }, dx::Pen( dx::Colors::DarkSlateGray, 1 ) );
		texture->Paint( { 15, 15 }, { 1, 1 } );
	};

	Form* form = new Form( window );

	return appl->run( );
}
