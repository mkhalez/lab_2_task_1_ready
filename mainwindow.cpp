#include "mainwindow.h"
#include <QFile>
#include <QFileDialog>
#include <QStandardItemModel>
#include <QTableView>
#include <ctime>
#include "ui_mainwindow.h"
#include "validstring.h"

const int kCols = 7;
const int kCol0 = 0;
const int kCol1 = 1;
const int kCol2 = 2;
const int kCol3 = 3;
const int kCol4 = 4;
const int kCol5 = 5;
const int kCol6 = 6;
const int kStartYear = 1900;
const int kDecimal = 10;


MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow)
//, list_of_date(nullptr)
//, tool(nullptr)
//, path("/home/mkh-alez/oaip/lab_2/task_1/example.txt")  // Инициализация path
{
    ui->setupUi(this);
    ui->currentDate->setReadOnly(true);
    ui->currentDate->setText(CurrentDate());


    Init(our_file_.GetPath());	// Передаем path в Init

    connect(ui->pushButton, &QPushButton::clicked, this,
            &MainWindow::Calculate);
    connect(ui->addButton, &QPushButton::clicked, this, &MainWindow::AddLine);
    connect(ui->saveButton, &QPushButton::clicked, this,
            &MainWindow::SaveHelper);
    connect(ui->openButton, &QPushButton::clicked, this,
            &MainWindow::DialogeWindow);
}

void MainWindow::Init(QString new_path) {
    our_file_.SetPath(std::move(new_path));

    our_file_.model = new QStandardItemModel(0, kCols);

    // установка заголовков таблицы
    our_file_.model->setHeaderData(kCol0, Qt::Horizontal, "Date");
    our_file_.model->setHeaderData(kCol1, Qt::Horizontal, "Next day");
    our_file_.model->setHeaderData(kCol2, Qt::Horizontal, "Previous day");
    our_file_.model->setHeaderData(kCol3, Qt::Horizontal, "Is leap");
    our_file_.model->setHeaderData(kCol4, Qt::Horizontal, "Number of week");
    our_file_.model->setHeaderData(kCol5, Qt::Horizontal, "Days till birthday");
    our_file_.model->setHeaderData(kCol6, Qt::Horizontal, "Duraction");

    ui->view->setModel(our_file_.model);


    our_file_.SetSize(1);
    our_file_.SetList();

    our_file_.SetBoolSize(0);
    our_file_.SetTool(true);


    our_file_.ReadFromFile();

    /*QFile inputFile(path);
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
    }*/


    //выравнивание таблицы по tableview
    QHeaderView* header_1 = ui->view->horizontalHeader();
    QHeaderView* header_2 = ui->view->verticalHeader();
    header_1->setSectionResizeMode(QHeaderView::Stretch);
    header_2->setSectionResizeMode(QHeaderView::Stretch);
}

MainWindow::~MainWindow() {
    delete ui;
}


/*void MainWindow::AddElement(MyDate* &dynamic_array, int& size)
{
    MyDate *new_array = new MyDate[size + 1];

    for(int i = 0; i < size; i++)
    {
        new_array[i] = dynamic_array[i];
    }
    delete[] dynamic_array;

    dynamic_array = new_array;

    size++;
}*/


/*void MainWindow::AddElementBool(bool* &tool, int& bool_size)
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
*/

void MainWindow::Calculate() {
    for (int i = 0; i < our_file_.GetSize(); i++) {
        MyDate coming_day;
        MyDate* pointer_to_list = our_file_.GetList();
        coming_day = pointer_to_list[i].NextDay();
        QString line = AddLeadingZeros(coming_day.GetDay(), 2) + "." +
                       AddLeadingZeros(coming_day.GetMonth(), 2) + "." +
                       AddLeadingZeros(coming_day.GetYear(), 4);
        QStandardItem* item = new QStandardItem(line);
        item->setTextAlignment(Qt::AlignCenter);  // Выравнивание по центру
        our_file_.model->setItem(i, 1, item);


        MyDate previous_day;
        previous_day = pointer_to_list[i].PreviousDay();
        line = AddLeadingZeros(previous_day.GetDay(), 2) + "." +
               AddLeadingZeros(previous_day.GetMonth(), 2) + "." +
               AddLeadingZeros(previous_day.GetYear(), 4);
        item = new QStandardItem(line);
        item->setTextAlignment(Qt::AlignCenter);  // Выравнивание по центру
        our_file_.model->setItem(i, kCol2, item);

        bool is_leap_day;
        is_leap_day = pointer_to_list[i].IsLeap();


        if (is_leap_day) {
            line = "Yes";
        } else {
            line = "No";
        }
        item = new QStandardItem(line);
        item->setTextAlignment(Qt::AlignCenter);  // Выравнивание по центру
        our_file_.model->setItem(i, kCol3, item);


        short number_of_week = pointer_to_list[i].WeekNumber();
        line = QString::number(number_of_week);
        item = new QStandardItem(line);
        item->setTextAlignment(Qt::AlignCenter);  // Выравнивание по центру
        our_file_.model->setItem(i, kCol4, item);

        int delta = pointer_to_list[i].Duration(
            pointer_to_list[(i + 1) % our_file_.GetSize()]);
        line = QString::number(delta);
        item = new QStandardItem(line);
        item->setTextAlignment(Qt::AlignCenter);  // Выравнивание по центру
        our_file_.model->setItem(i, kCol6, item);

        if (!(ui->lineEdit->text().isEmpty())) {
            ValidString check_valid;
            check_valid.SetInputDate(ui->lineEdit->text());

            try {
                if (!check_valid.ValidInputDate()) {
                    throw std::invalid_argument("Invalid date format or value");
                }


                line = ui->lineEdit->text();
                MyDate birthday = MyDate(line);
                int result = birthday.DaysTillYourBithday(pointer_to_list[i]);
                line = QString::number(result);
                item = new QStandardItem(line);
                item->setTextAlignment(
                    Qt::AlignCenter);  // Выравнивание по центру
                our_file_.model->setItem(i, kCol5, item);

            } catch (const std::invalid_argument& e) {
                pointer_to_list = nullptr;
                continue;
            }
        }

        pointer_to_list = nullptr;
    }
}

QString MainWindow::AddLeadingZeros(int number, int width) {
    return QString("%1").arg(number, width, kDecimal, QChar('0'));
}

void MainWindow::AddLine() {
    QList<QStandardItem*> new_row;
    new_row << new QStandardItem();

    // Добавляем строку в модель
    our_file_.model->appendRow(new_row);

    /*bool* tool_pointer = our_file.GetTool();
    int bool_size_tool = our_file.GetBoolSize();

    our_file.AddElementBool(tool_pointer, bool_size_tool);

    our_file.SetBoolSize(bool_size_tool);

    our_file.SetTool(false, tool_pointer);

    tool_pointer[bool_size_tool - 1] = false;
    tool_pointer = nullptr;*/
}

/*void MainWindow::Save()
{
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

            QString content_of_date = AddLeadingZeros(day, 2) + AddLeadingZeros(month, 2) + AddLeadingZeros(year, 4);
            if(content_of_date == value) continue;
            else
            {
                list_of_date[i] = MyDate(value);
                ReplaceLineInFile(path, i, value);
            }
        }
        else
        {
            AddElement(list_of_date, size);
            list_of_date[size - 1] = MyDate(value);
            AppendLineToFile(path, value);
        }
    }
    //empty line
    for(int i = 0; i < size; i++)
    {
        qDebug() << list_of_date[i].GetYear();
    }

}*/

QString MainWindow::CurrentDate() {
    std::time_t now = std::time(nullptr);
    std::tm* local_time = std::localtime(&now);

    int day = local_time->tm_mday;
    int month = local_time->tm_mon + 1;
    int year = local_time->tm_year + kStartYear;
    return AddLeadingZeros(day, 2) + "." + AddLeadingZeros(month, 2) + "." +
           AddLeadingZeros(year, 4);
}

/*
void MainWindow::ReplaceLineInFile(const QString& filePath, int lineNumber, const QString& newLine) {
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

void MainWindow::AppendLineToFile(const QString& filePath, const QString& newLine) {
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
*/

void MainWindow::DialogeWindow() {
    // Создаем диалог выбора файла
    QString file_path = QFileDialog::getOpenFileName(
        this,				 // Родительское окно
        tr("Открыть файл"),	 // Заголовок диалога
        "",	 // Начальная директория (пустая строка означает текущую директорию)
        tr("Текстовые файлы (*.txt);;Все файлы (*)")  // Фильтр файлов
    );

    // Если пользователь выбрал файл
    if (!file_path.isEmpty()) {
        qDebug() << "Выбранный файл:" << file_path;

        MyDate* pointer_list = our_file_.GetList();
        bool* pointer_tool = our_file_.GetTool();

        // Очищаем текущие данные


        if (pointer_list) {
            delete[] pointer_list;
            pointer_list = nullptr;
        }


        if (pointer_tool) {
            delete[] pointer_tool;
            pointer_tool = nullptr;
        }

        our_file_.MakeNullList();

        our_file_.model->clear();

        // Инициализируем данные из нового файла
        our_file_.SetPath(file_path);
        Init(our_file_.GetPath());
    } else {
        qDebug() << "Файл не выбран.";
    }
}

void MainWindow::SaveHelper() {
    our_file_.Save();
    QHeaderView* header_1 = ui->view->horizontalHeader();
    QHeaderView* header_2 = ui->view->verticalHeader();
    header_1->setSectionResizeMode(QHeaderView::Stretch);
    header_2->setSectionResizeMode(QHeaderView::Stretch);
}
