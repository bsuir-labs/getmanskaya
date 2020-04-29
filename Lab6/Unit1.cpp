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
    // Задаём заголовки в таблице
    this->sourceStringGrid->Cells[0][0] = "Key";
    this->sourceStringGrid->Cells[1][0] = "Value";
    updateTreeView();
}

// Функция проверки дерева на инициализацию
bool TForm1::treeIsInited() const
{
    return this->root != NULL;
}

// Функция построения представления дерева в виде текста
void TForm1::updateTreeView()
{
    this->PrintArea->Lines->Clear();    // Очищаем текущее значение
    if (!treeIsInited()) {              // Если дерева нету, то и выводить нечего
        this->PrintArea->Lines->Add("Tree is not inited.");
        return;
    }

    std::vector<String> rows = GetTreeView(this->root); // Иначе строим представление
    for (size_t i = 0; i < rows.size(); ++i)            // и выводим его на форму
        this->PrintArea->Lines->Add(rows[i]);
}

// Очистка поля вывода
void TForm1::clearOutput()
{
    this->searchResultsArea->Lines->Clear();
}

// Добавление строки в поле вывода
void TForm1::printToOutput(const String &str)
{
    this->searchResultsArea->Lines->Add(str);
}

// Обход дерева
void TForm1::preOrderTraversal(BSUIR::Tree *start)
{
    if (!start) return;

    String node = "[" + IntToStr(start->value) + "] " + start->caption;
    this->printToOutput(node);
    this->preOrderTraversal(start->left);
    this->preOrderTraversal(start->right);
}

// Обход дерева
void TForm1::postOrderTraversal(BSUIR::Tree *node)
{
    if (!node) return;

    String str = "[" + IntToStr(node->value) + "] " + node->caption;
    this->postOrderTraversal(node->left);
    this->postOrderTraversal(node->right);
    this->printToOutput(str);
}

// Обход дерева
void TForm1::inOrderTraversal(BSUIR::Tree *node)
{
    if (!node) return;

    String str = "[" + IntToStr(node->value) + "] " + node->caption;

    this->inOrderTraversal(node->left);
    this->printToOutput(str);
    this->inOrderTraversal(node->right);
}

// Очистка таблицы для ввода
void TForm1::clearInput()
{
    int size = sourceStringGrid->RowCount;
    for (int i = 1; i < size; ++i)
    {
        sourceStringGrid->Cells[0][i] = "";
        sourceStringGrid->Cells[1][i] = "";
    }
}

// Получение значений из таблицы в виде массива структур
BSUIR::RecordList TForm1::getListFromInput()
{
    int size = this->sourceStringGrid->RowCount;
    int realSize = 0;
    for (int i = 1; i < size && !this->sourceStringGrid->Cells[0][i].IsEmpty(); ++i)
        realSize++;

    BSUIR::RecordList list = BSUIR::CreateRecordList(realSize); // Создаём массив нужного размера
    for (int i = 1; i <= realSize; ++i)                         // И по очереди кладём туда значения
    {
        list.data[i - 1].key = StrToInt(sourceStringGrid->Cells[0][i]);
        list.data[i - 1].caption = sourceStringGrid->Cells[1][i];
    }

    return list;
}

//---------------------------------------------------------------------------

/// Инициализация дерева
/// По сути, тут всё из методы
BSUIR::Tree* BSUIR::InitTree(int value, String caption)
{
    Tree* root = new Tree;  // создаём вершину
    root->value = value;    // заполняем значения
    root->caption = caption;
    root->left = root->right = NULL;
    return root;            // возвращаем
}


// Удаление дерева
// Тоже, в общем-то, из методы
void BSUIR::DeleteTree(BSUIR::Tree **root)
{
    if (*root != NULL)
    {
        DeleteTree(&(*root)->left);     // рекурсивно спускаемся до листьев и удаляем
        DeleteTree(&(*root)->right);
        delete *root;
        *root = NULL;
    }
}

// Добавление элемента в дерево
// Тоже из методы
void BSUIR::InsertIntoTree(BSUIR::Tree *root, int value, String caption)
{
    Tree *cur = root, *prev = NULL;
    while (cur)             // Ищем, куда нужно вставить
    {
        if (cur->value == value) break; // если такой ключ уже есть, то ничего не делаем
        prev = cur;
        if (value > cur->value)
            cur = cur->right;
        else
            cur = cur->left;
    }
    if (!cur)       // если дерево было пустым, то создаём новое
    {
        cur = InitTree(value, caption);
        if (value > prev->value)
            prev->right = cur;
        else
            prev->left = cur;
    }
}

// Рекурсивно получаем размер дерева
int BSUIR::GetTreeSize(BSUIR::Tree *root)
{
    if (root == NULL) return 0; // Если текущей вершины нет, то возвращаем 1
    return 1 + GetTreeSize(root->left) + GetTreeSize(root->right); // Иначе возвращаем 1 + размер правого поддерева + размер левого
}

// Поиск элемента в дереве по ключу
// Тоже из методы
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

// Удаление элемента из дерева
// Код из методы, я понятнее вряд ли объясню
// Разве что тут переменные понятнее названы
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

// Получение представления дерева в виде текста
// Рекурсивно ходим по дереву и составляем строки
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

// Функция для подсчёта листьев
int BSUIR::CountLeaves(BSUIR::Tree *root)
{
    if (!root) return 0;
    if (root->left == NULL && root->right == NULL) return 1;    // если мы в листке, возвращаем 1
    return CountLeaves(root->left) + CountLeaves(root->right);  // Иначе спускаемся в поддеревья
}

// Функция для создания массива структур
BSUIR::RecordList BSUIR::CreateRecordList(int size)
{
    RecordList list;    // Создаём массив
    list.size = size;   // задаём размер
    list.data = new Record[size];   // выделяем память
    return list;    // возвращаем
}

// Функция для удаления массива
void BSUIR::RemoveRecordList(RecordList &list)
{
    list.size = 0;  // уменьшаем размер
    if (list.data != NULL)
    {
        delete list.data;   // удаляем массив
        list.data = NULL;
    }
}

// Функция сортировки массива
// Тут сортировка выбором, как в прошлых лабах была
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

// Создание дерева на основе массива структур
// Код из методы, как создать дерево из отсортированных значений
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

// Создание массива структур на основе дерева
// Обходим дерево в порядке возрастания ключа и добавляем по очереди
// элементы в массив
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

// Обработка кнопки добавления нового элемента
void __fastcall TForm1::AppendButtonClick(TObject *Sender)
{
    ((void)Sender);
    int value = StrToInt(this->newKeyEdit->Text);   // берём значение ключа
    String caption = this->newValueEdit->Text;      // и значение значения ://
    if (!treeIsInited())                            // Если дерева ещё не было
       root = BSUIR::InitTree(value, caption);      // То создаём новое
    else                                            // Иначе
        BSUIR::InsertIntoTree(root, value, caption);// Добавляем к текущему

    this->updateTreeView();                         // Обновляем представление
}
//---------------------------------------------------------------------------

// обработка кнопки поиска элемента в дереве
void __fastcall TForm1::findAndPrintButtonClick(TObject *Sender)
{
    ((void)Sender);

    this->searchResultsArea->Lines->Clear();                // очищаем вывод

    int key = StrToInt(this->findKeyEdit->Text);            // берём ключ для поиска из поля
    BSUIR::Tree *node = BSUIR::FindNodeByKey(root, key);    // Ищем ключ в дереве
    if (node)                                               // Если нашли, то выводим
    {
        String firstRow = "Found:";
        String secondRow = "Key:\t" + IntToStr(node->value);
        String thirdRow = "Value:\t" + node->caption;
        this->searchResultsArea->Lines->Add(firstRow);
        this->searchResultsArea->Lines->Add(secondRow);
        this->searchResultsArea->Lines->Add(thirdRow);
    }
    else
    {                                               // Либо сообщаем, что не нашли
        this->searchResultsArea->Lines->Add("No such key in tree :c");
    }
}
//---------------------------------------------------------------------------

// Обработка кнопки "найти и удалить"
void __fastcall TForm1::findAndEraseButtonClick(TObject *Sender)
{
    ((void)Sender);

    this->searchResultsArea->Lines->Clear();            // Очищаем вывод

    int key = StrToInt(this->findKeyEdit->Text);        // берём ключ
    bool result = BSUIR::RemoveFromTree(&root, key);    // удаляем по ключу

    String output;
    if (result)
        output = "Removed successfully";
    else
        output = "No such key in tree :c";
    this->searchResultsArea->Lines->Add(output);

    this->updateTreeView();
}
//---------------------------------------------------------------------------

// Обработка кнопки с обходом дерева
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

// Обработка кнопки с обходом дерева
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

// Обработка кнопки с обходом дерева
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

// Обработка кнопки с удалением дерева
void __fastcall TForm1::deleteButtonClick(TObject *Sender)
{
    ((void)Sender);
    BSUIR::DeleteTree(&root);
    this->updateTreeView();
    this->clearOutput();
    this->printToOutput("Tree was deleted.");
}
//---------------------------------------------------------------------------

// Обработка кнопки с ребалансировкой дерева
void __fastcall TForm1::rebalanceButtonClick(TObject *Sender)
{
    ((void)Sender);
    this->clearOutput();                // Очищаем вывод
    if (this->root == NULL)
    {
        this->printToOutput("Can't rebalance empty tree");
        return;
    }

    int treeSize = BSUIR::GetTreeSize(root);                    // Получаем размер дерева
    BSUIR::RecordList list = BSUIR::CreateRecordList(treeSize); // Создаём массив структур такого размера
    BSUIR::CreateListFromTree(list, root);                      // Заполняем его элементами из дерева
    BSUIR::Sort(list);                                          // Сортируем
    BSUIR::DeleteTree(&root);                                   // Удаляем дерево
    root = BSUIR::CreateTree(list);                             // Создаём новое дерево на основе массива

    this->printToOutput("The tree was rebalanced...");          // Выводим
    this->updateTreeView();
}
//---------------------------------------------------------------------------

// Обработка кнопки для очистки таблицы
void __fastcall TForm1::clearTableButtonClick(TObject *Sender)
{
    ((void)Sender);
    this->clearInput();    
}
//---------------------------------------------------------------------------

// Обработка кнопки для инициализации дерева значениями из таблицы
void __fastcall TForm1::initTreeButtonClick(TObject *Sender)
{
    ((void)Sender);
    BSUIR::RecordList list = this->getListFromInput();  // Получаем значения из таблицы
    BSUIR::Sort(list);                                  // сортируем
    if (this->treeIsInited()) BSUIR::DeleteTree(&root); // Если дерево какое-то было уже, то удаляем
    this->root = BSUIR::CreateTree(list);               // Создаём новое на основе массива
    this->updateTreeView();                             // Выводим
}
//---------------------------------------------------------------------------

// Обработка кнопки для подсчёта листьев
void __fastcall TForm1::leavesButtonClick(TObject *Sender)
{
    ((void)Sender);
    this->clearOutput();
    int numberOfLeaves = BSUIR::CountLeaves(root);
    String output = "The tree contains " + IntToStr(numberOfLeaves) + " leaves!";
    this->printToOutput(output);
}
//---------------------------------------------------------------------------

