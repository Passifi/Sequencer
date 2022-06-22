#include "MainComponent.h"

//==============================================================================







void BeatButtonLook::drawButtonBackground(juce::Graphics& g, juce::Button& button, const juce::Colour& backgroundColour, bool shouldDrawButtonAsHighlighted, bool isButtonDown)  {
  auto buttonArea = button.getLocalBounds();
  buttonArea.setWidth(200);
  buttonArea.setHeight(120);

  g.setColour(juce::Colours::orange);
  g.fillRect(buttonArea);
  
}

MainComponent::MainComponent()
{
    // Make sure you set the size of the component after
    // you add any child components.
    setSize (800, 600);
    
    look.setColour(juce::TextButton::ColourIds::buttonColourId,juce::Colours::red);
    addAndMakeVisible(bButton1);
    addAndMakeVisible(bButton2);
    addAndMakeVisible(bButton3);
    addAndMakeVisible(bButton4);
    addAndMakeVisible(bButton5);
    addAndMakeVisible(bButton6);
    addAndMakeVisible(bButton7);
    addAndMakeVisible(bButton8);
    bButton1.setLookAndFeel(&look);
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
    const int xOffset = 62;
    const int punshW = 60;
    const int punshH = 60;
    bButton1.setBounds(20,300,punshW,punshH);
    bButton2.setBounds(20+xOffset, 300, 60, 60);
    bButton3.setBounds(20+xOffset*2, 300, punshW, punshH);
    bButton4.setBounds(20 + xOffset * 3, 300, punshW, punshH);
    bButton5.setBounds(20 + xOffset * 4, 300, punshW, punshH);
    bButton6.setBounds(20 + xOffset * 5, 300, punshW, punshH);
    bButton7.setBounds(20 + xOffset * 6, 300, punshW, punshH);
    bButton8.setBounds(20 + xOffset * 7, 300, punshW, punshH);
    // This is called when the MainContentComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
}
