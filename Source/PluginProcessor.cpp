/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//add visualiser

Visualiser1 visualiser;

//Visualiser1 visualiser;
//ïûòàþñü äàòü ïîíÿòü ïðåïðîöåññîðó ÷òî ìíå íóæíû ýòè åáàíûå ôóíêöèè 
//==============================================================================
NewProjectAudioProcessor::NewProjectAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ),
    //äîïèñûâàþ ïðî treestate
    treeState(*this, nullptr)
#endif
{
    mFormatManager.registerBasicFormats();
    //çäåñü äîïèñûâàþ õóéíþ, ó÷èòûâàÿ îáúÿâëåííûå íàçâàíèÿ äëÿ ïàðàìåòîâ
    // à çäåñü ïèøó ïðî íîðìàëàéçàáë ðåíæ
    juce::NormalisableRange<float> gainRange(0.0f, 1.0f);
    treeState.createAndAddParameter(GAIN_ID, GAIN_NAME, GAIN_NAME, gainRange, 0.5, nullptr, nullptr);

    //ñòðåò÷ ïàðàìåòð
    juce::NormalisableRange<float> stretchRange(0.5f, 2.0f);
    treeState.createAndAddParameter(STRETCH_ID, STRETCH_NAME, STRETCH_NAME, stretchRange, 1, nullptr, nullptr);
}

NewProjectAudioProcessor::~NewProjectAudioProcessor()
{
    mFormatReader = nullptr;
}

//==============================================================================
const juce::String NewProjectAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool NewProjectAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool NewProjectAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool NewProjectAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double NewProjectAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int NewProjectAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int NewProjectAudioProcessor::getCurrentProgram()
{
    return 0;
}

void NewProjectAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String NewProjectAudioProcessor::getProgramName (int index)
{
    return {};
}

void NewProjectAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void NewProjectAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    
    
    visualiser.clear();
    renderedBuffer.clear();
    sampleBuffer.clear();

    

    //POINTERS

    //auto *tempSampleBuffer_ptr = sampleBuffer.getSample(currentChannel, i);
    //auto *tempRenderedBuffer_ptr = renderedBuffer.getSample(currentChannel, i);

    //íóæíî óñòàíîâèòü ñåìïëðåéò
    //setCurrentPlay
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void NewProjectAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool NewProjectAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void NewProjectAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.

    //rawVolume = 0.015;

    
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.

    int min_len;
    if (renderedBuffer.getNumSamples() >= maxLengthOfConvolution) min_len = maxLengthOfConvolution;
    else min_len = sampleBuffer.getNumSamples();

    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);

        for (int sample = 0; sample < buffer.getNumSamples(); ++sample) {
            channelData[sample] = rawVolume*convolve(buffer.getSample(channel, sample), renderedBuffer, sampleBuffer, min_len, channel);
        }






        //convolve(double c_currentSample, juce::AudioSampleBuffer c_renderedBuffer, 
        //juce::AudioSampleBuffer c_sampleBuffer, int c_maxLengthOfConvolution,int currentChannel)

        // ..do something to the data...
        //I ADD VISUALISER
       
        visualiser.pushBuffer(sampleBuffer);

    }






    /*for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer(channel);

        for (int sample = 0; sample < buffer.getNumSamples(); ++sample) {
            channelData[sample] = buffer.getSample(channel, sample) * rawVolume * stretchVolume;
        }






        //convolve(double c_currentSample, juce::AudioSampleBuffer c_renderedBuffer, 
        //juce::AudioSampleBuffer c_sampleBuffer, int c_maxLengthOfConvolution,int currentChannel)

        // ..do something to the data...
    }*/
    //up - LAST WORKING GAIN 
}

//==============================================================================
bool NewProjectAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* NewProjectAudioProcessor::createEditor()
{
    return new NewProjectAudioProcessorEditor (*this);
}

//==============================================================================
void NewProjectAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void NewProjectAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//ôóíêöèÿ ëîàä ôàéë
void NewProjectAudioProcessor::loadFile()
{
   juce::FileChooser chooser{ "Please load a file" };
    if (chooser.browseForFileToOpen())
        //ÄÎÏÈÑÀÒÜ ÒÓÒ, ÂÈÄÅÎ 13:14
    {
        auto file = chooser.getResult();
        mFormatReader = mFormatManager.createReaderFor(file);
        //äîïèñàíî ò.å. ñêîïèíðîâàíî ñ ôîðóìà è èçìåíåíî
        if (mFormatReader != 0)
        {
            juce::AudioSampleBuffer sampleBuffer(mFormatReader->numChannels, mFormatReader->lengthInSamples); 
            mFormatReader->read(&sampleBuffer, 0, mFormatReader->lengthInSamples, 0, true, true);
            //sampleBuffer = sampleBuffer1;//somnitelnaya huita
            //juce::AudioFormatReader::read(& buffer, 0, 0, 0l, true, true)
            //const auto lenaboba = mFormatReader->lengthInSamples;
             //juce::AudioFormatReader::read(&buffer, 0, 0, 0l, true, true);
            
            //ñòåð ýòó õóéí. íó ò.å. ñêîðåå âñåãî îíà íå áóäåò ðàáîòàòü ÿ õç çà÷åì ÿ å¸ îñòàâëÿþ
            //juce::AudioSampleBuffer buffer(mFormatReader->numChannels, mFormatReader->lengthInSamples);
            //buffer.readFromAudioReader(mFormatReader, 0, mFormatReader->lengthInSamples, 0, true, true);
            //float* firstChannelSamples = buffer.getSampleData(0, 0);
        }
    }
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new NewProjectAudioProcessor();
}

