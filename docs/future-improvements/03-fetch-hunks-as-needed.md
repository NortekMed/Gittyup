# 03 - Lazy Diff Hunk Loading

Status: Integrated, with status-diff hunk loading intentionally conservative

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

The current GitNortek code already includes the core lazy-loading behavior from this feature: `DiffView` creates an initial batch of file/hunk widgets and fetches more as the scrollbar approaches the end. Commit diffs can also fetch hunks incrementally through `FileWidget::fetchMore()`.

Status diffs still materialize all hunks for a loaded file because file, hunk, and line staging currently depend on every hunk in the file being present. This preserves correctness for stage, unstage, discard, and line-level operations.

## Desired Behavior

- The diff view should render the visible area quickly.
- Additional files/hunks should load as the user scrolls.
- Stage, unstage, discard, and line-level actions must remain correct for loaded and not-yet-loaded hunks.

## Implementation Plan

1. Keep the existing file-level lazy loading in `DiffView`.
2. Keep incremental hunk loading enabled for non-status diffs.
3. Keep status-diff hunk loading eager until staging logic no longer depends on loaded widgets.
4. Fix programmatic full-load paths so `fetchAll()` bypasses the scrollbar-position guard and cannot stall when the viewport is not near the bottom.

## Acceptance Criteria

- Large diffs open with limited initial widget construction.
- Programmatic consumers such as `editors()` and `scrollToFile()` can force-load remaining files without depending on scrollbar position.
- Existing file/hunk/line stage, unstage, and discard behavior remains unchanged.
- `cmake --build build/local --target gitnortek` succeeds.
- Relevant tests pass or manual validation notes are added here.

## Risk

High if status-diff hunk loading is made fully lazy. The current integration avoids that risk by preserving eager per-file hunk loading for status diffs and only fixing the full-load control path.
