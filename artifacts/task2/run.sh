#!/usr/bin/env bash
set -euo pipefail

SOURCE_DIR="./../.."
BIN_DIR="${SOURCE_DIR}/build/src/pass/app"
ANALYZER="${SOURCE_DIR}/src/pass/statistics.py"
TOP=20

for O in 0 1 2 3; do
  BIN="${BIN_DIR}/main_O${O}"
  OUT_TXT="$(mktemp "/tmp/prog_out_O${O}.XXXXXX.txt")"
  STATS="statistics_O${O}.txt"

  timeout "0.1s" "${BIN}" > "${OUT_TXT}" || true
  python3 "${ANALYZER}" "${OUT_TXT}" --top "${TOP}" > "${STATS}"

  rm -f "${OUT_TXT}"
  echo "Wrote ${STATS}"
done