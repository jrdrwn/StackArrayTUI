#include "ftxui/component/component.hpp"  // for Button, Horizontal, Renderer
#include "ftxui/component/screen_interactive.hpp"  // for ScreenInteractive
#include "ftxui/dom/elements.hpp"  // for gauge, separator, text, vbox, operator|, Element, border
#include "string"  // for operator+, to_string

#define MAX 5
#define C1 Color::Yellow1
#define C2 Color::Green3Bis
#define C3 Color::DeepSkyBlue3
#define CSTATE Color::LightCyan3

using namespace std;
using namespace ftxui;

struct Data {
  Color::Palette256 warna;
  int id;
};

Data s_left[MAX] = {
    {C3, 3},
    {C1, 1},
};
int top_left = 2;
Elements items_left = {};

Data s_center[MAX] = {
    {C3, 3},
};
int top_center = 1;
Elements items_center = {};

Data s_right[MAX] = {
    {C3, 3},
    {C2, 2},
    {C1, 1},
};
int top_right = 3;
Elements items_right = {};

string response = "Selamat Datang!";

Data data_state = {CSTATE, -1};

bool isfull(int top) { return top == MAX; }

bool isempty(int top) { return top == 0; }

void push(Data stack[], int &top, Data data) {
  if (isfull(top)) {
    response = "SUDAH PENUH";
    return;
  }
  stack[top] = data;
  top++;
  data_state = {CSTATE, -1};
  response = "DIISI";
}

void pop(Data stack[], int &top) {
  if (isempty(top)) {
    response = "KOSONG!";
    return;
  }
  response = "TERPOP!";
  top--;
  data_state = stack[top];
}

void display(Data stack[], int *top, Elements &items) {
  items = {};
  for (int i = *top - 1; i >= 0; --i) {
    items.push_back(vbox({text(L"")}) | bgcolor(stack[i].warna));
  }
}

int main() {
  auto state = Renderer([] {
    return hbox(text(response) | center | xflex) | yframe | border |
           color(data_state.warna);
  });

  FlexboxConfig flexbox_opt;
  flexbox_opt.direction = FlexboxConfig::Direction::Column;
  flexbox_opt.justify_content = FlexboxConfig::JustifyContent::FlexEnd;
  flexbox_opt.align_content = FlexboxConfig::AlignContent::Stretch;

  auto make_buttons = [](auto on_push, auto on_pop) {
    return Container::Horizontal(
               {Button("Push", on_push),
                Button("Pop", on_pop) | color(Color::RedLight)}) |
           center;
  };
  auto make_app_child = [](auto actions, auto view, auto c) {
    return Container::Vertical(
               {actions, Renderer([&] { return separator(); }), view}) |
           border | color(c) | size(HEIGHT, EQUAL, 11);
  };

  display(s_left, &top_left, items_left);
  auto left_stack_view =
      Renderer([&] { return flexbox(items_left, flexbox_opt); });
  auto left_buttons = make_buttons(
      [&] {
        if (data_state.warna != CSTATE) {
          push(s_left, top_left, data_state);
          display(s_left, &top_left, items_left);
        }
      },
      [&] {
        if (data_state.warna == CSTATE && data_state.id == -1) {
          pop(s_left, top_left);
          display(s_left, &top_left, items_left);
        }
      });
  auto left = make_app_child(left_buttons, left_stack_view, C1);

  display(s_center, &top_center, items_center);
  auto center_stack_view =
      Renderer([&] { return flexbox(items_center, flexbox_opt); });
  auto center_buttons = make_buttons(
      [&] {
        if (data_state.warna != CSTATE) {
          push(s_center, top_center, data_state);
          display(s_center, &top_center, items_center);
        }
      },
      [&] {
        if (data_state.warna == CSTATE && data_state.id == -1) {
          pop(s_center, top_center);
          display(s_center, &top_center, items_center);
        }
      });
  auto _center = make_app_child(center_buttons, center_stack_view, C3);

  display(s_right, &top_right, items_right);
  auto right_stack_view =
      Renderer([&] { return flexbox(items_right, flexbox_opt); });
  auto right_buttons = make_buttons(
      [&] {
        if (data_state.warna != CSTATE) {
          push(s_right, top_right, data_state);
          display(s_right, &top_right, items_right);
        }
      },
      [&] {
        if (data_state.warna == CSTATE && data_state.id == -1) {
          pop(s_right, top_right);
          display(s_right, &top_right, items_right);
        }
      });
  auto right = make_app_child(right_buttons, right_stack_view, C2);

  auto response_box = Renderer([&] { return hbox({text(response)}); });
  auto stack = Container::Horizontal({left, _center, right});
  auto screen = ScreenInteractive::Fullscreen();
  auto app = Container::Vertical({
                 state,
                 stack,
                 Button("KELUAR", screen.ExitLoopClosure()) |
                     color(Color::Red3) | center,
             }) |
             center | frame | borderEmpty;

  screen.Loop(app);

  return 0;
}
