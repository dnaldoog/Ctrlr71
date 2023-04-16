#ifndef __CTRLR_SYSEX_PROCESSOR__
#define __CTRLR_SYSEX_PROCESSOR__

#include "CtrlrSysexToken.h"

class CtrlrManager;
class CtrlrMidiMessage;
class CtrlrMidiMessageEx;
class CtrlrPanel;

class CtrlrSysexProcessor
{
	public:
		CtrlrSysexProcessor();
		virtual ~CtrlrSysexProcessor();
		virtual void sysexProcessChecksums(const Array<CtrlrSysexToken> &tokens, MidiMessage &midiMessage);
		virtual void sysexProcessPrograms(const Array<CtrlrSysexToken> &tokens, MidiMessage &m);
		virtual void sysExProcess (const Array<CtrlrSysexToken> &tokens, MidiMessage &m, const int value, const int channel);
		virtual Array <int,CriticalSection> &getGlobalVariables()																	{ return (unknownGlobalVariables); }
		virtual void sysExProcessToken (const CtrlrSysexToken token, uint8 *byte, const int value, const int channel);
		virtual double getValueFromSysExData (const Array<CtrlrSysexToken> &tokens, const CtrlrMidiMessageEx &message);

		const StringArray templatesPrepare();

		void checksumRolandJp8080(const CtrlrSysexToken token, MidiMessage &m);
		uint8 getRolandSplit (const int value, const int byteNum);
		void checksumWaldorfRackAttack(const CtrlrSysexToken token, MidiMessage &m);
		int getGlobalIndex(const CtrlrSysexToken token);

		static double getValue(const Array<CtrlrSysexToken> &tokens, const CtrlrMidiMessageEx &message);
		static void setSysExFormula(CtrlrMidiMessage &message, const String &formulaString);
		static void setMultiMessageFromString(CtrlrMidiMessage &message, const String &savedState);
		static CtrlrMidiMessageEx sysexMessageFromString (const String &formula, const int value, const int channel);
		static Array<CtrlrSysexToken> sysExToTokenArray (const String &formula);
		static CtrlrSysExFormulaToken sysExIdentifyToken(const String &tokenString);

		JUCE_LEAK_DETECTOR(CtrlrSysexProcessor)

	private:
		Array <int,CriticalSection> unknownGlobalVariables;
};

#endif
