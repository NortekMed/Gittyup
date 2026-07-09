# 04 - Alternative Tree View

Status: Planned

Source: `Nicolas01/Gittyup:AlternativeTreeView`

Key upstream behavior reviewed:
- Alternative changed-file tree view.
- Show only one tree view when a commit is selected.
- Preserve expanded/collapsed state.
- Show all diffs when a folder is selected.

## Goal

Improve changed-file navigation and folder selection behavior in the commit/status file tree.

## Current Behavior

File tree behavior is functional but folder-level review and tree state preservation can be improved.

## Desired Behavior

- Selecting a folder can show all diffs inside that folder.
- Expanded/collapsed state survives refreshes where practical.
- Commit-selected views avoid unnecessary staged/unstaged duplication.
- Existing file selection and diff navigation remains predictable.

## Implementation Plan

1. Inspect the current `TreeView`, `TreeModel`, `TreeProxy`, `DoubleTreeWidget`, and `DiffTreeModel` relationships.
2. Port folder-selection behavior first if it can be isolated.
3. Port collapse-state preservation second.
4. Avoid replacing the whole tree view unless the current architecture blocks incremental work.
5. Update this plan if the feature must depend on lazy diff hunk loading.

## Acceptance Criteria

- Folder selection displays useful aggregated diffs.
- File selection behavior remains unchanged.
- Refresh does not unnecessarily destroy tree expansion state.
- Build succeeds.

## Risk

High. The source branch is a large UI refactor and overlaps with diff-view changes.
