#ifndef __CTRLR_MACROS_H__
#define __CTRLR_MACROS_H__

#include "stdafx.h"

#ifdef JUCE_WINDOWS
#pragma warning(disable:4355)
#pragma warning(disable:4127)
#pragma warning(disable:4996)
#pragma warning(disable:4996)
#pragma warning(disable:4512)
#pragma warning(disable:4100)
#pragma warning(disable:4244)
#pragma warning(disable:4297)
#pragma warning(disable:4505)
#endif

#define CTRLR_PANEL_SCHEME				4
#define COMBO_NONE_ITEM					"-- None"
#define COMBO_ITEM_NONE					COMBO_NONE_ITEM
#define CTRLR_PROPERTIES_FILTER_STATE	"CTRLR_FILTER_STATE"
#define CTRLR_PROPERTIES_WINDOW_STATE	"CTRLR_WINDOW_STATE"
#define CTRLR_MENUBAR_HEIGHT			24
#define	CTRLR_DEFAULT_PARAMETER_COUNT	128

#define DEBUGGER __asm int 3

#ifdef JUCE_DEBUG
#define PC_START(x)			PerformanceCounter pc(x,1); pc.start();
#define PC_END()			pc.stop();
#else
#define PC_START(x)
#define PC_END
#endif

#define UID_NULL			Uuid((const uint8 *)nullptr)
#define SAMPLERATE			44100

#define MENU_OFFSET_MIDI		        0x10000
#define MENU_OFFSET_PROGRAMS	        0x30000
#define MENU_OFFSET_MIDI_DEV_IN         0x71000
#define MENU_OFFSET_MIDI_DEV_OUT        0x72000
#define MENU_OFFSET_MIDI_DEV_CTRLR      0x73000
#define MENU_OFFSET_MIDI_HOST_IN        0x74000
#define MENU_OFFSET_MIDI_HOST_OUT       0x75000
#define MENU_OFFSET_MIDI_INTERNAL_IN    0x76000
#define MENU_OFFSET_MIDI_INTERNAL_OUT   0x77000
#define MENU_OFFSET_CUSTOM_REQUESTS		0x78000

#define MENU_OFFSET_PROGRAM_LIST		0x80000

#define WARN(x)													AlertWindow::showMessageBox (AlertWindow::WarningIcon, "WARNING", x, "OK", nullptr)
#define INFO(x,y)												AlertWindow::showMessageBox (AlertWindow::InfoIcon, x, y, "OK", nullptr)
#define SURE(x,y)												AlertWindow::showOkCancelBox (AlertWindow::QuestionIcon, "Are you sure?", x, "Yes", "No", y, nullptr)
#define _STR(x)                                                 String(x)
#define STR(x)													_STR(x)
#define IMAGE(x)												ImageCache::getFromMemory(BinaryData::x, BinaryData::x ## Size)
#define STR2RECT(x)												Rectangle<int>::fromString(x)
#define VAR2RECT(x)												STR2RECT(x.toString())
#define STR2COLOUR(x)											Colour::fromString(x)
#define VAR2COLOUR(x)											STR2COLOUR(x.toString())
#define COLOUR2STR(x)											x.toString()
#define BIN2STR(x)                                              String(BinaryData::x, BinaryData::x ## Size)
#define STR2LUASTR(x)											x.toUTF8().getAddress()
#define XML2STR(x)												ScopedPointer <XmlElement> (x.createXml().release())->createDocument("")
#define DUMPTREE(x,y)                                           ScopedPointer <XmlElement> (x.createXml().release())->createDocument("").substring(0,y)
#define STR2FONT(x)												getFontManager().getFontFromString(x)
#define STR2FONTM(m,x)											m.getFontFromString(x)
#define FONT2STR(x)												getFontManager().getStringFromFont(x)
#define FONT2STRM(m,x)											m.getStringFromFont(x)
#define INTERNAL_FONT(x)										getFontManager().getFont (BinaryData::x, BinaryData::x ## Size)
#define HIGHLIGHT_COLOUR										0xff4364ff
#define MAXZOOM                                                 10.0
#define MINZOOM                                                 0.01

#define VST_INDEX_MANUFACTURER			1025
#define VST_INDEX_VERSION_CODE			1026
#define VST_INDEX_VERSION_STRING		1027
#define VST_INDEX_UNIQUEID				1028
#define VST_INDEX_NAME					1029

//==============================================================================
/** Used in SysEx formula editor
*/
enum CtrlrSysExFormulaToken
{
	ByteValue,
	ByteChannel,
	ByteChannel4Bit,
	LSB7bitValue,
	MSB7bitValue,
	LSB4bitValue,
	MSB4bitValue,
	GlobalVariable,
	ChecksumRolandJP8080,
	RolandSplitByte1,
	RolandSplitByte2,
	RolandSplitByte3,
	RolandSplitByte4,
	Ignore,
	FormulaToken,
	LUAToken,
	ChecksumWaldorfRackAttack,
	CurrentProgram,
	CurrentBank,
	NoToken
};

enum CtrlrPanelMidiChannel
{
	panelMidiInputChannelDevice,
	panelMidiOutputChannelDevice,
	panelMidiInputChannelHost,
	panelMidiOutputChannelHost,
	panelMidiControllerChannel
};

enum CtrlrPanelMidiOption
{
	panelMidiInputFromHost				= 2,
	panelMidiInputFromHostCompare		= 4,
	panelMidiOutputToHost				= 8,
	panelMidiThruH2H					= 16,
	panelMidiThruH2HChannelize			= 32,
	panelMidiThruH2D					= 64,
	panelMidiThruH2DChannelize			= 128,
	panelMidiThruD2D					= 256,
	panelMidiThruD2DChannelize			= 512,
	panelMidiThruD2H					= 1024,
	panelMidiThruD2HChannelize			= 2048,
	panelMidiRealtimeIgnore				= 4096,
	panelMidiControllerToLua			= 8192
};

enum CtrlrMidiLogOptions
{
	midiLogName=2,
	midiLogChannel=4,
	midiLogNumber=8,
	midiLogValue=16,
	midiLogRawData=32,
	midiLogTimestamp=64,
	midiLogRawDecimal=128,
	midiLogInput=256,
	midiLogOutput=512,
	midiLogDevice=1024,
	midiLogDevAttach=2048,
	midiLogDataSize=4096
};

enum CtrlrFontProperties
{
	fontTypefaceName,
	fontHeight,
	fontBold,
	fontItalic,
	fontUnderline,
	fontKerning,
	fontHorizontalScale,
	fontSet
};

enum CtrlrMIDIDeviceHandler
{
	JuceMIDI,
	RtMIDI
};

class CtrlrPanelMidiProcessor
{
	public:
		virtual ~CtrlrPanelMidiProcessor() {}
		virtual void midiOptionChanged(const CtrlrPanelMidiOption optionThatChanged)=0;
		virtual void midiChannelChaned(const CtrlrPanelMidiChannel channelThatChanged)=0;
};

struct CtrlrInstanceInfo
{
	String instanceName;
	String instanceVersion;
};

class CtrlrNotificationCallback
{
	public:
		virtual ~CtrlrNotificationCallback()
		{
			masterReference.clear();
		}
		virtual void notificationClicked (const MouseEvent e) = 0;

		WeakReference<CtrlrNotificationCallback>::Master masterReference;
};

class DragAndDropSourceDetails
{
	public:
		DragAndDropSourceDetails (const DragAndDropTarget::SourceDetails &details)
			: description(details.description.toString()), sourceComponent(details.sourceComponent), localPositionX(details.localPosition.getX()), localPositionY(details.localPosition.getY())
		{
		}

		DragAndDropSourceDetails (const String &_description, Component *_sourceComponent, int _localPositionX, int _localPositionY)
			: description(_description), sourceComponent(_sourceComponent), localPositionX(_localPositionX), localPositionY(_localPositionY),
				dragImage(Image()), imageOffsetX(-1), imageOffsetY(-1)
		{
		}

		DragAndDropSourceDetails (const String &_description, Image _dragImage, int _imageOffsetX, int _imageOffsetY)
			: description(_description), dragImage(_dragImage), imageOffsetX(_imageOffsetX), imageOffsetY(_imageOffsetY)
		{
		}

		DragAndDropSourceDetails ()
			: dragImage(Image()), imageOffsetX(-1), imageOffsetY(-1),
				sourceComponent(nullptr), localPositionX(-1), localPositionY(-1)
		{
		}

		const String getDescription() const		{ return (description); }
		Component *getSourceComponent() const	{ return (sourceComponent); }
		int getLocalPositionX() const			{ return (localPositionX); }
		int getLocalPositionY() const			{ return (localPositionY); }
		int getImageOffsetX() const				{ return (imageOffsetX); }
		int getImageOffsetY() const				{ return (imageOffsetY); }
		Image getDragImage() const				{ return (dragImage); }

	private:
		String description;
		Component *sourceComponent;
		int localPositionX;
		int localPositionY;
		Image dragImage;
		int imageOffsetX;
		int imageOffsetY;
};

enum CtrlrInstance
{
	InstanceSingle,
	InstanceMulti,
	InstanceSingleRestriced,
	InstanceSingleEngine,
	InstanceMultiEngine,
	InstanceSingleRestrictedEngine
};

enum CtrlrNotificationType
{
	NotifySuccess,
	NotifyFailure,
	NotifyInformation,
	NotifyWarning
};

enum CtrlrByteSplit
{
	SplitNone,
    Split4Bits,
    Split7Bits,
    Split8Bits
};

enum CtrlrByteEncoding
{
	EncodeNormal,
	EncodeMSBFirst,
	EncodeLSBFirst,
	EncodeDSI
};

enum CtrlrMIDIDeviceType
{
    outputDevice,
    inputDevice,
    controllerDevice,
    hostInputDevice,
    hostOutputDevice,
    oscInputDevice,
    oscOutputDevice,
    serialDevice
};

enum CtrlrPanelResourceType
{
	ImageRes,
	AudioRes,
	TextRes,
	XmlRes,
	FontRes,
	DataRes
};

#endif

