#include <windows.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h> 

#define MAX_WORDS 200
const char *lyrics[] = {
    "At sandali lang 'wag ka munang magsalita",
    "'Di ko hahayaan lahat ito ay mawala",
    "At sandali lang 'wag ka munang magsalita",
    "Ba't ko hahayaan pati ikaw ay mawala",
    "Nagtatanong sayo",
    "Kung pwede pa ba tayo"
};

char *words[MAX_WORDS];
int word_delays[MAX_WORDS];
int total_words = 0;
int current_word= 0;
UINT_PTR timer_id = 1;

void split_words() {
    for (int i = 0; i < sizeof(lyrics)/sizeof(lyrics[0]); i++) {
        char buffer[256];
        strcpy(buffer, lyrics[i]);
        char *token = strtok(buffer, " ");
        while (token != NULL) {
            words[total_words] = _strdup(token);
            switch (total_words) {
                case 0:  word_delays[total_words] = 200; break;   // At 
                case 1:  word_delays[total_words] = 400; break;   // sandali 
                case 2:  word_delays[total_words] = 500; break;   // lang 
                case 3:  word_delays[total_words] = 2900; break;  // 'wag 
                case 4:  word_delays[total_words] = 200; break;   // ka 
                case 5:  word_delays[total_words] = 300; break;   // munang 
                case 6:  word_delays[total_words] = 300; break;  // magsalita 

                // after 1st line

                case 8:  word_delays[total_words] = 250; break;   // 'Di
                case 9:  word_delays[total_words] = 400; break;   // ko
                case 10: word_delays[total_words] = 450; break;  // hahayaan
                case 11: word_delays[total_words] = 3000; break;   // lahat
                case 12: word_delays[total_words] = 200; break;   // ito
                case 13: word_delays[total_words] = 1100; break;  // ay
                case 14: word_delays[total_words] = 300; break;  // mawala 

                 // after 2nd line

                case 16: word_delays[total_words] = 300; break;   // At 
                case 17: word_delays[total_words] = 200; break;   // sandali 
                case 18: word_delays[total_words] = 800; break;   // lang 
                case 19: word_delays[total_words] = 3000; break;  // 'wag 
                case 20: word_delays[total_words] = 200; break;   // ka 
                case 21: word_delays[total_words] = 600; break;  // munang 
                case 22: word_delays[total_words] = 1200; break;  // magsalita 

                // after 3rd line

                case 24: word_delays[total_words] = 300; break;   // Ba't
                case 25: word_delays[total_words] = 300; break;   // ko
                case 26: word_delays[total_words] = 600; break;   // hahayaan
                case 27: word_delays[total_words] = 2800; break;  // pati
                case 28: word_delays[total_words] = 300; break;   // ikaw
                case 29: word_delays[total_words] = 400; break;  // ay
                case 30: word_delays[total_words] = 1500; break;   // mawala 

                // after 4th line

                case 32: word_delays[total_words] = 600; break;   // Nagtatanong
                case 33: word_delays[total_words] = 1000; break;  // sayo

                // after 5th line

                case 35: word_delays[total_words] = 2000; break;  // Kung
                case 36: word_delays[total_words] = 400; break;   // pwede
                case 37: word_delays[total_words] = 300; break;   // pa
                case 38: word_delays[total_words] = 300; break;   // ba
                case 39: word_delays[total_words] = 600; break;   // tayo

                default: word_delays[total_words] = 300; break;   // fallback
            }
            total_words++;
            token = strtok(NULL, " ");
        }
 
        words[total_words] = _strdup("\n"); 
        switch (i) {
            case 0: word_delays[total_words] = 1200; break; // after line 1
            case 1: word_delays[total_words] = 1200;  break; // after line 2
            case 2: word_delays[total_words] = 500; break; // after line 3
            case 3: word_delays[total_words] = 800; break; // after line 4
            case 4: word_delays[total_words] = 800; break; // after line 5
            default: word_delays[total_words] = 800; break;
        }
        total_words++; 
    }
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    static HFONT font;

    switch (uMsg) {
        case WM_CREATE:
            font = CreateFont(30, 0, 0, 0, FW_SEMIBOLD, FALSE, FALSE, FALSE,
                              ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
                              DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Arial");
            SetTimer(hwnd, timer_id, word_delays[0], NULL);
            return 0;

        case WM_TIMER:
            if (current_word < total_words) {

                InvalidateRect(hwnd, NULL, TRUE);
                current_word++;

                if (current_word < total_words) {
                    KillTimer(hwnd, timer_id); 
                    SetTimer(hwnd, timer_id, word_delays[current_word], NULL);
                } else {
                    KillTimer(hwnd, timer_id);
                }
            }
            return 0;

        case WM_PAINT: {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);

            HBRUSH hBrush = CreateSolidBrush(RGB(255, 60, 0)); // set background color 
            FillRect(hdc, &ps.rcPaint, hBrush);
            DeleteObject(hBrush);

            SetBkMode(hdc, TRANSPARENT); 
            SetTextColor(hdc, RGB(255, 255, 255)); 
            SelectObject(hdc, font);

            int x = 30, y = 30;
            for (int i = 0; i < current_word; i++) {
                if (strcmp(words[i], "\n") == 0) {
                    y += 30; 
                    x = 30;  
                } else {
                    // Draw the word
                    TextOut(hdc, x, y, words[i], strlen(words[i]));
                    SIZE sz;
                    GetTextExtentPoint32(hdc, words[i], strlen(words[i]), &sz);
                    x += sz.cx + 10; 
                }
            }

            EndPaint(hwnd, &ps);
            return 0;
        }

        case WM_DESTROY:
            for (int i = 0; i < total_words; i++) {
                if (words[i])
                    free(words[i]);
            }
            PostQuitMessage(0);
            return 0;
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine, int nCmdShow) {
    split_words();

    const char CLASS_NAME[] = "LyricsWindow";

    WNDCLASS wc = { };
    wc.lpfnWndProc = WindowProc;     
    wc.hInstance = hInstance;        
    wc.lpszClassName = CLASS_NAME;   

    RegisterClass(&wc); 

 
    HWND hwnd = CreateWindowEx(
        0,                            
        CLASS_NAME,                   
        "Tensionado - Soapdish",  
        WS_OVERLAPPEDWINDOW,          
        CW_USEDEFAULT, CW_USEDEFAULT, 
        800, 400,                    
        NULL,                        
        NULL,                  
        hInstance,                   
        NULL                      
    );

    if (hwnd == NULL) {
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);   // Display the window
    UpdateWindow(hwnd);          


    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg); 
        DispatchMessage(&msg); 
    }

    return 0; 
}