#include <string>
#include <stdio.h>
#include <SDL.h>
//
// keystroke.c - Pauses, then simulates a key press
// and release of the "A" key.
//
// Written by Ted Burke - last updated 17-4-2012
//
// To compile with MinGW:
//
//      gcc -o keystroke.exe keystroke.c
//
// To run the program:
//
//      keystroke.exe
//
// ...then switch to e.g. a Notepad window and wait
// 5 seconds for the A key to be magically pressed.
//

// Because the SendInput function is only supported in
// Windows 2000 and later, WINVER needs to be set as
// follows so that SendInput gets defined when windows.h
// is included below.
#include <vector>
#include <Controller.h>
#define WINVER 0x0500
#include <windows.h>


std::vector<ControllerHandler> Controls;

enum KEY{
    K_None = 0,K_ESC,K_1,K_2,K_3,K_4,K_5,K_6,K_7,K_8,K_9,K_0,
    K_Q=0x10,K_W,K_E,K_R,K_T,K_Y,K_U,K_I,K_O,K_P,
    K_ENTER = 0x1c,
    K_A=0x1e,K_S,K_D,K_F,K_G,K_H,K_J,K_K,K_L,
    K_Z = 0x2c,K_X,K_C,K_V,K_B,K_N,K_M,
    K_RSHIFT = 0x36,
    K_SPACE = 0x39,K_CTRL=0x1d
};
/*
    20 D     40 F6         60 Ctrl F3    80 Alt 9     A0 Alt Dn Arrow
   01 ESC   21 F     41 F7         61 Ctrl F4    81 Alt 0     A1 Alt PgDn
   02 1     22 G     42 F8         62 Ctrl F5    82 Alt -     A2 Alt Ins
   03 2     23 H     43 F9         63 Ctrl F6    82 Alt =     A3 Alt Del
   04 3     24 J     44 F10        64 Ctrl F7    84 Ctrl PgUp A4 Alt / (num)
   05 4     25 K     45 Num Lk     65 Ctrl F8    85 F11       A5 Alt Tab
   06 5     26 L     46 Scrl       66 Ctrl F9    86 F12       A6 Alt Enter
                        Lk                                       (num)
   07 6     27 ; :   47 Home       67 Ctrl F10   87 SH F11
   08 7     28 ' "   48 Up Arrow   68 Alt F1     88 SH F12
   09 8     29 ` ~   49 Pg Up      69 Alt F2     89 Ctrl F11
   0A 9     2A L SH  4A - (num)    6A Alt F3     8A Ctrl F12
   0B 0     2B \ |   4B 4 Left     6B Alt F4     8B Alt F11
                        Arrow
   0C - _   2C Z     4C 5 (num)    6C Alt F5     8C Alt F12
   0D = +   2D X     4D 6 Rt Arrow 6D Alt F6     8C Ctrl Up
                                                    Arrow
   0E BKSP  2E C     4E + (num)    6E Alt F7     8E Ctrl -
                                                    (num)
   0F Tab   2F V     4F 1 End      6F Alt F8     8F Ctrl 5
                                                    (num)
   10 Q     30 B     50 2 Dn Arrow 70 Alt F9     90 Ctrl +
                                                    (num)
   11 W     31 N     51 3 Pg Dn    71 Alt F10    91 Ctrl Dn
                                                    Arrow
   12 E     32 M     52 0 Ins      72 Ctrl PtScr 92 Ctrl Ins
   13 R     33 , <   53 Del .      73 Ctrl L     93 Ctrl Del
                                      Arrow
   14 T     34 . >   54 SH F1      74 Ctrl R     94 Ctrl Tab
                                      Arrow
   15 Y     35 / ?   55 SH F2      75 Ctrl End   95 Ctrl /
                                                    (num)
   16 U     36 R SH  56 SH F3      76 Ctrl PgDn  96 Ctrl *
                                                    (num)
   17 I     37 PtScr 57 SH F4      77 Ctrl Home  97 Alt Home
   18 O     38 Alt   58 SH F5      78 Alt 1      98 Alt Up
                                                    Arrow
   19 P     39 Spc   59 SH F6      79 Alt 2      99 Alt PgUp
   1A [ {   3A CpsLk 5A SH F7      7A Alt 3      9A
   1B ] }   3B F1    5B SH F8      7B Alt 4      9B Alt Left
                                                    Arrow
   1C Enter 3C F2    5C SH F9      7C Alt 5      9C
   1D Ctrl  3D F3    5D SH F10     7D Alt 6      9D Alt Rt
                                                    Arrow
   1E A     3E F4    5E Ctrl F1    7E Alt 7      9E
   1F S     3F F5    5F Ctrl F2    7F Alt 8      9F Alt End
*/

bool mouse_move(float x, float y)
{
    INPUT input;
    input.type = INPUT_MOUSE;
    input.mi.mouseData = 0;
    input.mi.time = 0;
    input.mi.dx = x;//x being coord in pixels
    input.mi.dy = y;//y being coord in pixels
    input.mi.dwFlags = MOUSEEVENTF_MOVE;
    SendInput(1, &input, sizeof(input));
    return true;
}
int MouseLClick(bool press)
{
    INPUT ip;
    ip.type = INPUT_MOUSE;
    ip.mi.dwFlags = (press?MOUSEEVENTF_LEFTDOWN:MOUSEEVENTF_LEFTUP);
    ip.mi.time = 0;
    ip.mi.dwExtraInfo = 0;
    SendInput(1,&ip,sizeof(INPUT));
}

int MouseRClick(bool press)
{
    INPUT ip;
    ip.type = INPUT_MOUSE;
    ip.mi.dwFlags = (press?MOUSEEVENTF_RIGHTDOWN:MOUSEEVENTF_RIGHTUP);
    ip.mi.time = 0;
    ip.mi.dwExtraInfo = 0;
    SendInput(1,&ip,sizeof(INPUT));
}

int MouseMClick(bool press)
{
    INPUT ip;
    ip.type = INPUT_MOUSE;
    ip.mi.dwFlags = (press?MOUSEEVENTF_MIDDLEDOWN:MOUSEEVENTF_MIDDLEUP);
    ip.mi.time = 0;
    ip.mi.dwExtraInfo = 0;
    SendInput(1,&ip,sizeof(INPUT));
}

int MouseWClick(float x, float y)
{
    INPUT ip;
    ip.type = INPUT_MOUSE;
    ip.mi.dwFlags = MOUSEEVENTF_WHEEL;
    ip.mi.dx = x;
    ip.mi.dy = y;
    ip.mi.mouseData = -y*120;
    ip.mi.time = 0;
    SendInput(1,&ip,sizeof(INPUT));
}

int KeyTap(uint16_t keycode)
{
    INPUT ip;
    // Set up a generic keyboard event.
    ip.type = INPUT_KEYBOARD;
    ip.ki.wScan = keycode; // hardware scan code for key
    ip.ki.time = 0;
    ip.ki.dwExtraInfo = 0;
    ip.ki.wVk = 0; // virtual-key code for the "a" key
    ip.ki.dwFlags = 0|KEYEVENTF_SCANCODE;// 0 for key press
    SendInput(1, &ip, sizeof(INPUT));
    ip.ki.dwFlags = KEYEVENTF_KEYUP|KEYEVENTF_SCANCODE; // KEYEVENTF_KEYUP for key release
    SendInput(1, &ip, sizeof(INPUT));
    return 0;
}
int Key(uint16_t keycode,bool press=true)
{
    INPUT ip;
    // Set up a generic keyboard event.
    ip.type = INPUT_KEYBOARD;
    ip.ki.wScan = keycode; // hardware scan code for key
    ip.ki.time = 0;
    ip.ki.dwExtraInfo = 0;
    ip.ki.wVk = 0; // virtual-key code for the "a" key
    ip.ki.dwFlags = (press?0:KEYEVENTF_KEYUP)|KEYEVENTF_SCANCODE; // 0 for key press
    SendInput(1, &ip, sizeof(INPUT));
    return 0;
}


glm::vec2 UpdateMouse(const glm::vec2 pos)
{
    glm::ivec2 ipos;GetCursorPos((POINT*)&ipos);
    glm::vec2 p = glm::vec2((float)ipos.x,(float)ipos.y) + glm::fract(pos);
    return p;
}
int main( int argc, char * argv[] )
{
    float prev[4] {0.0f,0.0f,0.0f,0.0f};
    SDL_InitSubSystem(SDL_INIT_EVENTS|SDL_INIT_GAMECONTROLLER);
    printf("initialized\n");
    SDL_Event e;
    bool on[4] = {0};
    while(true)
    {
        while( SDL_PollEvent(&e) )
        {
            switch(e.type)
            {
                    case SDL_CONTROLLERDEVICEREMOVED:
                        Controls.erase(Controls.begin()+e.cdevice.which);
                        break;
                    case SDL_CONTROLLERDEVICEREMAPPED:
                        SDL_Log("controller device remapped!");
                        break;
                    case SDL_CONTROLLERBUTTONDOWN:
                        Controls[e.cdevice.which].HandleButtons(e.cbutton);
                        break;
                    case SDL_CONTROLLERBUTTONUP:
                        Controls[e.cdevice.which].HandleButtons(e.cbutton);
                        break;
                    case SDL_CONTROLLERAXISMOTION:
                        Controls[e.cdevice.which].HandleAxis(e.caxis);
                        break;
                    case SDL_CONTROLLERDEVICEADDED:
                        {
                        int nc;
                        nc = SDL_NumJoysticks();
                        for(int i=0;i<nc;i++)
                        {
                            if(SDL_IsGameController(i)){
                                if( i>=(int)Controls.size())Controls.push_back(ControllerHandler(i));
                            }
                        }
                        }
                        printf("controller detected\n");
                    break;
                default:break;
            }
        }

        for(auto &c: Controls)
        {
            if(c.RAXI_POS.x != 0.0f && c.RAXI_POS.y != 0.0f)
            {
                if((int)c.RAXI_POS.x!=0 || (int)c.RAXI_POS.y!=0)
                    mouse_move(c.RAXI_POS.x*2.0,c.RAXI_POS.y*1.5);
            }

            if((int)c.R2 != 0){ MouseWClick(0.0,(int)c.R2);c.R2=0.0f;}
            if((int)c.L2 != 0){ MouseWClick(0.0,-(int)c.L2);c.L2=0.0f;}

            if( uint8_t state = c.get_button(BUTTONS::A) ) Key(K_SPACE,(bool)(state-1));
            if( uint8_t state = c.get_button(BUTTONS::B) ) Key(K_E,(bool)(state-1));
            if( uint8_t state = c.get_button(BUTTONS::X) ) Key(K_Q,(bool)(state-1));
            if( uint8_t state = c.get_button(BUTTONS::Y) ) Key(K_C,(bool)(state-1));

            if( uint8_t state = c.get_button(BUTTONS::DPAD_UP) ) Key(K_R,(bool)(state-1));
            if( uint8_t state = c.get_button(BUTTONS::DPAD_DOWN) ) Key(K_F,(bool)(state-1));
            if( uint8_t state = c.get_button(BUTTONS::DPAD_LEFT) ) Key(K_Z,(bool)(state-1));
            if( uint8_t state = c.get_button(BUTTONS::DPAD_RIGHT) ) Key(K_B,(bool)(state-1));
            if( uint8_t state = c.get_button(BUTTONS::START) ) Key(K_ESC,(bool)(state-1));

            //w s
            if( (int)c.LAXI_POS.y<0 && !on[0] ){ Key(K_W,true); on[0]=true; }
            else if( (int)c.LAXI_POS.y>0 && !on[0] ){ Key(K_S,true); on[0]=true; }
            else if( (int)c.LAXI_POS.y==0 && on[0] ){ Key(K_W,false);Key(K_S,false); on[0]=false;  }

            //a d
            if( (int)c.LAXI_POS.x<0 && !on[1] ){ Key(K_A,true); on[1]=true; }
            else if( (int)c.LAXI_POS.x>0 && !on[1] ){ Key(K_D,true); on[1]=true; }
            else if( (int)c.LAXI_POS.x==0 && on[1] ){ Key(K_A,false);Key(K_D,false); on[1]=false; }


            if( uint8_t state = c.get_button(BUTTONS::RSHOULDER) ) MouseLClick(state-1);
            if( uint8_t state = c.get_button(BUTTONS::LSHOULDER) ) MouseRClick(state-1);
            if( uint8_t state = c.get_button(BUTTONS::RSTICK) ) MouseMClick(state-1);


        }
        SDL_PumpEvents();
        SDL_Delay(3);
    }
    SDL_QuitSubSystem(SDL_INIT_EVENTS|SDL_INIT_GAMECONTROLLER);
    return 1;
}
