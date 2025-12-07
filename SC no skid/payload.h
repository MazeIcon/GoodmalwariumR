DWORD WINAPI GDIShader1(LPVOID lpParam) //credits to fr4ctalz
{
	HDC hdc = GetDC(NULL);
	HDC hdcCopy = CreateCompatibleDC(hdc);
	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);
	BITMAPINFO bmpi = { 0 };
	HBITMAP bmp;

	bmpi.bmiHeader.biSize = sizeof(bmpi);
	bmpi.bmiHeader.biWidth = screenWidth;
	bmpi.bmiHeader.biHeight = screenHeight;
	bmpi.bmiHeader.biPlanes = 1;
	bmpi.bmiHeader.biBitCount = 32;
	bmpi.bmiHeader.biCompression = BI_RGB;


	RGBQUAD* rgbquad = NULL;
	HSL hslcolor;

	bmp = CreateDIBSection(hdc, &bmpi, DIB_RGB_COLORS, (void**)&rgbquad, NULL, 0);
	SelectObject(hdcCopy, bmp);

	INT i = 0;

	while (1)
	{
		hdc = GetDC(NULL);
		StretchBlt(hdcCopy, 0, 0, screenWidth, screenHeight, hdc, 0, 0, screenWidth, screenHeight, SRCCOPY);

		RGBQUAD rgbquadCopy;

		for (int x = 0; x < screenWidth; x++)
		{
			for (int y = 0; y < screenHeight; y++)
			{
				int index = y * screenWidth + x;

				int fx = (int)((i ^ 4) + (i * 4) * pow(x * y, 1.0/3.0));

				rgbquadCopy = rgbquad[index];

				hslcolor = Colors::rgb2hsl(rgbquadCopy);
				hslcolor.h = fmod(fx / 400.f + y / screenHeight * .2f, 1.f);

				rgbquad[index] = Colors::hsl2rgb(hslcolor);
			}
		}

		i++;

		StretchBlt(hdc, 0, 0, screenWidth, screenHeight, hdcCopy, 0, 0, screenWidth, screenHeight, NOTSRCCOPY);
		ReleaseDC(NULL, hdc);
		DeleteDC(hdc);
	}

	return 0;
}
DWORD WINAPI GDIShader2(LPVOID lpParam) { //credits to N17Pro3426
	int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
	RGBQUAD* data = (RGBQUAD*)VirtualAlloc(0, (w * h + w) * sizeof(RGBQUAD), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE); int rgb = MAXDWORD64, v = 0, radius = 17.4f; double angle = 0;
	HDC hdc, hdcMem; HBITMAP hbm;
	for (int i = 0;; i++, i %= 6) {
		//if (!i) for (int c = 0; c < 21; c++)InvalidateRect(0, 0, 0);
		hdc = GetDC(0); hdcMem = CreateCompatibleDC(hdc); hbm = CreateBitmap(w, h, 1, 32, data);
		SelectObject(hdcMem, hbm);
		BitBlt(hdcMem, 0, 0, w, h, hdc, 0, 0, SRCCOPY); GetBitmapBits(hbm, w * h * 4, data);
		for (int i = 0; w * h > i; i++) {
			int x = i % w, y = i / h;
			if (i % h == 0 && rand() % 100 == 0)  v = 1 + rand() % 6;
			rgb ^= (int)data + (x*y);
			((BYTE*)(data + i))[v] += rgb;
		}
		float x = cos(angle) * radius, y = sin(angle) * radius;
		SetBitmapBits(hbm, w * h * 4, data); BitBlt(hdc, 0, 0, w, h, hdcMem, x, y, SRCCOPY);
		DeleteObject(hbm); DeleteObject(hdcMem);
		DeleteObject(hdc);
		//Sleep(39.7);
		angle = fmod(angle + PI / radius, PI * radius);
	}
}
DWORD WINAPI Payload1a_AmazingBall(LPVOID lpParam) {
    int radius = 18;
    int numCircles = 140;
    int cx = 150, cy = 150;
    int dx = 8, dy = 8;
    while (1) {
        HDC hdc = GetDC(0);
        int w = GetSystemMetrics(SM_CXSCREEN);
        int h = GetSystemMetrics(SM_CYSCREEN);

        for (int i = 0; i < numCircles; i++) {
            int spiralRadius = i * 0.85;
            int x = cx + spiralRadius * cos(i * 0.5);
            int y = cy + spiralRadius * sin(i * 0.5);

            HBRUSH brush = CreateSolidBrush(Hue(239));
            SelectObject(hdc, brush);

            Ellipse(hdc, x - radius, y - radius, x + radius, y + radius);

            DeleteObject(brush);
        }

        cx += dx;
        cy += dy;

        if (cx + radius > w || cx - radius < 0) dx = -dx;
        if (cy + radius > h || cy - radius < 0) dy = -dy;

        ReleaseDC(0, hdc);
        Sleep(10);
    }
    return 0;
}
DWORD WINAPI GDIShader3(LPVOID lpParam) {
    int i = 0;
    while (1)
    {
        HDC hdc = GetDC(NULL);
        HDC hcdc = CreateCompatibleDC(hdc);
        int w = GetSystemMetrics(0);
        int h = GetSystemMetrics(1);
        BITMAPINFO bmpi = { 0 };

        bmpi.bmiHeader.biSize = sizeof(bmpi);
        bmpi.bmiHeader.biWidth = w;
        bmpi.bmiHeader.biHeight = h;
        bmpi.bmiHeader.biPlanes = 1;
        bmpi.bmiHeader.biBitCount = 32;
        bmpi.bmiHeader.biCompression = BI_RGB;

        RGBQUAD* rgbquad = NULL;
        HSL hslcolor;

        HBITMAP hBitmap = CreateDIBSection(hdc, &bmpi, DIB_RGB_COLORS, (void**)&rgbquad, NULL, 0);
        SelectObject(hcdc, hBitmap);
        StretchBlt(hcdc, 0, 0, w, h, hdc, 0, 0, w, h, SRCCOPY);

        RGBQUAD rgbquadCopy;

        for (int x = 0; x < w; x++)
        {
            for (int y = 0; y < h; y++)
            {
                int index = y ^ x * h;

                int fx = (int)((i ^ 4) + ((4 - i)) + (i * 9) + ((i * 3))) * pow(y, 1.0/3.0);

                rgbquad[index].rgbRed *= fx;
                rgbquad[index].rgbGreen *= fx;
                rgbquad[index].rgbBlue *= fx;
            }
        }

        i++;
        StretchBlt(hdc, 0, 0, w, h, hcdc, 0, 0, w, h, SRCCOPY);
        ReleaseDC(NULL, hdc);
        ReleaseDC(NULL, hcdc);
        DeleteObject(hBitmap);
        DeleteDC(hcdc);
        DeleteDC(hdc);
    }
    return 0;
}
DWORD WINAPI GDIShader4(LPVOID lpParam) //opaque HSL base by fr4ctalz
{
	HDC hdc = GetDC(NULL);
	HDC hdcCopy = CreateCompatibleDC(hdc);
	int w = GetSystemMetrics(0);
	int h = GetSystemMetrics(1);
	BITMAPINFO bmpi = { 0 };
	HBITMAP bmp;
	bmpi.bmiHeader.biSize = sizeof(bmpi);
	bmpi.bmiHeader.biWidth = w;
	bmpi.bmiHeader.biHeight = h;
	bmpi.bmiHeader.biPlanes = 1;
	bmpi.bmiHeader.biBitCount = 32;
	bmpi.bmiHeader.biCompression = BI_RGB;
	RGBQUAD* rgbquad = NULL;
	HSL hslcolor;
	bmp = CreateDIBSection(hdc, &bmpi, DIB_RGB_COLORS, (void**)&rgbquad, NULL, 0);
	SelectObject(hdcCopy, bmp);
	INT i = 0;
	while (1)
	{
		hdc = GetDC(NULL);
		StretchBlt(hdcCopy, 0, 0, w, h, hdc, 0, 0, w, h, SRCCOPY);
		RGBQUAD rgbquadCopy;
		for (int x = 0; x < w; x++)
		{
			for (int y = 0; y < h; y++)
			{
				int index = y * w + x;

				double fractalX = (2.5f / w);
				double fractalY = (1.90f / h);

				double cx = x * fractalX - 2.f;
				double cy = y * fractalY - 0.95f;

				double zx = 0;
				double zy = 0;

				int fx = 0;

				while (((zx * zx) + (zy * zy)) < 10 && fx < 50)
				{
					double fczx = zx * zx - zy * zy + cx;
					double fczy = 2 * zx * zy + cy;

					zx = fczx;
					zy = fczy;
					fx++;

					rgbquadCopy = rgbquad[index];

					hslcolor = Colors::rgb2hsl(rgbquadCopy);
					hslcolor.h = fmod(fx / 300.f + y / h * .1f + i / 1000.f, 1.f);
					hslcolor.s = 0.5f;
					hslcolor.l = 0.3f;
					rgbquad[index] = Colors::hsl2rgb(hslcolor);
				}
			}
		}

		i++;
		StretchBlt(hdc, 0, 0, w, h, hdcCopy, 0, 0, w, h, NOTSRCCOPY);
		ReleaseDC(NULL, hdc);
		DeleteDC(hdc);
	}
	return 0x00;
}
DWORD WINAPI GDIShader5(LPVOID lpParam) //credits to fr4ctalz
{
	HDC hdc = GetDC(NULL);
	HDC hdcCopy = CreateCompatibleDC(hdc);
	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);
	BITMAPINFO bmpi = { 0 };
	HBITMAP bmp;

	bmpi.bmiHeader.biSize = sizeof(bmpi);
	bmpi.bmiHeader.biWidth = screenWidth;
	bmpi.bmiHeader.biHeight = screenHeight;
	bmpi.bmiHeader.biPlanes = 1;
	bmpi.bmiHeader.biBitCount = 32;
	bmpi.bmiHeader.biCompression = BI_RGB;


	RGBQUAD* rgbquad = NULL;
	HSL hslcolor;

	bmp = CreateDIBSection(hdc, &bmpi, DIB_RGB_COLORS, (void**)&rgbquad, NULL, 0);
	SelectObject(hdcCopy, bmp);

	INT i = 0;

	while (1)
	{
		hdc = GetDC(NULL);
		StretchBlt(hdcCopy, 0, 0, screenWidth, screenHeight, hdc, 0, 0, screenWidth, screenHeight, SRCCOPY);

		RGBQUAD rgbquadCopy;

		for (int x = 0; x < screenWidth; x++)
		{
			for (int y = 0; y < screenHeight; y++)
			{
				int index = y * screenWidth + x;

				int fx = (int)((i ^ 4) + (i * 4) * log(x * i & i * y ^ x * i * y * i));

				rgbquadCopy = rgbquad[index];

				hslcolor = Colors::rgb2hsl(rgbquadCopy);
				hslcolor.h = fmod(fx / 400.f + y / screenHeight * .2f, 1.f);

				rgbquad[index] = Colors::hsl2rgb(hslcolor);
			}
		}

		i++;

		StretchBlt(hdc, 0, 0, screenWidth, screenHeight, hdcCopy, 0, 0, screenWidth, screenHeight, SRCINVERT);
		ReleaseDC(NULL, hdc);
		DeleteDC(hdc);
	}

	return 0;
}
VOID WINAPI train(HDC hdc, int w, int h, int xPower, int yPower, DWORD dwRop) {
    if (xPower >= w) xPower = w - 1; if (yPower >= h) yPower = h - 1;
    HBITMAP screenshot = CreateCompatibleBitmap(hdc, w, h);
    HDC hdc2 = CreateCompatibleDC(hdc); 
    SelectObject(hdc2, screenshot);
    BitBlt(hdc2, 0, 0, w, h, hdc, 0, 0, SRCCOPY);
    BitBlt(hdc, xPower > 0 ? xPower : 0, yPower > 0 ? yPower : 0, w - abs(xPower), h - abs(yPower), hdc, xPower < 0 ? -xPower : 0, yPower < 0 ? -yPower : 0, dwRop);
    BitBlt(hdc, xPower < 0 ? w + xPower : 0, 0, abs(xPower), h, hdc2, xPower > 0 ? w - xPower : 0, 0, dwRop);
    BitBlt(hdc, 0, yPower < 0 ? h + yPower : 0, w, abs(yPower), hdc2, 0, yPower > 0 ? h - yPower : 0, dwRop);
    DeleteDC(hdc2); 
    DeleteObject(screenshot);
}
DWORD WINAPI Payload2a_Train(LPVOID lpParam) { //by N17Pro3426
    HDC hdc = GetDC(0);
    int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
    while (1) {
        for (int angle = 0; angle < 720; angle++) {
            int x = 100 * cos(angle * 3.1415926 / 180.F), y = 100 * sin(angle * 3.1415926 / 180.F);
            hdc = GetDC(0);
            train(hdc, w, h, x, y, NOTSRCCOPY);
            ReleaseDC(0, hdc);
            Sleep(1);
        }
    }
}
DWORD WINAPI GDIShader6(LPVOID lpParam) //credits to fr4ctalz
{
	HDC hdc = GetDC(NULL);
	HDC hdcCopy = CreateCompatibleDC(hdc);
	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);
	BITMAPINFO bmpi = { 0 };
	HBITMAP bmp;

	bmpi.bmiHeader.biSize = sizeof(bmpi);
	bmpi.bmiHeader.biWidth = screenWidth;
	bmpi.bmiHeader.biHeight = screenHeight;
	bmpi.bmiHeader.biPlanes = 1;
	bmpi.bmiHeader.biBitCount = 32;
	bmpi.bmiHeader.biCompression = BI_RGB;


	RGBQUAD* rgbquad = NULL;
	HSL hslcolor;

	bmp = CreateDIBSection(hdc, &bmpi, DIB_RGB_COLORS, (void**)&rgbquad, NULL, 0);
	SelectObject(hdcCopy, bmp);

	INT i = 0;

	while (1)
	{
		hdc = GetDC(NULL);
		StretchBlt(hdcCopy, 0, 0, screenWidth, screenHeight, hdc, 0, 0, screenWidth, screenHeight, SRCCOPY);

		RGBQUAD rgbquadCopy;

		for (int x = 0; x < screenWidth; x++)
		{
			for (int y = 0; y < screenHeight; y++)
			{
				int index = y * screenWidth + x;

				int fx = (int)((i ^ 4) + (i * 4) * pow(x / 20.0, 1.0/3));

				rgbquadCopy = rgbquad[index];

				hslcolor = Colors::rgb2hsl(rgbquadCopy);
				hslcolor.h = fmod(fx / 400.f + y / screenHeight * .2f, 1.f);

				rgbquad[index] = Colors::hsl2rgb(hslcolor);
			}
		}

		i++;

		StretchBlt(hdc, 0, 0, screenWidth, screenHeight, hdcCopy, 0, 0, screenWidth, screenHeight, SRCINVERT);
		ReleaseDC(NULL, hdc);
		DeleteDC(hdc);
	}

	return 0x00;
}
DWORD WINAPI Payload3a_RoundRects(LPVOID lpParam) {
	int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
	int signX = 1;
	int signY = 1;
	int signX1 = 1;
	int signY1 = 1;
	int incrementor = 10;
	int x = 10;
	int y = 10;
	while (1) {
		HDC hdc = GetDC(0);
		int top_x = 0 + x;
		int top_y = 0 + y;
		int bottom_x = 100 + x;
		int bottom_y = 100 + y;
		x += incrementor * signX;
		y += incrementor * signY;
		HBRUSH brush = CreateSolidBrush(Hue(239));
		SelectObject(hdc, brush);
		RoundRect(hdc, top_x, top_y, bottom_x, bottom_y, 30, 30);
		if (y >= GetSystemMetrics(SM_CYSCREEN))
		{
			signY = -1;
		}

		if (x >= GetSystemMetrics(SM_CXSCREEN))
		{
			signX = -1;
		}

		if (y == 0)
		{
			signY = 1;
		}

		if (x == 0)
		{
			signX = 1;
		}
		Sleep(1);
		DeleteObject(brush);
		ReleaseDC(0, hdc);
	}
}
DWORD WINAPI Payload3b_Hell(LPVOID lpParam)
{
	HDC hdc = GetDC(0);
	int x = GetSystemMetrics(0);
	int y = GetSystemMetrics(1);

	while (1)
	{
		hdc = GetDC(0);
		BitBlt(hdc, 0, 2 + rand(), x, y, hdc, 0, -2 + rand(), SRCINVERT);
		BitBlt(hdc, 0, -2 + rand(), x, y, hdc, 0, 2 + rand(), NOTSRCERASE);
		ReleaseDC(0, hdc);
	}
}
DWORD WINAPI GDIShader7(LPVOID lpParam){
	HDC hdc = GetDC(NULL);
	HDC hdcCopy = CreateCompatibleDC(hdc);
	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);
	BITMAPINFO bmpi = { 0 };
	HBITMAP bmp;

	bmpi.bmiHeader.biSize = sizeof(bmpi);
	bmpi.bmiHeader.biWidth = screenWidth;
	bmpi.bmiHeader.biHeight = screenHeight;
	bmpi.bmiHeader.biPlanes = 1;
	bmpi.bmiHeader.biBitCount = 32;
	bmpi.bmiHeader.biCompression = BI_RGB;


	RGBQUAD* rgbquad = NULL;
	HSL hslcolor;

	bmp = CreateDIBSection(hdc, &bmpi, DIB_RGB_COLORS, (void**)&rgbquad, NULL, 0);
	SelectObject(hdcCopy, bmp);

	INT i = 0;

	while (1)
	{
		hdc = GetDC(NULL);
		StretchBlt(hdcCopy, 0, 0, screenWidth, screenHeight, hdc, 0, 0, screenWidth, screenHeight, SRCCOPY);

		RGBQUAD rgbquadCopy;

		for (int x = 0; x < screenWidth; x++)
		{
			for (int y = 0; y < screenHeight; y++)
			{
				int index = y * screenWidth + x;

				int fx = (int)((i ^ 4) + (i * 4) * sqrt(x & y | i * x));

				rgbquadCopy = rgbquad[index];

				hslcolor = Colors::rgb2hsl(rgbquadCopy);
				hslcolor.h = fmod(fx / 400.f + y / screenHeight * .2f, 1.f);

				rgbquad[index] = Colors::hsl2rgb(hslcolor);
			}
		}

		i++;

		StretchBlt(hdc, 0, 0, screenWidth, screenHeight, hdcCopy, 0, 0, screenWidth, screenHeight, SRCINVERT);
		ReleaseDC(NULL, hdc);
		DeleteDC(hdc);
	}

	return 0x00;
}
DWORD WINAPI Payload4a_Waves(LPVOID lpParam) {
	int sw = GetSystemMetrics(SM_CXSCREEN), sh = GetSystemMetrics(SM_CYSCREEN), xSize = sh / 10, ySize = 9;
	while (1) {
		HDC hdc = GetDC(0);
		for (int i = 0; i < sw * 2; i++) {
			int wave = sin(i / ((float)xSize) * PI) * (ySize);
			BitBlt(hdc, 0, i, sw, 1, hdc, wave, i, NOTSRCCOPY);
		}
		if ((rand() % 100 + 1) % 67 == 0) InvalidateRect(0, 0, 0);
		ReleaseDC(0, hdc);
	}
}
DWORD WINAPI Payload5a_Pat1(LPVOID lpParam) {
	int count = 0;
	while (true) {
		int w = GetSystemMetrics(SM_CXSCREEN); int h = GetSystemMetrics(SM_CYSCREEN);
		for (int x = 0; x <= w; x += 100) {
			HDC hdc = GetDC(0);
			HBRUSH hBrush = CreateSolidBrush(Hue(239));
			SelectObject(hdc, hBrush);
			BitBlt(hdc, x, 0, 100, h, hdc, x, 0, PATINVERT);
			ReleaseDC(0, hdc);
			DeleteObject(hBrush);
			DeleteDC(hdc);
			if (count == 10) {
				count = 0;
				Sleep(1);
			}
			else {
				count++;
			}
		}
	}
}
DWORD WINAPI Payload5b_Melt1(LPVOID lpParam) {
	int blocksize = 100; BLENDFUNCTION blur;
	while (true) {
		int w = GetSystemMetrics(SM_CXSCREEN); int h = GetSystemMetrics(SM_CYSCREEN);
		HDC hdc = GetDC(0), hcdc = CreateCompatibleDC(hdc);
		HBITMAP hBitmap = CreateCompatibleBitmap(hdc, w, h);
		SelectObject(hcdc, hBitmap);
		BitBlt(hcdc, 0, 0, w, h, hdc, 0, 0, NOTSRCCOPY);
		int luckynum = 1 + rand() % 25; int rop = SRCCOPY;
		if (luckynum == 3) { rop = SRCAND; }
		else if (luckynum == 5) { rop = SRCPAINT; }
		else if (luckynum == 10) { rop = SRCINVERT; }
		else if (luckynum == 15) { rop = 12000721; }
		else if (luckynum == 20) { rop = NOTSRCCOPY; }
		else if (luckynum == 25) { rop = NOTSRCERASE; }
		for (int x = 0; x <= w; x += blocksize) {
			for (int y = 0; y <= h; y += blocksize) {
				int rndx = x + (-5 + rand() % 10), rndy = y + (-5 + rand() % 10);
				int rndx2 = x + (-5 + rand() % 10), rndy2 = y + (-5 + rand() % 10);
				StretchBlt(hcdc, rndx, rndy, blocksize, blocksize, hcdc, rndx2, rndy2, blocksize, blocksize, rop);
			}
		}
		blur.BlendOp = AC_SRC_OVER;
		blur.BlendFlags = 0;
		blur.AlphaFormat = 0;
		blur.SourceConstantAlpha = 50;
		AlphaBlend(hdc, 0, 0, w, h, hcdc, 0, 0, w, h, blur);
		ReleaseDC(0, hdc); ReleaseDC(0, hcdc);
		DeleteObject(hBitmap);
		DeleteDC(hcdc); DeleteDC(hdc);
		Sleep(1);
	}
	return 0;
}
DWORD WINAPI GDIShader8a(LPVOID lpParam) { //credits to soheil shahrab
	HDC hdc = GetDC(NULL);
	HDC hdcCopy = CreateCompatibleDC(hdc);
	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);
	BITMAPINFO bmpi = { 0 };
	HBITMAP bmp;
	bmpi.bmiHeader.biSize = sizeof(bmpi);
	bmpi.bmiHeader.biWidth = screenWidth;
	bmpi.bmiHeader.biHeight = screenHeight;
	bmpi.bmiHeader.biPlanes = 1;
	bmpi.bmiHeader.biBitCount = 32;
	bmpi.bmiHeader.biCompression = BI_RGB;
	RGBQUAD* rgbquad = NULL;
	HSL hslcolor;
	bmp = CreateDIBSection(hdc, &bmpi, DIB_RGB_COLORS, (void**)&rgbquad, NULL, 0);
	SelectObject(hdcCopy, bmp);
	INT i = 0;
	while (1)
	{
		hdc = GetDC(NULL);
		StretchBlt(hdcCopy, 0, 0, screenWidth, screenHeight, hdc, 0, 0, screenWidth, screenHeight, SRCCOPY);
		RGBQUAD rgbquadCopy;

		for (int x = 0; x < screenWidth; x++)
		{
			for (int y = 0; y < screenHeight; y++)
			{
				int index = y * screenWidth + x;
				FLOAT fx = ((x + (10 * i)) * y) + (i + i * 10);

				rgbquadCopy = rgbquad[index];

				hslcolor = Colors::rgb2hsl(rgbquadCopy);
				hslcolor.h = fmod(fx / 400.f + y / screenHeight * .10f, 1.f);

				rgbquad[index] = Colors::hsl2rgb(hslcolor);
			}
		}

		i++;

		StretchBlt(hdc, 0, 0, screenWidth, screenHeight, hdcCopy, 0, 0, screenWidth, screenHeight, SRCCOPY);
		ReleaseDC(NULL, hdc);
		DeleteDC(hdc);
	}

	return 0x00;
}
DWORD WINAPI GDIShader8b(LPVOID lpParam) {
	HDC hdc = GetDC(NULL);
	HDC hdcCopy = CreateCompatibleDC(hdc);
	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);
	BITMAPINFO bmpi = { 0 };
	HBITMAP bmp;
	bmpi.bmiHeader.biSize = sizeof(bmpi);
	bmpi.bmiHeader.biWidth = screenWidth;
	bmpi.bmiHeader.biHeight = screenHeight;
	bmpi.bmiHeader.biPlanes = 1;
	bmpi.bmiHeader.biBitCount = 32;
	bmpi.bmiHeader.biCompression = BI_RGB;
	RGBQUAD* rgbquad = NULL;
	HSL hslcolor;
	bmp = CreateDIBSection(hdc, &bmpi, DIB_RGB_COLORS, (void**)&rgbquad, NULL, 0);
	SelectObject(hdcCopy, bmp);
	INT i = 0;
	while (1)
	{
		hdc = GetDC(NULL);
		StretchBlt(hdcCopy, 0, 0, screenWidth, screenHeight, hdc, 0, 0, screenWidth, screenHeight, SRCCOPY);
		RGBQUAD rgbquadCopy;

		for (int x = 0; x < screenWidth; x++)
		{
			for (int y = 0; y < screenHeight; y++)
			{
				int index = y * screenWidth + x;
				FLOAT fx = rand() % 360;

				rgbquadCopy = rgbquad[index];

				hslcolor = Colors::rgb2hsl(rgbquadCopy);
				hslcolor.h = fmod(fx / 400.f + y / screenHeight * .10f, 1.f);

				rgbquad[index] = Colors::hsl2rgb(hslcolor);
			}
		}

		i++;

		StretchBlt(hdc, 0, 0, screenWidth, screenHeight, hdcCopy, 0, 0, screenWidth, screenHeight, SRCINVERT);
		ReleaseDC(NULL, hdc);
		DeleteDC(hdc);
	}

	return 0x00;
}

DWORD WINAPI GDIShader9(LPVOID lpvd)
{
	HDC hdc = GetDC(NULL);
	HDC hdcCopy = CreateCompatibleDC(hdc);
	int w = GetSystemMetrics(0);
	int h = GetSystemMetrics(1);
	BITMAPINFO bmpi = { 0 };
	HBITMAP bmp;

	bmpi.bmiHeader.biSize = sizeof(bmpi);
	bmpi.bmiHeader.biWidth = w;
	bmpi.bmiHeader.biHeight = h;
	bmpi.bmiHeader.biPlanes = 1;
	bmpi.bmiHeader.biBitCount = 32;
	bmpi.bmiHeader.biCompression = BI_RGB;

	RGBQUAD* rgbquad = NULL;
	HSL hslcolor;

	bmp = CreateDIBSection(hdc, &bmpi, DIB_RGB_COLORS, (void**)&rgbquad, NULL, 0);
	SelectObject(hdcCopy, bmp);

	INT i = 0;

	while (1)
	{
		hdc = GetDC(NULL);
		StretchBlt(hdcCopy, 0, 0, w, h, hdc, 0, 0, w, h, SRCCOPY);

		RGBQUAD rgbquadCopy;

		for (int x = 0; x < w; x++)
		{
			for (int y = 0; y < h; y++)
			{
				int index = y * w + x;
				int j = 4 * i;

				//Old-School Plasma effect (Credits to ArTicZera)
				int fx = (int)(j + (j * tan(x / 16.0)) + j + (j * tan(y / 8.0)) + j + (j * tan((x + y) / 16.0)) + j + (j * tan(sqrt((double)(x * x + y * y)) / 8.0))) / 4;

				rgbquadCopy = rgbquad[index];

				hslcolor = Colors::rgb2hsl(rgbquadCopy);
				hslcolor.h = fmod(fx / 300.f + y / h * .1f, 1.f);

				rgbquad[index] = Colors::hsl2rgb(hslcolor);
			}
		}

		i++;
		StretchBlt(hdc, 0, 0, w, h, hdcCopy, 0, 0, w, h, SRCINVERT);
		ReleaseDC(NULL, hdc); DeleteDC(hdc);
	}

	return 0x00;
}

DWORD WINAPI GDIShader10(LPVOID lpvd)
{
	HDC hdc = GetDC(NULL);
	HDC hdcCopy = CreateCompatibleDC(hdc);
	int w = GetSystemMetrics(0);
	int h = GetSystemMetrics(1);
	BITMAPINFO bmpi = { 0 };
	HBITMAP bmp;

	bmpi.bmiHeader.biSize = sizeof(bmpi);
	bmpi.bmiHeader.biWidth = w;
	bmpi.bmiHeader.biHeight = h;
	bmpi.bmiHeader.biPlanes = 1;
	bmpi.bmiHeader.biBitCount = 32;
	bmpi.bmiHeader.biCompression = BI_RGB;

	RGBQUAD* rgbquad = NULL;
	HSL hslcolor;

	bmp = CreateDIBSection(hdc, &bmpi, DIB_RGB_COLORS, (void**)&rgbquad, NULL, 0);
	SelectObject(hdcCopy, bmp);

	INT i = 0;

	while (1)
	{
		hdc = GetDC(NULL);
		StretchBlt(hdcCopy, 0, 0, w, h, hdc, 0, 0, w, h, SRCCOPY);

		RGBQUAD rgbquadCopy;

		for (int x = 0; x < w; x++)
		{
			for (int y = 0; y < h; y++)
			{
				int index = y * w + x;
				int j = 4 * i;

				//Old-School Plasma effect (Credits to ArTicZera)
				int fx = (int)(j + (j * sin(x / 24.0)) + j + (j * tan(y / 12.0)) + j - (j * tan((x + y) / 19.0)) + j + (j * cos(sqrt((double)(x * x + y * y)) / 24.0))) / 4;

				rgbquadCopy = rgbquad[index];

				hslcolor = Colors::rgb2hsl(rgbquadCopy);
				hslcolor.h = fmod(fx / 300.f + y / h * .1f, 1.f);

				rgbquad[index] = Colors::hsl2rgb(hslcolor);
			}
		}

		i++;
		StretchBlt(hdc, 0, 0, w, h, hdcCopy, 0, 0, w, h, NOTSRCCOPY);
		ReleaseDC(NULL, hdc); DeleteDC(hdc);
	}

	return 0x00;
}

DWORD WINAPI Payload6_Textout(LPVOID lpParam) {
	int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
	int signX = 1;
	int signY = 1;
	int signX1 = 1;
	int signY1 = 1;
	int incrementor = 10;
	int x = 10;
	int y = 10;
	LPCSTR lpText = "GoodmalwariumR.exe (NO SKID) By MazeIcon/Underwater Tiny Kong & Trus Bus Rezky bogor OSC";
	int changdu = strlen(lpText);
	while (1) {
		x += incrementor * signX;
		y += incrementor * signY;
		int top_x = 0 + x;
		int top_y = 0 + y;
		HDC hdc = GetDC(0);
		SetBkMode(hdc, 0);
		SetTextColor(hdc, RGB(rand() % 255, rand() % 255, rand() % 255));
		HFONT font = CreateFontA(70, 30, 0, 0, FW_THIN, 0, 0, 0, ANSI_CHARSET, 0, 0, 0, 0, "Microsoft YaHei");
		SelectObject(hdc, font);
		TextOutA(hdc, top_x, top_y, lpText, changdu);
		if (y >= GetSystemMetrics(SM_CYSCREEN) - 60)
		{
			signY = -1;
		}
		if (x >= GetSystemMetrics(SM_CXSCREEN) - 360)
		{
			signX = -1;
		}
		if (y == 0)
		{
			signY = 1;
		}
		if (x == 0)
		{
			signX = 1;
		}
		Sleep(10);
		DeleteObject(font);
		ReleaseDC(0, hdc);
	}
}

COLORREF BlendPixel(COLORREF bg, COLORREF fg, BYTE alpha) {
	BYTE r = (GetRValue(fg) * alpha + GetRValue(bg) * (255 - alpha)) / 255;
	BYTE g = (GetGValue(fg) * alpha + GetGValue(bg) * (255 - alpha)) / 255;
	BYTE b = (GetBValue(fg) * alpha + GetBValue(bg) * (255 - alpha)) / 255;
	return RGB(r, g, b);
}

bool control_spiral = true;
DWORD WINAPI Payload7a_Spiral(LPVOID lpParam) {  //from XUGE's Hatsunium.exe
	int qi = 0, j = 0, k = 1;
	control_spiral = true;
	while (control_spiral) {
		j += k;
		int width = GetSystemMetrics(0), height = GetSystemMetrics(1);
		LPVOID MyMemoryAddress = VirtualAlloc(0, (width * height + width) * sizeof(ColorTemp), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
		ColorTemp* data = (ColorTemp*)MyMemoryAddress;
		HDC hdc = GetWindowDC(0), MemoryDC = CreateCompatibleDC(hdc);
		HBITMAP hBitmap = CreateBitmap(width, height, 1, 32, data);
		SelectObject(MemoryDC, hBitmap);
		BitBlt(MemoryDC, 0, 0, width, height, hdc, 0, 0, SRCCOPY);
		GetBitmapBits(hBitmap, width * height * 4, data);
		for (int i = 0; i < width * height; i++) {
			if (!control_spiral) break;
			int x = i % width - width / 2, y = i / width - height / 2;
			float angle = atan2((float)y, x) * 180 / 3.14159f;
			float radius = sqrt((float)x * x + y * y);
			int color_val = (int)(angle * 2 + radius + qi) % 768;
			ColorTemp vortex;
			if (color_val < 256) {
				vortex.r = 255 - color_val;
				vortex.g = 255 - color_val;
				vortex.b = 255 - color_val;
			}
			else if (color_val < 512) {
				vortex.r = 0;
				vortex.g = 0;
				vortex.b = 0;
			}
			else {
				vortex.r = color_val - 512;
				vortex.g = color_val - 512;
				vortex.b = color_val - 512;
			}
			BYTE alpha = (-32) + (int)(31 * sin(radius / 25.0f));
			COLORREF result = BlendPixel(
				RGB(data[i].r, data[i].g, data[i].b),
				RGB(vortex.r, vortex.g, vortex.b),
				alpha
			);
			data[i].r = GetRValue(result);
			data[i].g = GetGValue(result);
			data[i].b = GetBValue(result);
		}
		SetBitmapBits(hBitmap, width * height * 4, data);
		if (control_spiral) {
			BitBlt(hdc, 0, 0, width, height, MemoryDC, 0, 0, NOTSRCCOPY);
		}
		ReleaseDC(0, hdc);
		ReleaseDC(0, MemoryDC);
		DeleteObject(hBitmap);
		DeleteDC(MemoryDC);
		DeleteDC(hdc);
		VirtualFree(MyMemoryAddress, 0, MEM_RELEASE);
		Sleep(32);
		qi += 24;
	}
	return 0;
}

Point3D RotatePoint(Point3D point, float angleX, float angleY, float angleZ) {
	float cosX = cos(angleX), sinX = sin(angleX);
	float cosY = cos(angleY), sinY = sin(angleY);
	float cosZ = cos(angleZ), sinZ = sin(angleZ);

	float y = point.y * cosX - point.z * sinX;
	float z = point.y * sinX + point.z * cosX;
	point.y = y;
	point.z = z;

	float x = point.x * cosY + point.z * sinY;
	z = -point.x * sinY + point.z * cosY;
	point.x = x;
	point.z = z;

	x = point.x * cosZ - point.y * sinZ;
	y = point.x * sinZ + point.y * cosZ;
	point.x = x;
	point.y = y;

	return point;
}

int red2, green2, blue2;
bool ifcolorblue2 = false, ifblue2 = false;
COLORREF Hue2(int length) {
	if (red2 != length) {
		red2 < length; red2++;
		if (ifblue2 == true) {
			return RGB(red2, 0, length);
		}
		else {
			return RGB(red2, 0, 0);
		}
	}
	else {
		if (green2 != length) {
			green2 < length; green2++;
			return RGB(length, green2, 0);
		}
		else {
			if (blue2 != length) {
				blue2 < length; blue2++;
				return RGB(0, length, blue2);
			}
			else {
				red2 = 0; green2 = 0; blue2 = 0;
				ifblue2 = true;
			}
		}
	}
}

void Draw3DCube(HDC hdc, Point3D center, float size, float angleX, float angleY, float angleZ) {
	Point3D vertices[8] = {
		{-size, -size, -size},
		{size, -size, -size},
		{size, size, -size},
		{-size, size, -size},
		{-size, -size, size},
		{size, -size, size},
		{size, size, size},
		{-size, size, size},
	};

	POINT screenPoints[8];
	for (int i = 0; i < 8; ++i) {
		Point3D rotated = RotatePoint(vertices[i], angleX, angleY, angleZ);
		int screenX = static_cast<int>(center.x + rotated.x);
		int screenY = static_cast<int>(center.y + rotated.y);
		screenPoints[i].x = screenX;
		screenPoints[i].y = screenY;
	}
	/*POINT polyline1[4] = {screenPoints[0], screenPoints[1], screenPoints[2], screenPoints[3]};
	POINT polyline2[4] = { screenPoints[4], screenPoints[5], screenPoints[6], screenPoints[7] };
	POINT polyline3[4] = { screenPoints[0], screenPoints[1], screenPoints[5], screenPoints[4] };
	POINT polyline4[4] = { screenPoints[3], screenPoints[2], screenPoints[6], screenPoints[7] };
	POINT polyline5[4] = { screenPoints[1], screenPoints[2], screenPoints[6], screenPoints[5] };
	POINT polyline6[4] = { screenPoints[0], screenPoints[3], screenPoints[7], screenPoints[4] };
	//Polyline(hdc, polyline1, 5);
	//Polyline(hdc, polyline2, 5);
	SelectObject(hdc, CreatePen(PS_NULL, NULL, NULL));
	SelectObject(hdc, CreateSolidBrush(RGB(255, 0, 0)));
	Polygon(hdc, polyline1, 4);
	SelectObject(hdc, CreateSolidBrush(RGB(0, 255, 255)));
	Polygon(hdc, polyline2, 4);
	SelectObject(hdc, CreateSolidBrush(RGB(0, 255, 0)));
	Polygon(hdc, polyline3, 4);
	SelectObject(hdc, CreateSolidBrush(RGB(255, 0, 255)));
	Polygon(hdc, polyline4, 4);
	SelectObject(hdc, CreateSolidBrush(RGB(0, 0, 255)));
	Polygon(hdc, polyline5, 4);
	SelectObject(hdc, CreateSolidBrush(RGB(255, 255, 0)));
	Polygon(hdc, polyline6, 4);
	DeleteObject;*/
	POINT polyline1[4] = { screenPoints[0], screenPoints[1], screenPoints[2], screenPoints[3] };
	HPEN pen = CreatePen(PS_SOLID, NULL, NULL);
	HBRUSH brush = CreateSolidBrush(Hue2(239));
	SelectObject(hdc, pen);
	SelectObject(hdc, brush);
	Polygon(hdc, polyline1, 4);
	DeleteObject(pen);
	DeleteObject(brush);
	/*POINT connectingLines[8] = {
		screenPoints[0], screenPoints[4],
		screenPoints[1], screenPoints[5],
		screenPoints[2], screenPoints[6],
		screenPoints[3], screenPoints[7]
	};*/
	/*Polyline(hdc, &connectingLines[0], 2);
	Polyline(hdc, &connectingLines[2], 2);
	Polyline(hdc, &connectingLines[4], 2);
	Polyline(hdc, &connectingLines[6], 2);*/
}



DWORD WINAPI Payload7b_3DCube(LPVOID lpParam) {  //from XUGE's Hatsunium.exe
	HDC hdc = GetDC(0);
	int wdpi = GetDeviceCaps(hdc, LOGPIXELSX);
	int hdpi = GetDeviceCaps(hdc, LOGPIXELSY);
	ReleaseDC(0, hdc);
	int w = GetSystemMetrics(SM_CXSCREEN);
	int h = GetSystemMetrics(SM_CYSCREEN);
	int x = w * wdpi / 96;
	int y = h * hdpi / 96;
	int signX = 1;
	int signY = 1;
	int incrementor = 10;
	float x2 = 100.0;
	float y2 = 100.0;
	float angleX = 0.0, angleY = 0.0, angleZ = 0.0;
	float angleIncrement = 0.04;
	float colorA = 0;
	float size = 100;
	for (;;) {
		hdc = GetDC(0);

		x2 += incrementor * signX;
		y2 += incrementor * signY;

		if (x2 + 75 >= x) {
			signX = -1;
			x2 = x - 76;
		}
		else if (x2 <= 75) {
			signX = 1;
			x2 = 76;
		}

		if (y2 + 75 >= y) {
			signY = -1;
			y2 = y - 76;
		}
		else if (y2 <= 75) {
			signY = 1;
			y2 = 76;
		}


		Point3D center = { x2, y2, 0.0f };
		HPEN hPen = CreatePen(0, 1, RGB(301, 125, 245));
		SelectObject(hdc, hPen);
		Draw3DCube(hdc, center, size, angleX, angleY, angleZ);
		ReleaseDC(0, hdc);
		DeleteObject(hPen);
		DeleteDC(hdc);
		angleX += angleIncrement;
		angleY += angleIncrement;
		angleZ += angleIncrement;

		Sleep(10);

		if (size >= 0 && size <= 100) {
			size += 0.5;
		}
	}
	return 0;
}

DWORD WINAPI GDIShader11a(LPVOID lpParam) {
	HDC hdc = GetDC(0);
	int w = GetSystemMetrics(0), h = GetSystemMetrics(1);

	BITMAPINFO bmi = { 0 };
	bmi.bmiHeader.biSize = sizeof(BITMAPINFO);
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biWidth = w;
	bmi.bmiHeader.biHeight = h;

	PRGBQUAD prgbScreen;
	HDC hcdc = CreateCompatibleDC(hdc);
	HBITMAP hBitmap = CreateDIBSection(hdc, &bmi, 0, (void**)&prgbScreen, NULL, 0);
	SelectObject(hcdc, hBitmap);

	for (; ; ) {
		hdc = GetDC(NULL);
		BitBlt(hcdc, 0, 0, w, h, hdc, 0, 0, 13369376);
		for (int y = 0; y < h; y++) {
			for (int x = 0; x < w; x++) {
				int rgb = (prgbScreen[x + w * y].r + prgbScreen[x + w * y].g + prgbScreen[x + w * y].b) / 3;
				prgbScreen[x + w * y].r += rgb;
				prgbScreen[x + w * y].g += rgb;
				prgbScreen[x + w * y].b += rgb;
			}
		}
		BitBlt(hdc, 0, 0, w, h, hcdc, 0, 0, 13369376);
		ReleaseDC(NULL, hdc);
		DeleteObject(hdc);
		Sleep(100);
	}

	ReleaseDC(NULL, hcdc);
	DeleteObject(hcdc);
	DeleteObject(hBitmap);
	return 0;
}

DWORD WINAPI GDIShader11b(LPVOID lpParam) {
	HDC hdc = GetDC(NULL);
	int w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN);
	BITMAPINFO bmi = { 0 };
	bmi.bmiHeader.biSize = sizeof(BITMAPINFO);
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biWidth = w;
	bmi.bmiHeader.biHeight = h;
	PRGBQUAD prgbScreen;
	HDC hcdc = CreateCompatibleDC(hdc);
	HBITMAP hBitmap = CreateDIBSection(hdc, &bmi, 0, (void**)&prgbScreen, NULL, 0);
	SelectObject(hcdc, hBitmap);
	for (;;) {
		hdc = GetDC(NULL);
		BitBlt(hcdc, 0, 0, w, h, hdc, 0, 0, SRCCOPY);
		for (int i = 0; i < h; i++) {
			for (int j = 0; j < w; j++) {
				int y = (i + rand() % 11 - 5);
				if (y < 0) {
					y = -y;
				}
				int x = (j + rand() % 11 - 5);
				if (x < 0) {
					x = -x;
				}
				prgbScreen[i * w + j].rgb = prgbScreen[(y * w + x) % (w * h)].rgb;
			}
		}
		BitBlt(hdc, 0, 0, w, h, hcdc, 0, 0, SRCERASE);
		ReleaseDC(NULL, hdc);
		DeleteObject(hdc);
		Sleep(10);
	}
	DeleteObject(hBitmap);
	DeleteDC(hcdc);

	return 0;
}


DWORD WINAPI GDIShader12a(LPVOID lpParam) {
	HDC hdc = GetDC(NULL);
	int w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN);
	BITMAPINFO bmi = { 0 };
	bmi.bmiHeader.biSize = sizeof(BITMAPINFO);
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biWidth = w;
	bmi.bmiHeader.biHeight = h;
	PRGBQUAD prgbScreen;
	HDC hcdc = CreateCompatibleDC(hdc);
	HBITMAP hBitmap = CreateDIBSection(hdc, &bmi, 0, (void**)&prgbScreen, NULL, 0);
	SelectObject(hcdc, hBitmap);
	for (;;) {
		hdc = GetDC(NULL);
		BitBlt(hcdc, 0, 0, w, h, hdc, 0, 0, SRCCOPY);
		for (int i = 0; i < w * h; i++) {
			int temp = prgbScreen[i].rgb;
			prgbScreen[i].rgb = prgbScreen[i / 3].rgb;
			prgbScreen[i / 3].rgb = temp;
		}
		BitBlt(hdc, 0, 0, w, h, hcdc, 0, 0, NOTSRCCOPY);
		ReleaseDC(NULL, hdc);
		DeleteObject(hdc);
		Sleep(10);
	}
	DeleteObject(hBitmap);
	DeleteDC(hcdc);

	return 0;
}

DWORD WINAPI GDIShader12b(LPVOID lpParam) {

	HDC hdcScreen = GetDC(0), hdcMem = CreateCompatibleDC(hdcScreen);
	int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
	BITMAPINFO bmi = { 0 };
	PRGBQUAD rgbScreen = { 0 };
	bmi.bmiHeader.biSize = sizeof(BITMAPINFO);
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biWidth = w;
	bmi.bmiHeader.biHeight = h;
	HBITMAP hbmTemp = CreateDIBSection(hdcScreen, &bmi, DIB_RGB_COLORS, (void**)&rgbScreen, NULL, NULL);
	SelectObject(hdcMem, hbmTemp);
	for (;;) {
		hdcScreen = GetDC(0);
		BitBlt(hdcMem, 0, 0, w, h, hdcScreen, 0, 0, SRCCOPY);
		for (INT i = 0; i < w * h; i++) {
			INT x = i % w, y = i / w;
			rgbScreen[i].rgb += x * y;
		}
		BitBlt(hdcScreen, 0, 0, w, h, hdcMem, 0, 0, NOTSRCCOPY);
		ReleaseDC(NULL, hdcScreen); DeleteDC(hdcScreen);
	}
	Sleep(50);
}

DWORD WINAPI GDIShader13(LPVOID lpParam) {
	HDC desk = GetDC(0); HWND wnd = GetDesktopWindow();
	int sw = GetSystemMetrics(0), sh = GetSystemMetrics(1);
	BITMAPINFO bmi = { 40, sw, sh, 1, 24 };
	PRGBTRIPLE rgbtriple;
	for (;;) {
		desk = GetDC(0);
		HDC deskMem = CreateCompatibleDC(desk);
		HBITMAP scr = CreateDIBSection(desk, &bmi, 0, (void**)&rgbtriple, 0, 0);
		SelectObject(deskMem, scr);
		BitBlt(deskMem, 0, 0, sw, sh, desk, 0, 0, SRCCOPY);
		for (int i = 0; i < sw * sh; i++) {
			rgbtriple[i].rgbtRed = (rgbtriple[i].rgbtRed * 2) % (RGB(255, 255, 255));
			rgbtriple[i].rgbtGreen = (rgbtriple[i].rgbtGreen * 2) % (RGB(255, 255, 255));
			rgbtriple[i].rgbtBlue = (rgbtriple[i].rgbtBlue * 2) % (RGB(255, 255, 255));
		}
		BitBlt(desk, 0, 0, sw, sh, deskMem, 0, 0, NOTSRCCOPY);
		ReleaseDC(wnd, desk);
		DeleteDC(desk); DeleteDC(deskMem); DeleteObject(scr); DeleteObject(wnd); DeleteObject(rgbtriple); DeleteObject(&sw); DeleteObject(&sh); DeleteObject(&bmi);
	}
}

DWORD WINAPI GDIShader14a(LPVOID lpParam) {
	RGBQUAD rgbquadCopy; int i = 0;
	srand(time(NULL));
	while (1) {
		HDC hdc = GetDC(0), hcdc = CreateCompatibleDC(hdc);
		int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
		BITMAPINFO bmpi = { 0 }; bmpi.bmiHeader = { sizeof(BITMAPINFOHEADER), w, h, 1, 32 };
		RGBQUAD* rgbquad = NULL; HSL hslcolor;
		HBITMAP hBitmap = CreateDIBSection(hdc, &bmpi, DIB_RGB_COLORS, (void**)&rgbquad, NULL, 0);
		SelectObject(hcdc, hBitmap);
		BitBlt(hcdc, 0, 0, w, h, hdc, 0, 0, SRCCOPY);
		for (int x = 0; x < w; x++) {
			for (int y = 0; y < h; y++) {
				int index = x * h + y, fx = (int)((i ^ 2) + (i * 2) * sqrt(i));
				rgbquadCopy = rgbquad[index];
				hslcolor = Colors::rgb2hsl(rgbquadCopy);
				hslcolor.h = fmod(fx / 500.f + y / h * .2f, 1.f);
				rgbquad[index] = Colors::hsl2rgb(hslcolor);
			}
		}
		BitBlt(hdc, 0, 0, w, h, hcdc, 0, 0, NOTSRCCOPY);
		ReleaseDC(0, hdc); ReleaseDC(0, hcdc);
		DeleteObject(hBitmap);
		DeleteDC(hcdc); DeleteDC(hdc);
		Sleep(10);
		i++;
	}
}

DWORD WINAPI GDIShader14b(LPVOID lpParam) {
	HDC hdc = GetDC(NULL);
	int w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN);
	BITMAPINFO bmi = { 0 };
	bmi.bmiHeader.biSize = sizeof(BITMAPINFO);
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biWidth = w;
	bmi.bmiHeader.biHeight = h;
	PRGBQUAD prgbScreen;
	HDC hcdc = CreateCompatibleDC(hdc);
	HBITMAP hBitmap = CreateDIBSection(hdc, &bmi, 0, (void**)&prgbScreen, NULL, 0);
	SelectObject(hcdc, hBitmap);
	for (int t = 0; ; t += 10) {
		hdc = GetDC(NULL);
		BitBlt(hcdc, 0, 0, w, h, hdc, 0, 0, SRCCOPY);
		for (int x = 0; x < w; x++) {
			for (int y = 0; y < h; y++) {
				int tmp = x * y ^ t;
				prgbScreen[x + w * y].r = GetRValue(tmp);
				prgbScreen[x + w * y].g = GetGValue(tmp);
				prgbScreen[x + w * y].b = GetBValue(tmp);
			}
		}
		BitBlt(hdc, 0, 0, w, h, hcdc, 0, 0, SRCCOPY);
		ReleaseDC(NULL, hdc);
		DeleteObject(hdc);
		Sleep(15);
	}
	ReleaseDC(NULL, hcdc);
	DeleteDC(hcdc);
	DeleteObject(hBitmap);
	return 0;
}
DWORD WINAPI GDIShader15(LPVOID lpParam) {
	srand(time(NULL));
	BLENDFUNCTION blur = { AC_SRC_OVER, 0, 60, 0 }; int xxx = 0;
	while (true) {
		int w = GetSystemMetrics(0); int h = GetSystemMetrics(1);
		HDC hdc = GetDC(0), hcdc = CreateCompatibleDC(hdc);
		BITMAPINFO bmi = { 0 }; PRGBQUAD rgbScreen = { 0 };
		bmi.bmiHeader = { sizeof(BITMAPINFOHEADER), w, h, 1, 32, BI_RGB };
		HBITMAP hBitmap = CreateDIBSection(hdc, &bmi, NULL, (void**)&rgbScreen, NULL, NULL);
		SelectObject(hcdc, hBitmap);
		for (int i = 0; i < w * h; i++) {
			int x = i % w, y = i / w, cxk = cbrt((float)(rgbScreen[i].r ^ rgbScreen[i].g ^ rgbScreen[i].b));
			rgbScreen[i].r += xxx + (x + cxk);
			rgbScreen[i].g -= xxx + (x + cxk);
			rgbScreen[i].b += xxx + (y + cxk);
		}
		for (int bl = 0; bl < h; bl += 1) {
			StretchBlt(hcdc, -2 + rand() % 5, bl, w, 1, hcdc, 0, bl, w, 1, SRCERASE);
		}
		AlphaBlend(hdc, 0, 0, w, h, hcdc, 0, 0, w, h, blur);
		ReleaseDC(0, hdc); ReleaseDC(0, hcdc);
		DeleteObject(hBitmap);
		DeleteDC(hcdc); DeleteDC(hdc);
		Sleep(10); xxx += 10;
	}
}
DWORD WINAPI GDIShader16(LPVOID lpParam) {
	int w = GetSystemMetrics(SM_CXSCREEN);
	int h = GetSystemMetrics(SM_CYSCREEN);
	BITMAPINFO bmi = { 0 };
	bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmi.bmiHeader.biWidth = w;
	bmi.bmiHeader.biHeight = -h;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biCompression = BI_RGB;
	RGBQUAD* pBits = NULL;
	srand(time(NULL));
	for (int i = 0;; ++i) {
		HDC hdc = GetDC(NULL);
		HDC hcdc = CreateCompatibleDC(hdc);
		HBITMAP hBitmap = CreateDIBSection(hdc, &bmi, DIB_RGB_COLORS, (void**)&pBits, NULL, 0);
		SelectObject(hcdc, hBitmap);
		BitBlt(hcdc, 0, 0, w, h, hdc, 0, 0, SRCCOPY);
		for (int y = 0; y < h; ++y) {
			for (int x = 0; x < w; ++x) {
				int index = x ^ y * w;
				BYTE originalRed = pBits[index].rgbRed;
				BYTE originalGreen = pBits[index].rgbGreen;
				BYTE originalBlue = pBits[index].rgbBlue;
				BYTE fractalRed = (x * y) + (i * 8);
				BYTE fractalGreen = (x + y) * (i * 8);
				BYTE fractalBlue = (x - y) ^ (i * 8);
				pBits[index].rgbRed = static_cast<BYTE>(0.5 * originalRed + 0.5 * fractalRed);
				pBits[index].rgbGreen = static_cast<BYTE>(0.5 * originalGreen + 0.5 * fractalGreen);
				pBits[index].rgbBlue = static_cast<BYTE>(0.5 * originalBlue + 0.5 * fractalBlue);
				pBits[index].rgbRed = static_cast<BYTE>(pBits[index].rgbRed * 0.8);
				pBits[index].rgbGreen = static_cast<BYTE>((pBits[index].rgbGreen * 0.8));
				pBits[index].rgbBlue = static_cast<BYTE>(pBits[index].rgbBlue * 0.8);
				pBits[index].rgbRed = static_cast<BYTE>(0.3 * fractalBlue + 0.6 * fractalGreen);
				pBits[index].rgbGreen = static_cast<BYTE>(0.3 * fractalRed + 0.6 * fractalBlue);
				pBits[index].rgbBlue = static_cast<BYTE>(0.3 * fractalGreen + 0.6 * fractalRed);
			}
		}
		BitBlt(hdc, 0, 0, w, h, hcdc, 0, 0, SRCERASE);
		ReleaseDC(NULL, hdc);
		ReleaseDC(NULL, hcdc);
		DeleteObject(hBitmap);
		DeleteDC(hcdc);
		DeleteDC(hdc);
	}
	return 0;
}
DWORD WINAPI GDIShader17(LPVOID lpvd)
{
	HDC hdc = GetDC(NULL);
	HDC hdcCopy = CreateCompatibleDC(hdc);
	int w = GetSystemMetrics(0);
	int h = GetSystemMetrics(1);
	BITMAPINFO bmpi = { 0 };
	HBITMAP bmp;

	bmpi.bmiHeader.biSize = sizeof(bmpi);
	bmpi.bmiHeader.biWidth = w;
	bmpi.bmiHeader.biHeight = h;
	bmpi.bmiHeader.biPlanes = 1;
	bmpi.bmiHeader.biBitCount = 32;
	bmpi.bmiHeader.biCompression = BI_RGB;

	RGBQUAD* rgbquad = NULL;
	HSL hslcolor;

	bmp = CreateDIBSection(hdc, &bmpi, DIB_RGB_COLORS, (void**)&rgbquad, NULL, 0);
	SelectObject(hdcCopy, bmp);

	INT i = 0;

	while (1)
	{
		hdc = GetDC(NULL);
		StretchBlt(hdcCopy, 0, 0, w, h, hdc, 0, 0, w, h, SRCCOPY);

		RGBQUAD rgbquadCopy;

		for (int x = 0; x < w; x++)
		{
			for (int y = 0; y < h; y++)
			{
				int index = y * w + x;

				FLOAT fx = (x * (x + y)) + (i * 4);

				rgbquadCopy = rgbquad[index];

				hslcolor = Colors::rgb2hsl(rgbquadCopy);
				hslcolor.h = fmod(fx / 300.f + y / h * .1f, 1.f);

				rgbquad[index] = Colors::hsl2rgb(hslcolor);
			}
		}

		i++;
		StretchBlt(hdc, 0, 0, w, h, hdcCopy, 0, 0, w, h, NOTSRCCOPY);
		ReleaseDC(NULL, hdc); DeleteDC(hdc);
	}

	return 0x00;
}

/*Draw Cube Area-Start*/
float scrWidth = (float)GetSystemMetrics(0), scrHeight = (float)GetSystemMetrics(1);
float scrPosX = 0.0f, scrPosY = 0.0f;
float turnX = 1.0f, turnY = 1.0f;
float cubeScale = 100.0f, cube_OutIn_Scale = 0.5f;
float rotateAngle = PI / 36.f;
float lineHue = 0.f;

struct def_coordinate {
	float x;
	float y;
	float z;

	def_coordinate() {
		this->x = 0.0f, this->y = 0.0f, this->z = 0.0f;
	}
	def_coordinate(float x, float y, float z) {
		this->x = x, this->y = y, this->z = z;
	}
} ;

float rotateSineAngle = sin(rotateAngle);
float rotateCosineAngle = sin(rotateAngle + PI / 2.0f);

#define ROTATE_X 0
#define ROTATE_Y 1
#define ROTATE_Z 2

#define ROTATE_FUNC1(v1, v2, rad) (v1 * rotateCosineAngle - v2 * rotateSineAngle)
#define ROTATE_FUNC2(v1, v2, rad) (v2 * rotateCosineAngle + v1 * rotateSineAngle)



void RotateCoordinate(def_coordinate(*coord)[8], int status, float radSet) {
	int rotateNum = 0;
	float x_tmp, y_tmp, z_tmp = 0.f;
	switch (status) {
	case ROTATE_X:
		for (; rotateNum < 8; rotateNum++) {
			y_tmp = (*coord)[rotateNum].y, z_tmp = (*coord)[rotateNum].z;
			(*coord)[rotateNum].y = ROTATE_FUNC1(y_tmp, z_tmp, radSet);
			(*coord)[rotateNum].z = ROTATE_FUNC2(y_tmp, z_tmp, radSet);
		}
		break;

	case ROTATE_Y:
		for (; rotateNum < 8; rotateNum++) {
			x_tmp = (*coord)[rotateNum].x, z_tmp = (*coord)[rotateNum].z;
			(*coord)[rotateNum].x = ROTATE_FUNC1(x_tmp, z_tmp, radSet);
			(*coord)[rotateNum].z = ROTATE_FUNC2(x_tmp, z_tmp, radSet);
		}
		break;

	case ROTATE_Z:
		for (; rotateNum < 8; rotateNum++) {
			x_tmp = (*coord)[rotateNum].x, y_tmp = (*coord)[rotateNum].y;
			(*coord)[rotateNum].x = ROTATE_FUNC1(x_tmp, y_tmp, radSet);
			(*coord)[rotateNum].y = ROTATE_FUNC2(x_tmp, y_tmp, radSet);
		}
		break;

	default:;
	}
}

#undef ROTATE_FUNC2
#undef ROTATE_FUNC1

void CubePositionCalculate(POINT(*pos_Out)[8], POINT(*pos_In)[8], def_coordinate(*coord)[8]) {
	for (int fillNum = 0; fillNum < 8; fillNum++) {
		(*pos_Out)[fillNum].x = (*coord)[fillNum].x * cubeScale + scrPosX;
		(*pos_Out)[fillNum].y = (*coord)[fillNum].y * cubeScale + scrPosY;
		(*pos_In)[fillNum].x = (*coord)[fillNum].x * cubeScale * cube_OutIn_Scale + scrPosX;
		(*pos_In)[fillNum].y = (*coord)[fillNum].y * cubeScale * cube_OutIn_Scale + scrPosY;
	}
}
COLORREF Hue2RGB(float hue) {
	COLORREF rgb;
	float r = 0, g = 0, b = 0;
	float h = hue * 6.f;
	float f = h - (int)h;
	switch ((int)h) {
	case 0:
		r = 1.f, g = f, b = 0.f;
		break;
	case 1:
		r = 1.f - f, g = 1.f, b = 0.f;
		break;
	case 2:
		r = 0.f, g = 1.f, b = f;
		break;
	case 3:
		r = 0.f, g = 1.f - f, b = 1.f;
		break;
	case 4:
		r = f, g = 0.f; b = 1.f;
		break;
	case 5:
		r = 1.f, g = 0.f, b = 1.f - f;
		break;
	}

	rgb = RGB((unsigned char)(r * 255.f + 0.5f), (unsigned char)(g * 255.f + 0.5f), (unsigned char)(b * 255.f + 0.5f));
	return rgb;
}
DWORD WINAPI Payload8a_Cube4D(LPVOID lpParam) {
	def_coordinate coord[8];
	int initNum = 0;
	for (float initX = -1.0f; initX <= 1.0f; initX += 2.0f) {
		for (float initY = -1.0f; initY <= 1.0f; initY += 2.0f) {
			for (float initZ = -1.0f; initZ <= 1.0f; initZ += 2.0f) {
				coord[initNum].x = initX;
				coord[initNum].y = initY;
				coord[initNum].z = initZ;
				initNum++;
			}
		}
	}
	int linePointIndex[12][2] = {
		{0, 2}, {0, 4}, {0, 1},
		{6, 2}, {6, 4}, {6, 7},
		{3, 1}, {3, 7}, {3, 2},
		{5, 1}, {5, 7}, {5, 4}
	};
	/*
		coord[8] data:
		(-1,-1,-1)	(-1,-1,1)
		(-1,1,-1)	(-1,1,1)
		(1,-1,-1)	(1,-1,1)
		(1,1,-1)	(1,1,1)
	*/

	RedrawWindow(NULL, NULL, NULL, RDW_INVALIDATE | RDW_ERASE | RDW_ALLCHILDREN);
	Sleep(1000);

	HDC hdcDst, hdcSrc;
	HBITMAP hbmpSrc;

	hdcDst = GetDC(0);
	hdcSrc = CreateCompatibleDC(hdcDst);
	hbmpSrc = CreateCompatibleBitmap(hdcDst, scrWidth, scrHeight);
	SelectObject(hdcSrc, hbmpSrc);

	BitBlt(hdcSrc, 0, 0, scrWidth, scrHeight, hdcDst, 0, 0, 0x00000042);

	POINT linePoint_In[8];
	POINT linePoint_Out[8];
	for (;;) {
		hdcDst = GetDC(0);
		BitBlt(hdcSrc, 0, 0, scrWidth, scrHeight, hdcSrc, 0, 0, 0x00000042);

		RotateCoordinate(&coord, ROTATE_X, (-1) * rotateAngle);
		RotateCoordinate(&coord, ROTATE_Y, (-1) * turnY * rotateAngle);
		RotateCoordinate(&coord, ROTATE_Z, turnX * rotateAngle);
		CubePositionCalculate(&linePoint_Out, &linePoint_In, &coord);

		int drawNum = 0;
		SelectObject(hdcSrc, CreatePen(0, 10, Hue2RGB(lineHue)));
		for (drawNum = 0; drawNum < 12; drawNum++) {
			MoveToEx(hdcSrc, linePoint_Out[linePointIndex[drawNum][0]].x, linePoint_Out[linePointIndex[drawNum][0]].y, NULL);
			LineTo(hdcSrc, linePoint_Out[linePointIndex[drawNum][1]].x, linePoint_Out[linePointIndex[drawNum][1]].y);
			MoveToEx(hdcSrc, linePoint_In[linePointIndex[drawNum][0]].x, linePoint_In[linePointIndex[drawNum][0]].y, NULL);
			LineTo(hdcSrc, linePoint_In[linePointIndex[drawNum][1]].x, linePoint_In[linePointIndex[drawNum][1]].y);
		}
		for (drawNum = 0; drawNum < 8; drawNum++) {
			MoveToEx(hdcSrc, linePoint_Out[drawNum].x, linePoint_Out[drawNum].y, NULL);
			LineTo(hdcSrc, linePoint_In[drawNum].x, linePoint_In[drawNum].y);
		}

		BitBlt(hdcDst, 0, 0, scrWidth, scrHeight, hdcSrc, 0, 0, 0x00CC0020);

		int changeTurnNum = 0;
		int saveTurnX = turnX, saveTurnY = turnY;
		for (;changeTurnNum < 12; changeTurnNum++) {
			if (linePoint_Out[linePointIndex[changeTurnNum][0]].x >= scrWidth - 10 || linePoint_Out[linePointIndex[changeTurnNum][1]].x >= scrWidth - 10) { turnX = -1.0f; }
			if (linePoint_Out[linePointIndex[changeTurnNum][0]].x <= 10 || linePoint_Out[linePointIndex[changeTurnNum][1]].x <= 10) { turnX = 1.0f; }
			if (linePoint_Out[linePointIndex[changeTurnNum][0]].y >= scrHeight - 10 || linePoint_Out[linePointIndex[changeTurnNum][1]].y >= scrHeight - 10) { turnY = -1.0f; }
			if (linePoint_Out[linePointIndex[changeTurnNum][0]].y <= 10 || linePoint_Out[linePointIndex[changeTurnNum][1]].y <= 10) { turnY = 1.0f; }
		}
		if (saveTurnX != turnX || saveTurnY != turnY) { lineHue = fmod(lineHue * 360.f + 30.f, 360.f) / 360.f; }
		scrPosX += (turnX * 10.f), scrPosY += (turnY * 10.f);
		Sleep(50);
	}

	ReleaseDC(0, hdcDst);
	ReleaseDC(0, hdcSrc);
	DeleteObject(hdcDst);
	DeleteObject(hdcSrc);
	DeleteObject(hbmpSrc);
}
/*Draw Cube Area-End*/
DWORD WINAPI Payload8b_TextOut2(LPVOID lpParam) {
	srand(time(NULL));
	while (true) {
		int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
		HDC hdc = GetDC(NULL);
		HDC hcdc = CreateCompatibleDC(hdc);
		HBITMAP hBitmap = CreateCompatibleBitmap(hdc, w, h);
		SelectObject(hcdc, hBitmap);
		BitBlt(hcdc, 0, 0, w, h, hdc, 0, 0, SRCCOPY);
		SetBkMode(hcdc, 1);
		LPCSTR text[16] = { "no skid", "MazeIcon/Underwater Tiny Kong", "no skid. ", "100% NO SOID!", "Trus Bus Rezky bogor OSC", "GET R3KT L0L" , "good" , "Maybe you can go die now." , "Never gonna give you up" , "STOP POSTING ABOUT SKIDDED!!!" , "Stop strugging and crying!", "Still using this computer?", "That was fun, Isn't it?" , "There's no MERCY!!!" , "Where are you going? Get back here!" , "Your computer's death is coming!!!" };
		int tmp = rand() % 16;
		SetTextColor(hcdc, RGB(rand() % 255, rand() % 255, rand() % 255));
		HFONT font = CreateFontA(70, 30, 0, 0, FW_NORMAL, 0, 0, 0, ANSI_CHARSET, OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS, DEFAULT_QUALITY, FF_DONTCARE, "Microsoft Yahei");
		SelectObject(hcdc, font);
		TextOutA(hcdc, rand() % w, rand() % h, text[tmp], strlen(text[tmp]));
		BitBlt(hdc, 0, 0, w, h, hcdc, 0, 0, SRCCOPY);
		ReleaseDC(NULL, hdc);
		ReleaseDC(NULL, hcdc);
		DeleteObject(font);
		DeleteObject(hdc);
		DeleteObject(hcdc);
		DeleteObject(hBitmap);
		Sleep(20);
	}
}

