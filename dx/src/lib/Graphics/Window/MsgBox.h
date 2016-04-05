#pragma once
#include "../lib.h"
#include "../../string.h"


begin_GRAPHICS
class Window;

enum DialogType
{
	AbortRetryIgnore = MB_ABORTRETRYIGNORE,
	CancelTryContinue = MB_CANCELTRYCONTINUE,
	Help = MB_HELP,
	OK = MB_OK,
	OKCancel = MB_OKCANCEL,
	RetryCancel = MB_RETRYCANCEL,
	YesNo = MB_YESNO,
	YesNoCancel = MB_YESNOCANCEL,
	IconExclamation = MB_ICONEXCLAMATION,
	IconWarning = MB_ICONWARNING,
	IconInformation = MB_ICONINFORMATION,
	IconAsterisk = MB_ICONASTERISK,
	IconQuestion = MB_ICONQUESTION,
	IconStop = MB_ICONSTOP,
	IconError = MB_ICONERROR,
	IconHand = MB_ICONHAND,
	RightText = MB_RIGHT,
	RTLReading = MB_RTLREADING,
	SetForeground = MB_SETFOREGROUND,
	Topmost = MB_TOPMOST,
	ServiceNotification = MB_SERVICE_NOTIFICATION
};

class MsgBox
{
public:
	enum DialogResult
	{
		Abort = IDABORT,
		Cancel = IDCANCEL,
		Continue = IDCONTINUE,
		Ignore = IDIGNORE,
		No = IDNO,
		Ok = IDOK,
		Retry = IDRETRY,
		TryAgain = IDTRYAGAIN,
		Yes = IDYES
	};

public:
	MsgBox( ) = delete;
	
	///<summary>
	///	Construct message box.
	///</summary>
	MsgBox( const __LIB String &_Message, 
			const __LIB String &_Title,
			const __DX uint &_Type );

	///<summary>
	///	Construct message box as a popup from '_Parent'.
	/// Meaning that '_Parent' will not function untill this
	/// MsgBox is closed.
	///</summary>
	MsgBox( __GRAPHICS Window *_Parent,
			const __LIB String &_Message, 
			const __LIB String &_Title,
			const __DX uint &_Type );

	///<summary>
	///	Show the dialog.
	///</summary>
	DialogResult Show( );
private:
	__GRAPHICS Window *_parent;
	__LIB String _msg, _title;
	__DX uint _type;
};

end_GRAPHICS

