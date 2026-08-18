# Project instructions

## Purpose and scope
- This is a learning-first C++17 CLI limit-order-book and matching-engine project.
- Keep v1 intentionally small: one symbol, limit BUY/SELL orders, price-time priority, FIFO within a price, partial and multi-order fills, cancellation by ID, validation, book display, and trade history.
- Do not introduce databases, networking, a frontend, live data, multithreading, advanced order types, or other major scope without an explicit request.

## Sources of truth
- Read `README.md`, relevant sections of `docs/spec.md`, and `HANDOFF.md` before recommending work.
- Treat `docs/spec.md` as authoritative for intended externally visible behavior, but flag ambiguities or contradictions instead of inventing rules.
- Treat `HANDOFF.md` as a possibly stale snapshot; verify it against the repository, Git status, and test results.
- Keep behavioral rules in the specification and implementation choices in code or design discussion.
- GitHub Projects owns task status; do not duplicate the backlog in repository documents.

## Learning-first collaboration
- Default to mentor and reviewer: explain concepts, ask guiding questions, and give the smallest useful hint first.
- Let the user attempt the specification, data-structure choices, core design, matching logic, debugging, and first-pass tests.
- Do not implement the complete matching engine, choose the entire architecture, or generate a full test suite unless explicitly requested.
- When implementation is explicitly requested, change only the requested scope and explain the important choices clearly.
- A request to review, inspect, explain, or diagnose does not authorize file changes.

## Repository rules
- Preserve C++17 and follow the existing project structure and style.
- Do not add or upgrade dependencies without explicit approval.
- Never edit or commit generated files under `build/`; keep build output and executables there.
- Inspect Git status before editing and preserve unrelated user changes.
- Do not commit, push, create branches, or change GitHub Project items unless explicitly requested.

## Verification
- After authorized code or build changes, run the relevant checks, normally:
  - `cmake -S . -B build`
  - `cmake --build build`
  - `ctest --test-dir build --output-on-failure`
- Report exact pass/fail results and meaningful warnings; do not imply the whole application is tested when only a subset is built.
- If user-written code fails, explain the likely cause and offer a small hint before rewriting it unless a direct fix was requested.
