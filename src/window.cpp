/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/


#include <glwidget.hpp>
#include <window.hpp>
#include <mainwindow.hpp>
#include <QSlider>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QKeyEvent>
#include <QPushButton>
#include <QDesktopWidget>
#include <QApplication>
#include <QMessageBox>
#include <QComboBox>
#include <QAction>

Window::Window(MainWindow *mw)
    : mainWindow(mw)
{
    glWidget = new GLWidget;
    glWidget->setSphereModel(GLWidget::MODEL::UV_ICOSAHEDRON);

    xSlider = createSlider();
    ySlider = createSlider();
    zSlider = createSlider();
    subSlider = createSubSlider();

    connect(xSlider, &QSlider::valueChanged, glWidget, &GLWidget::setXRotation);
    connect(glWidget, &GLWidget::xRotationChanged, xSlider, &QSlider::setValue);
    connect(ySlider, &QSlider::valueChanged, glWidget, &GLWidget::setYRotation);
    connect(glWidget, &GLWidget::yRotationChanged, ySlider, &QSlider::setValue);
    connect(zSlider, &QSlider::valueChanged, glWidget, &GLWidget::setZRotation);
    connect(glWidget, &GLWidget::zRotationChanged, zSlider, &QSlider::setValue);
    connect(subSlider, &QSlider::valueChanged, glWidget, &GLWidget::setSubdivision);
    
    box = createComboBox(glWidget);
    connect(box, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Window::ShapeSelectorIndexChanged);    
    
    QVBoxLayout *mainLayout = new QVBoxLayout;
    QHBoxLayout *container = new QHBoxLayout;
    QVBoxLayout *controlsLayout = new QVBoxLayout;
    QHBoxLayout *slidersLayout = new QHBoxLayout;
    slidersLayout->addWidget(xSlider);
    slidersLayout->addWidget(ySlider);
    slidersLayout->addWidget(zSlider);
    QWidget *sliders = new QWidget;
    sliders->setLayout(slidersLayout);    
    
    controlsLayout->addWidget(sliders);
    controlsLayout->addWidget(box);
    controlsLayout->addWidget(subSlider);
    QWidget *controls = new QWidget;
    controls->setLayout(controlsLayout);    
    
    container->addWidget(glWidget);
    container->addWidget(controls);
    
    QWidget *w = new QWidget;
    w->setLayout(container);
    mainLayout->addWidget(w);

    setLayout(mainLayout);

    xSlider->setValue(15 * 16);
    ySlider->setValue(345 * 16);
    zSlider->setValue(0 * 16);

    setWindowTitle(tr("Hello GL"));
}

QSlider *Window::createSlider()
{
    QSlider *slider = new QSlider(Qt::Vertical);
    slider->setRange(0, 360 * 16);
    slider->setSingleStep(16);
    slider->setPageStep(15 * 16);
    slider->setTickInterval(15 * 16);
    slider->setTickPosition(QSlider::TicksRight);
    return slider;
}

QSlider *Window::createSubSlider()
{
    QSlider *slider = new QSlider(Qt::Horizontal);
    slider->setRange(0, 100);
    slider->setSingleStep(1);
    slider->setPageStep(1);
    slider->setTickInterval(5);
    slider->setTickPosition(QSlider::TicksBelow);
    return slider;
}

QComboBox *Window::createComboBox(GLWidget *widget)
{
    QComboBox *box = new QComboBox(this);
    firstAction = new QAction(this);
    firstAction->setText("UV Sphere");
    secondAction = new QAction(this);
    secondAction->setText("Logo");
    thirdAction = new QAction(this);
    thirdAction->setText("Icosahedron");
    
    connect(firstAction, &QAction::triggered,
            [=]( ) {
                widget->setSphereModel(GLWidget::MODEL::UV_SPHERE);
                widget->update();                
            });
    connect(secondAction, &QAction::triggered,
            [=]( ) {
                widget->setSphereModel(GLWidget::MODEL::LOGO);
                widget->update();                
            });
    
    connect(thirdAction, &QAction::triggered,
            [=]( ) {
                widget->setSphereModel(GLWidget::MODEL::UV_ICOSAHEDRON);
                widget->update();
            });
    
    
    box->addItem(thirdAction->text(), QVariant::fromValue(thirdAction));
    box->addItem(firstAction->text(), QVariant::fromValue(firstAction));
    box->addItem(secondAction->text(), QVariant::fromValue(secondAction));

    
    return box;
}

void Window::ShapeSelectorIndexChanged(int index)
{
    QAction * selectedAction = box->itemData(index, Qt::UserRole).value<QAction *>();
    if (selectedAction)
    {
        selectedAction->trigger(); //do stuff with your action
    }
}

void Window::keyPressEvent(QKeyEvent *e)
{
    if (e->key() == Qt::Key_Escape)
        close();
    else
        QWidget::keyPressEvent(e);
}
