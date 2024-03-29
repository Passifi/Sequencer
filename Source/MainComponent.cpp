#include "MainComponent.h"

//==============================================================================



void PadLook::drawButtonBackground(juce::Graphics& g, juce::Button& button, const juce::Colour& backgroundColour, bool shouldDrawButtonAsHighlighted, bool isButtonDown) {
    auto buttonArea = button.getLocalBounds();
   
    auto edge = 4;

    buttonArea.removeFromBottom(edge);
    buttonArea.removeFromRight(edge);
    
    juce:: Colour color = shouldDrawButtonAsHighlighted ? juce::Colours::bisque : juce::Colours::antiquewhite;
    juce:: Colour colorShadow = juce::Colours::darkred;
    g.setColour(colorShadow);
    g.fillRect(buttonArea);
    buttonArea.translate(-4,-4);
    g.setColour(color);
    g.fillRect(buttonArea);
}



void BeatButtonLook::drawButtonBackground(juce::Graphics& g, juce::Button& button, const juce::Colour& backgroundColour, bool shouldDrawButtonAsHighlighted, bool isButtonDown)  {
  auto buttonArea = button.getLocalBounds();
  buttonArea.setWidth(200);
  buttonArea.setHeight(120);

  juce::Colour color = shouldDrawButtonAsHighlighted ? juce::Colours::orangered : juce::Colours::orange;
  color = isButtonDown ? juce::Colours::red : color;
  g.setColour(color);
  g.fillRect(buttonArea);

  
}

DialSliderLook::DialSliderLook() {
    setColour(juce::Slider::thumbColourId,juce::Colours::orange);
}

void DialSliderLook::drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height, float sliderPos, const float rotaryStartAngle, const float rotaryEndAngle, juce::Slider&)  {
    auto radius = (float)juce::jmin(width / 2, height / 2) - 4.0f;
    auto centreX = (float)x + (float)width * 0.5f;
    auto centreY = (float)y + (float)height * 0.5f;
    auto rx = centreX - radius;
    auto ry = centreY - radius;
    auto rw = radius * 2.0f;
    auto angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
    g.setColour(juce::Colours::lavenderblush);
    g.fillEllipse(rx, ry, rw, rw);
    g.setColour(juce::Colours::red);
    g.drawEllipse(rx, ry, rw, rw, 1.0f);

    juce::Path p;
    auto pointerLength = radius * 0.8f;
    auto pointerThickness = 2.0f;
    p.addRectangle(-pointerThickness * 0.8f, -radius, pointerThickness, pointerLength);
    p.applyTransform(juce::AffineTransform::rotation(angle).translated(centreX, centreY));

    g.setColour(juce::Colours::red);
    g.fillPath(p);
}

MainComponent::MainComponent()
{
    // Make sure you set the size of the component after
    // you add any child components.
    setSize (1200, 600);
    sliders[Speed].setSliderStyle(juce::Slider::Rotary);
    sliders[Speed].setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);

    look.setColour(juce::TextButton::ColourIds::buttonColourId,juce::Colours::red);
    

    for (int i = 0; i < KnobSliderLength; i++)
    {
        if (i < 16)
        {
            addAndMakeVisible(pads[i]);
            pads[i].setLookAndFeel(&padLook);
        }
        sliders[i].setSliderStyle(juce::Slider::Rotary);
        sliders[i].setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
        addAndMakeVisible(sliders[i]);
        sliders[i].setLookAndFeel(&lookSlider);
    }
    
    
    
    for (int i = 0; i < numberOfPushButtons; i++)
    {
        addAndMakeVisible(pushButtons[i]);
        pushButtons[i].setLookAndFeel(&look);
    }
   
    // Some platforms require permissions to open input channels so request that here
    if (juce::RuntimePermissions::isRequired (juce::RuntimePermissions::recordAudio)
        && ! juce::RuntimePermissions::isGranted (juce::RuntimePermissions::recordAudio))
    {
        juce::RuntimePermissions::request (juce::RuntimePermissions::recordAudio,
                                           [&] (bool granted) { setAudioChannels (granted ? 2 : 0, 2); });
    }
    else
    {
        // Specify the number of input and output channels that we want to open
        setAudioChannels (2, 2);
    }
}

MainComponent::~MainComponent()
{
    // This shuts down the audio device and clears the audio source.
    shutdownAudio();
}

//==============================================================================
void MainComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    // This function will be called when the audio device is started, or when
    // its settings (i.e. sample rate, block size, etc) are changed.

    // You can use this function to initialise any resources you might need,
    // but be careful - it will be called on the audio thread, not the GUI thread.

    // For more details, see the help for AudioProcessor::prepareToPlay()
}

void MainComponent::getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill)
{
    // Your audio-processing code goes here!

    // For more details, see the help for AudioProcessor::getNextAudioBlock()

    // Right now we are not producing any data, in which case we need to clear the buffer
    // (to prevent the output of random noise)
    bufferToFill.clearActiveBufferRegion();
}

void MainComponent::releaseResources()
{
    // This will be called when the audio device stops, or when it is being
    // restarted due to a setting change.

    // For more details, see the help for AudioProcessor::releaseResources()
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
    
    // You can add your drawing code here!
}

void MainComponent::resized()
{
    const int padX = 100;
    const int padY = 20;
    const int padW = 120;
    const int padH = 80;
    const int padOffsetX = padW + 5;
    const int padOffsetY = padH + 5;

    const int punshW = 60;
    const int punshH = 60;
    const int xOffset = punshW+2;
    int leftStart = (getWidth()/2 ) - xOffset*(numberOfPushButtons/2);
    int bottomOffset = getHeight() - punshH *2;
    sliders[Speed].setBounds(getWidth()/2,20 , 64, 64);
    sliders[Swing].setBounds(getWidth() / 2+65, 34, 50, 50);


    sliders[CutOff].setBounds(getWidth()/2 + getWidth()/4, 20, 60,60);
    sliders[Res].setBounds(getWidth() / 2 + getWidth() / 4 + 62, 20, 60, 60);
    sliders[Gain].setBounds(getWidth() / 2 + getWidth() / 4 + 124, 20, 60, 60);

    for (int i = 0; i < numberOfPushButtons; i++)
    {
         
        pads[i].setBounds((padX) + padOffsetX*(i%4), padY + (int)(i / 4) * padOffsetY, padW, padH);
        
        pushButtons[i].setBounds(leftStart+xOffset*i,bottomOffset,punshW,punshH);

    }
   
    
    // This is called when the MainContentComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
}
