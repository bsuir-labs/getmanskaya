//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <vector>

/*
  TODO list for 2020.03.19

  1. Implement tree initialization out of source table
  2. Implement tree deletion.
  3. Implement tree rebalancing.
  4. Implement number of leaves counting.
  5. Implement input fields validation.

*/

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
void DeleteTree(Tree **root);
void InsertIntoTree(Tree *root, int value, String caption);
/// Returns a pointer to a node with the specified key
/// If not found, returns NULL
Tree* FindNodeByKey(Tree *root, int key);
bool RemoveFromTree(Tree **root, int key);
std::vector<String> GetTreeView(Tree *root, String prefix = "", bool isLeft = false);

struct Record
{
    int key;
    String caption;
};

struct RecordList
{
    Record* data;
    int size;
};

RecordList CreateRecordList(int size);
void RemoveRecordList(RecordList &list);

/// -1 value for the right edge means "list->size - 1"
void Sort(RecordList list);

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
    TGroupBox *printGroupBox;
    TGroupBox *controlsGroupBox;
    TButton *preorderButton;
    TButton *postorderButton;
    TButton *inorderButton;
    TButton *rebalanceButton;
    TButton *deleteButton;
    TButton *leavesButton;
    TLabel *treeLabel;
    TGroupBox *treeInitGroupBox;
    TStringGrid *sourceStringGrid;
    TButton *initTreeButton;
    TButton *clearTableButton;
    void __fastcall AppendButtonClick(TObject *Sender);
    void __fastcall findAndPrintButtonClick(TObject *Sender);
    void __fastcall findAndEraseButtonClick(TObject *Sender);
    void __fastcall preorderButtonClick(TObject *Sender);
    void __fastcall postorderButtonClick(TObject *Sender);
    void __fastcall inorderButtonClick(TObject *Sender);
private:	// User declarations
    BSUIR::Tree *root;     // Root of our tree

    bool treeIsInited() const;

    void updateTreeView();

    void clearOutput();
    void printToOutput(const String &str);

    void preOrderTraversal(BSUIR::Tree *start);
    void postOrderTraversal(BSUIR::Tree *start);
    void inOrderTraversal(BSUIR::Tree *start);
public:		// User declarations
    __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
