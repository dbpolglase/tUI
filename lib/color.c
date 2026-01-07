#include <stdio.h>
#include <ncurses.h>

#include <tBasic.h>
#include <color.h>

static short curs_color(unsigned short fg)
{
    switch (7 & fg) {           /* RGB */
    case 0:                     /* 000 */
        return (COLOR_BLACK);
    case 1:                     /* 001 */
        return (COLOR_BLUE);
    case 2:                     /* 010 */
        return (COLOR_GREEN);
    case 3:                     /* 011 */
        return (COLOR_CYAN);
    case 4:                     /* 100 */
        return (COLOR_RED);
    case 5:                     /* 101 */
        return (COLOR_MAGENTA);
    case 6:                     /* 110 */
        return (COLOR_YELLOW);
    case 7:                     /* 111 */
        return (COLOR_WHITE);
    }
  return 0;
}



static int colornum(unsigned short fg, unsigned short bg)
{
    int B, bbb, ffff;

    B = 1 << 7;
    bbb = (7 & bg) << 4;
    ffff = 7 & fg;

    return (B | bbb | ffff);
}

static int colorfg(int pair)
{
 int fg=0;

  fg = 7 & pair;

  return fg;
}

static int colorbg(int pair)
{
 int bg=0;

  bg = pair & 0x7F;
  bg = bg >> 4;

  return bg;
}

static void init_colorpairs(void)
{
    unsigned short fg, bg;
    int colorpair;

    for (bg = 0; bg <= 7; bg++) {
        for (fg = 0; fg <= 7; fg++) {
            colorpair = colornum(fg, bg);
            init_pair(colorpair, curs_color(fg), curs_color(bg));
        }
    }
}

int COLOR_inicializar(unsigned short useColor)
{

  if (useColor && has_colors() == TRUE)
  {
    start_color();
    init_colorpairs();
  }
  return 0;
}

int COLOR_get(unsigned short bg, unsigned short fg)
{
  if (has_colors() == TRUE)
  {
    return (colornum(fg,bg));
  }
  return 0;
}


int COLOR_getBackground(int colorpair )
{
  if (has_colors() == TRUE)
  {
    return (colorbg(colorpair));
  }
  return 0;
}

int COLOR_getForeground(int colorpair )
{
  if (has_colors() == TRUE)
  {
    return (colorfg(colorpair));
  }
  return 0;
}

int COLOR_Attrb(tChAttr * color,int attributo)
{
  switch (attributo)
  {
    case WA_NORMAL: color->attr = WA_NORMAL;
                    break;
    case WA_STANDOUT: color->attr |= WA_STANDOUT;
                    break;
    case WA_UNDERLINE: color->attr |= WA_UNDERLINE;
                    break;
    case WA_REVERSE: color->attr |= WA_REVERSE;
                    break;
    case WA_BLINK: color->attr |= WA_BLINK;
                    break;
    case WA_DIM: color->attr |= WA_DIM;
                    break;
    case WA_BOLD: color->attr |= WA_BOLD;
                    break;
#if defined(WA_ITALIC)
    case WA_ITALIC: color->attr |= WA_ITALIC;
                    break;
#endif
    case WA_ALTCHARSET: color->attr |= WA_ALTCHARSET;
                    break;
    default:       return -1;
  }
  return 0;
}


