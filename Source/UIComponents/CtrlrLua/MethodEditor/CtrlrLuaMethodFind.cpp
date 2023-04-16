/*
  ==============================================================================

  This is an automatically generated GUI class created by the Introjucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Introjucer version: 3.1.0

  ------------------------------------------------------------------------------

  The Introjucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-13 by Raw Material Software Ltd.

  ==============================================================================
*/

//[Headers] You can add your own extra header files here...
#include "stdafx.h"
#include "CtrlrLuaMethodEditor.h"
#include "CtrlrLuaMethodCodeEditor.h"
#include "Methods/CtrlrLuaMethodManager.h"
#include "CtrlrInlineUtilitiesGUI.h"
//[/Headers]

#include "CtrlrLuaMethodFind.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
CtrlrLuaMethodFind::CtrlrLuaMethodFind (CtrlrLuaMethodEditor &_owner)
    : owner(_owner)
{
    setName ("Search and Replace");
    addAndMakeVisible (findInput = new TextEditor (""));
    findInput->setMultiLine (true);
    findInput->setReturnKeyStartsNewLine (false);
    findInput->setReadOnly (false);
    findInput->setScrollbarsShown (true);
    findInput->setCaretVisible (true);
    findInput->setPopupMenuEnabled (true);
    findInput->setColour (TextEditor::backgroundColourId, Colours::white);
    findInput->setColour (TextEditor::outlineColourId, Colour (0x00000000));
    findInput->setColour (TextEditor::shadowColourId, Colour (0x00000000));
    findInput->setText ("");

    addAndMakeVisible (replaceInput = new TextEditor (""));
    replaceInput->setMultiLine (true);
    replaceInput->setReturnKeyStartsNewLine (false);
    replaceInput->setReadOnly (false);
    replaceInput->setScrollbarsShown (true);
    replaceInput->setCaretVisible (true);
    replaceInput->setPopupMenuEnabled (true);
    replaceInput->setColour (TextEditor::backgroundColourId, Colours::white);
    replaceInput->setColour (TextEditor::outlineColourId, Colour (0x00000000));
    replaceInput->setColour (TextEditor::shadowColourId, Colour (0x00000000));
    replaceInput->setText ("");

    addAndMakeVisible (findNext = new TextButton (""));
    findNext->setButtonText (TRANS("Find"));
    findNext->setConnectedEdges (Button::ConnectedOnLeft | Button::ConnectedOnRight);
    findNext->addListener (this);
    findNext->setColour (TextButton::buttonColourId, Colour (0xffbababa));

    addAndMakeVisible (replaceNextButton = new TextButton (""));
    replaceNextButton->setButtonText (TRANS("Next"));
    replaceNextButton->setConnectedEdges (Button::ConnectedOnLeft | Button::ConnectedOnRight);
    replaceNextButton->addListener (this);
    replaceNextButton->setColour (TextButton::buttonColourId, Colour (0xffcbf2aa));

    addAndMakeVisible (replaceAllButton = new TextButton (""));
    replaceAllButton->setButtonText (TRANS("All"));
    replaceAllButton->setConnectedEdges (Button::ConnectedOnLeft | Button::ConnectedOnRight);
    replaceAllButton->addListener (this);
    replaceAllButton->setColour (TextButton::buttonColourId, Colour (0xffa9cfff));

    addAndMakeVisible (label = new Label ("new label",
                                          TRANS("Find")));
    label->setFont (Font (16.00f, Font::bold | Font::italic));
    label->setJustificationType (Justification::centredLeft);
    label->setEditable (false, false, false);
    label->setColour (TextEditor::textColourId, Colours::black);
    label->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (matchCase = new ToggleButton (""));
    matchCase->setButtonText (TRANS("Match Case"));
    matchCase->addListener (this);

    addAndMakeVisible (label2 = new Label ("new label",
                                           TRANS("Replace")));
    label2->setFont (Font (16.00f, Font::bold | Font::italic));
    label2->setJustificationType (Justification::centredLeft);
    label2->setEditable (false, false, false);
    label2->setColour (TextEditor::textColourId, Colours::black);
    label2->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (whereToFindCombo = new ComboBox (""));
    whereToFindCombo->setEditableText (false);
    whereToFindCombo->setJustificationType (Justification::centredLeft);
    whereToFindCombo->setTextWhenNothingSelected (TRANS("Current"));
    whereToFindCombo->setTextWhenNoChoicesAvailable ("");
    whereToFindCombo->addItem (TRANS("Current"), 1);
    whereToFindCombo->addItem (TRANS("All Open"), 2);
    whereToFindCombo->addItem (TRANS("All"), 3);
    whereToFindCombo->addListener (this);


    //[UserPreSize]
	replaceInput->addListener (this);
	findInput->addListener (this);

	lastFoundPosition = -1;
	findInput->setFont (Font(16));
	replaceInput->setFont (Font(16));
    //[/UserPreSize]

    setSize (424, 64);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

CtrlrLuaMethodFind::~CtrlrLuaMethodFind()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    findInput = nullptr;
    replaceInput = nullptr;
    findNext = nullptr;
    replaceNextButton = nullptr;
    replaceAllButton = nullptr;
    label = nullptr;
    matchCase = nullptr;
    label2 = nullptr;
    whereToFindCombo = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}


void CtrlrLuaMethodFind::resized()
{
    findInput->setBounds (4, 4, proportionOfWidth (0.3302f), 32);
    replaceInput->setBounds (proportionOfWidth (0.4505f), 4, proportionOfWidth (0.3302f), 32);
    findNext->setBounds (4 + proportionOfWidth (0.3302f), 4, proportionOfWidth (0.0991f), 32);
    replaceNextButton->setBounds (proportionOfWidth (0.4505f) + proportionOfWidth (0.3302f), 4, proportionOfWidth (0.0991f), 32);
    replaceAllButton->setBounds ((proportionOfWidth (0.4505f) + proportionOfWidth (0.3302f)) + proportionOfWidth (0.0991f), 4, proportionOfWidth (0.0991f), 32);
    label->setBounds (4 + 0, 40, 64, 24);
    matchCase->setBounds (4 + 68, 40, 96, 24);
    label2->setBounds (proportionOfWidth (0.4505f) + 121, 40, 64, 24);
    whereToFindCombo->setBounds (176, 40, 128, 24);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void CtrlrLuaMethodFind::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == findNext)
    {
        //[UserButtonCode_findNext] -- add your button handler code here..
		if (whereToFindCombo->getSelectedId() == 1 || whereToFindCombo->getSelectedId() == 0)
		{
			findNextMatch();
		}
		else if (whereToFindCombo->getSelectedId() == 2)
		{
			findInOpened();
		}
		else if (whereToFindCombo->getSelectedId() == 3)
		{
			findInAll();
		}
        //[/UserButtonCode_findNext]
    }
    else if (buttonThatWasClicked == replaceNextButton)
    {
        //[UserButtonCode_replaceNextButton] -- add your button handler code here..
		replaceNextMatch();
        //[/UserButtonCode_replaceNextButton]
    }
    else if (buttonThatWasClicked == replaceAllButton)
    {
        //[UserButtonCode_replaceAllButton] -- add your button handler code here..
		replaceAllMatches();
        //[/UserButtonCode_replaceAllButton]
    }
    else if (buttonThatWasClicked == matchCase)
    {
        //[UserButtonCode_matchCase] -- add your button handler code here..
        //[/UserButtonCode_matchCase]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}

void CtrlrLuaMethodFind::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == whereToFindCombo)
    {
        //[UserComboBoxCode_whereToFindCombo] -- add your combo box handling code here..
        //[/UserComboBoxCode_whereToFindCombo]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
}

void CtrlrLuaMethodFind::visibilityChanged()
{
    //[UserCode_visibilityChanged] -- Add your code here...
	if (isVisible())
	{
		findInput->grabKeyboardFocus();
		findInput->selectAll();
	}
    //[/UserCode_visibilityChanged]
}

bool CtrlrLuaMethodFind::keyPressed (const KeyPress& key)
{
    //[UserCode_keyPressed] -- Add your code here...
	if (key.getKeyCode() == 65650) // F3
	{
	}
    return false;  // Return true if your handler uses this key event, or false to allow it to be passed-on.
    //[/UserCode_keyPressed]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void CtrlrLuaMethodFind::textEditorReturnKeyPressed (TextEditor &editor)
{
	if (&editor == findInput)
	{
		if (whereToFindCombo->getSelectedId() <= 1)
		{
			findNextMatch();
		}
		else if (whereToFindCombo->getSelectedId() == 2)
		{
			findInOpened();
		}
		else if (whereToFindCombo->getSelectedId() == 3)
		{
			findInAll();
		}
	}

	if (&editor == replaceInput)
	{
		replaceNextMatch();
	}
}

void CtrlrLuaMethodFind::textEditorTextChanged (TextEditor &editor)
{
}

void CtrlrLuaMethodFind::replaceNextMatch()
{
	if (owner.getCurrentEditor() == nullptr)
	{
		return;
	}

	CodeDocument &doc		= owner.getCurrentEditor()->getCodeDocument();
	const String search		= findInput->getText();
	const String replace	= replaceInput->getText();

	findNextMatch(); // correction to find and replace on first time also
	if (lastFoundPosition >= 0)
	{
		doc.newTransaction();
		doc.deleteSection (lastFoundPosition, lastFoundPosition+search.length());
		doc.insertText (lastFoundPosition, replace);
	}
}

void CtrlrLuaMethodFind::replaceAllMatches()
{
	lastFoundPosition = -1;

	do
	{
		replaceNextMatch();
	}
	while (lastFoundPosition >= 0);
}

void CtrlrLuaMethodFind::setFocusOnFindInput()
{
	findInput->grabKeyboardFocus();
}

void CtrlrLuaMethodFind::findNextMatch()
{
	if (owner.getCurrentEditor() == nullptr)
	{
		return;
	}

	CodeDocument &doc		= owner.getCurrentEditor()->getCodeDocument();
	CodeEditorComponent *ed	= owner.getCurrentEditor()->getCodeComponent();
	const String search		= findInput->getText();
	int position			= -1;

	if (!matchCase->getToggleState())
	{
		position = doc.getAllContent().indexOfIgnoreCase (lastFoundPosition+1, search);
	}
	else
	{
		position = doc.getAllContent().indexOf (lastFoundPosition+1, search);
	}

	if (position >= 0)
	{
		lastFoundPosition = position;
		if (ed)
		{
			ed->selectRegion (CodeDocument::Position(doc,lastFoundPosition), CodeDocument::Position(doc, lastFoundPosition+search.length()));
		}
	}
	else
	{
		lastFoundPosition = -1;
	}
}

void CtrlrLuaMethodFind::findInOpened()
{
	if (owner.getTabs() == nullptr)
		return;

	StringArray names = owner.getTabs()->getTabNames();

	owner.getMethodEditArea()->insertOutput("\n\nSearching for: \""+findInput->getText()+"\" in all opened methods (double click line to jump)\n", Colours::darkblue);

	for (int i=0; i<owner.getTabs()->getNumTabs(); i++)
	{
		CtrlrLuaMethodCodeEditor *codeEditor = dynamic_cast<CtrlrLuaMethodCodeEditor*>(owner.getTabs()->getTabContentComponent(i));

		if (codeEditor != nullptr)
		{
			CodeDocument &doc		= codeEditor->getCodeDocument();

			Array<Range<int> > results = searchForMatchesInDocument (doc);

			for (int j=0; j<results.size(); j++)
			{
				reportFoundMatch (doc, names[i], results[j]);
			}
		}
	}

	owner.getMethodEditArea()->getLowerTabs()->setCurrentTabIndex(0,true);
}

void CtrlrLuaMethodFind::findInAll()
{
	owner.getMethodEditArea()->insertOutput("\n\nSearching for: \""+findInput->getText()+"\" in all methods (double click line to jump)\n", Colours::darkblue);
	StringArray names;

	for (int i=0; i<owner.getMethodManager().getNumMethods(); i++)
	{
		CtrlrLuaMethod *m = owner.getMethodManager().getMethodByIndex (i);

		if (m)
		{
			names.add (m->getName());

			if (m->getCodeEditor())
			{
				/* it has an editor so it's open */
				CodeDocument &doc		= m->getCodeEditor()->getCodeDocument();

				Array<Range<int> > results = searchForMatchesInDocument (doc);

				for (int j=0; j<results.size(); j++)
				{
					reportFoundMatch (doc, names[i], results[j]);
				}
			}
		}
	}

	owner.getMethodEditArea()->getLowerTabs()->setCurrentTabIndex(0,true);
}

const Array<Range<int> > CtrlrLuaMethodFind::searchForMatchesInDocument(CodeDocument &doc)
{
	Array<Range<int> > results;
	const String search		= findInput->getText();
	int position			= -1;
	lastFoundPosition		= -1;

	do
	{
		if (!matchCase->getToggleState())
		{
			position = doc.getAllContent().indexOfIgnoreCase (lastFoundPosition+1, search);
		}
		else
		{
			position = doc.getAllContent().indexOf (lastFoundPosition+1, search);
		}

		if (position >= 0)
		{
			lastFoundPosition		= position;
			results.add (Range<int> (lastFoundPosition, lastFoundPosition+search.length()));
		}
		else
		{
			lastFoundPosition = -1;
		}
	}
	while (lastFoundPosition >= 0);

	return (results);
}

void CtrlrLuaMethodFind::reportFoundMatch (CodeDocument &document, const String &methodName, const Range<int> range)
{
	CodeDocument::Position pos (document, range.getStart());
	AttributedString as;
	as.append ("Method: ", Colours::black);
	as.append (methodName, Colours::blue);

	as.append ("\tline: ", Colours::black);
	as.append (String(pos.getLineNumber()+1), Colours::darkgreen);

	as.append ("\tstart: ", Colours::black);
	as.append (String(range.getStart()), Colours::darkgreen);

	as.append ("\tend: ", Colours::black);
	as.append (String(range.getEnd()), Colours::darkgreen);

	owner.getMethodEditArea()->insertOutput (as);
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="CtrlrLuaMethodFind" componentName="Search and Replace"
                 parentClasses="public Component, public TextEditor::Listener"
                 constructorParams="CtrlrLuaMethodEditor &amp;_owner" variableInitialisers="owner(_owner)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="424" initialHeight="64">
  <METHODS>
    <METHOD name="keyPressed (const KeyPress&amp; key)"/>
    <METHOD name="visibilityChanged()"/>
  </METHODS>
  <BACKGROUND backgroundColour="0"/>
  <TEXTEDITOR name="" id="6f936e948893af75" memberName="findInput" virtualName=""
              explicitFocusOrder="0" pos="4 4 33.019% 32" bkgcol="ffffffff"
              outlinecol="0" shadowcol="0" initialText="" multiline="1" retKeyStartsLine="0"
              readonly="0" scrollbars="1" caret="1" popupmenu="1"/>
  <TEXTEDITOR name="" id="744e2163900608e0" memberName="replaceInput" virtualName=""
              explicitFocusOrder="0" pos="45.047% 4 33.019% 32" bkgcol="ffffffff"
              outlinecol="0" shadowcol="0" initialText="" multiline="1" retKeyStartsLine="0"
              readonly="0" scrollbars="1" caret="1" popupmenu="1"/>
  <TEXTBUTTON name="" id="fa9e37fe9ed18cb8" memberName="findNext" virtualName=""
              explicitFocusOrder="0" pos="0R 4 9.906% 32" posRelativeX="6f936e948893af75"
              bgColOff="ffbababa" buttonText="Find" connectedEdges="3" needsCallback="1"
              radioGroupId="0"/>
  <TEXTBUTTON name="" id="c0ea170c8f7a9eba" memberName="replaceNextButton"
              virtualName="" explicitFocusOrder="0" pos="0R 4 9.906% 32" posRelativeX="744e2163900608e0"
              bgColOff="ffcbf2aa" buttonText="Next" connectedEdges="3" needsCallback="1"
              radioGroupId="0"/>
  <TEXTBUTTON name="" id="3d16946d31b26786" memberName="replaceAllButton" virtualName=""
              explicitFocusOrder="0" pos="0R 4 9.906% 32" posRelativeX="c0ea170c8f7a9eba"
              bgColOff="ffa9cfff" buttonText="All" connectedEdges="3" needsCallback="1"
              radioGroupId="0"/>
  <LABEL name="new label" id="3e2e6635ee9aae4e" memberName="label" virtualName=""
         explicitFocusOrder="0" pos="0 40 64 24" posRelativeX="6f936e948893af75"
         edTextCol="ff000000" edBkgCol="0" labelText="Find" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="16" bold="1" italic="1" justification="33"/>
  <TOGGLEBUTTON name="" id="ec465ae4cc0e8e7a" memberName="matchCase" virtualName=""
                explicitFocusOrder="0" pos="68 40 96 24" posRelativeX="6f936e948893af75"
                buttonText="Match Case" connectedEdges="0" needsCallback="1"
                radioGroupId="0" state="0"/>
  <LABEL name="new label" id="846ac0d0c5ae311c" memberName="label2" virtualName=""
         explicitFocusOrder="0" pos="121 40 64 24" posRelativeX="744e2163900608e0"
         edTextCol="ff000000" edBkgCol="0" labelText="Replace" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="16" bold="1" italic="1" justification="33"/>
  <COMBOBOX name="" id="d5a9d17b100be8b2" memberName="whereToFindCombo" virtualName=""
            explicitFocusOrder="0" pos="176 40 128 24" editable="0" layout="33"
            items="Current&#10;All Open&#10;All" textWhenNonSelected="Current"
            textWhenNoItems=""/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
