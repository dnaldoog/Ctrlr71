#include "stdafx.h"
#include "CtrlrButton.h"
#include "CtrlrValueMap.h"
#include "CtrlrIDs.h"
#include "CtrlrModulator/CtrlrModulator.h"
#include "CtrlrPanel/CtrlrPanel.h"

//==============================================================================
CtrlrButton::CtrlrButton (CtrlrModulator &owner)
    : CtrlrComponent(owner),
      ctrlrButton (0)
{
	valueMap = new CtrlrValueMap();
    addAndMakeVisible (ctrlrButton = new TextButton ("ctrlrButton"));
    ctrlrButton->addListener (this);

    //[UserPreSize]
    ctrlrButton->addMouseListener(this, true);
	ctrlrButton->setBufferedToImage (true);
	setProperty (Ids::uiButtonTrueValue, 1);
	setProperty (Ids::uiButtonFalseValue, 0);
	setProperty (Ids::uiButtonIsToggle, false);;
	setProperty (Ids::uiButtonColourOn, "0xff0000ff");
	setProperty (Ids::uiButtonColourOff, "0xff4364ff");
	setProperty (Ids::uiButtonTextColourOn, "0xff000000");
	setProperty (Ids::uiButtonTextColourOff, "0xff454545");
	setProperty (Ids::uiButtonContent, "False\nTrue");
	setProperty (Ids::uiButtonConnectedLeft, false);
	setProperty (Ids::uiButtonConnectedRight, false);
	setProperty (Ids::uiButtonConnectedTop, false);
	setProperty (Ids::uiButtonConnectedBottom, false);
	setProperty (Ids::uiButtonRepeat, false);
	setProperty (Ids::uiButtonRepeatRate, 100);
	setProperty (Ids::uiButtonTriggerOnMouseDown, false);
	setProperty (Ids::componentInternalFunction, COMBO_ITEM_NONE);
    //[/UserPreSize]

    setSize (88, 32);

    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

CtrlrButton::~CtrlrButton()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    deleteAndZero (ctrlrButton);

    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void CtrlrButton::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void CtrlrButton::resized()
{
	ctrlrButton->setBounds (getUsableRect());
}

void CtrlrButton::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    if (isInternal())
	{
		owner.getOwnerPanel().performInternalComponentFunction(this);
		return;
	}

	if (!owner.getOwnerPanel().checkRadioGroup(this, buttonThatWasClicked->getToggleState()))
		return;
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == ctrlrButton)
    {
        //[UserButtonCode_ctrlrButton] -- add your button handler code here..
		valueMap->increment();
		ctrlrButton->setButtonText (valueMap->getCurrentText());
		setComponentValue (valueMap->getCurrentNonMappedValue(), true);
        //[/UserButtonCode_ctrlrButton]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}

void CtrlrButton::mouseDown (const MouseEvent& e)
{
    //[UserCode_mouseDown] -- Add your code here...
    if ((bool)getProperty(Ids::uiButtonTriggerOnMouseDown) == true)
    {
        if (e.eventComponent == ctrlrButton)
        {
            if (!isTimerRunning() && (bool)getProperty(Ids::uiButtonRepeat))
            {
                startTimer ((int)getProperty(Ids::uiButtonRepeatRate));
            }

            if (getProperty(Ids::uiButtonTriggerOnMouseDown))
            {
                ctrlrButton->triggerClick();
            }
        }
    }
	CtrlrComponent::mouseDown(e);
    //[/UserCode_mouseDown]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void CtrlrButton::timerCallback()
{
	if (ctrlrButton->isMouseButtonDown())
	{
		ctrlrButton->triggerClick();
	}
	else
	{
		stopTimer();
	}
}

void CtrlrButton::setComponentValue (const double newValue, const bool sendChangeMessage)
{
	valueMap->setCurrentNonMappedValue (newValue);
	ctrlrButton->setButtonText (valueMap->getTextForIndex (newValue));

	if (ctrlrButton->getClickingTogglesState())
	{
		if ((double)getProperty(Ids::uiButtonTrueValue) == newValue)
		{
			ctrlrButton->setToggleState (true, dontSendNotification);
			valueMap->setCurrentNonMappedValue (1);
		}
		else
		{
			ctrlrButton->setToggleState (false, dontSendNotification);
			valueMap->setCurrentNonMappedValue (0);
		}
	}

	if (sendChangeMessage)
	{
		owner.getProcessor().setValueGeneric (CtrlrModulatorValue(newValue,CtrlrModulatorValue::changedByGUI), sendChangeMessage);
	}
}

double CtrlrButton::getComponentMaxValue()
{
	return (valueMap->getNonMappedMax());
}

bool CtrlrButton::getToggleState()
{
	return (ctrlrButton->getToggleState());
}

const String CtrlrButton::getComponentText()
{
	return (ctrlrButton->getButtonText());
}

void CtrlrButton::setComponentText (const String &componentText)
{
	setComponentValue (valueMap->getNonMappedValue(componentText));
}

double CtrlrButton::getComponentValue()
{
	return (valueMap->getCurrentNonMappedValue());
}

int CtrlrButton::getComponentMidiValue()
{
	return (valueMap->getCurrentMappedValue());
}

void CtrlrButton::buttonContentChanged()
{
	valueMap->copyFrom (owner.getProcessor().setValueMap (getProperty (Ids::uiButtonContent)));
	setComponentValue (0, false);
}

void CtrlrButton::valueTreePropertyChanged (ValueTree &treeWhosePropertyHasChanged, const Identifier &property)
{
	if (property == Ids::uiButtonContent)
	{
		buttonContentChanged();
	}

	else if (property == Ids::uiButtonColourOff
		|| property == Ids::uiButtonColourOn
		|| property == Ids::uiButtonTextColourOff
		|| property == Ids::uiButtonTextColourOn)
	{
		ctrlrButton->setColour (TextButton::buttonColourId, VAR2COLOUR(getProperty(Ids::uiButtonColourOff)));
		ctrlrButton->setColour (TextButton::buttonOnColourId, VAR2COLOUR(getProperty(Ids::uiButtonColourOn)));
		ctrlrButton->setColour (TextButton::textColourOffId, VAR2COLOUR(getProperty(Ids::uiButtonTextColourOff)));
		ctrlrButton->setColour (TextButton::textColourOnId, VAR2COLOUR(getProperty(Ids::uiButtonTextColourOn)));
	}

	else if (property == Ids::uiButtonIsToggle)
	{
		ctrlrButton->setClickingTogglesState((bool)getProperty(property));
	}


	else if (property == Ids::uiButtonConnectedLeft
		|| property == Ids::uiButtonConnectedRight
		|| property == Ids::uiButtonConnectedTop
		|| property == Ids::uiButtonConnectedBottom
		)
	{
		const int leftFlag = (bool)getProperty(Ids::uiButtonConnectedLeft) ? Button::ConnectedOnLeft : 0;
		const int rightFlag = (bool)getProperty(Ids::uiButtonConnectedRight) ? Button::ConnectedOnRight : 0;
		const int topFlag = (bool)getProperty(Ids::uiButtonConnectedTop) ? Button::ConnectedOnTop : 0;
		const int bottomFlag = (bool)getProperty(Ids::uiButtonConnectedBottom) ? Button::ConnectedOnBottom : 0;
		ctrlrButton->setConnectedEdges (leftFlag | rightFlag | topFlag | bottomFlag);
	}
	else if (property == Ids::uiButtonTrueValue)
	{
		owner.setProperty (Ids::modulatorMax, getProperty(property));
	}
	else if (property == Ids::uiButtonFalseValue)
	{
		owner.setProperty (Ids::modulatorMin, getProperty(property));
	}
	else if (property == Ids::uiButtonRepeat)
	{
		if ((bool)getProperty(property) == false)
        {
			stopTimer();
		}
	}
	else
	{
		CtrlrComponent::valueTreePropertyChanged(treeWhosePropertyHasChanged, property);
	}

	if (restoreStateInProgress == false)
	{
		resized();
	}
}

void CtrlrButton::click()
{
	ctrlrButton->triggerClick();
}

bool CtrlrButton::isToggleButton()
{
	return (ctrlrButton->getClickingTogglesState());
}

void CtrlrButton::setToggleState(const bool toggleState, const bool sendChangeMessage)
{
	ctrlrButton->setToggleState (toggleState, sendChangeMessage ? sendNotification : dontSendNotification);
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Jucer information section --

    This is where the Jucer puts all of its metadata, so don't change anything in here!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="CtrlrButton" componentName=""
                 parentClasses="public CtrlrComponent" constructorParams="CtrlrModulator &amp;owner"
                 variableInitialisers="CtrlrComponent(owner)" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330000013" fixedSize="1" initialWidth="88"
                 initialHeight="32">
  <METHODS>
    <METHOD name="mouseDown (const MouseEvent&amp; e)"/>
  </METHODS>
  <BACKGROUND backgroundColour="ffffff"/>
  <TEXTBUTTON name="ctrlrButton" id="d906fca95b2d6ff7" memberName="ctrlrButton"
              virtualName="" explicitFocusOrder="0" pos="0 0 0M 0M" buttonText="Button"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif
