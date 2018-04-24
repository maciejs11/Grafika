#include <cmath>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif;

//Siemiok�t
//Maciej �lusarek

// Pocz�tkowy rozmiar i pozycja siedmiok�ta
GLfloat x_1 = 100.0f;
GLfloat y_1 = 100.0f;
GLsizei rsize = 50;

// Rozmiar kroku (liczba pikseli) w osi x i y
GLfloat xstep = 3.0f;
GLfloat ystep = 3.0f;

// Dane zmieniaj�cych si� rozmiar�w okna
GLfloat windowWidth;
GLfloat windowHeight;

// Wywo�ywana w celu przerysowania sceny
void RenderScene(void) {

	// Wyczyszczenie okna aktualnym kolorem czyszcz�cym
	glClear(GL_COLOR_BUFFER_BIT);

	// Aktualny kolor rysuj�cy - czerwony
	// R G B
	glColor3f(1.0f, 0.0f, 0.0f);

	// Narysowanie siedmiok�ta wype�nionego aktualnym kolorem
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(x_1, y_1);
	for (int i = 0; i <= 7; i++)
	{
		glVertex2f(
			(x_1 + (10.0 * cos(i * 2 * 3.14f / 7)) * 5),
			(y_1 + (10.0 * sin(i * 2 * 3.14f / 7)) * 5)
		);
	}
	glEnd();
	glFlush();

	// Wys�anie polece� do wykonania
	glutSwapBuffers();
}

// Wywo�ywana przez bibliotek GLUT w czasie, gdy okno nie jest przesuwane ani nie jest zmieniana jego wielko��

void TimerFunction(int value) {

	// Odwr�cenie kierunku, je�eli osi�gni�to lew� lub praw� kraw�d�
	if (x_1 > windowWidth - rsize || x_1 + (10.0 * cos(3 * 2 * 3.14f / 5)) * 5 < 0)
		xstep = -xstep;

	// Odwr�cenie kierunku, je�eli osi�gni�to doln� lub g�rn� kraw�d�
	if (y_1 > windowHeight - rsize || y_1 - rsize < 0)
		ystep = -ystep;

	// Kontrola obramowania. Wykonywana jest na wypadek, gdyby okno
	// zmniejszy�o swoj� wielko�� w czasie, gdy siedmiok�t odbija si� od
	// kraw�dzi, co mog�oby spowodowa�, �e znalaz� by si� poza
	// przestrzeni� ograniczajc�.
	if (x_1 > windowWidth - rsize)
		x_1 = windowWidth - rsize - 1;

	if (y_1 > windowHeight - rsize)
		y_1 = windowHeight - rsize - 1;

	// Wykonanie przesuni�cia siedmiok�ta
	x_1 += xstep;
	y_1 += ystep;

	// Ponowne rysowanie sceny z nowymi wsp�rz�dnymi
	glutPostRedisplay();
	glutTimerFunc(33, TimerFunction, 1);
}

// Konfigurowanie stanu renderowania

void SetupRC(void) {

	// Ustalenie niebieskiego koloru czyszcz�cego
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
}

// Wywo�ywana przez bibliotek� GLUT przy ka�dej zmianie wielko�ci okna

void ChangeSize(GLsizei w, GLsizei h) {

	// Zabezpieczenie przed dzieleniem przez zero
	if (h == 0)
		h = 1;

	// Ustalenie wielko�ci widoku zgodnego z rozmiarami okna

	glViewport(0, 0, w, h);

	// Ustalenie uk�adu wsp�rz�dnych
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (w <= h)
	{
		windowHeight = 250.0f*h / w;
		windowWidth = 250.0f;
	}
	else
	{
		windowWidth = 250.0f*w / h;
		windowHeight = 250.0f;
	}

	// Ustanowienie przestrzeni ograniczaj�cej (lewo, prawo, d�, g�ra, blisko, daleko)
	glOrtho(0.0f, windowWidth, 0.0f, windowHeight, 1.0f, -1.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Siedmiok�t");
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);
	glutTimerFunc(33, TimerFunction, 1);
	SetupRC();
	glutMainLoop();
}