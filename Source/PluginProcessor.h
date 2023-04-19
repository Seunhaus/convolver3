/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//äîïèñûâàþ äåôàéíû äëÿ ïàðàìåòåð àéäè, ýòè íàçâàíèÿ ïàðàìåòðîâ áóäóò îòîáðàæàòüñÿ â DAW 
#define GAIN_ID "gain"
#define GAIN_NAME "Gain"

#define STRETCH_ID "stretch"
#define STRETCH_NAME "Stretch"


class Visualiser1 : public juce::AudioVisualiserComponent
{
public:
    Visualiser1() : AudioVisualiserComponent(2)
    {
        setBufferSize(512 );//(512)/*buffer.getNumSamples()
        setSamplesPerBlock(16);
        setColours(juce::Colours::black, juce::Colours::indianred);
       
    };
};

//==============================================================================
/**
*/
class NewProjectAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    NewProjectAudioProcessor();
    ~NewProjectAudioProcessor() override;




    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    //çäåñü îáúÿâëÿþòñÿ ïåðåìåííûå 
    double rawVolume;
    double stretchVolume;
    //äîáàâèë îáúåêò êëàññà òðèèñòåéò äëÿ àâòîìàòèçàöèè
    juce::AudioProcessorValueTreeState treeState;
    
    //îáúÿâëåíèå ôóíêöèè ëîàä ôàéë
    void loadFile();
    //i create variables for max length of samples
    int maxLengthOfConvolution = 1000;
    //I CREATE FUNCTION CONVOUTION
    juce::AudioSampleBuffer renderedBuffer{ 2,maxLengthOfConvolution};
    juce::AudioSampleBuffer sampleBuffer{2,1};
    // VOT TUT HUETA
    juce::FileLogger fileLog();
    
    //juce::File fileLog{ juce::File::getCurrentWorkingDirectory() };
    //juce::FileLogger::FileLogger{ log1, (std::string)"Its a log file", (int64)128 * 1024 }FileLogger fileLog();
    
    //static File File::getCurrentWorkingDirectory




    
    void preconvolve() {};
    inline double convolve(double c_currentSample, juce::AudioSampleBuffer c_renderedBuffer, juce::AudioSampleBuffer c_sampleBuffer, int min_len, int currentChannel)
    {
        //for (int channel_c=0; channel_c<2;channel_c++)
        //{ 
        //int min_len;

        const float* tempSampleBuffer = c_sampleBuffer.getReadPointer(currentChannel);
        float* tempRenderedBuffer = c_renderedBuffer.getWritePointer(currentChannel);
        //if (c_sampleBuffer.getNumSamples() >= maxLengthOfConvolution) min_len = maxLengthOfConvolution;
        //else min_len = c_sampleBuffer.getNumSamples();
        for (int i = 0; i <= min_len - 1; i++)
        {
            tempRenderedBuffer[i] = tempRenderedBuffer[i + 1] + tempSampleBuffer[i] * c_currentSample;
            //c_renderedBuffer.setSample(currentChannel, i, c_renderedBuffer.getSample(currentChannel, i + 1) + c_currentSample * tempSampleBuffer);

        }
        //c_renderedBuffer.setSample(currentChannel, c_sampleBuffer.getNumSamples(),
        //   c_currentSample * c_sampleBuffer.getSample(currentChannel, c_sampleBuffer.getNumSamples()));
        tempRenderedBuffer[min_len] = tempSampleBuffer[min_len] * c_currentSample;
        //}
        return tempRenderedBuffer[0];// STOYALO 0 
    };
        
    //juce::AudioVisualiserComponent visualiser{ 2 };

    

   
    //Visualiser1 visualiser;
private:
    
    
    juce::AudioFormatManager mFormatManager;
    juce::AudioFormatReader* mFormatReader{nullptr};
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(NewProjectAudioProcessor)

        
    };


    class MyFileLogger : public NewProjectAudioProcessor {

        std::unique_ptr<juce::FileLogger> m_flogger;
        MyFileLogger() { m_flogger = std::unique_ptr<juce::FileLogger>(juce::FileLogger::createDateStampedLogger("foo", "mylog", ".txt", "Welcome to plugin")); };
        double NewProjectAudioProcessor::getTailLengthSeconds() const
        {
            if (m_flogger)
                m_flogger->logMessage("getTailLengthSeconds called");
            return 0.0;
        }

    };
    

