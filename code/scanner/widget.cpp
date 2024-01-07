#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <fstream>
#include <QTextCodec>
#pragma execution_character_set("utf-8")
using namespace std;


QString result;

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

const string keywords[] = {
    "asm","else","new","this","auto","enum","operator","throw","bool","explicit","private","true",
    "break","export","protected","try","case","extern","public","typedef","catch","false","register","typerid",
    "char","float","reinterpret_cast","typename","class","for","return","union","const","friend","short","unsigned",
    "const_cast","goto","signed","using","continue","if","sizeof","virtual","default","inline","static","void",
    "delete","int","static_cast","volatile","do","long","struct","wchar_t","double","mutable","switch","while",
    "dynamic_cast","namespace","template","main","cout","cin","using","namespace","std"
};

const char operators[] = {
    '+', '-', '*', '/', '=', '!', '>', '<', '|','&','^','~','?','%'
};

bool isDigit(char ch) {
    if (ch >= '0' && ch <= '9') {
        return true;
    }
    return false;
}

bool isAlpha(char ch) {
    if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || ch == '_') {
        return true;
    }
    return false;
}

bool isOperator(char ch) {

    for (char i : operators) {
        if (ch == i) {
            return true;
        }
    }

    return false;
}

bool isDelimiter(char ch) {
    char delimiter[] = {
            '(',   ')',   ',',   ';',  '{',  '}', '#', '.', ':','[',']'
    };

    for (char i : delimiter) {
        if (ch == i) {
            return true;
        }
    }

    return false;
}

bool isKeyword(string token) {

    for (string a : keywords) {
        if (token.compare(a) == 0) {
            return true;
        }
    }

    return false;
}

bool is0X(char ch)
{
    if ((ch >= 'a' && ch <= 'f') || (ch >= 'A' && ch <= 'F')) {
        return true;
    }
    return false;
}

void numToken(char ch, ifstream& inputFile)
{
    char c;
    string numberToken;
    numberToken += ch;
    while (inputFile.get(c))
    {
        // 普通整型
        if (isDigit(c))
        {
            numberToken += c;
            continue;
        }
        // 浮点型+科学计数法
        else if (c == '.')
        {
            numberToken += c;
            while (inputFile.get(c))
            {
                if (isDigit(c))
                {
                    numberToken += c;
                    continue;
                }
                else if (c == 'e' || c == 'E')
                {
                    numberToken += c;
                    inputFile.get(c);
                    if (c == '+' || c == '-')
                    {
                        numberToken += c;
                    }
                    while (inputFile.get(c))
                    {
                        if (isDigit(c))
                        {
                            numberToken += c;
                            continue;
                        }
                        break;
                    }
                }
                break;
            }
        }
        // 整型的科学计数法
        else if (c == 'e' || c == 'E')
        {
            numberToken += c;
            inputFile.get(c);
            if (c == '+' || c == '-')
            {
                numberToken += c;
            }
            while (inputFile.get(c))
            {
                if (isDigit(c))
                {
                    numberToken += c;
                    continue;
                }
                break;
            }
        }
        // 十六进制
        else if (c == 'x' || c == 'X')
        {
            numberToken += c;
            while (inputFile.get(c))
            {
                if (isDigit(c) || is0X(c))
                {
                    numberToken += c;
                    continue;
                }
                break;
            }
        }
        break;
    }
    inputFile.unget(); // 回退一格
    cout << numberToken << " 数字" << endl;
    result.append(QString::fromStdString(numberToken + " 数字\n"));
}

void alphaToken(char ch, ifstream& inputFile) {
    string alpha_token_value;
    alpha_token_value += ch;
    char c = inputFile.peek();

    //后面字符是字母或数字
    while (isAlpha(c) || isDigit(c))
    {
        alpha_token_value += c;
        inputFile.ignore();
        c = inputFile.peek();
    }

    //查表,若不是保留字则是标识符
    if (isKeyword(alpha_token_value)) {
        cout << alpha_token_value << " 关键字" << endl;
        result.append(QString::fromStdString(alpha_token_value + " 关键字\n"));
    }
    else {
        cout << alpha_token_value << " 标识符" << endl;
        result.append(QString::fromStdString(alpha_token_value + " 标识符\n"));
    }
}

void operatorToken(char ch, ifstream& inputFile) {
    string operatorToken;
    operatorToken += ch;

    char nextChar = inputFile.peek();


    if (nextChar == '=')  // 各种X=
    {
        operatorToken += "=";
        inputFile.ignore();
    }
    else if (ch == '>' && nextChar == '>')
    {
        operatorToken = ">>";
        inputFile.ignore();
        if (inputFile.peek() == '=') {
            operatorToken = ">>=";
            inputFile.ignore();
        }
    }
    else if (ch == '<' && nextChar == '<')
    {
        operatorToken = "<<";
        inputFile.ignore();
        if (inputFile.peek() == '=') {
            operatorToken = "<<=";
            inputFile.ignore();
        }
    }
    else if (ch == '&' && nextChar == '&')
    {
        operatorToken = "&&";
        inputFile.ignore();
    }
    else if (ch == '|' && nextChar == '|')
    {
        operatorToken = "||";
        inputFile.ignore();
    }
    else if (ch == '-' && nextChar == '>')
    {
        operatorToken = "->";
        inputFile.ignore();
    }
    else if (ch == '+' && nextChar == '+')
    {
        operatorToken = "++";
        inputFile.ignore();
    }
    else if (ch == '-' && nextChar == '-')
    {
        operatorToken = "--";
        inputFile.ignore();
    }

    cout << operatorToken << " 运算符" << endl;
    result.append(QString::fromStdString(operatorToken + " 运算符\n"));
}

int startCharType(char ch) {
    if (isDigit(ch)) {
        return 1;
    }
    else if (isAlpha(ch)) {
        return 2;
    }
    else if (isDelimiter(ch)) {
        return 3;
    }
    else if (isOperator(ch)) {
        return 4;
    }
    else if (ch == '\n') {
        return 6;
    }
    else if (ch == '\"') {
        return 7;
    }
    else if (ch == '\'') {
        return 8;
    }
    else {
        return 5;
    }
}


void Widget::on_pushButton_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this, tr("选择文件"), QDir::homePath(), tr("C++源文件 (*.cpp *.c);;文本文件 (*.txt);;所有文件 (*.*)"));

    if (!filePath.isEmpty())
    {
        result.clear();
        ifstream inputFile;
        QTextCodec *code = QTextCodec::codecForName("GB2312");

        string selectedFile = code->fromUnicode(filePath.toStdString().c_str()).data();
        inputFile.open(selectedFile.c_str(),ios::in);


//        cout<<filePath.toStdString();
//        ifstream inputFile(filePath.toStdString());
        if (!inputFile) {
            QMessageBox::critical(this, "错误信息", "导入错误！无法打开文件，请检查路径和文件是否被占用！");
            cerr << "Error opening file." << endl;
        }

        char c;
        string currentWord;

        while (inputFile.get(c))
        {
            // 首先识别注释
            if (c == '/')
            {
                currentWord += c;
                if (inputFile.peek() == '/')
                {   // 单行注释
                    string currentLine;
                    getline(inputFile, currentLine);
                    currentWord += currentLine;
                    cout << currentWord << " 注释" << endl;
                    result.append(QString::fromStdString(currentWord + " 注释\n"));
                    currentWord.clear();
                    continue; // 继续下一轮循环
                }
                else if (inputFile.peek() == '*')
                {   // 多行注释
                    inputFile.ignore(); // 忽略掉'*'
                    currentWord += '*';
                    bool commentClosed = false;
                    while (inputFile.get(c))
                    {
                        currentWord += c;
                        if (c == '*' && inputFile.peek() == '/') {
                            inputFile.ignore(); // 忽略掉'*'和'/'
                            currentWord += '/';
                            commentClosed = true;
                            break;
                        }
                    }
                    if (!commentClosed)
                    {
                        cerr << "Error: Unclosed multi-line comment." << endl;
                    }
                    else
                    {
                        cout << currentWord << " 注释" << endl;
                        result.append(QString::fromStdString(currentWord + " 注释\n"));
                    }
                    currentWord.clear();
                    continue; // 继续下一轮循环
                }
                else
                {
                    operatorToken(c, inputFile);
                    currentWord.clear();
                }
            }
            // 头文件
            else if (currentWord.empty() && c == '#') {
                cout << "#" << "\t特殊符号" << endl;
                result.append(QString::fromStdString("# 特殊符号\n"));
                currentWord.clear();
                while (inputFile.get(c) && (c != '<' && c != '\"')) {
                    currentWord += c;
                }
                cout << currentWord << "\t关键字" << endl;
                result.append(QString::fromStdString(currentWord + " 关键字\n"));
                currentWord.clear();
                currentWord += c;
                while (inputFile.get(c) && (c != '>' && c != '\"')) {
                    currentWord += c;
                }
                currentWord += c;
                cout << currentWord << "\t特殊符号" << endl;
                result.append(QString::fromStdString(currentWord + " 特殊符号\n"));
                inputFile.get(c);
                currentWord.clear();
            }
            else
            {
                switch (startCharType(c))
                {
                case 1: //数字
                    numToken(c, inputFile);
                    break;
                case 2: //字母
                    alphaToken(c, inputFile);
                    break;
                case 3:// 特殊字符
                    currentWord += c;
                    cout << c << " 特殊字符" << endl;
                    result.append(QString::fromStdString(currentWord + " 特殊字符\n"));
                    currentWord.clear();
                    break;
                case 4:
                    operatorToken(c, inputFile);
                    break;
                case 7: //串
                    currentWord += c;
                    while (inputFile.get(c) && (c != '\"')) {
                        currentWord += c;
                    }
                    currentWord += c;
                    cout << currentWord << " 字符串" << endl;
                    result.append(QString::fromStdString(currentWord + " 字符串\n"));
                    currentWord.clear();
                    break;
                case 8:
                    currentWord += c;
                    while (inputFile.get(c) && (c != '\"')) {
                        currentWord += c;
                    }
                    currentWord += c;
                    cout << currentWord << " 单字符" << endl;
                    result.append(QString::fromStdString(currentWord + " 单字符\n"));
                    currentWord.clear();
                    break;
                default:
                    break;
                }
            }
        }
        ui->plainTextEdit->setPlainText(result);
    }
}




void Widget::on_pushButton_2_clicked()
{
    // 保存结果到文本文件
    QString saveFilePath = QFileDialog::getSaveFileName(this, tr("保存结果文件"), QDir::homePath(), tr("文本文件 (*.txt)"));
    if (!saveFilePath.isEmpty() && !result.isEmpty()) {
        QFile outputFile(saveFilePath);
        if (outputFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream stream(&outputFile);
            stream << result;
            outputFile.close();
            QMessageBox::about(this, "提示","导出成功！");
        }
    }
    else if(result.isEmpty())
    {
        QMessageBox::warning(this, tr("提示"), tr("结果为空，请重试！"));
    }
}

