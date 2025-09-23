#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

class Color
{
public:
    // Геттеры
    int GetR() { return r; }
    int GetG() { return g; }
    int GetB() { return b; }

    float GetH() { return h; }
    float GetS() { return s; }
    float GetV() { return v; }

    // Сеттеры
    bool SetRGB(int r, int g, int b)
    {
        if (!IsCorrectRGB(r, g, b))
        {
            printf("RGB values must be in range 0-255\n");
            return false;
        }
        this->r = r;
        this->g = g;
        this->b = b;
        RGBToHSV();
        return true;
    }

    bool SetHSV(float h, float s, float v)
    {
        if (!IsCorrectHSV(h, s, v))
        {
            printf("H must be 0-360, S and V must be 0-1\n");
            return false;
        }
        this->h = h;
        this->s = s;
        this->v = v;
        HSVToRGB();
        return true;
    }

    void PrintRGB()
    {
        cout << "RGB: (" << r << ", " << g << ", " << b << ")" << endl;
    }

    void PrintHSV()
    {
        cout << "HSV: (" << h << "°, " << s << ", " << v << ")" << endl;
    }

private:
    int r, g, b;
    float h, s, v;

    void RGBToHSV()
    {
        float r_norm = r / 255.0f;
        float g_norm = g / 255.0f;
        float b_norm = b / 255.0f;

        float cmax = max(r_norm, max(g_norm, b_norm));
        float cmin = min(r_norm, min(g_norm, b_norm));
        float delta = cmax - cmin;

        if (delta == 0) {
            h = 0;
        } else if (cmax == r_norm) {
            h = fmod(60 * ((g_norm - b_norm) / delta) + 360, 360);
        } else if (cmax == g_norm) {
            h = fmod(60 * ((b_norm - r_norm) / delta) + 120, 360);
        } else {
            h = fmod(60 * ((r_norm - g_norm) / delta) + 240, 360);
        }

        if (cmax == 0) {
            s = 0;
        } else {
            s = delta / cmax;
        }
        v = cmax;
    }

    void HSVToRGB()
    {
        float h_norm = v * s;
        float s_norm = h_norm * (1 - abs(fmod(h / 60, 2) - 1));
        float v_norm = v - h_norm;
        
        float r_norm, g_norm, b_norm;
        
        if (h >= 0 && h < 60) {
            r_norm = h_norm; 
            g_norm = s_norm; 
            b_norm = 0;
        } else if (h >= 60 && h < 120) {
            r_norm = s_norm;
            g_norm = h_norm;
            b_norm = 0;
        } else if (h >= 120 && h < 180) {
            r_norm = 0; 
            g_norm = h_norm; 
            b_norm = s_norm;
        } else if (h >= 180 && h < 240) {
            r_norm = 0;
            g_norm = s_norm; 
            b_norm = h_norm;
        } else if (h >= 240 && h < 300) {
            r_norm = s_norm; 
            g_norm = 0; 
            b_norm = h_norm;
        } else {
            r_norm = h_norm; 
            g_norm = 0; 
            b_norm = s_norm;
        }
        
        r = round((r_norm + v_norm) * 255);
        g = round((g_norm + v_norm) * 255);
        b = round((b_norm + v_norm) * 255);
    }

    bool IsCorrectRGB(int r, int g, int b)
    {
        return (r >= 0 && r <= 255) && 
               (g >= 0 && g <= 255) && 
               (b >= 0 && b <= 255);
    }

    bool IsCorrectHSV(float h, float s, float v)
    {
        return (h >= 0 && h < 360) &&
               (s >= 0 && s <= 1) &&
               (v >= 0 && v <= 1);
    }
};

int main()
{
    cout << "Зеленый цвет (120°, 1.0, 1.0):" << endl;
    Color green;
    green.SetHSV(120.0f, 1.0f, 1.0f);
    green.PrintHSV();
    green.PrintRGB();
    cout << endl;

    cout << "Красный цвет (255, 0, 0)" << endl;
    Color red;
    red.SetRGB(255, 0, 0);
    red.PrintRGB();
    red.PrintHSV();
    cout << endl;

    cout << "Изменение цвета:" << endl;
    Color color_2;
    color_2.SetRGB(0, 0, 0);
    color_2.PrintRGB();
    color_2.PrintHSV();
    cout << endl;

    cout << "Обратное преобразование HSV->RGB:" << endl;
    Color color;
    color.SetHSV(0.0f, 0.0f, 0.5f);
    color.PrintHSV();
    color.PrintRGB();
    cout << endl;

    cout << "Преобразование RGB->HSV:" << endl;
    Color same_color;
    same_color.SetRGB(128, 128, 128);
    same_color.PrintHSV();
    same_color.PrintRGB();
    cout << endl;
    
    cout << "Проверка на вывод ошибки" << endl;
    Color noname;
    if (noname.SetRGB(256, 0, 1)) 
    {
        noname.PrintHSV();
        noname.PrintRGB();
    } 
    else 
    {
        cout << "Invalid color values - no output" << endl;
    }
    cout << endl;

    return 0;
}