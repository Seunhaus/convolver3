/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Convolver3AudioProcessorEditor::Convolver3AudioProcessorEditor (Convolver3AudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)//, openButton("Open")
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    addAndMakeVisible(&openButton);
    openButton.setButtonText("Open");
    openButton.onClick = [this] { openButtonClicked(); };

    addAndMakeVisible(&playButton);
    openButton.setButtonText("Play");
    openButton.onClick = [this] { playButtonClicked(); };

    //format manager
    //formatManager

    setSize (600, 400);
   
}

Convolver3AudioProcessorEditor::~Convolver3AudioProcessorEditor()
{
}

//==============================================================================
void Convolver3AudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void Convolver3AudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    openButton.setBounds(10, 10, getWidth() - 30, 30);
    openButton.setBounds(10, 50, getWidth() - 30, 30);
}

void Convolver3AudioProcessorEditor::openButtonClicked()
{
    DBG("openButtocn clicked");

    //choose a file 
    juce::FileChooser chooser("Choose a file",
        juce::File::getSpecialLocation(juce::File::userDocumentsDirectory),
        "*.wav",//"*.flac",
        true,
        false,
        nullptr);
    //if chooses a file 
    if(chooser.FileChooser::launchAsync())
        //what the user choose?
        //read a file
        //get the file ready to play
}

void Convolver3AudioProcessorEditor::playButtonClicked()
{
    DBG("playButtocn clicked");
}
