# LabWork2_2sem

Лабораторная работа по линейным структурам данных на C++.

Проект содержит:
- `DynamicArray<T>`
- `LinkedList<T>`
- `Sequence<T>`
- `ArraySequence<T>`
- `MutableArraySequence<T>`
- `ImmutableArraySequence<T>`
- `ListSequence<T>`
- консольный UI
- набор тестов

Сейчас пользовательский UI работает с `Sequence<int>`.

## Сборка и запуск

### Windows

Открой `x64 Native Tools Command Prompt for VS 2022` или подними окружение MSVC вручную:

```bat
"C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat"
```

Перейди в папку проекта и собери приложение:

```bat
cd /d D:\Документы\GitHub\LabWork2_2sem
cl /nologo /EHsc append_ui.cpp concat_ui.cpp create_sequence_ui.cpp insert_at_ui.cpp main.cpp map_ui.cpp prepend_ui.cpp print_sequences_ui.cpp reduce_ui.cpp run_tests_ui.cpp sequence_ui_utils.cpp slice_ui.cpp subsequence_ui.cpp tests.cpp ui.cpp where_ui.cpp /Fe:lab_app.exe
```

Запуск:

```bat
lab_app.exe
```

Если запуск идет из PowerShell:

```powershell
.\lab_app.exe
```

### Linux

В Linux используется `g++` и `Makefile`.

Сборка:

```bash
make
```

Запуск:

```bash
./lab_app
```

Очистка объектных файлов и бинарника:

```bash
make clean
```

## Меню

В UI доступны основные операции:
- `Create sequence`
- `Print sequence`
- `Append`
- `Prepend`
- `InsertAt`
- `GetSubsequence`
- `Concat`
- `Map`
- `Where`
- `Reduce`
- `Slice`
- `Run tests`


