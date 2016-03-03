#pragma once
#include "../../../dx.h"
#include "../../../Utils/Clock.h"

namespace Graphics {
	namespace UI {
		class Component;
		namespace Anim {

			// A tick 'counter'.
			class Tick
			{
				Utils::Clock& _clock;
				double _tick;
				bool _did_action;
				bool _anim_complete;

			public:
				Tick( Utils::Clock& );

				Utils::Clock& Clock( );

				double getTick( );
				void setTick( const double& );

				// If the current tick completed a action
				// e.g incrementing an integer.
				bool CompletedAction( );

				// If the current tick completed the animation
				// (Meaning it is done)
				bool AnimationCompleted( );


				void set_did_action( const bool& );
				void set_anim_complete( const bool& );
			};

			class AnimationHandler
			{
			protected:
				bool _running;
				Tick* _tick;
				Utils::Clock* _clock;
				UI::Component* _component;
				std::function<void(UI::Component*, Tick*)> _func;


			public:
				
				AnimationHandler( std::function<void(UI::Component*, Tick*)> func )
				{
					_func = ( func );
					_clock = new Utils::Clock( );
					_tick = new Anim::Tick( *_clock );
					_tick->set_anim_complete( false );
					_tick->set_did_action( false );
				}
				~AnimationHandler( );

				void setComponent( UI::Component* );
				UI::Component* getComponent( );
				Tick* getTick( );
				bool Start( );
				bool Stop( );
				bool isCompleted( );
				void Tick( );
			};
			
			// e.g a fade animation for a button
			/*	
				button->setAnimation( AnimationHandler( 
										[](Graphics::UI::Component* comp, Graphics::UI::Anim::Tick* tick)
										{
											if (tick->getTick() > 250)
											{
												auto style = comp->getStylesheet();
												style.set_value( "ui_button", Graphics::Style::Style_foreground, Graphics::Style::A,
																 std::to_string( (style.get_value( "ui_button", Graphics::Style::Style_foreground, Graphics::Style::A ) - 1) ) 
															   );
												comp->setStylesheet( style );
												tick->set_did_action(true);
											}
										}; ) );
			*/


		}
	}
}


