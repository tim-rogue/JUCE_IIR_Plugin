/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
IirfilterAudioProcessor::IirfilterAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       ),tree(*this,nullptr,"Attachments",{std::make_unique<AudioParameterFloat>("cutoff", "Cutoff", 20.0f, 20000.0f, 600.0f),
                                                           std::make_unique<AudioParameterFloat>("resonance", "Resonance", 1.0f, 5.0f, 2.0f)})
                        ,lowPassFilter(dsp::IIR::Coefficients<float>::makeLowPass(44100.0, 2000.0f, 0.1f))
#endif
{
}

IirfilterAudioProcessor::~IirfilterAudioProcessor()
{
}

//==============================================================================
const String IirfilterAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool IirfilterAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool IirfilterAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool IirfilterAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double IirfilterAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int IirfilterAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int IirfilterAudioProcessor::getCurrentProgram()
{
    return 0;
}

void IirfilterAudioProcessor::setCurrentProgram (int index)
{
}

const String IirfilterAudioProcessor::getProgramName (int index)
{
    return {};
}

void IirfilterAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void IirfilterAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    currSampleRate = sampleRate;
    
    // setting up the dsp module for use
    // this must be initialized
    dsp::ProcessSpec spec;
    spec.sampleRate = sampleRate;
    spec.numChannels = getTotalNumInputChannels();
    spec.maximumBlockSize = samplesPerBlock;

    lowPassFilter.prepare(spec);
    lowPassFilter.reset();
}

void IirfilterAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool IirfilterAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
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

void IirfilterAudioProcessor::updateFilter()
{
    float freq = *tree.getRawParameterValue(CUTOFF_DIAL_ID);
    float res = *tree.getRawParameterValue(RES_DIAL_ID);
    
    *lowPassFilter.state = *dsp::IIR::Coefficients<float>::makeLowPass(currSampleRate, freq, res);
    
}

void IirfilterAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    dsp::AudioBlock<float> block(buffer);
    updateFilter();
    lowPassFilter.process(dsp::ProcessContextReplacing<float>(block));
}

//==============================================================================
bool IirfilterAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* IirfilterAudioProcessor::createEditor()
{
    return new IirfilterAudioProcessorEditor (*this);
}

//==============================================================================
void IirfilterAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void IirfilterAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new IirfilterAudioProcessor();
}
