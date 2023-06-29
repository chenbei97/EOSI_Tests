#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QComboBox>
#include <QVBoxLayout>
#include <QDateTime>
#include <QImage>
#include <QVector>
#include <QTextEdit>
#include <QCursor>
#include <QTextDocument>

class MainWindow : public QWidget
{
    Q_OBJECT
private:
    QComboBox * box;
    QTextEdit * edit;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void showInfo(int index);
};
#endif // MAINWINDOW_H
