IMGUI_DIR = "external/imgui"

group("external")
project("imgui")
  kind("StaticLib")
  language("C++")
  links({
  })
  defines({
    "_LIB",
  })
  includedirs({
    "imgui",
    "../" .. SDL_INC_DIR,
  })
  files({
    "imgui/imconfig.h",
    "imgui/imgui_demo.cpp",
    "imgui/imgui_draw.cpp",
    "imgui/imgui_internal.h",
    "imgui/imgui_tables.cpp",
    "imgui/imgui_widgets.cpp",
    "imgui/imgui.cpp",
    "imgui/imgui.h",
    "imgui/imstb_rectpack.h",
    "imgui/imstb_textedit.h",
    "imgui/imstb_truetype.h",
    "imgui/backends/imgui_impl_sdl3.cpp",
    "imgui/backends/imgui_impl_sdl3.h",
    "imgui/backends/imgui_impl_sdlrenderer3.cpp",
    "imgui/backends/imgui_impl_sdlrenderer3.h",
  })
