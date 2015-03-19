#include <windows.h>
#include <gl/gl.h>

int WinMain(HINSTANCE instance, HINSTANCE _, LPSTR _cmd, int _show) {
  // Prepare window class
  WNDCLASSW wc = {};
  wc.lpfnWndProc    = DefWindowProc;
  wc.lpszClassName  = L"oglversionchecksample";
  if (!RegisterClassW(&wc)) { return 1; }

  // Create new window
  HWND window = CreateWindowW(wc.lpszClassName, 0, 0, 0, 0, 640, 480, 0, 0, instance, 0);

  // Retrieve device context from window handle
  HDC hdc = GetDC(window);

  // Describe demanding pixel format
  PIXELFORMATDESCRIPTOR fmt_desc = {
    sizeof(PIXELFORMATDESCRIPTOR),
    1,
    PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
                        // Flags
    PFD_TYPE_RGBA,      // The kind of framebuffer. RGBA or palette
    32,                 // Colordepth of the framebuffer
    0, 0, 0, 0, 0, 0,
    0,
    0,
    0,
    0, 0, 0, 0,
    24,                 // Number of bits for the depthbuffer
    8,                  // Number of bits for the stencilbuffer
    0,                  // Number of Aux buffers in the framebuffer
    PFD_MAIN_PLANE,
    0,
    0, 0, 0
  };

  // Let OS choose their pixel format
  int fmt = ChoosePixelFormat(hdc, &fmt_desc);
  SetPixelFormat(hdc, fmt, &fmt_desc);

  // Create OpenGL rendering context
  HGLRC ctxt = wglCreateContext(hdc);
  wglMakeCurrent(hdc, ctxt);

  // Print OpenGL version string
  const char* version = glGetString(GL_VERSION);
  puts(version);

  // Clean up
  wglDeleteContext(ctxt);
  return 0;
}
