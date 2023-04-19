/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class Convolver3AudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    Convolver3AudioProcessorEditor (Convolver3AudioProcessor&);
    ~Convolver3AudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

    void openButtonClicked();
    void playButtonClicked();
private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    Convolver3AudioProcessor& audioProcessor;

    //-create button 
    juce::TextButton openButton;
    juce::TextButton playButton;
    juce::TextButton stopButton;
    enum TransportState
    {
        Stopped,
        Starting,
        Playing,
        Stopping
    };

    juce::AudioFormatManager formatManager;

    //void changeState(TransportState newState)
    //{
    //    if (state != newState)
    //    {
    //        state = newState;

    //        switch (state)
    //        {
    //        case Stopped:                           // [3]
    //            stopButton.setEnabled(false);
    //            playButton.setEnabled(true);
    //            transportSource.setPosition(0.0);
    //            break;

    //        case Starting:                          // [4]
    //            playButton.setEnabled(false);
    //            transportSource.start();
    //            break;

    //        case Playing:                           // [5]
    //            stopButton.setEnabled(true);
    //            break;

    //        case Stopping:                          // [6]
    //            transportSource.stop();
    //            break;
    //        }
    //    }
    //}

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Convolver3AudioProcessorEditor)
};
