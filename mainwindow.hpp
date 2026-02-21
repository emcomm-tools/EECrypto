#ifndef MAINWINDOW_HPP_
#define MAINWINDOW_HPP_

#include <QMainWindow>
#include <QTextEdit>
#include <QLineEdit>
#include "eecrypto.hpp"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

private slots:
    void onCipher();
    void onDecipher();
    void onClear();
    void onAbout();

private:
    bool setKey();
    QTextEdit *textEdit;
    QLineEdit *passphraseEdit;
    EECrypto crypto;
};

#endif /* MAINWINDOW_HPP_ */
