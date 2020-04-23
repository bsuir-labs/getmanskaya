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
#include <Series.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
    TImage *Image1;
    TButton *loadImageButton;
    TChart *Chart1;
    TGroupBox *chartControlsGroupBox;
    TGroupBox *imageControlsGroupBox;
    TRadioGroup *functionsToPlotGroup;
    TButton *playAnimationButton;
    TOpenDialog *openPictureDialog;
    TRadioButton *sinRadioButton;
    TRadioButton *expRadioButton;
    TRadioButton *xxRadioButton;
    TLabeledEdit *startEdit;
    TLabeledEdit *finishEdit;
    TButton *plotCharButton;
    TLabeledEdit *stepEdit;
    TLineSeries *Series1;
    void __fastcall loadImageButtonClick(TObject *Sender);
    void __fastcall playAnimationButtonClick(TObject *Sender);
    void __fastcall plotCharButtonClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
