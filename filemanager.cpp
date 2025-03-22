#include "filemanager.h"
#include "validstring.h"
#include <QFile>
#include <QStandardItemModel>
#include <QTableView>
#include <ctime>
#include <QFileDialog>

FileManager::FileManager() {
    size = 1;

    list_of_date = new MyDate[size];

    bool_size = 0;
    tool = new bool[bool_size];
    path = "/home/mkh-alez/oaip/lab_2/task_1/example.txt";
}

FileManager::~FileManager()
{
    delete[] list_of_date;
}

void FileManager::SetPath(QString path)
{
    this->path = path;
}

QString FileManager::GetPath()
{
    return path;
}

void FileManager::ReadFromFile()
{
    QFile inputFile(path);
    if(inputFile.open(QIODevice::ReadOnly))
    {
        QTextStream in(&inputFile);
        int i = 0;
        while(!in.atEnd())
        {

            QString line = in.readLine();

            if(i > 0) AddElement(list_of_date, size);
            list_of_date[i] = MyDate(line);


            QList<QStandardItem*> newRow;
            newRow << new QStandardItem(line);

            // Добавляем строку в модель
            model->appendRow(newRow);

            AddElementBool(tool, bool_size);
            tool[i] = true;

            i++;
        }

        inputFile.close();
    }
}

void FileManager::AddElement(MyDate* &dynamic_array, int& size)
{
    MyDate *new_array = new MyDate[size + 1];

    for(int i = 0; i < size; i++)
    {
        new_array[i] = dynamic_array[i];
    }
    delete[] dynamic_array;

    dynamic_array = new_array;

    size++;
}


void FileManager::AddElementBool(bool* &tool, int& bool_size)
{
    bool *new_tool = new bool[bool_size + 1];

    for(int i = 0; i < bool_size; i++)
    {
        new_tool[i] = tool[i];
    }
    delete[] tool;

    tool = new_tool;
    bool_size++;
}

QString FileManager::AddLeadingZeros(int number, int width) {
    return QString("%1").arg(number, width, 10, QChar('0'));
}


void FileManager::Save()
{
    /*for(int i = 0; i < bool_size; i++)
    {
        qDebug() << tool[i];
    }
*/
    /*for(int i = 0; i < size; i++)
    {
        qDebug() << AddLeadingZeros(list_of_date[i].GetDay(), 2) + "." + AddLeadingZeros(list_of_date[i].GetMonth(), 2) + "." + AddLeadingZeros(list_of_date[i].GetYear(), 4);
    }*/

    //qDebug() << model->rowCount();
        for(int i = 0; i < model->rowCount(); i++)
    {
        QStandardItem* item = model->item(i, 0);
        QString value = item->text();


        if(tool[i] == true)
        {
            int day = list_of_date[i].GetDay();
            int month = list_of_date[i].GetMonth();
            int year = list_of_date[i].GetYear();

            QString content_of_date = AddLeadingZeros(day, 2) + "." + AddLeadingZeros(month, 2) + "." + AddLeadingZeros(year, 4);


            if(content_of_date == value) continue;
            else
            {
                list_of_date[i] = MyDate(value);
                ReplaceLineInFile(path, i, value);
            }
        }
        else
        {

            if(item && item->text().isEmpty())
            {
                model->removeRow(i);
                i--;
            }
            else
            {
                ValidString check_valid;
                check_valid.SetInputDate(value);

                try{
                    if(!check_valid.ValidInputDate())
                    {
                        throw std::invalid_argument("Invalid date format or value");
                    }
                    AddElement(list_of_date, size);
                    list_of_date[size - 1] = MyDate(value);
                    //AddElementBool(tool, bool_size);
                    tool[bool_size - 1] = true;
                    AppendLineToFile(path, value);


                } catch (const std::invalid_argument& e){

                    model->removeRow(i);
                    i--;

                }
            }

        }
    }

    //empty line
    /*for(int i = 0; i < bool_size; i++)
    {
        qDebug() << tool[i];
    }
    qDebug() << "------";*/

}

void FileManager::ReplaceLineInFile(QString& filePath, int lineNumber, QString& newLine) {
    // Открываем файл для чтения и записи
    QFile file(filePath);
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        qWarning() << "Не удалось открыть файл:" << filePath;
        return;
    }

    QTextStream stream(&file);
    int currentLine = 0;
    int startPos = 0;

    // Ищем нужную строку
    while (!stream.atEnd()) {
        startPos = stream.pos(); // Запоминаем начало строки
        QString line = stream.readLine(); // Читаем строку
        if (currentLine == lineNumber) {
            // Проверяем, что новая строка имеет ту же длину
            if (line.size() != newLine.size()) {
                qWarning() << "Новая строка должна иметь ту же длину, что и старая.";
                file.close();
                return;
            }

            // Перемещаемся в начало строки
            file.seek(startPos);

            // Записываем новую строку
            stream << newLine;

            // Закрываем файл
            file.close();
            return;
        }
        currentLine++; // Переходим к следующей строке
    }

    // Если строка не найдена, добавляем новую строку в конец файла
    if (currentLine == lineNumber) {
        stream << newLine << "\n"; // Добавляем новую строку
    } else {
        qWarning() << "Некорректный номер строки:" << lineNumber;
    }

    file.close();
}

void FileManager::AppendLineToFile(QString& filePath, QString& newLine) {
    // Открываем файл для добавления данных
    QFile file(filePath);
    if (!file.open(QIODevice::Append | QIODevice::Text)) {
        qWarning() << "Не удалось открыть файл для добавления:" << filePath;
        return ;
    }

    // Записываем новую строку в конец файла
    QTextStream out(&file);
    out << newLine << "\n"; // Добавляем новую строку и символ новой строки
    file.close();

    return;
}

/*QString FileManager::OpenFile() {
    // Создаем диалог выбора файла
    QString filePath = QFileDialog::getOpenFileName(
        parentWidget,                   // Родительское окно
        tr("Открыть файл"),     // Заголовок диалога
        "",                     // Начальная директория (пустая строка означает текущую директорию)
        tr("Текстовые файлы (*.txt);;Все файлы (*)") // Фильтр файлов
        );

    // Если пользователь выбрал файл
    if (!filePath.isEmpty()) {
        qDebug() << "Выбранный файл:" << filePath;

        // Очищаем текущие данные
        if (list_of_date) {
            delete[] list_of_date;
            list_of_date = nullptr;
        }
        if (tool) {
            delete[] tool;
            tool = nullptr;
        }

        model->clear();

        // Инициализируем данные из нового файла
        path = filePath;
        return path;
    } else {
        qDebug() << "Файл не выбран.";
        return "";
    }
}*/



void FileManager::SetSize(int size)
{
    this->size = size;
}

int FileManager::GetSize()
{
    return size;
}

void FileManager::SetBoolSize(int bool_size)
{
    this->bool_size = bool_size;
}

int FileManager::GetBoolSize()
{
    return bool_size;
}

MyDate* FileManager::GetList()
{
    return list_of_date;
}

void FileManager::SetList()
{
    list_of_date = new MyDate[size];
}

void FileManager::SetTool(bool start, bool* new_array)
{
    if(start)
    {
        tool = new bool[bool_size];
    }
    else
    {
        tool = new_array;
    }
}

bool* FileManager::GetTool()
{
    return tool;
}

void FileManager::MakeNullList()
{
    list_of_date = nullptr;
    tool = nullptr;
}



















