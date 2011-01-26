#ifndef COLOR_HPP
#define COLOR_HPP

#if defined( __WIN32__ ) || defined( _WIN32 )
  #include <windows.h>
#endif

#include <iostream>
#include <string>

class Exception {
  public:

  #if defined( __WIN32__ ) || defined( _WIN32 )

    enum { BLUE, GREEN, RED, YELLOW, MAGENTA, CYAN };
      // empty message resets console colors
    static void msg( std::string msg = "", int c = 3) {
      HANDLE h = GetStdHandle ( STD_OUTPUT_HANDLE );
      WORD wOldColorAttrs;
      CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
        // save current color information
      GetConsoleScreenBufferInfo(h, &csbiInfo);
      wOldColorAttrs = csbiInfo.wAttributes;
        // set parameterized color value
      c == 0 ? SetConsoleTextAttribute( h, FOREGROUND_BLUE | FOREGROUND_INTENSITY ) :
      c == 1 ? SetConsoleTextAttribute( h, FOREGROUND_GREEN | FOREGROUND_INTENSITY ) :
      c == 2 ? SetConsoleTextAttribute( h, FOREGROUND_RED | FOREGROUND_INTENSITY ) :
      c == 4 ? SetConsoleTextAttribute( h, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY ) :
      c == 5 ? SetConsoleTextAttribute( h, FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY ) :
      c == 6 ? SetConsoleTextAttribute( h, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY ) :
      SetConsoleTextAttribute( h, wOldColorAttrs );
      printf( "%s", msg.c_str() );
      SetConsoleTextAttribute( h, wOldColorAttrs );   
    }

  #else

    enum { BLACK, RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, WHITE };
      // fg/bg = B, R, G, Y, B, M, C, W
    static void msg( std::string msg = "", int fg = 7, int bg = 0, int attr = 0) {
      char command[13];
      sprintf( command, "%c[%d;%d;%dm", 0x1B, attr, fg + 30, bg + 40 );
      printf("%s", command);
      printf( "%s", msg.c_str() );
      sprintf( command, "%c[%d;%d;%dm", 0x1B, 0, 7 + 30, 0 + 40 );
      printf("%s", command);
    }

  #endif

};

#endif