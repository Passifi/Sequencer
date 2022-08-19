#pragma once
#include <array>
#include <JuceHeader.h>
const int numberOfPushButtons = 16;
const int numberOfPads = 16;
//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class BeatButtonLook : public juce::LookAndFeel_V4 {

   public:

    void drawButtonBackground(juce::Graphics& g, juce::Button& button, const juce::Colour& backgroundColour, bool shouldDrawButtonAsHighlighted, bool isButtonDown) override;


};

class PadLook : public juce::LookAndFeel_V4 {

public:

    void drawButtonBackground(juce::Graphics& g, juce::Button& button, const juce::Colour& backgroundColour, bool shouldDrawButtonAsHighlighted, bool isButtonDown) override;


};


class DialSliderLook : public juce::LookAndFeel_V4 {
    public:
        DialSliderLook();
        void drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height, float sliderPos, const float rotaryStartAngle, const float rotaryEndAngle, juce::Slider&) override;

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
    
    enum KnobSliders  {
        Speed,Swing, CutOff, Res, Gain,KnobSliderLength
    };

    
    
    BeatButtonLook look;
    DialSliderLook lookSlider;
    PadLook padLook;
    std::array<juce::TextButton, numberOfPads> pads;
    std::array<juce::TextButton,numberOfPushButtons> pushButtons;
    std::array<juce::Slider,KnobSliderLength> sliders;

    //==============================================================================
    // Your private member variables go here...


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
