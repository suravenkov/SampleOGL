#include "sampleoglwidget.h"

#include <QMouseEvent>
#include <QOpenGLContext>
#include <QTimer>

#include <GL/glu.h>
#include <GL/gl.h>
#include <GL/glaux.h>
//-----------------------------------------------------------------------------//
SampleOGLWidget::SampleOGLWidget(QWidget *parent, Qt::WindowFlags f):
    QOpenGLWidget(parent, f),
    m_cylinder(0),
    m_xRotate(0.0f),
    m_yRotate(0.0f),
    m_zRotate(0.0f),
    m_zTranslate(0.0f),
    m_scale(1.0f),
    m_color(113, 90, 153, 200),
    m_rotateAxis(1.0f, 0.0f, 0.0f),
    m_freeRotate(0.0f),
    m_timer(new QTimer(this))
{
}
//-----------------------------------------------------------------------------//
void SampleOGLWidget::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);

    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    GLfloat mat_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialf(GL_FRONT, GL_SHININESS, 128);

    GLfloat posDist = m_cylHeight * 2.0f;
    GLfloat lightPos[4] = {posDist, posDist, posDist, 1.0f};
    GLfloat lightDir[3] = {-1.0f, -1.0f, -1.0f};
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, lightDir);

    glShadeModel(GL_SMOOTH);
    m_cylinder = CreateCylinder(m_cylRadius, m_cylHeight);

    connect(m_timer, &QTimer::timeout, this, &SampleOGLWidget::doRotate);
    m_timer->start(m_rotateSpeedMsec);
}
//-----------------------------------------------------------------------------//
void SampleOGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glScalef(m_scale, m_scale, m_scale);
    glTranslatef(0.0f, 0.0f, m_zTranslate);
    glRotatef(m_freeRotate, m_rotateAxis.x(), m_rotateAxis.y(), m_rotateAxis.z());
    glRotatef(m_xRotate, 1.0f, 0.0f, 0.0f);
    glRotatef(m_yRotate, 0.0f, 1.0f, 0.0f);
    glRotatef(m_zRotate, 0.0f, 0.0f, 1.0f);
    setColor(m_color);
    glCallList(m_cylinder);
}
//-----------------------------------------------------------------------------//
void SampleOGLWidget::resizeGL(int width, int height)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    GLfloat ratio = (GLfloat)height / (GLfloat)width;
    GLdouble sceneSize  = m_cylHeight * m_sceneGapRatio;
    GLdouble sceneDepth = m_cylHeight * m_sceneGapRatio;
    if (width >= height)
        glOrtho(-sceneSize/ratio, sceneSize/ratio, -sceneSize,       sceneSize,       -sceneDepth, sceneDepth);
    else
        glOrtho(-sceneSize,       sceneSize,       -sceneSize*ratio, sceneSize*ratio, -sceneDepth, sceneDepth);
    glViewport(0, 0, (GLint)width, (GLint)height);
}
//-----------------------------------------------------------------------------//
void SampleOGLWidget::mousePressEvent(QMouseEvent* mouseEvent)
{
    m_position = mouseEvent->pos();
}
//-----------------------------------------------------------------------------//
void SampleOGLWidget::mouseReleaseEvent(QMouseEvent* mouseEvent)
{
    Q_UNUSED(mouseEvent);
}
//-----------------------------------------------------------------------------//
void SampleOGLWidget::mouseMoveEvent(QMouseEvent* mouseEvent)
{
    m_xRotate = 180.0 / m_scale * (GLfloat)(mouseEvent->position().y() - m_position.y()) / height();
    m_yRotate = 180.0 / m_scale * (GLfloat)(mouseEvent->position().x() - m_position.x()) / width();
    update();
}
//-----------------------------------------------------------------------------//
void SampleOGLWidget::wheelEvent(QWheelEvent* wheelEvent)
{
    if (wheelEvent->angleDelta().y() > 0)
        scale_plus();
    else if (wheelEvent->angleDelta().y() < 0)
        scale_minus();

    update();
}
//-----------------------------------------------------------------------------//
void SampleOGLWidget::scale_plus()
{
    m_scale = m_scale * m_scaleRatio;
}
//-----------------------------------------------------------------------------//
void SampleOGLWidget::scale_minus()
{
    m_scale = m_scale / m_scaleRatio;
}
//-----------------------------------------------------------------------------//
void SampleOGLWidget::rotate_up()
{
    // % operation to limit rotate value to prevent overflow
    m_xRotate = (int)(m_xRotate + m_rotateStep) % 360;
}
//-----------------------------------------------------------------------------//
void SampleOGLWidget::rotate_down()
{
    m_xRotate = (int)(m_xRotate - m_rotateStep) % 360;
}
//-----------------------------------------------------------------------------//
void SampleOGLWidget::rotate_left()
{
    m_yRotate = (int)(m_yRotate + m_rotateStep) % 360;
}
//-----------------------------------------------------------------------------//
void SampleOGLWidget::rotate_right()
{
    m_yRotate = (int)(m_yRotate - m_rotateStep) % 360;
}
//-----------------------------------------------------------------------------//
void SampleOGLWidget::rotate_free()
{
    m_freeRotate = (int)(m_freeRotate + m_rotateStep) % 360;
}
//-----------------------------------------------------------------------------//
void SampleOGLWidget::defaultScene()
{
    m_xRotate = 0.0f;
    m_yRotate = 0.0f;
    m_zRotate = 0.0f;
    m_zTranslate = 0.0f;
    m_scale = 1.0f;
    m_freeRotate = 0.0f;
    if (m_timer->isActive())
        m_timer->stop();
    else
        m_timer->start();
}
//-----------------------------------------------------------------------------//
void SampleOGLWidget::setColor(QColor color)
{
    m_color = color;
    glColor3f(color.redF(), color.greenF(), color.blueF());
}
//-----------------------------------------------------------------------------//
QColor SampleOGLWidget::color() const
{
    return m_color;
}
//-----------------------------------------------------------------------------//
void SampleOGLWidget::setRotateAxis(QVector3D axis)
{
    m_rotateAxis = axis;
}
//-----------------------------------------------------------------------------//
QVector3D SampleOGLWidget::rotateAxis() const
{
    return m_rotateAxis;
}
//-----------------------------------------------------------------------------//
void SampleOGLWidget::startRotation(bool needStart)
{
    if (needStart)
        m_timer->start();
    else
        m_timer->stop();
}
//-----------------------------------------------------------------------------//
void SampleOGLWidget::doRotate()
{
    rotate_free();
    update();
}
//-----------------------------------------------------------------------------//
GLuint SampleOGLWidget::CreateCylinder(GLfloat radius, GLfloat height)
{
    GLuint id = glGenLists(1);
    if (id == 0)
        return 0;  // Error: could not create display list
    
    glNewList(id, GL_COMPILE);
        glBegin(GL_TRIANGLE_STRIP);
            GLUquadric* quadric = gluNewQuadric();
            gluQuadricDrawStyle(quadric, GLU_FILL);
            gluCylinder(quadric, radius, radius, height, m_nSlices, m_nStacks);
            gluDisk(quadric, 0.0, radius, m_nSlices, m_nStacks);
            glTranslatef(0.0f, 0.0f, height);
            gluDisk(quadric, 0.0, radius, m_nSlices, m_nStacks);
        glEnd();
    glEndList();

    return id;
}