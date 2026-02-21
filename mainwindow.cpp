#include "mainwindow.hpp"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QMessageBox>
#include <QApplication>
#include <QClipboard>
#include <QStatusBar>
#include <QCheckBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("ET-Crypto");
    resize(600, 400);

    setStyleSheet("QMainWindow { border: 2px solid #888; }");

    QWidget *central = new QWidget(this);
    setCentralWidget(central);

    QVBoxLayout *layout = new QVBoxLayout(central);
    layout->setContentsMargins(10, 10, 10, 10);

    QHBoxLayout *passLayout = new QHBoxLayout();
    passphraseEdit = new QLineEdit(this);
    passphraseEdit->setPlaceholderText("Enter passphrase...");
    passphraseEdit->setEchoMode(QLineEdit::Normal);
    passLayout->addWidget(passphraseEdit);

    QCheckBox *showPass = new QCheckBox("Show passphrase", this);
    showPass->setChecked(true);
    connect(showPass, &QCheckBox::toggled, this, [this](bool checked) {
        passphraseEdit->setEchoMode(checked ? QLineEdit::Normal : QLineEdit::Password);
    });
    passLayout->addWidget(showPass);
    layout->addLayout(passLayout);

    textEdit = new QTextEdit(this);
    textEdit->setPlaceholderText("Enter text to cipher or paste cipher text to decipher...");
    layout->addWidget(textEdit);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    QPushButton *cipherBtn = new QPushButton("Cipher", this);
    QPushButton *decipherBtn = new QPushButton("Decipher", this);
    QPushButton *clearBtn = new QPushButton("Clear", this);
    QPushButton *aboutBtn = new QPushButton("About", this);
    buttonLayout->addWidget(cipherBtn);
    buttonLayout->addWidget(decipherBtn);
    buttonLayout->addWidget(clearBtn);
    buttonLayout->addWidget(aboutBtn);
    layout->addLayout(buttonLayout);

    connect(cipherBtn, &QPushButton::clicked, this, &MainWindow::onCipher);
    connect(decipherBtn, &QPushButton::clicked, this, &MainWindow::onDecipher);
    connect(clearBtn, &QPushButton::clicked, this, &MainWindow::onClear);
    connect(aboutBtn, &QPushButton::clicked, this, &MainWindow::onAbout);

    statusBar()->showMessage("Ready");
}

bool MainWindow::setKey()
{
    QString str = passphraseEdit->text();
    if (str.isEmpty()) {
        QMessageBox::warning(this, "Error", "Enter a passphrase to cipher or decipher your text!");
        return false;
    }
    crypto.MakeKey(&str);
    return true;
}

void MainWindow::onCipher()
{
    QString plain = textEdit->toPlainText();
    if (plain.isEmpty()) {
        QMessageBox::warning(this, "Error", "No text to cipher!");
        return;
    }
    if (!setKey())
        return;

    QString cipher;
    cipher.reserve((plain.length() * 4) + 2);
    crypto.CipherText(&plain, &cipher);

    textEdit->setPlainText(cipher);

    QApplication::clipboard()->setText(cipher);
    statusBar()->showMessage("Text ciphered and copied to clipboard");
}

void MainWindow::onDecipher()
{
    QString cipher = textEdit->toPlainText();
    if (cipher.isEmpty()) {
        QMessageBox::warning(this, "Error", "No text to decipher!");
        return;
    }
    if (!setKey())
        return;

    QString plain;
    if (crypto.DecipherText(&cipher, &plain)) {
        textEdit->setPlainText(plain);
        statusBar()->showMessage("Text deciphered");
    } else {
        QMessageBox::warning(this, "Error",
            "Cannot decipher — invalid cipher text or wrong passphrase.");
    }
}

void MainWindow::onAbout()
{
    QMessageBox msgBox(this);
    msgBox.setWindowTitle("About ET-Crypto");
    msgBox.setTextFormat(Qt::RichText);
    msgBox.setText(
        "<h3>ET-Crypto</h3>"
        "<p>Symmetric text encryption tool using the EECrypto algorithm. "
        "Cipher and decipher text messages using a shared passphrase.</p>"
        "<hr>"
        "<p><b>RF Encryption Warning (Canada / USA)</b></p>"
        "<p>Amateur Radio regulations prohibit transmitting encrypted "
        "communications intended to obscure their meaning. "
        "When using ET-Crypto over RF, operators <b>must</b> publish "
        "their passphrase and comply with all applicable laws and "
        "regulations (Industry Canada RBR-4 / FCC Part 97).</p>"
        "<p><b>Recommended practice:</b> Use the destination station's "
        "callsign as the passphrase.</p>"
        "<hr>"
        "<p>The EECrypto algorithm source code is open and publicly "
        "available on GitHub:<br>"
        "<a href=\"https://github.com/emcomm-tools/EECrypto\">"
        "https://github.com/emcomm-tools/EECrypto</a></p>"
        "<hr>"
        "<p><b>Author:</b> Sylvain Deguire (VA2OPS)<br>"
        "<b>Version:</b> 1.0</p>");
    msgBox.exec();
}

void MainWindow::onClear()
{
    if (QMessageBox::question(this, "Confirm",
            "Wipe all text, passphrase, and clipboard?",
            QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes) {
        textEdit->clear();
        passphraseEdit->clear();
        QApplication::clipboard()->clear();
        statusBar()->showMessage("Cleared");
    }
}
