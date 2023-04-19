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
class NewProjectAudioProcessorEditor : public juce::AudioProcessorEditor,
                                       public juce::Slider::Listener
                                       //,public Visualiser1
    //äîïèñàë  public juce::Slider::Listener 
{
public:
    NewProjectAudioProcessorEditor (NewProjectAudioProcessor&);
    ~NewProjectAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

    //ïðîòîòèï, ðàçðåøàþùèé ïåðåîïðåäåëåíèå ìåòîäà
    void  sliderValueChanged(juce::Slider* slider) override;

    //âûçûâàþ îáúåêò êëàññà ñëàéäåð àòòà÷åìåíò
    //÷åë âòóòîðå ñêàçàë ÷òî íóæíî èñïîëüçîâàòü óêàçàòåëü, ïîýòîìó äîáàâèë â óãëîâûå ñêîáêè êëàññ è ïåðåä íèì äîïèñàë
    //juce::ScopedPointer, juce ïîäñêàçûâàåò ÷òî îí óñòàðåë, ïîýòîìó ÿ çàìåíþ íà òî ÷òî îí ïðåäëàãàåò std::unique_ptr
    juce::ScopedPointer <juce::AudioProcessorValueTreeState::SliderAttachment> sliderAttach;



private:
        // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    NewProjectAudioProcessor& audioProcessor;
    //ñîçäàþ ñëàéäåðû

    juce::Slider gainSlider;
    juce::Slider stretchSlider;
    juce::Slider mixSlider;

    //îáúÿâëÿþ êíîïêó
    juce::TextButton mLoadButton{ "Load" };
    

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NewProjectAudioProcessorEditor)
};
