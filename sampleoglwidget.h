#ifndef SAMPLEOGLWIDGET_H
#define SAMPLEOGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QVector3D>

class QMouseEvent;
class QTimer;

class SampleOGLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
public:
    SampleOGLWidget(QWidget* parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());

    void   setColor(QColor color);
    QColor color() const;

    void      setRotateAxis(QVector3D axis);
    QVector3D rotateAxis() const;
    void      startRotation(bool needStart = true);

    void scale_plus();
    void scale_minus();
    void rotate_up();
    void rotate_down();
    void rotate_left();
    void rotate_right();
    void rotate_free();
    void translate_down();
    void translate_up();
    void defaultScene();
protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int width, int hight) override;

    void mousePressEvent(QMouseEvent* mouseEvent) override;
    void mouseMoveEvent(QMouseEvent* mouseEvent) override;
    void mouseReleaseEvent(QMouseEvent* mouseEvent) override;
    void wheelEvent(QWheelEvent* wheelEvenl) override;
private:
    GLuint CreateCylinder(GLfloat radius, GLfloat height);
private slots:
    void doRotate();
private:
    GLuint  m_cylinder;

    GLfloat m_xRotate;
    GLfloat m_yRotate;
    GLfloat m_zRotate;
    GLfloat m_zTranslate;
    GLfloat m_scale;

    QPoint    m_position;
    QColor    m_color;
    QVector3D m_rotateAxis;
    GLfloat   m_freeRotate;

    QTimer* m_timer;

    const float m_cylRadius = 1.0f;
    const float m_cylHeight = 3.0f;
    const float m_sceneGapRatio = 1.1f;
    const float m_rotateStep = 1.0f;
    const float m_translateStep = 0.05f;
    const float m_scaleRatio = 1.1f;

    const GLuint m_nSlices = 30;
    const GLuint m_nStacks = 30;
    const int    m_rotateSpeedMsec = 10;
};

#endif // SAMPLEOGLWIDGET_H
