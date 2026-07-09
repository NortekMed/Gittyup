# 06 - Recurse Untracked Directories

Status: Already integrated

Source: `Nicolas01/Gittyup:RecurseUntrackedDirs`

Key upstream commit reviewed:
- `fa6bcd1d` - Recurse untracked directories

## Goal

Improve staging, discard, and display behavior for untracked directories.

## Current Behavior

The current GitNortek code already recurses untracked directories during status diff creation:

- `Repository::diffTreeToIndex()` adds `GIT_DIFF_RECURSE_UNTRACKED_DIRS` with `GIT_DIFF_INCLUDE_UNTRACKED` when untracked files are visible.
- `Repository::diffIndexToWorkdir()` applies the same recursion flag for workdir diffs.
- The behavior still respects the `untracked.hide` setting.

## Desired Behavior

- Untracked directories can be recursively expanded and handled.
- Stage/discard behavior should affect contained files predictably.
- Large generated directories should still be handled carefully.

## Implementation Plan

1. Keep the existing `GIT_DIFF_RECURSE_UNTRACKED_DIRS` usage in status diff generation.
2. Keep honoring `untracked.hide` so hidden untracked files are not expanded.
3. No code port is needed from `Nicolas01/Gittyup:RecurseUntrackedDirs` because the relevant implementation is already present.

## Acceptance Criteria

- Nested untracked files are visible/actionable from the UI when untracked files are shown.
- Stage/discard actions can operate on recursively discovered untracked files.
- Ignored files remain ignored.
- Build succeeds.

## Risk

Low. This is a documentation/status update for an already integrated diff option.
