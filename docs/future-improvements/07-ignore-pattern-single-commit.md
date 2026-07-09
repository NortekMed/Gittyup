# 07 - Ignore Pattern Action

Status: Already integrated

Source: `Nicolas01/Gittyup:IgnorePatternSingleCommit`

Key upstream commit reviewed:
- `21614904` - IgnorePatternSingleCommit

## Goal

Add an ignore-pattern workflow from file context/status UI.

## Current Behavior

The current GitNortek code already includes the ignore-pattern workflow:

- `FileContextMenu` exposes an `Ignore` action for selected untracked files.
- `IgnoreDialog` lets the user confirm or edit the proposed newline-separated patterns.
- `RepoView::ignore()` appends the confirmed text to the repository `.gitignore` and refreshes the view.

## Desired Behavior

- User can invoke an ignore action from a file context menu.
- GitNortek proposes a useful pattern for the selected file or path.
- The chosen pattern is written to the appropriate ignore file.
- The view refreshes after the ignore operation.

## Implementation Plan

1. Keep the existing `FileContextMenu::ignoreFile()` workflow.
2. Keep the existing `IgnoreDialog` confirmation/edit step.
3. Keep writing to repository `.gitignore`; no product decision is currently needed because that is the implemented behavior.
4. No code port is needed from `Nicolas01/Gittyup:IgnorePatternSingleCommit` because the relevant implementation is already present.

## Acceptance Criteria

- Ignore action is available for selected untracked files.
- User can confirm or edit the pattern before writing.
- `.gitignore` is updated and the UI refreshes after confirmation.
- Build succeeds.

## Risk

Low. This is a documentation/status update for an already integrated workflow.
