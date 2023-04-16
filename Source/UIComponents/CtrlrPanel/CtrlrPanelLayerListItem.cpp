#include "stdafx.h"
#include "CtrlrPanelLayerListItem.h"
#include "CtrlrPropertyEditors/CtrlrPropertyComponent.h"
#include "CtrlrPanelCanvasLayer.h"
#include "CtrlrPanelLayerList.h"
#include "CtrlrInlineUtilitiesGUI.h"

CtrlrPanelLayerListItem::CtrlrPanelLayerListItem (CtrlrPanelLayerList &_owner)
    : layer(0), owner(_owner),
      layerName (0),
      layerVisibility (0),
      layerColour (0),
      layerIndex (0)
{
    addAndMakeVisible (layerName = new Label ("",
                                              L"Layer Name"));
    layerName->setFont (Font (12.0000f, Font::plain));
    layerName->setJustificationType (Justification::centredLeft);
    layerName->setEditable (true, true, false);
    layerName->setColour (TextEditor::textColourId, Colours::black);
    layerName->setColour (TextEditor::backgroundColourId, Colour (0x0));
    layerName->addListener (this);

    addAndMakeVisible (layerVisibility = new ToggleButton(""));
    layerVisibility->addListener (this);

    addAndMakeVisible (layerColour = new CtrlrColourEditorComponent (this));
    addAndMakeVisible (layerIndex = new Label (L"layerIndex",
                                               L"2"));
    layerIndex->setFont (Font (12.0000f, Font::plain));
    layerIndex->setJustificationType (Justification::centred);
    layerIndex->setEditable (false, false, false);
    layerIndex->setColour (TextEditor::textColourId, Colours::black);
    layerIndex->setColour (TextEditor::backgroundColourId, Colour (0x0));


    //[UserPreSize]
	layerName->addMouseListener (this, true);
	layerVisibility->addMouseListener (this, true);
	layerColour->addMouseListener (this, true);
	layerIndex->addMouseListener (this, true);

	layerVisibility->setMouseCursor (MouseCursor::PointingHandCursor);
    //[/UserPreSize]

    setSize (355, 40);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

CtrlrPanelLayerListItem::~CtrlrPanelLayerListItem()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    deleteAndZero (layerName);
    deleteAndZero (layerVisibility);
    deleteAndZero (layerColour);
    deleteAndZero (layerIndex);


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void CtrlrPanelLayerListItem::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    g.setColour(Colours::black);
    g.drawLine(0, getHeight(), getWidth(), getHeight(), 1.0f);
    //[/UserPrePaint]

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void CtrlrPanelLayerListItem::resized()
{
    layerName->setBounds (48, 4, proportionOfWidth (0.5183f), 12);
    layerVisibility->setBounds (8, 4, 32, 32);
    layerColour->setBounds (48, 16, getWidth() - 144, 16);
    layerIndex->setBounds (getWidth() - 83, getHeight() - 16, 14, 16);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void CtrlrPanelLayerListItem::labelTextChanged (Label* labelThatHasChanged)
{
    //[UserlabelTextChanged_Pre]
    //[/UserlabelTextChanged_Pre]

    if (labelThatHasChanged == layerName)
    {
        //[UserLabelCode_layerName] -- add your label text handling code here..
		if (layer)
		{
			layer->setProperty (Ids::uiPanelCanvasLayerName, layerName->getText());
		}
        //[/UserLabelCode_layerName]
    }

    //[UserlabelTextChanged_Post]
    //[/UserlabelTextChanged_Post]
}

void CtrlrPanelLayerListItem::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == layerVisibility)
    {
        //[UserButtonCode_layerVisibility] -- add your button handler code here..
		if (layer)
		{
			layer->setProperty (Ids::uiPanelCanvasLayerVisibility, layerVisibility->getToggleState());
		}
        //[/UserButtonCode_layerVisibility]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}

void CtrlrPanelLayerListItem::mouseDown (const MouseEvent& e)
{
    //[UserCode_mouseDown] -- Add your code here...
	if (layer)
	{
		owner.setSelectedRow (rowIndex);
	}
    //[/UserCode_mouseDown]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void CtrlrPanelLayerListItem::setLayer (CtrlrPanelCanvasLayer *_layer)
{
	if (_layer == nullptr)
		return;

	layer = _layer;

	layerName->setText (layer->getProperty(Ids::uiPanelCanvasLayerName), dontSendNotification);
	layerVisibility->setToggleState (layer->getProperty(Ids::uiPanelCanvasLayerVisibility), sendNotification);
	layerColour->setColour (VAR2COLOUR(layer->getProperty(Ids::uiPanelCanvasLayerColour)), false);
	layerIndex->setText (layer->getProperty(Ids::uiPanelCanvasLayerIndex).toString(), dontSendNotification);
}

void CtrlrPanelLayerListItem::changeListenerCallback (ChangeBroadcaster* source)
{
	if (layer)
	{
		layer->setProperty (Ids::uiPanelCanvasLayerColour, layerColour->getColour().toString());
        layerColour->updateLabel();
	}
}

void CtrlrPanelLayerListItem::setRow(const int _rowIndex)
{
	rowIndex = _rowIndex;
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Jucer information section --

    This is where the Jucer puts all of its metadata, so don't change anything in here!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="CtrlrPanelLayerListItem"
                 componentName="" parentClasses="public Component, public ChangeListener"
                 constructorParams="CtrlrPanelLayerList &amp;_owner" variableInitialisers="layer(0), owner(_owner)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330000013"
                 fixedSize="1" initialWidth="355" initialHeight="40">
  <METHODS>
    <METHOD name="mouseDown (const MouseEvent&amp; e)"/>
  </METHODS>
  <BACKGROUND backgroundColour="ffffff"/>
  <LABEL name="" id="a96af5bb0d837023" memberName="layerName" virtualName=""
         explicitFocusOrder="0" pos="48 4 51.831% 12" edTextCol="ff000000"
         edBkgCol="0" labelText="Layer Name" editableSingleClick="1" editableDoubleClick="1"
         focusDiscardsChanges="0" fontname="Default font" fontsize="12"
         bold="0" italic="0" justification="33"/>
  <IMAGEBUTTON name="" id="2965d7960a5cfd60" memberName="layerVisibility" virtualName=""
               explicitFocusOrder="0" pos="8 4 32 32" tooltip="Layer visibility"
               buttonText="" connectedEdges="0" needsCallback="1" radioGroupId="0"
               keepProportions="1" resourceNormal="" opacityNormal="1" colourNormal="0"
               resourceOver="" opacityOver="0.5" colourOver="0" resourceDown=""
               opacityDown="1" colourDown="0"/>
  <GENERICCOMPONENT name="" id="b66f09cccadeeec4" memberName="layerColour" virtualName=""
                    explicitFocusOrder="0" pos="48 16 144M 16" class="CtrlrColourEditorComponent"
                    params="this"/>
  <LABEL name="layerIndex" id="5dd9a815809be664" memberName="layerIndex"
         virtualName="" explicitFocusOrder="0" pos="83R 8R 14 8" edTextCol="ff000000"
         edBkgCol="0" labelText="2" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="8"
         bold="0" italic="0" justification="36"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif
