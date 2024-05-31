#include <windows.h>

HWND hInput;

double hesapla(const char* expression);

// Pencere isleme fonksiyonu
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    	
        case WM_CREATE: // Pencere icindeki ogelerin olusturulmasi icin
        
            // Islemlerin gozuktugu kutuyu olusturmak icin
            hInput = CreateWindowEx(0, TEXT("EDIT"), 
				NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_RIGHT,
                10, 10, 200, 30, hWnd, NULL, NULL, NULL);


            // Sayi butonlarini olusturmak icin
            CreateWindowEx(0, TEXT("BUTTON"), TEXT("0"), 
				WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                10 + (0%3) * 50, 50 + (0/3) * 50, 50, 50, // Butonun boyutu
				hWnd, (HMENU)0  /* Butonun id si*/, NULL, NULL);
                
            CreateWindowEx(0, TEXT("BUTTON"), TEXT("1"), 
				WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                10 + (1%3) * 50, 50 + (1/3) * 50, 50, 50, 
				hWnd, (HMENU)1, NULL, NULL);
                
            CreateWindowEx(0, TEXT("BUTTON"), TEXT("2"), 
				WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                10 + (2%3) * 50, 50 + (2/3) * 50, 50, 50, 
				hWnd, (HMENU)2, NULL, NULL);
                
            CreateWindowEx(0, TEXT("BUTTON"), TEXT("3"), 
				WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                10 + (3%3) * 50, 50 + (3/3) * 50, 50, 50, 
				hWnd, (HMENU)3, NULL, NULL);
                
            CreateWindowEx(0, TEXT("BUTTON"), TEXT("4"), 
				WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                10 + (4%3) * 50, 50 + (4/3) * 50, 50, 50, 
				hWnd, (HMENU)4, NULL, NULL);
                
            CreateWindowEx(0, TEXT("BUTTON"), TEXT("5"), 
				WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                10 + (5%3) * 50, 50 + (5/3) * 50, 50, 50, 
				hWnd, (HMENU)5, NULL, NULL);
                
            CreateWindowEx(0, TEXT("BUTTON"), TEXT("6"), 
				WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                10 + (6%3) * 50, 50 + (6/3) * 50, 50, 50, 
				hWnd, (HMENU)6, NULL, NULL);
                    
            CreateWindowEx(0, TEXT("BUTTON"), TEXT("7"), 
				WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                10 + (7%3) * 50, 50 + (7/3) * 50, 50, 50, 
				hWnd, (HMENU)7, NULL, NULL);

			CreateWindowEx(0, TEXT("BUTTON"), TEXT("8"), 
				WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                10 + (8%3) * 50, 50 + (8/3) * 50, 50, 50, 
				hWnd, (HMENU)8, NULL, NULL);
                    
            CreateWindowEx(0, TEXT("BUTTON"), TEXT("9"), 
				WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                10 + (9%3) * 50, 50 + (9/3) * 50, 50, 50, 
				hWnd, (HMENU)9, NULL, NULL);
                    
                    
			// Islem butonlarini olusturmak icin
            CreateWindowEx(0, TEXT("BUTTON"), TEXT("+"), 
				WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                10 + 3 * 50, 50, 50, 50, 
				hWnd, (HMENU)10, NULL, NULL);

            CreateWindowEx(0, TEXT("BUTTON"), TEXT("-"), 
				WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                10 + 3 * 50, 100, 50, 50, 
				hWnd, (HMENU)11, NULL, NULL);
                    
            CreateWindowEx(0, TEXT("BUTTON"), TEXT("*"), 
				WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                10 + 3 * 50, 150, 50, 50, 
				hWnd, (HMENU)12, NULL, NULL);
                    
            CreateWindowEx(0, TEXT("BUTTON"), TEXT("/"), 
				WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                10 + 3 * 50, 200, 50, 50, 
				hWnd, (HMENU)13, NULL, NULL);
			
				
            // Tum yazilanlari silmek icin olusturulan buton
            CreateWindowEx(0, TEXT("BUTTON"), TEXT("Clear"), 
				WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            	10 + (10%3) * 50, 50 + (10/3) * 50, 50, 50, 
				hWnd, (HMENU)14, NULL, NULL);
                    
                    
            // Son yazilan bir karakteri silmek icin olusturulan buton
            CreateWindowEx(0, TEXT("BUTTON"), TEXT("C"), 
				WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                10 + (11%3) * 50, 50 + (11/3) * 50, 50, 50, 
				hWnd, (HMENU)15, NULL, NULL);
                    
                    
            // Islemin sonucunu gormek icin olusturulan buton
        	CreateWindowEx(0, TEXT("BUTTON"), TEXT("="), 
				WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                10 + (12%3) * 50, 50 + (12/3) * 50, 200, 45, 
				hWnd, (HMENU)16, NULL, NULL);
            
			break;


        case WM_COMMAND: // Buton tiklama eylemine yanit olarak gerceklestirilecek islemleri belirlemek icin
        
            if (HIWORD(wParam) == BN_CLICKED) {
                int buttonId = LOWORD(wParam);
                
                if (buttonId >= 0 && buttonId <= 9) { // Sayilar icin
                    char szButtonText[2];
                    GetWindowText((HWND)lParam, szButtonText, 2);
                    SendMessage(hInput, EM_REPLACESEL, TRUE, (LPARAM)szButtonText);
                } 
				
				else if (buttonId == 10) { // Toplama islemi icin
                    SendMessage(hInput, EM_REPLACESEL, TRUE, (LPARAM)" + ");
                }
                
                else if (buttonId == 11) { // Cikarma islemi icin
                    SendMessage(hInput, EM_REPLACESEL, TRUE, (LPARAM)" - ");
            	}
            	
                else if (buttonId == 12) { // Carpma islemi icin
                    SendMessage(hInput, EM_REPLACESEL, TRUE, (LPARAM)" * ");
                }
                
                else if (buttonId == 13) { // Bolme islemi icin
                    SendMessage(hInput, EM_REPLACESEL, TRUE, (LPARAM)" / ");
          		}
          		
				else if (buttonId == 14) { // Clear butonuna tiklandiginda tüm yazilanlari silmek icin
                   
                    SetWindowText(hInput, "");
            	}
            	
                else if (buttonId == 15) { // C butonuna tiklandiginda son karakteri silmek icin
                    
                    int len = GetWindowTextLength(hInput);
                    SendMessage(hInput, EM_SETSEL, len - 1, len);
                    SendMessage(hInput, EM_REPLACESEL, TRUE, (LPARAM)"");
                } 
				
				else if (buttonId == 16) { // = butonuna tiklandiginda islemin sonucunu bulmak icin
                    
                    int len = GetWindowTextLength(hInput) + 1;
                    char* expression = (char*)malloc(len);
                    GetWindowText(hInput, expression, len);

                    double result = hesapla(expression); // hesapla fonksiyonuyla islemin sonucu bulunur.
                    char resultStr[256];
                    
                     //virgulden sonrasi 0 ise sonrasini yazdirmamak icin
                    if(result/result!=(int)result/result) sprintf(resultStr, " = %f", result);
                    else sprintf(resultStr, " = %.0f", result);

                    SendMessage(hInput, EM_SETSEL, 0, -1);
                    SendMessage(hInput, EM_REPLACESEL, TRUE, (LPARAM)resultStr);

                    free(expression);
                }
                
            }
            break;

        case WM_DESTROY: // Pencereyi kapatmak icin
            PostQuitMessage(0);
            break;

        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
    }

    return 0;
}


double hesapla(const char* expression) { // Islemin sonucunu bulur.
    int sayi1, sayi2;
    char islem;

    sscanf(expression, "%d %c %d", &sayi1, &islem, &sayi2);

    switch (islem) {
        case '+':
            return sayi1 + sayi2;
        case '-':
        	return sayi1 - sayi2;
        case '*':
        	return sayi1 * sayi2;
        case '/':
        	if(sayi2==0) MessageBox(NULL, "Hata : Sifira bolme hatasi!", "Hata", MB_OK | MB_ICONERROR);
        	else return (double)sayi1 / sayi2;
        default:
            return 0;
    }
}

int main() { // Ana fonksiyon
    
    WNDCLASS wc = { 0 };
    wc.lpfnWndProc = WndProc;
    wc.hInstance = GetModuleHandle(NULL);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 24); // Pencerenin arka plan rengi
    wc.lpszClassName = TEXT("HesapMakinesi");

    
    RegisterClass(&wc);

    // Pencereyi olusturur
    HWND hWnd = CreateWindowEx(0, TEXT("HesapMakinesi"), TEXT("Hesap Makinesi"),
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 250, 350, // Pencerenin boyutu
        NULL, NULL, GetModuleHandle(NULL), NULL);

    
    ShowWindow(hWnd, SW_SHOWNORMAL); // Pencereyi gosterir
    UpdateWindow(hWnd); // gunceller

    // Pencerede yapilan eylemler icin bir dongu 
    MSG msg = { 0 };
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

