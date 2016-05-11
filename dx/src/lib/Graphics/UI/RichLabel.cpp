#include "RichLabel.h"
#include "../Font.h"
#include "../Text.h"
#include "../Pen.h"
#include "../Texture.h"

begin_UI

RichLabel::RichLabel()
	: Component()
{
	OnModified() += ::dx::lib::EventHandler<void(Component*)>("Constructor_Watcher",
		[this](Component *component) 
	{
		this->changed_ = true; 
	});
	changed_ = true;
}

void RichLabel::Paint(Window *sender, BasePainter *painter)
{
	if ( !isVisible( ) )
		return;
	OnPrePaint( ).Invoke( this, painter );

	// Just incase :P
	FlexibleGuard guard{ kpr_ };

	auto pos = determineRegion();


	::dx::lib::Math::Vector2 fullsize{ 0, 0 };
	for ( auto it = all_text_.begin(), begin = all_text_.begin(), end = all_text_.end(); 
		  it < end; 
		  ++it )
	{
		// First lets check if we changed
		if ( changed_ ) // If so recalculate everything
		{
			// Check font
			if ( !it->container.font )
				it->container.font = (getFont( ) ? getFont( ) : painter->defaultFont( ));

			// Recalculate position
			if ( it == begin ) // First...
			{
				it->position = pos.position;
				it->container.orig_tex_y = it->position.y;
			}
			else
			{
				auto prev = (it - 1);

				// did the previus node end on a new line
				if ( prev->container.new_line ) 
				{
					it->position = { pos.position.x, prev->position.y + prev->size.y }; // kk then get original x pos and the prev y + its size
					it->container.orig_tex_y = it->position.y;
				}
				else if ( it->container.is_texture )
				{
					it->position.x = prev->position.x + prev->size.x + 8;
					it->position.y = (prev->size.y / 2 - it->container.texture->getSize( ).y / 2) + prev->position.y;
					it->container.orig_tex_y = prev->container.orig_tex_y;
				}
				else
				{
					// Is prev texture
					if ( prev->container.is_texture )
					{
						// Set x
						it->position.x = prev->position.x + prev->size.x;

						// Now allign y PROPERLY.
						it->position.y = prev->container.orig_tex_y;

						// Set this ones orig_tex_y
						it->container.orig_tex_y = prev->container.orig_tex_y;
					}
					else
					{
						// Set position
						it->position = prev->position + ::dx::lib::Math::Vector2{ prev->size.x, 0.0f }; // Ok then get the vector of prev pos + prev size(x only)
						// Set orig
						it->container.orig_tex_y = it->position.y;
					}
				}
			}

			// Size
			it->size = (it->container.is_texture ? 
						it->container.texture->getSize( ) : 
						it->container.font->calculateMetrixOf( it->container.text ));

			if ( it->container.new_line )
				fullsize.y += it->size.y;
			else if ( it->size.x > fullsize.x )
				fullsize.x = it->size.x;

			if ( fullsize.y == 0 )
				fullsize.y = it->size.y;
		}
		// Right, lets draw
		if ( it->container.is_texture )
			it->container.texture->Paint( it->position, { 1, 1 } );
		else
		{
			Text text;
			text.setPosition( it->position );
			text.setFont( it->container.font );
			text.setText( it->container.text );
			text.setMaxClip( it->size );

			// Paintaronie
			painter->Paint( text, Pen( it->container.color, 1 ) );
		}
	}

	// We dont wanna raise a modified event if its not needed, obviously.
	if ( local_.size != fullsize && fullsize != Math::Vector2{ 0, 0 } )
		this->setSize( fullsize );

	changed_ = false;
	OnPostPaint( ).Invoke( this, painter );
}

void RichLabel::appendText( String text, std::shared_ptr<Font> font, uint color)
{
	text_.append( text );

	if ( text.contains( "\n" ) )
	{
		auto vecs = text.split( '\n' );
		for ( auto text : vecs )
		{
			TextContainer container;
			container.text = std::move( text );
			container.font = font;
			container.color = std::move( color );
			container.new_line = true;
			container.is_texture = false;
			container.is_selected = false;
			contrs_.push_back( std::move( container ) );
		}
	}
	else
	{
		TextContainer container;
		container.text = std::move( text );
		container.font = font;
		container.color = std::move( color );
		container.new_line = false;
		container.is_texture = false;
		container.is_selected = false;
		contrs_.push_back( std::move( container ) );
	}

	OnModified( ).Invoke( this );
	recalculate_text( );
}

void RichLabel::appendText( String text, std::shared_ptr<Font> font)
{
	appendText( std::move( text ), font, Colors::White );
}

void RichLabel::appendText(String text, uint color)
{
	appendText( std::move( text ), getFont( ), std::move( color ) );
}

void RichLabel::appendText( String text )
{
	appendText( std::move( text ), getFont( ), Colors::White );
}

void RichLabel::appendText(std::shared_ptr<Texture> texture)
{
	if ( texture->getSize( ) > ::dx::lib::Math::Vector2{ 64, 64 } )
		return;
	TextContainer container;
	container.text = "";
	container.font = nullptr;
	container.color = 0;
	container.new_line = false;
	container.is_selected = false;
	container.is_texture = true;
	container.texture = texture;
	contrs_.push_back( std::move( container ) );
	OnModified( ).Invoke( this );
	recalculate_text( );
}


void RichLabel::setText(const ::dx::lib::String & text)
{
	text_ = text;
	contrs_.clear();
	contrs_.push_back( TextContainer{ nullptr, text, ::dx::Colors::White, getFont( ), false, false } );
	recalculate_text();
}

RichLabel::RichText * RichLabel::textAt(const int & index)
{
	return &all_text_[index];
}

RichLabel::RichText * RichLabel::textFrom(const std::function<bool(RichText*)>& functor)
{
	for ( auto&x : all_text_ )
		if ( functor( &x ) )
			return &x;
	return nullptr;
}

RichLabel::RichText * RichLabel::textFromText(const ::dx::lib::String & text)
{
	for ( auto&x : all_text_ )
		if ( x.container.text == text )
			return &x;
	return nullptr;
}

RichLabel::RichText * RichLabel::textInRegion(const ::dx::lib::Math::Region & region)
{
	for ( auto &x : all_text_ )
		if ( x.position.Intersects( region ) )
			return &x;
	return nullptr;
}

void RichLabel::clearText()
{
	text_ = "";
	all_text_.clear();
	contrs_.clear();
	changed_ = true;
}

AsyncKeeper & RichLabel::AquireMutex()
{
	return kpr_;
}

void RichLabel::recalculate_text()
{
	// Setup ze mutex just incase some retard appends text in another thread :|
	AsyncGuard guard{ kpr_ };

	// Clear text container
	all_text_.clear();

	for ( auto cont : contrs_ )
	{
		RichText text;
		text.container = std::move( cont );
		text.position = { -1, -1 };
		text.size = { -1, -1 };
		all_text_.push_back( std::move( text ) );
	}
}




end_UI