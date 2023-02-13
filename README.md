# StackArrayTUI

Aplikasi ini adalah sebuah permainan sederhana yang terinspirasi dari sebuah permainan anak-anak yang bernama _Rings of Color_ dan terinspirasi dari sebuah iklan permainan botol warna yang acak yang warnanya harus diurutkan sampai jadi satu warna.

#

Aplikasi ini dibuat dari bahasa pemrograman C++ yang memanfaatkan konsep _Stack (Array of Struct)_ dan menggunakan _library_ atau pustaka pihak ketiga bernama [FTXUI](https://github.com/ArthurSonzogni/FTXUI) (_Functional Terminal (X) User interface_) untuk membuat antarmuka pengguna agar aplikasi lebih menarik dan mudah untuk diakses.

#

Untuk data _struct_ di aplikasi ini yaitu:

```cpp
struct Data {
  Color::Palette256 warna;
  int id;
};
```

untuk detail _struct_ sebagai berikut.
|tipe|nama|deskripsi|
|---|---|---|
|Color::Palette256|warna|nilai warna yang akan diterapkan pada aplikasi|
|int|id|untuk memisakan komponen agar tidak bertabrakan|

#

Aplikasi ini mendefinisikan _stack (Array)_ yang maksimal isinya ada 5 namun bisa diubah.

```cpp
#define MAX 5
```

_stack_ yang ada di aplikasi ini ada 3 buah yang dimana setiap _stack_ menyimpan data _struct_ agar bisa diterapkan pada aplikasi dan ditetapkan nilai awal agar bisa menyesuaikan pada referensi permainan.

```cpp
Data s_left[MAX] = {
    {Color::DeepSkyBlue3, 3},
    {Color::Yellow1, 1},
};
int top_left = 2;
Elements items_left = {};

Data s_center[MAX] = {
    {Color::DeepSkyBlue3, 3},
};
int top_center = 1;
Elements items_center = {};

Data s_right[MAX] = {
    {Color::DeepSkyBlue3, 3},
    {Color::Green3Bis, 2},
    {Color::Yellow1, 1},
};
int top_right = 3;
Elements items_right = {};
```

#

untuk fungsi-fungsi yang ada tidak jauh beda dengan fungsi yang ada pada stack pada umumnya hanya saja sedikit ada penyesuaikan.

```cpp
bool isfull(int top) { return top == MAX; }

bool isempty(int top) { return top == 0; }

void push(Data stack[], int &top, Data data) {
  if (isfull(top)) {
    response = "SUDAH PENUH";
    return;
  }
  stack[top] = data;
  top++;
  data_state = {Color::LightCyan3, -1};
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
```

#

untuk bagian program utama atau yang ada di `int main()` berisi pengaturan untuk mengatur tata letak pengguna menyesuaikan fungsi dari _stack_

# Cara mengcompile menjalankan aplikasi

aplikasi ini perlu di compile terlebih dahulu sebelum dijalankan.

bahan-bahan

- [CMake](https://cmake.org/) yang berfungsi sebagai tools untuk membuat aplikasi
- Compiler yang bisa menggunakan GCC, MinGW, Clang dan lainnya.

lalu masuk ke dalam folder utama dari aplikasi dan jalankan perintah ini pada Terminal atau CMD

```bash
cmake --build ./build --config Release --target all -j 10
```

atau memakai IDE seperti Visual Studio Code atau CLion agar mempermudah

jika sudah di compile maka aplikasi dapan dijalankan dengan cara masuk ke folder `./build` dan jalankan perintah pada Terminal atau CMD

```
.\StackArrayTUI.exe
```
