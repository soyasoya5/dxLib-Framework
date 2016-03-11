#pragma once
class Win32Window;
struct WindowEventParams;
#include "../Utils/string.h"
#include "UI\BackgroundTask.h"


namespace Graphics {
	namespace Renderer { class D9Renderer; }
	namespace UI { class Canvas; class Window; class Text; }

	enum DialogType : uint
	{
		Dialog_ok,
		Dialog_yes_no,
		Dialog_yes_no_cancel,
		Dialog_continue,
	};

	enum DialogResult : uint
	{
		Result_Ok,
		Result_Yes,
		Result_No,
		Result_Cancel,
		Result_Continue
	};

	class Task
	{
	public:
		typedef std::chrono::high_resolution_clock clock;
		typedef std::chrono::time_point<clock> time_point;
		typedef std::function<void(void*)> function;
		

	private:
		void* _data;
		function _func;
		time_point _time;
	public:
		Task( void *_Data, const function &_Func, const time_point &_Time );
		bool do_task_if_time( const time_point &_Point );
	};

	class Form : public Object
	{
	protected:
		friend class Win32Window;
		Win32Window* _win32window;
		UI::Window* _window;
		UI::Canvas* _canvas;
		std::vector<Task> _tasks;
		dx::AsyncKeeper _task_kpr;

	public:
		virtual void Initalize( ) = 0;
		virtual void Tick( ) = 0;
		void DoTick( );
		

		virtual void Paint( Renderer::D9Renderer* );
		void PaintSafe( Renderer::D9Renderer* );

		virtual bool Event( WindowEventParams );

		virtual void Release( );

		// For async
		void addTask( void* _Data,
					  const std::chrono::time_point<std::chrono::high_resolution_clock> &_Time, 
					  const std::function<void(void*)> &_Task );
		
		pointer<UI::Window> Dialog( const DialogType &_Type,
									const std::initializer_list<UI::Text> &_Text,
									const Utils::String &_Title,
									const Utils::String &_Name,
									std::function<void(DialogResult, pointer<UI::Window>, pointer<UI::Canvas>)> _Event );

		pointer<UI::Window> Dialog( const DialogType &_Type,
									const std::initializer_list<UI::Text> &_Text,
									const Utils::String &_Title,
									const Utils::String &_Name,
									std::function<void(DialogResult, pointer<UI::Window>, pointer<UI::Canvas>)> _Event,
									pointer<UI::Window> _Window );

		template<typename _Duration = std::chrono::milliseconds, typename _Func>
		void PerformTaskIn( _Duration &&duration, _Func &&func )
		{
			auto time = std::chrono::duration_cast<std::chrono::milliseconds>( std::forward<_Duration>( duration ) );
			_tasks.push_back( Task{ time, std::forward<_Func>( func ) } );
		}



	public:
		Win32Window* getWin32( );
		UI::Window* getWindow( );
		UI::Canvas* getCanvas( );

	};

	

	

}