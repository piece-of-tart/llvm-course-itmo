#!/usr/bin/env python3

import argparse
import sys
from collections import Counter
from dataclasses import dataclass
from collections.abc import Iterable


@dataclass(frozen=True, slots=True)
class Gram:
    length: int
    items: tuple[str, ...]


def load_chunks(filepath: str, cut_on_blank: bool) -> list[list[str]]:
    blocks: list[list[str]] = [[]]

    with open(filepath, "r", encoding="utf-8", errors="replace") as handle:
        for raw_line in handle:
            stripped = raw_line.strip()
            if not stripped:
                if cut_on_blank and blocks[-1]:
                    blocks.append([])
                continue
            blocks[-1].append(stripped)

    return [b for b in blocks if b]


def walk_windows(tokens: list[str], span: int) -> Iterable[tuple[str, ...]]:
    total = len(tokens)
    if span <= 0 or span > total:
        return

    end = total - span + 1
    for pos in range(end):
        yield tuple(tokens[pos : pos + span])


def tally_windows(
    chunks: list[list[str]], spans: list[int]
) -> tuple[Counter, dict[int, int]]:
    freq: Counter = Counter()
    volume: dict[int, int] = {s: 0 for s in spans}

    for chunk in chunks:
        size = len(chunk)
        for span in spans:
            windows_here = size - span + 1
            if windows_here <= 0:
                continue

            volume[span] += windows_here
            for window in walk_windows(chunk, span):
                freq[Gram(span, window)] += 1

    return freq, volume


def render_pattern(seq: tuple[str, ...]) -> str:
    return seq[0] if len(seq) == 1 else "  |  ".join(seq)


def print_table(
    ranking: list[tuple[Gram, int]],
    volume: dict[int, int],
    limit: int,
    share_mode: str,
    global_total: int | None = None,
) -> None:
    if global_total is None:
        global_total = sum(volume.values())

    title = f"{'#':>3}  {'len':>3}  {'hits':>7}  {'share':>8}  pattern"
    print(title)
    print("-" * len(title))

    for idx, (key, hits) in enumerate(ranking[:limit], 1):
        if share_mode == "overall":
            denom = global_total or 1
        else:
            denom = volume.get(key.length, 0) or 1

        share = 100.0 * hits / denom
        print(
            f"{idx:>3}  {key.length:>3}  {hits:>7}  {share:>7.2f}%  {render_pattern(key.items)}"
        )


def build_cli() -> argparse.ArgumentParser:
    parser = argparse.ArgumentParser()
    parser.add_argument(
        "path", help="Input text file (one 'use <- instruction' per line)."
    )
    parser.add_argument(
        "--top", type=int, default=20, help="How many patterns to print."
    )
    parser.add_argument("--min-len", type=int, default=2, help="Minimal window length.")
    parser.add_argument("--max-len", type=int, default=5, help="Maximum window length.")
    parser.add_argument(
        "--threshold",
        type=int,
        default=2,
        help="Keep only patterns with hits >= threshold.",
    )
    parser.add_argument(
        "--share",
        choices=["by_len", "overall"],
        default="by_len",
        help="Share denominator: by_len (same length) or overall (all lengths).",
    )
    parser.add_argument(
        "--split-by-len",
        action="store_true",
        help="Print separate top lists for each window length.",
    )
    parser.add_argument("--no-split-on-blank", action="store_true")
    return parser


def main() -> int:
    parser = build_cli()
    opt = parser.parse_args()

    spans = list(range(opt.min_len, opt.max_len + 1))
    split_on_blank = not opt.no_split_on_blank

    chunks = load_chunks(opt.path, cut_on_blank=split_on_blank)
    if not chunks:
        print("[err] no input lines found", file=sys.stderr)
        return 2

    counts, totals = tally_windows(chunks, spans)

    kept: list[tuple[Gram, int]] = [
        (g, n) for g, n in counts.items() if n >= opt.threshold
    ]
    kept.sort(key=lambda kv: (-kv[1], -kv[0].length, kv[0].items))

    denom_all = sum(totals.values())
    mode = "overall" if opt.share == "overall" else "by_len"

    if opt.split_by_len:
        for span in spans:
            subset = [(g, n) for (g, n) in kept if g.length == span]
            if not subset:
                continue
            print(
                f"\n-------------------- TOP {opt.top} windows (len={span}) --------------------"
            )
            print(f"Total windows len={span}: {totals.get(span, 0)}")
            print_table(subset, totals, opt.top, mode, denom_all)
    else:
        print(f"Chunks: {len(chunks)}")
        print("Totals by len:", ", ".join(f"{s}={totals.get(s, 0)}" for s in spans))
        print(f"Overall total windows: {denom_all}")
        print(
            f"\n-------------------- TOP {opt.top} windows (len in {spans}) --------------------"
        )
        print_table(kept, totals, opt.top, mode, denom_all)

    return 0


if __name__ == "__main__":
    raise SystemExit(main())
