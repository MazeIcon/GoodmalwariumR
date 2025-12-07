#include<stdio.h>
#include<windows.h>
#include<math.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h>
#include<tchar.h>

#define PI 3.141
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"msimg32.lib")
extern "C" WINBASEAPI HWND WINAPI GetConsoleWindow ();

typedef unsigned __int64 DWORD64, *PDWORD64;
#define MAXDWORD64 ((DWORD64)~(DWORD64)0)

int red, green, blue;
bool ifcolorblue = false, ifblue = false;
typedef union _RGBQUAD {
	COLORREF rgb;
	struct {
		BYTE r;
		BYTE g;
		BYTE b;
		BYTE Reserved;
	};
}_RGBQUAD, ColorTemp, * PRGBQUAD;
typedef struct
{
	FLOAT h;
	FLOAT s;
	FLOAT l;
} HSL;
namespace Colors
{
	//These HSL functions was made by Wipet, credits to him!

	HSL rgb2hsl(RGBQUAD rgb)
	{
		HSL hsl;

		BYTE r = rgb.rgbRed;
		BYTE g = rgb.rgbGreen;
		BYTE b = rgb.rgbBlue;

		FLOAT _r = (FLOAT)r / 255.f;
		FLOAT _g = (FLOAT)g / 255.f;
		FLOAT _b = (FLOAT)b / 255.f;

		FLOAT rgbMin = min(min(_r, _g), _b);
		FLOAT rgbMax = max(max(_r, _g), _b);

		FLOAT fDelta = rgbMax - rgbMin;
		FLOAT deltaR;
		FLOAT deltaG;
		FLOAT deltaB;

		FLOAT h = 0.f;
		FLOAT s = 0.f;
		FLOAT l = (FLOAT)((rgbMax + rgbMin) / 2.f);

		if (fDelta != 0.f)
		{
			s = l < .5f ? (FLOAT)(fDelta / (rgbMax + rgbMin)) : (FLOAT)(fDelta / (2.f - rgbMax - rgbMin));
			deltaR = (FLOAT)(((rgbMax - _r) / 6.f + (fDelta / 2.f)) / fDelta);
			deltaG = (FLOAT)(((rgbMax - _g) / 6.f + (fDelta / 2.f)) / fDelta);
			deltaB = (FLOAT)(((rgbMax - _b) / 6.f + (fDelta / 2.f)) / fDelta);

			if (_r == rgbMax)      h = deltaB - deltaG;
			else if (_g == rgbMax) h = (1.f / 3.f) + deltaR - deltaB;
			else if (_b == rgbMax) h = (2.f / 3.f) + deltaG - deltaR;
			if (h < 0.f)           h += 1.f;
			if (h > 1.f)           h -= 1.f;
		}

		hsl.h = h;
		hsl.s = s;
		hsl.l = l;
		return hsl;
	}

	RGBQUAD hsl2rgb(HSL hsl)
	{
		RGBQUAD rgb;

		FLOAT r = hsl.l;
		FLOAT g = hsl.l;
		FLOAT b = hsl.l;

		FLOAT h = hsl.h;
		FLOAT sl = hsl.s;
		FLOAT l = hsl.l;
		FLOAT v = (l <= .5f) ? (l * (1.f + sl)) : (l + sl - l * sl);

		FLOAT m;
		FLOAT sv;
		FLOAT fract;
		FLOAT vsf;
		FLOAT mid1;
		FLOAT mid2;

		INT sextant;

		if (v > 0.f)
		{
			m = l + l - v;
			sv = (v - m) / v;
			h *= 6.f;
			sextant = (INT)h;
			fract = h - sextant;
			vsf = v * sv * fract;
			mid1 = m + vsf;
			mid2 = v - vsf;

			switch (sextant)
			{
			case 0:
				r = v;
				g = mid1;
				b = m;
				break;
			case 1:
				r = mid2;
				g = v;
				b = m;
				break;
			case 2:
				r = m;
				g = v;
				b = mid1;
				break;
			case 3:
				r = m;
				g = mid2;
				b = v;
				break;
			case 4:
				r = mid1;
				g = m;
				b = v;
				break;
			case 5:
				r = v;
				g = m;
				b = mid2;
				break;
			}
		}

		rgb.rgbRed = (BYTE)(r * 255.f);
		rgb.rgbGreen = (BYTE)(g * 255.f);
		rgb.rgbBlue = (BYTE)(b * 255.f);

		return rgb;
	}
}
COLORREF Hue(int length) {
	if (red != length) {
		red < length; red++;
		if (ifblue == true) {
			return RGB(red, 0, length);
		}
		else {
			return RGB(red, 0, 0);
		}
	}
	else {
		if (green != length) {
			green < length; green++;
			return RGB(length, green, 0);
		}
		else {
			if (blue != length) {
				blue < length; blue++;
				return RGB(0, length, blue);
			}
			else {
				red = 0; green = 0; blue = 0;
				ifblue = true;
			}
		}
	}
}
void InitDPI() {
	HMODULE hModUser32=LoadLibraryW(L"user32.dll");
	BOOL(WINAPI *SetProcessDPIAware)(VOID) = (BOOL(WINAPI *)(VOID))GetProcAddress(hModUser32,"SetProcessDPIAware");
	if (SetProcessDPIAware)
		SetProcessDPIAware();
	FreeLibrary(hModUser32);
}

DWORD xs;
void SeedXorshift32(DWORD dwSeed) {
	xs = dwSeed;
}
DWORD Xorshift32() {
	xs ^= xs << 13;
	xs ^= xs >> 17;
	xs ^= xs << 5;
	return xs;
}

LPCWSTR GenRandomUnicodeString(int len) {
	wchar_t* strRandom = new wchar_t[len + 1];

	for (int i = 0; i < len; i++) {
		strRandom[i] = (rand() % 256) + 1024;
	}

	strRandom[len] = L'\0';

	return strRandom;
}
/*VOID WINAPI RotatePoints(POINT* points, int count, POINT center, float angle)// by 
{
	float cosVal = cos(angle);
	float sinVal = sin(angle);
	for (int i = 0; i < count; i++)
	{
		int translatedX = points[i].x - center.x;
		int translatedY = points[i].y - center.y;
		points[i].x = static_cast<int>(translatedX * cosVal - translatedY * sinVal + center.x);
		points[i].y = static_cast<int>(translatedX * sinVal + translatedY * cosVal + center.y);
	}
}*/
typedef struct
{
    float x;
    float y;
    float z;
} VERTEX;

struct Point3D {
    float x, y, z;
};

typedef struct
{
    int vtx0;
    int vtx1;
} EDGE;
namespace _3D   //by N17Pro3426
{
    VOID RotateX(VERTEX* vtx, float angle)
    {
        vtx->y = cos(angle) * vtx->y - sin(angle) * vtx->z;
        vtx->z = sin(angle) * vtx->y + cos(angle) * vtx->z;
    }
    VOID RotateY(VERTEX* vtx, float angle)
    {
        vtx->x = cos(angle) * vtx->x + sin(angle) * vtx->z;
        vtx->z = -sin(angle) * vtx->x + cos(angle) * vtx->z;
    }
    VOID RotateZ(VERTEX* vtx, float angle)
    {
        vtx->x = cos(angle) * vtx->x - sin(angle) * vtx->y;
        vtx->y = sin(angle) * vtx->x + cos(angle) * vtx->y;
    }
    void DrawEdge(HDC dc, LPCTSTR icon, int x0, int y0, int x1, int y1, int r)
    {
        int dx = abs(x1 - x0);
        int dy = -abs(y1 - y0);
        int sx = (x0 < x1) ? 1 : -1;
        int sy = (y0 < y1) ? 1 : -1;
        int error = dx + dy;
        int i = 0;
        HINSTANCE HSHELL32 = LoadLibrary(_T("shell32.dll"));
        while (true)
        {
            if (i == 0)
            {
                DrawIconEx(dc, x0, y0, LoadIcon(HSHELL32, MAKEINTRESOURCE(rand() % 336)),12,12,NULL,NULL,DI_NORMAL);
                i = 10;
            }
            else
            {
                i--;
            }
            if (x0 == x1 && y0 == y1)
            {
                break;
            }
            int e2 = 2 * error;
            if (e2 >= dy)
            {
                if (x0 == x1)
                {
                    break;
                }
                error += dy;
                x0 += sx;
            }
            if (e2 <= dx)
            {
                if (y0 == y1)
                {
                    break;
                }
                error += dx;
                y0 += sy;
            }
        }
    }
}
