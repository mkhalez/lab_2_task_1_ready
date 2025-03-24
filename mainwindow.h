#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include "filemanager.h"


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

   public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

   private:
    Ui::MainWindow* ui;
    //void AddElement(MyDate* &dynamic_array, int &size);
    //MyDate* list_of_date;
    //int size;
    //int bool_size;
    QStandardItemModel* model_window_;
    QString AddLeadingZeros(int number, int width);
    //bool* tool;
    //void AddElementBool(bool* &tool, int &bool_size);
    QString CurrentDate();
    //void ReplaceLineInFile(const QString& filePath, int lineNumber, const QString& newLine);
    //QString path;
    //void AppendLineToFile(const QString& filePath, const QString& newLine);
    //void OpenFile();
    void Init(QString path);
    //void OpenFileAndInit();
    FileManager our_file_;


   private slots:
    void Calculate();
    void AddLine();
    void DialogeWindow();
    void SaveHelper();
};
#endif	// MAINWINDOW_H
