#include "ftxui/component/component.hpp"  // for Button, Horizontal, Renderer
#include "ftxui/component/screen_interactive.hpp"  // for ScreenInteractive
#include "ftxui/dom/elements.hpp"  // for gauge, separator, text, vbox, operator|, Element, border
#include "scroller.hpp"
#include "string"  // for operator+, to_string

#define MAX 5

using namespace std;
using namespace ftxui;

struct Mahasiswa {
  string nim, nama;
} mahasiswa;
Mahasiswa stack[MAX];
int top = 0;

Elements items = {};
string response;

bool isfull() { return top == MAX; }

bool isempty() { return top == 0; }

void push() {
  if (isfull()) {
    response = "SUDAH PENUH";
    return;
  }
  stack[top] = mahasiswa;
  mahasiswa = {};
  top++;
  response = "DIISI";
}

void pop() {
  if (isempty()) {
    response = "KOSONG!";
    return;
  }
  response = "TERPOP!";
  top--;
}

void display() {
  items = {};
  for (int i = top - 1; i >= 0; --i) {
    items.push_back(
        window(text(to_string(i + 1) + ((i + 1 == top) ? " - TOP" : "")),
               vbox({text(stack[i].nim) | color(Color::Yellow3),
                     text(stack[i].nama) | color(Color::Green3)})));
  }
}

int main() {
  auto input_nim = Input(&mahasiswa.nim, "22xxxx") | size(WIDTH, EQUAL, 19);
  auto input_nama =
      Input(&mahasiswa.nama, "Fulan bin Fulan") | size(WIDTH, EQUAL, 18);
  auto input_box_nim = Renderer(
      input_nim, [&] { return hbox(text("NIM: "), input_nim->Render()); });
  auto input_box_nama = Renderer(
      input_nama, [&] { return hbox(text("Nama: "), input_nama->Render()); });
  auto form = Container::Vertical({input_box_nim, input_box_nama});

  auto stack_c =
      Renderer([&] { return vbox(items) | color(Color::Aquamarine3); });

  auto buttons = Container::Horizontal({Button("Push",
                                               [&] {
                                                 if (mahasiswa.nim.empty() ||
                                                     mahasiswa.nama.empty()) {
                                                   response =
                                                       "NIM/NAMA HARUS DIISI!";
                                                   return;
                                                 }
                                                 push();
                                                 display();
                                               }),
                                        Button("Pop",
                                               [&] {
                                                 pop();
                                                 display();
                                               }) |
                                            color(Color::RedLight)}) |
                 center;

  auto response_box = Renderer([&] { return hbox({text(response)}); });
  auto app =
      Container::Vertical(
          {response_box | inverted, Renderer([&] { return separator(); }), form,
           Renderer([&] { return separator(); }), buttons, Scroller(stack_c)}) |
      center | yframe | border;

  auto screen = ScreenInteractive::FitComponent();
  screen.Loop(app);

  return 0;
}
