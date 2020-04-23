//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Chart.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
#include <ExtDlgs.hpp>
#include <TeEngine.hpp>
#include <TeeProcs.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
    TImage *Image1;
    TButton *loadImageButton;
    TChart *Chart1;
    TGroupBox *chartControlsGroupBox;
    TGroupBox *imageControlsGroupBox;
    TRadioGroup *RadioGroup1;
    TButton *playAnimationButton;
    TOpenDialog *openPictureDialog;
    void __fastcall loadImageButtonClick(TObject *Sender);
    void __fastcall playAnimationButtonClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
