# 05 - Maximize Detail Pane

Status: Planned

Source: `Nicolas01/Gittyup:MaximizeDetail`

Key upstream commits reviewed:
- `25d396a8` - add State action
- `a9d8b86c` - add functions to maximize a widget in `mDetailSplitter`
- `f9878e31` - Toggle maximize when action is triggered

## Goal

Add a user action to maximize or restore the detail/diff pane.

## Current Behavior

The detail pane shares space with the sidebar and log. Reviewing large diffs may require manual splitter adjustment.

## Desired Behavior

- User can toggle a maximized detail view.
- Previous splitter layout is restored when toggled back.
- Existing maximize/fullscreen actions remain coherent.

## Implementation Plan

1. Inspect current `RepoView` splitter handling and existing maximize menu actions.
2. Add a small reusable state action only if necessary.
3. Prefer minimal `RepoView` methods over broad UI refactor.
4. Add toolbar/menu wiring if it matches current design.

## Acceptance Criteria

- Detail pane can be maximized/restored from UI.
- State survives normal refreshes while the view is open.
- Build succeeds.

## Risk

Medium-high. The source branch depends on broader diff-view refactor, so implementation should be adapted to current GitNortek.
