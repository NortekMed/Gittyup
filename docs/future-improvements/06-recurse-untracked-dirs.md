# 06 - Recurse Untracked Directories

Status: Planned

Source: `Nicolas01/Gittyup:RecurseUntrackedDirs`

Key upstream commit reviewed:
- `fa6bcd1d` - Recurse untracked directories

## Goal

Improve staging, discard, and display behavior for untracked directories.

## Current Behavior

Untracked folders may be treated as a single item or require less convenient manual handling depending on status/diff context.

## Desired Behavior

- Untracked directories can be recursively expanded and handled.
- Stage/discard behavior should affect contained files predictably.
- Large generated directories should still be handled carefully.

## Implementation Plan

1. Inspect current status generation and `DiffTreeModel` handling of untracked entries.
2. Identify whether recursion belongs in git status collection, tree model expansion, or action execution.
3. Avoid accidentally recursing into ignored or huge directories without user intent.
4. Add tests or manual validation with nested untracked directories.

## Acceptance Criteria

- Nested untracked files are visible/actionable from the UI.
- Stage/discard actions recurse correctly when selected at folder level.
- Ignored files remain ignored.
- Build succeeds.

## Risk

Medium-high. Directory recursion can be expensive and destructive actions need careful safeguards.
