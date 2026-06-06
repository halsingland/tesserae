#include <windows.h>
#include <GL/gl.h>
#include <math.h>

void love() {

    HDC hDC = GetDC(NULL);

    PIXELFORMATDESCRIPTOR pfd = { sizeof(PIXELFORMATDESCRIPTOR), 1,
        PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
        PFD_TYPE_RGBA, 32, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 16, 0, 0, 0, 0, 0, 0, 0 };

    int format = ChoosePixelFormat(hDC, &pfd);
    SetPixelFormat(hDC, format, &pfd);

    HGLRC hRC = wglCreateContext(hDC);
    wglMakeCurrent(hDC, hRC);

    float t = 0.00f;

    while (1) {
        if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) break;

        glClear(GL_COLOR_BUFFER_BIT);

        for (float i = 1.0f; i <= 12.0f; i += 0.4f) {
            glLoadIdentity();

            float posX = sinf(t * 1.50f + i * 1.10f) * 0.70f;
            float posY = cosf(t * 0.9f + (i * i) * 0.4f) * 0.5f;
            glTranslatef(posX, posY, 0.0f);

            glRotatef(t * 35.0f * i, 1.0f, 0.0f, 0.0f);
            glRotatef(t * 25.00f * i, 0.0f, 1.0f, 0.0f);
            glRotatef(t * 13.00f * i, 0.0f, 0.0f, 1.0f);

            float base_size = 0.2f + (i * 0.08f);
            float scale = base_size + sinf(t * 3.0f + i * 2.0f) * 0.2f;

            float r = sinf(t + i) * 0.5f + 0.50f;
            float g = sinf(t + i + 1.00f) * 0.5f + 0.5f;
            float b = sinf(t - i) * 0.5f + 0.5f;

            glBegin(GL_QUADS);
                glColor3f(r, g, 0.1f);     glVertex2f(-0.15f * scale, -0.15f * scale);
                glColor3f(0.1f, g, b);     glVertex2f(0.15f * scale, -0.15f * scale);
                glColor3f(r, 0.1f, b);     glVertex2f(0.15f * scale, 0.15f * scale);
                glColor3f(1.0f - r, g, b); glVertex2f(-0.15f * scale, 0.15f * scale);
            glEnd();
        }

        SwapBuffers(hDC);
        t += 0.01255f;
        Sleep(22);
    }

    ExitProcess(0);
}
