#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

 
#define FRAME_WIDTH  80
#define FRAME_HEIGHT 30
#define ANIMATION_DELAY 200000   

 
static const char * frame0[FRAME_HEIGHT] = {
"                                                                                ",
"                          ****RICKROLL INCOMING****                            ",
"                                                                                ",
"                              @@@@@@@@@@@@                                     ",
"                            @@##############@@                                 ",
"                           @##################@                                ",
"                          @##......##......##@                                ",
"                          @##......##......##@                                ",
"                          @####################                                ",
"                           @########^^########@                               ",
"                            @@######____######@@                              ",
"                              @@@@@@@@@@@@@@@@                                ",
"                                                                                ",
"               NNNN    N  EEEEE  V   V  EEEEE  RRRR                           ",
"               N   N   N  E      V   V  E      R   R                          ",
"               N    N  N  EEEE   V   V  EEEE   RRRR                           ",
"               N     N N  E       V V   E      R  R                           ",
"               N      NN  EEEEE    V    EEEEE  R   R                          ",
"                                                                                ",
"               GGGGG  OOOO  N   N  N   N  AAAA                                ",
"               G      O    O NN  N  NN  N A    A                              ",
"               G GGG  O    O N N N  N N N AAAAAA                              ",
"               G   G  O    O N  NN  N  NN A    A                              ",
"               GGGGG  OOOO  N   N  N   N A    A                               ",
"                                                                                ",
"                            GIVE YOU UP!                                       ",
"                                                                                ",
"                        [Press Ctrl+C to stop]                                ",
"                                                                                ",
"                                                                                "
};

// Frame 1: Dance move 1
static const char * frame1[FRAME_HEIGHT] = {
"                                                                                ",
"                      ♪♫ NEVER GONNA LET YOU DOWN ♫♪                          ",
"                                                                                ",
"                         /    @@@@@@@@@@@@    \\                               ",
"                       /    @@##############@@   \\                            ",
"                      |    @##################@   |                           ",
"                      |    @##......##......##@   |                           ",
"                      |    @##......##......##@   |                           ",
"                       \\   @####################  /                           ",
"                        \\   @########^^########@ /                            ",
"                         \\  @@######____######@@/                             ",
"                           @@@@@@@@@@@@@@@@@@@@                               ",
"                          /                    \\                              ",
"                         /  WWWW    W  EEEE     \\                             ",
"                        |   W   W   W  E         |                            ",
"                        |   W   W   W  EEE       |                            ",
"                        |   W W W   W  E         |                            ",
"                         \\  WW WW   W  EEEE     /                             ",
"                          \\                    /                              ",
"                           RRRRR  U   U  N   N                                ",
"                           R   R  U   U  NN  N                                ",
"                           RRRR   U   U  N N N                                ",
"                           R  R   U   U  N  NN                                ",
"                           R   R  UUUU   N   N                                ",
"                                                                                ",
"                          AROUND AND DESERT YOU!                              ",
"                                                                                ",
"                             ♪♫♪♫♪♫♪♫♪♫                                       ",
"                                                                                ",
"                                                                                "
};

// Frame 2: Dance move 2
static const char * frame2[FRAME_HEIGHT] = {
"                                                                                ",
"                    ♪♫ NEVER GONNA MAKE YOU CRY ♫♪                            ",
"                                                                                ",
"                     \\      @@@@@@@@@@@@      /                               ",
"                      \\   @@##############@@  /                               ",
"                       \\ @##################@ /                               ",
"                        |@##......##......##@|                               ",
"                        |@##......##......##@|                               ",
"                        |@####################|                               ",
"                        |@########^^########@|                               ",
"                        |@@######____######@@|                               ",
"                         @@@@@@@@@@@@@@@@@@@@                                ",
"                              |        |                                      ",
"                           N   N  EEEE  V   V                                ",
"                          /N   N  E     V   V\\                               ",
"                         | NN  N  EEE   V   V |                              ",
"                         | N N N  E      V V  |                              ",
"                          \\N  NN  EEEE    V  /                               ",
"                              |        |                                      ",
"                           SSSSS  AAAA  Y   Y                                ",
"                           S     A    A  Y Y                                  ",
"                           SSSS  AAAAAA   Y                                   ",
"                               S A    A   Y                                   ",
"                           SSSSS A    A   Y                                   ",
"                                                                                ",
"                            GOODBYE!                                           ",
"                                                                                ",
"                       🎵 YOU'VE BEEN RICKROLLED! 🎵                          ",
"                                                                                ",
"                                                                                "
};

// Frame 3: Victory pose
static const char * frame3[FRAME_HEIGHT] = {
"********************************************************************************",
"*                          CONGRATULATIONS!                                   *",
"*                      YOU'VE BEEN RICKROLLED!                               *",
"********************************************************************************",
"                                                                                ",
"                    \\o/    @@@@@@@@@@@@    \\o/                               ",
"                     |   @@##############@@   |                               ",
"                    / \\ @##################@ / \\                             ",
"                        @##......##......##@                                  ",
"                        @##......##......##@                                  ",
"                        @####################                                  ",
"                        @########^^########@                                  ",
"                        @@######____######@@                                  ",
"                          @@@@@@@@@@@@@@@@                                    ",
"                                                                                ",
"            ♪♫ WE'RE NO STRANGERS TO LOVE... ♫♪                               ",
"                                                                                ",
"               RRRRR  IIIII  CCCCC  K   K                                     ",
"               R   R    I    C      K  K                                      ",
"               RRRR     I    C      KKK                                       ",
"               R  R     I    C      K  K                                      ",
"               R   R  IIIII  CCCCC  K   K                                     ",
"                                                                                ",
"               AAAA   SSSSS  TTTTT  L      EEEEE  Y   Y                      ",
"              A    A  S        T    L      E       Y Y                       ",
"              AAAAAA  SSSS     T    L      EEE      Y                        ",
"              A    A      S    T    L      E        Y                        ",
"              A    A  SSSSS    T    LLLLL  EEEEE    Y                        ",
"                                                                                ",
"********************************************************************************",
"*                    Thanks for falling for the rickroll!                    *",
"********************************************************************************"
};

// Array of frame pointers
static const char ** frames[] = {
    frame0,
    frame1,
    frame2,
    frame3,
    frame2,  // Go back for more dance moves
    frame1,
    frame0,
    frame3,  // Final victory
    NULL
};

void clear_screen() {
    printf("\033[2J\033[H");   
}

void print_frame_with_colors(const char ** frame) {
    for (int i = 0; i < FRAME_HEIGHT; i++) {
        if (frame[i] == NULL) {
            printf("\n");
            continue;
        }
        
        int row_length = strlen(frame[i]);
        int max_chars = row_length < FRAME_WIDTH ? row_length : FRAME_WIDTH;
        
        for (int j = 0; j < max_chars; j++) {
            char c = frame[i][j];
            switch(c) {
                case '@': 
                    printf("\033[93m%c\033[0m", c);  
                    break;
                case '#': 
                    printf("\033[91m%c\033[0m", c);   
                    break;
                case '.': 
                    printf("\033[96m%c\033[0m", c);  
                    break;
                case '^': 
                    printf("\033[95m%c\033[0m", c);   
                    break;
                case '_': 
                    printf("\033[97m%c\033[0m", c);   
                    break;
                case '*': 
                    printf("\033[41m\033[93m%c\033[0m", c);  
                    break;
                case 'R': case 'I': case 'C': case 'K':
                case 'A': case 'S': case 'T': case 'L': case 'E': case 'Y':
                    printf("\033[1m\033[91m%c\033[0m", c);  
                    break;
                case 'N': case 'V': case 'G': case 'O': case 'U': case 'P':
                case 'W': case 'D': case 'M': case 'Y':
                    printf("\033[1m\033[94m%c\033[0m", c);  
                    break;
                case '/': case '\\': case '|': case '-':
                    printf("\033[92m%c\033[0m", c);  
                    break;
                case '♪': case '♫': case '':
                    printf("\033[95m%c\033[0m", c);  
                    break;
                case 'o':
                    printf("\033[93m%c\033[0m", c);   
                    break;
                default: 
                    printf("%c", c);
                    break;
            }
        }
        printf("\n");
    }
}

// Special intro sequence
void rickroll_intro() {
    printf("\033[2J\033[H");
    
    // Flash red background
    printf("\033[41m");
    printf("\n\n\n\n\n\n\n");
    printf("                                    WARNING!\n");
    printf("                              RICKROLL DETECTED!\n");
    printf("                               PREPARE YOURSELF!\n");
    printf("\n\n\n\n\n\n\n");
    printf("\033[0m");
    
    usleep(1000000);  // 1 second
    
    printf("\033[2J\033[H");
    printf("\033[93m");  // Yellow text
    printf("\n\n\n\n\n\n\n");
    printf("                               3...\n");
    printf("\n\n\n\n\n\n\n");
    printf("\033[0m");
    usleep(800000);
    
    printf("\033[2J\033[H");
    printf("\033[93m");
    printf("\n\n\n\n\n\n\n");
    printf("                               2...\n");
    printf("\n\n\n\n\n\n\n");
    printf("\033[0m");
    usleep(800000);
    
    printf("\033[2J\033[H");
    printf("\033[93m");
    printf("\n\n\n\n\n\n\n");
    printf("                               1...\n");
    printf("\n\n\n\n\n\n\n");
    printf("\033[0m");
    usleep(800000);
    
    printf("\033[2J\033[H");
    printf("\033[1m\033[91m");  // Bold red
    printf("\n\n\n\n\n\n\n");
    printf("                         YOU'VE BEEN RICKROLLED!\n");
    printf("\n\n\n\n\n\n\n");
    printf("\033[0m");
    usleep(1500000);  // 1.5 seconds
}

int main() {
    int frame_count = 0;
    
    
    while (frames[frame_count] != NULL && frame_count < 20) {
        frame_count++;
    }
    
    if (frame_count == 0) {
        printf("Error: No frames found!\n");
        return 1;
    }
    
     
    rickroll_intro();
    
    printf("Rick Astley Animation! You know the rules, and so do I...\n");
    printf("Press Ctrl+C to stop (but you know you won't!)\n");
    sleep(2);
    
    int current_frame = 0;
    int cycles = 0;
    
    while (cycles < 3) {   
        clear_screen();
        
        if (current_frame >= frame_count || frames[current_frame] == NULL) {
            current_frame = 0;
            cycles++;
        }
        
        print_frame_with_colors(frames[current_frame]);
        
        
        printf("\n");
        if (current_frame % 4 == 0) {
            printf("\033[1m\033[96m                    ♪♫ We're no strangers to love... ♫♪\033[0m\n");
        } else if (current_frame % 4 == 1) {
            printf("\033[1m\033[95m                    ♪♫ You know the rules and so do I... ♫♪\033[0m\n");
        } else if (current_frame % 4 == 2) {
            printf("\033[1m\033[94m                    ♪♫ A full commitment's what I'm thinking of... ♫♪\033[0m\n");
        } else {
            printf("\033[1m\033[92m                    ♪♫ You wouldn't get this from any other guy! ♫♪\033[0m\n");
        }
        
        current_frame = (current_frame + 1) % frame_count;
        usleep(ANIMATION_DELAY);
    }
    
     
    clear_screen();
    printf("\033[1m\033[91m");
    printf("\n\n\n\n\n\n");
    printf("    ████████╗██╗  ██╗ █████╗ ███╗   ██╗██╗  ██╗███████╗\n");
    printf("    ╚══██╔══╝██║  ██║██╔══██╗████╗  ██║██║ ██╔╝██╔════╝\n");
    printf("       ██║   ███████║███████║██╔██╗ ██║█████╔╝ ███████╗\n");
    printf("       ██║   ██╔══██║██╔══██║██║╚██╗██║██╔═██╗ ╚════██║\n");
    printf("       ██║   ██║  ██║██║  ██║██║ ╚████║██║  ██╗███████║\n");
    printf("       ╚═╝   ╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═══╝╚═╝  ╚═╝╚══════╝\n");
    printf("\n");
    printf("           ███████╗ ██████╗ ██████╗     ██████╗ ███████╗██╗███╗   ██╗ ██████╗ \n");
    printf("           ██╔════╝██╔═══██╗██╔══██╗    ██╔══██╗██╔════╝██║████╗  ██║██╔════╝ \n");
    printf("           █████╗  ██║   ██║██████╔╝    ██████╔╝█████╗  ██║██╔██╗ ██║██║  ███╗\n");
    printf("           ██╔══╝  ██║   ██║██╔══██╗    ██╔══██╗██╔══╝  ██║██║╚██╗██║██║   ██║\n");
    printf("           ██║     ╚██████╔╝██║  ██║    ██████╔╝███████╗██║██║ ╚████║╚██████╔╝\n");
    printf("           ╚═╝      ╚═════╝ ╚═╝  ╚═╝    ╚═════╝ ╚══════╝╚═╝╚═╝  ╚═══╝ ╚═════╝ \n");
    printf("\n");
    printf("                    ██████╗ ██╗ ██████╗██╗  ██╗██████╗  ██████╗ ██╗     ██╗     ███████╗██████╗ ██╗\n");
    printf("                    ██╔══██╗██║██╔════╝██║ ██╔╝██╔══██╗██╔═══██╗██║     ██║     ██╔════╝██╔══██╗██║\n");
    printf("                    ██████╔╝██║██║     █████╔╝ ██████╔╝██║   ██║██║     ██║     █████╗  ██║  ██║██║\n");
    printf("                    ██╔══██╗██║██║     ██╔═██╗ ██╔══██╗██║   ██║██║     ██║     ██╔══╝  ██║  ██║╚═╝\n");
    printf("                    ██║  ██║██║╚██████╗██║  ██╗██║  ██║╚██████╔╝███████╗███████╗███████╗██████╔╝██╗\n");
    printf("                    ╚═╝  ╚═╝╚═╝ ╚═════╝╚═╝  ╚═╝╚═╝  ╚═╝ ╚═════╝ ╚══════╝╚══════╝╚══════╝╚═════╝ ╚═╝\n");
    printf("\033[0m\n\n");
    
    return 0;
}
