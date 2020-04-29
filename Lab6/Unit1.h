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

namespace BSUIR
{

/// Описание структуры вершины дерева
struct Tree                    
{
    int value;          // ключ
    String caption;     // значение
    Tree* left;         // указатель на левого ребёнка
    Tree* right;        // и на правого
};

/// \brief Функция для создания нового корня дерева
/// \param value - ключ корня
/// \param caption - значение корня
/// \return Указатель на новый корень
Tree* InitTree(int value, String caption);


/// \brief Функция для удаления дерева
/// \param root - указатель на указатель на корень дерева
void DeleteTree(Tree **root);


/// \brief Функция для добавления элемента в дерево
/// \param root - указатель на корень дерева
/// \param value - ключ нового элемента
/// \param caption - значение нового элемента
void InsertIntoTree(Tree *root, int value, String caption);


/// \brief Функция получения размера дерева
/// \param root - указатель на корень дерева
/// \return количество вершин в дереве
int GetTreeSize(Tree *root);


/// \brief Функция поиска элемента в дереве по ключу
/// \param root - указатель на корень
/// \param key  - ключ для поиска
/// \return Если элемент найден, то вернём указатель на него. Иначе - NULL
Tree* FindNodeByKey(Tree *root, int key);


/// \brief Функция удаления элемента из дерева по ключу
/// \param root - указатель на указатель на корень
/// \param key  - ключ элемента для удаления
/// \return true, если элемент найден и удалён, иначе - false
bool RemoveFromTree(Tree **root, int key);


/// \brief Функция, которая строит представление дерева в виде текста
/// \param root - указатель на начало дерева
/// Остальные параметры используются только внутри
/// \return Возвращает массив строк с представлением дерева в виде текста
std::vector<String> GetTreeView(Tree *root, String prefix = "", bool isLeft = false);


/// \brief Функция для подсчёта листьев в дереве
/// \param root - указатель на корень дерева
/// \return Количество листьев в дереве
int CountLeaves(Tree *root);


/// Вспомогательная структура для сортировок
/// Выглядит, как и вершины дерева, только 
/// Без указателей на детей
struct Record
{
    int key;
    String caption;
};


/// Структура для хранения массива вспомогательных структур
struct RecordList
{
    Record* data;   // Указатель на массив
    int size;       // Размер массива
};


/// \brief Функция для создания массива структур
/// \param size - размер массива
/// \return RecordList размером в size
RecordList CreateRecordList(int size);


/// \brief Функция для удаления массива структур
/// \param list - массив для удаления
void RemoveRecordList(RecordList &list);


/// \brief Функция для сортировки массива структур
/// \param list - массив для сортировки
void Sort(RecordList list);


/// \brief Функция для создания дерева из массива структур
/// \param list - массив структур, из которого нужно сделать дерево
/// Остальные параметры служебные
/// \return Указатель на новое дерево
Tree *CreateTree(RecordList list, int l = 0, int r = -1);


/// \brief Функция для создания массива структур по заданному дереву
/// \param list - массив структур, куда будут помещены элементы
/// \param root - указатель на корень дерева
/// Остальные параметры служебные
int CreateListFromTree(RecordList list, Tree *root, int lastElement = 0);

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
    void __fastcall deleteButtonClick(TObject *Sender);
    void __fastcall rebalanceButtonClick(TObject *Sender);
    void __fastcall clearTableButtonClick(TObject *Sender);
    void __fastcall initTreeButtonClick(TObject *Sender);
    void __fastcall leavesButtonClick(TObject *Sender);
private:	// User declarations

    /// Указатель на корень дерева
    BSUIR::Tree *root;

    /// \brief Функция для проверки, инициализировано ли дерево
    /// \return true, если инициализировано, иначе false
    bool treeIsInited() const;

    /// \brief Функция для обновления представления дерева в виде текста на форме
    void updateTreeView();

    /// \brief Функция для очистки поля с выводом на форме
    void clearOutput();

    /// \brief Функция для добавления новой строки в поле вывода на форме
    void printToOutput(const String &str);

    /// Функции для обхода дерева в разном порядке
    /// Везде передаётся указатель на корень дерева
    /// Ответ пишется на форме в поле вывода
    void preOrderTraversal(BSUIR::Tree *start);
    void postOrderTraversal(BSUIR::Tree *start);
    void inOrderTraversal(BSUIR::Tree *start);

    /// Функция для очистки таблицы для ввода списка элементов
    void clearInput();

    /// Функция, которая конвертирует данные из таблицы в массив структур
    /// для дальнейшего добавления в дерево
    BSUIR::RecordList getListFromInput();
public:		// User declarations
    __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
