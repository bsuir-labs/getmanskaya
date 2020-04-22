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
    // setup cols
    this->sourceStringGrid->Cells[0][0] = "Key";
    this->sourceStringGrid->Cells[1][0] = "Value";
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

void TForm1::clearOutput()
{
    this->searchResultsArea->Lines->Clear();
}

void TForm1::printToOutput(const String &str)
{
    this->searchResultsArea->Lines->Add(str);
}

void TForm1::preOrderTraversal(BSUIR::Tree *start)
{
    if (!start) return;

    String node = "[" + IntToStr(start->value) + "] " + start->caption;
    this->printToOutput(node);
    this->preOrderTraversal(start->left);
    this->preOrderTraversal(start->right);
}

void TForm1::postOrderTraversal(BSUIR::Tree *node)
{
    if (!node) return;

    String str = "[" + IntToStr(node->value) + "] " + node->caption;
    this->postOrderTraversal(node->left);
    this->postOrderTraversal(node->right);
    this->printToOutput(str);
}

void TForm1::inOrderTraversal(BSUIR::Tree *node)
{
    if (!node) return;

    String str = "[" + IntToStr(node->value) + "] " + node->caption;

    this->inOrderTraversal(node->left);
    this->printToOutput(str);
    this->inOrderTraversal(node->right);
}

void TForm1::clearInput()
{
    int size = sourceStringGrid->RowCount;
    for (int i = 1; i < size; ++i)
    {
        sourceStringGrid->Cells[0][i] = "";
        sourceStringGrid->Cells[1][i] = "";
    }
}

BSUIR::RecordList TForm1::getListFromInput()
{
    int size = this->sourceStringGrid->RowCount;
    int realSize = 0;
    for (int i = 1; i < size && !this->sourceStringGrid->Cells[0][i].IsEmpty(); ++i)
        realSize++;

    BSUIR::RecordList list = BSUIR::CreateRecordList(realSize);
    for (int i = 1; i <= realSize; ++i)
    {
        list.data[i - 1].key = StrToInt(sourceStringGrid->Cells[0][i]);
        list.data[i - 1].caption = sourceStringGrid->Cells[1][i];
    }

    return list;
}

//---------------------------------------------------------------------------

BSUIR::Tree* BSUIR::InitTree(int value, String caption)
{
    Tree* root = new Tree;
    root->value = value;
    root->caption = caption;
    root->left = root->right = NULL;
    return root;
}

void BSUIR::DeleteTree(BSUIR::Tree **root)
{
    if (*root != NULL)
    {
        DeleteTree(&(*root)->left);
        DeleteTree(&(*root)->right);
        delete *root;
        *root = NULL;
    }
}

void BSUIR::InsertIntoTree(BSUIR::Tree *root, int value, String caption)
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
        cur = InitTree(value, caption);
        if (value > prev->value)
            prev->right = cur;
        else
            prev->left = cur;
    }
}

int BSUIR::GetTreeSize(BSUIR::Tree *root)
{
    if (root == NULL) return 0;
    return 1 + GetTreeSize(root->left) + GetTreeSize(root->right);
}

BSUIR::Tree* BSUIR::FindNodeByKey(BSUIR::Tree *root, int key)
{
    Tree *ptr = root;
    while (ptr)
    {
        if (ptr->value == key) break;
        if (key > ptr->value)
            ptr = ptr->right;
        else
            ptr = ptr->left;
    }
    return ptr;
}

bool BSUIR::RemoveFromTree(BSUIR::Tree **root, int key)
{
    Tree *toBeRemoved, *prevRemoved;
    Tree *swapNode, *prevSwapNode;
    toBeRemoved = *root;
    prevRemoved = NULL;
    while (toBeRemoved && toBeRemoved->value != key)
    {
        prevRemoved = toBeRemoved;
        if (key > toBeRemoved->value)
            toBeRemoved = toBeRemoved->right;
        else
            toBeRemoved = toBeRemoved->left;
    }
    if (!toBeRemoved) return false;

    if (toBeRemoved->right == NULL)
        swapNode = toBeRemoved->left;
    else if (toBeRemoved->left == NULL)
        swapNode = toBeRemoved->right;
    else
    {
        prevSwapNode = toBeRemoved;
        swapNode = toBeRemoved->left;
        while (swapNode->right != NULL)
        {
            prevSwapNode = swapNode;
            swapNode = swapNode->right;
        }
        if (prevSwapNode == toBeRemoved) swapNode->right = toBeRemoved->right;
        else
        {
            swapNode->right = toBeRemoved->right;
            prevSwapNode->right = swapNode->left;
            swapNode->left = prevSwapNode;
        }
    }

    if (toBeRemoved == *root) *root = swapNode;
    else
    {
        if (toBeRemoved->value < prevRemoved->value)
            prevRemoved->left = swapNode;
        else
            prevRemoved->right = swapNode;
    }
    delete toBeRemoved;
    return true;
}

std::vector<String> BSUIR::GetTreeView(BSUIR::Tree *root, String prefix, bool isLeft)
{
   std::vector<String> res;

   if (root != NULL)
   {
       String row = prefix + "+--[" + IntToStr(root->value) + "] " + root->caption;
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

int BSUIR::CountLeaves(BSUIR::Tree *root)
{
    if (!root) return 0;
    if (root->left == NULL && root->right == NULL) return 1;
    return CountLeaves(root->left) + CountLeaves(root->right);
}

BSUIR::RecordList BSUIR::CreateRecordList(int size)
{
    RecordList list;
    list.size = size;
    list.data = new Record[size];
    return list;
}

void BSUIR::RemoveRecordList(RecordList &list)
{
    list.size = 0;
    if (list.data != NULL)
    {
        delete list.data;
        list.data = NULL;
    }
}

void BSUIR::Sort(BSUIR::RecordList list)
{
    int size = list.size;
    for (int i = 0; i < size - 1; ++i)
    {
        int to_swap = i;
        for (int j = i + 1; j < size; ++j)
            if (list.data[j].key < list.data[to_swap].key)
               to_swap = j;
        if (to_swap != i)
        {
           Record tmp = list.data[i];
           list.data[i] = list.data[to_swap];
           list.data[to_swap] = tmp;
        }
    }
}

BSUIR::Tree *BSUIR::CreateTree(BSUIR::RecordList list, int l, int r)
{
    if (r == -1) r = list.size;
    if (l == r) return NULL;

    int mid = (l + r) / 2;
    Tree* node = new Tree;
    node->value = list.data[mid].key;
    node->caption = list.data[mid].caption;
    node->left = CreateTree(list, l, mid);
    node->right = CreateTree(list, mid + 1, r);
    return node;
}

int BSUIR::CreateListFromTree(BSUIR::RecordList list, BSUIR::Tree *root, int lastElement)
{
    if (root == NULL) return lastElement;
    lastElement = CreateListFromTree(list, root->left, lastElement);
    Record rec;
    rec.key = root->value;
    rec.caption = root->caption;
    list.data[lastElement] = rec;
    lastElement++;
    lastElement = CreateListFromTree(list, root->right, lastElement);
    return lastElement;
}

void __fastcall TForm1::AppendButtonClick(TObject *Sender)
{
    ((void)Sender);
    int value = StrToInt(this->newKeyEdit->Text);
    String caption = this->newValueEdit->Text;
    if (!treeIsInited())
       root = BSUIR::InitTree(value, caption);
    else
        BSUIR::InsertIntoTree(root, value, caption);

    this->updateTreeView();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::findAndPrintButtonClick(TObject *Sender)
{
    ((void)Sender);

    this->searchResultsArea->Lines->Clear();

    int key = StrToInt(this->findKeyEdit->Text);
    BSUIR::Tree *node = BSUIR::FindNodeByKey(root, key);
    if (node)
    {
        String firstRow = "Found:";
        String secondRow = "Key:\t" + IntToStr(node->value);
        String thirdRow = "Value:\t" + node->caption;
        this->searchResultsArea->Lines->Add(firstRow);
        this->searchResultsArea->Lines->Add(secondRow);
        this->searchResultsArea->Lines->Add(thirdRow);
    }
    else
    {
        this->searchResultsArea->Lines->Add("No such key in tree :c");
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::findAndEraseButtonClick(TObject *Sender)
{
    ((void)Sender);

    this->searchResultsArea->Lines->Clear();

    int key = StrToInt(this->findKeyEdit->Text);
    bool result = BSUIR::RemoveFromTree(&root, key);

    String output;
    if (result)
        output = "Removed successfully";
    else
        output = "No such key in tree :c";
    this->searchResultsArea->Lines->Add(output);

    this->updateTreeView();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::preorderButtonClick(TObject *Sender)
{
    ((void)Sender);
    if (!this->treeIsInited())
    {
        this->printToOutput("Init the tree first.");
        return;
    }
    this->clearOutput();
    this->printToOutput("### PRE-ORDER TRAVERSAL ###");

    this->preOrderTraversal(this->root);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::postorderButtonClick(TObject *Sender)
{
    ((void)Sender);
    if (!this->treeIsInited())
    {
        this->printToOutput("Init the tree first.");
        return;
    }
    this->clearOutput();
    this->printToOutput("### POST-ORDER TRAVERSAL ###");

    this->postOrderTraversal(this->root);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::inorderButtonClick(TObject *Sender)
{
    ((void)Sender);
    if (!this->treeIsInited())
    {
        this->printToOutput("Init the tree first.");
        return;
    }
    this->clearOutput();
    this->printToOutput("### IN-ORDER TRAVERSAL ###");

    this->inOrderTraversal(this->root);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::deleteButtonClick(TObject *Sender)
{
    ((void)Sender);
    BSUIR::DeleteTree(&root);
    this->updateTreeView();
    this->clearOutput();
    this->printToOutput("Tree was deleted.");
}
//---------------------------------------------------------------------------

void __fastcall TForm1::rebalanceButtonClick(TObject *Sender)
{
    ((void)Sender);
    this->clearOutput();
    if (this->root == NULL)
    {
        this->printToOutput("Can't rebalance empty tree");
        return;
    }

    int treeSize = BSUIR::GetTreeSize(root);
    BSUIR::RecordList list = BSUIR::CreateRecordList(treeSize);
    BSUIR::CreateListFromTree(list, root);
    BSUIR::Sort(list);
    BSUIR::DeleteTree(&root);
    root = BSUIR::CreateTree(list);

    this->printToOutput("The tree was rebalanced...");
    this->updateTreeView();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::clearTableButtonClick(TObject *Sender)
{
    ((void)Sender);
    this->clearInput();    
}
//---------------------------------------------------------------------------

void __fastcall TForm1::initTreeButtonClick(TObject *Sender)
{
    ((void)Sender);
    BSUIR::RecordList list = this->getListFromInput();
    BSUIR::Sort(list);
    if (this->treeIsInited()) BSUIR::DeleteTree(&root);
    this->root = BSUIR::CreateTree(list);
    this->updateTreeView();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::leavesButtonClick(TObject *Sender)
{
    ((void)Sender);
    this->clearOutput();
    int numberOfLeaves = BSUIR::CountLeaves(root);
    String output = "The tree contains " + IntToStr(numberOfLeaves) + " leaves!";
    this->printToOutput(output);
}
//---------------------------------------------------------------------------

