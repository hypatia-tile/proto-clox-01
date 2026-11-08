# Retrospective

This repository was retired on 2026-11-08, partway through Step 1, renamed from
`clox` to `proto-clox-01`, and archived. This file is for whoever opens it
later — most likely its owner, starting clox again — and records where it
stopped, what is worth carrying over, and the design threads that were open
when it stopped.

## Why it stopped

Too much time had passed since the work was last active to pick it up where it
was. The owner chose to start again rather than resume.

## Where it stopped

| When | What |
| --- | --- |
| 2026-09-03 | Initial commit; working agreement and roadmap |
| 2026-09 | Step 0 (environment) complete, tagged `step0` |
| 2026-09-11 — 09-16 | ch14.1-14.3: `clox_count_t`, the memory layer, a writable `Chunk`; D-005 to D-008 recorded |
| *(seven weeks with no commits)* | |
| 2026-11-04 | ch14.4-14.6 written: line information, `Value` and the constant pool, the disassembler |
| 2026-11-08 | Retired |

The last four commits (`30ab3f8`, `2ac73bf`, `d15f42c`, `35c1e60`) are the
owner's ch14.4-14.6 work and its first test. They were pushed when the
repository was retired, **without a `step-review` and without their tests being
confirmed to run**. Treat them as a draft, not as reviewed code. No `ch14` tag
exists.

Two issues were closed at retirement without being finished:

- **#11** — the rest of Step 1. Its body is still the most complete statement of
  how ch14 maps onto this code base, including the "Known loose ends" and the
  unanswered comprehension question (why one `reallocate`, and why it wants the
  old size).
- **#9** — reporting which allocation failed. A small, self-contained design;
  it introduces the third failure category ("environment failure") alongside
  D-008's two.

## What is worth carrying over

- **`CLAUDE.md`** — the division of labour, the tag scheme, superseding instead
  of editing issues, "a check never modifies files".
- **`docs/divergences.md`** — D-001 to D-008. D-001 (AddressSanitizer deadlocks
  at init on this macOS) is an environment fact and will be true again.
  D-005 to D-008 are design decisions; a new attempt can adopt them, or reject
  them knowingly.
- **`docs/roadmap.md`** — the step list and the working contract.
- **`flake.nix` and `meson.build`** — a toolchain that was proven to work, with
  Criterion and clangd.

## Open design threads

Discussed with the owner in the last session, agreed in direction, never filed.

### Line information as its own module

Agreed: keep the book's name `line` (a `pos` that also carried columns was
considered and dropped), and choose the encoding at **compile time**, not
through function pointers.

- `src/lines.{h,c}` holding a `LineTable`; `Chunk` holds a `LineTable lines`
  member instead of `int *lines`.
- Four functions: `initLineTable`, `freeLineTable`,
  `writeLine(LineTable *, int line)` — an append, once per bytecode byte, with
  no offset — and `getLine(const LineTable *, clox_count_t offset)`.
- Every later `chunk->lines[offset]` in the book (ch18, ch24 runtime errors)
  translates to `getLine`.
- The parallel-array invariant (`code` and `lines` share count and capacity)
  disappears from the memory layout. What remains is logical: the number of
  `writeLine` calls equals `chunk->count`.
- Tests written against the interface alone become the equivalence check when
  the encoding is swapped.
- Order: the book's parallel array first, inside the module, on `main`; the
  module split as a divergence. Run-length encoding as Challenge 14.1 on a
  `challenge/ch14-rle-lines` branch.

### Run-length encoding (Challenge 14.1)

Two layouts for the runs array:

1. `(line, length)` per run — `getLine` walks and subtracts.
2. `(line, start offset)` per run, plus a total byte count — **the one
   recommended**. Start offsets are sorted, so `getLine` can binary search, and
   the total gives both the out-of-range check and the invariant above for free.

Line numbers are **not** monotonic (ch23's `for` increment clause), so search on
offsets, never on lines. Delta encoding, as in CPython's line table or Lua's
line info, is the next step beyond and more than clox needs.

### Every commit builds

The owner wanted Nix-managed tooling (treefmt, pre-commit) to guarantee that
every commit builds. Points established before it was set aside:

- A pre-commit hook builds the **working tree**, not the commit. An untracked
  file that `meson.build` lists passes the hook and fails a fresh checkout —
  `test/test_chunk.c` was in exactly that state. Partial commits
  (`git commit -- <paths>`) differ from the tree too. The hook should export the
  commit's contents into a temporary directory and build there.
- treefmt formats in place by default, which breaks "a check never modifies
  files". The hook must run in check-only mode; formatting in place is a
  separate command that says so (`nix fmt`).
- A hook can be skipped and covers one machine. The guarantee needs CI running
  `nix flake check` on **each pushed commit**, since several are pushed per
  step.
- Unsettled: whether the hook's script belongs in `scripts/` or
  `scripts/agents/`.

## Questions for the next attempt

Not conclusions — things to decide at the start rather than discover midway.

- Step 0 took a week, and ch14.1-14.3 produced four divergences and two issue
  supersessions before any bytecode existed. Is that depth what the learning is
  for, or should the first chapters run closer to the book and the refactoring
  start once the VM runs?
- Should per-commit build verification be part of Step 0 this time, before the
  first commit of code?
