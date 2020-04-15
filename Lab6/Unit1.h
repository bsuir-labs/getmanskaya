//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <vector>

namespace BSUIR
{

struct Tree
{
    int value; // key
    String caption;  // value
    Tree* left; // left child
    Tree* right; // right child
};

/// The function for creating new root node
/// and initializing it with a value
Tree* InitTree(int value, String caption);
void InsertIntoTree(Tree *root, int value, String caption);
/// Returns a pointer to a node with the specified key
/// If not found, returns NULL
Tree* FindNodeByKey(Tree *root, int key);
bool RemoveFromTree(Tree **root, int key);
std::vector<String> GetTreeView(Tree *root, String prefix = "", bool isLeft = false);

}

//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
    TMemo *PrintArea;
    TButton *AppendButton;
    TLabeledEdit *newKeyEdit;
    TGroupBox *appendGroupBox;
    TLabeledEdit *newValueEdit;
    TGroupBox *findGroupBox;
    TButton *findAndPrintButton;
    TLabeledEdit *findKeyEdit;
    TButton *findAndEraseButton;
    TMemo *searchResultsArea;
    TLabel *searchResultsLabel;
    void __fastcall AppendButtonClick(TObject *Sender);
    void __fastcall findAndPrintButtonClick(TObject *Sender);
    void __fastcall findAndEraseButtonClick(TObject *Sender);
private:	// User declarations
    BSUIR::Tree *root;     // Root of our tree

    bool treeIsInited() const;

    void updateTreeView();
public:		// User declarations
    __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
