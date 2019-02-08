/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

#define CUTOFF_DIAL_ID "cutoff"
#define CUTOFF_DIAL_NAME "Cutoff"
#define CUTTOFF_DIAL_MIN_VAL 20.0f
#define CUTTOFF_DIAL_MAX_VAL 20000.0f
#define CUTTOFF_DIAL_DEFAULT_VAL 600.0f
#define RES_DIAL_ID "resonance"
#define RES_DIAL_NAME "Resonance"
#define RES_DIAL_MIN_VAL 1.0f
#define RES_DIAL_MAX_VAL 5.0f
#define RES_DIAL_DEFAULT_VAL 2.0f

//==============================================================================
/**
*/
class IirfilterAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    IirfilterAudioProcessor();
    ~IirfilterAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    void updateFilter();
    
    AudioProcessorValueTreeState tree;
    
private:
    double currSampleRate;
    dsp::ProcessorDuplicator <dsp::IIR::Filter <float>, dsp::IIR::Coefficients <float>> lowPassFilter;
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (IirfilterAudioProcessor)
};
