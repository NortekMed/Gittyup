# 04 - Alternative Tree View

Status: Integrated, focused on folder selection correctness

Source: `Nicolas01/Gittyup:AlternativeTreeView`

Key upstream behavior reviewed:
- Alternative changed-file tree view.
- Show only one tree view when a commit is selected.
- Preserve expanded/collapsed state.
- Show all diffs when a folder is selected.

## Goal

Improve changed-file navigation and folder selection behavior in the commit/status file tree.

## Current Behavior

The current GitNortek code already includes the focused upstream behavior for folder-level diff selection: selected folder nodes expand to their child file model indexes, so the diff view can show all matching files.

The remaining issue was path matching correctness. The helper accepted substring matches in one direction, which meant similar sibling names such as `src/test` and `src/test.txt1` could be confused and the existing `Diff` tests did not match the implementation.

## Desired Behavior

- Selecting a folder can show all diffs inside that folder.
- Expanded/collapsed state survives refreshes where practical.
- Commit-selected views avoid unnecessary staged/unstaged duplication.
- Existing file selection and diff navigation remains predictable.

## Implementation Plan

1. Keep the existing folder selection flow through `DoubleTreeWidget`, `TreeView`, `DiffTreeModel::modelIndices()`, and `DiffView::updateFiles()`.
2. Fix `containsPath()` to be boundary-aware for exact paths and parent/child paths in either call direction.
3. Preserve the existing `Diff` path-matching tests and add a sibling-prefix regression case.
4. Do not port the broader historical tree-view refactor because the focused behavior is already present.

## Acceptance Criteria

- Folder selection displays aggregated diffs for files inside the selected folder.
- Folder matching does not include sibling paths with the same text prefix.
- File selection behavior remains unchanged.
- Build succeeds.

## Risk

Moderate. The broader source branch is a large UI refactor, but this integration only touches path matching and existing tests.
