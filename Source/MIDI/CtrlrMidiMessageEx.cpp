#include "stdafx.h"
#include "CtrlrUtilities.h"
#include "CtrlrMidiMessageEx.h"
#include "CtrlrLog.h"

/** CtrlrMidiMessageEx container implementation

*/

CtrlrMidiMessageEx::CtrlrMidiMessageEx()
	:	indirectValueFlag(ByteValue),
		indirectNumberFlag(ByteValue),
		overrideValue(-1),
		overrideNumber(-1),
		messageContainer(0,true)
{
	m.setTimeStamp(1);
}

CtrlrMidiMessageEx::CtrlrMidiMessageEx(const MidiMessage &other)
	:	m(other),
		indirectValueFlag(ByteValue),
		indirectNumberFlag(ByteValue),
		overrideValue(-1),
		overrideNumber(-1),
		messageContainer(0,true)
{
	m.setTimeStamp(1);
}

bool CtrlrMidiMessageEx::operator== (const CtrlrMidiMessageEx &other) const
{
	return (false);
}

int CtrlrMidiMessageEx::getValueInternal(const int value) const
{
	if (overrideValue >= 0)
	{
		return (indirectOperation (overrideValue, indirectValueFlag));
	}
	return (indirectOperation (jmax<int>(0,value), indirectValueFlag));
}

const BigInteger CtrlrMidiMessageEx::getBitValue()
{
	if (m.isNoteOff() || m.isNoteOn())
	{
		return (getValueAsBigInteger(m.getVelocity(), indirectValueFlag));
	}
	else if (m.isController())
	{
		return (getValueAsBigInteger(m.getControllerValue(), indirectValueFlag));
	}
	else if (m.isChannelPressure())
	{
		return (getValueAsBigInteger(m.getChannelPressureValue(), indirectValueFlag));
	}
	else if (m.isAftertouch())
	{
		return (getValueAsBigInteger(m.getAfterTouchValue(), indirectValueFlag));
	}
	else if (m.isProgramChange())
	{
		return (getValueAsBigInteger(m.getProgramChangeNumber(), indirectValueFlag));
	}
	else if (m.isPitchWheel())
	{
		return (getValueAsBigInteger(m.getPitchWheelValue(), indirectValueFlag));
	}
	return (BigInteger(0));
}

int CtrlrMidiMessageEx::getNumberInternal(const int number) const
{
	if (overrideNumber >= 0)
	{
		return (indirectOperation (overrideNumber, indirectNumberFlag));
	}

	return (indirectOperation (number, indirectNumberFlag));
}

void CtrlrMidiMessageEx::setChannel (const int channel)
{
	if (!m.isSysEx())
	{
		m.setChannel (channel);
	}
}

int CtrlrMidiMessageEx::getValue() const
{
	if (m.isNoteOff() || m.isNoteOn())
	{
		return (getValueInternal(m.getVelocity()));
	}
	else if (m.isController())
	{
		return (getValueInternal(m.getControllerValue()));
	}
	else if (m.isChannelPressure())
	{
		return (getValueInternal(m.getChannelPressureValue()));
	}
	else if (m.isAftertouch())
	{
		return (getValueInternal(m.getAfterTouchValue()));
	}
	else if (m.isProgramChange())
	{
		return (getValueInternal(m.getProgramChangeNumber()));
	}
	else if (m.isPitchWheel())
	{
		return (getValueInternal(m.getPitchWheelValue()));
	}
	return (-1);
}

void CtrlrMidiMessageEx::setValue (const int value)
{
	const int ch	= m.getChannel();

	if (m.isNoteOff() || m.isNoteOn())
	{
		m.setVelocity ((float)jmin<int>(getValueInternal(value),127)/127);
	}
	else if (m.isController())
	{
		m = MidiMessage::controllerEvent (ch, getNumberInternal(m.getControllerNumber()), jmin<int>(getValueInternal(value),127));
	}
	else if (m.isChannelPressure())
	{
		m = MidiMessage::channelPressureChange (ch, jmin<int>(getValueInternal(value),127));
	}
	else if (m.isAftertouch())
	{
		m = MidiMessage::aftertouchChange (ch, getNumberInternal(m.getNoteNumber()), jmin<int>(getValueInternal(value),127));
	}
	else if (m.isProgramChange())
	{
		m = MidiMessage::programChange (ch, jmin<int>(getValueInternal(value),127));
	}
	else if (m.isPitchWheel())
	{
		m = MidiMessage::pitchWheel (ch, jmin<int>(getValueInternal(value),16383));
	}
}

int CtrlrMidiMessageEx::getNumber() const
{
	if (m.isNoteOff() || m.isNoteOn() || m.isAftertouch())
	{
		return (getNumberInternal(m.getNoteNumber()));
	}
	else if (m.isController())
	{
		return (getNumberInternal(m.getControllerNumber()));
	}
	else if (m.isProgramChange())
	{
		return (getNumberInternal(m.getProgramChangeNumber()));
	}

	return (-1);
}

void CtrlrMidiMessageEx::setNumber (const int number)
{
	const int ch	= m.getChannel();

	if (m.isNoteOff() || m.isNoteOn())
	{
		m.setNoteNumber (getNumberInternal(number));
	}
	else if (m.isController())
	{
		m = MidiMessage::controllerEvent (ch, getNumberInternal(number), getValueInternal(m.getControllerValue()));
	}
	else if (m.isAftertouch())
	{
		m = MidiMessage::aftertouchChange (ch, getNumberInternal(number), getValueInternal(m.getAfterTouchValue()));
	}
	else if (m.isProgramChange())
	{
		m = MidiMessage::programChange (ch, getValueInternal(m.getProgramChangeNumber()));
	}
}
