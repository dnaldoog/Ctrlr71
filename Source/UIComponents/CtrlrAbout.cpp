#include "stdafx.h"
#include "stdafx_luabind.h"
#include "CtrlrAbout.h"
#include "CtrlrRevision.h"
#include "CtrlrPanel/CtrlrPanel.h"
#include "CtrlrInlineUtilitiesGUI.h"

CtrlrAbout::CtrlrAbout (CtrlrManager &_owner)
    : owner(_owner)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    String authorEmail;
    if(owner.getActivePanel()) authorEmail = owner.getActivePanel()->getProperty(Ids::panelAuthorEmail);
        else authorEmail = "";
    String authorDonateUrl;
    if(owner.getActivePanel()) authorDonateUrl =   owner.getActivePanel()->getProperty(Ids::panelAuthorDonateUrl);
        else authorDonateUrl = "";

    addAndMakeVisible (ctrlrName = new Label ("",
                                              TRANS("Ctrlr")));
    ctrlrName->setFont (Font (48.00f, Font::bold));
    ctrlrName->setJustificationType (Justification::centredLeft);
    ctrlrName->setEditable (false, false, false);
    ctrlrName->setColour (Label::textColourId, Colour (0xd6000000));
    ctrlrName->setColour (TextEditor::textColourId, Colours::black);
    ctrlrName->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (ctrlrLogo = gui::createDrawableButton("Ctrlr", BIN2STR(ctrlr_logo_svg)));
    ctrlrLogo->addListener (this);

    addAndMakeVisible (versionInfoLabel = new TextEditor (""));
    versionInfoLabel->setMultiLine (true);
    versionInfoLabel->setReturnKeyStartsNewLine (true);
    versionInfoLabel->setReadOnly (true);
    versionInfoLabel->setScrollbarsShown (true);
    versionInfoLabel->setCaretVisible (false);
    versionInfoLabel->setPopupMenuEnabled (true);
    versionInfoLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));
    versionInfoLabel->setColour (TextEditor::outlineColourId, Colour (0x9c000000));
    versionInfoLabel->setColour (TextEditor::shadowColourId, Colour (0x00000000));
    versionInfoLabel->setText ("");

    addAndMakeVisible (label = new Label ("new label",
                                          TRANS("Instance name")));
    label->setFont (Font (24.00f, Font::bold));
    label->setJustificationType (Justification::topRight);
    label->setEditable (false, false, false);
    label->setColour (TextEditor::textColourId, Colours::black);
    label->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

	if (!authorDonateUrl.isEmpty())
	{
		addAndMakeVisible(labelDonate = new Label("new label", TRANS("Donate")));
		labelDonate->setFont(Font(24.00f, Font::plain));
		labelDonate->setJustificationType(Justification::topRight);
		labelDonate->setEditable(false, false, false);
		labelDonate->setColour(TextEditor::textColourId, Colours::black);
		labelDonate->setColour(TextEditor::backgroundColourId, Colour(0x00000000));
	}

	addAndMakeVisible (label2 = new Label ("new label",
                                           TRANS("Author")));
    label2->setFont (Font (24.00f, Font::plain));
    label2->setJustificationType (Justification::topRight);
    label2->setEditable (false, false, false);
    label2->setColour (TextEditor::textColourId, Colours::black);
    label2->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

	if (!authorEmail.isEmpty())
	{
		addAndMakeVisible(labelAuthorEmail = new Label("new label", TRANS("Contact")));
		labelAuthorEmail->setFont(Font(24.00f, Font::plain));
		labelAuthorEmail->setJustificationType(Justification::topRight);
		labelAuthorEmail->setEditable(false, false, false);
		labelAuthorEmail->setColour(TextEditor::textColourId, Colours::black);
		labelAuthorEmail->setColour(TextEditor::backgroundColourId, Colour(0x00000000));
	}

	addAndMakeVisible (label3 = new Label ("new label",
                                           TRANS("Version")));
    label3->setFont (Font (24.00f, Font::plain));
    label3->setJustificationType (Justification::topRight);
    label3->setEditable (false, false, false);
    label3->setColour (TextEditor::textColourId, Colours::black);
    label3->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label4 = new Label ("new label",
                                           TRANS("URL")));
    label4->setFont (Font (24.00f, Font::plain));
    label4->setJustificationType (Justification::topRight);
    label4->setEditable (false, false, false);
    label4->setColour (TextEditor::textColourId, Colours::black);
    label4->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (instanceUrl = new HyperlinkButton ("",
                                                          URL ("http://www.rawmaterialsoftware.com/juce")));
    instanceUrl->setTooltip (TRANS("http://www.rawmaterialsoftware.com/juce"));
	instanceUrl->setJustificationType(Justification::topLeft);

	if (!authorEmail.isEmpty())
	{
		addAndMakeVisible(instanceAuthorEmail = new HyperlinkButton(authorEmail,URL("mailto:" + authorEmail)));
		instanceAuthorEmail->setJustificationType(Justification::topLeft);
	}

	if (!authorDonateUrl.isEmpty())
	{
		addAndMakeVisible(instanceAuthorDonateUrl = new HyperlinkButton(authorDonateUrl, URL(authorDonateUrl)));
		instanceAuthorDonateUrl->setJustificationType(Justification::topLeft);
	}

	addAndMakeVisible (instanceVersion = new Label ("",
                                                    ""));
    instanceVersion->setFont (Font (22.00f, Font::bold));
    instanceVersion->setJustificationType (Justification::topLeft);
    instanceVersion->setEditable (false, false, false);
    instanceVersion->setColour (TextEditor::textColourId, Colours::black);
    instanceVersion->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (instanceAuthor = new Label ("",
                                                   ""));
    instanceAuthor->setFont (Font (22.00f, Font::bold));
    instanceAuthor->setJustificationType (Justification::topLeft);
    instanceAuthor->setEditable (false, false, false);
    instanceAuthor->setColour (TextEditor::textColourId, Colours::black);
    instanceAuthor->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (instanceName = new Label ("",
                                                 ""));
    instanceName->setFont (Font (24.00f, Font::bold));
    instanceName->setJustificationType (Justification::topLeft);
    instanceName->setEditable (false, false, false);
    instanceName->setColour (TextEditor::textColourId, Colours::black);
    instanceName->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (instanceDescription = new TextEditor (""));
    instanceDescription->setMultiLine (true);
    instanceDescription->setReturnKeyStartsNewLine (true);
    instanceDescription->setReadOnly (true);
    instanceDescription->setScrollbarsShown (true);
    instanceDescription->setCaretVisible (false);
    instanceDescription->setPopupMenuEnabled (false);
    instanceDescription->setColour (TextEditor::backgroundColourId, Colour (0x00ffffff));
    instanceDescription->setColour (TextEditor::outlineColourId, Colour (0x59000000));
    instanceDescription->setColour (TextEditor::shadowColourId, Colour (0x00000000));
    instanceDescription->setText ("");


    //[UserPreSize]
	ctrlrLogo->setMouseCursor(MouseCursor::PointingHandCursor);
	addVersionInfo ("Version", STR(ctrlrRevision));
	addVersionInfo ("Build date", STR(ctrlrRevisionDate));
#if CTRLR_NIGHTLY == 1
	addVersionInfo ("Branch", "Nightly");
#else
	addVersionInfo ("Branch", "master");
#endif
	addVersionInfo ("Juce", SystemStats::getJUCEVersion().fromLastOccurrenceOf("JUCE v", false, true));

	addVersionInfo ("libusb", "1.0.19");
    addVersionInfo ("liblo", "0.28");
	addVersionInfo ("lua", LUA_RELEASE);
	addVersionInfo ("luabind", _STR(LUABIND_VERSION / 1000) + "." + _STR(LUABIND_VERSION / 100 % 100) + "." + _STR(LUABIND_VERSION % 100));
	addVersionInfo ("boost", _STR(BOOST_VERSION / 100000) + "." + _STR(BOOST_VERSION / 100 % 1000) + "." + _STR(BOOST_VERSION % 100));
	versionInfoLabel->setFont (Font (owner.getFontManager().getDefaultMonoFontName(), 14.0f, Font::plain));

	if (owner.isSingleInstance())
	{
    //[/UserPreSize]

		int height = 380;
		if (!authorEmail.isEmpty())
		{
			height += 40;
		}

		if (!authorDonateUrl.isEmpty())
		{
			height += 40;
		}

		setSize (600, height);


    //[Constructor] You can add your own custom stuff here..
		if (owner.getActivePanel())
		{
			instanceName->setText (owner.getActivePanel()->getProperty(Ids::name).toString(), dontSendNotification);
			instanceAuthor->setText (owner.getActivePanel()->getProperty(Ids::panelAuthorName).toString(), dontSendNotification);
			instanceDescription->setText (owner.getActivePanel()->getProperty(Ids::panelAuthorDesc).toString(), dontSendNotification);
			instanceUrl->setButtonText (owner.getActivePanel()->getProperty(Ids::panelAuthorUrl));
			instanceUrl->setURL(URL(owner.getActivePanel()->getProperty(Ids::panelAuthorUrl)));
			instanceVersion->setText (owner.getActivePanel()->getVersionString(false, false, "."), dontSendNotification);
		}
	}
	else
	{
		setSize (600, 96);
	}
	updateVersionLabel();
    //[/Constructor]
}

CtrlrAbout::~CtrlrAbout()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    ctrlrName = nullptr;
    ctrlrLogo = nullptr;
    versionInfoLabel = nullptr;
    label = nullptr;
	labelAuthorEmail = nullptr;
	labelDonate = nullptr;
    label2 = nullptr;
    label3 = nullptr;
    label4 = nullptr;
    instanceUrl = nullptr;
    instanceVersion = nullptr;
    instanceAuthor = nullptr;
    instanceName = nullptr;
    instanceDescription = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void CtrlrAbout::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.setColour (Colour (0xff4c4c4c));
    g.fillRect (proportionOfWidth (0.0200f), 163, proportionOfWidth (0.9600f), 2);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void CtrlrAbout::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    ctrlrName->setBounds (proportionOfWidth (0.0200f) + proportionOfWidth (0.0800f) - -8, 8, proportionOfWidth (0.2000f), 48);
    ctrlrLogo->setBounds (proportionOfWidth (0.0200f), 8, proportionOfWidth (0.0800f), 48);
    versionInfoLabel->setBounds ((proportionOfWidth (0.0200f) + proportionOfWidth (0.0800f) - -8) + proportionOfWidth (0.2000f) - -8, 8, proportionOfWidth (0.6600f), 76);
	label->setBounds (proportionOfWidth (0.0133f), 120, proportionOfWidth (0.4600f), 24);
	instanceName->setBounds(proportionOfWidth(0.5000f), 120, proportionOfWidth(0.4800f), 24);
	int height = 136;
	if (labelDonate)
	{
		height += 40;
		labelDonate->setBounds(proportionOfWidth(0.0133f), height, proportionOfWidth(0.4600f), 24);
		instanceAuthorDonateUrl->setBounds(proportionOfWidth(0.5000f), height, proportionOfWidth(0.4800f), 24);
	}
	height += 40;
	label2->setBounds (proportionOfWidth (0.0133f), height, proportionOfWidth (0.4600f), 24);
	instanceAuthor->setBounds(proportionOfWidth(0.5000f), height, proportionOfWidth(0.4800f), 24);
	if (labelAuthorEmail)
	{
		height += 40;
		labelAuthorEmail->setBounds(proportionOfWidth(0.0133f), height, proportionOfWidth(0.4600f), 24);
		instanceAuthorEmail->setBounds(proportionOfWidth(0.5000f), height, proportionOfWidth(0.4800f), 24);
	}
	height += 40;
	label3->setBounds (proportionOfWidth (0.0133f), height, proportionOfWidth (0.4600f), 24);
	instanceVersion->setBounds(proportionOfWidth(0.5000f), height, proportionOfWidth(0.4800f), 24);
	height += 40;
	label4->setBounds (proportionOfWidth (0.0133f), height, proportionOfWidth (0.4600f), 24);
    instanceUrl->setBounds (proportionOfWidth (0.5000f), height, proportionOfWidth (0.4800f), 24);
	height += 32;
	instanceDescription->setBounds (proportionOfWidth (0.0200f), height, proportionOfWidth (0.9600f), 80);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void CtrlrAbout::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == ctrlrLogo)
    {
        //[UserButtonCode_ctrlrLogo] -- add your button handler code here..
        //[/UserButtonCode_ctrlrLogo]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void CtrlrAbout::addVersionInfo (const String &name, const String &version)
{
	versionInformationArray.set (name, version);
}

void CtrlrAbout::updateVersionLabel()
{
	for (int i = 0; i < versionInformationArray.size(); i++)
	{
		versionInfoLabel->insertTextAtCaret(versionInformationArray.getAllKeys()[i] + ": ");
		versionInfoLabel->insertTextAtCaret(versionInformationArray.getAllValues()[i] + "\n");
	}
	versionInfoLabel->setText (versionInformationArray.getDescription());
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="CtrlrAbout" componentName=""
                 parentClasses="public Component" constructorParams="CtrlrManager &amp;_owner"
                 variableInitialisers="owner(_owner)" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330" fixedSize="1" initialWidth="600"
                 initialHeight="380">
  <BACKGROUND backgroundColour="ffffff">
    <RECT pos="2% 163 96% 2" fill="solid: ff4c4c4c" hasStroke="0"/>
  </BACKGROUND>
  <LABEL name="" id="cb1b7e33d5cdf245" memberName="ctrlrName" virtualName=""
         explicitFocusOrder="0" pos="-8R 8 20% 48" posRelativeX="a6024ea6965f7c56"
         textCol="d6000000" edTextCol="ff000000" edBkgCol="0" labelText="Ctrlr"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="48" bold="1" italic="0" justification="33"/>
  <IMAGEBUTTON name="" id="a6024ea6965f7c56" memberName="ctrlrLogo" virtualName=""
               explicitFocusOrder="0" pos="2% 8 8% 48" buttonText="" connectedEdges="0"
               needsCallback="1" radioGroupId="0" keepProportions="1" resourceNormal=""
               opacityNormal="0.75" colourNormal="0" resourceOver="" opacityOver="0.85000002384185791016"
               colourOver="0" resourceDown="" opacityDown="0.99000000953674316406"
               colourDown="0"/>
  <TEXTEDITOR name="" id="f62f729d279478eb" memberName="versionInfoLabel" virtualName=""
              explicitFocusOrder="0" pos="-8R 8 66% 76" posRelativeX="cb1b7e33d5cdf245"
              bkgcol="0" outlinecol="9c000000" shadowcol="0" initialText=""
              multiline="1" retKeyStartsLine="1" readonly="1" scrollbars="1"
              caret="0" popupmenu="1"/>
  <LABEL name="new label" id="eb972e3a417aa275" memberName="label" virtualName=""
         explicitFocusOrder="0" pos="1.333% 120 46% 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Instance name" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="24" bold="1" italic="0" justification="10"/>
  <LABEL name="new label" id="bf16026dd2efbaf9" memberName="label2" virtualName=""
         explicitFocusOrder="0" pos="1.333% 176 46% 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Author" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="24"
         bold="0" italic="0" justification="10"/>
  <LABEL name="new label" id="1686cf6bdfd3d170" memberName="label3" virtualName=""
         explicitFocusOrder="0" pos="1.333% 216 46% 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Version" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="24"
         bold="0" italic="0" justification="10"/>
  <LABEL name="new label" id="6a832c3d3c867e98" memberName="label4" virtualName=""
         explicitFocusOrder="0" pos="1.333% 256 46% 24" edTextCol="ff000000"
         edBkgCol="0" labelText="URL" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="24"
         bold="0" italic="0" justification="10"/>
  <HYPERLINKBUTTON name="" id="251aa6b8d6ae85ab" memberName="instanceUrl" virtualName=""
                   explicitFocusOrder="0" pos="50% 256 48% 24" tooltip="http://www.rawmaterialsoftware.com/juce"
                   buttonText="" connectedEdges="0" needsCallback="0" radioGroupId="0"
                   url="http://www.rawmaterialsoftware.com/juce"/>
  <LABEL name="" id="f562f13a91eadcdd" memberName="instanceVersion" virtualName=""
         explicitFocusOrder="0" pos="50% 216 48% 24" edTextCol="ff000000"
         edBkgCol="0" labelText="" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="22"
         bold="1" italic="0" justification="9"/>
  <LABEL name="" id="34d3121f62edb861" memberName="instanceAuthor" virtualName=""
         explicitFocusOrder="0" pos="50% 176 48% 24" edTextCol="ff000000"
         edBkgCol="0" labelText="" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="22"
         bold="1" italic="0" justification="9"/>
  <LABEL name="" id="42b994d457a1c948" memberName="instanceName" virtualName=""
         explicitFocusOrder="0" pos="50% 120 48% 24" edTextCol="ff000000"
         edBkgCol="0" labelText="" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="24"
         bold="1" italic="0" justification="9"/>
  <TEXTEDITOR name="" id="b4e0855b38c272a2" memberName="instanceDescription"
              virtualName="" explicitFocusOrder="0" pos="2% 288 96% 80" bkgcol="ffffff"
              outlinecol="59000000" shadowcol="0" initialText="" multiline="1"
              retKeyStartsLine="1" readonly="1" scrollbars="1" caret="0" popupmenu="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
