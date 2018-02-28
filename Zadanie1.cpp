#include <cmath>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif;

//Siemiokąt
//Maciej Ślusarek

// Początkowy rozmiar i pozycja siedmiokąta
GLfloat x_1 = 100.0f;
GLfloat y_1 = 100.0f;
GLsizei rsize = 50;

// Rozmiar kroku (liczba pikseli) w osi x i y
GLfloat xstep = 3.0f;
GLfloat ystep = 3.0f;

// Dane zmieniających się rozmiarów okna
GLfloat windowWidth;
GLfloat windowHeight;

// Wywoływana w celu przerysowania sceny
void RenderScene(void) {

	// Wyczyszczenie okna aktualnym kolorem czyszczącym
	glClear(GL_COLOR_BUFFER_BIT);

	// Aktualny kolor rysujący - czerwony
	// R G B
	glColor3f(1.0f, 0.0f, 0.0f);

	// Narysowanie siedmiokąta wypełnionego aktualnym kolorem
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

	// Wysłanie poleceń do wykonania
	glutSwapBuffers();
}

// Wywoływana przez bibliotek GLUT w czasie, gdy okno nie jest przesuwane ani nie jest zmieniana jego wielkość

void TimerFunction(int value) {

	// Odwrócenie kierunku, jeżeli osiągnięto lewę lub prawą krawędź
	if (x_1 > windowWidth - rsize || x_1 + (10.0 * cos(3 * 2 * 3.14f / 5)) * 5 < 0)
		xstep = -xstep;

	// Odwrócenie kierunku, jeżeli osiągnięto dolną lub górną krawędź
	if (y_1 > windowHeight - rsize || y_1 - rsize < 0)
		ystep = -ystep;

	// Kontrola obramowania. Wykonywana jest na wypadek, gdyby okno
	// zmniejszyło swoją wielkość w czasie, gdy siedmiokąt odbija się od
	// krawędzi, co mogłoby spowodować, że znalazł by się poza
	// przestrzenią ograniczajcą.
	if (x_1 > windowWidth - rsize)
		x_1 = windowWidth - rsize - 1;

	if (y_1 > windowHeight - rsize)
		y_1 = windowHeight - rsize - 1;

	// Wykonanie przesunięcia siedmiokąta
	x_1 += xstep;
	y_1 += ystep;

	// Ponowne rysowanie sceny z nowymi współrzędnymi
	glutPostRedisplay();
	glutTimerFunc(33, TimerFunction, 1);
}

// Konfigurowanie stanu renderowania

void SetupRC(void) {

	// Ustalenie niebieskiego koloru czyszczącego
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
}

// Wywoływana przez bibliotekę GLUT przy każdej zmianie wielkości okna

void ChangeSize(GLsizei w, GLsizei h) {

	// Zabezpieczenie przed dzieleniem przez zero
	if (h == 0)
		h = 1;

	// Ustalenie wielkości widoku zgodnego z rozmiarami okna

	glViewport(0, 0, w, h);

	// Ustalenie układu współrzędnych
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

	// Ustanowienie przestrzeni ograniczającej (lewo, prawo, dół, góra, blisko, daleko)
	glOrtho(0.0f, windowWidth, 0.0f, windowHeight, 1.0f, -1.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Siedmiokąt");
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);
	glutTimerFunc(33, TimerFunction, 1);
	SetupRC();
	glutMainLoop();	
}