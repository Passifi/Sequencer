#pragma once
#include <array>
#include <JuceHeader.h>
const int numberOfPushButtons = 16;
//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class BeatButtonLook : public juce::LookAndFeel_V4 {

   public:

    void drawButtonBackground(juce::Graphics& g, juce::Button& button, const juce::Colour& backgroundColour, bool shouldDrawButtonAsHighlighted, bool isButtonDown) override;


};





class MainComponent  : public juce::AudioAppComponent
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent() override;

    //==============================================================================
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

    //==============================================================================
    void paint (juce::Graphics& g) override;
    void resized() override;

private:
    BeatButtonLook look;
    std::array<juce::TextButton,numberOfPushButtons> pushButtons;
    
    //==============================================================================
    // Your private member variables go here...


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
