#ifndef DUMB_NICKNAME_GENERATOR_WINDOW_H
#define DUMB_NICKNAME_GENERATOR_WINDOW_H

#include <QPushButton>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QEventLoop>
#include <QSlider>
#include <cmath>
#include "model/model.h"


class Window : public QWidget
{
public:
    explicit Window(QWidget *parent = nullptr);
private Q_SLOTS:
    void generate();
    void updatePrompt(const QString &newPrompt);
    void updateValue(int newValue);
private:
    GenerativeModel model;
    QPushButton *buttonGenerate;
    QString prompt;
    QLineEdit *inputField;
    QLabel *outputText;
    QSlider *noiseSlider;
    QLabel *noiseLabel;
    float noiseValue;
};

#endif //DUMB_NICKNAME_GENERATOR_WINDOW_H
