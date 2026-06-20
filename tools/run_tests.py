#!/usr/bin/env python3
import argparse
import json
import os
import re
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
TESTS_DIR = ROOT / "tests"
ERROR_MANAGER_HPP = ROOT / "include" / "addition" / "error_manager.hpp"
CODE_RE = re.compile(r"\b([A-Z]{3}_\d{4})\b")

KNOWN_UNREACHABLE_PREFIXES = ("RUN_",)

KNOWN_UNREACHABLE_CODES = {"LEX_2002", "LEX_3002"}


class Colors:
    GREEN = "\033[32m"
    RED = "\033[31m"
    YELLOW = "\033[33m"
    CYAN = "\033[36m"
    BOLD = "\033[1m"
    RESET = "\033[0m"


def discover_all_codes():
    text = ERROR_MANAGER_HPP.read_text(encoding="utf-8")
    codes = set(re.findall(r'const std::string \w+ = "([A-Z]{3}_\d{4})"', text))
    codes.discard("ERR_0000")
    return codes


def discover_cases(filter_substr=None):
    cases = []
    for json_path in sorted(TESTS_DIR.rglob("*.json")):
        if filter_substr and filter_substr not in str(json_path):
            continue
        cases.append(json_path)
    return cases


def run_case(atm_binary, json_path):
    spec = json.loads(json_path.read_text(encoding="utf-8"))
    args = spec.get("args", [])
    no_file = spec.get("no_file", False)
    expect_ok = spec.get("expect_ok", False)
    expected_codes = set(spec.get("codes", []))

    missing_file = spec.get("missing_file", False)
    chmod_000 = spec.get("chmod_000", False)

    cmd = [str(atm_binary)]
    atm_file = None
    if not no_file:
        atm_file = json_path.with_name(spec.get("file", json_path.stem + ".atm"))
        if not atm_file.exists() and not missing_file:
            return False, f"фикстура не найдена: {atm_file}", set()
        cmd.append(str(atm_file))
    cmd.extend(args)

    old_mode = None
    if chmod_000 and atm_file is not None and atm_file.exists():
        old_mode = atm_file.stat().st_mode
        os.chmod(atm_file, 0o000)

    try:
        try:
            proc = subprocess.run(
                cmd, cwd=ROOT, capture_output=True, text=True, timeout=20
            )
        except subprocess.TimeoutExpired:
            return False, "таймаут выполнения (возможно, зависание/бесконечный цикл)", set()
    finally:
        if old_mode is not None:
            os.chmod(atm_file, old_mode)

    output = proc.stdout + proc.stderr
    found_codes = set(CODE_RE.findall(output))

    prefixes = spec.get("code_prefixes")
    if prefixes:
        found_codes = {c for c in found_codes if c.startswith(tuple(prefixes))}

    if expect_ok:
        if found_codes:
            return False, f"ожидался успех без ошибок, но найдены коды: {sorted(found_codes)}", found_codes
        return True, "", found_codes

    if found_codes != expected_codes:
        missing = expected_codes - found_codes
        extra = found_codes - expected_codes
        detail = []
        if missing:
            detail.append(f"не найдены: {sorted(missing)}")
        if extra:
            detail.append(f"лишние/неожиданные: {sorted(extra)}")
        return False, "; ".join(detail), found_codes

    return True, "", found_codes


def main():
    parser = argparse.ArgumentParser(description="Тестовый раннер ATOM compiler")
    parser.add_argument("--binary", default=str(ROOT / "build" / "atm"))
    parser.add_argument("--filter", default=None, help="подстрока пути для фильтрации тестов")
    parser.add_argument("--quiet", action="store_true", help="печатать только итог и провалы")
    args = parser.parse_args()

    atm_binary = Path(args.binary)
    if not atm_binary.exists():
        print(f"{Colors.RED}Бинарник не найден: {atm_binary}. Соберите проект (cmake --build build).{Colors.RESET}")
        return 1

    cases = discover_cases(args.filter)
    if not cases:
        print(f"{Colors.YELLOW}Не найдено ни одного тест-кейса (*.json) в {TESTS_DIR}{Colors.RESET}")
        return 1

    passed, failed = 0, 0
    all_tested_codes = set()
    failures = []

    for json_path in cases:
        rel = json_path.relative_to(TESTS_DIR)
        ok, detail, found_codes = run_case(atm_binary, json_path)
        spec = json.loads(json_path.read_text(encoding="utf-8"))
        all_tested_codes |= set(spec.get("codes", []))
        if ok:
            passed += 1
            if not args.quiet:
                print(f"{Colors.GREEN}PASS{Colors.RESET} {rel}")
        else:
            failed += 1
            failures.append((rel, detail))
            print(f"{Colors.RED}FAIL{Colors.RESET} {rel} -- {detail}")

    print(f"\n{Colors.BOLD}Итог: {passed} прошло, {failed} провалено, всего {passed + failed}{Colors.RESET}")

    all_codes = discover_all_codes()
    unreachable = {c for c in all_codes if c.startswith(KNOWN_UNREACHABLE_PREFIXES)}
    unreachable |= KNOWN_UNREACHABLE_CODES
    coverable = all_codes - unreachable
    uncovered = coverable - all_tested_codes
    if uncovered:
        print(f"\n{Colors.YELLOW}Покрытие кодов ошибок: {len(coverable - uncovered)}/{len(coverable)} "
              f"(без учёта {len(unreachable)} RUN_*-кодов, недостижимых до подключения интерпретатора).{Colors.RESET}")
        print(f"{Colors.YELLOW}Не покрыты тестами: {sorted(uncovered)}{Colors.RESET}")
    else:
        print(f"\n{Colors.GREEN}Полное покрытие всех {len(coverable)} достижимых кодов ошибок "
              f"(без учёта {len(unreachable)} RUN_*-кодов).{Colors.RESET}")

    return 1 if failed else 0


if __name__ == "__main__":
    sys.exit(main())
