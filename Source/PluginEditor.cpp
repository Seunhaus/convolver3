/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "PluginProcessor.cpp"
//#include "PluginProcessor.cpp"
//==============================================================================
NewProjectAudioProcessorEditor::NewProjectAudioProcessorEditor (NewProjectAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    //Visualiser visualiser;
    //ADD VISUALISER
    addAndMakeVisible(visualiser);

    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    //îïðåäåëÿþ êíîïêó, ñòàâëþ ôóíêöèþ íà ýòó êíîïêó
    mLoadButton.onClick = [&]() {audioProcessor.loadFile(); };
    addAndMakeVisible(mLoadButton);


    setSize (400, 300);
    //äîïèñàë âîò ýòîò ñëàéäåð àòòà÷
    sliderAttach = new juce::AudioProcessorValueTreeState::SliderAttachment (audioProcessor.treeState, GAIN_ID, gainSlider);

    sliderAttach = new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.treeState, STRETCH_ID, stretchSlider);

    //äîáàâëÿþ
    gainSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    gainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 25);
    gainSlider.setRange(0.0, 1.0);
    //òàêæå äîïèñàë àää ëèñòåíåð
    gainSlider.addListener(this);
    gainSlider.setValue(0.5);
    addAndMakeVisible(gainSlider);

    



    //ïîëàãàþ òàê ìîæíî îïðåäåëèòü âòîðîé ñëàéäåð
    stretchSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    stretchSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 25);
    stretchSlider.setRange(0.5, 2.0);
    
    stretchSlider.addListener(this);
    stretchSlider.setValue(1);
    addAndMakeVisible(stretchSlider);

}

NewProjectAudioProcessorEditor::~NewProjectAudioProcessorEditor()
{
}

//==============================================================================
void NewProjectAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("fusk2!", getLocalBounds(), juce::Justification::centred, 1);
}

void NewProjectAudioProcessorEditor::resized()
{
    //visualiser resize 
    visualiser.setBounds(180, 50, 300, 100);

    mLoadButton.setBounds(100, 50, 50, 50);
    //äîáàâëÿþ ãðàíèöû äëÿ ñëàéäåðà åñëè ðàçìåð îêíà áóäåò èçìåíåí ïîëüçîâàòåëåì
    gainSlider.setBounds(10, 50, 20, 200);

    stretchSlider.setBounds(40, 50, 20, 200);


    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
//äîïèñàë ýòî, ýòî ïåðåîïðåäåëÿåò ìåòîä ñëàéäåðâàëþå÷åíäæåä
void  NewProjectAudioProcessorEditor::sliderValueChanged(juce::Slider* slider)
{
    if (slider == &gainSlider)
    {
        audioProcessor.rawVolume = gainSlider.getValue();
    }
    if (slider == &stretchSlider)
    {
        audioProcessor.stretchVolume = stretchSlider.getValue();
    }
}
