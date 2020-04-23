//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <jpeg.hpp>

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm1::loadImageButtonClick(TObject *Sender)
{
    this->openPictureDialog->Title = "Open image";
    if (this->openPictureDialog->Execute())
    {
        String file = this->openPictureDialog->FileName;
        this->Image1->Picture->LoadFromFile(file);
        this->Image1->Stretch = true;
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::playAnimationButtonClick(TObject *Sender)
{
    this->Image1->Picture->Bitmap->Width = Image1->Width;
    this->Image1->Picture->Bitmap->Height = Image1->Height;

    double factor = Image1->Height * 1.0 / 11;

    Image1->Canvas->Pen->Color = clWhite;
    Image1->Canvas->Brush->Color = clWhite;
    Image1->Canvas->Rectangle(0, 0, Image1->Width, Image1->Height);

    Image1->Canvas->Pen->Color = clBlack;
    Image1->Canvas->Brush->Color = clBlue;

    int x, y;
    // first line
    x = 1 * factor;
    y = 3 * factor;
    Image1->Canvas->MoveTo(x, y);
    for (y = 3 * factor + 1; y <= 5 * factor; ++y)
    {
        Image1->Canvas->LineTo(x, y);
        Image1->Canvas->MoveTo(x, y);
        Repaint();
        Sleep(10);
    }

    y = 6 * factor;
    Image1->Canvas->MoveTo(x, y);
    for (y = y + 1; y <= 8 * factor; ++y)
    {
        Image1->Canvas->LineTo(x, y);
        Image1->Canvas->MoveTo(x, y);
        Repaint();
        Sleep(10);
    }

    for (x = x + 1; x <= 3 * factor; ++x)
    {
        Image1->Canvas->LineTo(x, y);
        Image1->Canvas->MoveTo(x, y);
        Repaint();
        Sleep(10);
    }

    for (y = y + 1; y <= 10 * factor; ++y)
    {
        Image1->Canvas->LineTo(x, y);
        Image1->Canvas->MoveTo(x, y);
        Repaint();
        Sleep(10);
    }

    for (x = x + 1; x <= 5 * factor; ++x)
    {
        Image1->Canvas->LineTo(x, y);
        Image1->Canvas->MoveTo(x, y);
        Repaint();
        Sleep(10);
    }

    x = 6 * factor;
    Image1->Canvas->MoveTo(x, y);
    for (x = x + 1; x <= 8 * factor; ++x)
    {
        Image1->Canvas->LineTo(x, y);
        Image1->Canvas->MoveTo(x, y);
        Repaint();
        Sleep(10);
    }

    for (y = y - 1; y >= 8 * factor; --y)
    {
        Image1->Canvas->LineTo(x, y);
        Image1->Canvas->MoveTo(x, y);
        Repaint();
        Sleep(10);
    }

    for (x = x + 1; x <= 10 * factor; ++x)
    {
        Image1->Canvas->LineTo(x, y);
        Image1->Canvas->MoveTo(x, y);
        Repaint();
        Sleep(10);
    }

    for (y = y - 1; y >= 6 * factor; --y)
    {
        Image1->Canvas->LineTo(x, y);
        Image1->Canvas->MoveTo(x, y);
        Repaint();
        Sleep(10);
    }

    y = 5 * factor;
    Image1->Canvas->MoveTo(x, y);
    for (y = y - 1; y >= 3 * factor; --y)
    {
        Image1->Canvas->LineTo(x, y);
        Image1->Canvas->MoveTo(x, y);
        Repaint();
        Sleep(10);
    }

    for (x = x - 1; x >= 8 * factor; --x)
    {
        Image1->Canvas->LineTo(x, y);
        Image1->Canvas->MoveTo(x, y);
        Repaint();
        Sleep(10);
    }

    for (y = y - 1; y >= 1 * factor; --y)
    {
        Image1->Canvas->LineTo(x, y);
        Image1->Canvas->MoveTo(x, y);
        Repaint();
        Sleep(10);
    }

    for (x = x - 1; x >= 6 * factor; --x)
    {
        Image1->Canvas->LineTo(x, y);
        Image1->Canvas->MoveTo(x, y);
        Repaint();
        Sleep(10);
    }

    x = 5 * factor;
    Image1->Canvas->MoveTo(x, y);
    for (x = x - 1; x >= 3 * factor; --x)
    {
        Image1->Canvas->LineTo(x, y);
        Image1->Canvas->MoveTo(x, y);
        Repaint();
        Sleep(10);
    }

    for (y = y + 1; y <= 3 * factor; ++y)
    {
        Image1->Canvas->LineTo(x, y);
        Image1->Canvas->MoveTo(x, y);
        Repaint();
        Sleep(10);
    }

    for (x = x - 1; x >= 1 * factor; --x)
    {
        Image1->Canvas->LineTo(x, y);
        Image1->Canvas->MoveTo(x, y);
        Repaint();
        Sleep(10);
    }

    x = 3 * factor;
    y = 3 * factor;

    for (x = x + 1; x <= 5 * factor; ++x)
    {
        Image1->Canvas->LineTo(x, y);
        Image1->Canvas->MoveTo(x, y);
        Repaint();
        Sleep(10);
    }

    for (y = y + 1; y <= 5 * factor; ++y)
    {
        Image1->Canvas->LineTo(x, y);
        Image1->Canvas->MoveTo(x, y);
        Repaint();
        Sleep(10);
    }

    y = 6 * factor;
    for (y = y + 2, x = x + 1; y <= 8 * factor && x <= 6 * factor; y += 2, x++)
    {
        Image1->Canvas->LineTo(x, y);
        Image1->Canvas->MoveTo(x, y);
        Repaint();
        Sleep(10);
    }

    for (x = x - 1; x >= 4 * factor; --x)
    {
        Image1->Canvas->LineTo(x, y);
        Image1->Canvas->MoveTo(x, y);
        Repaint();
        Sleep(10);
    }

    for (y = y - 2, x = x - 1; y >= 6 * factor && x >= 3 * factor; y -= 2, x--)
    {
        Image1->Canvas->LineTo(x, y);
        Image1->Canvas->MoveTo(x, y);
        Repaint();
        Sleep(10);
    }

    for (y = y + 1; y <= 8 * factor; ++y)
    {
        Image1->Canvas->LineTo(x, y);
        Image1->Canvas->MoveTo(x, y);
        Repaint();
        Sleep(10);
    }
}
//---------------------------------------------------------------------------
