# 03 - Lazy Diff Hunk Loading

Status: Planned

Source: `Nicolas01/Gittyup:fetchHunksAsNeeded`

Key upstream commits reviewed:
- `7e94c3bc` - Load files and hunks depending on scrollbar position
- `f3a1e792` - Fix discarding hunks and files
- `dbb89a94` - Fix file stage/unstage
- `bd064f4c` - Fix line stage/unstage
- `5545fee9` - Finalize line stage/unstage

## Goal

Improve responsiveness when viewing large diffs by loading files and hunks on demand instead of constructing the whole diff UI immediately.

## Current Behavior

Large commits can create many `FileWidget` and `HunkWidget` instances immediately, causing UI stalls and memory pressure.

## Desired Behavior

- The diff view should render the visible area quickly.
- Additional files/hunks should load as the user scrolls.
- Stage, unstage, discard, and line-level actions must remain correct for loaded and not-yet-loaded hunks.

## Implementation Plan

1. Study the current `DiffView`, `FileWidget`, `HunkWidget`, `Patch`, and `DiffTreeModel` architecture.
2. Do not blindly cherry-pick the branch because it is large and diverged.
3. Identify the smallest lazy-loading seam in current `DiffView`.
4. Preserve existing stage/unstage/discard tests before changing behavior.
5. Add or update tests around line/hunk stage behavior if feasible.
6. Port in small internal steps, but squash into one feature commit when stable.

## Acceptance Criteria

- Large diffs open faster or with visibly less initial work.
- Existing file/hunk/line stage, unstage, and discard behavior still works.
- `cmake --build build/local --target gitnortek` succeeds.
- Relevant tests pass or manual validation notes are added here.

## Risk

High. This feature touches core diff rendering and patch mutation behavior.
