//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
    : TForm(Owner)
    , root(NULL)
{
    updateTreeView();
}

bool TForm1::treeIsInited() const
{
    return this->root != NULL;
}

void TForm1::updateTreeView()
{
    this->PrintArea->Lines->Clear();
    if (!treeIsInited()) {
        this->PrintArea->Lines->Add("Tree is not inited.");
        return;
    }

    std::vector<String> rows = GetTreeView(this->root);
    for (size_t i = 0; i < rows.size(); ++i)
        this->PrintArea->Lines->Add(rows[i]);
}
//---------------------------------------------------------------------------

BSUIR::Tree* BSUIR::InitTree(int value)
{
    Tree* root = new Tree;
    root->value = value;
    root->left = root->right = NULL;
    return root;
}

void BSUIR::InsertIntoTree(BSUIR::Tree *root, int value)
{
    Tree *cur = root, *prev = NULL;
    while (cur)
    {
        if (cur->value == value) break;
        prev = cur;
        if (value > cur->value)
            cur = cur->right;
        else
            cur = cur->left;
    }
    if (!cur)
    {
        cur = InitTree(value);
        if (value > prev->value)
            prev->right = cur;
        else
            prev->left = cur;
    }
}

/*
void printBT(const std::string& prefix, const BSTNode* node, bool isLeft)
{
    if( node != nullptr )
    {
        std::cout << prefix;

        std::cout << (isLeft ? "+--" : "+--" );

        // print the value of the node
        std::cout << node->m_val << std::endl;

        // enter the next tree level - left and right branch
        printBT( prefix + (isLeft ? "¦   " : "    "), node->m_left, true);
        printBT( prefix + (isLeft ? "¦   " : "    "), node->m_right, false);
    }
}

void printBT(const BSTNode* node)
{
    printBT("", node, false);    
}

// pass the root node of your binary tree
printBT(root);
*/

std::vector<String> BSUIR::GetTreeView(BSUIR::Tree *root, String prefix, bool isLeft)
{
   std::vector<String> res;

   if (root != NULL)
   {
       String row = prefix + "+--" + IntToStr(root->value);
       res.push_back(row);

       std::vector<String> left = GetTreeView(root->left, prefix + (isLeft ? "|   " : "    "), true);
       std::vector<String> right = GetTreeView(root->right, prefix + (isLeft ? "|   " : "    "), false);

       for (size_t i = 0; i < left.size(); ++i)
           res.push_back(left[i]);
       for (size_t i = 0; i < right.size(); ++i)
           res.push_back(right[i]);
   }
   else
   {
       String row = prefix + "+--NULL";
       res.push_back(row);
   }
   return res;
}
void __fastcall TForm1::AppendButtonClick(TObject *Sender)
{
    ((void)Sender);
    int value = StrToInt(this->NewElementEdit->Text);
    if (!treeIsInited())
       root = BSUIR::InitTree(value);
    else
        BSUIR::InsertIntoTree(root, value);

    this->updateTreeView();
}
//---------------------------------------------------------------------------

