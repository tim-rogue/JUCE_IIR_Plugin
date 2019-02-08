/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
IirfilterAudioProcessorEditor::IirfilterAudioProcessorEditor (IirfilterAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (200, 200);
    
    //set up the cuttoff frequecy dial
    filterCutoffDial.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    filterCutoffDial.setRange(20.0f, 20000.0f);
    filterCutoffDial.setValue(600.0f);
    filterCutoffDial.setSkewFactorFromMidPoint(1000.f);
    filterCutoffDial.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    filterCutoffDial.setPopupDisplayEnabled(true, true, this);
    addAndMakeVisible(&filterCutoffDial);
    //set up the resonance dial
    filterResonanceDial.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    filterResonanceDial.setRange(1.0f, 5.0f);
    filterResonanceDial.setValue(2.0f);
    filterResonanceDial.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    filterResonanceDial.setPopupDisplayEnabled(true, true, this);
    addAndMakeVisible(&filterResonanceDial);
    //initializing the fields we access dial values with
    filterCuttoffValue = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.tree, CUTOFF_DIAL_ID, filterCutoffDial);
    filterResonanceValue = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.tree, RES_DIAL_ID, filterResonanceDial);
    
    
    
}

IirfilterAudioProcessorEditor::~IirfilterAudioProcessorEditor()
{
}

//==============================================================================
void IirfilterAudioProcessorEditor::paint (Graphics& g)
{
    
    Rectangle<int> titleArea(0, 10, getWidth(), 20);
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (Colours::black);
    g.setColour (Colours::white);
   
    g.drawText("Cutoff", 46, 70, 50, 25, Justification::centredLeft);
    g.drawText("Resonance", 107, 70, 70, 25, Justification::centredLeft);
    
    Rectangle<float> area(25,25,150,150);
    g.setColour(Colours::yellow);
    g.drawRoundedRectangle(area, 20.0f, 2.0f);
}

void IirfilterAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    
    //Rectangle<int> area = getLocalBounds().reduced(40);
    filterCutoffDial.setBounds(30, 90, 70, 70);
    filterResonanceDial.setBounds(100, 90, 70, 70);
}
