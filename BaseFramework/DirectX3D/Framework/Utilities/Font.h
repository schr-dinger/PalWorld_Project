#pragma once

class Font : public Singleton<Font>
{
public:
    Font();
    ~Font();

    void AddColor(string key, float r, float g, float b);
    void AddStyle(string key, wstring font, float size = 20.0f,
        DWRITE_FONT_WEIGHT weight = DWRITE_FONT_WEIGHT_NORMAL,
        DWRITE_FONT_STYLE style = DWRITE_FONT_STYLE_NORMAL,
        DWRITE_FONT_STRETCH stretch = DWRITE_FONT_STRETCH_NORMAL,
        DWRITE_TEXT_ALIGNMENT alignnment = DWRITE_TEXT_ALIGNMENT_LEADING); // ����: �⺻�� ���� ����,  
                                                                           // DWRITE_TEXT_ALIGNMENT_CENTER : ��� ����
                                                                           // DWRITE_TEXT_ALIGNMENT_TRAILING : ���� ����
                                                                           // DWRITE_TEXT_ALIGNMENT_JUSTIFIED : ���� ����

    void SetColor(string key);
    void SetStyle(string key);

    void RenderText(wstring text, Float2 pos, Float2 size = Float2());
    void RenderText(string text, Float2 pos, int alignnment = 0, Float2 size = Float2()); // alignnment : 0 ���� ����, 1 ���, 2, ����

    ID2D1DeviceContext* GetDC() { return context; }

    wstring ChangeWString(string value);

private:
    ID2D1Factory1* factory;
    IDWriteFactory* writeFactory;

    ID2D1Device* device;
    ID2D1DeviceContext* context;

    ID2D1Bitmap1* targetBitmap;

    map<string, ID2D1SolidColorBrush*> brushes;
    map<string, IDWriteTextFormat*> formats;

    ID2D1SolidColorBrush* curBrush;
    IDWriteTextFormat* curFormat;
};