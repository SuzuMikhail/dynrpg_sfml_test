#include <DynRPG/DynRPG.h>
#include <SFML/Graphics.hpp>

#include <windows.h>
#include <io.h>
#include <iostream>
#include <fstream>
#include <fcntl.h>
#include <string>
#include <cstdio>
#include <ctime>
#include <iomanip>

using namespace std;

static const WORD MAX_CONSOLE_LINES = 500;
static const string WINDOW_PATH = "System\\system1.png";


RPG::Image * imgtext;
sf::RenderWindow * m_win;
sf::Sprite * sp;
sf::Texture * tex;

bool imageDrawn = false;

void rpg_draw(){
    imgtext = RPG::Image::create();
    imgtext->loadFromFile(WINDOW_PATH);
    RPG::screen->canvas->draw(20, 20, imgtext);
    RPG::Image::destroy(imgtext);
}

void sf_draw(){
    sp = new sf::Sprite();
    //cout << "sp created" << endl;

    tex = new sf::Texture();
    tex->loadFromFile(WINDOW_PATH);
    //cout << "tex->loadFromFile" << endl;

    sp->setTexture(*tex);
    sp->setPosition(200, 200);
    //cout << "sp setPosition" << endl;
    m_win->draw(*sp);
    //cout << "After draw" << endl;
    m_win->display();
    delete sp;
    delete tex;
    //cout << "pointers freed" << endl;
}

bool onStartup(char *pluginName) {
    int hConHandle;
    long lStdHandle;
    CONSOLE_SCREEN_BUFFER_INFO coninfo;
    FILE *fp;

    AllocConsole();

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &coninfo);
    coninfo.dwSize.Y = MAX_CONSOLE_LINES;
    SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), coninfo.dwSize);

    lStdHandle = (long)GetStdHandle(STD_OUTPUT_HANDLE);
    hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);
    fp = _fdopen( hConHandle, "w" );
    *stdout = *fp;
    setvbuf( stdout, NULL, _IONBF, 0 );

    // redirect unbuffered STDIN to the console
    lStdHandle = (long)GetStdHandle(STD_INPUT_HANDLE);
    hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);
    fp = _fdopen( hConHandle, "r" );
    *stdin = *fp;
    setvbuf( stdin, NULL, _IONBF, 0 );

    // redirect unbuffered STDERR to the console
    lStdHandle = (long)GetStdHandle(STD_ERROR_HANDLE);
    hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);
    fp = _fdopen( hConHandle, "w" );
    *stderr = *fp;
    setvbuf( stderr, NULL, _IONBF, 0 );
    std::ios::sync_with_stdio();

    return true;
}

void onInitTitleScreen(){
    m_win = new sf::RenderWindow();
    //m_win->create(GetParent(GetParent(RPG::screen->getCanvasHWND())));
    //m_win->create(RPG::screen->getCanvasHWND());
    m_win->create(GetParent(RPG::screen->getCanvasHWND()));
    //cout << "m_win create" << endl;
}


void onFrame(RPG::Scene scene){
    cout << endl << "onFrame()" << endl;

    if(imageDrawn == true){
        clock_t rpg_s, sf_s;

        rpg_s = clock();
        rpg_draw();
        double rpg_d = double(clock() - rpg_s) / double(CLOCKS_PER_SEC);
        cout << "rpg_draw: " << rpg_d << setprecision(5) << endl;

        sf_s = clock();
        sf_draw();
        double sf_d = double(clock() - sf_s) / double(CLOCKS_PER_SEC);
        cout << "sf_draw: " << sf_d << setprecision(5) << endl;

        Sleep(500);
    }
}

bool onComment(const char * text,
                const RPG::ParsedCommentData * parsedData,
                RPG::EventScriptLine * nextScriptLine,
                RPG::EventScriptData * scriptData,
                int eventId,
                int pageId,
                int lineId,
                int * nextLineId){
    if(strcmp(parsedData[0].command, "TestWin")){
        printf("TestWin Launched\n");

        imageDrawn = true;
        return false;
    } else {
        return true;
    }
}

void onExit(){
    //delete tex;
    //delete sp;
    delete m_win;
    //RPG::Image::destroy(imgtext);
}
