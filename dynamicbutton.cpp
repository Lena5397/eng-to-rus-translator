#include "dynamicbutton.h"

DynamicButton::DynamicButton(QWidget *parent) :
    QPushButton(parent)
{

       QString text;

}

DynamicButton::~DynamicButton()
{

}

void DynamicButton::setStoredText(QString t)
{
   text = t;
}

/* Метод для возврата значения номера кнопки
 * */
QString DynamicButton::getText()
{
    return text;
}

