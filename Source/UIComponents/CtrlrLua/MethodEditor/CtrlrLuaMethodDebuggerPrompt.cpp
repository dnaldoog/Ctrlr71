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
//[/Headers]

#include "CtrlrLuaMethodDebuggerPrompt.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
#include "CtrlrLuaMethodEditor.h"
//[/MiscUserDefs]

//==============================================================================
CtrlrLuaMethodDebuggerPrompt::CtrlrLuaMethodDebuggerPrompt (CtrlrLuaMethodEditor &_owner)
    : owner(_owner)
{
    addAndMakeVisible (debuggerOutput = new TextEditor ("Debugger output"));
    debuggerOutput->setMultiLine (true);
    debuggerOutput->setReturnKeyStartsNewLine (false);
    debuggerOutput->setReadOnly (true);
    debuggerOutput->setScrollbarsShown (true);
    debuggerOutput->setCaretVisible (false);
    debuggerOutput->setPopupMenuEnabled (true);
    debuggerOutput->setColour (TextEditor::textColourId, Colour (0xff5c5c5c));
    debuggerOutput->setColour (TextEditor::outlineColourId, Colour (0x00000000));
    debuggerOutput->setColour (TextEditor::shadowColourId, Colour (0x00000000));
    debuggerOutput->setText ("");

    addAndMakeVisible (debuggerInput = new TextEditor ("Debugger input"));
    debuggerInput->setMultiLine (false);
    debuggerInput->setReturnKeyStartsNewLine (false);
    debuggerInput->setReadOnly (false);
    debuggerInput->setScrollbarsShown (false);
    debuggerInput->setCaretVisible (true);
    debuggerInput->setPopupMenuEnabled (true);
    debuggerInput->setColour (TextEditor::highlightColourId, Colour (0x5b247c8d));
    debuggerInput->setColour (TextEditor::outlineColourId, Colour (0x8a000000));
    debuggerInput->setColour (TextEditor::shadowColourId, Colour (0x00000000));
    debuggerInput->setText ("");

    addAndMakeVisible (debugContinue = new ImageButton ("Continue"));
    debugContinue->setTooltip (TRANS("Continue"));
    debugContinue->addListener (this);

    debugContinue->setImages (false, true, true,
                              Image(), 0.550f, Colour (0x00000000),
                              Image(), 0.850f, Colour (0x00000000),
                              Image(), 1.000f, Colour (0x00000000));
    addAndMakeVisible (debugStepOver = new ImageButton ("Step Over"));
    debugStepOver->setTooltip (TRANS("Step Over"));
    debugStepOver->addListener (this);

    debugStepOver->setImages (false, true, true,
                              Image(), 0.550f, Colour (0x00000000),
                              Image(), 0.850f, Colour (0x00000000),
                              Image(), 1.000f, Colour (0x00000000));
    addAndMakeVisible (debugStepInto = new ImageButton ("Step Into"));
    debugStepInto->setTooltip (TRANS("Step Into"));
    debugStepInto->addListener (this);

    debugStepInto->setImages (false, true, true,
                              Image(), 0.550f, Colour (0x00000000),
                              Image(), 0.850f, Colour (0x00000000),
                              Image(), 1.000f, Colour (0x00000000));
    addAndMakeVisible (debuggerInfo = new ConcertinaPanel());
    debuggerInfo->setExplicitFocusOrder (50);
    debuggerInfo->setName ("Realtime information");

    addAndMakeVisible (debugStepOut = new ImageButton ("Step Out"));
    debugStepOut->setTooltip (TRANS("Step Out"));
    debugStepOut->addListener (this);

    debugStepOut->setImages (false, true, true,
                             Image(), 0.550f, Colour (0x00000000),
                             Image(), 0.850f, Colour (0x00000000),
                             Image(), 1.000f, Colour (0x00000000));
    addAndMakeVisible (debugRestart = new ImageButton ("Restart"));
    debugRestart->setTooltip (TRANS("Restart"));
    debugRestart->addListener (this);

    debugRestart->setImages (false, true, true,
                             Image(), 0.550f, Colour (0x00000000),
                             Image(), 0.850f, Colour (0x00000000),
                             Image(), 1.000f, Colour (0x00000000));
    addAndMakeVisible (debugStop = new ImageButton ("Stop"));
    debugStop->setTooltip (TRANS("Stop"));
    debugStop->addListener (this);

    debugStop->setImages (false, true, true,
                          Image(), 0.550f, Colour (0x00000000),
                          Image(), 0.850f, Colour (0x00000000),
                          Image(), 1.000f, Colour (0x00000000));

    addAndMakeVisible (clearOutput = new ImageButton ("Clear"));
    clearOutput->setTooltip (TRANS("Clear"));
    clearOutput->addListener (this);

    clearOutput->setImages (false, true, true,
        Image(), 0.550f, Colour (0x00000000),
        Image(), 0.850f, Colour (0x00000000),
        Image(), 1.000f, Colour (0x00000000));

    //[UserPreSize]
    collectionState = Ended;

    addAndMakeVisible (resizer	= new StretchableLayoutResizerBar (&layoutManager, 1, true));

    layoutManager.setItemLayout (0, -0.001, -1.0, -0.59);
    layoutManager.setItemLayout (1, 8, 8, 8);
    layoutManager.setItemLayout (2, -0.001, -1.0, -0.39);

    debuggerInfo->addPanel (0, stackTracePanel = new CtrlrLuaMethodDebuggerStackTrace(owner), true);
    debuggerInfo->addPanel (1, varsPanel = new CtrlrLuaMethodDebuggerVars(owner), true);

    debuggerOutput->setFont (Font (Font::getDefaultMonospacedFontName(), 14.0f, Font::plain));
    debuggerInput->setFont (Font (Font::getDefaultMonospacedFontName(), 14.0f, Font::plain));
    debuggerInput->addListener (this);

    debugContinue->setImages (false, true, true,
                              ImageCache::getFromMemory(BinaryData::play_svg, BinaryData::play_svgSize), 0.550f, Colour (0x00000000),
                              ImageCache::getFromMemory(BinaryData::play_svg, BinaryData::play_svgSize), 0.850f, Colour (0x00000000),
                              ImageCache::getFromMemory(BinaryData::play_svg, BinaryData::play_svgSize), 1.000f, Colour (0x00000000));
    debugContinue->setMouseCursor (MouseCursor::PointingHandCursor);

    debugStepInto->setImages (false, true, true,
                              ImageCache::getFromMemory(BinaryData::appbar_debug_step_into_png, BinaryData::appbar_debug_step_into_pngSize), 0.550f, Colour (0x00000000),
                              ImageCache::getFromMemory(BinaryData::appbar_debug_step_into_png, BinaryData::appbar_debug_step_into_pngSize), 0.850f, Colour (0x00000000),
                              ImageCache::getFromMemory(BinaryData::appbar_debug_step_into_png, BinaryData::appbar_debug_step_into_pngSize), 1.000f, Colour (0x00000000));
    debugStepInto->setMouseCursor (MouseCursor::PointingHandCursor);

    debugStepOver->setImages (false, true, true,
                              ImageCache::getFromMemory(BinaryData::appbar_debug_step_over_png, BinaryData::appbar_debug_step_over_pngSize), 0.550f, Colour (0x00000000),
                              ImageCache::getFromMemory(BinaryData::appbar_debug_step_over_png, BinaryData::appbar_debug_step_over_pngSize), 0.850f, Colour (0x00000000),
                              ImageCache::getFromMemory(BinaryData::appbar_debug_step_over_png, BinaryData::appbar_debug_step_over_pngSize), 1.000f, Colour (0x00000000));
    debugStepOver->setMouseCursor (MouseCursor::PointingHandCursor);

    debugRestart->setImages (false, true, true,
                              ImageCache::getFromMemory(BinaryData::appbar_debug_restart_png, BinaryData::appbar_debug_restart_pngSize), 0.550f, Colour (0x00000000),
                              ImageCache::getFromMemory(BinaryData::appbar_debug_restart_png, BinaryData::appbar_debug_restart_pngSize), 0.850f, Colour (0x00000000),
                              ImageCache::getFromMemory(BinaryData::appbar_debug_restart_png, BinaryData::appbar_debug_restart_pngSize), 1.000f, Colour (0x00000000));
    debugRestart->setMouseCursor (MouseCursor::PointingHandCursor);

    debugStepOut->setImages (false, true, true,
                              ImageCache::getFromMemory(BinaryData::appbar_debug_step_out_png, BinaryData::appbar_debug_step_out_pngSize), 0.550f, Colour (0x00000000),
                              ImageCache::getFromMemory(BinaryData::appbar_debug_step_out_png, BinaryData::appbar_debug_step_out_pngSize), 0.850f, Colour (0x00000000),
                              ImageCache::getFromMemory(BinaryData::appbar_debug_step_out_png, BinaryData::appbar_debug_step_out_pngSize), 1.000f, Colour (0x00000000));
    debugStepOut->setMouseCursor (MouseCursor::PointingHandCursor);

    debugStop->setImages (false, true, true,
								ImageCache::getFromMemory(BinaryData::stop_svg, BinaryData::stop_svgSize), 0.550f, Colour (0x00000000),
								ImageCache::getFromMemory(BinaryData::stop_svg, BinaryData::stop_svgSize), 0.850f, Colour (0x00000000),
								ImageCache::getFromMemory(BinaryData::stop_svg, BinaryData::stop_svgSize), 1.000f, Colour (0x00000000));
    debugStop->setMouseCursor (MouseCursor::PointingHandCursor);

    clearOutput->setImages (false, true, true,
								ImageCache::getFromMemory(BinaryData::cleanup_svg, BinaryData::cleanup_svgSize), 0.550f, Colour (0x00000000),
								ImageCache::getFromMemory(BinaryData::cleanup_svg, BinaryData::cleanup_svgSize), 0.850f, Colour (0x00000000),
								ImageCache::getFromMemory(BinaryData::cleanup_svg, BinaryData::cleanup_svgSize), 1.000f, Colour (0x00000000));
    clearOutput->setMouseCursor (MouseCursor::PointingHandCursor);

    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

CtrlrLuaMethodDebuggerPrompt::~CtrlrLuaMethodDebuggerPrompt()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    debuggerOutput = nullptr;
    debuggerInput = nullptr;
    debugContinue = nullptr;
    debugStepOver = nullptr;
    debugStepInto = nullptr;
    debuggerInfo = nullptr;
    debugStepOut = nullptr;
    debugRestart = nullptr;
    debugStop = nullptr;
	clearOutput = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void CtrlrLuaMethodDebuggerPrompt::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void CtrlrLuaMethodDebuggerPrompt::resized()
{
    debuggerOutput->setBounds (0, 32, proportionOfWidth (0.7000f), getHeight() - 50);
    debuggerInput->setBounds (0, getHeight() - 18, getWidth() - 0, 18);
    debugContinue->setBounds (0, 0, 32, 32);
    debugStepOver->setBounds (40, 0, 32, 32);
    debugStepInto->setBounds (80, 0, 32, 32);
    debuggerInfo->setBounds (proportionOfWidth (0.7000f), 32, proportionOfWidth (0.3000f), getHeight() - 50);
    debugStepOut->setBounds (120, 0, 32, 32);
    debugRestart->setBounds (160, 0, 32, 32);
    debugStop->setBounds (200, 0, 32, 32);
	clearOutput->setBounds (240, 0, 32, 32);
    //[UserResized] Add your own custom resize handling here..
    Component* comps[] = { debuggerOutput, resizer, debuggerInfo  };
	layoutManager.layOutComponents (comps, 3, 0, 32, getWidth(), getHeight() - 50, false, true);
    //[/UserResized]
}

void CtrlrLuaMethodDebuggerPrompt::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == debugContinue)
    {
        //[UserButtonCode_debugContinue] -- add your button handler code here..
        sendCommand ("run");
        //[/UserButtonCode_debugContinue]
    }
    else if (buttonThatWasClicked == debugStepOver)
    {
        //[UserButtonCode_debugStepOver] -- add your button handler code here..
        sendCommand ("over");
        //[/UserButtonCode_debugStepOver]
    }
    else if (buttonThatWasClicked == debugStepInto)
    {
        //[UserButtonCode_debugStepInto] -- add your button handler code here..
        sendCommand ("step");
        //[/UserButtonCode_debugStepInto]
    }
    else if (buttonThatWasClicked == debugStepOut)
    {
        //[UserButtonCode_debugStepOut] -- add your button handler code here..
        sendCommand ("out");
        //[/UserButtonCode_debugStepOut]
    }
    else if (buttonThatWasClicked == debugRestart)
    {
        //[UserButtonCode_debugRestart] -- add your button handler code here..
        sendCommand ("exit");
        //[/UserButtonCode_debugRestart]
    }
    else if (buttonThatWasClicked == debugStop)
    {
        //[UserButtonCode_debugStop] -- add your button handler code here..
        //[/UserButtonCode_debugStop]
    }
	else if (buttonThatWasClicked == clearOutput)
	{
		//[UserButtonCode_clearOutput] -- add your button handler code here..
		debuggerOutput->setText("");
		//[/UserButtonCode_clearOutput]
	}

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void CtrlrLuaMethodDebuggerPrompt::insertRawDebuggerOutput(const String &output)
{
    insertToOutput (output);

    if (output.contains("Paused at file"))
    {
        /* Debugger tells us we paused at some location in the code
            get the method name, and highlight the relevant code in
            the editor
        */
        const String file = output.fromFirstOccurrenceOf("Paused at file ", false, true).upToFirstOccurrenceOf(" ", false, true);
        const int line = output.fromFirstOccurrenceOf(" line ", false, true).getIntValue();

        owner.highlightCode (file, line);
    }

    if (output.contains ("::start trace"))
    {
        collectedData = "";
        collectionState = Trace;
        return;
    }

    if (output.contains ("::start dumpvar"))
    {
        collectedData = "";
        collectionState = Values;
        return;
    }

    if (output.contains("::end"))
    {
        finishDataCollection();
    }

    if (collectionState != Ended)
        collectedData << output;
}

void CtrlrLuaMethodDebuggerPrompt::finishDataCollection()
{
    switch (collectionState)
    {
        case Trace:
            stackTracePanel->setData(collectedData);
            break;
        case Values:
            varsPanel->setData(collectedData);
            break;
        default:
            break;
    }

    collectionState = Ended;
}

void CtrlrLuaMethodDebuggerPrompt::sendCommand (const String &command)
{
    if (owner.getParentComponent()->isCurrentlyModal())
    {
        commandQueue.add (command);

        insertToOutput (command.trim() + "\n", Colours::black);

        if (owner.getParentComponent()->isCurrentlyModal())
        {
            owner.getParentComponent()->exitModalState(1);
        }
    }
    else
    {
        _WRN("CtrlrLuaMethodDebuggerPrompt::sendCommand debugger is not active");
    }
}

void CtrlrLuaMethodDebuggerPrompt::textEditorReturnKeyPressed (TextEditor &editor)
{
    if (&editor == debuggerInput)
    {
        sendCommand (debuggerInput->getText());
        debuggerInput->clear();
    }
}

StringArray &CtrlrLuaMethodDebuggerPrompt::getCommandQueue()
{
    return (commandQueue);
}

const String CtrlrLuaMethodDebuggerPrompt::getCurrentDebuggerCommand(const bool clearTheReturnedCommand)
{
    if (commandQueue.size() <= 0)
        return ("");

    const String ret = commandQueue[commandQueue.size() - 1];
    commandQueue.remove (commandQueue.size() - 1);
    return (ret);
}

void CtrlrLuaMethodDebuggerPrompt::visibilityChanged()
{
    if (isVisible())
    {
        debuggerInput->grabKeyboardFocus ();
    }
}

void CtrlrLuaMethodDebuggerPrompt::insertToOutput(const String &what, Colour textColour)
{
    const Colour lastColourUsed = debuggerOutput->findColour(TextEditor::textColourId);

    debuggerOutput->setColour (TextEditor::textColourId, textColour);
    debuggerOutput->setCaretPosition (debuggerOutput->getText().length());
    debuggerOutput->insertTextAtCaret (what);
    debuggerOutput->setColour (TextEditor::textColourId, lastColourUsed);
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="CtrlrLuaMethodDebuggerPrompt"
                 componentName="" parentClasses="public Component, public TextEditor::Listener"
                 constructorParams="CtrlrLuaMethodEditor &amp;_owner" variableInitialisers="owner(_owner)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="600" initialHeight="400">
  <BACKGROUND backgroundColour="ffffff"/>
  <TEXTEDITOR name="Debugger output" id="2220af475a8f6614" memberName="debuggerOutput"
              virtualName="" explicitFocusOrder="0" pos="0 32 70% 50M" textcol="ff5c5c5c"
              outlinecol="0" shadowcol="0" initialText="" multiline="1" retKeyStartsLine="0"
              readonly="1" scrollbars="1" caret="0" popupmenu="1"/>
  <TEXTEDITOR name="Debugger input" id="b2b8220d7f2d2565" memberName="debuggerInput"
              virtualName="" explicitFocusOrder="0" pos="0 18R 0M 18" hilitecol="5b247c8d"
              outlinecol="8a000000" shadowcol="0" initialText="" multiline="0"
              retKeyStartsLine="0" readonly="0" scrollbars="0" caret="1" popupmenu="1"/>
  <IMAGEBUTTON name="Continue" id="2ccb9131528ecffc" memberName="debugContinue"
               virtualName="" explicitFocusOrder="0" pos="0 0 32 32" tooltip="Continue"
               buttonText="Continue" connectedEdges="0" needsCallback="1" radioGroupId="0"
               keepProportions="1" resourceNormal="" opacityNormal="0.55000001192092895508"
               colourNormal="0" resourceOver="" opacityOver="0.85000002384185791016"
               colourOver="0" resourceDown="" opacityDown="1" colourDown="0"/>
  <IMAGEBUTTON name="Step Over" id="2f8e190ee1a2d9c6" memberName="debugStepOver"
               virtualName="" explicitFocusOrder="0" pos="40 0 32 32" tooltip="Step Over"
               buttonText="Step Over" connectedEdges="0" needsCallback="1" radioGroupId="0"
               keepProportions="1" resourceNormal="" opacityNormal="0.55000001192092895508"
               colourNormal="0" resourceOver="" opacityOver="0.85000002384185791016"
               colourOver="0" resourceDown="" opacityDown="1" colourDown="0"/>
  <IMAGEBUTTON name="Step Into" id="216fcc9599371746" memberName="debugStepInto"
               virtualName="" explicitFocusOrder="0" pos="80 0 32 32" tooltip="Step Into"
               buttonText="Step Into" connectedEdges="0" needsCallback="1" radioGroupId="0"
               keepProportions="1" resourceNormal="" opacityNormal="0.55000001192092895508"
               colourNormal="0" resourceOver="" opacityOver="0.85000002384185791016"
               colourOver="0" resourceDown="" opacityDown="1" colourDown="0"/>
  <GENERICCOMPONENT name="Realtime information" id="f9beea3d026db326" memberName="debuggerInfo"
                    virtualName="" explicitFocusOrder="50" pos="70% 32 30% 50M" class="ConcertinaPanel"
                    params=""/>
  <IMAGEBUTTON name="Step Out" id="b5b0a5654ecfc920" memberName="debugStepOut"
               virtualName="" explicitFocusOrder="0" pos="120 0 32 32" tooltip="Step Out"
               buttonText="Step Out" connectedEdges="0" needsCallback="1" radioGroupId="0"
               keepProportions="1" resourceNormal="" opacityNormal="0.55000001192092895508"
               colourNormal="0" resourceOver="" opacityOver="0.85000002384185791016"
               colourOver="0" resourceDown="" opacityDown="1" colourDown="0"/>
  <IMAGEBUTTON name="Restart" id="d692f318070f2b5a" memberName="debugRestart"
               virtualName="" explicitFocusOrder="0" pos="160 0 32 32" tooltip="Restart"
               buttonText="Restart" connectedEdges="0" needsCallback="1" radioGroupId="0"
               keepProportions="1" resourceNormal="" opacityNormal="0.55000001192092895508"
               colourNormal="0" resourceOver="" opacityOver="0.85000002384185791016"
               colourOver="0" resourceDown="" opacityDown="1" colourDown="0"/>
  <IMAGEBUTTON name="Stop" id="337404b10168d0f4" memberName="debugStop" virtualName=""
               explicitFocusOrder="0" pos="200 0 32 32" tooltip="Stop" buttonText="Stop"
               connectedEdges="0" needsCallback="1" radioGroupId="0" keepProportions="1"
               resourceNormal="" opacityNormal="0.55000001192092895508" colourNormal="0"
               resourceOver="" opacityOver="0.85000002384185791016" colourOver="0"
               resourceDown="" opacityDown="1" colourDown="0"/>
  <IMAGEBUTTON name="Clear" id="337404b1016253f4" memberName="clearOutput" virtualName=""
               explicitFocusOrder="0" pos="240 0 32 32" tooltip="Clear debug output" buttonText="Clear"
               connectedEdges="0" needsCallback="1" radioGroupId="0" keepProportions="1"
               resourceNormal="" opacityNormal="0.55000001192092895508" colourNormal="0"
               resourceOver="" opacityOver="0.85000002384185791016" colourOver="0"
               resourceDown="" opacityDown="1" colourDown="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
