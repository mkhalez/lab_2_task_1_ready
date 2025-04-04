#ifndef FILEMANAGER_H
#define FILEMANAGER_H


#include <QStandardItemModel>
#include <QString>
#include <QWidget>
#include "mydate.h"

class FileManager {
   public:
    FileManager();	// Изменили тип параметра на QWidget*
    // Остальные методы
    ~FileManager();

   public:
    void SetPath(QString path);
    QString GetPath();
    void ReplaceLineInFile(QString& filePath, int lineNumber, QString& newLine);
    QString path;
    void AppendLineToFile(QString& filePath, QString& newLine);
    //QString OpenFile();
    void ReadFromFile();
    void AddElementBool(bool*& tool, int& bool_size);
    void AddElement(MyDate*& dynamic_array, int& size);
    void Save();
    QStandardItemModel* model;
    void SetSize(int size);
    int GetSize();
    void SetBoolSize(int bool_size);
    int GetBoolSize();
    MyDate* GetList();
    bool* GetTool();
    void SetList();
    void SetTool(bool start, bool* new_array = nullptr);
    void MakeNullList();

   private:
    MyDate* list_of_date_;
    int size_;
    int bool_size_;
    bool* tool_;

    QString AddLeadingZeros(int number, int width);

    QWidget* parentWidget;
};

#endif	// FILEMANAGER_H
