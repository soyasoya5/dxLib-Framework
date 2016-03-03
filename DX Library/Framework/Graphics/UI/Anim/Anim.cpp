#include "Anim.h"

namespace Graphics {
	namespace UI {
		namespace Anim {

			Graphics::UI::Anim::Tick::Tick(Utils::Clock &clock)
				: _clock(clock), _tick(0), _did_action(false), _anim_complete(false)
			{
			}

			Utils::Clock &Graphics::UI::Anim::Tick::Clock()
			{
				return _clock;
			}

			double Graphics::UI::Anim::Tick::getTick()
			{
				return _tick;
			}

			void Graphics::UI::Anim::Tick::setTick(const double &t)
			{
				_tick = t;
			}

			bool Graphics::UI::Anim::Tick::CompletedAction()
			{
				return _did_action;
			}

			bool Graphics::UI::Anim::Tick::AnimationCompleted()
			{
				return _anim_complete;;
			}

			void Graphics::UI::Anim::Tick::set_did_action(const bool &b)
			{
				_did_action = b;
			}

			void Graphics::UI::Anim::Tick::set_anim_complete(const bool &b)
			{
				_anim_complete = b;
			}

			Graphics::UI::Anim::AnimationHandler::~AnimationHandler()
			{
				delete _tick, _clock;
			}

			void Graphics::UI::Anim::AnimationHandler::setComponent(UI::Component *comp)
			{
				_component = comp;
			}

			UI::Component * Graphics::UI::Anim::AnimationHandler::getComponent()
			{
				return _component;
			}

			Tick * AnimationHandler::getTick()
			{
				return _tick;
			}

			bool AnimationHandler::Start()
			{
				if ( !_component || _running )
					return false;
				_running = true;
				_clock->Start( );
				return true;
			}

			bool AnimationHandler::Stop()
			{
				if ( !_running )
					return false;
				_running = false;
				return true;
			}

			bool AnimationHandler::isCompleted()
			{
				return _tick->AnimationCompleted( );
			}

			void Graphics::UI::Anim::AnimationHandler::Tick()
			{
				if ( !_running )
					return;
				_tick->set_did_action( false ); // Reset action
				_clock->End( );
				_tick->setTick( _tick->getTick( ) + std::abs( _clock->Milli( ) ) );
				_func( _component, _tick );
				_clock->Start( );

				if ( _tick->CompletedAction( ) )
					_tick->setTick( 0 );
			}

		}
	}
}
