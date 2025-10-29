# CSE 471 Project 1 By Graham Parker
The title of the selection I have created is FinalSelection.wav.
The title of the 15 second Effects Component Shorter Piece I have created is EffectsComponentShorterPiece.wav.

I am a one person group so my only team member is: Graham Parker.

My score files are the same as the ones used in Step 5 except that "note" objects now have a "sample" attribute instead of a key. In addition alongside "notes" there are also "effects". Effects have "measures" and "beats" like notes, but they also have "intensity" ranging from 0 to 1 (double) denoting how strong the Fuzz effect will be on the Recorded Performance Synthesizer. 

Example score file:
```
<score bpm="140" beatspermeasure="4">
     <instrument instrument="RecordingInstrument">
        <effect measure="1" beat="1" intensity=".2"/>
        <note measure="1" beat="1" duration="20" sample="/Guitar_1.wav"/>
     </instrument>
</score>
```
 
The actual score file used to make my Final Selection is named FinalSelection.score inside the "Synthie" folder.
The actual score file used to make my 15 second Effects Component Shorter Piece is named "EffectsComponentShorterPiece.score" inside the "Synthie" folder

# Sequencer Component:
The sequencer component is simular to the Synthesizer component from Step 5. It generates notes, instruments, and effects. It parses the score file and creates a "CNote" object for each effect or note. Those CNote objects either set their "m_soundRecording" to the sample's sound source, or set their "m_fuzz_intensity" to the intensity provided. Every frame, the "Generate()" function is called in the sequencer and it runs a loop that calls every "Generate()" function for each instrument. These will all be "CRecordingInstrument"s. 

Full ownership of the Sequencer Component goes to Graham Parker

# Recorded Performance Synthesizer:
The recorded performance synthesizer is inside the "CRecordingInstrument" class. It takes input from the sequencer component in the form of a double. It takes in audio frames from the given sample on the current frame of the audio (calculated from the inverse of the sample rate multiplied by the number of seconds passed). It then temporarily scales the audio volume up if the fuzz effect is active so that the Hyperbolic Tangent Function can effectively operate. The TanH curve resembles the curve of the desired fuzz effect (being squarish and less rounded than a traditional sine wave), so by running the current frame of audio input through the TanH function, we can effectively turn our audio wave into a more square shape. We then scale the audio back down to size afterwards so the sound is not unusually loud. Then the frames are sent to the "Generate()" function of the Effects class before being returned to the Sequencer.

10 - The recording exists

20 - The recording is played by the synthesizer

30 - The recording is synchronized

35 - One Effect has been applied ( fuzz effect )

40 - There are at least 30 points in the score where the effect was modified/controlled

total points: 40/50

Full ownership of the Recorded Performance Synthesizer goes to Graham Parker

# Effects Component:
The Effects component recieves a double of the frames of audio created by the Recorded Performance Synthesizer. It then passes the audio back to the Recorded Performance Synthesizer.

10 - Component Passes Audio

total points: 10/50

Full ownership of the Effects Component goes to Graham Parker
