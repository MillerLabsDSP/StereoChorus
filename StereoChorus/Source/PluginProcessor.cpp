/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
StereoChorusAudioProcessor::StereoChorusAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
}

StereoChorusAudioProcessor::~StereoChorusAudioProcessor()
{
}

juce::AudioProcessorValueTreeState::ParameterLayout StereoChorusAudioProcessor::createParameterLayout() {
    juce::AudioProcessorValueTreeState::ParameterLayout parameters;
    
    juce::NormalisableRange<float> range_freq (0.5f, 15.f, 0.001f);
    parameters.add(std::make_unique<juce::AudioParameterFloat> (juce::ParameterID {"FREQ", 1},
                                                                 "Frequency",
                                                                 range_freq,
                                                                 1.0f));
    
    juce::NormalisableRange<float> range_depth (0.f, 2.f, 0.001f);
    parameters.add(std::make_unique<juce::AudioParameterFloat> (juce::ParameterID {"DEPTH", 2},
                                                                 "Depth",
                                                                 range_depth,
                                                                 1.0f));
    
    juce::NormalisableRange<float> range_delay (20.f, 40.f, 0.001f);
    parameters.add(std::make_unique<juce::AudioParameterFloat> (juce::ParameterID {"DELAY", 3},
                                                                 "Delay",
                                                                 range_delay,
                                                                 30.f));
            
    juce::NormalisableRange<float> range_shape (0.f, 1.f, 0.001f);
    parameters.add(std::make_unique<juce::AudioParameterFloat> (juce::ParameterID {"SHAPE", 4},
                                                                 "Shape",
                                                                range_shape,
                                                                 1.0f));
    juce::NormalisableRange<float> range_mix (0.f, 1.f, 0.001f);
    parameters.add(std::make_unique<juce::AudioParameterFloat> (juce::ParameterID {"MIX", 6},
                                                                 "Mix",
                                                                range_mix,
                                                                 1.0f));
        
    return parameters;
}

//==============================================================================
const juce::String StereoChorusAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool StereoChorusAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool StereoChorusAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool StereoChorusAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double StereoChorusAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int StereoChorusAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int StereoChorusAudioProcessor::getCurrentProgram()
{
    return 0;
}

void StereoChorusAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String StereoChorusAudioProcessor::getProgramName (int index)
{
    return {};
}

void StereoChorusAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void StereoChorusAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    for (int i = 0; i < NUM_PARAMS - 1; ++i) { param_values.push_back(0); }
    chorus.prepareToPlay(sampleRate, samplesPerBlock);
}

void StereoChorusAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool StereoChorusAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void StereoChorusAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    param_values[0] = apvts.getRawParameterValue("FREQ")->load();
    param_values[1] = apvts.getRawParameterValue("DEPTH")->load();
    param_values[2] = apvts.getRawParameterValue("DELAY")->load();
    param_values[3] = apvts.getRawParameterValue("SHAPE")->load();
    param_values[5] = apvts.getRawParameterValue("MIX")->load();
//    param_values[4] = apvts.getRawParameterValue("STEREO")->load();

    for (int channel = 0; channel < totalNumInputChannels; ++channel) {
        
        chorus.setFracRate(param_values[0]);
        chorus.setFracDepth(param_values[1]);
        chorus.setFracDelay(param_values[2]);
        chorus.setFracShape(param_values[3]);
        chorus.setMix(param_values[5]);
        
        chorus.processBuffer(buffer);
        
    }
}

//==============================================================================
bool StereoChorusAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* StereoChorusAudioProcessor::createEditor()
{
//    return new StereoChorusAudioProcessorEditor (*this);
    return new juce::GenericAudioProcessorEditor (*this);

}

//==============================================================================
void StereoChorusAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void StereoChorusAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new StereoChorusAudioProcessor();
}
