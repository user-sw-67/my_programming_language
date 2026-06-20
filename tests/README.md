# Тестовая система компилятора ATOM

Чёрный ящик: каждый тест-кейс запускает `build/atm` на `.atm`-файле и
сравнивает множество найденных в выводе кодов ошибок (`LEX_*`, `PAR_*`,
`SEM_*`, `PRE_*`, `CFG_*`) с ожидаемым.

## Запуск

```
python3 tools/run_tests.py            # все тесты
python3 tools/run_tests.py --filter semantics/pass2   # подмножество
ctest --test-dir build                # то же самое через CTest
```

## Структура

```
tests/
  lexer/        LEX_*   (src/lexer/lexer.cpp)
  parser/       PAR_*   (src/parser/parser.cpp)
  semantics/pass1/  SEM_11xx..SEM_15xx (DefinitionVisitor)
  semantics/pass2/  SEM_21xx..SEM_27xx (AnalysisVisitor)
  semantics/pass3/  SEM_31xx (OptimizationVisitor)
  cli/          PRE_*, CFG_*  (source_manager.cpp, program_manager.cpp)
  ok/           позитивные сценарии — валидный код, ошибок быть не должно
```

## Формат тест-кейса

Каждый кейс — пара файлов с одинаковым именем (stem):
`<name>.atm` (исходник) + `<name>.json` (ожидание).

```json
{
  "description": "короткое описание, что именно проверяется",
  "codes": ["SEM_2101", "SEM_2301"],
  "expect_ok": false,
  "args": [],
  "file": "<name>.atm",
  "no_file": false
}
```

- `codes` — точное множество кодов ошибок, которые должны появиться в
  выводе (порядок и дубликаты не важны, но это **именно множество**:
  лишних или отсутствующих кодов быть не должно — раннер сравнивает строго).
- `expect_ok` — `true` означает, что в выводе не должно быть **вообще
  никаких** кодов ошибок (программа корректна на всех проверяемых этапах).
  При `expect_ok: true` поле `codes` не используется.
- `args` — дополнительные флаги CLI помимо пути к файлу (по умолчанию `[]`).
- `file` — имя `.atm`-файла рядом с json (по умолчанию `<name>.atm`).
- `no_file` — `true`, если тест не передаёт файл вообще (для `CFG_0003`);
  в этом случае `.atm`-файл не нужен.

## Известное ограничение покрытия

Коды `RUN_*` (см. `include/addition/error_manager.hpp`) возникают только
внутри Value-операций интерпретатора (`src/semantics/value.cpp`,
`src/addition/builds_manager.cpp`). `ProgramManager::run()` сейчас
останавливается после семантического анализа и не запускает интерпретацию
(см. CLAUDE.md, раздел "дорожная карта") — поэтому `RUN_*` коды физически
недостижимы через `build/atm` и не покрываются этими тестами. Раннер
автоматически исключает их из отчёта о покрытии. Когда появится backend
интерпретатора, для них нужно будет добавить отдельную категорию
`tests/runtime/`.
