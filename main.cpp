/*
 Project 5: Part 3 / 4
 video: Chapter 3 Part 4: 

Create a branch named Part3

 the 'new' keyword

 1) add #include "LeakedObjectDetector.h" to main
 
 3) Add 'JUCE_LEAK_DETECTOR(OwnerClass)' at the end of your UDTs.
 
 4) write the name of your class where it says "OwnerClass"
 
 5) write wrapper classes for each type similar to how it was shown in the video
 
 7) update main() 
      replace your objects with your wrapper classes, which have your UDTs as pointer member variables.
      
    This means if you had something like the following in your main() previously: 
*/
#if false
 Axe axe;
 std::cout << "axe sharpness: " << axe.sharpness << "\n";
 #endif
 /*
    you would update that to use your wrappers:
    
 */

#if false
AxeWrapper axWrapper( new Axe() );
std::cout << "axe sharpness: " << axWrapper.axPtr->sharpness << "\n";
#endif
/*
notice that the object name has changed from 'axe' to 'axWrapper'
You don't have to do this, you can keep your current object name and just change its type to your Wrapper class

 8) After you finish, click the [run] button.  Clear up any errors or warnings as best you can.
 
 see here for an example: https://repl.it/@matkatmusic/ch3p04example

 you can safely ignore any warnings about exit-time-destructors.
 if you would like to suppress them, add -Wno-exit-time-destructors to the .replit file 
   with the other warning suppression flags
 */





/*
 copied UDT 1:
 */
#include <iostream>
#include <string>
#include "LeakedObjectDetector.h"

struct EchoMachine
{
    int numPlaybackHead = 0;
    float headSpacing = 0.f;
    float tapeSaturation = 0.0f;  
    float springReverbMix = 0.0f;
    float outputLvl = 0.f;
    float tapeReadSpeed = 0;

    EchoMachine(){}
    ~EchoMachine()
    {
        std::cout << "dtor -> EchoMachine" << std::endl;
    }

    struct Overdrive 
    {
        
        float clippingPoint = 0.f ;
        float lowPassFreq = 0.f;
        int inputSigIndex = 0;
        float sigMix = 0.f;
        float outputLvl  = 0.0f;

        Overdrive(){}
        ~Overdrive()
        {
            std::cout << "dtor -> EchoMachine::Overdrive" << std::endl;
        }

        void limitSig (int inputSig, int limiTresh,bool autoMakeUpGain);
        void filterSig (int inputIndex, float q,float freq, char filterType);
        void distortionType (char distoType);

        JUCE_LEAK_DETECTOR(Overdrive)
    };

    void distorSignal ();

    void repeatSoundSource (bool repeatState, float loopStart,float loopEnd, float looplength);

    void tapeSpeed (bool playTape, int tapeSpeed);

    void echoFunction (int treshold);

    JUCE_LEAK_DETECTOR(EchoMachine)
};

struct OverdriveWrapper
{
    OverdriveWrapper( EchoMachine::Overdrive* ptr ) : pointerToOverdrive( ptr ) {}
    ~OverdriveWrapper()
    {
        delete pointerToOverdrive;
    }
    
    EchoMachine::Overdrive* pointerToOverdrive = nullptr;
};

struct EchoMachineWrapper
{
    EchoMachineWrapper( EchoMachine* ptr ) : pointerToEmachine( ptr ) {}
    ~EchoMachineWrapper()
    {
        delete pointerToEmachine;
    }
    
    EchoMachine* pointerToEmachine = nullptr;
};

void EchoMachine::Overdrive::limitSig(int inputSig, int limiTresh, bool autoMakeUpGain)
{
    if (autoMakeUpGain == 1)
    {
        sigMix += inputSig * limiTresh;
    }
    else
    {
        sigMix += inputSig;
    }
    
}

void EchoMachine::Overdrive::filterSig(int inputIndex, float q, float freq, char filterType = 'a')
{
    float centerQ = 0;

    centerQ = q * freq;
    inputSigIndex = inputIndex;
    lowPassFreq+= freq;
    
    if (filterType == 'a')
    {
        centerQ += 0.5f;
    }
    else
    {
        centerQ += 1.f;
    }

    std::cout << "EchoMachine::Overdrive::filterSig " << centerQ  << std::endl;
}

void EchoMachine::Overdrive::distortionType(char distoType)
{
    if (distoType == 'F')
    {
        clippingPoint = 0.01f;
        lowPassFreq = 1200;
    }
    else
    {
        clippingPoint = 0.6f;
        lowPassFreq = 8000;
    }

    std::cout << "EchoMachine::Overdrive::distortionType " << distoType  << std::endl;
}

void EchoMachine::distorSignal ()
{
    /*
    std::cout << "EchoMachine::distorSignal " << numPlaybackHead << std::endl;  //2) printing out something interesting
    */
    std::cout << "\nTHIS \nEchoMachine : numPlaybackHead -> " << this->numPlaybackHead  << "\n" << "and EchoMachine : tapeReadSpeed -> " << this->tapeReadSpeed << std::endl;
}

void EchoMachine::repeatSoundSource (bool repeatState, float loopStart, float loopEnd, float looplength)
{
    if (repeatState && (looplength > 30))
    {
        outputLvl = 1.0f;
        headSpacing = loopEnd - loopStart;
    }
    else
    {
        outputLvl = 0.0f;
    }
}

void EchoMachine::tapeSpeed (bool playTape, int tapeSpeed)
{
    if (playTape)
    {
        tapeReadSpeed *= tapeSpeed;
    }
    else
    {
        tapeReadSpeed = 1;
    }
}

void EchoMachine::echoFunction (int treshold)
{
    float delayTime = 0.0f;
        
    for (int i = 0; i <= treshold; i++)
    {
        delayTime += treshold;
        std::cout << i << " " << "delayTime : " << delayTime << std::endl;
    }
}

/*
 copied UDT 2:
 */
struct SolideStateAmp
{
    int numSpeakers;
    float speakerSize;
    float masterLvl;
    int ampModelingPresets;
    float fxvl;

    SolideStateAmp() : numSpeakers(4), speakerSize(12.0f), masterLvl(9.5f), ampModelingPresets(87), fxvl(5.5f){}  
    ~SolideStateAmp()
    {
        std::cout << "dtor -> SolideStateAmp" << std::endl;
    }

    void signalProcessing (bool processSignal, int sampleStart, int sampleEnd);
    void imitateTubeAmp (int ampSelectIndex, std::string speakerIr); 
    void amplifieSound (int inputSig, float gain);
    float volumeLevel (float maxVolume);

    JUCE_LEAK_DETECTOR(SolideStateAmp)
};

struct SolideStateAmpWrapper
{
    SolideStateAmpWrapper( SolideStateAmp* ptr ) : pointerToSolideStateAmp( ptr ) {}
    ~SolideStateAmpWrapper()
    {
        delete pointerToSolideStateAmp;
    }
    
    SolideStateAmp* pointerToSolideStateAmp = nullptr;
};

void SolideStateAmp::signalProcessing(bool processSignal, int sampleStart, int sampleEnd)
{
   sampleEnd = (processSignal != 1) ? 0 : 1 + sampleStart;

    /*
   std::cout << " \nSolideStateAmp::signalProcessing ampModelingPresets: " << ampModelingPresets << " \nsampleEnd: " << sampleEnd << std::endl;
   */

   std::cout << "\nTHIS\nSolideStateAmp : numSpeakers -> " << this->numSpeakers  << "\n" << "and SolideStateAmp : speakerSize -> " << this->speakerSize << std::endl;
}

void SolideStateAmp::imitateTubeAmp(int ampSelectIndex, std::string speakerIr)
{
    if (ampSelectIndex <= 50 && speakerIr == "Celestion")
    {
        numSpeakers = 4;
        speakerSize = 12.0f;
    }
    else
    {
        numSpeakers = 2;
        speakerSize = 10.0f; 
    }
}

void SolideStateAmp::amplifieSound(int inputSig, float gain)
{
    masterLvl = (inputSig * gain)/100;
}

float SolideStateAmp::volumeLevel (float maxVolume)
{
    float volLevel {0.f};
    
    while(volLevel < maxVolume)
    {
        volLevel += 0.5f;
        if (volLevel >= 11)
        {
            std::cout << volLevel << " is too loud,max at 11.0" << std::endl;
            break;
        }
    }
    return volLevel;
}

/*
 copied UDT 3:
 */
struct PerformanceMeter
{
    PerformanceMeter();
    
    float textSize;
    float windowSize;
    std::string fontStyle;
    std::string backGroundColor;
    double cpuClockSpeed;

    ~PerformanceMeter()
    {
         std::cout << "dtor -> PerformanceMeter" << std::endl;
    }

    struct DefaultMainWindow
    {
        float w;
        float h;

        DefaultMainWindow() : w(1920.f), h(1080.f){}
        ~DefaultMainWindow()
        {
            std::cout << "dtor -> PerformanceMeter::DefaultMainWindow" << std::endl;
        }
    JUCE_LEAK_DETECTOR(DefaultMainWindow)
};

    void displayCpu (int posX, int posY, float width, float height,bool active, double cpuClock);
    void displayRam (int posX, int posY, float width, float height,bool active);
    void displayDiskRead (int posX, int posY, float width, float height,bool active);
    void isWindowToBig (float myWindowH, float myWindowW);
    
    void printThisFm()
    {
        std::cout << "\nTHIS\nPerformanceMeter : textSize -> " << this->textSize  << "\n" << "and PerformanceMeter : windowSize -> " << this->windowSize << std::endl;
    }

    JUCE_LEAK_DETECTOR(PerformanceMeter)
    
};

struct PerformanceMeterWrapper
{
    PerformanceMeterWrapper( PerformanceMeter* ptr ) : pointerToPerformanceMeter( ptr ) {}
    ~PerformanceMeterWrapper()
    {
        delete pointerToPerformanceMeter;
    }
    
    PerformanceMeter* pointerToPerformanceMeter = nullptr;
};

struct DefaultMainWindowWrapper
{
    DefaultMainWindowWrapper( PerformanceMeter::DefaultMainWindow* ptr ) : pointerToDefaultMainWindow( ptr ) {}
    ~DefaultMainWindowWrapper()
    {
        delete pointerToDefaultMainWindow;
    }
    
    PerformanceMeter::DefaultMainWindow* pointerToDefaultMainWindow = nullptr;
};

PerformanceMeter::PerformanceMeter()
{
    textSize = 0;
    windowSize = 0.0f;
    fontStyle = "arial";
    backGroundColor = "green";
    cpuClockSpeed = 0.0; 
}

void PerformanceMeter::displayCpu(int posX, int posY, float width, float height, bool active, double cpuClock)
{
    int numLines = 8;
    textSize = height/numLines;

    if(active)
    {
        windowSize = (width * height) - (posX + posY);
        cpuClockSpeed = cpuClock * 2;
    }
    else
    {
        windowSize = 0;
    }
}

void PerformanceMeter::displayRam(int posX, int posY, float width, float height, bool active)
{
    if (active)
    {
        textSize = height/100;
        windowSize = (width * height) - (posX + posY);
        fontStyle = "default";
    }
    else
    {
        fontStyle = "arial";
    }

}

void PerformanceMeter::displayDiskRead(int posX, int posY, float width, float height, bool active)
{
    if (active)
    {
        textSize = height/25;
        windowSize = (width*height) - (posX +posY);
        fontStyle = "default";
    }
    else
    {
        fontStyle = "arial";
    }
}

void PerformanceMeter::isWindowToBig (float myWindowH, float myWindowW)
{
    DefaultMainWindow window;
        
    for (int i = 0 ; i <  myWindowW; i++)
    {
        if (i > window.w)
        {
            std::cout << "resizing window width to : " << myWindowW << std::endl;
            window.w = myWindowW;
            break;
        }
    }

    for (int i = 0 ; i <  myWindowH; i++)
    {
        if (i > window.h)
        {
            std::cout << "resizing window height to : " << myWindowH << std::endl;
            window.h = myWindowH;
            break;
        }
    }
}

/*
 new UDT 4:
 with 2 member functions
 */
struct Prog1
{
    EchoMachine univox;
    SolideStateAmp bossKatana;
    PerformanceMeter reaperPerfo;

    Prog1(){}
    ~Prog1()
    {
        std::cout << "dtor -> Prog1" << std::endl;
    }

    void printFuntionA();
    void printFuntionB();

    JUCE_LEAK_DETECTOR(Prog1)
};

struct Prog1Wrapper
{
    Prog1Wrapper( Prog1* ptr ) : pointerToProg1( ptr ) {}
    ~Prog1Wrapper()
    {
        delete pointerToProg1;
    }
    
    Prog1* pointerToProg1 = nullptr;
};

void Prog1::printFuntionA()
{
    std::cout << "univox.numPlaybackHead : " << univox.numPlaybackHead << std::endl;
}

void Prog1::printFuntionB()
{
    std::cout << "PerformanceMeter reaperPerfo fontStyle : " + reaperPerfo.fontStyle << std::endl;
}

/*
 new UDT 5:
 with 2 member functions
 */
struct Prog2
{
    EchoMachine::Overdrive univox;
    SolideStateAmp bossKatana;
    PerformanceMeter reaperPerfo;

    Prog2(){}
    ~Prog2()
    {
        std::cout << "dtor -> Prog2" << std::endl;
    }

    void printFunctionA();
    void printFunctionB();

    JUCE_LEAK_DETECTOR(Prog2) 
};

struct Prog2Wrapper
{
    Prog2Wrapper( Prog2* ptr ) : pointerToProg2( ptr ) {}
    ~Prog2Wrapper()
    {
        delete pointerToProg2;
    }
    
    Prog2* pointerToProg2 = nullptr;
};

void Prog2::printFunctionA()
{
    
    std::cout << "univox.outputLvl : " << univox.outputLvl << std::endl;
}

void Prog2::printFunctionB()
{
    univox.filterSig(0, 4, 800, 'a');
}

/*
 MAKE SURE YOU ARE NOT ON THE MASTER BRANCH

 Commit your changes by clicking on the Source Control panel on the left, entering a message, and click [Commit and push].
 
 If you didn't already: 
    Make a pull request after you make your first commit
    pin the pull request link and this repl.it link to our DM thread in a single message.

 send me a DM to review your pull request when the project is ready for review.

 Wait for my code review.
 */

//#include <iostream>
int main()
{
    EchoMachineWrapper echoMch( new EchoMachine() );
    SolideStateAmpWrapper solidAmp( new SolideStateAmp() );
    PerformanceMeterWrapper perfoMeter( new PerformanceMeter() );

    
    Prog1Wrapper p1( new Prog1() );
    Prog2Wrapper p2( new Prog2() );

    perfoMeter.pointerToPerformanceMeter->isWindowToBig(1080, 1920);
    perfoMeter.pointerToPerformanceMeter->isWindowToBig(2160, 3840);
    
    echoMch.pointerToEmachine->echoFunction(15);
    
    float lvl1 = solidAmp.pointerToSolideStateAmp->volumeLevel(15.0f);
    float lvl2 = solidAmp.pointerToSolideStateAmp->volumeLevel(8.5f);

    std::cout << "amp level 1 : " << lvl1 << std::endl;
    std::cout << "amp level 2 : " << lvl2 << std::endl;
    
    p1.pointerToProg1->printFuntionA();
    p1.pointerToProg1->printFuntionB();
    
    p2.pointerToProg2->printFunctionA();
    p2.pointerToProg2->printFunctionB();
    

    //if you don't have any std::cout statements in main() that access member variables of your U.D.Ts
    
    std::cout << "\nEchoMachine : numPlaybackHead = " << echoMch.pointerToEmachine->numPlaybackHead  << "\n" << "and EchoMachine : tapeReadSpeed = " << echoMch.pointerToEmachine->tapeReadSpeed << std::endl;
    echoMch.pointerToEmachine->distorSignal();
    
    std::cout << "\nSolideStateAmp : numSpeakers = " << solidAmp.pointerToSolideStateAmp->numSpeakers  << "\n" << "and SolideStateAmp : speakerSize = " << solidAmp.pointerToSolideStateAmp->speakerSize << std::endl;
    solidAmp.pointerToSolideStateAmp->signalProcessing(true, 1, 44100);

    std::cout << "\nPerformanceMeter : textSize = " << perfoMeter.pointerToPerformanceMeter->textSize  << "\n" << "and PerformanceMeter : windowSize = " << perfoMeter.pointerToPerformanceMeter->windowSize << std::endl;
    perfoMeter.pointerToPerformanceMeter->printThisFm();

    std::cout << "\ngood to go!" << std::endl;
}
