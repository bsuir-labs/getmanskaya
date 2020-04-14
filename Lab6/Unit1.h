//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <vector>

namespace BSUIR
{

struct Tree
{
    int value;
    Tree* left; // left child
    Tree* right; // right child
};

/// The function for creating new root node
/// and initializing it with a value
Tree* InitTree(int value);
void InsertIntoTree(Tree *root, int value);
std::vector<String> GetTreeView(Tree *root, String prefix = "", bool isLeft = false);

}

//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
    TMemo *PrintArea;
    TEdit *NewElementEdit;
    TLabel *Label1;
    TButton *AppendButton;
    void __fastcall AppendButtonClick(TObject *Sender);
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
