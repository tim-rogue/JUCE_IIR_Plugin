/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class IirfilterAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    IirfilterAudioProcessorEditor (IirfilterAudioProcessor&);
    ~IirfilterAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    Slider filterCutoffDial;
    Slider filterResonanceDial;
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    IirfilterAudioProcessor& processor;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (IirfilterAudioProcessorEditor)
    
public:
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> filterCuttoffValue;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> filterResonanceValue;
};
