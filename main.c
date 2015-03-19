#include <windows.h>
#include <gl/gl.h>


LRESULT CALLBACK event_handler(HWND, UINT, WPARAM, LPARAM);

int WinMain(HINSTANCE instance, HINSTANCE _, LPSTR _cmd, int _show) {
  WNDCLASSW wc = {};
  wc.lpfnWndProc    = event_handler;
  wc.hInstance      = instance;
  wc.hbrBackground  = (HBRUSH)(COLOR_BACKGROUND);
  wc.lpszClassName  = L"oglversionchecksample";
  wc.style          = CS_OWNDC;
  if (!RegisterClassW(&wc)) { return 1; }
  CreateWindowW(wc.lpszClassName, L"openglversioncheck",
    WS_OVERLAPPEDWINDOW | WS_VISIBLE, 0, 0, 640, 480, 0, 0, instance, 0);

  MSG msg = {};
  while (GetMessage(&msg, NULL, 0, 0) > 0)
    DispatchMessage(&msg);

  return 0;
}

LRESULT CALLBACK event_handler(HWND window, UINT message, WPARAM w_param, LPARAM l_param) {
  if (message != WM_CREATE) {
    return DefWindowProc(window, message, w_param, l_param);
  }

  PIXELFORMATDESCRIPTOR fmt_desc = {
    sizeof(PIXELFORMATDESCRIPTOR),
    1,
    PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
                        //Flags
    PFD_TYPE_RGBA,      // The kind of framebuffer. RGBA or palette.
    32,                 // Colordepth of the framebuffer.
    0, 0, 0, 0, 0, 0,
    0,
    0,
    0,
    0, 0, 0, 0,
    24,                 // Number of bits for the depthbuffer
    8,                  // Number of bits for the stencilbuffer
    0,                  // Number of Aux buffers in the framebuffer.
    PFD_MAIN_PLANE,
    0,
    0, 0, 0
  };

  // Retrieve device context from window handle
  HDC hdc = GetDC(window);

  // Let OS choose their pixel format
  int fmt;
  fmt = ChoosePixelFormat(hdc, &fmt_desc);
  SetPixelFormat(hdc, fmt, &fmt_desc);

  // Create OpenGL rendering context
  HGLRC ctxt = wglCreateContext(hdc);
  wglMakeCurrent(hdc, ctxt);

  MessageBoxA(0, (char*)glGetString(GL_VERSION), "OPENGL VERSION", 0);

  wglDeleteContext(ctxt);
  PostQuitMessage(0);

  return 0;
}
