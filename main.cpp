/*
Project 5: Part 1 / 4
 video Chapter 2 - Part 12

 Create a branch named Part1

Purpose:  This project continues developing Project3.
       you will learn how to take code from existing projects and migrate only what you need to new projects
       you will learn how to write code that doesn't leak as well as how to refactor. 

 Destructors
        
 0) move all of your implementations of all functions to OUTSIDE of the class. 
 
 1) Copy 3 of your user-defined types (the ones with constructors and for()/while() loops from Project 3) here
 2) add destructors
        make the destructors do something like print out the name of the class.

 3) add 2 new UDTs that use only the types you copied above as member variables.

 4) add 2 member functions that use your member variables to each of these new UDTs

 5) Add constructors and destructors to these 2 new types that do stuff.  
        maybe print out the name of the class being destructed, or call a member function of one of the members.  be creative
 
 6) copy over your main() from the end of Project3 and get it to compile with the types you copied over.
        remove any code in main() that uses types you didn't copy over.
 
 7) Instantiate your 2 UDT's from step 4) in the main() function at the bottom.
 
 8) After you finish, click the [run] button.  Clear up any errors or warnings as best you can.
 
 */

/*
 copied UDT 1:
 */
#include <iostream>

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
    };

    void distorSignal ();

    void repeatSoundSource (bool repeatState, float loopStart,float loopEnd, float looplength);

    void tapeSpeed (bool playTape, int tapeSpeed);

    void echoFunction (int treshold);
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
    std::cout << "EchoMachine::distorSignal " << numPlaybackHead << std::endl;  //2) printing out something interesting
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
};

void SolideStateAmp::signalProcessing(bool processSignal, int sampleStart, int sampleEnd)
{
   sampleEnd = (processSignal != 1) ? 0 : 1 + sampleStart;

   std::cout << " \nSolideStateAmp::signalProcessing ampModelingPresets: " << ampModelingPresets << " \nsampleEnd: " << sampleEnd << std::endl;
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
};

    void displayCpu (int posX, int posY, float width, float height,bool active, double cpuClock);
    void displayRam (int posX, int posY, float width, float height,bool active);
    void displayDiskRead (int posX, int posY, float width, float height,bool active);
    void isWindowToBig (float myWindowH, float myWindowW);
    
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
    EchoMachine echoMch;
    SolideStateAmp solidAmp;
    PerformanceMeter perfoMeter;

    Prog1 p1;
    Prog2 p2;

    perfoMeter.isWindowToBig(1080, 1920);
    perfoMeter.isWindowToBig(2160, 3840);
    
    echoMch.echoFunction(15);
    
    float lvl1 = solidAmp.volumeLevel(15.0f);
    float lvl2 = solidAmp.volumeLevel(8.5f);

    std::cout << "amp level 1 : " << lvl1 << std::endl;
    std::cout << "amp level 2 : " << lvl2 << std::endl;
    
    p1.printFuntionA();
    p1.printFuntionB();
    
    p2.printFunctionA();
    p2.printFunctionB();

    std::cout << "good to go!" << std::endl;
}
