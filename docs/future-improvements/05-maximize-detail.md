# 05 - Maximize Detail Pane

Status: Already integrated

Source: `Nicolas01/Gittyup:MaximizeDetail`

Key upstream commits reviewed:
- `25d396a8` - add State action
- `a9d8b86c` - add functions to maximize a widget in `mDetailSplitter`
- `f9878e31` - Toggle maximize when action is triggered

## Goal

Add a user action to maximize or restore the detail/diff pane.

## Current Behavior

The current GitNortek code already includes the maximize-detail feature:

- `RepoView::detailSplitterMaximize()` hides or restores widgets in `mDetailSplitter`.
- `MenuBar` exposes a `StateAction` labeled `Maximize`/`Normal` with `Ctrl+M`.
- The action applies the same maximized widget choice across open repository views.
- `MainWindow::addTab()` applies the current maximize state to newly opened tabs.

## Desired Behavior

- User can toggle a maximized detail view.
- Previous splitter layout is restored when toggled back.
- Existing maximize/fullscreen actions remain coherent.

## Implementation Plan

1. Keep the existing `RepoView::detailSplitterMaximize()` implementation.
2. Keep the existing `MenuBar` toggle wiring and `Ctrl+M` shortcut.
3. No code port is needed from `Nicolas01/Gittyup:MaximizeDetail` because the relevant implementation is already present.

## Acceptance Criteria

- Detail pane can be maximized/restored from the View menu or `Ctrl+M`.
- New tabs inherit the active maximize state.
- Build succeeds.

## Risk

Low. This is a documentation/status update for an already integrated feature.
